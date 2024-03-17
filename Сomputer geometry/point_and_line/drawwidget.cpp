#include "drawwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>

const int circ_size = 20;

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
  pTask = 0;
  m_bMovePointFlag = false;
}


void DrawWidget::paintEvent(QPaintEvent *event)
{

  QPainter p(this);
 // p.drawArc(200, 200, 100, 100, 0, 360 * 16);

  if(pTask)
  {
    p.drawLine(pTask->A.x, pTask->A.y, pTask->B.x, pTask->B.y);

    p.drawArc(pTask->A.x - circ_size / 2, pTask->A.y - circ_size / 2, circ_size, circ_size, 0, 360 * 16);
    p.drawArc(pTask->B.x - circ_size / 2, pTask->B.y - circ_size / 2, circ_size, circ_size, 0, 360 * 16);
    p.drawArc(pTask->C.x - circ_size / 2, pTask->C.y - circ_size / 2, circ_size, circ_size, 0, 360 * 16);

    QFont font = p.font();
    font.setPixelSize(24);
    p.setFont(font);

    p.drawText(pTask->A.x + circ_size / 2, pTask->A.y  - circ_size / 2, "A");
    p.drawText(pTask->B.x + circ_size / 2, pTask->B.y  - circ_size / 2, "B");
    p.drawText(pTask->C.x + circ_size / 2, pTask->C.y  - circ_size / 2, "C");

  }
}

void DrawWidget::SetDefaultPoints()
{
  if(pTask)
  {
    int w = width();
    int h = height();
    pTask->A = vector2d(w / 3, h / 2);
    pTask->B = vector2d(2 * w / 3, h / 2);
    pTask->C = vector2d(w / 2, h / 3);
    pTask->it_turn();

  }
}

void DrawWidget::mouseMoveEvent(QMouseEvent *event)
{
  if(m_bMovePointFlag)
  {
    vector2d curPos(event->x(), event->y());
    if(ptNum == ptA)
    {
      pTask->A = curPos;
      pTask->it_turn();
      repaint();
      emit signalPointsChanged();
    }
    else
    if(ptNum == ptB)
    {
      pTask->B = curPos;
      pTask->it_turn();
      repaint();
      emit signalPointsChanged();
    }
    else
    if(ptNum == ptC)
    {
      pTask->C = curPos;
      pTask->it_turn();
      repaint();
      emit signalPointsChanged();
    }
  }
}

void DrawWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
      int XX = event->x();
      int YY = event->y();
      vector2d v(XX, YY);

      if((v - pTask->A).length() < circ_size / 2)
      {
        m_bMovePointFlag = true;
        ptNum = ptA;
      }
      else if((v - pTask->B).length() < circ_size / 2)
      {
        m_bMovePointFlag = true;
        ptNum = ptB;
      }
      else if((v - pTask->C).length() < circ_size / 2)
      {
        m_bMovePointFlag = true;
        ptNum = ptC;
      }


    }
}

void DrawWidget::mouseReleaseEvent(QMouseEvent *event)
{
  m_bMovePointFlag = false;
}

void DrawWidget :: on_Ay_changed(const QString& txt)
{
    // some validation
    bool flag = true;
    double val = txt.toDouble(&flag); //ui->le_Ax->text().toDouble();
    if(!flag)
    {
        QMessageBox msgBox;
        msgBox.setText("Error in coordinate x of point A.");
        msgBox.exec();

        //ui->le_Ax->setText(QString::number(current_task.A.x));
    }
    else {
      pTask->A.y = val;
    }
    pTask->it_turn();
   // pTask->testIntersection();
    repaint();
}
