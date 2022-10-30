#include "complexcalc.h"
#include "./ui_complexcalc.h"

#include<Qt3DExtras>

ComplexCalc::ComplexCalc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ComplexCalcClass)
{
    ui->setupUi(this);
    QHBoxLayout* const layout = new QHBoxLayout(ui->widget);
    Qt3DExtras::Qt3DWindow* view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    layout->addWidget(QWidget::createWindowContainer(view));
}

ComplexCalc::~ComplexCalc()
{
    delete ui;
}
