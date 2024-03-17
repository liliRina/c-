#include "task_data.h"
#include <iostream>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
double cross(vector2d const & a, vector2d const & b)
{
   return a.x * b.y - b.x * a.y;
}

enum Turn it_turn(vector2d A, vector2d B, vector2d C)
{
    double l = (B.x - A.x) * (C.y - A.y);
    double r = (C.x - A.x) * (B.y - A.y);
    double e = (abs(l) + abs( r)) * std::numeric_limits<double>::epsilon() * 4;
    double det = l - r;
    //std::cout<<det<<std::endl;
    if (det > e)
    {
        return left;
    }

    if (det < -e)
    {
        return right;
    }
    double ldet = cross(B - A, C - A);
    if (ldet > 0)
    {
        return left;
    }
    if (ldet < 0)
    {
        return right;
    }
    return collinear;
}
vector2d task_data::intersec(vector2d A, vector2d B, vector2d C, vector2d D)
{
    double delta = (B.x - A.x) * (C.y - D.y) - (B.y - A.y) * (C.x - D.x);
    if(delta != 0)
    {

      double lambda = ((C.x - A.x) * (C.y - D.y) - (C.y - A.y) * (C.x - D.x)) / delta;
      double mu = ((B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x)) / delta;
      vector2d inters;
      if(lambda >= 0 && lambda <= 1 && mu >= 0 && mu <= 1)
      {
        intersections.push_back((1 - lambda) * A + lambda * B);
        return ((1 - lambda) * A + lambda * B);
      }
    }
    vector2d F(-1, 0);
    return F;
}
bool rebro (float x, float y, float x1, float y1, float x2, float y2)
{
    if (x2-x1==0)
    {
        if (x-x1==0 && y >= std::min(y1, y2) && y<=std::max(y1, y2))
        {
            return true;
        }
    }
    else
    {
        if (x<=std::max(x1, x2) && x>=std::min(x1, x2) && (x2-x1)*(y-y1)-(y2-y1)*(x-x1)==0)
        {
            return true;
        }
    }
    return false;
}
bool peresek (float x0, float y0,float x1, float y1,float x2, float y2)
{
    if (((y1<y0 && y2>=y0) || (y2<y0 && y1>=y0)) && ((y0-y1)*(x1-x2)+y1*x1-x1*y2)/(y1-y2)<x0)
    {
        return true;
    }
    return false;
}

bool task_data::point_in_mnoug(vector2d A)
{

        /*float x0, y0, x1, y1, x2, y2, xc, yc;
        int perek=0;
        x0=A.x;
        y0=A.y;
        x1=points[0].x;
        y1=points[0].y;
        x2=x1;
        y2=y1;
        bool leshit = false;
        for (int i=1; i<points.size(); i++)
        {
           // cin >> xc >> yc;
            xc=points[i].x;
            yc=points[i].y;
            if (rebro(x0, y0, x2, y2, xc, yc))
            {
                leshit=true;
            }
            if (peresek(x0, y0, x2, y2, xc, yc))
            {
                perek++;
            }
            x2=xc;
            y2=yc;
        }
        if (rebro(x0, y0, x2, y2, x1, y1))
        {
            leshit=true;
        }
        if (peresek(x0, y0, x2, y2, x1, y1))
        {
            perek++;
        }
        if (perek%2==1 || leshit)
            return true;
        else
            return false;*/
    QPolygonF  Tr;
   // std::cerr<<"1 "<<std::endl;
    for (int i=0; i<points.size(); i++)
    {
       QPointF S (points[i].x, points[i].y);
       Tr<<S;
        //std::cerr<<"1 "<<std::endl;
    }

   // std::cerr<<"1 "<<std::endl;
   QPointF U (A.x, A.y);
   Qt :: FillRule g;
   g=Qt ::OddEvenFill;
   return Tr.containsPoint(U, g);

}

