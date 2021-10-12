#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class button : public QPushButton
{

    int number = 0;


public:
    button();
    ~button(){};

    void SetName(int n){number = n;}
    int GetName(){return number;}

private:






};

#endif // BUTTON_H
