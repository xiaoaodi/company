#include "register.h"
#include "ui_register.h"

register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

register::~Register()
{
delete ui;
}
