#include "workerwindow.h"
#include "ui_workerwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>

workerwindow::workerwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::workerwindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->pageeight);
    datainit();

    setAutoFillBackground(true);
           QPalette pal = this->palette();
           pal.setBrush(backgroundRole(), QPixmap(":/new/prefix1/images/first.jpg"));
           setPalette(pal);

}

workerwindow::~workerwindow()
{
    delete ui;

}



void workerwindow::datainit(){

}

//1.员工信息的查看



void workerwindow::on_btn_data_find_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagetwo);


    //ui->stackedWidget->setCurrentWidget(ui->pagefive);
    modelworkers =new QSqlTableModel(this);
    modelworkers->setTable("tb_workers");//指定使用哪一个表

    //把model放进表中
    ui->tableView_data->setModel(modelworkers);

    modelworkers->setHeaderData(0,Qt::Horizontal,"员工编号");
    modelworkers->setHeaderData(1,Qt::Horizontal,"部门编号");
    modelworkers->setHeaderData(2,Qt::Horizontal,"账号");
    modelworkers->setHeaderData(3,Qt::Horizontal,"密码");
    modelworkers->setHeaderData(4,Qt::Horizontal,"姓名");
    modelworkers->setHeaderData(5,Qt::Horizontal,"性别");
    modelworkers->setHeaderData(6,Qt::Horizontal,"电话");
    modelworkers->setHeaderData(7,Qt::Horizontal,"邮件");
    modelworkers->setHeaderData(8,Qt::Horizontal,"地址");
    modelworkers->setHeaderData(9,Qt::Horizontal,"身份证");
    modelworkers->setHeaderData(10,Qt::Horizontal,"入职日期");
    modelworkers->setHeaderData(11,Qt::Horizontal,"婚况");
    modelworkers->setHeaderData(12,Qt::Horizontal,"备注");
    QString str=QString("workers_account='%1'").arg(workers_account);
    modelworkers->setFilter(str);
    modelworkers->select();
    workers_deptid = modelworkers->record(0).value("workers_deptid").toInt();
//    qDebug()<<workers_deptid;
   workers_name = modelworkers->record(0).value("workers_name").toString();
//    qDebug()<<workers_name;


    //设置model编辑模式,手动ji进行提交修改；
    modelworkers->setEditStrategy(QSqlTableModel::OnManualSubmit);

}

void workerwindow::on_btn_update_data_clicked()
{
    modelworkers->submitAll();
}



void workerwindow::on_btn_rest_clicked()
{
    modelworkers->revertAll();
    modelworkers->submitAll();
}


void workerwindow::on_btn_page_mainwindow_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->pageeight);
}


//2.部门信息



void workerwindow::on_btn_dept_back_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageeight);
}

void workerwindow::on_btn_dept_find_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagethree);
    modeldept =new QSqlTableModel(this);
    modeldept->setTable("tb_dept");//指定使用哪一个表

    //把model放进表中
    ui->tableView_dept->setModel(modeldept);

    modeldept->setHeaderData(0,Qt::Horizontal,"部门编号");
    modeldept->setHeaderData(1,Qt::Horizontal,"部门名字");
    modeldept->setHeaderData(2,Qt::Horizontal,"添加时间");
    modeldept->setHeaderData(3,Qt::Horizontal,"操作人");
    modeldept->setHeaderData(4,Qt::Horizontal,"备注");

    //设置model编辑模式,手动ji进行提交修改；
    modeldept->setEditStrategy(QSqlTableModel::OnManualSubmit);
    qDebug()<<workers_deptid;
    QString str=QString("dept_id='%1'").arg(workers_deptid);

    modeldept->setFilter(str);
    modeldept->select();
}

//薪资管理


void workerwindow::on_btn_salary_find_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagefour);
    modelsalary =new QSqlTableModel(this);
    modelsalary->setTable("tb_salary");//指定使用哪一个表

    //把model放进表中
    ui->tableView_salary->setModel(modelsalary);


    modelsalary->setHeaderData(0,Qt::Horizontal,"薪资编号");
    modelsalary->setHeaderData(1,Qt::Horizontal,"员工编号");
    modelsalary->setHeaderData(2,Qt::Horizontal,"员工姓名");
    modelsalary->setHeaderData(3,Qt::Horizontal,"工作月份");
    modelsalary->setHeaderData(4,Qt::Horizontal,"月薪");

    //设置model编辑模式,手动ji进行提交修改；
    modelsalary->setEditStrategy(QSqlTableModel::OnManualSubmit);
    QString str=QString("salary_workersname='%1'").arg(workers_name);
    modelsalary->setFilter(str);
    modelsalary->select();

}




