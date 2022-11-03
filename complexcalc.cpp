#include "complexcalc.h"
#include "complexcalc_ui.h"
#include "glwindowcontrol.h"

#include<Qt3DExtras>

ComplexCalc::ComplexCalc(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::ComplexCalcUI)
{
  ui->setupUi(this);

  mainGL = new GLWindowControl(ui->openGL3DWindow);

}

ComplexCalc::~ComplexCalc()
{
  delete ui;
}
