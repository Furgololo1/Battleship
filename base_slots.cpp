#include "base.h"
#include "./ui_base.h"


void Base::on_DestroyAllShip(QString allship)
{
    QString firstship = allship.left(2);

    for(const auto &s : ships)
        for(const auto &shipvec : *s->GetShipvec())
            if(shipvec->GetName() == firstship){
                s->DestroyShip();
                break;
            }
}


void Base::on_DestroyAllEnemyShip(QString allships)
{
    QString destroyedButton = "QPushButton{background-color: #F44336;   border: 1px; border-color: #F44336;   border-style: solid;   color: #000000;   padding: 15px 32px;    text-align: center;   text-decoration: none;    }";
    QString oneship = allships.left(2);
    int size = (allships.length()/2);

    for (int i = 0; i < size; i++) {
        for(int row = 0; row < 10; row++){
            for(int col = 0; col < 10; col++){
                if(enemybuttons[row][col]->GetName() == oneship){
                    enemybuttons[row][col]->setStyleSheet(destroyedButton);
                    enemybuttons[row][col]->setDisabled(true);
                    enemybuttons[row][col]->bIsDestroyed = true;
                    allships.remove(oneship, Qt::CaseInsensitive);
                    oneship = allships.left(2);
                }
            }
        }
    }

}


void Base::on_EndGame()
{
    btn1->setHidden(false);
    btn1->setText("Restart");
    connect(btn1, &QPushButton::clicked, this, &Base::ResetGame);
}


void Base::onConnectedToServer()
{
    qDebug()<<"Connected to the server";

    ui->accept_btn->setHidden(false);
    ui->discard_btn->setHidden(false);
}


void Base::onDisconnectedFromServer()
{
    qDebug()<<"Cannot connect to the server";
}


void Base::on_accept_btn_clicked()
{
    nc->AcceptInvite();
}


void Base::on_discard_btn_clicked()
{
    nc->DiscardInvite();
}


void Base::on_sendinvite_btn_clicked()
{
    nc->SendToServer("!invite?!" + ui->players->currentItem()->text());
}


void Base::onStartGame()
{
    ui->stackedWidget->setCurrentIndex(0);
    CreateLabelsForShipsValidation();

    if(!bUIExists)
        CreateUI();
    else{
        for(auto &i : enemybuttons)
            for(auto &j : i)
                CreateEnemyConnection(j);
        for(auto &i : buttons)
            for(auto &j : i)
                CreateConnection(j);
    }

    btn1 = new QPushButton("Play", ui->stackedWidget->currentWidget());
    btn1->move(290, 20);


    connect(btn1, &QPushButton::clicked, this, &Base::onPlay);
    EnablePlayerButtons();

    btn1->setHidden(false);
    btn1->setDisabled(true);
    btn1->setText("Play");

}


void Base::onPlay(){

    for(auto &l : labels)
        delete l;

    labels.erase(labels.begin(), labels.end());

    SendShips();
    nc->SendToServer("!ready!");
    btn1->setHidden(true);
    btn1->disconnect();

    DisablePlayerButtons();
    DisableEnemyButtons();

    QString labelstyle = "QLabel{ border: 3px solid #FF004B; color: rgb(0,0,0); font-family: 'Arial Black'; font-size: 12px; }";

    info_lbl = new QLabel("Wait for\nenemy player", ui->stackedWidget->currentWidget());
    info_lbl->setHidden(false);
    info_lbl->show();
    info_lbl->move(270,30);
    info_lbl->setFixedSize(120, 50);
    info_lbl->setStyleSheet(labelstyle);
    info_lbl->setFont(QFont("Arial", 14));
    info_lbl->setAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);
    uimem->info_lbl = info_lbl;

}


void Base::on_connect_btn_clicked()
{
    uimem = new UiMembers();
    uimem->playerlist = ui->players;
    uimem->wtp_lbl = ui->wtp_lbl;
    uimem->enemy_lbl = ui->enemy_lbl;
    uimem->you_lbl = ui->you_lbl;
    uimem->btn1 = btn1;

    _socket = new QTcpSocket(this);
    nc = new NetworkClient(_socket, uimem);

    nc->ConnectWithServer(ui->ip_le->text(), ui->name_le->text(), std::bind(&Base::ConnectedSuccesfull, this));

    connect(_socket, &QAbstractSocket::connected, this, &Base::onConnectedToServer);
    connect(nc, &NetworkClient::onUrTurn, this, &Base::EnableEnemyButtons);
    connect(nc, &NetworkClient::onNotUrTurn, this, &Base::DisableEnemyButtons);
    connect(nc, &NetworkClient::onRemoveShip, this, &Base::RemoveShip);
    connect(nc, &NetworkClient::DestroyShip, this, &Base::on_DestroyAllShip);
    connect(nc, &NetworkClient::DestroyEnemyShip, this, &Base::on_DestroyAllEnemyShip);
    connect(nc, &NetworkClient::Reset, this ,&Base::on_EndGame);
    connect(nc, &NetworkClient::StartGame, this, &Base::onStartGame);
}

//debug
void Base::on_pushButton_clicked()
{
    AssignButtonToShip(buttons[0][0]);
    AssignButtonToShip(buttons[1][0]);
    AssignButtonToShip(buttons[2][0]);
    AssignButtonToShip(buttons[3][0]);

    AssignButtonToShip(buttons[0][2]);
    AssignButtonToShip(buttons[1][2]);
    AssignButtonToShip(buttons[2][2]);

    AssignButtonToShip(buttons[0][4]);
    AssignButtonToShip(buttons[1][4]);
    AssignButtonToShip(buttons[2][4]);

    AssignButtonToShip(buttons[0][6]);
    AssignButtonToShip(buttons[1][6]);

    AssignButtonToShip(buttons[0][8]);
    AssignButtonToShip(buttons[1][8]);

    AssignButtonToShip(buttons[3][8]);
    AssignButtonToShip(buttons[4][8]);

    AssignButtonToShip(buttons[3][6]);

    AssignButtonToShip(buttons[4][4]);

    AssignButtonToShip(buttons[4][2]);

    AssignButtonToShip(buttons[5][0]);

}


