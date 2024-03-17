#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->draw_widget->SetTaskPtr(&current_task);

    // инициализация задачи
    ui->draw_widget->SetDefaultPoints();

    //ui->le_Ax->setText("TEST LINE EDIT");
    //on_points_Changed();

    //connect(ui->draw_widget, SIGNAL(signalPointsChanged()), this, SLOT(on_points_Changed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
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

  ui->le_Dx->setText(QString::number(current_task.D.x));
  ui->le_Dy->setText(QString::number(current_task.D.y));
}
*/


void MainWindow::on_add2_clicked()
{
    vector2d A(10, 10);
    current_task.points.push_back(A);
    ui->draw_widget->repaint();
}


void MainWindow::on_coord1_textChanged(const QString &arg1)
{
    current_task.new_x=arg1.toDouble();
}


void MainWindow::on_coord2_textChanged(const QString &arg1)
{
    current_task.new_y=arg1.toDouble();
}


void MainWindow::on_add_clicked()
{
    vector2d A(10, 10);
    current_task.points2.push_back(A);
    ui->draw_widget->repaint();
}

