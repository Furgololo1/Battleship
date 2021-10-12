#include "ship.h"

ship::ship()
{
       shipname = "basic";
       shipsize = 0;
}

bool ship::IsButtonAShip(QString n)
{
    if(shipname == n)
        return true;

   return false;

}
