#ifndef FOCUSMANAGER_H
#define FOCUSMANAGER_H

#endif // FOCUSMANAGER_H

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
     bool isWhitelisted(const QUrl& url) const;
     FocusManager(const FocusManager&);
     void operator=(const FocusManager&);

public:

    bool onFocus;

    FocusManager();
    ~FocusManager();
    void addToWhitelist(const QUrl& url);
    void deleteFromWhitelist(const QUrl& url);
    void handleTypeAccess(QLineEdit* edit);
    void handleClickAccess(QLineEdit* edit, WebView* tab);
    void handleNewTab(QLineEdit* edit, WebView* tab);

signals:
    void pass();
};


FocusManager& fm();

