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

//TODO: Get OpenGL to run! Test in new Project: https://icode.best/i/61087846187635
