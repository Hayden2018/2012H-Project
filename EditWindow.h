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
    enum heading{
        QURL
    };
    void add(QString url);      //add a new url
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::EditWindow *ui;
};

#endif // EDITWINDOW_H
