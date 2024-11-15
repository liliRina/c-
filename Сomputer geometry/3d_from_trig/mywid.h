#ifndef MYWID_H
#define MYWID_H

#include <QWidget>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include <QPainter>
class mywid : public QWidget
{
    Q_OBJECT
public:
    explicit mywid(QWidget *parent = nullptr);

public slots:
    void paintEvent(QPaintEvent *event);
public:
    const TGAColor white = TGAColor(255, 0, 0, 255);
    const TGAColor red   = TGAColor(255, 0,   0,   255);
    const TGAColor green = TGAColor(0,   255, 0,   255);
    //int W = width();
   // int H = height();

    const int W  = 500;
    const int H = 500;
};

#endif // MYWID_H
