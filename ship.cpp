#include "ship.h"

ship::ship()
{
       shipname = "basic";
       shipsize = 0;
}

bool ship::IsButtonAShip(int n)
{
    //if(shipname == n)
        //return true;

   return false;

}


//33, 34, 35    40
QPair<bool, bool> ship::TryAddButtonToShip(int blocks){

    if(shipblocks.size() < 1){
           shipblocks.push_back(blocks);
           return QPair<bool,bool>(true,true);
    }

    else{
            for(const auto & s : shipblocks){

                     if((s + 10 == blocks || s - 10 == blocks || s - 1 == blocks || s + 1 == blocks) && shipblocks.size() < 2){
                            shipblocks.push_back(blocks);
                            std::sort(std::begin(shipblocks), std::end(shipblocks));
                            return QPair<bool,bool>(true,true);
                    }

                     else if((s + 10 == blocks || s - 10 == blocks || s - 1 == blocks || s + 1 == blocks) && shipblocks.size() >= 2){
                            if((int)(shipblocks[0] + ((shipblocks[1] - shipblocks[0]) * shipblocks.size())) == blocks){
                                 shipblocks.push_back(blocks);
                                 std::sort(std::begin(shipblocks), std::end(shipblocks));
                                 return QPair<bool,bool>(true,true);
                            }
                            else{
                                return QPair<bool,bool>(true,false);
                            }
                    }

                     else if (s + 10 + 1 == blocks || s + 10 - 1 == blocks || s - 10 + 1 == blocks || s - 10 - 1 == blocks) {
                         return QPair<bool,bool>(true, false);
                     }

            }
    }


    return QPair<bool,bool>(false,false);
}


bool ship::AdditionValidation(button *b){

    return true;
}



QPair<bool, bool> ship::TryAddButtonToShip(button *b){



    if(shipvec.size() < 1){
           shipvec.push_back(b);
           return QPair<bool,bool>(true,true);
    }

    else{
            for(const auto & s : shipvec){

                if(shipvec.size() < 2){

                        if((b->GetRow().toInt() + 1 == s->GetRow().toInt() || b->GetRow().toInt() - 1 == s->GetRow().toInt()) && b->GetCol() == s->GetCol()){
                            shipvec.push_back(b);
                            std::sort(std::begin(shipblocks), std::end(shipblocks));
                            layout = Layout::Vertical;
                            return QPair<bool,bool>(true,true);
                        }

                        else if(((int)b->GetCol().toLatin1() + 1 == (int)s->GetCol().toLatin1() || (int)b->GetCol().toLatin1() - 1 == (int)s->GetCol().toLatin1()) && (b->GetRow().toInt() == s->GetRow().toInt())){
                            shipvec.push_back(b);
                            std::sort(std::begin(shipblocks), std::end(shipblocks));
                            layout = Layout::Horizontal;
                            return QPair<bool,bool>(true,true);
                        }

                }

               else{//zaimplementowac algorytm z góry

                        if((b->GetCol() == s->GetCol()) && (b->GetRow().toInt() == shipvec[0]->GetRow().toInt() || b->GetRow().toInt() - 1 == shipvec[0]->GetRow().toInt())){
                            if((shipvec[0]->GetRow().toInt() + shipvec.size() == b->GetRow().toInt()) || (shipvec[0]->GetRow().toInt() - 1 == b->GetRow().toInt())){
                                shipvec.push_back(b);
                                std::sort(std::begin(shipblocks), std::end(shipblocks));
                                layout = Layout::Vertical;
                                return QPair<bool,bool>(true,true);
                            }
                            else return QPair<bool, bool>(true, false);
                        }

                        else if((b->GetRow().toInt() == s->GetRow().toInt()) && ((int)b->GetCol().toLatin1() + 1 == (int)s->GetCol().toLatin1() || (int)b->GetCol().toLatin1() - 1 == (int)s->GetCol().toLatin1())){
                            //if(b->GetCol().){
                                shipvec.push_back(b);
                                std::sort(std::begin(shipblocks), std::end(shipblocks));
                                layout = Layout::Horizontal;
                                return QPair<bool,bool>(true,true);
                            //}
                        }


               }

            }
    }

    return QPair<bool,bool>(false,false);


}
