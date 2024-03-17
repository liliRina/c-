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

protected:

    bool m_bMovePointFlag;
    int ptNum;

signals:

    void signalPointsChanged();

public slots:
     void on_Ay_changed(const QString& txt);

};

#endif // DRAWWIDGET_H