bool task_data::point_in_mnoug2(vector2d A)
{

        /*float x0, y0, x1, y1, x2, y2, xc, yc;
        int perek=0;
        x0=A.x;
        y0=A.y;
        x1=points2[0].x;
        y1=points2[0].y;
        x2=x1;
        y2=y1;
        bool leshit = false;
        for (int i=1; i<points2.size(); i++)
        {
            xc=points2[i].x;
            yc=points2[i].y;
            if (rebro(x0, y0, x2, y2, xc, yc))
            {
                leshit=true;
            }
            if (peresek(x0, y0, x2, y2, xc, yc))
            {
                perek++;
            }
            x2=xc;
            y2=yc;
        }
        if (rebro(x0, y0, x2, y2, x1, y1))
        {
            leshit=true;
        }
        if (peresek(x0, y0, x2, y2, x1, y1))
        {
            perek++;
        }
        if (perek%2==1 || leshit)
            return true;
        else
            return false;*/
    //std::cerr<<"1 "<<std::endl;
    QPolygonF  Tr;
    //std::cerr<<"1 "<<std::endl;
    for (int i=0; i<points2.size(); i++)
    {
       QPointF S (points2[i].x, points2[i].y);
       Tr<<S;
        //std::cerr<<"1 "<<std::endl;
    }
    //std::cerr<<"1 "<<std::endl;
    QPointF U (A.x, A.y);
    Qt :: FillRule g;
    g=Qt ::OddEvenFill;
    //Tr.containsPoint(U, g);
    return Tr.containsPoint(U, g);

}
bool task_data::intersec_inner (vector2d A, vector2d B, vector2d C, vector2d D)
{
    /*float x1=A.x, y1=A.y, x2=B.x, y2=B.y, x3=C.x, y3=C.y, x4=D.x, y4=D.y;
    float n;
    if (y2 - y1 != 0) {  // a(y)
            float q = (x2 - x1) / (y1 - y2);
            float sn = (x3 - x4) + (y3 - y4) * q; if (!sn) { return 0; }  // c(x) + c(y)*q
            float fn = (x3 - x1) + (y3 - y1) * q;   // b(x) + b(y)*q
            n = fn / sn;
        }
        else {
            if (!(y3 - y4)) { return 0; }  // b(y)
            n = (y3 - y1) / (y3 - y4);   // c(y)/b(y)
        }
    double dot = x3 + (x4 - x3) * n; // x3 + (-b(x))*n
    double dot2 = y3 + (y4 - y3) * n;

    return (((x1<=x3 && x3<=x2) || (x1<=x4 && x4<=x2)) && ( (y1<=y3 && y3<=y2) || (y1<=y4 && y4<=y2)));

    */

    if (A==B || A==D || A==C)
    {
        return false;
    }
    if (B==C || B==D)
    {
        return false;
    }
    if (C==D)
    {
        return false;
    }
    /*double delta=(B.y-A.y)*(C.x-D.x)-(D.y-C.y)*(A.x-B.x);
    double delta1=(double)(A.x*B.y-B.x*A.y)*(double)(C.x-D.x)-(double)(C.x*D.y-D.x*C.y)*(double)(A.x-B.x);
    double delta2=-(double)(A.x*B.y-B.x*A.y)*(double)(D.y-C.y)+(double)(C.x*D.y-D.x*C.y)*(double)(B.y-A.y);
    std::cout<<delta<<std::endl;
    if (delta!=0)
    {
        double int_x=delta1/delta;
        double int_y=delta2/delta;
        return A.x<=int_x && int_x<=B.x && A.y<=int_y && int_y<=B.y && C.x<=int_x && int_x<=D.x && C.y<=int_y && int_y<=D.y;
    }
    */

    double delta = (B.x - A.x) * (C.y - D.y) - (B.y - A.y) * (C.x - D.x);
    if(delta != 0)
    {

      double lambda = ((C.x - A.x) * (C.y - D.y) - (C.y - A.y) * (C.x - D.x)) / delta;
      double mu = ((B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x)) / delta;
      vector2d inters;
      if(lambda >= 0 && lambda <= 1 && mu >= 0 && mu <= 1)
      {
        return true;
      }
    }
    return false;
}
bool task_data::intersec_inner2 (vector2d A, vector2d B, vector2d C, vector2d D)
{
    /*float x1=A.x, y1=A.y, x2=B.x, y2=B.y, x3=C.x, y3=C.y, x4=D.x, y4=D.y;
    float n;
    if (y2 - y1 != 0) {  // a(y)
            float q = (x2 - x1) / (y1 - y2);
            float sn = (x3 - x4) + (y3 - y4) * q; if (!sn) { return 0; }  // c(x) + c(y)*q
            float fn = (x3 - x1) + (y3 - y1) * q;   // b(x) + b(y)*q
            n = fn / sn;
        }
        else {
            if (!(y3 - y4)) { return 0; }  // b(y)
            n = (y3 - y1) / (y3 - y4);   // c(y)/b(y)
        }
    double dot = x3 + (x4 - x3) * n; // x3 + (-b(x))*n
    double dot2 = y3 + (y4 - y3) * n;

    return (((x1<=x3 && x3<=x2) || (x1<=x4 && x4<=x2)) && ( (y1<=y3 && y3<=y2) || (y1<=y4 && y4<=y2)));

    */

    if (A==B || A==D || A==C)
    {
        return false;
    }
    if (B==C || B==D)
    {
        return false;
    }
    if (C==D)
    {
        return false;
    }
    /*double delta=(B.y-A.y)*(C.x-D.x)-(D.y-C.y)*(A.x-B.x);
    double delta1=(double)(A.x*B.y-B.x*A.y)*(double)(C.x-D.x)-(double)(C.x*D.y-D.x*C.y)*(double)(A.x-B.x);
    double delta2=-(double)(A.x*B.y-B.x*A.y)*(double)(D.y-C.y)+(double)(C.x*D.y-D.x*C.y)*(double)(B.y-A.y);
    std::cout<<delta<<std::endl;
    if (delta!=0)
    {
        double int_x=delta1/delta;
        double int_y=delta2/delta;
        return A.x<=int_x && int_x<=B.x && A.y<=int_y && int_y<=B.y && C.x<=int_x && int_x<=D.x && C.y<=int_y && int_y<=D.y;
    }
    */

    double delta = (B.x - A.x) * (C.y - D.y) - (B.y - A.y) * (C.x - D.x);
    if(delta != 0)
    {

        double lambda = ((C.x - A.x) * (C.y - D.y) - (C.y - A.y) * (C.x - D.x)) / delta;
        double mu = ((B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x)) / delta;
        vector2d inters;
        std::cout<<delta<<" "<<lambda<<" "<<mu<<std::endl;
        std::cout<<((1 - lambda) * A + lambda * B).x<<"toc "<<((1 - lambda) * A + lambda * B).y;
        std::cout<<A.x<<" "<<A.y<<" "<<B.x<<" "<<B.y<<" "<<C.x<<" "<<C.y<<" "<<D.x<<" "<<D.y<<std::endl;
        if(lambda >= 0 && lambda <= 1 && mu >= 0 && mu <= 1)
        {
            return true;
        }
    }
    return false;
}
