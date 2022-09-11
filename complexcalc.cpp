#include "complexcalc.h"
#include "./ui_complexcalc.h"

ComplexCalc::ComplexCalc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ComplexCalc)
{
    ui->setupUi(this);
}

ComplexCalc::~ComplexCalc()
{
    delete ui;
}

