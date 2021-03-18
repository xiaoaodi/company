#ifndef MYSQL_H
#define MYSQL_H

#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>

typedef struct workers
{
    int workers_id;
    int workers_deptid;
    QString workers_account;
    QString workers_password;
    QString workers_name;
    QString workers_sex;
    QString workers_iphone;
    QString workers_email;
    QString workers_address;
    QString workers_identify;
    QString workers_dates;
    QString workers_state;
    QString workers_remarks;

}workers;

class mysql
{
public:
    mysql();  //数据库构造函数
    void initsql(); //连接数据库
    void createtable();//创建所有的表
    bool add_workers(workers *worker);
    bool update_workers(workers *worker);


private:
    QSqlQuery *query;
};

#endif // MYSQL_H
