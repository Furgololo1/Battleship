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

    //ship size
    int shipsize = 0;

    //counts ships in fleet of one player
      int shipsinfleet = 0;

public:
    ship();
    ship(std::vector<std::vector<button *> > &tempbuttons): buttons(&tempbuttons){};
    //ship(int size, QString name,  std::vector<std::vector<button *> > &tempbuttons): shipsize(size), shipname(name), buttons(&tempbuttons){};
    ~ship(){delete buttons; shipvec.clear();}

    bool IsButtonAShip(int n);


    bool TryAddButtonToShip(button *b);

    bool AdditionValidation(button *b);

    int GetShipsize(){return shipsinfleet;}

    std::vector<button *> *GetShipvec(){return &shipvec;}

private:

    //ship components
    std::vector<button *> shipvec;

    //temporary buttons for disconnecting
    std::vector<std::vector<button *> > *buttons = nullptr;


    void sortRow();
    void sortCol();

    void DisconnectButton(button *b);


};

#endif // SHIP_H
