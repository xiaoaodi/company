#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

private slots:
    void on_startServer_clicked();

    void on_send_clicked();

private:
    Ui::Server *ui;
    QTcpServer* m_server;
    QTcpSocket* m_tcp;
};
#endif // SERVER_H
