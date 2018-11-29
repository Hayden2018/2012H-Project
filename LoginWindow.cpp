#include "LoginWindow.h"
#include "ui_LoginWindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow),
    USERNAME("comp2012h"),
    PASSWORD("comp2012hdesmond")
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_buttonBox_accepted()
{
    QString usr = ui->m_userNameLineEdit->text();
    QString pwd = ui->m_passwordLineEdit->text();

    if(usr == USERNAME  && pwd == PASSWORD){
        emit loginSuccess();
    }
    else{
        emit loginFail();
    }
}
