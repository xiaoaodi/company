#ifndef WIDGET_H
#define WIDGET_H

#include "mysql.h"
#include "workerwindow.h"
#include <QWidget>
#include <QButtonGroup>
#include <QPushButton>
#include "adminwindow.h"
#include <QSqlQuery>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QString admin_account;
    QString admin_password;

public slots:

    void  dealadminwindow();
    void  dealadminwindow1();



private slots:
    void on_pushButton_3_clicked();

    void on_login_clicked();

    void on_cancel_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Widget *ui;
    QButtonGroup *bg;

    AdminWindow *adminwindow;
    workerwindow *workerwin;


};

#endif // WIDGET_H
