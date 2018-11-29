#include "EditWindow.h"
#include "ui_EditWindow.h"

EditWindow::EditWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditWindow)
{
    ui->setupUi(this);

    //Set Column to 1
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QURL, QHeaderView::Stretch);

    //Set header
    QStringList header;
    header << "Allowed Url";
    ui->tableWidget->setHorizontalHeaderLabels(header);
}

EditWindow::~EditWindow()
{
    delete ui;
}

void EditWindow::add(QString url){
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, QURL, new QTableWidgetItem(url));
    //Emit add signal to the manager
}

void EditWindow::on_pushButton_clicked()
{
    bool ok = false;
    QString url = QInputDialog::getText(this, "New URL", "Please type in a new url:", QLineEdit::Normal, "", &ok);

    if(!ok){
        return;
    }
    if(url == ""){
        QMessageBox::information(nullptr, "Error", "The url is empty!");
    }
    else if(false){     //Checking here

        QMessageBox::information(nullptr, "Error", "The website is already in the whitelist!");
    }
    else{
        this->add(url);
    }
}

void EditWindow::on_pushButton_2_clicked()
{
    if(ui->tableWidget->selectionModel()->selectedRows().size() <= 0){
        QMessageBox::information(nullptr, "Error", "No url selected!");
    }
    else{
        ui->tableWidget->removeRow(ui->tableWidget->selectionModel()->currentIndex().row());
        //Emit delete signal to the manager
    }
}
