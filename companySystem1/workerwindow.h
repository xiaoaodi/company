#ifndef WORKERWINDOW_H
#define WORKERWINDOW_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include "mysql.h"

namespace Ui {
class workerwindow;
}

class workerwindow : public QWidget
{
    Q_OBJECT

public:
    explicit workerwindow(QWidget *parent = nullptr);
    ~workerwindow();


    QString workers_account;
    QString workers_password;

    int workers_id;
    int workers_deptid;
    QString workers_name;
    QString workers_sex;
    QString workers_iphone;
    QString workers_email;
    QString workers_address;
    QString workers_identify;
    QString workers_dates;
    QString workers_state;
    QString workers_remarks;

private slots:
    void on_btn_data_find_clicked();

    void on_btn_update_data_clicked();

    void on_btn_rest_clicked();

    void on_btn_dept_back_clicked();

    void on_btn_page_mainwindow_clicked();

    void on_btn_dept_find_clicked();

    void datainit();

    void on_btn_salary_find_clicked();

    void on_btn_worker_go_find_clicked();

    void on_btn_leave_find_clicked();

    void on_pushButton_12_clicked();

    void on_btn_leave_rest_clicked();

    void on_btn_leave_sure_clicked();

    void on_pushButton_10_clicked();

    void on_btn_leave_look_clicked();

    void on_btn_context_find_clicked();

    void on_pushButton_9_clicked();

    void on_btn_changed_password_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_13_clicked();
    void on_btn_exit_clicked();

signals:
     /* 信号必须有signals关键字来声明
      * 信号没有返回值，但可以有参数
      * 信号就是函数的声明，只需声明，无需定义
      * 使用：emit mySignal();
      * 信号可以重载
     */
    void mySignal1();

private:
    Ui::workerwindow *ui;

    QSqlTableModel *model;
    QSqlTableModel *modelworkers;
    QSqlTableModel *modeldept;
    QSqlTableModel *modelsalary;
    QSqlTableModel *showwork;
    QSqlTableModel *leave;
    QSqlTableModel *notice;

};

#endif // WORKERWINDOW_H
