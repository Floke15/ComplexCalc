#ifndef COMPLEXCALC_H
#define COMPLEXCALC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ComplexCalc; }
QT_END_NAMESPACE

class ComplexCalc : public QMainWindow
{
    Q_OBJECT

public:
    ComplexCalc(QWidget *parent = nullptr);
    ~ComplexCalc();

private:
    Ui::ComplexCalc *ui;
};
#endif // COMPLEXCALC_H
