#ifndef SHIP_H
#define SHIP_H

#include <QString>

#include <vector>



class ship
{
    //ship size
    int shipsize = 0;

    QString shipname = "basic";

    //counts ships in fleet of one player
  //  static int shipsinfleet = 0;

public:
    ship();
    ship(int size, QString name): shipsize(size), shipname(name){};
    ~ship(){};

    bool IsButtonAShip(QString n);

    void AddButtonToShip(QString blocks){  shipblocks.push_back(blocks);  }

    QString GetShipName(){return shipname;}

    std::vector<QString> *GetShipBlocks(){return &shipblocks;}

private:

    //ship blocks
    std::vector<QString> shipblocks;


};

#endif // SHIP_H
