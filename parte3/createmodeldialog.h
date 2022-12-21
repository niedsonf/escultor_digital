#ifndef CREATEMODELDIALOG_H
#define CREATEMODELDIALOG_H

#include <QDialog>
#include <stdlib.h>

namespace Ui {
class CreateModelDialog;
}

class CreateModelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateModelDialog(QWidget *parent = nullptr);
    ~CreateModelDialog();
    int getDimension(void);

private:
    Ui::CreateModelDialog *ui;
};

#endif // CREATEMODELDIALOG_H
