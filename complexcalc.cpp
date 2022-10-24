#include "complexcalc.h"
#include "./ui_complexcalc.h"

ComplexCalc::ComplexCalc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ComplexCalcClass)
{
    ui->setupUi(this);
}

ComplexCalc::~ComplexCalc()
{
    delete ui;
}
