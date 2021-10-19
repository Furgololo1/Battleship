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




void Base::on_pushButton_clicked()
{
//    ships->push_back(new ship(4, "Ship 4"));

//    QString a = "Aa";
//    qDebug()<<(int)a[1].toLatin1();
}



void Base::CreateConnection(button *b)
{

 b->connect(b, &button::clicked, this, [b, this]()mutable{
//      AssignButtonToShip(b);
      A(b);
 });


}
/*
void Base::AssignButtonToShip(button *b)
{
    //section 1
    if(ships->size() == 0){
        ships->push_back(new ship());
        (*ships)[0]->TryAddButtonToShip(b->GetName());
    }

    //section 1
    else{
        int size = ships->size();

     //first bool - when true meets the conditions for adding, second bool - can be add
        QPair<bool,bool> state (false, false);


        //section 2
        for(int i = 0; i < size; i++){

                state = (*ships)[i]->TryAddButtonToShip(b->GetName());

                      if(state.first == true && state.second == true){
                            b->setStyleSheet(shipsbutton);
                            b->disconnect();
                            return;
                      }

                      else if(state.first == true && state.second == false){
                          qDebug()<<"Cannot add button: "<<b->GetName() << " to ship"<<i;
                          return;
                      }

            }

            if(state.first == false && state.second == false){
                   ships->push_back(new ship());
                   (*ships)[ships->size()-1]->TryAddButtonToShip(b->GetName());
            }

        }




    b->setStyleSheet(shipsbutton);
    b->disconnect();

}
*/

void Base::A(button *b){
    if(ships->size() == 0){
        ships->push_back(new ship());
        (*ships)[0]->TryAddButtonToShip(b);
    }

    else{

        int size = ships->size();
        bool isadded = false;
        int toremove = 0;

     //first bool - when true meets the conditions for adding, second bool - can be add
        QPair<bool,bool> state (false, false);


        //section 2
        for(int i = 0; i < size; i++){
            state = (*ships)[i]->TryAddButtonToShip(b);


            if(state.first == true && state.second == true ){
                  b->setStyleSheet(shipsbutton);
                  b->disconnect();
                  isadded = true;
                  toremove = i;
                 // return;
            }


            else if(state.first == true && state.second == false && isadded == true){
                qDebug()<<"Cannot add button: "<<b->GetName() << " to ship"<<i;
                b->setStyleSheet(normalbutton);
                (*ships)[toremove]->RemoveLastAddedButton();
                return;
            }

        }

        if(state.first == false && state.second == false){
               ships->push_back(new ship());
               (*ships)[ships->size()-1]->TryAddButtonToShip(b);
        }

    }

    b->setStyleSheet(shipsbutton);
    b->disconnect();

}



void Base::on_pushButton_2_clicked()
{
    if(!ships) return;

    int size = ships->size();

    qDebug()<<"Vector of ships size : "<<size;

    for(int i = 0; i < size; i++){
        qDebug()<<"Ship nr " << i <<"  layout: "<<(*ships)[i]->GetLayout();

              for(const auto &s : *(*ships)[i]->GetShipvec()){
                    qDebug()<<"Ship :"<<s->GetName() ;
              }

        qDebug()<<"";

    }

}
























