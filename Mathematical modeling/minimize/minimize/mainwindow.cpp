#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    a=new algo();

    //setGeometry(QApplication::desktop()->screenGeometry());
    setGeometry(500, 500, 1100, 1000);
    ui->widget->rescaleAxes();

    ui->widget->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    ui->widget->axisRect()->setupFullAxesBox(true);
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    ui->widget->xAxis->setRange(x1, x2);
    ui->widget->yAxis->setRange(y1, y2);
    ui->centralwidget->resize(1000, 1000);
    QCPColorMap *colorMap = new QCPColorMap(ui->widget->xAxis, ui->widget->yAxis);
    int nx = 200;
    int ny = 200;
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(x1, x2), QCPRange(y1, y2)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    double x, y, z;
    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
      for (int yIndex=0; yIndex<ny; ++yIndex)
      {
        colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
        z=a->func(x, y);
        colorMap->data()->setCell(xIndex, yIndex, z);
      }
    }
    QCPColorScale *colorScale = new QCPColorScale(ui->widget);
    ui->widget->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    //colorScale->axis()->setLabel("Magnetic Field Strength");
    colorMap->setGradient(QCPColorGradient::gpPolar);
    colorMap->rescaleDataRange();
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->widget);
    ui->widget->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    ui->widget->rescaleAxes();
    ui->widget->addGraph();
    QPen Pen(QColor(250, 250, 250, 255));
    Pen.setWidth(10);
    ui->widget->graph(0)->setPen(Pen);
    ui->widget->graph(0)->setData(a->x, a->y);
    ui->widget->graph(0)->setPen(QColor(250, 0, 0, 255));//задаем цвет точки
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);//убираем линии
    ui->widget->graph(0)->setPen(Pen);
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

    this->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E6E6FA, stop: 1 #E6E6FA)");
    ui->widget->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E6E6FA, stop: 1 #E6E6FA)");
    ui->widget->replot();
    connect(_timer, &QTimer::timeout, this, &MainWindow::onTimeout);
}


