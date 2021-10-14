#ifndef SHIP_H
#define SHIP_H

#include <QString>
#include <algorithm>
#include <vector>



class ship
{
    //ship size
    int shipsize = 0;

    int n = 0;

    QString shipname = "basic";

    //counts ships in fleet of one player
  //  static int shipsinfleet = 0;

public:
    ship();
    ship(int size, QString name): shipsize(size), shipname(name){};
    ~ship(){};

    bool IsButtonAShip(int n);

    bool TryAddButtonToShip(int blocks);

    bool AdditionValidation(int s);

  //  int GetShipName(){return shipname;}

    std::vector<int> *GetShipBlocks(){return &shipblocks;}

private:

    //ship blocks
    std::vector<int> shipblocks;


};

#endif // SHIP_H
