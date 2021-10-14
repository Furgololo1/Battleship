#include "base.h"
#include "./ui_base.h"

Base::Base(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Base)
{
    ui->setupUi(this);

    this->resize(400,265);

    ships = new std::vector<ship *>();

    CreateButtons();
}

Base::~Base()
{
    //delete buttons;
    delete ui;
}

void Base::CreateButtons()
{

    buttons.push_back(std::vector<button *>());

    int number = 1;

    for(int i = 0; i < 10; i++){
        buttons.push_back(std::vector<button *>());

        for(int j = 0; j < 10; j++){
            buttons[i].push_back(new button());
            buttons[i][j]->setParent(this);
            buttons[i][j]->resize(buttonsize, buttonsize);
            buttons[i][j]->move(x,y);
            buttons[i][j]->setStyleSheet(normalbutton);
            buttons[i][j]->SetName(number);
            buttons[i][j]->setText(QString::number(number));
            CreateConnection(buttons[i][j]);
            
            x+=25;
            number++;
        }
        x = 10;
        y += 25;
    }


}




void Base::on_pushButton_clicked()
{
  //  ships->push_back(new ship(4, "Ship 4"));

}



void Base::CreateConnection(button *b)
{

 b->connect(b, &button::clicked, this, [b, this]()mutable{
      //(*ships)[ships->size()]->TryAddButtonToShip(b->GetName());
      AssignButtonToShip(b);
      b->setStyleSheet(shipsbutton);
      b->disconnect();
 });


}

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

     //if adding to ship button *b is succesful  (first "if" statement is true) then "isgood" is true
     //if
        bool isgood = false;


        //for loops for checking addition validation
        //section 2
        for(int i = 0; i < size; i++){
            for(const auto s : *(*ships)[i]->GetShipBlocks()){

             //section 3
                if(s - 10 == b->GetName() || s + 10 == b->GetName() || s + 1 == b->GetName() || s - 1 == b->GetName()){


                 //section 4
                    if((*ships)[i]->TryAddButtonToShip(b->GetName())){}


                 //section 4
                    else{
                        qDebug()<<"Cannot add "<<b->GetName();
                    }

                  // isgood = true;
                   //break;
                    return;
                }
            }
        }


        //section 2
      //  if(isgood == false){
           ships->push_back(new ship());
           (*ships)[ships->size()-1]->TryAddButtonToShip(b->GetName());
           qDebug()<<"Not breaking loops";
        //}
    }


}



void Base::on_pushButton_2_clicked()
{
    if(!ships) return;

    int size = ships->size();

    qDebug()<<"Vector of ships size : "<<size;

    for(int i = 0; i < size; i++){
        qDebug()<<"Ship nr " << i ;

              for(const auto &s : *(*ships)[i]->GetShipBlocks()){
                    qDebug()<<"Ship :"<<s ;
              }

        qDebug()<<"";

    }

}
