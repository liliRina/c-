#include "task_data.h"
#include <iostream>
#include <limits>

double cross(vector2d const & a, vector2d const & b)
{
   return a.x * b.y - b.x * a.y;
}




void task_data :: it_turn()
{
    double l = (B.x - A.x) * (C.y - A.y);
    double r = (C.x - A.x) * (B.y - A.y);
    double e = (abs(l) + abs( r)) * std::numeric_limits<double>::epsilon() * 4;
    double det = l - r;
    std::cout<<det<<std::endl;
    if (det > e)
    {
        turn_="left";
        return;
    }

    if (det < -e)
    {
        turn_="right";
        return;
    }
    //vector2d la(a), lb(b), lc( c);
    double ldet = cross(B - A, C - A);
    if (ldet > 0)
    {
        turn_="left";
        return;
    }

    if (ldet < 0)
    {
        turn_="right";
        return;
    }
    turn_="net";
}


/*bool task_data :: testIntersection()
{

  double delta = (B.x - A.x) * (C.y - D.y) - (B.y - A.y) * (C.x - D.x);

  if(delta != 0) //// ха-ха
  {

    double lambda = ((C.x - A.x) * (C.y - D.y) - (C.y - A.y) * (C.x - D.x)) / delta;
    double mu = ((B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x)) / delta;

    if(lambda >= 0 && lambda <= 1 && mu >= 0 && mu <= 1)
    {
      this->ptIntersection = (1 - lambda) * A + lambda * B ;
      this->m_bIntFlag = true;
      return true;
    }
  }
  this->m_bIntFlag = false;
  return false;
}
*/
