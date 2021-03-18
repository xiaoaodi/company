#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQuery>
#include "mysql.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

    void adminwindowinit();
    void workersinit(workers *user);


    //数据
    QString admin_account;
    QString admin_password;


private slots:
    void on_buttonadd_clicked();

    void on_buttonsure_clicked();

    void on_buttoncancel_clicked();

    void on_buttondel_clicked();

    void on_buttonfind_clicked();

    void on_Actionpwdchanged_triggered();

    void on_Actionfind_triggered();

    void on_buttonpwdcancel_clicked();

    void on_buttonpwdsure_clicked();

    void on_workers_add_triggered();

    void on_pushButton_sure_clicked();

    void on_pushButton_changed_clicked();

    void on_pushButton_cancel_clicked();

    void on_workers_find_triggered();


    void on_pushButton_workers_find_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_action_add_dept_triggered();

    void on_action_operation_dept_triggered();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_dept_find_clicked();

    void on_pushButton_dept_clear_clicked();

    void on_pushButton_dept_changed_clicked();

    void on_pushButton_dept_del_clicked();

    void on_pushButton_dept_cancel_clicked();



    void on_action_add_salary_triggered();

    void on_action_change_salary_triggered();

    void on_action_add_showwork_triggered();

    void on_action_changed_showwork_triggered();

    void on_action_changed_date_triggered();

    void on_pushButton_5_clicked();

    void on_pushButton_add_salary_cancel_clicked();


    void on_pushButton_find_salary_clicked();

    void on_pushButton_find_salary_cancel_clicked();

    void on_pushButton_change_salary_clicked();

    void on_pushButton_del_salary_clicked();

    void on_pushButton_cancel_salary_clicked();

    void on_pushButton_salary_rollbackmian_clicked();

    void on_btn_showwork_sure_clicked();

    void on_btn_showwork_cancel_clicked();

    void on_btn_showwork_back_clicked();

    void on_btn_showwork_changed_clicked();

    void on_btn_showwork_del_clicked();

    void on_btn_showwork_find_clicked();

    void on_btn_showwork_find_cancel_clicked();

    void on_btn_showwork_back2_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_btn_leave_find_clicked();

    void on_btn_leave_find_cancel_clicked();

    void on_pushButton_28_clicked();

    void on_action_add_adv_triggered();

    void on_action_changed_adv_triggered();

    void on_pushButton_6_clicked();

    void on_pushButton_adv_changed_clicked();

    void on_pushButton_adv_del_clicked();

    void on_pushButton_adv_rest_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_btn_revt_admin_clicked();

    void on_actionzhu_triggered();

    void on_sys_exit_clicked();

    void on_actiontuichuxitong_triggered();

    void on_btn_showwork_cancel_2_clicked();

signals:
     /* 信号必须有signals关键字来声明
      * 信号没有返回值，但可以有参数
      * 信号就是函数的声明，只需声明，无需定义
      * 使用：emit mySignal();
      * 信号可以重载
     */
    void mySignal();


private:
    Ui::AdminWindow *ui;

     QSqlTableModel *model;
     QSqlTableModel *modelworkers;
     QSqlTableModel *modeldept;
     QSqlTableModel *modelsalary;
     QSqlTableModel *showwork;
     QSqlTableModel *leave;
     QSqlTableModel *notice;
};

#endif // ADMINWINDOW_H
