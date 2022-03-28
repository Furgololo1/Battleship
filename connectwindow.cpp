#include "connectwindow.h"


void ConnectWindow::ConnectedSuccesfull()
{
    delete teip;
    delete tenick;
    delete btnconn;
    delete labels->at(3);
    delete labels->at(2);
    delete labels->at(1);
}


void ConnectWindow::onConnbtn()
{
    nc->ConnectWithServer(teip->text(), tenick->text(), std::bind(&ConnectWindow::ConnectedSuccesfull, this));
}


void ConnectWindow::CreateGUI()
{

    teip = new QLineEdit(this);
    tenick = new QLineEdit(this);
    btnconn = new QPushButton("Połącz", this);
    labels = new std::vector<QLabel*>();
    labels->push_back(new QLabel("Podaj ip serwera", this));
    labels->push_back(new QLabel("Podaj swój nick", this));
    labels->push_back(new QLabel("Połącz się z serwerem", this));
    labels->push_back(new QLabel("Połącz się z \nserwerem żeby \nzobaczyć liste \ngraczy", this));


 //connections

    connect(btnconn, &QPushButton::clicked, this, &ConnectWindow::onConnbtn);

 //spawning first gui

    Spawn(teip, 10, 80 ,150, 30);
    Spawn(tenick, 10, 140, 150, 30);

    btnconn->move(10,200);
    btnconn->setFixedSize(150, 30);
    btnconn->setFont(QFont("Arial", 10));

    Spawn(labels->at(0), 10, 60, 150, 20);
    Spawn(labels->at(1), 10, 120, 150, 20);
    Spawn(labels->at(2), 10, 180, 150, 20);
    Spawn(labels->at(3), 170, 60, 120, 60);


}
