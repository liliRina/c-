#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <algo.h>
#include "../qcustomplot/qcustomplot.h"
#include <QTimer>
#include <string>
//#include "exprtk.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
enum cur_alg { PSO = 0, PSO_inertia=1, LBPSO = 2, With_dead=3, With_fire=4, Genetic=5};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    algo *a;
    //void trig_function();

protected slots:
    void onTimeout();
private slots:
    void on_button_clicked();

    //void on_lineEdit_editingFinished();

    void on_comboBox_currentTextChanged(const QString &arg1);
private:
    Ui::MainWindow *ui;
    double x1=-10,
    x2=10,
    y1=-10,
    y2=10;
    QTimer* _timer = new QTimer(this);
    std::string function="NONE";
    std::string algor="метод роя частиц";
    bool start=0;
    cur_alg alg=PSO;
};



#endif // MAINWINDOW_H
