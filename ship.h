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

    ship(){};
    ship(std::vector<std::vector<Button *> > &tempButtons): buttons(&tempButtons){};
    ship(std::vector<std::vector<Button *> > &tempButtons, int i): buttons(&tempButtons), index(i){};

    ~ship(){shipvec.clear(); /*buttons->clear();*/}

    int GetIndex(){return index;}

    QPair<bool,bool> TryAddButtonToShip(Button *b);

    bool AdditionValidation();

    int GetShipsize(){return shipsinfleet;}

    int GetShipSize2(){return shipvec.size();}

    std::vector<Button *> *GetShipvec(){return &shipvec;}

    bool RemoveFromShip(Button *b);
    bool RemoveFromShip(QString &ship);
    void DestroyShip();

    void Merge(ship* s);

    void Destroy();


private:

    //ship components
    std::vector<Button *> shipvec;

    //temporary buttons for disconnecting
    std::vector<std::vector<Button *> > *buttons = nullptr;


    void sortRow();
    void sortCol();

    void DisableButton(Button *b);
    void EnableButtons(Button *b);


};

#endif // SHIP_H
