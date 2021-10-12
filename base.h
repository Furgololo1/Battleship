#ifndef BASE_H
#define BASE_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <vector>


#include "button.h"
#include "ship.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Base; }
QT_END_NAMESPACE

class Base : public QMainWindow
{
    Q_OBJECT

public:
    Base(QWidget *parent = nullptr);
    ~Base();


    void CreateButtons();
public slots:


    void test(){
        buttons[0][0]->setStyleSheet(shipsbutton);
    };


private slots:
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

private:
    Ui::Base *ui;

    //size of
    int shipsize = 0;

    int x = 10, y = 10;
    int buttonsize = 20;

    QString normalbutton = "QPushButton{background-color: #BFCDE0;   border: none;   color: white;   padding: 15px 32px;    text-align: center;   text-decoration: none;    }";

    QString shipsbutton = "QPushButton{background-color: #056DE3;   border: none;   color: white;   padding: 15px 32px;    text-align: center;   text-decoration: none;    }";


    //ships
    std::vector<ship *> *ships = nullptr;



    //vector of all buttons in game
    std::vector<std::vector<button *> > buttons;




    //                              functions

    void CreateConnection(button *b);

    void AssignButtonToShip(button *b);





};
#endif // BASE_H
