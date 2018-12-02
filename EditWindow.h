#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QInputDialog>
namespace Ui {
class EditWindow;
}

class EditWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditWindow(QWidget *parent = nullptr);
    ~EditWindow();
    enum heading{ QURL };       //Just for readability
    void add(QString url);      //add a new url into the AVL tree and update the Table Widget screen

signals:
    void refocus();

private slots:
    void on_pushButton_clicked();       //Handling add function
    void on_pushButton_2_clicked();     //Handling remove function

    void on_radioButton_clicked();      //Enable focus mode
    
    void on_radioButton_2_clicked();    //Disable focus mode and disable add and remove functions

private:
    Ui::EditWindow *ui;
};

#endif // EDITWINDOW_H
