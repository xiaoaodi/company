#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
   //初始化管理员模型
    ui->stackedWidget->setCurrentWidget(ui->pagethree);
   adminwindowinit();

}

AdminWindow::~AdminWindow()
{
    delete ui;
}

//1丶管理员模块的代码



void AdminWindow::adminwindowinit(){
    //设置欢迎界面
    ui->stackedWidget->setCurrentWidget(ui->pagethree);
    //设置一个模型
    model =new QSqlTableModel(this);
    model->setTable("tb_admin");//指定使用哪一个表

    //把model放进表中
    ui->tableView->setModel(model);

    //显示model里面的数据
    model->select();

    model->setHeaderData(0,Qt::Horizontal,"管理员编号");
    model->setHeaderData(1,Qt::Horizontal,"登录账号");
    model->setHeaderData(2,Qt::Horizontal,"登陆密码");
    model->setHeaderData(3,Qt::Horizontal,"操作时间");

    //设置model编辑模式,手动ji进行提交修改；
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //设置tableview不允许修改数据库信息；
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
void AdminWindow::on_buttonadd_clicked()//管理员界面的增加按钮
{
    //添加一个空记录
    QSqlRecord record =model->record();//获取一个空记录
    //获取行号
    int row =model->rowCount();
    //在指定的行号插入空记录；
    model->insertRecord(row,record);

}

void AdminWindow::on_buttonsure_clicked()////管理员界面的确认按钮
{

   bool rel= model->submitAll();//提交所有的动作
    if(rel){
    QMessageBox::information(this,tr("确认"),tr("确认当前所有操作！"),QMessageBox::Ok);
    }
}

void AdminWindow::on_buttoncancel_clicked()//管理员界面的取消按钮
{
    ui->lineEdit->clear();
    model->revertAll();//取消所有的动作
    bool rel=model->submitAll();//提交动作
    if(rel){
    QMessageBox::information(this,tr("取消"),tr("取消当前所有操作！"),QMessageBox::Ok);
    }
}

void AdminWindow::on_buttondel_clicked()//管理员界面的删除按钮
{
    //获取选中的模型
    QItemSelectionModel *sModel =ui->tableView->selectionModel();
    //取出模型中的索引
    QModelIndexList list =sModel->selectedRows();
    //删除 选中的行号
    for(int i=0;i<list.size();i++){
        model->removeRow(list.at(i).row());
    }


}


void AdminWindow::on_buttonfind_clicked()//管理员界面的查找按钮
{
    QString name =ui->lineEdit->text();

    if(name=="")
     {
        model->setFilter("");//设置过滤条件为空
        model->select();
     }
    else
    {
         QString str=QString("admin_name='%1'").arg(name);
         model->setFilter(str);
         model->select();
    }
}


void AdminWindow::on_Actionpwdchanged_triggered()////切换到修改密码界面
{
    ui->stackedWidget->setCurrentWidget(ui->pageseconed);
}


void AdminWindow::on_Actionfind_triggered()//切换到管理员用户操作界面
{

    ui->stackedWidget->setCurrentWidget(ui->pagefrist);
}


void AdminWindow::on_buttonpwdcancel_clicked()//修改管理员密码取消按钮
{
    ui->Edit1->setText("");
    ui->Edit2->setText("");
    ui->Edit3->setText("");
}


void AdminWindow::on_buttonpwdsure_clicked()//修改管理员密码确认按钮
{
    if((ui->Edit1->text()=="")||(ui->Edit2->text()==""||ui->Edit3->text()==""))
        {
            QMessageBox::information(this,tr("警告"),tr("输入不能为空！"),QMessageBox::Ok);
            return;
        }

    qDebug()<<admin_account;
    QString password=ui->Edit1->text();
    QString password1=ui->Edit2->text();
    QString password2=ui->Edit3->text();

    if(password!=admin_password){
         QMessageBox::warning(NULL,"Error","你输入的原始密码不正确，请重新输入");
         ui->Edit1->setText("");
         ui->Edit2->setText("");
         ui->Edit3->setText("");
         return;
    }
    else if(password1!=password2){
        QMessageBox::warning(NULL,"Error","你输入的两次密码不一致，请重新输入");
        ui->Edit1->setText("");
        ui->Edit2->setText("");
        ui->Edit3->setText("");
        return;
    }
    QSqlQuery  query;
    QString str=QString("update tb_admin set admin_password='%1' where admin_name='%2'").arg(password1).arg(admin_account);
    qDebug()<<str;
    bool rel=query.exec(str);
    //qDebug()<<rel;
    if(rel)
      {
        QMessageBox::information(NULL, "修改密码"," 修改密码成功，请重新登陆！！！", QMessageBox::Yes);
        emit mySignal();
        ui->Edit1->setText("");
        ui->Edit2->setText("");
        ui->Edit3->setText("");
        ui->stackedWidget->setCurrentWidget(ui->pagethree);
      }
    ui->stackedWidget->setCurrentWidget(ui->pagethree);

}
void AdminWindow::on_btn_revt_admin_clicked() //重置按钮
{
    ui->lineEdit->clear();
}





// 2、员工信息模块




void AdminWindow::on_workers_add_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->pagefour);
}

