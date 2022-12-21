#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sculptor.h"
#include "stdlib.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum tools{PutVoxel, CutVoxel, PutBox, CutBox, PutSphere, CutSphere, PutEllipse, CutEllipse};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    void make(int,int,int);
signals:
    void sendDimension(int d);
    void sendDisplay(std::vector<std::vector<Voxel>>);
private:
    Ui::MainWindow *ui;
    Sculptor sculptor = Sculptor(10,10,10);
    int dim = 10;
    tools tool = PutVoxel;
};
#endif // MAINWINDOW_H
