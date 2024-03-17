#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <QFile>
#include <QString>
#include "world.h"
#include <cmath>
#include <ctime>
#include <QVector>
#include <QString>
#include <fstream>
#include <string>
#include <iostream>
#include "core/cTLE.h"
#include "orbit/cOrbit.h"
#include "miwidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_startTimerButton_clicked();
    void on_timeChangedSlot();

private:
    Ui::MainWindow *ui;
    QTimer* _mainTimer;

    int epochTime=0;
    miWidget *wi;
    int cnt=0;

};
#endif // MAINWINDOW_H
