#include "frist.h"
#include "ui_frist.h"

frist::frist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frist)
{
    ui->setupUi(this);
}

frist::~frist()
{
    delete ui;
}

void frist::on_pushButton_clicked()
{

}
