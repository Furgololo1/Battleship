
#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

#include "client.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

public slots:
    //void onNewConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onReadyRead();


private slots:

    void onNewConnection();

    void on_pushButton_clicked();

private:

   // QString GetNick(QTcpSocket* s);

    void CheckCommand(QString command, Client* c);


    Ui::Server *ui;
    QTcpServer *_server = nullptr;
    QList<QTcpSocket*>  _sockets;
    QList<QString> _nicks;

    QList<Client *> clients;

    QVector<QString> text;

};
#endif // SERVER_H

