#include "complexcalc.h"
#include "complexcalc_ui.h"
#include "glwindowcontrol.h"

#include<Qt3DExtras>

ComplexCalc::ComplexCalc(QWidget* parent)
  : QMainWindow(parent)
  , ui_(new Ui::ComplexCalcUI)
{
  ui_->setupUi(this);

  mainGL_ = new GLWindowControl(ui_->openGL3DWindow);

}

ComplexCalc::~ComplexCalc()
{
  delete ui_;
}
