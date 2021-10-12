#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class button : public QPushButton
{

    QString name = "basic";


public:
    button();
    ~button(){};

    void SetName(QString n){name = n;}
    QString GetName(){return name;}

private:






};

#endif // BUTTON_H
