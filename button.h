#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class button : public QPushButton
{

    QString name = "";
    QString row = "1";
    QChar col = 'A';



public:
    button();
    ~button(){};

    void SetName(QChar c, QString r){
        name = c + r;
        row = r;
        col = c;
    }
    QString GetName(){return name;}
    QChar GetCol(){return col;}
    QString GetRow(){return row;}

private:






};

#endif // BUTTON_H
