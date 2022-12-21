#ifndef DIALOG_H
#define DIALOG_H

#include <QColorDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QColorDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
