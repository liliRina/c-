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
    //connect(ui->coord1, SIGNAL(textEdited(const QString &)), this, SLOT(on_Ax_changed(const QString &)));
/*    connect(ui->le_Ay, SIGNAL(textEdited(const QString &)), ui->draw_widget, SLOT(on_Ay_changed(const QString &)));
*/
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_add_clicked()
{
    vector2d A(current_task.new_x, current_task.new_y);
    current_task.points.push_back(A);
    ui->draw_widget->shell();
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

