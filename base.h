#ifndef BASE_H
#define BASE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Base; }
QT_END_NAMESPACE

class Base : public QMainWindow
{
    Q_OBJECT

public:
    Base(QWidget *parent = nullptr);
    ~Base();

private:
    Ui::Base *ui;
};
#endif // BASE_H
