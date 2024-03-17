#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include "task_data.h"

class DrawWidget : public QWidget
{
    Q_OBJECT

public:
    task_data * pTask;
    int state=2;
    bool parametrical;

public:
    explicit DrawWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);
    void SetTaskPtr(task_data * p) { pTask = p; }

    void addPoint();
    void deletePoint();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

protected:
    bool m_bMovePointFlag;
    int ptNum;
};

#endif // DRAWWIDGET_H
