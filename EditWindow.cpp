#include "EditWindow.h"
#include "ui_EditWindow.h"
#include "focusmanager.h"


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

    fm().whitelist.in_order_action([this](const QString& s){add(s);});

    if(fm().onFocus){
        ui->radioButton->setChecked(true);
    }
    else
    {
        ui->radioButton_2->setChecked(true);
    }
}

EditWindow::~EditWindow()
{
    delete ui;
}

void EditWindow::add(QString url){
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, QURL, new QTableWidgetItem(url));
    if (!url.contains("https://"))
        url = "https://" + url;
    // modify the whitelist
    fm().addToWhitelist(url);
}

void EditWindow::on_pushButton_clicked()
{
    bool ok = false;
    QString url = QInputDialog::getText(this, "New URL", "Please type in a new url:", QLineEdit::Normal, "", &ok);
    QString t_url = url;
    if (!t_url.contains("https://"))
        t_url = "https://" + t_url;

    if(!ok){
        return;
    }
    if(url == ""){
        QMessageBox::information(nullptr, "Error", "The url is empty!");
    }
    else if(fm().isWhitelisted(t_url)){     //Checking here
        QMessageBox::information(nullptr, "Error", "The website is already in the whitelist!");
    }
    else{
        this->add(url);
    }
}

void EditWindow::on_pushButton_2_clicked()
{
    int r = ui->tableWidget->selectionModel()->currentIndex().row();
    int c = ui->tableWidget->selectionModel()->currentIndex().column();
    QString str = ui->tableWidget->item(r, c)->text();
    if(ui->tableWidget->rowCount() == 1){
        QMessageBox::information(nullptr, "I Beg You", "Please don't delete your only friend T_T");
        return;
    }
    if (!str.contains("https://"))
        str = "https://" + str;

    if(ui->tableWidget->selectionModel()->selectedRows().size() <= 0){
        QMessageBox::information(nullptr, "Error", "No url selected!");
    }
    else{
        ui->tableWidget->removeRow(ui->tableWidget->selectionModel()->currentIndex().row());
        // delete in whitelist
        fm().deleteFromWhitelist(str);
    }
}

void EditWindow::on_radioButton_clicked()
{
    fm().onFocus = true;
    ui->tableWidget->setEnabled(true);
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
}

void EditWindow::on_radioButton_2_clicked()
{
    fm().onFocus = false;
    ui->tableWidget->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
}
