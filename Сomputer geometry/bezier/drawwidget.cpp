#include "drawwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QVector>
#include <QPainterPath>
#include <iostream>
const int circ_size = 20;

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
  pTask = 0;
  m_bMovePointFlag = false;
}


void DrawWidget::paintEvent(QPaintEvent *event)
{

  QPainter p(this);
  if(pTask)
  {
    for (int i=0; i<pTask->points.size(); i++)
    {
         p.drawArc(pTask->points[i].x - circ_size / 2, pTask->points[i].y - circ_size / 2, circ_size, circ_size, 0, 360 * 16);
    }
    for (int i=0; i<pTask->points.size(); i++)
    {
         p.drawArc(pTask->points[i].x - circ_size / 2, pTask->points[i].y - circ_size / 2, circ_size, circ_size, 0, 360 * 16);
    }
    QFont font = p.font();
    font.setPixelSize(24);
    p.setFont(font);
    for (int i=0; i<pTask->points.size(); i++)
    {
        p.drawText(pTask->points[i].x + circ_size / 2, pTask->points[i].y  - circ_size / 2, QString::number(i));
    }
    QPainterPath path;
    path.moveTo(pTask->points[0].x, pTask->points[0].y);
    int x=0, y=0;
    int n=pTask->points.size()-1;
    std::cout<<pTask->chki.size()<<std::endl;
    std::cout<<pTask->chki[n][0]<<std::endl;
    for (double i=0; i<=1; i=i+0.05)
    {
        x=0;
        y=0;
        for (int j=0; j<n+1; j++)
        {
            x+=pTask->points[j].x*pow((1-i), n-j)*pow(i, j)*pTask->chki[n][j];
            y+=pTask->points[j].y*pow((1-i), n-j)*pow(i, j)*pTask->chki[n][j];
        }
        path.lineTo(x, y);
    }
    p.drawPath(path);

  }
}

void DrawWidget::SetDefaultPoints()
{
  if(pTask)
  {
    int w = width();
    int h = height();
    pTask->points.push_back(vector2d(w / 3, h / 2));
    pTask->points.push_back(vector2d(2 * w / 3, h / 2));
    pTask->points.push_back(vector2d(w / 2, h / 3));
  }
}

void DrawWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bMovePointFlag)
    {
        vector2d curPos(event->x(), event->y());
        pTask->points[ptNum] = curPos;
        repaint();
        emit signalPointsChanged();
    }
}

void DrawWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
      int XX = event->x();
      int YY = event->y();
      vector2d v(XX, YY);
      for (int i=0; i<pTask->points.size(); i++)
      {
          if ((v - pTask->points[i]).length() < circ_size / 2)
          {
              m_bMovePointFlag = true;
              ptNum =i;
              return;
          }
      }
    }
}

void DrawWidget::mouseReleaseEvent(QMouseEvent *event)
{
  m_bMovePointFlag = false;
}

