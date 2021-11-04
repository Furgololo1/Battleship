#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QTcpSocket>


class NetworkClient
{
public:
    NetworkClient();


public slots:
    void onReadyRead();

private:

     QTcpSocket  *_socket = nullptr;

};

#endif // NETWORKCLIENT_H
