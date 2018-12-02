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
    void loginSuccess();    //Emit signal to browser window if the login information is correct
    void loginFail();       //Emit signal to browser window if the login information is wrong

private slots:
    void on_buttonBox_accepted();   //Check login information if the OK button is clicked

private:
    Ui::LoginWindow *ui;
    QString USERNAME;           //A constant to store correct username
    QString PASSWORD;           //A constant to store correct password
};

#endif // LOGINWINDOW_H
