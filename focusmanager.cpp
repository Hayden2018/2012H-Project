#include "focusmanager.h"

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
        msgBox.exec();
    }
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


//Need to Implement Read File
FocusManager::FocusManager() :
    QObject(),
    onFocus(true)
{}

//Need to Implement Write File
FocusManager::~FocusManager(){}


bool FocusManager::isWhiteListed(QUrl url){
    if (url == QUrl("https://www.ust.hk")) return true;
    return false;
}
