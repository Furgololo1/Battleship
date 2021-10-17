#ifndef BASE_H
#define BASE_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QPair>
#include <QLabel>
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
    void CreateEnemyButtons();

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

    int x = 10, y = 45;
    int buttonsize = 20;

    QString normalbutton = "QPushButton{background-color: #CB4335;   border: none;   color: white;   padding: 15px 32px;    text-align: center;   text-decoration: none;    }";

    QString shipsbutton = "QPushButton{background-color: #056DE3;   border: none;   color: white;   padding: 15px 32px;    text-align: center;   text-decoration: none;    }";


    //ships
    std::vector<ship *> *ships = nullptr;



    //vector of all buttons in game
    std::vector<std::vector<button *> > buttons;

    std::vector<std::vector<button *> > enemybuttons;

    std::vector<QLabel *> *labels = nullptr;




    //                              functions

    void CreateConnection(button *b);

    void AssignButtonToShip(button *b);

    void A(button *b);

    void CreateUI();





};
#endif // BASE_H
