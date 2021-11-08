#include "connectwindow.h"

/*onnectWindow::ConnectWindow(QWidget *parent) : QWidget(parent)
{
    this->resize(300,300);
    this->setWindowTitle("Connect with server");
}
*/

void ConnectWindow::onOKbtn()
{
    nc->ConnectWithServer(teip->text(), tenick->text());

}

void ConnectWindow::CreateGUI()
{

    teip = new QLineEdit(this);
    tenick = new QLineEdit(this);
    btnok = new QPushButton("OK", this);
    labels = new std::vector<QLabel*>();
 // pl = new QListView(this);
    labels->push_back(new QLabel("Podaj ip serwera", this));
    labels->push_back(new QLabel("Podaj swój nick", this));
    labels->push_back(new QLabel("Połącz się z serwerem", this));
    labels->push_back(new QLabel("Połącz się z \nserwerem żeby \nzobaczyć liste \ngraczy", this));


 //connections

    connect(btnok, &QPushButton::clicked, this, &ConnectWindow::onOKbtn);



    labels->at(0)->move(10,60);
    labels->at(0)->setFixedSize(150,20);
    labels->at(0)->setFont(QFont("Arial", 10));
    labels->at(0)->setAlignment(Qt::AlignmentFlag::AlignHCenter);

    teip->move(10,80);
    teip->setFixedSize(150,30);
    tenick->setFont(QFont("Arial", 10));
    //teip->setFontPointSize(12);
    teip->setAlignment(Qt::AlignmentFlag::AlignHCenter);



    labels->at(1)->move(10,120);
    labels->at(1)->setFixedSize(150,20);
    labels->at(1)->setFont(QFont("Arial", 10));
    labels->at(1)->setAlignment(Qt::AlignmentFlag::AlignHCenter);

    tenick->move(10,140);
    tenick->setFixedSize(150,30);
    tenick->setFont(QFont("Arial", 10));
    //tenick->setFontPointSize(12);
    tenick->setAlignment(Qt::AlignmentFlag::AlignHCenter);



    labels->at(2)->move(10,180);
    labels->at(2)->setFixedSize(150,20);
    labels->at(2)->setFont(QFont("Arial", 10));
    labels->at(2)->setAlignment(Qt::AlignmentFlag::AlignHCenter);

    btnok->move(10,210);
    btnok->setFixedSize(150,30);
    btnok->setFont(QFont("Arial", 10));



    labels->at(3)->move(170,60);
    labels->at(3)->setFixedSize(120,60);
    labels->at(3)->setFont(QFont("Arial", 10));
    labels->at(3)->setAlignment(Qt::AlignmentFlag::AlignHCenter);

    //pl->move(170, 30);
    //pl->setFixedSize(120,120);



}
