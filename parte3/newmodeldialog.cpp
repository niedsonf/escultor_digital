#include "newmodeldialog.h"
#include "ui_newmodeldialog.h"

NewModelDialog::NewModelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewModelDialog)
{
    ui->setupUi(this);
}

NewModelDialog::~NewModelDialog()
{
    delete ui;
}
