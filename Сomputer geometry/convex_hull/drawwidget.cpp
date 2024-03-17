#include "drawwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
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
    //std::cout<<pTask->obol.size()<<std::endl;
    for (int i=0; i<pTask->obol.size()-1; i++)
    {
         p.drawLine(pTask->obol[i].x, pTask->obol[i].y, pTask->obol[i+1].x, pTask->obol[i+1].y);
    }
    p.drawLine(pTask->obol[pTask->obol.size()-1].x, pTask->obol[pTask->obol.size()-1].y, pTask->obol[0].x, pTask->obol[0].y);
    std::cout<<pTask->points.size()<<std::endl;
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
  }
}

void DrawWidget::SetDefaultPoints()
{
  if(pTask)
  {
    int w = width();
    int h = height();
    pTask->n=4;
    pTask->points.push_back(vector2d(w / 3, h / 2));
    pTask->points.push_back(vector2d(2 * w / 3, h / 2));
    pTask->points.push_back(vector2d(w / 2, h / 3));
    pTask->points.push_back(vector2d(w / 2, 2 * h / 3));
    /*int n=pTask->n;
    for (int i=0; i<pTask->n; i++)
    {
        pTask->points.push_back(vector2d(w/(n+1)*(n-i), h/(2*(n+1)) ));
    }*/
    shell();
  }
}

void DrawWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bMovePointFlag)
    {
        vector2d curPos(event->x(), event->y());
        pTask->points[ptNum] = curPos;
        shell();
        repaint();
        //emit signalPointsChanged();
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
              ptNum = i;
              return;
          }
      }
    }
}

void DrawWidget::mouseReleaseEvent(QMouseEvent *event)
{
  m_bMovePointFlag = false;
}


bool cmp (vector2d a, vector2d b)
{
    return (a.x<b.x) || (a.x==b.x && a.y<b.y);
}

bool left (vector2d a, vector2d b, vector2d c)
{
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x)<0;
}

bool right (vector2d a, vector2d b, vector2d c)
{
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x)> 0;
}

void DrawWidget::shell()
{
   std::vector <vector2d> tochki=pTask->points;
   sort (tochki.begin(), tochki.end(), &cmp);
   vector2d start = tochki[0],  finish = tochki.back();
   std::vector<vector2d> up;
   std::vector<vector2d> down;
   std::vector <vector2d> obolochka;
   up.push_back (start);
   down.push_back (start);
   for (int i=1; i<tochki.size(); i++)
   {
    if (i==tochki.size()-1 || left (start, tochki[i], finish))
    {
        while (up.size()>=2 && !left (up[up.size()-2], up[up.size()-1], tochki[i]))
        {
            up.pop_back();
        }
        up.push_back (tochki[i]);
    }

    if (i==tochki.size()-1 || right (start, tochki[i], finish))
    {
        while (down.size()>=2 && !right (down[down.size()-2], down[down.size()-1], tochki[i]))
        {
           down.pop_back();
        }
        down.push_back (tochki[i]);
    }
   }
   for (int i=0; i<up.size(); ++i)
   {
       obolochka.push_back (up[i]);
   }
   for (int i=down.size()-2; i>0; i--)
   {
       obolochka.push_back (down[i]);
   }

   pTask->obol.clear();
   pTask->obol=obolochka;
}
