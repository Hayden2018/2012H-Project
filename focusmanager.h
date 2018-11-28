#ifndef FOCUSMANAGER_H
#define FOCUSMANAGER_H

#endif // FOCUSMANAGER_H

#include <QMessageBox>
#include <QLineEdit>
#include <QUrl>
#include "webview.h"

class FocusManager : public QObject {

     Q_OBJECT
     bool isWhiteListed(QUrl url);
     //Need AVL tree member here

public:
    bool onFocus;
    FocusManager(); //Need to implement read file
    ~FocusManager(); //Need to implement write file
    //Need to implement add function
    //Need to implement remove function
    void handleTypeAccess(QLineEdit* edit);
    void handleClickAccess(QLineEdit* edit, WebView* tab);

signals:
    void pass();
};
