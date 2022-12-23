#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <QDialog>

namespace Ui {
class ModelView;
}

class ModelView : public QDialog
{
    Q_OBJECT

public:
    explicit ModelView(QWidget *parent = nullptr);
    ~ModelView();

private:
    Ui::ModelView *ui;
};

#endif // MODELVIEW_H
