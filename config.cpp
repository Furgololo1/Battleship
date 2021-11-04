#include "base.h"




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

    btn1 = new QPushButton("Play", this);
    btn1->move(270, 30);
    btn1->setFixedSize(120,30);

    connect(btn1, &QPushButton::clicked, this, &Base::onPlay);

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
