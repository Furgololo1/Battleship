#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class button : public QPushButton
{

    QString name = "";
    QString roww = "1";
    QChar col = 'A';
    int row = 0;
    bool isadded = false;


public:
    button();
    ~button(){};

    void SetName(QChar c, QString r){
        name = c + r;
        roww = r;
        col = c;
    }
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

private:






};

#endif // BUTTON_H
