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
    
    //Traverse the original AVL tree and add all the elements inside to the current QTable
    fm().whitelist.in_order_action([this](const QString& s){add(s);});

    if(fm().onFocus){
        //If the focus mode is enabled, enable add, remove and QTable elements
        ui->radioButton->setChecked(true);
        ui->tableWidget->setEnabled(true);
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
    }
    else
    {
        //If the focus mode is disabled, disable all the elements
        ui->radioButton_2->setChecked(true);
        ui->tableWidget->setEnabled(false);
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
    }
}

EditWindow::~EditWindow()
{
    delete ui;
}

//Add a new URL
void EditWindow::add(QString url){
    //Insert a new row in the Table Widget first
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    //Set the content to url
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, QURL, new QTableWidgetItem(url));
    
    //Add prefix to the url and add to the white list in focus manager
    if (!url.contains("https://"))
        url = "https://" + url;
    // modify the whitelist
    fm().addToWhitelist(url);
}

void EditWindow::on_pushButton_clicked()
{
    //Get a new url through QInputDialog
    bool ok = false;
    QString url = QInputDialog::getText(this, "New URL", "Please type in a new url:", QLineEdit::Normal, "", &ok);
    QString t_url = url;
    if (!t_url.contains("https://"))
        t_url = "https://" + t_url;
   
    //Return if cancel is clicked
    if(!ok){
        return;
    }
    
    if(url == ""){
        //If it is empty, ouput a message
        QMessageBox::information(nullptr, "Error", "The url is empty!");
    }
    else if(fm().isWhitelisted(t_url)){
        //Check if the url is already exist in the white list.
        QMessageBox::information(nullptr, "Error", "The website is already in the whitelist!");
    }
    else{
        //Add if it is not exist in the white list
        this->add(url);
    }
}

void EditWindow::on_pushButton_2_clicked()
{
    //Get the content in the selected row
    int r = ui->tableWidget->selectionModel()->currentIndex().row();
    int c = ui->tableWidget->selectionModel()->currentIndex().column();
    QString str = ui->tableWidget->item(r, c)->text();
    
    //Don't delete if there is only one url left
    if(ui->tableWidget->rowCount() == 1){
        QMessageBox::information(nullptr, "I Beg You", "Please don't delete your only friend T_T");
        return;
    }
    
    //Add prefix to the str
    if (!str.contains("https://"))
        str = "https://" + str;
    
    //Check if any url is selected
    if(ui->tableWidget->selectionModel()->selectedRows().size() <= 0){
        QMessageBox::information(nullptr, "Error", "No url selected!");
    }
    else{
        //Remove the row
        ui->tableWidget->removeRow(ui->tableWidget->selectionModel()->currentIndex().row());
        // delete in whitelist
        fm().deleteFromWhitelist(str);
    }
    emit refocus();
}

void EditWindow::on_radioButton_clicked()
{
    //Set onFocus to true
    fm().onFocus = true;
    //Enable all the elements
    ui->tableWidget->setEnabled(true);
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    emit refocus();
}

void EditWindow::on_radioButton_2_clicked()
{
    //Set onFocus to true
    fm().onFocus = false;
    //Disable all the elements
    ui->tableWidget->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
}
