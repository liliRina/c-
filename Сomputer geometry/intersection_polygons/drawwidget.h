#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include "task_data.h"

class DrawWidget : public QWidget
{
    Q_OBJECT

public:

    task_data * pTask;

public:
    explicit DrawWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);
    void SetTaskPtr(task_data * p) { pTask = p; }
    void get_inters();
    void SetDefaultPoints();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);
    void triag();

    bool have  (vector2d A, vector2d B,vector2d C);
    bool isInside(vector2d A, vector2d B, vector2d C);
    std::vector <std::vector<int>> nado;
    QPolygonF s_f (const QPolygonF &r);

protected:

    bool m_bMovePointFlag;
    bool first;
    int ptNum;

    std::vector <std::vector <vector2d> > tupl;

signals:

    void signalPointsChanged();

public slots:


};

#endif // DRAWWIDGET_H
