#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include "mysql.h"
#include "widget.h"

namespace Ui {
class  Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private:
    Ui::Register *ui;

    QWidget *p;

};

#endif // REGISTER_H
