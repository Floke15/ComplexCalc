#include "complexvar.h"

#include <QPushButton>
#include <QGridLayout>

ComplexVar::ComplexVar(QWidget* parent, std::string name, std::complex<double> value, double omega, double phi, QColor color) :
  parent_(parent),
  name_(name),
  value_(value),
  omega_(omega),
  phi_(phi),
  color_(color)
{
  this->setObjectName("newVariable");
  this->setMinimumSize(200, 50);
  QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
  

  QGridLayout* gridLayout = new QGridLayout(this);
  gridLayout->setContentsMargins(10, 10, 10, 10);
  gridLayout->setSpacing(5);
  gridLayout->setObjectName("VarGridLayout");


  QPushButton* newButton = new QPushButton(this);
  newButton->setObjectName("newVarButton");
  newButton->setText("test");
  newButton->setMinimumSize(0, 20);
  QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy1.setHeightForWidth(newButton->sizePolicy().hasHeightForWidth());
  newButton->setSizePolicy(sizePolicy1);

  gridLayout->addWidget(newButton, 0, 0, 0, 0);
}
