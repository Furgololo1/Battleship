#include "base.h"
#include "./ui_base.h"

Base::Base(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Base)
{
    ui->setupUi(this);

    this->resize(910,302);

//    ships = new std::vector<ship *>();


    CreateButtons();
    CreateEnemyButtons();
    CreateUI();
}

Base::~Base()
{
    if(conw)
        delete conw;
    if(uimem)
        delete uimem;
    if(nc)
        delete nc;

    _socket->close();

    if(_socket)
        delete _socket;

    if(btn1)
        delete btn1;

    for(auto &i : ships)
        delete i;


    delete ui;
}


void Base::RemoveButtonFromShip(Button *b){

    for(int i = 0; i < ships.size(); i++){
        //ship* removedship = reinterpret_cast<ship*>(*ships.begin()+1);
        if(ships[i]->RemoveFromShip(b))  ships.erase(ships.begin()+i);
       // qDebug()<<
    }
    CheckShipAmount();

}


void Base::AssignButtonToShip(Button *b){

       qDebug()<<ships.size();

       if(ships.size() == 0){
           ships.emplace_back(new ship(buttons, 0));
           ships[0]->TryAddButtonToShip(b);
           b->setStyleSheet(shipsbutton);
           //b->disconnect();
       }

       else{

           int size = ships.size();
           bool isadded = false;
           int indextoadded = 0;

        //first bool - when true meets the conditions for adding, second bool - can be add
           QPair<bool,bool> state = QPair<bool,bool>(false,false);


           //section 2
           for(int i = 0; i < size; i++){

               state = ships[i]->TryAddButtonToShip(b);

               if((state.first == true) && (state.second == true)){
                     b->setStyleSheet(shipsbutton);

                     if(isadded){
                         ships.at(indextoadded)->Merge(ships.at(i));
                         ships.erase(ships.begin()+i);
                     }

                     isadded = true;
                     indextoadded = i;
               }

               else if((state.first == false) && (state.second == true)) return;

           }

           if((state.first == false) && (state.second == false)){
                  ships.emplace_back(new ship(buttons, ships.size()));
                  ships[ships.size()-1]->TryAddButtonToShip(b);
                  b->setStyleSheet(shipsbutton);
           }

       }

       b->bisclicked = true;
       CheckShipAmount();

}


void Base::CheckShipAmount()
{
    std::vector<int>* countships = new std::vector<int>();

    QString labelstyle1 = "QLabel{ background-color: ";
    QString labelstyle2 = "; color: rgb(0,0,0); font-family: 'Arial Black'; font-size: 18px; }";

    for(const auto &s : ships)
            countships->push_back(s->GetShipsize());

    std::vector<bool>* bisokay = new std::vector<bool>(4,false);

        int i = 1;
        int count;
        for(const auto &l : labels){
            count = std::count(countships->begin(), countships->end(), (5-i));
            l->setText(QString::number(count) + "/" + QString::number(i));

            if(count != i)
                l->setStyleSheet(labelstyle1 + "#FF004B" + labelstyle2);
            else{
                bisokay->at(i-1) = true;
                l->setStyleSheet(labelstyle1 + "#43A047" + labelstyle2);
            }

            i++;
        }

    for(const auto &v : *bisokay){
        if(!v){
            bcanplay = false;
            btn1->setDisabled(true);
            break;
        }
        else{
            bcanplay = true;
            btn1->setDisabled(false);
        }
    }

    delete bisokay;
    delete countships;

}


void Base::EnablePlayerButtons()
{
 //player buttons

    for(int i = 0; i < 10; i++){
       // Buttons.push_back(std::vector<Buttons *>());
        for(int j = 0; j < 10; j++){
            buttons[i][j]->setDisabled(false);
        }
    }

}


void Base::DisablePlayerButtons()
{
    //player buttons

       for(int i = 0; i < 10; i++){
          // Buttons.push_back(std::vector<Buttons *>());
           for(int j = 0; j < 10; j++){
               buttons[i][j]->setDisabled(true);
           }
       }
}


void Base::DisableEnemyButtons()
{

 //enemy buttons, disabled when not owner player turn

    for(int i = 0; i < 10; i++){
       // Buttons.push_back(std::vector<Button *>());
        for(int j = 0; j < 10; j++){
            enemybuttons[i][j]->setDisabled(true);
        }
    }

}

void Base::EnableEnemyButtons()
{
    //enemy buttons

       for(int i = 0; i < 10; i++){
          // Buttons.push_back(std::vector<Button *>());
           for(int j = 0; j < 10; j++){
               enemybuttons[i][j]->setDisabled(false);
           }
       }
}


void Base::RemoveShip(QString shiptoremove)
{
    for(const auto &s: ships)
        if(s->RemoveFromShip(shiptoremove)) break;
}


