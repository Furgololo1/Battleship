#include "ship.h"


ship::ship()
{
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
           DisableButton(b);
           shipsinfleet++;
           return QPair<bool,bool>(true,true);
    }

    else{
            for(const auto & s : shipvec){

                        if((b->GetCol() == s->GetCol()) && (b->GetRow() + 1 == s->GetRow() || b->GetRow() - 1 == s->GetRow())){
                                shipvec.push_back(b);
                                sortRow();
                                DisableButton(b);
                                shipsinfleet++;
                                return QPair<bool,bool>(true,true);
                        }



                        else if((b->GetRow() == s->GetRow()) && (b->GetCol() + 1 == s->GetCol() || b->GetCol() - 1 == s->GetCol())){
                                shipvec.push_back(b);
                                sortCol();
                                DisableButton(b);
                                shipsinfleet++;
                                return QPair<bool,bool>(true,true);
                        }


               }
            }

    return QPair<bool,bool>(false,false);


}


void ship::DisableButton(button *b){

        int x = b->GetRow()-2;
        int y = b->GetCol()%65-1;

         if((x >= 0 && x <= 9) && (y >= 0 && y <= 9))
            (*buttons)[x][y]->setDisabled(true);

         y += 2;

         if((x >= 0 && x <= 9) && (y >= 0 && y <= 9))
            (*buttons)[x][y]->setDisabled(true);

         x += 2;
         if((x >= 0 && x <= 9) && (y >= 0 && y <= 9))
            (*buttons)[x][y]->setDisabled(true);


         y -= 2;
         if((x >= 0 && x <= 9) && (y >= 0 && y <= 9))
            (*buttons)[x][y]->setDisabled(true);


}


void ship::EnableButtons(button *b){

    int x = b->GetRow()-2;
    int y = b->GetCol()%65-1;

     y += 2;

     x += 2;
     if((x >= 0 && x <= 9) && (y >= 0 && y <= 9))
        (*buttons)[x][y]->setDisabled(false);


     y -= 2;
     if((x >= 0 && x <= 9) && (y >= 0 && y <= 9))
        (*buttons)[x][y]->setDisabled(false);
}


bool ship::RemoveFromShip(button *b){

    QString normalbutton = "QPushButton{background-color: #FFFFFF;   border: 1px; border-color: #056DE3;   border-style: solid;   color: #000000;   padding: 15px 32px;    text-align: center;   text-decoration: none;    }";

    //this is iterator to remove if button exists in shipvec
    auto itr = std::find(shipvec.begin(), shipvec.end(), b);
    auto ittobuttons = itr;

    while(ittobuttons != shipvec.end()){
        (*ittobuttons)->bisclicked = false;
        (*ittobuttons)->setStyleSheet(normalbutton);
        EnableButtons(*ittobuttons);
        ittobuttons++;
        shipsinfleet--;

    }

    //qDebug()<<"size: "<<shipvec.size();


    shipvec.erase(itr, shipvec.end());

        b->bisclicked = false;
        b->setStyleSheet(normalbutton);

       // qDebug()<<"size: "<<shipvec.size();


    if(shipvec.size() == 0)
        return true;

    return false;
}

void ship::Merge(ship *ship)
{

        for(auto &s : *ship->GetShipvec()){
            if(!std::binary_search(shipvec.begin(), shipvec.end(), s))
                shipvec.push_back(std::move(s));
        }

        std::vector<button *>::iterator it = std::unique(shipvec.begin(), shipvec.end());

        shipvec.resize(std::distance(shipvec.begin(), it));

     //size od vector after merge vectors
        shipsinfleet = shipvec.size();


sortCol();
sortRow();
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
