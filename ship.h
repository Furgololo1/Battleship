#ifndef SHIP_H
#define SHIP_H



#include <QString>
#include <QPair>
#include <algorithm>
#include <vector>

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


    //counts ships in fleet of one player
  //  static int shipsinfleet = 0;

public:
    ship();
    ship(int size, QString name): shipsize(size), shipname(name){};
    ~ship(){};

    bool IsButtonAShip(int n);

    QPair<bool, bool> TryAddButtonToShip(int blocks);
    QPair<bool, bool> TryAddButtonToShip(button *b);

    bool AdditionValidation(button *b);

  //  int GetShipName(){return shipname;}

    std::vector<int> *GetShipBlocks(){return &shipblocks;}
    std::vector<button *> *GetShipvec(){return &shipvec;}

private:

    //ship blocks
    std::vector<int> shipblocks;
    std::vector<button *> shipvec;


};

#endif // SHIP_H
