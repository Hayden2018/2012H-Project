#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
signals:
    void loginSuccess();
    void loginFail();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::LoginWindow *ui;
    QString USERNAME;
    QString PASSWORD;
};

#endif // LOGINWINDOW_H
