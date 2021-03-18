#ifndef FRISTWIDGET_H
#define FRISTWIDGET_H

#include <QWidget>

namespace Ui {
class fristwidget;
}

class fristwidget : public QWidget
{
    Q_OBJECT

public:
    explicit fristwidget(QWidget *parent = nullptr);
    ~fristwidget();

private slots:

private:
    Ui::fristwidget *ui;
};

#endif // FRISTWIDGET_H
