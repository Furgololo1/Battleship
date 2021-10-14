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



bool ship::TryAddButtonToShip(int blocks){
    if(shipblocks.size() > 1){
        if(blocks%10 == n){
            shipblocks.push_back(blocks);
            std::sort(std::begin(shipblocks), std::end(shipblocks));
            return true;
        }
        else return false;
    }

    else{
        n = blocks%10;
        shipblocks.push_back(blocks);
        return true;
    }


    return true;
}
