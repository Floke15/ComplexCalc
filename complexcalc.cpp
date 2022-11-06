#include "complexcalc.h"
#include "complexcalc_ui.h"

#include<Qt3DExtras>

ComplexCalc::ComplexCalc(QWidget* parent)
  : QMainWindow(parent)
  , ui_(new Ui::ComplexCalcUI)
{
  ui_->setupUi(this);
}

ComplexCalc::~ComplexCalc()
{
  delete ui_;
}
