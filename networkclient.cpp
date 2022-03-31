#include "networkclient.h"

#include <QDebug>
#include <QHostAddress>
#include <QTcpSocket>



void NetworkClient::SendToServer(QString text){
    socket->write(QByteArray::fromStdString(text.toStdString())+ "^");
}


void NetworkClient::onReadyRead()
{
    QByteArray command = socket->readAll();
        qDebug()<<command;
        socket->reset();
        CutCommand(command);
}


void NetworkClient::AcceptInvite()
{
    socket->write("!inviteok!" + QByteArray::fromStdString(enemynick.toStdString()) + "^");
    uimem->enemy_lbl->setText(enemynick);
    emit StartGame();
}


void NetworkClient::DiscardInvite()
{
    socket->write("!invitenot!" + QByteArray::fromStdString(enemynick.toStdString()) + "^");
//    uimem->stack->setCurrentIndex(1);
}

void NetworkClient::Shoot(QString shot, Button* button)     //shoot
{
    socket->write("?shoot?" + QByteArray::fromStdString(shot.toStdString()) + "^");
    //socket->waitForReadyRead(1000);
    uimem->enemybutton = button;
}


void NetworkClient::InterpretCommand(QString com)
{
        if(com.contains("?nick?", Qt::CaseSensitive))              //inquiry of nick
            socket->write(QByteArray::fromStdString("?nick? " + nick.toStdString() + "^"));

        else if(com.contains("!players!", Qt::CaseSensitive))           //gets list of player
            uimem->playerlist->addItem(com.remove("!players!", Qt::CaseSensitive));

        else if(com.contains("?invite?", Qt::CaseSensitive)){           //notify that player is invite to game
            enemynick = com.remove("?invite?", Qt::CaseSensitive);
            uimem->wtp_lbl->setText(enemynick + "\nwants to play with you");
        }

        else if(com.contains("!invitenot!", Qt::CaseSensitive)){        //infor that invite is rejected
        }

        else if(com.contains("!inviteok!", Qt::CaseSensitive)){         //inform that invite is accept and starts game
            enemynick = com.remove("!inviteok!", Qt::CaseSensitive);
            uimem->enemy_lbl->setText(enemynick);
            emit StartGame();
           }

        else if(com.contains("!shootok!", Qt::CaseSensitive)){          //change enemy button to hit img,it's hit
            uimem->enemybutton->Hit();
        }

        else if(com.contains("!shootmiss!", Qt::CaseSensitive)){        //change enemy button to miss img, it's not hit
            uimem->enemybutton->Miss();
        }

        else if(com.contains("!urturn!", Qt::CaseSensitive)){
            if(!bEnd)
                uimem->info_lbl->setText("Your turn");
            emit onUrTurn();
        }

        else if(com.contains("!noturturn!", Qt::CaseSensitive)){
            if(!bEnd)
                uimem->info_lbl->setText(enemynick + "'s turn");
            emit onNotUrTurn();

        }

        else if(com.contains("!hit!", Qt::CaseSensitive)){              //Emits removing button from class Base
            emit onRemoveShip(com.remove("!hit!", Qt::CaseSensitive));
        }

        else if(com.contains("!destroy!", Qt::CaseSensitive)){
            emit DestroyShip(com.remove("!destroy!", Qt::CaseSensitive));
        }

        else if(com.contains("!destroyenemy!", Qt::CaseSensitive)){
            emit DestroyEnemyShip(com.remove("!destroyenemy!", Qt::CaseSensitive));
        }

        else if(com.contains("!win!", Qt::CaseSensitive)){
            bEnd = true;
            uimem->info_lbl->setText("You won!!!");
            EndGame();
        }


       else if(com.contains("!lose!", Qt::CaseSensitive)){
            bEnd = true;
            uimem->info_lbl->setText(enemynick + " won!!!");
            EndGame();
        }

        //socket->reset();

}


void NetworkClient::CutCommand(QString com)         //extracts the command from qbytearray and interprets it sequentially
{
    int commands = com.count('^', Qt::CaseSensitive);

    for(int i = 0; i < commands; i++){
        int index = com.indexOf("^", Qt::CaseSensitive);

        QString a = com.mid(0, index);
        com.erase(com.begin(), com.begin()+index+1);

        InterpretCommand(a);
    }
}


void NetworkClient::EndGame()
{
    enemynick.clear();
    socket->reset();
    emit Reset();
    uimem->info_lbl->move(270, 70);
    bEnd = false;
}











