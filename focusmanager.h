#ifndef FOCUSMANAGER_H
#define FOCUSMANAGER_H


#include "QMessageBox"
#include "QLineEdit"
#include <QUrl>
#include <QString>
#include "avl.tpp"

class FocusManager : public QObject {

     Q_OBJECT
     QLineEdit** edit; //move it under private??

 public:
    bool isWhitelisted(const QUrl& url) const;
    void addToWhitelist(const QUrl& url);
    void deleteFromWhitelist(const QUrl& url);

    FocusManager(QLineEdit*& edit);
    ~FocusManager();

public slots:
    void handleAccessRequest();

signals:
    void pass();
    void stop();

private:
    AVL<QString> whitelist;
    const QString recordDirectory;
    const QString recordPath;

    FocusManager(const FocusManager&);
    void operator=(const FocusManager&);

};
#endif // FOCUSMANAGER_H
