#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include "createmodeldialog.h"
#include <QDebug>
#include "voxel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->horizontalSliderZ, SIGNAL(valueChanged(int)), ui->sculptorDisplay, SLOT(changeZ(int)));
    connect(ui->actionNewModel, SIGNAL(triggered(bool)), this, SLOT(openNewModelDialog()));
    connect(this, SIGNAL(sendDimension(int)), ui->sculptorDisplay, SLOT(receiveDimension(int)));
    connect(this, SIGNAL(sendDisplay(std::vector<std::vector<Voxel>>)), ui->sculptorDisplay, SLOT(receivePlan(std::vector<std::vector<Voxel>>)));
    connect(ui->actionPutVoxel, SIGNAL(triggered(bool)), this, SLOT(putVoxelTool()));
    connect(ui->actionCutVoxel, SIGNAL(triggered(bool)), this, SLOT(cutVoxelTool()));
    connect(ui->actionPutBox, SIGNAL(triggered(bool)), this, SLOT(putBoxTool()));
    connect(ui->actionCutBox, SIGNAL(triggered(bool)), this, SLOT(cutBoxTool()));
    connect(ui->actionPutSphere, SIGNAL(triggered(bool)), this, SLOT(putSphereTool()));
    connect(ui->actionCutSphere, SIGNAL(triggered(bool)), this, SLOT(cutSphereTool()));
    connect(ui->actionPutEllipse, SIGNAL(triggered(bool)), this, SLOT(putEllipseTool()));
    connect(ui->actionCutEllipse, SIGNAL(triggered(bool)), this, SLOT(cutEllipseTool()));
    connect(ui->sculptorDisplay, SIGNAL(clickedVoxel(int,int,int)), this, SLOT(make(int,int,int)));
    emit sendDimension(dim);
    emit sendDisplay(sculptor.getPlan(0));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openNewModelDialog()
{
    CreateModelDialog d;
    if(d.exec() == QDialog::Accepted) {
        dim = d.getDimension();
        sculptor = Sculptor(dim, dim, dim);
        emit sendDimension(dim);
        emit sendDisplay(sculptor.getPlan(0));
    }
}

void MainWindow::putVoxelTool()
{
    tool = PutVoxel;
}

void MainWindow::cutVoxelTool()
{
    tool = CutVoxel;
}

void MainWindow::putBoxTool()
{
    tool = PutBox;
}

void MainWindow::cutBoxTool()
{
    tool = CutBox;
}

void MainWindow::putSphereTool()
{
    tool = PutSphere;
}

void MainWindow::cutSphereTool()
{
    tool = PutSphere;
}

void MainWindow::putEllipseTool()
{
    tool = PutEllipse;
}

void MainWindow::cutEllipseTool()
{
    tool = CutEllipse;
}

void MainWindow::make(int x, int y, int z)
{
    switch(tool){
        case PutVoxel:
            sculptor.putVoxel(x,y,z);
            break;
        case CutVoxel:
            sculptor.cutVoxel(x,y,z);
            break;
         default:
            sculptor.putVoxel(x,y,z);
            break;
    }
    emit sendDisplay(sculptor.getPlan(z));
}

