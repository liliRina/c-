#ifndef WORLD_H
#define WORLD_H

#include <QObject>

#include <QTimer>
#include <QDateTime>
#include <QFile>
#include <string>
#include "world.h"
#include <cmath>
#include <ctime>
#include <QVector>
#include <string>
#include <fstream>
#include <string>
#include <iostream>
#include "core/cTLE.h"
#include "orbit/cOrbit.h"
#include "core/coreLib.h"
#include "math.h"
#include <QObject>
#include "worldobject.h"
#include <vector>
class world : public QObject
{
    Q_OBJECT
public:
    explicit world(QObject *parent = nullptr);
    QVector <worldObject*> vector_objects;
    std::vector<double> world_Update(int time);
    void addObject(worldObject *obj);
    QVector <cOrbit> satellites;
    QVector  <QVector <double> >object;
    void create_world();

signals:

};

#endif // WORLD_H