void AdminWindow::on_pushButton_sure_clicked() //增加员工按钮
{
     workers user;
     workersinit(&user);
     mysql user1;
     bool ret=user1.add_workers(&user);
     if(ret == false)
     {
         QMessageBox::information(this, tr("消息"), tr("添加失败!"), QMessageBox::Ok);

         return;
     }
     QMessageBox::information(this, tr("消息"), tr("添加成功!"), QMessageBox::Ok);
}

void AdminWindow::on_pushButton_changed_clicked()//修改员工按钮
{
    workers user;
    workersinit(&user);
     mysql user1;
     bool ret=user1.update_workers(&user);
     if(ret == false)
     {
         QMessageBox::information(this, tr("消息"), tr("查无此人!"), QMessageBox::Ok);
         return;
     }
     QMessageBox::information(this, tr("消息"), tr("修改成功!"), QMessageBox::Ok);
}

void AdminWindow::workersinit(workers *user)//对员工信息进行初始化
{
    user->workers_id=ui->lineEdit_workers_id->text().toInt();
    user->workers_deptid=ui->lineEdit_workers_dept_id->text().toInt();
    user->workers_name=ui->lineEdit_workers_name->text();
    user->workers_sex=ui->lineEdit_workers_sex->text();
    user->workers_dates=ui->lineEdit_workers_dates->text();
    user->workers_email=ui->lineEdit_workers_email->text();
    user->workers_state=ui->lineEdit_workers_state->text();
    user->workers_iphone=ui->lineEdit_workers_iphone->text();
    user->workers_address=ui->lineEdit_workers_address->text();
    user->workers_remarks=ui->lineEdit_workers_remarks->toPlainText();
    user->workers_identify=ui->lineEdit_workers_identify->text();
    user->workers_password=ui->lineEdit_workers_password->text();
    user->workers_account=ui->lineEdit_workers_account->text();
}

void AdminWindow::on_pushButton_cancel_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagethree);
}

void AdminWindow::on_workers_find_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->pagefive);
    modelworkers =new QSqlTableModel(this);
    modelworkers->setTable("tb_workers");//指定使用哪一个表

    //把model放进表中
    ui->tableView_workers->setModel(modelworkers);

    //显示model里面的数据
    modelworkers->select();

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

    //设置model编辑模式,手动ji进行提交修改；
    modelworkers->setEditStrategy(QSqlTableModel::OnManualSubmit);
}



void AdminWindow::on_pushButton_workers_find_clicked()
{
    QString workers_name = ui->lineEdit_workers_find->text();
    if(workers_name==""){
        modelworkers->setFilter("");//设置过滤条件为空
        modelworkers->select();
        return;
    }
    QString str=QString("workers_name='%1'").arg(workers_name);
    modelworkers->setFilter(str);
    modelworkers->select();

}

void AdminWindow::on_pushButton_2_clicked()
{
    //获取选中的模型
    QItemSelectionModel *sModel =ui->tableView_workers->selectionModel();
    //取出模型中的索引
    QModelIndexList list =sModel->selectedRows();
    //删除 选中的行号
    for(int i=0;i<list.size();i++){
        modelworkers->removeRow(list.at(i).row());
    }
    modelworkers->submitAll();//提交所有的动作
    int rel=1;
    if(rel==1){
        QMessageBox::information(this, tr("删除"), tr("删除成功!"), QMessageBox::Ok);
        modelworkers->setFilter("");//设置过滤条件为空
        modelworkers->select();
    }
    else
    QMessageBox::information(this, tr("删除"), tr("删除失败!"), QMessageBox::Ok);

}

void AdminWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagethree);
}




//3.部门管理模块



