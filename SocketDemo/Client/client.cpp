#include "client.h"
#include "ui_client.h"

#include <QtNetwork/QTcpSocket>

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    setWindowTitle("TCP - 客户端");

    ui->port->setText("10000");
    ui->ip->setText("127.0.0.1");
    // 创建通信的套接字对象
    m_tcp = new QTcpSocket(this);
    // 检测服务器是否回复了数据
    connect(m_tcp, &QTcpSocket::readyRead, [=]()
    {
        // 接收服务器发送的数据
        QByteArray recvMsg = m_tcp->readAll();
        ui->record->append("服务器Say: " + recvMsg);
    });

    // 检测是否和服务器是否连接成功了
    connect(m_tcp, &QTcpSocket::connected, this, [=]()
    {
        ui->record->append("恭喜, 连接服务器成功!!!");
        //m_status->setPixmap(QPixmap(":/connect.png").scaled(20, 20));
    });

    // 检测服务器是否和客户端断开了连接
    connect(m_tcp, &QTcpSocket::disconnected, this, [=]()
    {
        ui->record->append("服务器已经断开了连接, ...");
        ui->connectServer->setEnabled(true);
        ui->disconnect->setEnabled(false);
    });

}

Client::~Client()
{
    delete ui;
}


void Client::on_connect_clicked()
{



}

void Client::on_disconnect_clicked()
{
    m_tcp->close();
    ui->connectServer->setEnabled(true);
    ui->disconnect->setEnabled(false);
}

void Client::on_send_clicked()
{
    QString sendMsg = ui->msg->toPlainText();
    m_tcp->write(sendMsg.toUtf8());
    ui->record->append("客户端Say: " + sendMsg);
    ui->msg->clear();
}

void Client::on_connectServer_clicked()
{
    QString ip = ui->ip->text();
    unsigned short port = ui->port->text().toInt();
    // 连接服务器
    m_tcp->connectToHost(QHostAddress(ip), port);
    ui->connectServer->setEnabled(false);
    ui->disconnect->setEnabled(true);
}
