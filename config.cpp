#include "base.h"


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
        labels.emplace_back(new QLabel("0/"+QString::number(i+1), this));
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

  CreateLabelsForShipsValidation();

    btn1 = new QPushButton("Connect to the server", this);
    btn1->move(270, 30);
    btn1->setFixedSize(120,30);

    connect(btn1, &QPushButton::clicked, this, &Base::onConnect);

    uimem = new UiMembers();

}

void Base::CreateEnemyButtons(){

    x = 400;
    y = 45;

    enemybuttons.push_back(std::vector<Button *>());

    int number = 0;
    char letter = 'A';

    for(int i = 0; i < 10; i++){
        enemybuttons.emplace_back(std::vector<Button *>());

        for(int j = 0; j < 10; j++){
            enemybuttons[i].emplace_back(new Button());
            enemybuttons[i][j]->setParent(this);
            enemybuttons[i][j]->resize(buttonsize, buttonsize);
            enemybuttons[i][j]->move(x,y);
            enemybuttons[i][j]->setStyleSheet(normalenemybutton);
            enemybuttons[i][j]->SetName(static_cast<QChar>(letter), number);
            enemybuttons[i][j]->setDisabled(true);
            CreateEnemyConnection(enemybuttons[i][j]);
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

    int number = 0;
    char letter = 'A';

    for(int i = 0; i < 10; i++){
        buttons.push_back(std::vector<Button *>());

        for(int j = 0; j < 10; j++){
            buttons[i].push_back(new Button());
            buttons[i][j]->setParent(this);
            buttons[i][j]->resize(buttonsize, buttonsize);
            buttons[i][j]->move(x,y);
            buttons[i][j]->setStyleSheet(normalbutton);
            buttons[i][j]->SetName(static_cast<QChar>(letter), number);
            buttons[i][j]->setDisabled(true);
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