void AdminWindow::on_action_add_dept_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->pagesix);
}

void AdminWindow::on_action_operation_dept_triggered()//初始化dept表
{
    ui->stackedWidget->setCurrentWidget(ui->pageseven);
    modeldept =new QSqlTableModel(this);
    modeldept->setTable("tb_dept");//指定使用哪一个表

    //把model放进表中
    ui->tableView_dept->setModel(modeldept);

    //显示model里面的数据
    modeldept->select();

    modeldept->setHeaderData(0,Qt::Horizontal,"部门编号");
    modeldept->setHeaderData(1,Qt::Horizontal,"部门名字");
    modeldept->setHeaderData(2,Qt::Horizontal,"添加时间");
    modeldept->setHeaderData(3,Qt::Horizontal,"操作人");
    modeldept->setHeaderData(4,Qt::Horizontal,"备注");

    //设置model编辑模式,手动ji进行提交修改；
    modeldept->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

void AdminWindow::on_pushButton_clicked()//添加按钮
{
        int dept_id =ui->lineEdit_deptid->text().toUInt();
        QString dept_name=ui->lineEdit_deptname->text();
        QString dept_date=ui->lineEdit_deptdate->text();
        QString dept_user=ui->lineEdit_deptuser->text();
        QString dept_description=ui->textEdit_dept_description->toPlainText();
        if(dept_id==NULL||dept_name==""||dept_user==""||dept_date==""){
             QMessageBox::information(this, tr("添加失败"), tr("输入不能为空，请重新输入！！！!"), QMessageBox::Ok);
        }
       QSqlQuery *query1=new QSqlQuery;
        QString str=QString("insert into tb_dept value('%1','%2','%3','%4','%5')").arg(dept_id).arg(dept_name)
                .arg(dept_date).arg(dept_user).arg(dept_description);
        query1->exec(str);
        int rel=1;
        if(rel==1){
           QMessageBox::information(this, tr("添加成功"), tr("成功添加一个部门！！！!"), QMessageBox::Ok);
        }
        ui->lineEdit_deptid->clear();
        ui->lineEdit_deptname->clear();
        ui->lineEdit_deptdate->clear();
        ui->lineEdit_deptuser->clear();
        ui->textEdit_dept_description->clear();

}

void AdminWindow::on_pushButton_4_clicked()//返回按钮
{
    ui->stackedWidget->setCurrentWidget(ui->pagethree);
}

void AdminWindow::on_pushButton_9_clicked()//返回按钮
{
    ui->stackedWidget->setCurrentWidget(ui->pagethree);

}

void AdminWindow::on_pushButton_dept_find_clicked()//查询按钮
{
    QString dept_name=ui->lineEdit_dept_search->text();
    if(dept_name==""){
        modeldept->setFilter("");//设置过滤条件为空
        modeldept->select();
        return;
    }
    QString str=QString("dept_name='%1'").arg(dept_name);
    modeldept->setFilter(str);
    modeldept->select();

}

void AdminWindow::on_pushButton_dept_clear_clicked()//取消按钮
{
    ui->lineEdit_dept_search->clear();
}

void AdminWindow::on_pushButton_dept_changed_clicked()
{
    modeldept->submitAll();
    int rel=1;
    if(rel==1){
       QMessageBox::information(this, tr("修改成功"), tr("成功修改部门信息！！！!"), QMessageBox::Ok);
    }
}

void AdminWindow::on_pushButton_dept_del_clicked()
{
    //获取选中的模型
    QItemSelectionModel *sModel =ui->tableView_dept->selectionModel();
    //取出模型中的索引
    QModelIndexList list =sModel->selectedRows();
    //删除 选中的行号
    for(int i=0;i<list.size();i++){
        modeldept->removeRow(list.at(i).row());
    }
    modeldept->submitAll();//提交所有的动作
    int rel=1;
    if(rel==1){
       QMessageBox::information(this, tr("删除成功"), tr("成功删除选中的部门信息！！！!"), QMessageBox::Ok);
    }
}

void AdminWindow::on_pushButton_dept_cancel_clicked()
{
    modeldept->revertAll();
    modeldept->submitAll();
    int rel=1;
    if(rel==1){
       QMessageBox::information(this, tr("取消操作成功"), tr("取消操作成功！！！!"), QMessageBox::Ok);
    }

}



//4.薪资管理模块






void AdminWindow::on_action_add_salary_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->pageeight);

}

