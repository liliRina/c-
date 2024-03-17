#include "drawwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QRandomGenerator>

const int circ_size = 15;

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
  pTask = 0;
  m_bMovePointFlag = false;
}


void DrawWidget::paintEvent(QPaintEvent *event)
{
  QColor lines_color = QColor(65, 105,225);

  QPainter p(this);

  QPen pen(QColor(255, 165, 0));
  p.setPen(pen);
  p.setBrush(QColor(255, 165, 0));

  for (int i=0; i<pTask->points.size(); i++)
       p.drawEllipse(pTask->points[i].x - circ_size / 2, pTask->points[i].y- circ_size / 2, circ_size, circ_size);

  if(pTask && pTask->points.size()>1)
  {



    if (state == 1)
    {
        if (!parametrical) {
            QVector<double> xs = pTask->lagrange().first;
            QVector<double> ys = pTask->lagrange().second;

            QPen pen(lines_color);
            p.setPen(pen);

            for(int i=0; i<xs.size()-1; i++)
            {
                p.drawLine(xs[i], ys[i], xs[i+1], ys[i+1]);
            }
        }
        else {
            QVector<double> xs = pTask->lagrange_parametrical().first;
            QVector<double> ys = pTask->lagrange_parametrical().second;

            QPen pen(lines_color);
            p.setPen(pen);

            for(int i=0; i<xs.size()-1; i++)
            {
                p.drawLine(xs[i], ys[i], xs[i+1], ys[i+1]);
            }
        }
    }
    else if (state == 2)
    {
        if (!parametrical) {
            QVector<double> xs = pTask->hermite().first;
            QVector<double> ys = pTask->hermite().second;

            QPen pen(lines_color);
            p.setPen(pen);

            for(int i=0; i<xs.size()-1; i++)
            {
                p.drawLine(xs[i], ys[i], xs[i+1], ys[i+1]);
            }
        }
        else {
            QVector<double> xs = pTask->hermite_parametrical().first;
            QVector<double> ys = pTask->hermite_parametrical().second;

            QPen pen(lines_color);
            p.setPen(pen);

            for(int i=0; i<xs.size()-1; i++)
            {
                p.drawLine(xs[i], ys[i], xs[i+1], ys[i+1]);
            }
        }
    }
    else if(state == 3)
    {
        if(!parametrical) {
            QVector<double> xs = pTask->cubic().first;
            QVector<double> ys = pTask->cubic().second;

            QPen pen(lines_color);
            p.setPen(pen);

            for(int i=0; i<xs.size()-1; i++)
            {
                p.drawLine(xs[i], ys[i], xs[i+1], ys[i+1]);
            }
        }
        else {
            QVector<double> xs = pTask->cubic_parametrical().first;
            QVector<double> ys = pTask->cubic_parametrical().second;

            QPen pen(lines_color);
            p.setPen(pen);

            for(int i=0; i<xs.size()-1; i++)
            {
                p.drawLine(xs[i], ys[i], xs[i+1], ys[i+1]);
            }
        }
    }

    else {

    }

  }

}

void DrawWidget::addPoint()
{
    int w = QRandomGenerator::global()->bounded(width()/4)+3*width()/8;
    int h = QRandomGenerator::global()->bounded(height()/4)+3*height()/8;

    pTask->points.push_back(vector2d(w, h));
    repaint();

}
void DrawWidget::deletePoint()
{
    if (pTask->points.size()>0)
    {
        pTask->points.pop_back();
        repaint();
    }
}


void DrawWidget::mouseMoveEvent(QMouseEvent *event)
{
  if(m_bMovePointFlag)
  {
    auto x_c = event->x();
    auto y_c = event->y();
    if (x_c<0)
        x_c = 0;
    if (x_c>width())
        x_c = width();
    if (y_c<0)
        y_c = 0;
    if (y_c>height())
        y_c = height();
    vector2d curPos(x_c, y_c);
    pTask->points[ptNum] = curPos;
    repaint();
  }
}

void DrawWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
      int XX = event->x();
      int YY = event->y();
      vector2d v(XX, YY);
      for (int i=0;i<pTask->points.size();++i)

      {
          if((v - pTask->points[i]).length() < circ_size / 2)
          {
            m_bMovePointFlag = true;
            ptNum = i;
            break;
          }
      }
    }
}

void DrawWidget::mouseReleaseEvent(QMouseEvent *event)
{
  m_bMovePointFlag = false;
}

