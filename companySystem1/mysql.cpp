#include "mysql.h"

mysql::mysql()
{


}


void mysql::initsql(){
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPort(3310);
    db.setPassword("123456");
    db.setDatabaseName("com");
    if(db.open())
        {
            qDebug()<<"Database connected successfully!";
            createtable();
            return;
        }
    else
        {
            qDebug()<<"Database connected failed!";
            return;
        }
        createtable();
}



void mysql::createtable(){
    query=new QSqlQuery;
    //创建管理员表
    query->exec("create table tb_admin(admin_id int auto_increment PRIMARY KEY NOT NULL,"
                "admin_name VARCHAR(30) UNIQUE NOT NULL, "
                "admin_password VARCHAR(30) NOT NULL,"
                "admin_dates date)");
    //创建员工表
    query->exec("create table tb_workers("
               "workers_id int PRIMARY KEY NOT NULL,"
               "workers_deptid int,"
               "workers_account varchar(30),"
               "workers_password varchar(30),"
               "workers_name varchar(30),"
               "workers_sex varchar(20),"
               "workers_iphone varchar(30),"
               "workers_email varchar(30),"
               "workers_address varchar(30),"
               "workers_identify varchar(30),"
               "workers_dates varchar(30),"
               "workers_state varchar(20),"
               "workers_remarks varchar(200))");
    //创建部门表
    query->exec("create table tb_dept("
               "dept_id int PRIMARY KEY NOT NULL,"
               "dept_name varchar(30),"
               "dept_date varchar(30),"
               "dept_user varchar(30),"
               "dept_description varchar(20))");
    //创建出勤信息表
    query->exec("create table tb_showwork("
               "showwork_id int PRIMARY KEY NOT NULL,"
               "showwork_workerid int,"
               "showwork_workername varchar(30),"
               "showwork_month varchar(30),"
               "showwork_day varchar(20))");

    //创建请假信息表
    query->exec("create table tb_leave("
               "leave_id int PRIMARY KEY NOT NULL,"
               "leave_workername varchar(30),"
               "leave_beginday varchar(30),"
               "leave_endday varchar(20),"
                "leave_description varchar(500),"
               "leave_state varchar(20))");
    //创建薪资表
    query->exec("create table tb_salary("
               "salary_id int PRIMARY KEY NOT NULL,"
               "salary_workersid int,"
               "salary_workersname varchar(30),"
               "salary_month varchar(30),"
               "salary_money varchar(20))");

    //创建公告表
    query->exec("create table tb_notice("
               "notice_id int PRIMARY KEY NOT NULL,"
               "notice_date varchar(300),"
               "notice_content varchar(300))");

    query->exec("insert into tb_admin values(NULL,'root','root','1999-11-12')");


}


bool mysql::add_workers(workers *worker){
    query=new QSqlQuery;
    QString str=QString("insert into tb_workers value('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13')").arg(worker->workers_id)
            .arg(worker->workers_deptid).arg(worker->workers_account).arg(worker->workers_password).arg(worker->workers_name)
            .arg(worker->workers_sex).arg(worker->workers_iphone).arg(worker->workers_email)
            .arg(worker->workers_address).arg(worker->workers_identify).arg(worker->workers_dates).arg(worker->workers_state).arg(worker->workers_remarks);
    bool ret=query->exec(str);
    return ret;

}


bool mysql::update_workers(workers *worker){
    query=new QSqlQuery;
    QString str=QString("select *from tb_workers where stuaccount=%1").arg(worker->workers_id);
    query->exec(str);
    query->last();
    int record = query->at() + 1;
    if(record==0)
        return false;
    str=QString("update into set workers_id = '%1', workers_deptid = '%2', "
                        "workers_account = %3, workers_password = '%4', workers_name = '%5', "
                        "workers_sex = '%6', workers_iphone = '%7', workers_email = '%8',"
                        " workers_address = '%9', workers_identify = '%10', workers_dates = %11, workers_remarks = '%12', stusex = '%13' where stuaccount = '%14'").arg(worker->workers_id)
            .arg(worker->workers_deptid).arg(worker->workers_account).arg(worker->workers_password).arg(worker->workers_name)
            .arg(worker->workers_sex).arg(worker->workers_iphone).arg(worker->workers_email)
            .arg(worker->workers_address).arg(worker->workers_identify).arg(worker->workers_dates).arg(worker->workers_state).arg(worker->workers_remarks).arg(worker->workers_id);
    qDebug()<<str;
    bool ret = query->exec(str);
    return ret;

}