void AdminWindow::on_action_change_salary_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->pagenine);
    modelsalary =new QSqlTableModel(this);
    modelsalary->setTable("tb_salary");//指定使用哪一个表

    //把model放进表中
    ui->tableView_salary->setModel(modelsalary);

    //显示model里面的数据
    modelsalary->select();

    modelsalary->setHeaderData(0,Qt::Horizontal,"薪资编号");
    modelsalary->setHeaderData(1,Qt::Horizontal,"员工编号");
    modelsalary->setHeaderData(2,Qt::Horizontal,"员工姓名");
    modelsalary->setHeaderData(3,Qt::Horizontal,"工作月份");
    modelsalary->setHeaderData(4,Qt::Horizontal,"月薪");

    //设置model编辑模式,手动ji进行提交修改；
    modelsalary->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

void AdminWindow::on_pushButton_5_clicked() //增加薪资按钮
{
    int salary_id =ui->lineEdit_salary_id->text().toUInt();
    int salary_workersid=ui->lineEdit_salary_workers_id->text().toInt();
    QString salary_workersname=ui->lineEdit_salary_name->text();
    QString salary_month=ui->lineEdit_salary_month->text();
    QString salary_money=ui->lineEdit_salary_money->text();
    if(salary_id==NULL||salary_workersid==NULL||salary_workersname==""||salary_month==""){
         QMessageBox::information(this, tr("添加失败"), tr("输入不能为空，请重新输入！！！!"), QMessageBox::Ok);
    }
   QSqlQuery *query2=new QSqlQuery;
    QString str=QString("insert into tb_salary value('%1','%2','%3','%4','%5')").arg(salary_id).arg(salary_workersid)
            .arg(salary_workersname).arg(salary_month).arg(salary_money);
    query2->exec(str);
    int rel=1;
    if(rel==1){
       QMessageBox::information(this, tr("添加成功"), tr("成功添加一个薪资信息！！！!"), QMessageBox::Ok);
    }
    ui->lineEdit_salary_id->clear();
    ui->lineEdit_salary_workers_id->clear();
    ui->lineEdit_salary_name->clear();
    ui->lineEdit_salary_month->clear();
    ui->lineEdit_salary_money->clear();

}

void AdminWindow::on_pushButton_add_salary_cancel_clicked()//增加员工的取消按钮
{
    ui->lineEdit_salary_id->clear();
    ui->lineEdit_salary_workers_id->clear();
    ui->lineEdit_salary_name->clear();
    ui->lineEdit_salary_month->clear();
    ui->lineEdit_salary_money->clear();
}

void AdminWindow::on_pushButton_find_salary_clicked()//查找按钮
{
    QString salary_name=ui->lineEdit_find_salary->text();
    if(salary_name==""){
        modelsalary->setFilter("");//设置过滤条件为空
        modelsalary->select();
        return;
    }
    QString str=QString("salary_workersname='%1'").arg(salary_name);
    modelsalary->setFilter(str);
    modelsalary->select();
}

void AdminWindow::on_pushButton_find_salary_cancel_clicked()
{
   ui->lineEdit_find_salary->clear();
}

void AdminWindow::on_pushButton_change_salary_clicked()
{
    modelsalary->submitAll();
    int rel=1;
    if(rel==1){
       QMessageBox::information(this, tr("修改成功"), tr("成功修改薪资信息！！！!"), QMessageBox::Ok);
    }
}

void AdminWindow::on_pushButton_del_salary_clicked()
{
    int i=0;
    //获取选中的模型
    QItemSelectionModel *sModel =ui->tableView_salary->selectionModel();
    //取出模型中的索引
    QModelIndexList list =sModel->selectedRows();
    //删除 选中的行号
    for(;i<list.size();i++){
        modelsalary->removeRow(list.at(i).row());
    }
    if(i==0){
        return;
    }
   bool rel= modelsalary->submitAll();//提交所有的动作
    if(rel){
       QMessageBox::information(this, tr("删除成功"), tr("成功删除选中的薪资信息！！！!"), QMessageBox::Ok);
    }
}

void AdminWindow::on_pushButton_cancel_salary_clicked()
{
    modelsalary->revertAll();
    modelsalary->submitAll();
    int rel=1;
    if(rel==1){
       QMessageBox::information(this, tr("取消操作成功"), tr("取消操作成功！！！!"), QMessageBox::Ok);
    }
}

void AdminWindow::on_pushButton_salary_rollbackmian_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagethree);
}



