#include "drawwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <iostream>
#include <queue>

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
     //std::cout<<pTask->segm.size()<<std::endl;
     for (int i=0; i<pTask->segm.size(); i++)
     {
          p.drawLine(pTask->segm[i].first.x, pTask->segm[i].first.y, pTask->segm[i].second.x, pTask->segm[i].second.y);
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
    triag();
  }
}

void DrawWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bMovePointFlag)
    {
        vector2d curPos(event->x(), event->y());
        pTask->points[ptNum] = curPos;
        triag();
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


bool cmp (vector2d a, vector2d b)
{
    return (a.y<b.y) || (a.x==b.x && a.y<b.y);
}
/*
//bool left (vector2d a, vector2d b, vector2d c)
{
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x)<0;
}

//bool right (vector2d a, vector2d b, vector2d c)
{
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x)> 0;
}

*/


void DrawWidget::triag()
{
   std::vector<vector2d> tochki=pTask->points;
   std::vector <std::pair<vector2d, vector2d> > res;
   sort (tochki.begin(), tochki.end(), &cmp);
   vector2d cur1, cur2, central;
   vector2d bestA;
   double best_cos=2;
   std::cout<<" aaa "<<std::endl;
   res.push_back(std::make_pair(tochki[0], tochki[1]));
   for (int i=0; i<tochki.size(); i++)
   {
       if (((tochki[i].x-tochki[0].x)*(tochki[i].x-tochki[1].x)+(tochki[i].y-tochki[0].y)*(tochki[i].y-tochki[1].y))/
            ((tochki[i]-tochki[0]).length()*(tochki[i]-tochki[1]).length())<best_cos)
       {
           bestA=tochki[i];
           best_cos=((tochki[i].x-tochki[0].x)*(tochki[i].x-tochki[1].x)+(tochki[i].y-tochki[0].y)*(tochki[i].y-tochki[1].y))/
                   ((tochki[i]-tochki[0]).length()*(tochki[i]-tochki[1]).length());
            std::cout<<bestA.x<<" "<<best_cos<<" "<<bestA.y<<std::endl;
       }
   }
   std::cout<<tochki[0].x<<" "<<tochki[0].y<<std::endl;
   std::cout<<tochki[1].x<<" "<<tochki[1].y<<std::endl;
   std::cout<<bestA.x<<" "<<bestA.y<<std::endl;
   pTask->active.push(std::make_pair(std::make_pair(tochki[0], bestA), tochki[1]));
   pTask->active.push(std::make_pair(std::make_pair(tochki[1], bestA), tochki[0]));
   int i=0;
   while (i<50 && !pTask->active.empty())
   //while (!pTask->active.empty())
   {
       cur1=(pTask->active.front().first.first);
       cur2=pTask->active.front().first.second;
       central=pTask->active.front().second;
       best_cos=2;
       res.push_back(std::make_pair(cur1, cur2));
       std::cout<<cur1.x<<" 2222222 "<<cur1.y<<std::endl;
       std::cout<<cur2.x<<" 2222222 "<<cur2.y<<std::endl;
       pTask->active.pop();
       switch (it_turn(cur1, cur2, central))
       {
           case left:
               std::cout<<" llll "<<std::endl;
               for (int i=0; i<tochki.size(); i++)
               {
                   if (it_turn(cur1, cur2, tochki[i])==right)
                   {
                       if (((tochki[i].x-cur1.x)*(tochki[i].x-cur2.x)+(tochki[i].y-cur1.y)*(tochki[i].y-cur2.y))/
                            ((tochki[i]-cur1).length()*(tochki[i]-cur2).length())<best_cos)
                       {
                           bestA=tochki[i];
                           best_cos=((tochki[i].x-cur1.x)*(tochki[i].x-cur2.x)+(tochki[i].y-cur1.y)*(tochki[i].y-cur2.y))/
                                   ((tochki[i]-cur1).length()*(tochki[i]-cur2).length());
                       }
                   }
               }
               break;
            case right:
               std::cout<<" rrrrrrr "<<std::endl;
               for (int i=0; i<tochki.size(); i++)
               {
                   if (it_turn(cur1, cur2, tochki[i])==left)
                   {
                       if (((tochki[i].x-cur1.x)*(tochki[i].x-cur2.x)+(tochki[i].y-cur1.y)*(tochki[i].y-cur2.y))/
                            ((tochki[i]-cur1).length()*(tochki[i]-cur2).length())<best_cos)
                       {
                           bestA=tochki[i];
                           best_cos=((tochki[i].x-cur1.x)*(tochki[i].x-cur2.x)+(tochki[i].y-cur1.y)*(tochki[i].y-cur2.y))/
                                   ((tochki[i]-cur1).length()*(tochki[i]-cur2).length());
                       }
                   }
               }
               break;
            case collinear:
               std::cout<<"col"<<std::endl;
               break;
       }
       if (best_cos!=2)
       {
           std::cout<<bestA.x<<" "<<bestA.y<<std::endl;
           pTask->active.push(std::make_pair(std::make_pair(cur1, bestA), cur2));
           pTask->active.push(std::make_pair(std::make_pair(cur2, bestA), cur1));
       }
       i++;
   }
   while (!pTask->active.empty())
   {
       pTask->active.pop();
   }
   pTask->segm=res;
}

