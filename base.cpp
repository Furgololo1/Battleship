#include "base.h"
#include "./ui_base.h"

Base::Base(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Base)
{
    ui->setupUi(this);

    this->resize(910,302);

    ships = new std::vector<ship *>();


    CreateButtons();
    CreateEnemyButtons();
    CreateUI();
}

Base::~Base()
{
    //delete buttons;
    delete ui;
}



void Base::CreateConnection(button *b)
{

 b->connect(b, &button::clicked, this, [b, this]()mutable{

     if(!b->bisclicked)
         AssignButtonToShip(b);
     else
         RemoveButtonFromShip(b);
     });

}


void Base::onPlay(){
    qDebug()<<"Starting Game";

    for(auto &l : *labels)
        delete l;
    delete labels;

    disconnect(btn1, &QPushButton::clicked, this, &Base::onPlay);
    connect(btn1, &QPushButton::clicked, this, &Base::onConnect);

    btn1->setText("Connect with server");
}


void Base::onConnect(){
    qDebug()<<"New connection";

    conw = new ConnectWindow();
    conw->show();

}


void Base::RemoveButtonFromShip(button *b){


    for(int i = 0; i < ships->size(); i++){
        if((*ships)[i]->RemoveFromShip(b))ships->erase((*ships).begin()+i);
    }
    CheckShipAmount();

}


void Base::AssignButtonToShip(button *b){


    if(ships->size() == 0){
        ships->push_back(new ship(buttons, 0));
        (*ships)[0]->TryAddButtonToShip(b);
        b->setStyleSheet(shipsbutton);
        //b->disconnect();
    }

    else{

        int size = ships->size();
        bool isadded = false;
        int indextoadded = 0;

     //first bool - when true meets the conditions for adding, second bool - can be add
        QPair<bool,bool> state = QPair<bool,bool>(false,false);


        //section 2
        for(int i = 0; i < size; i++){

            state = (*ships)[i]->TryAddButtonToShip(b);

            if((state.first == true) && (state.second == true)){
                  b->setStyleSheet(shipsbutton);

                  if(isadded){
                      ships->at(indextoadded)->Merge(ships->at(i));
                      ships->erase(ships->begin()+i);
                  }

                  isadded = true;
                  indextoadded = i;
            }

            else if((state.first == false) && (state.second == true)) return;

        }

        if((state.first == false) && (state.second == false)){
               ships->push_back(new ship(buttons, ships->size()));
               (*ships)[ships->size()-1]->TryAddButtonToShip(b);
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

    for(const auto &s : *ships)
            countships->push_back(s->GetShipsize());

    std::vector<bool>* bisokay = new std::vector<bool>(4,false);

        int i = 1;
        int count;
        for(const auto &l : *labels){
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
          //  btn1->setDisabled(true);
            break;
        }
        else{
            bcanplay = true;
            //btn1->setDisabled(false);
        }
    }



    delete bisokay;
    delete countships;

}



