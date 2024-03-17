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

    //ui->le_Ax->setText("TEST LINE EDIT");
    on_points_Changed();

    connect(ui->draw_widget, SIGNAL(signalPointsChanged()), this, SLOT(on_points_Changed()));
    connect(ui->le_Ax, SIGNAL(textEdited(const QString &)), this, SLOT(on_Ax_changed(const QString &)));
    connect(ui->le_Ay, SIGNAL(textEdited(const QString &)), ui->draw_widget, SLOT(on_Ay_changed(const QString &)));
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

void MainWindow::on_points_Changed()
{
  ui->le_Ax->setText(QString::number(current_task.A.x));
  ui->le_Ay->setText(QString::number(current_task.A.y));

  ui->le_Bx->setText(QString::number(current_task.B.x));
  ui->le_By->setText(QString::number(current_task.B.y));

  ui->le_Cx->setText(QString::number(current_task.C.x));
  ui->le_Cy->setText(QString::number(current_task.C.y));
  //std::cout<<current_task.turn_<<std::endl;

  ui->turn->setText(QString::fromStdString(current_task.turn_));
}

void MainWindow::on_Ax_changed(const QString& txt)
{
  // some validation
  bool flag = true;
  double val = txt.toDouble(&flag);
  if(!flag)
  {
      QMessageBox msgBox;
      msgBox.setText("Error in coordinate x of point A.");
      msgBox.exec();

      ui->le_Ax->setText(QString::number(current_task.A.x));
  }
  else {
    current_task.A.x = val;
  }

  //current_task.testIntersection();
  current_task.it_turn();
  ui->draw_widget->repaint();
}
