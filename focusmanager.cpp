#include "focusmanager.h"

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <algorithm>

void FocusManager::handleAccessRequest(){
    QString s = (*edit)->text();
    QUrl url = QUrl(s);
    QMessageBox msgBox;
    msgBox.setText("You are trying to access: " + s);
    msgBox.exec();
    if(isWhitelisted(url)){
        emit pass();
    }
    else{
        msgBox.setText("Access Denied");
        msgBox.exec();
        emit stop();
    }
}

void FocusManager::handleTypeAccess(QLineEdit* edit){

    if(!onFocus){
        emit pass();
        return;
    }

    QUrl url = QUrl(edit->text());
    if(isWhiteListed(url)){
        emit pass();
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("C-You are about to get distracted! Stay Focus!");
        msgBox.exec()
    }
}


FocusManager::FocusManager(QLineEdit*& edit) :
    QObject(),
    edit(&edit),
    recordDirectory(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/comp2012h_project"),
    recordPath(recordDirectory + "/record.txt")
{
    //Make directory if it does not exist
    if (!QDir(recordDirectory).exists())
            QDir().mkpath(recordDirectory);

    QFile file(recordPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);

    while (!in.atEnd())
        whitelist.insert(QUrl(in.readLine()).host());

    whitelist.insert(QUrl("ust.hk").host());

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

void FocusManager::handleClickAccess(QLineEdit* edit, WebView* tab){

    QUrl url = tab->url();
    if(url.toDisplayString() == "") return;

    if(!onFocus){
        edit->setText(url.toDisplayString());
        return;
    }

    if(tab->urlJustChanged){
        tab->urlJustChanged = false;
        edit->setText(url.toDisplayString());
        return;
    }

    if(isWhiteListed(url)){
        edit->setText(url.toDisplayString());
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("C-You are about to get distracted! Stay Focus!");
        msgBox.exec();
        tab->urlJustChanged = true;
        tab->setUrl(QUrl(edit->text()));
    }
}
