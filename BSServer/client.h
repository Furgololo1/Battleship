#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QDebug>

class Client
{

    QTcpSocket* _socket = nullptr;
    QString nick;

public:
    Client();
    Client(QTcpSocket *soc): _socket(soc){
        //_socket->write("?nick?");
    };
    ~Client();

    void SetNick(QString n){nick = n;};
    QTcpSocket *GetSocket(){return _socket;}
    QString GetNick(){return nick;}

private:


};

#endif // CLIENT_H
