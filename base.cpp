#include "base.h"
#include "./ui_base.h"

Base::Base(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Base)
{
    ui->setupUi(this);

    this->resize(660,300);

    ui->stackedWidget->setCurrentIndex(1);

    ui->accept_btn->setHidden(true);
    ui->discard_btn->setHidden(true);

}

void Base::ResetGame(){

    for(auto &s : ships){
        delete s;
    }

    ships.erase(ships.begin(), ships.end());
    ships.clear();

    ResetButtons(&buttons);
    ResetButtons(&enemybuttons);

    delete info_lbl;
    delete btn1;

    ui->wtp_lbl->setText("No pending \ninvitations...");

    bcanplay = false;
    ui->stackedWidget->setCurrentIndex(1);
}


void Base::ResetButtons(std::vector<std::vector<Button *>> *vec){
    for(auto &i : *vec)
        for(auto &j : i){
            j->disconnect();
            j->Reset();
        }
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


void Base::ConnectedSuccesfull()
{
    delete ui->ip_le;
    delete ui->name_le;
    delete ui->connect_btn;
    delete ui->connect_lbl;
    ui->accept_btn->setHidden(false);
    ui->discard_btn->setHidden(false);
}


void Base::CreateConnection(Button *b)
{

  b->connect(b, &Button::clicked, this, [b, this]()mutable{

     qDebug()<<"Clicked button";

     if(!b->bisclicked)
         AssignButtonToShip(b);
     else
         RemoveButtonFromShip(b);
     });

}


void Base::CreateEnemyConnection(Button *b)
{
    b->connect(b, &Button::clicked, this, [b, this]()mutable{
        nc->Shoot(b->GetName(), b);
        b->setDisabled(true);
        qDebug()<<"Shoot in button with name "<<b->GetName();
    });
}


void Base::CreateLabelsForShipsValidation()
{
    QString labelstyle = "QLabel{ background-color:#FF004B; color: rgb(0,0,0); font-family: 'Arial Black'; font-size: 18px; }";

    int x = 270, y = 120;
    int sizex = 120, sizey = 30;

    for(int i = 0; i < 4; i++){
        labels.emplace_back(new QLabel("0/"+QString::number(i+1), ui->stackedWidget->currentWidget()));
        labels[i]->move(x,y);
        labels[i]->setFixedSize(sizex,sizey);
        labels[i]->setStyleSheet(labelstyle);
        labels[i]->setAlignment(Qt::Alignment::enum_type::AlignHCenter);
        labels[i]->setHidden(false);
        x += 10;
        y += 40;
        sizex -= 20;
    }

}


void Base::CreateUI(){
  CreateEnemyButtons();
  CreateButtons();
  bUIExists = true;
}

void Base::CreateEnemyButtons(){

    enemybuttons.push_back(std::vector<Button *>());

    int x = 400;
    int y = 45;

    int number = 0;
    char letter = 'A';

    Button* newBtn;

    for(int i = 0; i < 10; i++){
        enemybuttons.emplace_back(std::vector<Button *>());

        for(int j = 0; j < 10; j++){
            newBtn = new Button();
            newBtn->setParent(ui->stackedWidget->currentWidget());
            newBtn->resize(buttonsize, buttonsize);
            newBtn->move(x,y);
            newBtn->setStyleSheet(normalenemybutton);
            newBtn->SetName(static_cast<QChar>(letter), number);
            newBtn->setDisabled(true);
            newBtn->setHidden(false);
            CreateEnemyConnection(newBtn);
            enemybuttons[i].push_back(newBtn);
            x+=25;
            letter++;
        }
        letter = 'A';
        number++;
        x = 400;
        y += 25;
    }
}


void Base::CreateButtons(){

    buttons.push_back(std::vector<Button *>());

    int x = 10;
    int y = 45;

    int number = 0;
    char letter = 'A';
    Button* newBtn;

    for(int i = 0; i < 10; i++){
        buttons.push_back(std::vector<Button *>());

        for(int j = 0; j < 10; j++){
            newBtn = new Button();
            newBtn->setParent(ui->stackedWidget->currentWidget());
            newBtn->resize(buttonsize, buttonsize);
            newBtn->move(x,y);
            newBtn->setStyleSheet(normalbutton);
            newBtn->SetName(static_cast<QChar>(letter), number);
            newBtn->setDisabled(true);
            newBtn->setHidden(false);
            CreateConnection(newBtn);
            buttons[i].push_back(newBtn);

            x+=25;
            letter++;
        }
        letter = 'A';
        number++;
        x = 10;
        y += 25;
    }

}


Base::~Base()
{

    if(uimem)
        delete uimem;
    if(nc)
        delete nc;

    if(_socket){
        _socket->close();
        delete _socket;
    }

    if(btn1)
        delete btn1;

    for(auto &i : ships)
        delete i;

    delete ui;
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



