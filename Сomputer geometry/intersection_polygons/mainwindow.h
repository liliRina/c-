#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "task_data.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:

    task_data current_task;



public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*
    void on_pushButton_clicked();
    void on_points_Changed();

    void on_Ax_changed(const QString& txt);
*/

    void on_add_clicked();
    void on_coord1_textChanged(const QString &arg1);
    void on_coord2_textChanged(const QString &arg1);

    void on_add2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
