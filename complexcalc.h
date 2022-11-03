#ifndef COMPLEXCALC_H
#define COMPLEXCALC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ComplexCalcUI; }
QT_END_NAMESPACE

class GLWindowControl;

class ComplexCalc : public QMainWindow
{
  Q_OBJECT

public:
  ComplexCalc(QWidget* parent = nullptr);
  ~ComplexCalc();

private:
  Ui::ComplexCalcUI* ui;
  GLWindowControl* mainGL;
};
#endif // COMPLEXCALC_H
