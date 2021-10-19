#ifndef SHIP_H
#define SHIP_H



#include <QString>
#include <QPair>
#include <algorithm>
#include <vector>
#include <iostream>

#include "button.h"


class ship
{

    enum Layout{
        Horizontal,
        Vertical
    };


    //ship size
    int shipsize = 0;

    QString shipname = "basic";

    Layout layout;

    button *lastadded = nullptr;


    //counts ships in fleet of one player
  //  static int shipsinfleet = 0;

public:
    ship();
    ship(int size, QString name): shipsize(size), shipname(name){};
    ~ship(){};

    bool IsButtonAShip(int n);

    QString GetLayout(){if(layout == Layout::Horizontal) return "Horizontal";  return "Vertical";}

    QPair<bool, bool> TryAddButtonToShip(int blocks);
    QPair<bool, bool> TryAddButtonToShip(button *b);

    bool AdditionValidation(button *b);

  //  int GetShipName(){return shipname;}

    std::vector<int> *GetShipBlocks(){return &shipblocks;}
    std::vector<button *> *GetShipvec(){return &shipvec;}

    void RemoveLastAddedButton(){
        for(int i = 0; i < shipvec.size(); i++)
            if(shipvec[i] == lastadded)
                shipvec.erase(shipvec.begin() + i-1);

    };

private:

    //ship blocks
    std::vector<int> shipblocks;
    std::vector<button *> shipvec;


    void sortRow();
    void sortCol();


};

#endif // SHIP_H
