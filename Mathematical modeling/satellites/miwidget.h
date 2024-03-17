#ifndef MIWIDGET_H
#define MIWIDGET_H
#include <QGLWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTime>
#include "miwidget.h"
#include "world.h"
#include <QWidget>
class miWidget : public QOpenGLWidget,protected QOpenGLFunctions
{
public:
    void paint_cube(int x, int y, int z);
    explicit miWidget(QWidget *parent = 0);
    void updateGl_(double x_, double y_, double z_);
    world* My_world;
protected:
    void paintGL() Q_DECL_OVERRIDE;
    void initializeGL() Q_DECL_OVERRIDE;//reimplementando las funciones virtuales
    void resizeGL(int w, int h)Q_DECL_OVERRIDE;
    void graficarLineas();



public:
    double x=1, y=1, z=1;
    double rotate_y=0;
    double rotate_x=0;
    double rotate_z=0;
    double count=0;
    double x11;
    double y11;
    double z11;

    double x1;
    double y1;
    double z1;
    double x2;
    double y2;
    double z2;
    double plus=0.1*3.14;
};

#endif // MIWIDGET_H
