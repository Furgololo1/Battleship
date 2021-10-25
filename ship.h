#ifndef SHIP_H
#define SHIP_H



#include <QString>
#include <QPair>
#include <QDebug>
#include <algorithm>
#include <vector>
#include <iostream>

#include "button.h"


class ship
{

    int index = 0;

    //ship size
    int shipsize = 0;

    //counts ships in fleet of one player
    int shipsinfleet = 0;

public:

    ship();
    ship(std::vector<std::vector<button *> > &tempbuttons): buttons(&tempbuttons){};
    ship(std::vector<std::vector<button *> > &tempbuttons, int i): buttons(&tempbuttons), index(i){};

    ~ship(){delete buttons; shipvec.clear();}

    bool IsButtonAShip(int n);

    int GetIndex(){return index;}

    QPair<bool,bool> TryAddButtonToShip(button *b);

    bool AdditionValidation(button *b);

    int GetShipsize(){return shipsinfleet;}

    std::vector<button *> *GetShipvec(){return &shipvec;}

    bool RemoveFromShip(button *b);

    static std::vector<int> shipssize;
    static std::vector<int> shipsamount;

private:

    //ship components
    std::vector<button *> shipvec;

    //temporary buttons for disconnecting
    std::vector<std::vector<button *> > *buttons = nullptr;


    void sortRow();
    void sortCol();

    void DisconnectButton(button *b);

    //this function check if there is 1 ship with size 4, 2x3, 3x2, 4x1, if amount of ships is max then function
    //return false and doesn't add new button to ship. True means that user can add new button to ship.
    bool CheckAmountOfShips(int shipsizetoadd);


};

#endif // SHIP_H
