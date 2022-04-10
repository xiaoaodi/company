#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    this->setWindowTitle("服务器");
    ui->port->setText("10000");
    // 创建 QTcpServer 对象
       m_server = new QTcpServer(this);
       // 检测是否有新的客户端连接
       connect(m_server, &QTcpServer::newConnection, this, [=]()
       {
           m_tcp = m_server->nextPendingConnection();
           ui->record->append("成功和客户端建立了新的连接...");
           //m_status->setPixmap(QPixmap(":/connect.png").scaled(20, 20));
           // 检测是否有客户端数据
           connect(m_tcp, &QTcpSocket::readyRead, this, [=]()
           {
               // 接收数据
               QString recvMsg = m_tcp->readAll();
               ui->record->append("客户端Say: " + recvMsg);
           });
           // 客户端断开了连接
           connect(m_tcp, &QTcpSocket::disconnected, this, [=]()
           {
               ui->record->append("客户端已经断开了连接...");
               m_tcp->deleteLater();
              // m_status->setPixmap(QPixmap(":/disconnect.png").scaled(20, 20));
           });
       });

}

Server::~Server()
{
    delete ui;
}

// 启动服务器端的服务按钮
void Server::on_startServer_clicked()
{
    unsigned short port = ui->port->text().toInt();
    // 设置服务器监听
    m_server->listen(QHostAddress::Any, port);
    ui->startServer->setEnabled(false);
}

void Server::on_send_clicked()
{
    QString sendMsg = ui->msg->toPlainText();
      m_tcp->write(sendMsg.toUtf8());
      ui->record->append("服务器Say: " + sendMsg);
      ui->msg->clear();
}
