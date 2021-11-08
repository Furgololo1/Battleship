#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QListView>

#include "networkclient.h"

class ConnectWindow : public QWidget
{
    Q_OBJECT
private:
    //pointer to network client
    NetworkClient* nc = nullptr;
    //text edit to iput server ip
    QLineEdit* teip = nullptr;
    //text edit for typing player nick
    QLineEdit* tenick = nullptr;
    //button to aprove typed ip from server and send it to nc
    QPushButton* btnok = nullptr;
    //vector of labels
    std::vector<QLabel*> *labels = nullptr;
    //list of players conneced to server
    QListView* pl = nullptr;

public:
   // explicit ConnectWindow(QWidget *parent = nullptr);
    ConnectWindow(NetworkClient* networkclient): nc(networkclient){
        this->resize(300,300);
        this->setWindowTitle("Connect with server");
        CreateGUI();
    }


private slots:

    void onOKbtn();

private:

    void CreateGUI();




};

#endif // CONNECTWINDOW_H
