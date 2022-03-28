#include "button.h"

Button::Button()
{

}


void Button::Hit()
{
    if(!bIsDestroyed)
        this->setStyleSheet(hitbutton);
}


void Button::Miss()
{
    this->setText("X");
}


void Button::Reset()
{
    this->setStyleSheet(normalbutton);
    bisclicked = false;
    bIsDestroyed = false;
    isadded = false;
    //name.clear();
    this->setText("");
//    this->setDisabled(false);

}
