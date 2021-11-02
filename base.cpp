#include "base.h"
#include "./ui_base.h"

Base::Base(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Base)
{
    ui->setupUi(this);

    this->resize(655,300);

    ships = new std::vector<ship *>();

    ui->pushButton->setDisabled(true);

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

    QString labelstyle = "QLabel{ background-color:#FF004B; color: rgb(0,0,0); font-family: 'Arial Black'; font-size: 18px; }";

    labels = new std::vector<QLabel *>();

    int x = 270, y = 120;
    int sizex = 120, sizey = 30;

    for(int i = 0; i < 4; i++){
        labels->push_back(new QLabel("0/"+QString::number(i+1), this));
        (*labels)[i]->move(x,y);
        (*labels)[i]->setFixedSize(sizex,sizey);
        (*labels)[i]->setStyleSheet(labelstyle);
        (*labels)[i]->setAlignment(Qt::Alignment::enum_type::AlignHCenter);
        x += 10;
        y += 40;
        sizex -= 20;
    }

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
            enemybuttons[i][j]->setStyleSheet(normalenemybutton);
            enemybuttons[i][j]->SetName((QChar)letter, number);
            //enemybuttons[i][j]->setText(letter + QString::number(number));
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
            //buttons[i][j]->setText(letter + QString::number(number));
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



void Base::on_pushButton_2_clicked()
{
    /*if(!ships) return;

    int size = ships->size();

    qDebug()<<"#####################    Clicked button    #####################";
    qDebug()<<"bcanplay = "<<bcanplay;

    for(int i = 0; i < size; i++){
        qDebug() << "Ship nr " <<  ships->at(i)->GetIndex();
        qDebug() << "Validation " << ships->at(i)->AdditionValidation();

              for(const auto &s : *ships->at(i)->GetShipvec()){
                    qDebug()<<"Ship :"<<s->GetName() ;
              }

        qDebug()<<"";

    }

    CheckShipAmount();*/

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
            ui->pushButton->setDisabled(true);
            break;
        }
        else{
            bcanplay = true;
            ui->pushButton->setDisabled(false);
        }
    }



    delete bisokay;
    delete countships;

}


void Base::on_pushButton_clicked()
{
    qDebug()<<"Starting Game";
}
