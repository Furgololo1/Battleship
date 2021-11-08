#include "networkclient.h"

#include <QDebug>
#include <QHostAddress>
#include <QTcpSocket>




void NetworkClient::ConnectWithServer(QString ip, QString n)
{

 server_ip = ip;
 nick = n;

     _socket->connectToHost(QHostAddress(server_ip), 9999);
     //_socket->write(QByteArray::fromStdString("?nick? "+nick.toStdString()));
     connect(_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

}


void NetworkClient::SendToChat(QString text){
    _socket->write(QByteArray::fromStdString("!chat! " + text.toStdString()));
}


void NetworkClient::onReadyRead()
{
    QByteArray command = _socket->readAll();
        qDebug()<<command;
        CheckCommand(command);
        // _socket->write(QByteArray("ok !\n"));
}

void NetworkClient::CheckCommand(QString com)
{
    if(com.contains("?nick?", Qt::CaseSensitive))
        _socket->write(QByteArray::fromStdString("?nick? " + nick.toStdString()));


}
