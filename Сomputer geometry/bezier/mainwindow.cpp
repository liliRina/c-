#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->draw_widget->SetTaskPtr(&current_task);

    // инициализация задачи
    ui->draw_widget->SetDefaultPoints();



    connect(ui->draw_widget, SIGNAL(signalPointsChanged()), this, SLOT(on_points_Changed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    // инициализация задачи
    ui->draw_widget->SetDefaultPoints();
    ui->draw_widget->repaint();
}




void MainWindow::on_plus_clicked()
{
    vector2d A(500, 500);
    current_task.points.push_back(A);
    current_task.schitaim_ch();
    ui->draw_widget->repaint();

}

