#include "modelview.h"
#include "ui_modelview.h"

ModelView::ModelView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModelView)
{
    ui->setupUi(this);
}

ModelView::~ModelView()
{
    delete ui;
}
