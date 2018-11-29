#include "focusmanager.h"

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <algorithm>
#include <iostream>

void FocusManager::handleTypeAccess(QLineEdit* edit){

    QString s = edit->text();
    if(!s.contains("https://"))
        s = "https://" + s;
    QUrl url = QUrl(s);

    if(isWhitelisted(url)){
        emit pass();
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("You are about to get distracted, Stay Focus!");
        msgBox.exec();
    }

}


void FocusManager::handleClickAccess(QLineEdit* edit, WebView* tab){

    QUrl url = tab->url();
    if (url.toEncoded() == "") return;

    if(tab->urlJustChanged){
        tab->urlJustChanged = false;
        edit->setText(url.toDisplayString());
        return;
    }

    if(isWhitelisted(url)){
        edit->setText(url.toDisplayString());
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("You are about to get distracted, Stay Focus !");
        msgBox.exec();
        tab->urlJustChanged = true;
        if(url == QUrl(edit->text()))
            tab->setUrl(QUrl("https://www.ust.hk"));
        else
            tab->setUrl(QUrl(edit->text()));
    }

}


//Need to Implement Read File
FocusManager::FocusManager() :
    QObject(),
    recordDirectory(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/comp2012h_project"),
    recordPath(recordDirectory + "/record.txt"),
    onFocus(true)
{
    //Make directory if it does not exist
    if (!QDir(recordDirectory).exists())
            QDir().mkpath(recordDirectory);

    QFile file(recordPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);

    while (!in.atEnd())
        whitelist.insert(QUrl(in.readLine()).host());

    whitelist.insert(QUrl("https://www.ust.hk").host());
    whitelist.insert(QUrl("https://www.google.com").host());

    file.close();
}


FocusManager::~FocusManager()
{
    QFile file(recordPath);
    file.remove();

    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream out(&file);

    whitelist.in_order_action([&](const QString& s){out << s << endl;});
}


bool FocusManager::isWhitelisted(const QUrl& url) const
{
    if(!onFocus) return true;
    return whitelist.contains(url.host());
}

void FocusManager::addToWhitelist(const QUrl& url)
{
    return whitelist.insert(url.host());
}

void FocusManager::deleteFromWhitelist(const QUrl& url)
{
    return whitelist.remove(url.host());
}



