#ifndef FOCUSMANAGER_H
#define FOCUSMANAGER_H
/* File: focusmanager.h */

/* 
 * This class is the manager responsible for the focus mode
 * The whitelist is handled and stored by this class,
 * as well as offline storage of the whitelist
 */

#include <QMessageBox>
#include <QLineEdit>
#include <QUrl>
#include <QString>
#include "avl.h"
#include "webview.h"

class FocusManager : public QObject {

    friend class EditWindow;

     Q_OBJECT
     AVL<QString> whitelist;
     const QString recordDirectory;
     const QString recordPath;
     bool isWhitelisted(const QUrl& url) const; // Check whether URL is in whitelist
     FocusManager(const FocusManager&); // Prevent copy of focusmanager
     void operator=(const FocusManager&); // Prevent copy of focusmanager

public:

    bool onFocus; // if focus mode has been enabled

    FocusManager();
    ~FocusManager();
    void addToWhitelist(const QUrl& url); // Add an URL to the whitelist
    void deleteFromWhitelist(const QUrl& url); //Delete an URL from the whitelist
    void handleTypeAccess(QLineEdit* edit); // Performs checking when the user tries to visit websites via the URL bar
    void handleClickAccess(QLineEdit* edit, WebView* tab); // Performs checking when the user clicks on a line

signals:
    void pass(); //Signal that a webiste typed in the URL bar is whitelisted
};


FocusManager& fm(); // Other users can communicate with THE focus manager through fm(). 
                    // This is to prevent multiple instantiation of focusmanger i.e. enforcing singleton. 

#endif // FOCUSMANAGER_H
