#include "ship.h"

std::vector<int> ship::shipssize(10, 0);
std::vector<int> ship::shipsamount(4, 0);

ship::ship()
{
       //shipname = "basic";
       shipsize = 0;
}

bool ship::IsButtonAShip(int n)
{

   return false;

}


bool ship::AdditionValidation(){

    //delete buttons;
    const int size = shipvec.size();


    if((shipvec[0]->GetCol() + (size-1) == shipvec[size-1]->GetCol()) || (shipvec[0]->GetCol() - (size-1) == shipvec[size-1]->GetCol()))
        return true;

    else if((shipvec[0]->GetRow() + (size-1) == shipvec[size-1]->GetRow()) || (shipvec[0]->GetRow() - (size-1) == shipvec[size-1]->GetRow()))
        return true;

    else
        return false;
}



QPair<bool,bool> ship::TryAddButtonToShip(button *b){



    if(shipvec.size() < 1){
           shipvec.push_back(b);
           DisconnectButton(b);
           shipsinfleet++;
           return QPair<bool,bool>(true,true);
    }

    else{
            for(const auto & s : shipvec){

                        if((b->GetCol() == s->GetCol()) && (b->GetRow() + 1 == s->GetRow() || b->GetRow() - 1 == s->GetRow())){
                                shipvec.push_back(b);
                                sortRow();
                                DisconnectButton(b);
                                shipsinfleet++;
                                return QPair<bool,bool>(true,true);
                        }



                        else if((b->GetRow() == s->GetRow()) && (b->GetCol() + 1 == s->GetCol() || b->GetCol() - 1 == s->GetCol())){
                                shipvec.push_back(b);
                                sortCol();
                                DisconnectButton(b);
                                shipsinfleet++;
                                return QPair<bool,bool>(true,true);
                        }


               }
            }

    return QPair<bool,bool>(false,false);


}



bool ship::CheckAmountOfShips(int shipsizetoadd)
{
    if(shipsizetoadd > 4)return false;

    const int five = 5;

    for(int i = 1; i <= 4; i++){
            if(shipsamount[i-1] >= five-i)return false;
        }
        shipssize[index]++;


    //5-4 = 1; 5-3 = 2; itd;

    int count = 0;

    for(int i = 1; i <= 4; i++){
        for(const auto &s : shipssize){
            if(s == i)count++;
        }
        qDebug()<<"there are "<<count<<" ships on size "<<i;
        shipsamount[i-1] = count;
        count = 0;
    }


    return true;
}



void ship::DisconnectButton(button *b){


        int x = b->GetRow()-2;
        int y = b->GetCol()%65-1;

         if((x >= 0 && x <= 9) && (y >= 0 && y <= 9))
            (*buttons)[x][y]->disconnect();

         y += 2;

         if((x >= 0 && x <= 9) && (y >= 0 && y <= 9))
            (*buttons)[x][y]->disconnect();

         x += 2;
         if((x >= 0 && x <= 9) && (y >= 0 && y <= 9))
            (*buttons)[x][y]->disconnect();


         y -= 2;
         if((x >= 0 && x <= 9) && (y >= 0 && y <= 9))
            (*buttons)[x][y]->disconnect();

}


bool ship::RemoveFromShip(button *b){

    QString normalbutton = "QPushButton{background-color: #FFFFFF;   border: none;   color: #000000;   padding: 15px 32px;    text-align: center;   text-decoration: none;    }";

    //this is iterator to remove if button exists in shipvec
    auto itr = std::find(shipvec.begin(), shipvec.end(), b);
    auto ittobuttons = itr;

    while(ittobuttons != shipvec.end()){
        (*ittobuttons)->bisclicked = false;
        (*ittobuttons)->setStyleSheet(normalbutton);
        ittobuttons++;

    }

    qDebug()<<"size: "<<shipvec.size();


    shipvec.erase(itr, shipvec.end());

        b->bisclicked = false;
        b->setStyleSheet(normalbutton);

        qDebug()<<"size: "<<shipvec.size();


    if(shipvec.size() == 0)
        return true;

    return false;
}


void ship::sortRow(){

    int size = (int)shipvec.size();

    do{
        for(int i = 1; i < size; i++){
            if(shipvec[i]->GetRow() < shipvec[i-1]->GetRow())
                std::swap(shipvec[i], shipvec[i-1]);
        }

        size--;
    }while(size > 1);

}



void ship::sortCol(){

    int size = (int)shipvec.size();

    do{
        for(int i = 1; i < size; i++){
            if(shipvec[i]->GetCol() < shipvec[i-1]->GetCol())
                std::swap(shipvec[i], shipvec[i-1]);
        }

        size--;
    }while(size > 1);

}
