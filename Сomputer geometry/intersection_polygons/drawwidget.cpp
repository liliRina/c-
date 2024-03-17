#include "drawwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <iostream>
#include <queue>
#include <set>
#include <cmath>
#include <vector>
#include <unistd.h>

const int circ_size = 20;

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
  pTask = 0;
  m_bMovePointFlag = false;
  first=false;
}


void DrawWidget::paintEvent(QPaintEvent *event)
{

  QPainter p(this);

  if(pTask)
  {
    //std::cout<<"sdfsdfsd "<<tupl.size()<<std::endl;
    //std::cout<<"inters "<<pTask->intersections.size()<<std::endl;
    //std::cout<<pTask->segm.size()<<std::endl;

    //std::cout<<"uuuuuu"<<std::endl;
      for (int i=0; i<tupl.size(); i++)
      {
          //std::cout<<"alert "<<tupl[i][0].x<<" "<<tupl[i][0].y<<" "<<tupl[i][1].x<<" "<<tupl[i][1].y<<" "<<tupl[i][2].x<<" "<<tupl[i][2].y<<std::endl;
          if (have (tupl[i][0], tupl[i][1], tupl[i][2]))
          {
              //std::cout<<nado[i][0]<<" "<<nado[i][1]<<" "<<nado[i][2]<<std::endl;

              QPolygonF polygon;
              //int a=tupl[i][1];
              //polygon << QPointF(tupl[i][0].x, tupl[i][0].y) << QPointF(tupl[i][1].x, tupl[i][1].y)<<QPointF (tupl[i][2].x, tupl[i][2].y);
              //std::cout<<"alert "<<tupl[i][0].x<<" "<<tupl[i][0].y<<" "<<tupl[i][1].x<<" "<<tupl[i][1].y<<" "<<tupl[i][2].x<<" "<<tupl[i][2].y<<std::endl;
              p.setBrush(Qt::blue);     // Устанавливаем кисть, которой будем отрисовывать объект
             //
              polygon=s_f(polygon);
             // p.drawPolygon(polygon);
          }
      }

    for (int i=0; i<pTask->segm.size(); i++)
    {
        p.drawLine(pTask->segm[i].first.x, pTask->segm[i].first.y, pTask->segm[i].second.x, pTask->segm[i].second.y);
    }
    for (int i=0; i<pTask->points.size(); i++)
    {
        p.drawArc(pTask->points[i].x - circ_size / 2, pTask->points[i].y - circ_size / 2, circ_size, circ_size, 0, 360 * 16);
    }
    QFont font = p.font();
    font.setPixelSize(30);
    p.setFont(font);
    p.setPen(QColor(0, 255, 255));
    for (size_t i=0; i<pTask->p.size(); i++)
    {
         p.drawText(pTask->p[i].x + circ_size / 2, pTask->p[i].y  - circ_size / 2, QString::number(i));
    }
    for (size_t i=0; i<pTask->p2.size(); i++)
    {
         p.drawText(pTask->p2[i].x + circ_size / 2, pTask->p2[i].y  - circ_size / 2, QString::number(i+pTask->p.size()));
    }
    p.setPen(QColor(255, 0, 0));
    for (int i=1; i<pTask->points.size(); i++)
    {
        p.drawLine(pTask->points[i-1].x, pTask->points[i-1].y, pTask->points[i].x, pTask->points[i].y);
    }
    p.drawLine(pTask->points[0].x, pTask->points[0].y, pTask->points[pTask->points.size()-1].x, pTask->points[pTask->points.size()-1].y);
    for (int i=1; i<pTask->points2.size(); i++)
    {
        p.drawLine(pTask->points2[i-1].x, pTask->points2[i-1].y, pTask->points2[i].x, pTask->points2[i].y);
    }
    p.drawLine(pTask->points2[0].x, pTask->points2[0].y,
            pTask->points2[pTask->points2.size()-1].x, pTask->points2[pTask->points2.size()-1].y);
    p.setPen(Qt::black);
    for (size_t i=0; i<pTask->points2.size(); i++)
    {
        p.drawArc(pTask->points2[i].x - circ_size / 2, pTask->points2[i].y - circ_size / 2, circ_size, circ_size, 0, 360 * 16);
    }
   // QFont font = p.font();
    font.setPixelSize(24);
    p.setFont(font);
    for (int i=0; i<pTask->points.size(); i++)
    {
        p.drawText(pTask->points[i].x + circ_size / 2, pTask->points[i].y  - circ_size / 2, QString::number(i));
    }
    for (int i=0; i<pTask->points2.size(); i++)
    {
        p.drawText(pTask->points2[i].x + circ_size / 2, pTask->points2[i].y  - circ_size / 2, QString::number(i+pTask->points.size()));
    }
    QPolygonF polygon;
    //int a=tupl[i][1];
    //polygon << QPointF(tupl[i][0].x, tupl[i][0].y) << QPointF(tupl[i][1].x, tupl[i][1].y)<<QPointF (tupl[i][2].x, tupl[i][2].y);
    //std::cout<<"alert "<<tupl[i][0].x<<" "<<tupl[i][0].y<<" "<<tupl[i][1].x<<" "<<tupl[i][1].y<<" "<<tupl[i][2].x<<" "<<tupl[i][2].y<<std::endl;
    p.setBrush(Qt::blue);     // Устанавливаем кисть, которой будем отрисовывать объект
   //
    polygon=s_f(polygon);
    p.drawPolygon(polygon);

  }
}

