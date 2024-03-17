#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QVector>
#include <QVector3D>
#include <cmath>
class worldObject
{
public:
    worldObject();
    QVector <double> currCoord{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // x, y, z, vx, vy, vx, ax, ay, az, mass
    //QVector <double> prevCoord{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    //QVector <double> tempCoord{0,0,0,0};
    worldObject(QVector <double> coord);
    ~worldObject();
};

#endif // WORLDOBJECT_H
