#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "sculptor.h"
#include "stdlib.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum Tools{PutVoxel, CutVoxel, PutBox, CutBox, PutSphere, CutSphere, PutEllipse, CutEllipse};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void changeTool(Tools);
public slots:
    void openNewModelDialog(void);
    void putVoxelTool(void);
    void cutVoxelTool(void);
    void putBoxTool(void);
    void cutBoxTool(void);
    void putSphereTool(void);
    void cutSphereTool(void);
    void putEllipseTool(void);
    void cutEllipseTool(void);
    void writeOFF(void);
    void make(int,int,int);
    void changedPlan(int);
    void pickColor(void);
    void getFrontView(void);
    void getBackView(void);
    void getLeftView(void);
    void getRightView(void);
    void getTopView(void);
    void getBottomView(void);
    void getLayerView(void);
signals:
    void sendDimension(int d);
    void sendDisplay(std::vector<std::vector<Voxel>>);
    void sendPlan(int);
private:
    Ui::MainWindow *ui;
    Sculptor *sculptor = new Sculptor(10,10,10);
    int dim = 10;
    Tools tool;
    std::vector<QPushButton*> viewButtons;
};
#endif // MAINWINDOW_H
