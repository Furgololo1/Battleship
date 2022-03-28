#ifndef BASE_H
#define BASE_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QPair>
#include <QLabel>
#include <QWidget>
#include <QHostAddress>
#include <QTcpSocket>
#include <vector>


#include "networkclient.h"
#include "connectwindow.h"
#include "button.h"
#include "ship.h"
#include "types.cpp"



QT_BEGIN_NAMESPACE
namespace Ui { class Base; }
QT_END_NAMESPACE

class Base : public QMainWindow
{
    Q_OBJECT

public:
    Base(QWidget *parent = nullptr);
    ~Base();


    void CreateButtons();
    void CreateEnemyButtons();
    void SendShips();



private slots:

    void onPlay();

    void onConnect();

    void onChoosePlayer();

    void onConnectedToServer();

    void onDisconnectedFromServer();

    void on_choosepl_btn_clicked();

    void on_pushbutton_clicked();

    void on_accept_btn_clicked();

    void on_discard_btn_clicked();

    void on_sendinvite_btn_clicked();

    void EnableEnemyButtons();

    void DisableEnemyButtons();

    void RemoveShip(QString );

    void on_DestroyAllShip(QString );
    void on_DestroyAllEnemyShip(QString );

    void on_EndGame();

    void on_ResetGame();

    void on_pushButton_clicked();

    void onStartGame();

private:
    Ui::Base *ui;

    bool bcanplay = false;

    //size of
    int shipsize = 0;

    int x = 10, y = 45;
    int buttonsize = 20;

    QString normalbutton = "QPushButton{background-color: #FFFFFF;   border: 1px; border-color: #056DE3;   border-style: solid;  color: #000000;   padding: 15px 32px;    text-align: center;   text-decoration: none;    }";
    QString normalenemybutton = "QPushButton{background-color: #FFFFFF;   border: 1px; border-color: #808080;   border-style: solid;  color: #000000;   padding: 15px 32px;    text-align: center;   text-decoration: none;    }";
    QString shipsbutton = "QPushButton{background-color: #056DE3;   border: none; color: white;   padding: 15px 32px;    text-align: center;   text-decoration: none;    }";

    NetworkClient *nc = nullptr;

    QTcpSocket  *_socket = nullptr;

    ConnectWindow *conw = nullptr;

    UiMembers* uimem = nullptr;


//056DE3

    //      ships
    std::vector<ship *> ships;

    //      gui
    std::vector<QLabel *> labels;


    //play and connect button
    QPushButton *btn1 = nullptr;


    //      vector of all Buttons in game

    std::vector<std::vector<Button *> > buttons;

    std::vector<std::vector<Button *> > enemybuttons;

    //                              functions

    void CreateConnection(Button *b);
    void CreateEnemyConnection(Button *b);

    void AssignButtonToShip(Button *b);

    void RemoveButtonFromShip(Button *b);

    void CreateUI();

    void CheckShipAmount();

    void DisablePlayerButtons();

    void EnablePlayerButtons();

    void CreateLabelsForShipsValidation();




};
#endif // BASE_H
