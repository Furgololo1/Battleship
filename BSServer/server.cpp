#include "server.h"
#include "ui_server.h"



Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    _server = new QTcpServer(this);
    _server->listen(QHostAddress::Any, 9999);
    connect(_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}


Server::~Server()
{
    delete ui;
}


void Server::onNewConnection()
{
   QTcpSocket *clientSocket = _server->nextPendingConnection();
   connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
   connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    _sockets.push_back(clientSocket);
    //_nicks->
    clients.push_back(new Client(clientSocket));
    clientSocket->write("?nick?");


}


void Server::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        _sockets.removeOne(sender);
    }
}


void Server::onReadyRead()
{

    for(const auto &c : clients){
            CheckCommand(c->GetSocket()->readAll(), c);
    }

}


void Server::CheckCommand(QString command, Client* c)
{
    qDebug()<<command;

    if(command.contains("?nick?",Qt::CaseSensitive))
        c->SetNick(command.remove("?nick? ",Qt::CaseSensitive));


    else if(command.contains("!chat!",Qt::CaseSensitive)){

                ui->textEdit->append(c->GetNick() + ": " + command.remove("!chat! ", Qt::CaseInsensitive));

        text.clear();

    }

    c->GetSocket()->reset();

}


void Server::on_pushButton_clicked()
{
    for(const auto &c : clients)
        qDebug()<<c->GetNick();

}
