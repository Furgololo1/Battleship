#include "base.h"
#include "./ui_base.h"

Base::Base(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Base)
{
    ui->setupUi(this);

    this->resize(655,300);

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


void Base::CreateUI(){

//    labels = new std::vector<QLabel*>();

//    labels->push_back(new QLabel("Twoja flota", this));
//    (*labels)[0]->setFont(QFont("Arial Black", 15, 1, false));
//    (*labels)[0]->move(50, 20);

}


void Base::CreateEnemyButtons(){

    x = 400;
    y = 45;

    enemybuttons.push_back(std::vector<button *>());

    int number = 1;
    char letter = 'A';

    for(int i = 0; i < 10; i++){
        enemybuttons.push_back(std::vector<button *>());

        for(int j = 0; j < 10; j++){
            enemybuttons[i].push_back(new button());
            enemybuttons[i][j]->setParent(this);
            enemybuttons[i][j]->resize(buttonsize, buttonsize);
            enemybuttons[i][j]->move(x,y);
            enemybuttons[i][j]->setStyleSheet(normalbutton);
            enemybuttons[i][j]->SetName((QChar)letter, number);
            enemybuttons[i][j]->setText(letter + QString::number(number));
           // CreateConnection(enemybuttons[i][j]);

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

    buttons.push_back(std::vector<button *>());

    int number = 1;
    char letter = 'A';

    for(int i = 0; i < 10; i++){
        buttons.push_back(std::vector<button *>());

        for(int j = 0; j < 10; j++){
            buttons[i].push_back(new button());
            buttons[i][j]->setParent(this);
            buttons[i][j]->resize(buttonsize, buttonsize);
            buttons[i][j]->move(x,y);
            buttons[i][j]->setStyleSheet(normalbutton);
            buttons[i][j]->SetName((QChar)letter, number);
            buttons[i][j]->setText(letter + QString::number(number));
            CreateConnection(buttons[i][j]);
            
            x+=25;
            letter++;
        }
        letter = 'A';
        number++;
        x = 10;
        y += 25;
    }


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


void Base::RemoveButtonFromShip(button *b){
    b->bisclicked = false;
    b->setStyleSheet(normalbutton);

    for(const auto &s : *ships){
        qDebug()<<s->RemoveFromShip(b);
    }

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

     //first bool - when true meets the conditions for adding, second bool - can be add
        QPair<bool,bool> state = QPair<bool,bool>(false,false);


        //section 2
        for(int i = 0; i < size; i++){

            state = (*ships)[i]->TryAddButtonToShip(b);

            if((state.first == true) && (state.second == true)){
                  b->setStyleSheet(shipsbutton);
                  //b->disconnect();
                 // return;
            }

            else if((state.first == false) && (state.second == true)) return;

        }

        if((state.first == false) && (state.second == false)){
               ships->push_back(new ship(buttons, ships->size()));
               (*ships)[ships->size()-1]->TryAddButtonToShip(b);
               b->setStyleSheet(shipsbutton);
               //b->disconnect();
        }

    }
    b->bisclicked = true;
}



void Base::on_pushButton_2_clicked()
{
    if(!ships) return;

    int size = ships->size();

//    qDebug()<<"Vector of ships size : "<<size;

    for(int i = 0; i < size; i++){
        qDebug()<<"Ship nr " <<  (*ships)[i]->GetIndex();

              for(const auto &s : *(*ships)[i]->GetShipvec()){
                    qDebug()<<"Ship :"<<s->GetName() ;
              }

        qDebug()<<"";

    }

}

//aaaaa test

void Base::CheckShipsCorrectness(){

}