//考勤管理模块


void AdminWindow::on_action_add_showwork_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->pageten);
}

void AdminWindow::on_action_changed_showwork_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->pageshowwork);
    showwork =new QSqlTableModel(this);
    showwork->setTable("tb_showwork");//指定使用哪一个表

    //把model放进表中
    ui->tableView_showwork->setModel(showwork);

    //显示model里面的数据
    showwork->select();

    showwork->setHeaderData(0,Qt::Horizontal,"表编号");
    showwork->setHeaderData(1,Qt::Horizontal,"员工编号");
    showwork->setHeaderData(2,Qt::Horizontal,"员工姓名");
    showwork->setHeaderData(3,Qt::Horizontal,"工作月份");
    showwork->setHeaderData(4,Qt::Horizontal,"工作天数");

    //设置model编辑模式,手动ji进行提交修改；
    showwork->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

void AdminWindow::on_btn_showwork_sure_clicked()
{
    int showwork_id =ui->lineEdit_showwork_id->text().toUInt();
    int showwork_workerid=ui->lineEdit_showwork_workersid->text().toInt();
    QString showwork_workername=ui->lineEdit_showwork_name->text();
    QString showwork_month=ui->lineEdit_showwork_month->text();
    QString showwork_day=ui->lineEdit_showwork_day->text();
    if(showwork_id==NULL||showwork_workerid==NULL||showwork_workername==""||showwork_month==""){
         QMessageBox::information(this, tr("添加失败"), tr("输入不能为空，请重新输入！！！!"), QMessageBox::Ok);
    }
   QSqlQuery *query3=new QSqlQuery;
    QString str=QString("insert into tb_showwork value('%1','%2','%3','%4','%5')").arg(showwork_id).arg(showwork_workerid)
            .arg(showwork_workername).arg(showwork_month).arg(showwork_day);
    bool rel =query3->exec(str);
    if(rel){
       QMessageBox::information(this, tr("添加成功"), tr("成功添加一个出勤信息！！！!"), QMessageBox::Ok);
    }
    ui->lineEdit_showwork_id->clear();
    ui->lineEdit_showwork_workersid->clear();
    ui->lineEdit_showwork_name->clear();
    ui->lineEdit_showwork_month->clear();
    ui->lineEdit_showwork_day->clear();
}

void AdminWindow::on_btn_showwork_cancel_clicked()
{
    ui->lineEdit_showwork_id->clear();
    ui->lineEdit_showwork_workersid->clear();
    ui->lineEdit_showwork_name->clear();
    ui->lineEdit_showwork_month->clear();
    ui->lineEdit_showwork_day->clear();
}



void AdminWindow::on_btn_showwork_back_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagethree);
}

void AdminWindow::on_btn_showwork_changed_clicked()
{
    bool rel=showwork->submitAll();
    if(rel){
       QMessageBox::information(this, tr("修改成功"), tr("成功修改出勤信息！！！!"), QMessageBox::Ok);
    }
}


void AdminWindow::on_btn_showwork_del_clicked()
{
    int i=0;
    //获取选中的模型
    QItemSelectionModel *sModel =ui->tableView_showwork->selectionModel();
    //取出模型中的索引
    QModelIndexList list =sModel->selectedRows();
    //删除 选中的行号
    for(;i<list.size();i++){
        showwork->removeRow(list.at(i).row());
    }
    if(i==0){
        return;
    }
   bool rel= showwork->submitAll();//提交所有的动作
    if(rel){
       QMessageBox::information(this, tr("删除成功"), tr("成功删除选中的出勤信息！！！!"), QMessageBox::Ok);
    }
}

void AdminWindow::on_btn_showwork_find_clicked()
{
    QString showwork_name=ui->lineEdit_showwork_find->text();
    if(showwork_name==""){
        showwork->setFilter("");//设置过滤条件为空
        showwork->select();
        return;
    }
    QString str=QString("showwork_workername='%1'").arg(showwork_name);
    showwork->setFilter(str);
    showwork->select();

}

void AdminWindow::on_btn_showwork_find_cancel_clicked()
{
    ui->lineEdit_showwork_find->clear();
}

void AdminWindow::on_btn_showwork_back2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagethree);
}

void AdminWindow::on_btn_showwork_cancel_2_clicked()//取消操作按钮
{
  showwork->revertAll();
  bool rel=showwork->submitAll();
  if(rel){
     QMessageBox::information(this, tr("取消成功"), tr("成功取消操作！！！!"), QMessageBox::Ok);
  }
}



