#include "ship.h"

ship::ship()
{
       //shipname = "basic";
       shipsize = 0;
}

bool ship::IsButtonAShip(int n)
{

   return false;

}


bool ship::AdditionValidation(button *b){

    delete buttons;

    return true;
}



bool ship::TryAddButtonToShip(button *b){



    if(shipvec.size() < 1){
           shipvec.push_back(b);
           DisconnectButton(b);
           shipsinfleet++;
           return true;
    }

    else{
            for(const auto & s : shipvec){

                /*if(shipvec.size() < 2){

                        if((b->GetRow() + 1 == s->GetRow() || b->GetRow() - 1 == s->GetRow()) && b->GetCol() == s->GetCol()){
                            shipvec.push_back(b);
                            std::sort(std::begin(shipblocks), std::end(shipblocks));
                            DisconnectButton(b);
                            return QPair<bool,bool>(true,true);
                        }

                        else if((b->GetCol() + 1 == s->GetCol() || b->GetCol() - 1 == s->GetCol()) && (b->GetRow() == s->GetRow())){
                            shipvec.push_back(b);
                            std::sort(std::begin(shipblocks), std::end(shipblocks));
                            DisconnectButton(b);
                            return QPair<bool,bool>(true,true);
                        }

                }*/

               //else{
                        if((b->GetCol() == s->GetCol()) && (b->GetRow() + 1 == s->GetRow() || b->GetRow() - 1 == s->GetRow())){
                                shipvec.push_back(b);
                                sortRow();
                                DisconnectButton(b);
                                shipsinfleet++;
                                return true;
                        }



                        else if((b->GetRow() == s->GetRow()) && (b->GetCol() + 1 == s->GetCol() || b->GetCol() - 1 == s->GetCol())){
                                shipvec.push_back(b);
                                sortCol();
                                DisconnectButton(b);
                                shipsinfleet++;
                                return true;
                        }


               }
            }
   // }

    return false;


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



void ship::sortRow(){

    int size = shipvec.size();

    do{
        for(int i = 1; i < size; i++){
            if(shipvec[i]->GetRow() < shipvec[i-1]->GetRow())
                std::swap(shipvec[i], shipvec[i-1]);
        }

        size--;
    }while(size > 1);

}



void ship::sortCol(){

    int size = shipvec.size();

    do{
        for(int i = 1; i < size; i++){
            if(shipvec[i]->GetCol() < shipvec[i-1]->GetCol())
                std::swap(shipvec[i], shipvec[i-1]);
        }

        size--;
    }while(size > 1);

}
