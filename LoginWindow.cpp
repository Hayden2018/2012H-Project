#include "LoginWindow.h"
#include "ui_LoginWindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow),
    USERNAME("comp2012h"),          //setting username
    PASSWORD("comp2012hdesmond")    //setting password
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_buttonBox_accepted()
{
    QString usr = ui->m_userNameLineEdit->text();       //Get username from the corresponding line edit
    QString pwd = ui->m_passwordLineEdit->text();       //Get password from the corresponding line edit

    if(usr == USERNAME  && pwd == PASSWORD){        //Check if login information is correct
        emit loginSuccess();                        //If both are correct, emit success signal
    }
    else{
        emit loginFail();                           //If either one is wrong, emit fail signal
    }
}