//请假管理模块


void AdminWindow::on_action_changed_date_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->pageday_1);
    leave =new QSqlTableModel(this);
    leave->setTable("tb_leave");//指定使用哪一个表

    //把model放进表中
    ui->tableView_leave->setModel(leave);

    //显示model里面的数据
    leave->select();

    leave->setHeaderData(0,Qt::Horizontal,"请假编号");
    leave->setHeaderData(1,Qt::Horizontal,"员工姓名");
    leave->setHeaderData(2,Qt::Horizontal,"开始时间");
    leave->setHeaderData(3,Qt::Horizontal,"结束时间");
    leave->setHeaderData(4,Qt::Horizontal,"请假理由");
    leave->setHeaderData(5,Qt::Horizontal,"审核状态");

    //设置model编辑模式,手动ji进行提交修改；
    leave->setEditStrategy(QSqlTableModel::OnManualSubmit);
}


void AdminWindow::on_pushButton_24_clicked()
{
    bool rel=leave->submitAll();
    if(rel){
       QMessageBox::information(this, tr("操作成功"), tr("操作成功！！！!"), QMessageBox::Ok);
    }
}

void AdminWindow::on_pushButton_25_clicked()
{
    leave->revertAll();//取消所有的动作
    leave->submitAll();//提交动作
}

void AdminWindow::on_btn_leave_find_clicked()
{
    QString name=ui->lineEdit_leave_find->text();
    if(name==""){
        leave->setFilter("");//设置过滤条件为空
        leave->select();
        return;
    }
    QString str=QString("leave_workername='%1'").arg(name);
    leave->setFilter(str);
    leave->select();
}

void AdminWindow::on_btn_leave_find_cancel_clicked()
{
    ui->lineEdit_leave_find->clear();
}

void AdminWindow::on_pushButton_28_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagethree);
}

void AdminWindow::on_action_add_adv_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->pageadv);
}

void AdminWindow::on_action_changed_adv_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->pageadv_1);
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

void AdminWindow::on_pushButton_6_clicked()
{
     int notice_id =ui->lineEdit_adv_id->text().toInt();
     QString notice_date =ui->lineEdit_adv_date->text();
     QString notice_content =ui->textEdit_adv_content->toPlainText();
     if(notice_id==NULL||notice_date==NULL||notice_content==""){
          QMessageBox::information(this, tr("添加失败"), tr("输入不能为空，请重新输入！！！!"), QMessageBox::Ok);
     }
    QSqlQuery *query3=new QSqlQuery;
     QString str=QString("insert into tb_notice value('%1','%2','%3')").arg(notice_id).arg(notice_date)
             .arg(notice_content);
     bool rel =query3->exec(str);
     if(rel){
        QMessageBox::information(this, tr("添加成功"), tr("成功添加一个公告信息！！！!"), QMessageBox::Ok);
     }
}

void AdminWindow::on_pushButton_adv_changed_clicked()
{
    notice->submitAll();
}

void AdminWindow::on_pushButton_adv_del_clicked()
{
    int i=0;
    //获取选中的模型
    QItemSelectionModel *sModel =ui->tableView_2->selectionModel();
    //取出模型中的索引
    QModelIndexList list =sModel->selectedRows();
    //删除 选中的行号
    for(;i<list.size();i++){
        notice->removeRow(list.at(i).row());
    }
    if(i==0){
        return;
    }
   bool rel= notice->submitAll();//提交所有的动作
    if(rel){
       QMessageBox::information(this, tr("删除成功"), tr("成功删除选中的出勤信息！！！!"), QMessageBox::Ok);
    }
}

void AdminWindow::on_pushButton_adv_rest_clicked()
{
    notice->revertAll();
    notice->submitAll();
}

void AdminWindow::on_pushButton_14_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagethree);
}

void AdminWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pagethree);
}

void AdminWindow::on_pushButton_11_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->pagethree);
}

//返回主页面

void AdminWindow::on_actionzhu_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->pagethree);
}




//void AdminWindow::on_actiontuichuxitong_triggered()
//{
//    emit mySignal();
//}

void AdminWindow::on_sys_exit_clicked()
{
    emit mySignal();
    //qDebug()<<"sdadsda";

}

void AdminWindow::on_actiontuichuxitong_triggered()
{
    emit mySignal();
    qDebug()<<"sdadsda";
}