void Base::SendShips()
{

    QString fleet = "";

    for(const auto &f : ships){    // f means 1 fleet (vector of Buttons from class ship)
        for(const auto &s : *f->GetShipvec()){
            fleet += s->GetName();
        }
        nc->SendToServer("!ships!" + fleet);
        fleet.clear();
    }

}


//######################        SLOTS       #######################


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
    uimem->btn1->setHidden(false);
    uimem->btn1->setText("New Game");
    connect(btn1, &QPushButton::clicked, this, &Base::on_ResetGame);
}


void Base::on_ResetGame()
{
    btn1->disconnect();

    if(!ships.empty()){

        DisableEnemyButtons();
        DisablePlayerButtons();

        nc->SendToServer("!endgame!");

        for(auto &s : ships){
            delete s;
        }

        ships.erase(ships.begin(), ships.end());
        ships.clear();


        for(const auto &i : buttons)
            for(const auto &i2 : i)
                i2->Reset();

        for(const auto &i : enemybuttons)
           for(const auto &i2 : i)
               i2->Reset();


        ui->stack->setCurrentIndex(2);

        delete uimem->info_lbl;
        btn1->setHidden(true);

        CreateLabelsForShipsValidation();

    }

}


void Base::onConnectedToServer()
{
    delete conw;
    //btn1->setText("Play");
    qDebug()<<"Connected to the server";

    btn1->setHidden(true);
    disconnect(btn1, &QPushButton::clicked, this, &Base::onConnect);

    if(ui->stack->currentIndex() == 1)
        ui->stack->setCurrentIndex(2);
    else
        ui->stack->setCurrentIndex(1);
}


void Base::onDisconnectedFromServer()
{
    qDebug()<<"Cannot connect to the server";
}


void Base::on_choosepl_btn_clicked()
{
    if(ui->stack->currentIndex() == 1)
        ui->stack->setCurrentIndex(2);
    else
        ui->stack->setCurrentIndex(1);
}


void Base::on_pushbutton_clicked()
{
    //nc->SendToServer(ui->players->currentItem());
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


void Base::on_pushButton_clicked()
{
//    if(ships){
        for(const auto &f : ships)
            for(const auto &s : *f->GetShipvec())
                qDebug()<<s->GetName();
//    }

         qDebug()<<"ship size"<<ships.size();

}


void Base::onStartGame()
{
    connect(btn1, &QPushButton::clicked, this, &Base::onPlay);
    EnablePlayerButtons();

        uimem->stack->setCurrentIndex(1);
        uimem->choosepl_btn->hide();
        uimem->btn1->setHidden(false);
        uimem->btn1->setDisabled(true);
        uimem->btn1->setText("Play");

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

    uimem->info_lbl = new QLabel("Wait for\nenemy player", this);
   // uimem->info_lbl->setHidden(false);
    uimem->info_lbl->show();
    uimem->info_lbl->move(270,30);
    uimem->info_lbl->setFixedSize(120, 50);
    uimem->info_lbl->setStyleSheet(labelstyle);
    uimem->info_lbl->setFont(QFont("Arial", 14));
    uimem->info_lbl->setAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);

}

void Base::onConnect(){

    uimem->playerlist = ui->players;
    uimem->stack = ui->stack;
    uimem->wtp_lbl = ui->wtp_lbl;
    uimem->choosepl_btn = ui->choosepl_btn;
    uimem->enemy_lbl = ui->enemy_lbl;
    uimem->you_lbl = ui->you_lbl;
    uimem->btn1 = btn1;


    _socket = new QTcpSocket(this);
    nc = new NetworkClient(_socket, uimem);

    conw = new ConnectWindow(nc);
    conw->show();

    connect(_socket, &QAbstractSocket::connected, this, &Base::onConnectedToServer);
    connect(nc, &NetworkClient::onUrTurn, this, &Base::EnableEnemyButtons);
    connect(nc, &NetworkClient::onNotUrTurn, this, &Base::DisableEnemyButtons);
    connect(nc, &NetworkClient::onRemoveShip, this, &Base::RemoveShip);
    connect(nc, &NetworkClient::DestroyShip, this, &Base::on_DestroyAllShip);
    connect(nc, &NetworkClient::DestroyEnemyShip, this, &Base::on_DestroyAllEnemyShip);
    connect(nc, &NetworkClient::Reset, this ,&Base::on_EndGame);
    connect(nc, &NetworkClient::StartGame, this, &Base::onStartGame);

}


void Base::onChoosePlayer()
{

    if(ui->stack->currentIndex() == 1)
        ui->stack->setCurrentIndex(2);
    else
        ui->stack->setCurrentIndex(1);

}

