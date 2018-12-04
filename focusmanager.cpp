#include "focusmanager.h"

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <algorithm>
#include <iostream>

//Performs checking when the user tries to visit websites via the URL bar
void FocusManager::handleTypeAccess(QLineEdit* edit){

    QString s = edit->text(); // Get URL text
    if(!s.contains("https://"))  // Correct URL format
        s = "https://" + s;
    QUrl url = QUrl(s);

    if(isWhitelisted(url)){
        emit pass();  // If it is in white list emit pass signal
    }
    else{
        QMessageBox::information(nullptr, "Calm Down", "You are about to get distracted, Stay Focus!"); // Warning otherwise
    }

}

// Performs checking when the user clicks on a link
void FocusManager::handleClickAccess(QLineEdit* edit, WebView* tab){

    QUrl url = tab->url(); // Get link URL
    if (url.toEncoded() == "") return; // Prevent invalid message during construction of tab

    if(isWhitelisted(url)){
        edit->setText(url.toDisplayString()); // If URL is in whitelist set URL bar text
        tab->isNew = false; // Set to false because an URL has already been loaded
    }
    else{
        QMessageBox::information(nullptr, "Calm Down", "You are about to get distracted, Stay Focus!");
        if(tab->isNew)
            tab->deleteLater(); // If a new tab is not in whitelist close it
        tab->back(); // If a old tab leave the whitelist go back to previous page
    }
}

//Constructor
FocusManager::FocusManager() :
    QObject(),
    recordDirectory(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/comp2012h_project"),
    recordPath(recordDirectory + "/record.txt"),
    onFocus(true)
{
    //Make directory if it does not exist
    if (!QDir(recordDirectory).exists())
            QDir().mkpath(recordDirectory);

    //Prepare to read file
    QFile file(recordPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file); 

    while (!in.atEnd())
        whitelist.insert(in.readLine()); // Read and insert to AVL

    whitelist.insert(QUrl("https://www.ust.hk").host()); // Default whitelist
    whitelist.insert(QUrl("https://www.google.com").host()); // Default whitelist

    whitelist.remove("");

    file.close();
}

//Destructor
FocusManager::~FocusManager()
{
    QFile file(recordPath);
    file.remove(); //Clean existing file

    //Prepare to write file
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream out(&file);

    //Wirte all URLs in whitelist to file
    whitelist.in_order_action([&](const QString& s){out << s << endl;});
}


// Check whether URL is in whitelist
bool FocusManager::isWhitelisted(const QUrl& url) const
{
    if(!onFocus) return true; // Alwats true if focus mode is off
    return whitelist.contains(url.host());
}

// Add an URL to the whitelist
void FocusManager::addToWhitelist(const QUrl& url)
{
    if (url.toEncoded() == "") // Prevent empty URL input
        return;

    whitelist.insert(url.host());
}

//Delete an URL from the whitelist
void FocusManager::deleteFromWhitelist(const QUrl& url)
{
    return whitelist.remove(url.host());
}

// Other users can communicate with THE focus manager through fm(). 
// This is to prevent multiple instantiation of focusmanger i.e. enforcing singleton. 
FocusManager& fm()
{
    static FocusManager fm;
    return fm;
}

