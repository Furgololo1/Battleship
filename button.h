#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class Button : public QPushButton
{

    QString name = "";
    QChar col = '0';
    int row = 0;
    bool isadded = false;

    QString normalbutton = "QPushButton{background-color: #FFFFFF;   border: 1px; border-color: #056DE3;   border-style: solid;  color: #000000;   padding: 15px 32px;    text-align: center;   text-decoration: none;    }";
   // QString normalbutton = "QPushButton{background-color: #FFFFFF;   border: 1px; border-color: #F44336;   border-style: solid;  color: #000000;   padding: 15px 32px;    text-align: center;   text-decoration: none;    }";
    QString hitbutton = "QPushButton{background-color: #FFFFFF;   border: 3px; border-color: #F44336;   border-style: solid;  color: #000000;   padding: 15px 32px;    text-align: center;   text-decoration: none;    }";

public:
    Button();
    ~Button(){};

    void SetName(QChar c, int r){
        name = c + QString::number(r);
        row = r;
        col = c;
    }

    QString GetName(){return name;}

    int GetCol(){return static_cast<int>(col.toLatin1());}

    int GetRow(){return row;}

    bool IsAdded(){return isadded;}

    void Add(bool state){ isadded = state;}

    bool bisclicked = false;

    bool bIsDestroyed = false;

    void Hit();
    void Miss();

    void Reset();

private:






};

#endif // BUTTON_H
