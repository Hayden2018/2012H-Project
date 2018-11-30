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
    enum header{ QURL };
    void add(QString url);      //add a new url

signals:
    void refocus();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    //Update url
    void updateUrl(const QModelIndex &indexA, const QModelIndex &indexB);
    void setPrevSelected(const QModelIndex & current, const QModelIndex & previous);  //set the prevSelected
private:
    Ui::EditWindow *ui;
    QString prevSelected;     //store the previous selected cell
    bool justAdded;     //Check if a new element is just added to prevent calling updateUrl when adding a new url
};

#endif // EDITWINDOW_H
