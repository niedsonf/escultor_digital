#ifndef NEWMODELDIALOG_H
#define NEWMODELDIALOG_H

#include <QDialog>
#include <stdlib.h>

namespace Ui {
class NewModelDialog;
}

class NewModelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewModelDialog(QWidget *parent = nullptr);
    ~NewModelDialog();

private:
    Ui::NewModelDialog *ui;

};

#endif // NEWMODELDIALOG_H
