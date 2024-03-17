#ifndef TASK_DATA_H
#define TASK_DATA_H
#include <math.h>
#include <vector>
#include <queue>
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
    vector2d operator=(const vector2d& op)
    {
        x=op.x;
        y=op.y;
        return  vector2d(op.x, op.y);
    }

};
inline bool operator!=(const vector2d& L, const vector2d& R)
{
    return (L.x !=R.x || L.y!=R.y);
}
inline bool operator==(const vector2d& L, const vector2d& R)
{
    return (L.x == R.x+1||L.x == R.x-1 || L.x==R.x)  && (L.y==R.y-1 || L.y==R.y+1 || L.y==R.y);
}
inline bool operator<(const vector2d& L, const vector2d& R)
{
    return (L.y<R.y) || (L.x==R.x && L.y<R.y);
}
inline vector2d operator*(const double& t, const vector2d& v)
{
  return vector2d(t * v.x, t * v.y);
}

double cross(vector2d const & a, vector2d const & b);

enum Turn
{
    left,
    right,
    collinear
};
enum Turn it_turn(vector2d A, vector2d B, vector2d C);

struct task_data
{
  int n;
  double new_x;
  double new_y;
  std::vector <vector2d> points;
  std::vector <vector2d> points2;
  std::vector <vector2d> p;
  std::vector <vector2d> p2;
  bool m_bIntFlag;
  std::vector <std::pair<vector2d, vector2d> > segm;
  std::vector <std::pair<vector2d, vector2d> > segm2;
  std::vector <vector2d> intersections;
  std::queue <std::pair<std:: pair<std::pair<vector2d, int>, std::pair<vector2d, int> >, std::pair<vector2d, int> > > active;
  task_data()
  {
    m_bIntFlag = false;
  }
  vector2d intersec(vector2d A, vector2d B, vector2d C, vector2d D);
  bool point_in_mnoug(vector2d A);
  bool point_in_mnoug2(vector2d A);
  bool intersec_inner (vector2d A, vector2d B, vector2d C, vector2d D);
  bool intersec_inner2 (vector2d A, vector2d B, vector2d C, vector2d D);
};



#endif // TASK_DATA_H
