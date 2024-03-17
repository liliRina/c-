#include "miwidget.h"
#include <iostream>
#include <QtGui>
#include <QObject>
#include <QQuaternion>
#include <QGLWidget>
miWidget::miWidget(QWidget *parent):QOpenGLWidget(parent)// гн
{
    My_world=new world();
}


void miWidget::initializeGL()
{

    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20, 20, -20, 20, 20, -20);
}

void miWidget::resizeGL(int w, int h)
{          // присваивает проекционной матрице единичную матрицу
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-3, 5, -3, 5, -3, 3);
}

void miWidget::updateGl_(double x_, double y_, double z_)
{

}
void miWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10000, 10000, -10000, 10000, 10000, -10000);

    int rad=1100;
    glColor3f( 1.0, 0.0, 1.0 );
    glBegin(GL_POLYGON);
    glVertex3f( rad, -rad, rad );
    glVertex3f( rad, rad, rad );
    glVertex3f( -rad, rad, rad);
    glVertex3f( -rad, -rad, rad );
    glEnd();
    count+=plus;

    for (int i=1; i<My_world->object.size(); i++)
    {

        std::cout<<i<<std::endl;
         paint_cube(My_world->object[i][0], My_world->object[i][1], My_world->object[i][2]);


    }

    glFlush();
    this->makeCurrent();
}






void miWidget ::paint_cube(int x, int y, int z)
{
    int len=500;
    int rad=50;
    double A=count, B=0, C=count;
    //std::cout<<A<<std::endl;

    double sx = sin(A), cx = cos(A),
           sy = sin(B), cy = cos(B),
           sz = sin(C), cz = cos(C);
    std::cout<<x<<" "<<y<<" "<<z<<std::endl;
    glBegin(GL_LINES);
    glColor3f( 1.0, 1.0, 0.0 );
    glVertex3f(x, y, z );
    x11=len;
    y11=0;
    z11=0;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f( x+x11, y+y11, z+z11 );


    glColor3f( 0.0, 1.0, 0.0 );
    glVertex3f(x, y, z );
    x11=0;
    y11=len;
    z11=0;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f( x+x11, y+y11, z+z11 );
    glColor3f( 1.0, 0.0, 1.0 );
        glVertex3f( x, y, z );      // P1 es rojo
        x11=0;
        y11=0;
        z11=len;
        x1 =  x11 * cz +  y11 * sz;
        y1 =  y11 * cz -  x11 * sz;
        z1 =  z11;
        x2 = x1 * cy + z1 * sy;
        y2 = y1;
        z2 = z1 * cy - x1 * sy;
        x11=x2;
        y11=y2 * cx + z1 * sx;
        z11=z2 * cx - x1 * sx;
        glVertex3f( x+x11, y+y11, z+z11 );
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f( 1.0, 1.0, 1.0 ); //бочок

    x11=rad;
    y11=-rad;
    z11=rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f( x+x11, y+y11, z+z11 );        // P1 es rojo

    x11=rad;
    y11=rad;
    z11=rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f( x+x11, y+y11, z+z11 );

    x11=-rad;
    y11=rad;
    z11=rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f( x+x11, y+y11, z+z11);        // P3 es azul

    x11=-rad;
    y11=-rad;
    z11=rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f( x+x11, y+y11, z+z11 );
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f( 0.0, 1.0, 1.0 ); //бочок

    x11=rad;
    y11=-rad;
    z11=-rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f( x+x11, y+y11, z+z11 );      // P1 es rojo

    x11=rad;
    y11=rad;
    z11=-rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f(x+x11, y+y11, z+z11);       // P2 es verde

    x11=-rad;
    y11=+rad;
    z11=-rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f(x+x11, y+y11, z+z11 );        // P3 es azul

    x11=-rad;
    y11=-rad;
    z11=-rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f( x+x11, y+y11, z+z11 );        // P4 es morado
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f( 1.0, 0.0, 1.0 ); //бок

    x11=rad;
    y11=-rad;
    z11=-rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f( x+x11, y+y11, z+z11);        // P1 es rojo

    x11=rad;
    y11=rad;
    z11=-rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f( x+x11, y+y11, z+z11 );       // P2 es verde

    x11=rad;
    y11=rad;
    z11=rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f( x+x11, y+y11, z+z11 );        // P3 es azul

    x11=rad;
    y11=-rad;
    z11=rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f( x+x11, y+y11, z+z11 );        // P4 es morado
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f( 0.0, 1.0, 0.0 );//бок

    x11=-rad;
    y11=-rad;
    z11=rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f(x+x11, y+y11, z+z11 );        // P1 es rojo

    x11=-rad;
    y11=rad;
    z11=rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f( x+x11, y+y11, z+z11);        // P2 es verde

    x11=-rad;
    y11=rad;
    z11=-rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f( x+x11, y+y11, z+z11 );        // P3 es azul

    x11=-rad;
    y11=-rad;
    z11=-rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f( x+x11, y+y11, z+z11 );        // P4 es morado
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f( 1.0, 1.0, 0.0 );//морда
    x11=rad;
    y11=rad;
    z11=rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f( x+x11, y+y11, z+z11 );        // P1 es rojo

    x11=rad;
    y11=rad;
    z11=-rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f(x+x11, y+y11, z+z11 );        // P2 es verde

    x11=-rad;
    y11=rad;
    z11=-rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f (x+x11, y+y11, z+z11 );        // P3 es azul

    x11=-rad;
    y11=rad;
    z11=rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f( x+x11, y+y11, z+z11 );        // P4 es morado
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f( 1.0, 0.0, 0.0 );//жопа

    x11=rad;
    y11=-rad;
    z11=-rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f(x+x11, y+y11, z+z11 );        // P1 es rojo

    x11=rad;
    y11=-rad;
    z11=rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f(x+x11, y+y11, z+z11 );       // P2 es verde

    x11=-rad;
    y11=-rad;
    z11=rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f(x+x11, y+y11, z+z11);        // P3 es azul

    x11=-rad;
    y11=-rad;
    z11=-rad;
    x1 =  x11 * cz +  y11 * sz;
    y1 =  y11 * cz -  x11 * sz;
    z1 =  z11;
    x2 = x1 * cy + z1 * sy;
    y2 = y1;
    z2 = z1 * cy - x1 * sy;
    x11=x2;
    y11=y2 * cx + z1 * sx;
    z11=z2 * cx - x1 * sx;
    glVertex3f(x+x11, y+y11, z+z11);        // P4 es morado

    glEnd();
}

/*  x1 =  x * cz +  y * sz  // Rotation of each vertex
    y1 =  y * cz -  x * sz
    z1 =  z

    x2 = x1 * cy + z1 * sy
    y2 = z1
    z2 = z1 * cy - x1 * sy

    x3 = x2
    y3 = y2 * cx + z1 * sx
    z3 = z2 * cx - x1 * sx*/
