#ifndef TASK_DATA_H
#define TASK_DATA_H
#include <math.h>
#include <vector>

enum { ptA = 1, ptB, ptC, ptD };

struct vector2d
{
  double x;
  double y;

  vector2d() { }
  vector2d(double in_X, double in_Y) : x(in_X), y(in_Y) {}

  double length() { return sqrt(x * x + y * y); }

  vector2d operator+(const vector2d& op) const
  {
      return  vector2d(x + op.x, y + op.y);
  }

  vector2d operator-(const vector2d& op) const
  {
      return  vector2d(x - op.x, y - op.y);
  }

};

inline vector2d operator*(const double& t, const vector2d& v)
{
  return vector2d(t * v.x, t * v.y);
}

struct task_data
{
  int n;
  double new_x;
  double new_y;
  std::vector <vector2d> points;
  //bool m_bIntFlag;
  std::vector <vector2d> obol;
  task_data()
  {
   //m_bIntFlag = false;
  }

};



#endif // TASK_DATA_H
