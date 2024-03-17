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
    void on_addPoint_clicked();
    void on_deletePoint_clicked();
    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