void MainWindow::onTimeout()
{
//////////// алгоритм задаёт туть //////////////////
    switch(alg)
    {
        case PSO:
        {
            if (a->swarn())
            {
                _timer->stop();
                std::cout<<"DONE"<<std::endl;
                ui->lineEdit->setText(QString::fromStdString("DONE"));
                ui->lineEdit_4->setText(QString::number(a->best, 'g', 4));
                ui->lineEdit_3->setText(QString::number(a->bestx, 'g', 4));
                ui->lineEdit_2->setText(QString::number(a->besty, 'g', 4));
            }
            break;
        }
        case PSO_inertia:
        {
            if (a->inertia_swarn())
            {
                _timer->stop();
                std::cout<<"DONE"<<std::endl;
                ui->lineEdit->setText(QString::fromStdString("DONE"));
                ui->lineEdit_4->setText(QString::number(a->best, 'g', 4));
                ui->lineEdit_3->setText(QString::number(a->bestx, 'g', 4));
                ui->lineEdit_2->setText(QString::number(a->besty, 'g', 4));
            }
            break;
        }
        case LBPSO:
        {
            if (a->neighbourhood())
            {
                _timer->stop();
                std::cout<<"DONE"<<std::endl;
                ui->lineEdit->setText(QString::fromStdString("DONE"));
                ui->lineEdit_4->setText(QString::number(a->best, 'g', 2));
                ui->lineEdit_3->setText(QString::number(a->bestx, 'g', 2));
                ui->lineEdit_2->setText(QString::number(a->besty, 'g', 2));
            }
            break;
        }
        case With_dead:
        {
            if (a->with_dead())
            {
                _timer->stop();
                std::cout<<"DONE"<<std::endl;
                ui->lineEdit->setText(QString::fromStdString("DONE"));
                ui->lineEdit_4->setText(QString::number(a->best, 'g', 2));
                ui->lineEdit_3->setText(QString::number(a->bestx, 'g', 2));
                ui->lineEdit_2->setText(QString::number(a->besty, 'g', 2));
            }
            break;
        }
        case With_fire:
        {
            if (a->fire_swarn())
            {
                _timer->stop();
                std::cout<<"DONE"<<std::endl;
                ui->lineEdit->setText(QString::fromStdString("DONE"));
                ui->lineEdit_4->setText(QString::number(a->best, 'g', 2));
                ui->lineEdit_3->setText(QString::number(a->bestx, 'g', 2));
                ui->lineEdit_2->setText(QString::number(a->besty, 'g', 2));
            }
            break;
        }
        case Genetic:
        {
            if (a->genetic())
            {
                _timer->stop();
                std::cout<<"DONE"<<std::endl;
                ui->lineEdit->setText(QString::fromStdString("DONE"));
                ui->lineEdit_4->setText(QString::number(a->best, 'g', 2));
                ui->lineEdit_3->setText(QString::number(a->bestx, 'g', 2));
                ui->lineEdit_2->setText(QString::number(a->besty, 'g', 2));
            }
            break;
        }
        default:
        {
            std::cout<<"algffffff"<<std::endl;
        }
    }

    /*if (a->fire_swarn())
    {
        _timer->stop();
        std::cout<<"DONE"<<std::endl;
    }*/
    QPen Pen(QColor(250, 250, 250, 255));
    Pen.setWidth(10);
    ui->widget->graph(0)->setPen(Pen);
    ui->widget->graph(0)->setData(a->x, a->y);
    ui->widget->graph(0)->setData(a->x, a->y);
    ui->widget->graph(0)->setPen(QColor(250, 0, 0, 255));//задаем цвет точки
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);//убираем линии
    ui->widget->graph(0)->setPen(Pen);
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    ui->widget->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_clicked()
{
    if (!_timer->isActive())
    {
        _timer->start(100);
        start=1;
    }
    else
    {
        _timer->stop();
        start=0;
    }

}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    _timer->stop();
    qDebug()<<arg1;
    function=arg1.toStdString();

    if (function=="PSO")
    {
        std::cout<<"00000"<<std::endl;
        alg=PSO;
    }
    if (function=="PSO_inertia")
    {
        std::cout<<"1111111"<<std::endl;
        alg=PSO_inertia;
    }
    if (function=="LBPSO")
    {
        std::cout<<"22222222"<<std::endl;
        alg=LBPSO;
    }
    if (function=="With_dead")
    {
        std::cout<<"3333333333"<<std::endl;
        alg=With_dead;
    }
    if (function=="With_fire")
    {
        std::cout<<"44444444"<<std::endl;
        alg=With_fire;
    }
    if (function=="Genetic")
    {
        std::cout<<"55555555"<<std::endl;
        alg=Genetic;
    }
    delete a;
    a=new algo();
    _timer->start(100);
    ui->lineEdit->setText(QString::fromStdString(""));
    ui->lineEdit_4->setText(QString::fromStdString(""));
    ui->lineEdit_3->setText(QString::fromStdString(""));
    ui->lineEdit_2->setText(QString::fromStdString(""));
}


/*void MainWindow::on_lineEdit_editingFinished()
{
    //QString text=ui->lineEdit->displayText();
    //function=text.toStdString();

    typedef double T; // numeric type (float, double, mpfr etc...)

     typedef exprtk::symbol_table<T> symbol_table_t;
     typedef exprtk::expression<T>   expression_t;
     typedef exprtk::parser<T>       parser_t;

     std::string expression_string = "z := x - (3 * y)";

     T x = T(123.456);
     T y = T(98.98);
     T z = T(0.0);

     symbol_table_t symbol_table;
     symbol_table.add_variable("x",x);
     symbol_table.add_variable("y",y);
     symbol_table.add_variable("z",z);

     expression_t expression;
     expression.register_symbol_table(symbol_table);

     parser_t parser;

     if (!parser.compile(expression_string,expression))
     {
        printf("Compilation error...\n");
        return;
     }

     T result = expression.value();

}*/
