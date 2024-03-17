#ifndef TASK_DATA_H
#define TASK_DATA_H
#include <math.h>
#include <QVector>

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
  bool operator!=(const vector2d& op) const
  {
      return  (x - op.x != 0) or (y - op.y!=0);
  }

};

inline vector2d operator*(const double& t, const vector2d& v)
{
  return vector2d(t * v.x, t * v.y);
}


struct task_data
{
  QVector<vector2d> points;

  task_data() {  }
  QVector<int> graham();
  QPair<QVector<double>, QVector<double> > lagrange();
  QPair<QVector<double>, QVector<double>> lagrange_parametrical();

  QPair<QVector<double>, QVector<double>> hermite();
  QPair<QVector<double>, QVector<double>> hermite_parametrical();

  QVector<double> tridiagonal_matrix_algorithm(QVector<double> a, QVector<double> b, QVector<double> c, QVector<double> d);

  QPair<QVector<double>, QVector<double>> cubic();
  QPair<QVector<double>, QVector<double>> cubic_parametrical();
};



#endif // TASK_DATA_H
