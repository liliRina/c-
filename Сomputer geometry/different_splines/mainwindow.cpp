#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->draw_widget->SetTaskPtr(&current_task);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    current_task.points.clear();
    ui->count_label->setText(QString::number(current_task.points.size()));
    ui->draw_widget->repaint();
}

void MainWindow::on_addPoint_clicked()
{
    ui->draw_widget->addPoint();
    ui->count_label->setText(QString::number(current_task.points.size()));
    ui->draw_widget->repaint();
}

void MainWindow::on_deletePoint_clicked()
{
    ui->draw_widget->deletePoint();
    ui->count_label->setText(QString::number(current_task.points.size()));
    ui->draw_widget->repaint();
}

void MainWindow::on_radioButton_clicked()
{
    ui->draw_widget->state = 1;
    ui->draw_widget->repaint();
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (!ui->draw_widget->parametrical)
        ui->draw_widget->parametrical = 1;
    else
        ui->draw_widget->parametrical = 0;
    ui->draw_widget->repaint();
}


void MainWindow::on_radioButton_2_clicked()
{
    ui->draw_widget->state = 2;
    ui->draw_widget->repaint();
}


void MainWindow::on_radioButton_3_clicked()
{
    ui->draw_widget->state = 3;
    ui->draw_widget->repaint();
}

