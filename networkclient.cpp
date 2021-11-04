#include "networkclient.h"

#include <QDebug>
#include <QHostAddress>

NetworkClient::NetworkClient()
{

}



void NetworkClient::onReadyRead()
{
    QByteArray datas = _socket->readAll();
    qDebug() << datas;
   // _socket->write(QByteArray("ok !\n"));
}
