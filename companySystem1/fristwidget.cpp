#include "fristwidget.h"
#include "ui_fristwidget.h"

fristwidget::fristwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fristwidget)
{
    ui->setupUi(this);
}

fristwidget::~fristwidget()
{
    delete ui;
}
