#include "createmodeldialog.h"
#include "ui_createmodeldialog.h"

CreateModelDialog::CreateModelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateModelDialog)
{
    ui->setupUi(this);
}

CreateModelDialog::~CreateModelDialog()
{
    delete ui;
}

int CreateModelDialog::getDimension()
{
    return ui->horizontalSliderD->value();
}
