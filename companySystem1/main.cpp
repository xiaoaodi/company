#include "widget.h"
#include "mysql.h"
#include "frist.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mysql sq;
    sq.initsql();
    Widget w;
    w.show();
    return a.exec();
}
