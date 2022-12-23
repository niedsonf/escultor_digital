#include "sculptordisplay.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QDebug>
#include <QMouseEvent>

SculptorDisplay::SculptorDisplay(QWidget *parent)
    : QWidget{parent}
{
    setMouseTracking(true);
}

void SculptorDisplay::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    QBrush brush;
    QPen pen;
    int ref = width() < height() ? width() : height();

    brush.setColor(Qt::lightGray);
    brush.setStyle(Qt::Dense4Pattern);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.setBrush(brush);

    int voxelDimension = ref/dim;
    int startPoint = 0;
    int linePoint = 0;

    for(int x=0; x<dim; x++){
        for(int y=0; y<dim; y++){
            if(currentDisplay[x][y].isOn){
                brush.setColor(QColor(currentDisplay[x][y].r, currentDisplay[x][y].g, currentDisplay[x][y].b, currentDisplay[x][y].a));
                brush.setStyle(Qt::SolidPattern);
                painter.setBrush(brush);

            } else {
                brush.setColor(Qt::lightGray);
                brush.setStyle(Qt::Dense4Pattern);
                painter.setBrush(brush);
            }
            painter.drawRect(startPoint,linePoint,voxelDimension,voxelDimension);

            startPoint += voxelDimension;
        }
        linePoint += voxelDimension;
        startPoint = 0;
    }

}

void SculptorDisplay::mousePressEvent(QMouseEvent *event)
{
    int ref = width() < height() ? width() : height();
    int voxelDimension = ref/dim;
    int posX = event->x()/voxelDimension, posY = event->y()/voxelDimension;
    isPressed = true;
    if(isPressed && event->x() < ref && event->y() < ref) {clickedVoxel(posX, posY, planZ);}
}

void SculptorDisplay::mouseMoveEvent(QMouseEvent *event)
{
    int ref = width() < height() ? width() : height();
    int voxelDimension = ref/dim;
    int posX = event->x()/voxelDimension, posY = event->y()/voxelDimension;
    if(isPressed && event->x() < ref && event->y() < ref) {clickedVoxel(posX, posY, planZ);}
    repaint();
}

void SculptorDisplay::mouseReleaseEvent(QMouseEvent *event)
{
    isPressed = false;
}

void SculptorDisplay::receiveDimension(int d)
{
    dim = d;
}

void SculptorDisplay::receivePlan(std::vector<std::vector<Voxel>> i)
{
    currentDisplay = i;
    repaint();
}

void SculptorDisplay::receivePlanNumber(int i)
{
    planZ = i;
}