bool DrawWidget:: have (vector2d A, vector2d  B, vector2d C)
{
    vector2d D;
    D.x=(A.x+B.x+C.x)/3;
    D.y=(A.y+B.y+C.y)/3;
    return (pTask->point_in_mnoug(D) && pTask->point_in_mnoug2(D));

}

void DrawWidget::SetDefaultPoints()
{
  if(pTask)
  {
    int w = width();
    int h = height();
    pTask->n=4;
    pTask->points.push_back(vector2d(200, 400));
    pTask->points.push_back(vector2d(500, 500));
    pTask->points.push_back(vector2d(100, 200));
    pTask->points.push_back(vector2d(300, 300));
    pTask->points2.push_back(vector2d(400, 200));
    pTask->points2.push_back(vector2d(600, 600));
    pTask->points2.push_back(vector2d(200, 100));
    pTask->points2.push_back(vector2d(200, 200));
    std::cerr<<"ok"<<std::endl;
    get_inters();
    std::cerr<<"ok"<<std::endl;
    triag();
    std::cerr<<"ok"<<std::endl;
  }
}
bool cmp (std::pair<vector2d, int> a, std::pair<vector2d, int> b)
{
    return (a.first.y<b.first.y) || (a.first.y==b.first.y && a.first.x<b.first.x);
}
bool com (vector2d a, vector2d b)
{
    return (a.x<b.x) || (a.x==b.x && a.y<b.y);
}
void DrawWidget::get_inters()
{
  //std::vector <vector2d> poin=pTask->points;
  //std::vector <vector2d> poin2=pTask->points2;
    std::vector <vector2d> poin={pTask->points[0]};


    for (size_t i=0; i<pTask->points.size()-1; i++)//i<pTask->points.size()-1; i++)
    {
        std::vector <vector2d> tmp;
        for (size_t j=0; j<pTask->points2.size()-1; j++)
        {
            if(pTask->intersec(pTask->points[i], pTask->points[i+1], pTask->points2[j], pTask->points2[j+1]).x>=0)
            {
                //std::cout<<pTask->intersec(pTask->points[i], pTask->points[i+1], pTask->points2[j], pTask->points2[j+1]).x<<std::endl;
                vector2d D=pTask->intersec(pTask->points[i], pTask->points[i+1], pTask->points2[j], pTask->points2[j+1]);
                tmp.push_back(D);
            }
        }
        if (pTask->intersec(pTask->points[i], pTask->points[i+1], pTask->points2[0], pTask->points2[pTask->points2.size()-1]).x>=0)
        {

            vector2d D=pTask->intersec(pTask->points[i], pTask->points[i+1], pTask->points2[0], pTask->points2[pTask->points2.size()-1]);
            tmp.push_back(D);
        }
        sort(tmp.begin(), tmp.end(), com);
        if (pTask->points[i].x<=pTask->points[i+1].x)
        {
            poin.insert(poin.end(), tmp.begin(), tmp.end());
        }
        else
        {
            poin.insert(poin.end(), tmp.rbegin(), tmp.rend());

        }
        if (i+1<=pTask->points.size()-1)
        {
            poin.push_back(pTask->points[i+1]);
        }
    }
    std::vector <vector2d> tmp;
    for (size_t j=0; j<pTask->points2.size()-1; j++)
    {
        if (pTask->intersec(pTask->points[0], pTask->points[pTask->points.size()-1], pTask->points2[j], pTask->points2[j+1]).x>=0)
        {
            vector2d D=pTask->intersec(pTask->points[0], pTask->points[pTask->points.size()-1], pTask->points2[j], pTask->points2[j+1]);
            tmp.push_back(D);
        }
    }
    if (pTask->intersec(pTask->points[0], pTask->points[pTask->points.size()-1], pTask->points2[0], pTask->points2[pTask->points2.size()-1]).x>=0)
    {
        vector2d D=pTask->intersec(pTask->points[0], pTask->points[pTask->points.size()-1], pTask->points2[0], pTask->points2[pTask->points2.size()-1]);
        tmp.push_back(D);
    }
    sort(tmp.begin(), tmp.end(), com);
    if (pTask->points[0].x>=pTask->points[pTask->points.size()-1].x)
    {
        poin.insert(poin.end(), tmp.begin(), tmp.end());
    }
    else
    {
        poin.insert(poin.end(), tmp.rbegin(), tmp.rend());
    }
    pTask->p.clear();
    pTask->p=poin;

    poin.clear();
    poin={pTask->points2[0]};

    for (size_t i=0; i<pTask->points2.size()-1; i++)
    {
        std::vector <vector2d> tmp;
        for (size_t j=0; j<pTask->points.size()-1; j++)
        {
            if(pTask->intersec(pTask->points2[i], pTask->points2[i+1], pTask->points[j], pTask->points[j+1]).x>=0)
            {
                //std::cout<<pTask->intersec(pTask->points[i], pTask->points[i+1], pTask->points2[j], pTask->points2[j+1]).x<<std::endl;
                vector2d D=pTask->intersec(pTask->points2[i], pTask->points2[i+1], pTask->points[j], pTask->points[j+1]);
                tmp.push_back(D);
            }
        }
        if (pTask->intersec(pTask->points2[i], pTask->points2[i+1], pTask->points[0], pTask->points[pTask->points.size()-1]).x>=0)
        {
            //std::cout<<"dg"<<std::endl;
            vector2d D=pTask->intersec(pTask->points2[i], pTask->points2[i+1], pTask->points[0], pTask->points[pTask->points.size()-1]);
            tmp.push_back(D);
        }
        sort(tmp.begin(), tmp.end(), com);
        if (pTask->points2[i].x<=pTask->points2[i+1].x)
        {
            poin.insert(poin.end(), tmp.begin(), tmp.end());
        }
        else
        {
            if (tmp.size()!=0)
            {
                poin.insert(poin.end(), tmp.rbegin(), tmp.rend());
            }

        }
        if (i+1<=pTask->points2.size()-1)
        {
            poin.push_back(pTask->points2[i+1]);
        }
    }
    tmp.clear();
    for (size_t j=0; j<pTask->points.size()-1; j++)
    {
        if (pTask->intersec(pTask->points2[0], pTask->points2[pTask->points2.size()-1], pTask->points[j], pTask->points[j+1]).x>=0)
        {
            vector2d D=pTask->intersec(pTask->points2[0], pTask->points2[pTask->points2.size()-1], pTask->points[j], pTask->points[j+1]);
            tmp.push_back(D);
        }
    }
    if (pTask->intersec(pTask->points2[0], pTask->points2[pTask->points2.size()-1], pTask->points[0], pTask->points[pTask->points.size()-1]).x>=0)
    {
        vector2d D=pTask->intersec(pTask->points2[0], pTask->points2[pTask->points2.size()-1], pTask->points[0], pTask->points[pTask->points2.size()-1]);
        tmp.push_back(D);
    }
    sort(tmp.begin(), tmp.end(), com);
    if (pTask->points2[0].x>=pTask->points2[pTask->points2.size()-1].x)
    {
        poin.insert(poin.end(), tmp.begin(), tmp.end());
    }
    else
    {
        if (tmp.size()!=0)
        {
            poin.insert(poin.end(), tmp.rbegin(), tmp.rend());
        }
    }
    //std::cout<<pTask->points2.size()<<std::endl;
    //std::cout<<pTask->points2[pTask->points2.size()-1].x<<std::endl;
    pTask->p2.clear();
    pTask->p2=poin;
    poin.clear();
   /* pTask->p=pTask->points;
    pTask->p2=pTask->points2;*/
}

void DrawWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bMovePointFlag)
    {
        vector2d curPos(event->x(), event->y());
        if (first)
        {
            pTask->points[ptNum] = curPos;
        }
        else
        {
            pTask->points2[ptNum] = curPos;
        }
        //pTask->points[ptNum] = curPos;
        get_inters();
        triag();

        repaint();
        emit signalPointsChanged();
    }
}
QPolygonF DrawWidget::s_f (const QPolygonF &r)
{
    QPolygonF polig1, polig2;
    for (int i=0; i<pTask->points.size(); i++)
    {
        polig1 << QPointF(pTask->points[i].x, pTask->points[i].y);
    }
    polig1<<QPointF(pTask->points[0].x, pTask->points[0].y);
    for (int i=0; i<pTask->points2.size(); i++)
    {
        QPointF S(pTask->p2[i].x, pTask->p2[i].y);
        polig2<<QPointF(pTask->points2[i].x, pTask->points2[i].y);
    }
    polig2<<QPointF(pTask->points2[0].x, pTask->points2[0].y);
    return polig2.intersected(polig1);

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
              first=true;
              ptNum =i;
              return;
          }
      }
      for (int i=0; i<pTask->points2.size(); i++)
      {
          if ((v - pTask->points2[i]).length() < circ_size / 2)
          {
              m_bMovePointFlag = true;
              first=false;
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




bool compare (std::pair <std::pair <int, int>, double> A, std::pair <std::pair <int, int>, double> B)
{
    return A.second>B.second;
}


/* A function to check whether point P(x, y) lies inside the triangle formed
by A(x1, y1), B(x2, y2) and C(x3, y3) */
int sign (int x1, int y1, int x2, int y2, int x3, int y3) {
  return (x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3);
}
bool DrawWidget::isInside(vector2d A, vector2d B, vector2d C)
{
    QPolygonF  Tr;
    Tr << QPointF(A.x, A.y)<<QPointF(B.x, B.y)<<QPointF(C.x, C.y);
    for (size_t i=0; i<pTask->p.size(); i++)
    {
        if (A==pTask->p[i] || B==pTask->p[i] || C==pTask->p[i])
        {
            continue;
        }
        Qt :: FillRule g;
        g=Qt ::OddEvenFill;
        QPointF U(pTask->p[i].x, pTask->p[i].y);
        if(Tr.containsPoint(U, g))
        {
            return true;
        }
    }
    for (size_t i=0; i<pTask->p2.size(); i++)
    {
        if (A==pTask->p2[i] || B==pTask->p2[i] || C==pTask->p2[i])
        {
            continue;
        }
        Qt :: FillRule g;
        g=Qt ::OddEvenFill;
        QPointF U(pTask->p2[i].x, pTask->p2[i].y);
        if(Tr.containsPoint(U, g))
        {
            return true;
        }
    }
    return false;
}


void DrawWidget::triag()
{
    std::vector <vector2d> tochki=pTask->p;
    tochki.insert(tochki.end(), pTask->p2.begin(), pTask->p2.end());
    std::vector <std::vector<int> > who;
    //std::cout<<pTask->p.size()<< " "<<pTask->p2.size()<<std::endl;
    pTask->segm.clear();
    nado.clear();
    std::vector <std::vector<vector2d> > tu;
    std::vector <std::pair <std::pair <int, int>, double> > pachan;
    std::vector <std::set <int> >tringles (pTask->p.size()+pTask->p2.size());
    double len;
    //std::cout<<"ooo"<<std::endl;
    for (int i=0; i<pTask->p.size()-1; i++)
    {
        tringles[i].insert(i+1);
        tringles[i+1].insert(i);
        pTask->segm.push_back(std::make_pair(pTask->p[i],pTask->p[i+1]));
        who.push_back({i, i+1});

        //std::cout<<pTask->p[i].x<<pTask->p[i+1].x<<" ";
    }
    //std::cout<<std::endl;
    tringles[0].insert(pTask->p.size()-1);
    tringles[pTask->p.size()-1].insert(0);
    pTask->segm.push_back(std::make_pair(pTask->p[0],pTask->p[pTask->p.size()-1]));
    int r=pTask->p.size();
    int y=0;
    who.push_back({0, (int)pTask->p.size()-1});
    for (; r<pTask->p2.size()+pTask->p.size()-1; r++)
    {
        //std::cout<<r<<std::endl;
        //std::cout<<tringles.size()<<std::endl;
        tringles[r].insert(r+1);
        tringles[r+1].insert(r);
        //pTask->segm.push_back(std::make_pair(pTask->p2[r-pTask->p.size()+1],pTask->p2[r-pTask->p.size()+2]));
        pTask->segm.push_back(std::make_pair(pTask->p2[y],pTask->p2[y+1]));
        who.push_back({r, r+1});
        y++;
    }
    tringles[pTask->p.size()].insert(pTask->p2.size()+pTask->p.size()-1);
    tringles[pTask->p2.size()+pTask->p.size()-1].insert(pTask->p.size());
    pTask->segm.push_back(std::make_pair(pTask->p2[0],pTask->p2[pTask->p2.size()-1]));
    who.push_back({(int)pTask->p.size(), (int)pTask->p2.size()+(int)pTask->p.size()-1});
    //std::cout<<pTask->segm.size()<<std::endl;
    int t=0;
    for (int i=0; i<tochki.size(); i++)
    {
        for (int j=t; j<tochki.size(); j++)
        {
            if ((i==j || i==j-1 || i==j+1) &&
                    (!(i==pTask->p.size()-1 && j==pTask->p.size()) || !(j==pTask->p.size()-1 && i==pTask->p.size())))
            {
                continue;
            }
            len=sqrt((double)((tochki[i].x-tochki[j].x)*(tochki[i].x-tochki[j].x))+(double)((tochki[i].y-tochki[j].y)*(tochki[i].y-tochki[j].y)));
            pachan.push_back(std::make_pair(std::make_pair(i, j), len));
        }
        t++;
    }
    sort(pachan.begin(), pachan.end(), compare);
    int i=0;
    bool peresec=false;
    //std::cout<<"kkkkk"<<std::endl;
    while (i<pachan.size())
    {
        int o=0;
        for (auto j: pTask->segm)
        {
            if (pTask->intersec_inner(j.first, j.second, tochki[pachan[i].first.first], tochki[pachan[i].first.second]))
            {
                //std::cout<<pachan[i].first.first<<" "<<pachan[i].first.second<<std::endl;
                if ((pachan[i].first.first==0 && pachan[i].first.second==3) ||
                    (pachan[i].first.first==3 && pachan[i].first.second==0) && o==10)
                {
                   // pTask->intersec_inner2(j.first, j.second, tochki[pachan[i].first.first], tochki[pachan[i].first.second]);
                   // std::cout<<who[o][0]<<" "<<who[o][1]<<std::endl;
                }
                peresec=true;
            }
            /*if (((pachan[i].first.first==0 && pachan[i].first.second==3) ||
                (pachan[i].first.first==3 && pachan[i].first.second==0)) && o==14)
            {
                pTask->intersec_inner2(j.first, j.second, tochki[pachan[i].first.first], tochki[pachan[i].first.second]);
                std::cout<<who[o][0]<<" "<<who[o][1]<<std::endl;
                std::cout<<peresec<<std::endl;

            }*/
            o++;
        }

        if (!peresec)
        {
            if (((pachan[i].first.first==0 && pachan[i].first.second==11) ||
                (pachan[i].first.first==11 && pachan[i].first.second==0)))
            {
                //pTask->intersec_inner2(pTask->segm[10].first, pTask->segm[10].second, tochki[pachan[i].first.first], tochki[pachan[i].first.second]);
                //std::cout<<who[o][0]<<" "<<who[o][1]<<std::endl;
               // std::cout<<peresec<<std::endl;
            }
            pTask->segm.push_back(std::make_pair(tochki[pachan[i].first.first],tochki[pachan[i].first.second]));
            who.push_back({pachan[i].first.first, pachan[i].first.second});
            //if (pachan[i].first.first>pachan[i].first.second)
            {
                tringles[pachan[i].first.second].insert(pachan[i].first.first);
            }
            //else
            {
                tringles[pachan[i].first.first].insert(pachan[i].first.second);
            }
        }

        peresec=false;
        i++;

    }
  // std::cout<<"ggg"<<std::endl;
    for (int i=0; i<tringles.size(); i++)
    {
        for (auto j:tringles[i])
        {
            std::cout<<j<<" ";

            for (auto k:tringles[j])
            {
                if (tringles[k].find(i)!=tringles[k].end() && k!=i && i!=j && !isInside(tochki[i], tochki[j], tochki[k]))
                {
                   // std::cout<<"dfgh"<<std::endl;
                    if (i==2&& j==3&& k==4)
                    {
                       // std::cout<<"oq"<<std::endl;
                    }
                    nado.push_back({i, j, k});
                    tu.push_back({tochki[i], tochki[j], tochki[k]});
                   // std::cout<<i<<" "<<j<<" "<<k<<std::endl;
                }
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<tu.size()<<std::endl;
    tupl=tu;

}

