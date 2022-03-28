#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QListView>
#include <thread>
#include <chrono>


#include "networkclient.h"


class ConnectWindow : public QWidget
{
    Q_OBJECT
private:

 //pointer to network client
    NetworkClient* nc = nullptr;
 //text edit to input server ip
    QLineEdit* teip = nullptr;
 //text edit for typing player nick
    QLineEdit* tenick = nullptr;
 //button to aprove typed ip from server and send it to nc
    QPushButton* btnconn = nullptr;
 //vector of labels
    std::vector<QLabel*> *labels = nullptr;


public:
   // explicit ConnectWindow(QWidget *parent = nullptr);
    ConnectWindow(NetworkClient* networkclient): nc(networkclient){
        this->resize(300,300);
        this->setWindowTitle("Connect with server");
        CreateGUI();
    }
    ~ConnectWindow(){
        delete labels;
    }

    void ConnectedSuccesfull();


private slots:

    void onConnbtn();

private:

    void CreateGUI();


template <typename T>
    void Spawn(T object,  int x, int y, int sizex, int sizey){
        object->move(x,y);
        object->setFixedSize(sizex, sizey);
        object->setFont(QFont("Arial", 10));
        object->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    }


};


#endif // CONNECTWINDOW_H
