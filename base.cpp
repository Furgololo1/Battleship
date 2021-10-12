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

    char letter = 65;
    int number = 1;

    for(int i = 0; i < 10; i++){
        buttons.push_back(std::vector<button *>());

        for(int j = 0; j < 10; j++){
            buttons[i].push_back(new button());
            buttons[i][j]->setParent(this);
            buttons[i][j]->resize(buttonsize, buttonsize);
            buttons[i][j]->move(x,y);
            buttons[i][j]->setStyleSheet(normalbutton);
            buttons[i][j]->SetName(letter+QString::number(number));
            buttons[i][j]->setText(buttons[i][j]->GetName());
            CreateConnection(buttons[i][j]);
            
            x+=25;
            letter++;

        }
        number++;
        letter = 65;
       // number = 1;
        x = 10;
        y += 25;
    }


}




void Base::on_pushButton_clicked()
{
    ships->push_back(new ship(4, "Ship 4"));
}



void Base::CreateConnection(button *b)
{

 b->connect(b, &button::clicked, this, [b, this]()mutable{
      //(*ships)[ships->size()]->AddButtonToShip(b->GetName());
      AssignButtonToShip(b);
      b->setStyleSheet(shipsbutton);
 });


}

void Base::AssignButtonToShip(button *b)
{

   // if(ships->size() == 0)
        ships->push_back(new ship());

  (*ships)[0]->AddButtonToShip(b->GetName());

    for(auto const &i : *(*ships)[0]->GetShipBlocks())
        qDebug()<<(int)i.toStdString()[0] + (int)i.toStdString()[1];




}



void Base::on_pushButton_2_clicked()
{
    if(!ships) return;

    for(auto const& i : *(*ships)[0]->GetShipBlocks())
        qDebug()<<i<<" ";
}
