#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H


#include <QTcpSocket>
#include <QHostAddress>
#include <QTextEdit>
#include <QListWidget>
#include <QStackedWidget>

#include "types.cpp"


class NetworkClient : public QObject
{
     Q_OBJECT


    //server ip. localhost is basic
    QString server_ip = "127.0.0.1";

    QString nick = "You";

    UiMembers* uimem = nullptr;

    QTcpSocket* socket = nullptr;

    QString enemynick = "Enemy";

    bool bEnd = false;


public:
    NetworkClient(){};
    NetworkClient(QTcpSocket* s, UiMembers *um): socket(s), uimem(um){};


    template<typename Function>
    void ConnectWithServer(QString ip, QString n, Function func);
    void SendToServer(QString);
    void AcceptInvite();
    void DiscardInvite();
    void Shoot(QString shot, Button *button);

    //QList<QString>

signals:

    void onUrTurn();
    void onNotUrTurn();
    void onRemoveShip(QString shiptoremove);
    void DestroyShip(QString ship);
    void DestroyEnemyShip(QString ship);
    void StartGame();
    void Reset();


private slots:
    void onReadyRead();


private:

    void InterpretCommand(QString com);
    void CutCommand(QString com);
   // void StartGame();
    void EndGame();


};


template<typename Function>
void NetworkClient::ConnectWithServer(QString ip, QString n, Function func)
{

    server_ip = ip;
    nick = n;

     socket->connectToHost(QHostAddress(server_ip), 9999);
     //_socket->write(QByteArray::fromStdString("?nick? "+nick.toStdString()));

     if(socket->state() == QAbstractSocket::ConnectingState){
         connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
         func();
     }

     uimem->you_lbl->setText(nick);

}


#endif // NETWORKCLIENT_H