//出勤管理
void workerwindow::on_btn_worker_go_find_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagefive);
    showwork =new QSqlTableModel(this);
    showwork->setTable("tb_showwork");//指定使用哪一个表

    //把model放进表中
    ui->tableView->setModel(showwork);


    showwork->setHeaderData(0,Qt::Horizontal,"表编号");
    showwork->setHeaderData(1,Qt::Horizontal,"员工编号");
    showwork->setHeaderData(2,Qt::Horizontal,"员工姓名");
    showwork->setHeaderData(3,Qt::Horizontal,"工作月份");
    showwork->setHeaderData(4,Qt::Horizontal,"工作天数");

    //设置model编辑模式,手动ji进行提交修改；
    showwork->setEditStrategy(QSqlTableModel::OnManualSubmit);
    QString str=QString("showwork_workername='%1'").arg(workers_name);
    showwork->setFilter(str);
    showwork->select();

}

void workerwindow::on_btn_leave_find_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagesix);
}

void workerwindow::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageeight);
}

void workerwindow::on_btn_leave_rest_clicked()
{
    ui->leave_id->clear();
    ui->leave_endday->clear();
    ui->leave_beginday->clear();
    ui->leave_workername->clear();
    ui->leave_description->clear();
}

void workerwindow::on_btn_leave_sure_clicked()
{
    int leave_id = ui->leave_id->text().toInt();
    QString leave_workername= ui->leave_workername->text();
    QString leave_beginday= ui->leave_beginday->text();
    QString leave_endday= ui->leave_endday->text();
    QString leave_description= ui->leave_description->toPlainText();

    if(leave_id==0||leave_workername==""||leave_beginday==""||leave_endday==""){
         QMessageBox::information(this, tr("添加失败"), tr("输入不能为空，请重新输入！！！!"), QMessageBox::Ok);
    }
   QSqlQuery *query1=new QSqlQuery;
    QString str=QString("insert into tb_leave value('%1','%2','%3','%4','%5')").arg(leave_id).arg(leave_workername)
            .arg(leave_beginday).arg(leave_endday).arg(leave_description);
    query1->exec(str);
    int rel=1;
    if(rel==1){
       QMessageBox::information(this, tr("添加成功"), tr("提交成功！！！!"), QMessageBox::Ok);
    }
}

void workerwindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageeight);

}

void workerwindow::on_btn_leave_look_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagesenven);
    leave =new QSqlTableModel(this);
    leave->setTable("tb_leave");//指定使用哪一个表

    //把model放进表中
    ui->tableView_2->setModel(leave);


    leave->setHeaderData(0,Qt::Horizontal,"请假编号");
    leave->setHeaderData(1,Qt::Horizontal,"员工姓名");
    leave->setHeaderData(2,Qt::Horizontal,"开始时间");
    leave->setHeaderData(3,Qt::Horizontal,"结束时间");
    leave->setHeaderData(4,Qt::Horizontal,"请假理由");
    leave->setHeaderData(5,Qt::Horizontal,"审核状态");

    //设置model编辑模式,手动ji进行提交修改；
    leave->setEditStrategy(QSqlTableModel::OnManualSubmit);
    QString str=QString("leave_workername='%1'").arg(workers_name);
    leave->setFilter(str);
    leave->select();
}

void workerwindow::on_btn_context_find_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagesenven);
    notice =new QSqlTableModel(this);
    notice->setTable("tb_notice");//指定使用哪一个表

    //把model放进表中
    ui->tableView_2->setModel(notice);

    //显示model里面的数据
    notice->select();

    notice->setHeaderData(0,Qt::Horizontal,"公告编号");
    notice->setHeaderData(1,Qt::Horizontal,"公告时间");
    notice->setHeaderData(2,Qt::Horizontal,"公告内容");

    //设置model编辑模式,手动ji进行提交修改；
    notice->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

void workerwindow::on_pushButton_9_clicked()
{
    if((ui->password->text()=="")||(ui->password_1->text()==""||ui->password_2->text()==""))
            {
                QMessageBox::information(this,tr("警告"),tr("输入不能为空！"),QMessageBox::Ok);
                return;
            }
       //qDebug()<<adminaccount;
        QString password=ui->password->text();
        QString password1=ui->password_1->text();
        QString password2=ui->password_2->text();

        if(password!=workers_password){
             QMessageBox::warning(NULL,"Error","你输入的原始密码不正确，请重新输入");
        }
        if(password1!=password2){
            QMessageBox::warning(NULL,"Error","你输入的两次密码不一致，请重新输入");
            return;
        }
        QSqlQuery  query;
        QString str=QString("update tb_workers set workers_password='%1' where workers_account='%2'").arg(password1).arg(workers_account);
        query.exec(str);
        int sel=1;
        if(sel==1)
          {
            QMessageBox::information(NULL, "修改密码"," 修改密码成功！！！", QMessageBox::Yes);
           }
        ui->password->setText("");
        ui->password_1->setText("");
        ui->password_2->setText("");
}

void workerwindow::on_btn_changed_password_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagepwd);

}

void workerwindow::on_pushButton_11_clicked()
{
    ui->password->setText("");
    ui->password_1->setText("");
    ui->password_2->setText("");
}

void workerwindow::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageeight);
}

void workerwindow::on_btn_exit_clicked()
{
    emit mySignal1();
   // qDebug()<<"sdadsda";
}
