#ifndef COMPLEXCALC_H
#define COMPLEXCALC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ComplexCalcUI; }
QT_END_NAMESPACE

class OpenGLWindow;

class ComplexCalc : public QMainWindow
{
  Q_OBJECT

public:
  ComplexCalc(QWidget* parent = nullptr);
  ~ComplexCalc();

private:
  Ui::ComplexCalcUI* ui_;
  OpenGLWindow* mainGL_;
};
#endif // COMPLEXCALC_H
