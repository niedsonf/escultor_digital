#ifndef SCULPTORDISPLAY_H
#define SCULPTORDISPLAY_H

#include <QWidget>
#include "stdlib.h"
#include "voxel.h"

class SculptorDisplay : public QWidget
{
    Q_OBJECT
private:
    int dim;
    int planZ;
    std::vector<std::vector<Voxel>> currentDisplay;
public:
    explicit SculptorDisplay(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
public slots:
    void changeZ(int plan);
    void receiveDimension(int);
    void receivePlan(std::vector<std::vector<Voxel>>);
signals:
    void clickedVoxel(int x, int y, int z);
};

#endif // SCULPTORDISPLAY_H
