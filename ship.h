#ifndef SHIP_H
#define SHIP_H



#include <QString>
#include <QPair>
#include <QDebug>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

#include "button.h"


class ship
{

    int index = 0;

    //counts buttons in one ship (vector)
    int shipsinfleet = 0;

public:

    ship();
    ship(std::vector<std::vector<button *> > &tempbuttons): buttons(&tempbuttons){};
    ship(std::vector<std::vector<button *> > &tempbuttons, int i): buttons(&tempbuttons), index(i){};

    ~ship(){delete buttons; shipvec.clear();}

    int GetIndex(){return index;}

    QPair<bool,bool> TryAddButtonToShip(button *b);

    bool AdditionValidation();

    int GetShipsize(){return shipsinfleet;}

    std::vector<button *> *GetShipvec(){return &shipvec;}

    bool RemoveFromShip(button *b);

    void Merge(ship* s);


private:

    //ship components
    std::vector<button *> shipvec;

    //temporary buttons for disconnecting
    std::vector<std::vector<button *> > *buttons = nullptr;


    void sortRow();
    void sortCol();

    void DisableButton(button *b);
    void EnableButtons(button *b);


};

#endif // SHIP_H
