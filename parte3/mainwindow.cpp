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
    //SET UI AND SLIDERS VALUES
    ui->setupUi(this);
    ui->horizontalSliderPlan->setMaximum(dim-1);
    ui->horizontalSliderRadius->setMaximum(dim);
    ui->horizontalSliderXRadius->setMaximum(dim);
    ui->horizontalSliderYRadius->setMaximum(dim);
    ui->horizontalSliderZRadius->setMaximum(dim);
    ui->horizontalSliderXSize->setMaximum(dim);
    ui->horizontalSliderYSize->setMaximum(dim);
    ui->horizontalSliderZSize->setMaximum(dim);

    connect(ui->horizontalSliderPlan, SIGNAL(valueChanged(int)), this, SLOT(changedPlan(int)));
    connect(ui->actionNewModel, SIGNAL(triggered(bool)), this, SLOT(openNewModelDialog()));
    connect(this, SIGNAL(sendPlan(int)), ui->sculptorDisplay, SLOT(receivePlanNumber(int)));
    connect(this, SIGNAL(sendDimension(int)), ui->sculptorDisplay, SLOT(receiveDimension(int)));
    connect(this, SIGNAL(sendDisplay(std::vector<std::vector<Voxel>>)), ui->sculptorDisplay, SLOT(receivePlan(std::vector<std::vector<Voxel>>)));

    //CONNECT ACTION Tools
    connect(ui->actionPutVoxel, SIGNAL(triggered(bool)), this, SLOT(putVoxelTool()));
    connect(ui->actionCutVoxel, SIGNAL(triggered(bool)), this, SLOT(cutVoxelTool()));
    connect(ui->actionPutBox, SIGNAL(triggered(bool)), this, SLOT(putBoxTool()));
    connect(ui->actionCutBox, SIGNAL(triggered(bool)), this, SLOT(cutBoxTool()));
    connect(ui->actionPutSphere, SIGNAL(triggered(bool)), this, SLOT(putSphereTool()));
    connect(ui->actionCutSphere, SIGNAL(triggered(bool)), this, SLOT(cutSphereTool()));
    connect(ui->actionPutEllipse, SIGNAL(triggered(bool)), this, SLOT(putEllipseTool()));
    connect(ui->actionCutEllipse, SIGNAL(triggered(bool)), this, SLOT(cutEllipseTool()));

    connect(ui->sculptorDisplay, SIGNAL(clickedVoxel(int,int,int)), this, SLOT(make(int,int,int)));
    connect(ui->pushButtonColor, SIGNAL(clicked(bool)), this, SLOT(pickColor()));
    connect(ui->actionBuildOFF, SIGNAL(triggered(bool)), this, SLOT(writeOFF(void)));

    //CONNECT PUSH BUTTONS VIEWS
    connect(ui->pushButtonFrontView, SIGNAL(clicked(bool)), this, SLOT(getFrontView()));
    connect(ui->pushButtonBackView, SIGNAL(clicked(bool)), this, SLOT(getBackView()));
    connect(ui->pushButtonLeftView, SIGNAL(clicked(bool)), this, SLOT(getLeftView()));
    connect(ui->pushButtonRightView, SIGNAL(clicked(bool)), this, SLOT(getRightView()));
    connect(ui->pushButtonTopView, SIGNAL(clicked(bool)), this, SLOT(getTopView()));
    connect(ui->pushButtonBottomView, SIGNAL(clicked(bool)), this, SLOT(getBottomView()));
    connect(ui->pushButtonLayerView, SIGNAL(clicked(bool)), this, SLOT(getLayerView()));

    emit sendDimension(dim);
    emit sendDisplay(sculptor->getPlan(ui->horizontalSliderPlan->value()));
    changeTool(PutVoxel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeTool(Tools t)
{
    tool = t;
    std::vector<QAction *> actionTools = {ui->actionPutVoxel, ui->actionCutVoxel, ui->actionPutBox, ui->actionCutBox, ui->actionPutSphere, ui->actionCutSphere, ui->actionPutEllipse, ui->actionCutEllipse};
    switch(t){
    case PutVoxel:
        for(int i=0; i<actionTools.size(); i++){
            if(actionTools.at(i) == actionTools[0]){
                actionTools[i]->setChecked(true);
            } else {
                actionTools[i]->setChecked(false);
            }
        }
        break;

    case CutVoxel:
        for(int i=0; i<actionTools.size(); i++){
            if(actionTools.at(i) == actionTools[1]){
                actionTools[i]->setChecked(true);
            } else {
                actionTools[i]->setChecked(false);
            }
        }
        break;

    case PutBox:
        for(int i=0; i<actionTools.size(); i++){
            if(actionTools.at(i) == actionTools[2]){
                actionTools[i]->setChecked(true);
            } else {
                actionTools[i]->setChecked(false);
            }
        }
        break;

    case CutBox:
        for(int i=0; i<actionTools.size(); i++){
            if(actionTools.at(i) == actionTools[3]){
                actionTools[i]->setChecked(true);
            } else {
                actionTools[i]->setChecked(false);
            }
        }
        break;

    case PutSphere:
        for(int i=0; i<actionTools.size(); i++){
            if(actionTools.at(i) == actionTools[4]){
                actionTools[i]->setChecked(true);
            } else {
                actionTools[i]->setChecked(false);
            }
        }
        break;

    case CutSphere:
        for(int i=0; i<actionTools.size(); i++){
            if(actionTools.at(i) == actionTools[5]){
                actionTools[i]->setChecked(true);
            } else {
                actionTools[i]->setChecked(false);
            }
        }
        break;

    case PutEllipse:
        for(int i=0; i<actionTools.size(); i++){
            if(actionTools.at(i) == actionTools[6]){
                actionTools[i]->setChecked(true);
            } else {
                actionTools[i]->setChecked(false);
            }
        }
        break;

    case CutEllipse:
        for(int i=0; i<actionTools.size(); i++){
            if(actionTools.at(i) == actionTools[7]){
                actionTools[i]->setChecked(true);
            } else {
                actionTools[i]->setChecked(false);
            }
        }
        break;
    default:
        for(int i=0; i<actionTools.size(); i++){
            if(actionTools.at(i) == actionTools[0]){
                actionTools[i]->setChecked(false);
            } else {
                actionTools[i]->setChecked(true);
            }
        }
        break;
    }
}


void MainWindow::openNewModelDialog()
{
    CreateModelDialog d;
    if(d.exec() == QDialog::Accepted) {
        dim = d.getDimension();
        delete sculptor;
        sculptor = new Sculptor(dim, dim, dim);
        ui->horizontalSliderPlan->setMaximum(dim-1);
        ui->horizontalSliderPlan->setValue(0);
        ui->horizontalSliderRadius->setMaximum(dim);
        ui->horizontalSliderXRadius->setMaximum(dim);
        ui->horizontalSliderYRadius->setMaximum(dim);
        ui->horizontalSliderZRadius->setMaximum(dim);
        ui->horizontalSliderXSize->setMaximum(dim);
        ui->horizontalSliderYSize->setMaximum(dim);
        ui->horizontalSliderZSize->setMaximum(dim);
        emit sendDimension(dim);
        emit sendDisplay(sculptor->getPlan(0));
    }
}

void MainWindow::putVoxelTool()
{
    changeTool(PutVoxel);
}

void MainWindow::cutVoxelTool()
{
    changeTool(CutVoxel);
}

void MainWindow::putBoxTool()
{
    changeTool(PutBox);
}

void MainWindow::cutBoxTool()
{
    changeTool(CutBox);
}

void MainWindow::putSphereTool()
{
    changeTool(PutSphere);
}

void MainWindow::cutSphereTool()
{
    changeTool(CutSphere);
}

void MainWindow::putEllipseTool()
{
    changeTool(PutEllipse);
}

void MainWindow::cutEllipseTool()
{
    changeTool(CutEllipse);
}

void MainWindow::writeOFF()
{
    sculptor->writeOFF(ui->lineEditFileName->text());
}

void MainWindow::make(int x, int y, int z)
{
    switch(tool){
    case PutVoxel:
        sculptor->putVoxel(x,y,z);
        break;
    case CutVoxel:
        sculptor->cutVoxel(x,y,z);
        break;
    case PutBox:
        sculptor->putBox(x, x+ui->horizontalSliderXSize->value(), y, y+ui->horizontalSliderYSize->value(), z, z+ui->horizontalSliderZSize->value());
        break;
    case CutBox:
        sculptor->cutBox(x, x+ui->horizontalSliderXSize->value(), y, y+ui->horizontalSliderYSize->value(), z, z+ui->horizontalSliderZSize->value());
        break;
    case PutSphere:
        sculptor->putSphere(x,y,z,ui->horizontalSliderRadius->value());
        break;
    case CutSphere:
        sculptor->cutSphere(x,y,z,ui->horizontalSliderRadius->value());
        break;
    case PutEllipse:
        sculptor->putEllipsoid(x,y,z,ui->horizontalSliderXRadius->value(), ui->horizontalSliderYRadius->value(), ui->horizontalSliderZRadius->value());
        break;
    case CutEllipse:
        sculptor->cutEllipsoid(x,y,z,ui->horizontalSliderXRadius->value(), ui->horizontalSliderYRadius->value(), ui->horizontalSliderZRadius->value());
        break;
    }
    emit sendDisplay(sculptor->getPlan(z));
}

void MainWindow::changedPlan(int i)
{
    viewButtons = {ui->pushButtonFrontView, ui->pushButtonBackView, ui->pushButtonTopView, ui->pushButtonBottomView, ui->pushButtonLeftView, ui->pushButtonRightView, ui->pushButtonLayerView};
    for(int i=0; i<viewButtons.size(); i++){
        if(viewButtons.at(i) == viewButtons[6]){
            viewButtons[i]->setChecked(true);
        } else {
            viewButtons[i]->setChecked(false);
        }
    }
    emit sendDisplay(sculptor->getPlan(i));
    emit sendPlan(i);
}

void MainWindow::pickColor()
{
    QColor color = QColorDialog::getColor(Qt::cyan, this, "Pick a color");
    if(color.isValid()) {
        sculptor->setColor(color.red(), color.green(), color.blue(), 255);
    }
}

void MainWindow::getFrontView()
{
    viewButtons = {ui->pushButtonFrontView, ui->pushButtonBackView, ui->pushButtonTopView, ui->pushButtonBottomView, ui->pushButtonLeftView, ui->pushButtonRightView, ui->pushButtonLayerView};
    for(int i=0; i<viewButtons.size(); i++){
        if(viewButtons.at(i) == viewButtons[0]){
            viewButtons[i]->setChecked(true);
        } else {
            viewButtons[i]->setChecked(false);
        }
    }
    emit sendDisplay(sculptor->getView(FrontView));
}

void MainWindow::getBackView()
{
    viewButtons = {ui->pushButtonFrontView, ui->pushButtonBackView, ui->pushButtonTopView, ui->pushButtonBottomView, ui->pushButtonLeftView, ui->pushButtonRightView, ui->pushButtonLayerView};
    for(int i=0; i<viewButtons.size(); i++){
        if(viewButtons.at(i) == viewButtons[1]){
            viewButtons[i]->setChecked(true);
        } else {
            viewButtons[i]->setChecked(false);
        }
    }
    emit sendDisplay(sculptor->getView(BackView));
}

void MainWindow::getLeftView()
{
    viewButtons = {ui->pushButtonFrontView, ui->pushButtonBackView, ui->pushButtonTopView, ui->pushButtonBottomView, ui->pushButtonLeftView, ui->pushButtonRightView, ui->pushButtonLayerView};
    for(int i=0; i<viewButtons.size(); i++){
        if(viewButtons.at(i) == viewButtons[4]){
            viewButtons[i]->setChecked(true);
        } else {
            viewButtons[i]->setChecked(false);
        }
    }
    emit sendDisplay(sculptor->getView(LeftView));
}

void MainWindow::getRightView()
{
    viewButtons = {ui->pushButtonFrontView, ui->pushButtonBackView, ui->pushButtonTopView, ui->pushButtonBottomView, ui->pushButtonLeftView, ui->pushButtonRightView, ui->pushButtonLayerView};
    for(int i=0; i<viewButtons.size(); i++){
        if(viewButtons.at(i) == viewButtons[5]){
            viewButtons[i]->setChecked(true);
        } else {
            viewButtons[i]->setChecked(false);
        }
    }
    emit sendDisplay(sculptor->getView(RightView));
}

void MainWindow::getTopView()
{
    viewButtons = {ui->pushButtonFrontView, ui->pushButtonBackView, ui->pushButtonTopView, ui->pushButtonBottomView, ui->pushButtonLeftView, ui->pushButtonRightView, ui->pushButtonLayerView};
    for(int i=0; i<viewButtons.size(); i++){
        if(viewButtons.at(i) == viewButtons[2]){
            viewButtons[i]->setChecked(true);
        } else {
            viewButtons[i]->setChecked(false);
        }
    }
    emit sendDisplay(sculptor->getView(TopView));
}

void MainWindow::getBottomView()
{
    viewButtons = {ui->pushButtonFrontView, ui->pushButtonBackView, ui->pushButtonTopView, ui->pushButtonBottomView, ui->pushButtonLeftView, ui->pushButtonRightView, ui->pushButtonLayerView};
    for(int i=0; i<viewButtons.size(); i++){
        if(viewButtons.at(i) == viewButtons[3]){
            viewButtons[i]->setChecked(true);
        } else {
            viewButtons[i]->setChecked(false);
        }
    }
    emit sendDisplay(sculptor->getView(BottomView));
}

void MainWindow::getLayerView()
{
    viewButtons = {ui->pushButtonFrontView, ui->pushButtonBackView, ui->pushButtonTopView, ui->pushButtonBottomView, ui->pushButtonLeftView, ui->pushButtonRightView, ui->pushButtonLayerView};
    for(int i=0; i<viewButtons.size(); i++){
        if(viewButtons.at(i) == viewButtons[6]){
            viewButtons[i]->setChecked(true);
        } else {
            viewButtons[i]->setChecked(false);
        }
    }

    emit sendDisplay(sculptor->getPlan(ui->horizontalSliderPlan->value()));

}

