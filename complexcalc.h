#ifndef COMPLEXCALC_H
#define COMPLEXCALC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ComplexCalcClass; }
QT_END_NAMESPACE

class ComplexCalc : public QMainWindow
{
  Q_OBJECT

public:
  ComplexCalc(QWidget *parent = nullptr);
  ~ComplexCalc();

private:
  Ui::ComplexCalcClass *ui;
};
#endif // COMPLEXCALC_H
