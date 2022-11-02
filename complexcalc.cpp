#include "complexcalc.h"
#include "complexcalc_ui.h"

#include<Qt3DExtras>

ComplexCalc::ComplexCalc(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::ComplexCalcClass)
{
  ui->setupUi(this);

}

ComplexCalc::~ComplexCalc()
{
  delete ui;
}
