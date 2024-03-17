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

    void SetDefaultPoints();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);
    void triag();

protected:

    bool m_bMovePointFlag;
    int ptNum;

signals:

    void signalPointsChanged();

public slots:


};

#endif // DRAWWIDGET_H
