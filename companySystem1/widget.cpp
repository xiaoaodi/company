#include "widget.h"
#include "ui_widget.h"
#include "mysql.h"
#include "workerwindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextEdit>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setAutoFillBackground(true);
    QPalette pal = this->palette();
    pal.setBrush(backgroundRole(), QPixmap(":/new/prefix1/images/second.jpg"));
    setPalette(pal);

    QIcon icon;
    icon.addFile(QStringLiteral("bitbug_favicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
    this->setWindowIcon(icon);





    this->setWindowTitle("公司员工管理系统");
    adminwindow =new AdminWindow(this);
    workerwin =new workerwindow;
    ui->password->setEchoMode(QLineEdit::Password);//密码方式显示文本
 // connect(adminwindow, SIGNAL(mySignal()), this, SLOT(dealadminwindow()) );
    void (AdminWindow::*funSignal)() = &AdminWindow::mySignal;
    connect(adminwindow, funSignal, this, &Widget::dealadminwindow);


    void (workerwindow::*funSignal1)() = &workerwindow::mySignal1;
    connect(workerwin, funSignal1, this, &Widget::dealadminwindow1);


}

Widget::~Widget()
{

    delete ui;
}


void Widget::on_login_clicked()
{
    if((ui->account->text()=="")||(ui->password->text()==""))
        {
            QMessageBox::information(this,tr("警告"),tr("输入不能为空！"),QMessageBox::Ok);
            return;
        }
    QString admin_account= ui->account->text();
    QString admin_password=ui->password->text();

    if(ui->checkBoxadmin->isChecked())
       {
            QString s=QString("select * from tb_admin"
                      " where admin_name='%1'and admin_password='%2' ").arg(admin_account).arg(admin_password);//数据库存储用户名用username密码用password
            /*if(UName == "admin"&&Pword == "admin")
                QMessageBox::information(NULL, "登陆成功", "登陆成功！！！", QMessageBox::Yes);*/
            //查询数据库如果账号和密码匹配返回真否则返回假
             QSqlQuery query;
             query.exec(s);
            if(query.first())
              {
                QMessageBox::information(NULL, "登陆成功", "登陆成功！！！", QMessageBox::Yes);
//                adminwindow =new AdminWindow(this);
                adminwindow->admin_account=admin_account;
                adminwindow->admin_password=admin_password;
                adminwindow->show();
                this->hide();
              }

             else
                QMessageBox::warning(NULL,"Error","登录失败，请重新输入你的账号密码！！！");
    }
    else
      {
        QString s=QString("select * from tb_workers"
                  " where workers_account='%1'and workers_password='%2' ").arg(admin_account).arg(admin_password);
        QSqlQuery query;
        query.exec(s);
       if(query.first())
       {
           QMessageBox::information(NULL, "登陆成功", "登陆成功！！！", QMessageBox::Yes);
            // workerwin =new workerwindow(this);
             workerwin->workers_account=admin_account;
             workerwin->workers_password=admin_password;
             workerwin ->show();
             this->hide();
       }
        else
           QMessageBox::warning(NULL,"Error","登录失败，请重新输入你的账号密码！！！");
      }

}

void Widget::on_cancel_clicked()
{
    ui->account->clear();
    ui->password->clear();
}

void Widget::on_pushButton_4_clicked()
{
    this->close();
}

void Widget::on_pushButton_3_clicked()//关于系统页面
{
    int width =400;
    int height =250;
    QDialog *p = new QDialog;
    p->setAttribute(Qt::WA_DeleteOnClose);
    p->setWindowTitle("关于员工管理系统");
    p->setMinimumSize(400,250);
    p->setMaximumSize(400,250);

    QLabel *p2=new QLabel(p);
    p2->resize(400,250);

    QImage *img =new QImage;
    img->load(":/new/prefix1/images/lab1 (2).png");
    p2->setPixmap(QPixmap::fromImage(*img).scaled(width,height,Qt::KeepAspectRatio));
    p->show();
}

void Widget::dealadminwindow(){

   adminwindow->hide();
   this->show();
   ui->account->clear();
   ui->password->clear();
}
void Widget::dealadminwindow1(){

   workerwin->hide();
   this->show();
   ui->account->clear();
   ui->password->clear();
}
