#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class button : public QPushButton
{

    QString name = "";
    QChar col = '0';
    int row = 0;
    bool isadded = false;

public:
    button();
    ~button(){};

    void SetName(QChar c, int r){
        name = c + QString::number(r);
        row = r;
        col = c;
    }

    QString GetName(){return name;}

    int GetCol(){return (int)col.toLatin1();}

    int GetRow(){return row;}

    bool IsAdded(){return isadded;}

    void Add(bool state){ isadded = state;}

    bool bisclicked = false;

private:






};

#endif // BUTTON_H
