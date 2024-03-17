#include "task_data.h"
double cross(vector2d const & a, vector2d const & b)
{
   return a.x * b.y - b.x * a.y;
}

enum Turn it_turn(vector2d A, vector2d B, vector2d C)
{
    double l = (B.x - A.x) * (C.y - A.y);
    double r = (C.x - A.x) * (B.y - A.y);
    //double e = (abs(l) + abs( r)) * std::numeric_limits<double>::epsilon() * 4;
    double e = (abs(l) + abs( r)) * 3.14 * 4;
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

