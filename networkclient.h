#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QTextEdit>


class NetworkClient : public QObject
{
     Q_OBJECT


    //server ip. localhost is basic
    QString server_ip = "127.0.0.1";

    QString nick = "Player";

    QTcpSocket* _socket = nullptr;

    QTextEdit* chat = nullptr;


public:
    NetworkClient(){};
    NetworkClient(QTcpSocket* _s, QTextEdit *c): _socket(_s){}, chat(c);


    void ConnectWithServer(QString ip, QString n);
    void SendToChat(QString);

private slots:
    void onReadyRead();

private:

    void CheckCommand(QString com);



};

#endif // NETWORKCLIENT_H
