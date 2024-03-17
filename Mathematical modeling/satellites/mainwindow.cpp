#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->_mainTimer = new QTimer();
    this->wi=new miWidget();
    connect(this->_mainTimer, SIGNAL(timeout()), this, SLOT(on_timeChangedSlot()));
}

void MainWindow::on_timeChangedSlot()
{
    epochTime+=1;
    cnt++;
    //std::cout<<epochTime<<std::endl;
    ui->widget->My_world->world_Update(epochTime);
    ui->widget->update();

    /* cout << "v_x: "<< _world->vector_objects[0]->currCoord[3] << " v_y: " << _world->vector_objects[0]->currCoord[4] << endl;
    cout << "|V|: " << sqrt(pow(_world->vector_objects[0]->currCoord[3], 2) + pow(_world->vector_objects[0]->currCoord[4], 2)) << endl;
    cout << "Earth_y: " << _world->vector_objects[0]->currCoord[1] << " Moon_y:_" << _world->vector_objects[1]->currCoord[1] << endl;
    cout << "|V_Sun|: " << sqrt(pow(_world->vector_objects[2]->currCoord[3], 2) + pow(_world->vector_objects[2]->currCoord[4], 2)) << endl;
    if (is_custom_cluster == false)
    {
        if(k_1%60 == 0)
        {
            double r_model;
            double r_cTle;

            for(int i = 1; i < this->_world->vector_objects.size(); i++)
            {
                r_model = sqrt(pow(_world->vector_objects[i]->currCoord[0], 2) + pow(_world->vector_objects[i]->currCoord[1], 2) + pow(_world->vector_objects[i]->currCoord[2], 2));
                r_cTle = sqrt(pow(satellites[i-1].PositionEci(k_2).Position().m_x, 2) + pow(satellites[i-1].PositionEci(k_2).Position().m_y, 2) + pow(satellites[i-1].PositionEci(k_2).Position().m_z, 2));

                energy_norm += pow(abs(r_model - r_cTle), 2);
            }
            //cout << sqrt(energy_norm) << endl;
            ui->lcdNumber->display(sqrt(energy_norm));
            //cout << _world->vector_objects[1]->currCoord[0] << " " << satellites[0].PositionEci(k_2).Position().m_x << endl;
            k_2++;
        }
        k_1++;
    }
    // std::cout << "Timer changed! " << std::endl;
    // this->_world->Update(QDateTime::currentSecsSinceEpoch());*/
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startTimerButton_clicked()
{
    if(!this->_mainTimer->isActive())
    {
        this->_mainTimer->start(250); // cколько тут укажем, так часто будет вызывать timechangeedslot
        std::cout << "Timer started! " << std::endl;

    }
    else
    {
        this->_mainTimer->stop();
        std::cout << "Timer stopped! " << std::endl;
    }
}

