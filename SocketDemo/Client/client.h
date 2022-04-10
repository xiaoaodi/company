#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void on_connect_clicked();

    void on_disconnect_clicked();

    void on_send_clicked();

    void on_connectServer_clicked();

private:
    Ui::Client *ui;
    QTcpSocket *m_tcp;
};
#endif // CLIENT_H
