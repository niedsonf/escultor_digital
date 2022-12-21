#include "sculptordisplay.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QDebug>
#include <QMouseEvent>

SculptorDisplay::SculptorDisplay(QWidget *parent)
    : QWidget{parent}
{

}

void SculptorDisplay::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    QBrush brush;
    QPen pen;
    int ref = width() < height() ? width() : height();

    brush.setColor(Qt::lightGray);
    brush.setStyle(Qt::SolidPattern);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.setBrush(brush);

    int voxelDimension = ref/dim;
    int startPoint = 0;
    int linePoint = 0;

    for(int x=0; x<dim; x++){
        for(int y=0; y<dim; y++){
            if(currentDisplay[x][y].isOn){
                brush.setColor(Qt::cyan);
                painter.setBrush(brush);
            } else {
                brush.setColor(Qt::lightGray);
                painter.setBrush(brush);
            }
            painter.drawRect(startPoint,linePoint,voxelDimension,voxelDimension);
            startPoint += voxelDimension;
        }
        linePoint += voxelDimension;
        startPoint = 0;
    }


    /*for(float i=0.1; i<1; i+=0.1){
        painter.drawLine(0, ref*i, ref, ref*i);
    }*/

}

void SculptorDisplay::mousePressEvent(QMouseEvent *event)
{
    int ref = width() < height() ? width() : height();
    int voxelDimension = ref/dim;
    int posX = event->x()/voxelDimension, posY = event->y()/voxelDimension;
    qDebug() << "X: " << posX << " Y: " << posY;
    emit clickedVoxel(posX, posY, planZ);
    repaint();
}

void SculptorDisplay::changeZ(int plan)
{
    planZ = plan;
}

void SculptorDisplay::receiveDimension(int d)
{
    dim = d;
    repaint();
}

void SculptorDisplay::receivePlan(std::vector<std::vector<Voxel>> i)
{
    currentDisplay = i;
    repaint();
}
