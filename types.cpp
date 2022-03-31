#pragma once

#include <QTextEdit>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QPushButton>

#include "button.h"

struct UiMembers{

    QListWidget* playerlist = nullptr;

    QLabel* wtp_lbl = nullptr;

    QLabel* enemy_lbl = nullptr;

    QLabel* you_lbl = nullptr;

    QLabel* info_lbl = nullptr;

    QPushButton* btn1 = nullptr;

    Button* enemybutton = nullptr;

    void RemoveUiMembers(){
        delete playerlist;
        delete wtp_lbl;
        delete enemy_lbl;
        delete you_lbl;
        delete info_lbl;
        //delete btn1;
        delete enemybutton;

    }

};
