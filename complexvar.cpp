#include "complexvar.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>

ComplexVar::ComplexVar(QWidget* parent, std::string name, std::complex<double> value, double omega, QColor color) :
  parent_(parent),
  name_(name),
  value_(value),
  omega_(omega),
  color_(color)
{
  this->setObjectName("newVariable");
  this->setMinimumSize(200, 72);
  this->setFrameShape(QFrame::StyledPanel);
  //this->setMidLineWidth(1);
  QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
  

  QVBoxLayout* verticalLayout = new QVBoxLayout(this);
  verticalLayout->setContentsMargins(0, 0, 0, 0);
  verticalLayout->setSpacing(0);
  verticalLayout->setObjectName("VarVerticalLayout");
  verticalLayout->setAlignment(Qt::AlignTop);


  QWidget* horizontalWidget1 = new QWidget(this);
  horizontalWidget1->setObjectName("horizontalWidget1");
  horizontalWidget1->setFixedHeight(24);
  QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy4.setHeightForWidth(horizontalWidget1->sizePolicy().hasHeightForWidth());
  horizontalWidget1->setSizePolicy(sizePolicy4);

  QWidget* horizontalWidget2 = new QWidget(this);
  horizontalWidget2->setObjectName("horizontalWidget2");
  horizontalWidget2->setFixedHeight(24);
  horizontalWidget2->setSizePolicy(sizePolicy4);

  QWidget* horizontalWidget3 = new QWidget(this);
  horizontalWidget2->setObjectName("horizontalWidget2");
  horizontalWidget2->setFixedHeight(24);
  horizontalWidget2->setSizePolicy(sizePolicy4);

  verticalLayout->addWidget(horizontalWidget1);
  verticalLayout->addWidget(horizontalWidget2);
  verticalLayout->addWidget(horizontalWidget3);


  QHBoxLayout* horizontalLayout1 = new QHBoxLayout(horizontalWidget1);
  horizontalLayout1->setContentsMargins(0, 0, 0, 0);
  horizontalLayout1->setSpacing(0);
  horizontalLayout1->setObjectName("horizontalLayout1");
  horizontalLayout1->setAlignment(Qt::AlignLeft);

  QHBoxLayout* horizontalLayout2 = new QHBoxLayout(horizontalWidget2);
  horizontalLayout2->setContentsMargins(0, 0, 0, 0);
  horizontalLayout2->setSpacing(0);
  horizontalLayout2->setObjectName("horizontalLayout2");
  horizontalLayout2->setAlignment(Qt::AlignLeft);

  QHBoxLayout* horizontalLayout3 = new QHBoxLayout(horizontalWidget3);
  horizontalLayout3->setContentsMargins(0, 0, 0, 0);
  horizontalLayout3->setSpacing(0);
  horizontalLayout3->setObjectName("horizontalLayout3");
  horizontalLayout3->setAlignment(Qt::AlignLeft);


  QPushButton* expandButton = new QPushButton(horizontalWidget1);
  expandButton->setObjectName("expandButton");
  expandButton->setText("Expand");
  expandButton->setFixedHeight(24);
  QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy1.setHorizontalStretch(1);
  sizePolicy1.setHeightForWidth(expandButton->sizePolicy().hasHeightForWidth());
  expandButton->setSizePolicy(sizePolicy1);

  QPushButton* switchButton = new QPushButton(horizontalWidget1);
  switchButton->setObjectName("switchButton");
  switchButton->setText("Euler");
  switchButton->setFixedHeight(24);
  switchButton->setSizePolicy(sizePolicy1);

  QPushButton* deleteButton = new QPushButton(horizontalWidget1);
  deleteButton->setObjectName("deleteButton");
  deleteButton->setText("-");
  deleteButton->setFixedSize(20, 20);
  deleteButton->setStyleSheet("border: 1px; background-color: rgb(196, 43, 28)");
  QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy5.setHorizontalStretch(0);
  sizePolicy5.setHeightForWidth(deleteButton->sizePolicy().hasHeightForWidth());
  deleteButton->setSizePolicy(sizePolicy5);

  horizontalLayout1->addWidget(expandButton);
  horizontalLayout1->addWidget(switchButton);
  horizontalLayout1->addWidget(deleteButton);


  QLineEdit* nameInput = new QLineEdit(this);
  nameInput->setObjectName("nameInput");
  nameInput->setFixedHeight(24);
  nameInput->setPlaceholderText("Name");
  QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy2.setHorizontalStretch(1);
  sizePolicy2.setHeightForWidth(nameInput->sizePolicy().hasHeightForWidth());
  nameInput->setSizePolicy(sizePolicy2);

  QWidget* omegaSubWidget = new QWidget();
  omegaSubWidget->setObjectName("omegaSubWidget");
  omegaSubWidget->setFixedHeight(24);
  QSizePolicy sizePolicy6(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy6.setHorizontalStretch(1);
  sizePolicy6.setHeightForWidth(omegaSubWidget->sizePolicy().hasHeightForWidth());
  omegaSubWidget->setSizePolicy(sizePolicy6);

  horizontalLayout2->addWidget(nameInput);
  horizontalLayout2->addWidget(omegaSubWidget);

  QHBoxLayout* horizontalLayoutOmega = new QHBoxLayout(omegaSubWidget);
  horizontalLayoutOmega->setContentsMargins(0, 0, 0, 0);
  horizontalLayoutOmega->setSpacing(0);
  horizontalLayoutOmega->setObjectName("omegaSubWidget");
  horizontalLayoutOmega->setAlignment(Qt::AlignLeft);

  QLabel* omegaLabel = new QLabel(omegaSubWidget);
  omegaLabel->setObjectName("omegaLabel");
  omegaLabel->setFixedSize(20, 24);
  omegaLabel->setText("ω:");
  omegaLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  QSizePolicy sizePolicy7(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy7.setHeightForWidth(omegaLabel->sizePolicy().hasHeightForWidth());
  omegaLabel->setSizePolicy(sizePolicy7);

  QLineEdit* omegaInput = new QLineEdit(this);
  omegaInput->setObjectName("nameInput");
  omegaInput->setFixedHeight(24);
  QSizePolicy sizePolicy8(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy8.setHeightForWidth(nameInput->sizePolicy().hasHeightForWidth());
  omegaInput->setSizePolicy(sizePolicy8);

  horizontalLayoutOmega->addWidget(omegaLabel);
  horizontalLayoutOmega->addWidget(omegaInput);

  
  QWidget* varSubWidget1 = new QWidget();
  varSubWidget1->setObjectName("varSubWidget1");
  varSubWidget1->setFixedHeight(24);
  QSizePolicy sizePolicy10(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy10.setHorizontalStretch(1);
  sizePolicy10.setHeightForWidth(varSubWidget1->sizePolicy().hasHeightForWidth());
  varSubWidget1->setSizePolicy(sizePolicy10);

  QWidget* varSubWidget2 = new QWidget();
  varSubWidget2->setObjectName("varSubWidget2");
  varSubWidget2->setFixedHeight(24);
  varSubWidget2->setSizePolicy(sizePolicy10);

  horizontalLayout3->addWidget(varSubWidget1);
  horizontalLayout3->addWidget(varSubWidget2);

  QHBoxLayout* horizontalLayoutInput1 = new QHBoxLayout(varSubWidget1);
  horizontalLayoutInput1->setContentsMargins(0, 0, 0, 0);
  horizontalLayoutInput1->setSpacing(0);
  horizontalLayoutInput1->setObjectName("horizontalLayoutInput1");
  horizontalLayoutInput1->setAlignment(Qt::AlignLeft);

  QLabel* input1Label = new QLabel(this);
  input1Label->setObjectName("input1Label");
  input1Label->setFixedSize(20, 24);
  input1Label->setText("Re:");
  input1Label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy3.setHeightForWidth(nameInput->sizePolicy().hasHeightForWidth());
  input1Label->setSizePolicy(sizePolicy3);

  QLineEdit* input1Input = new QLineEdit(this);
  input1Input->setObjectName("input1Input");
  input1Input->setFixedHeight(24);
  QSizePolicy sizePolicy11(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy11.setHeightForWidth(input1Input->sizePolicy().hasHeightForWidth());
  input1Input->setSizePolicy(sizePolicy11);

  horizontalLayoutInput1->addWidget(input1Label);
  horizontalLayoutInput1->addWidget(input1Input);

  QHBoxLayout* horizontalLayoutInput2 = new QHBoxLayout(varSubWidget2);
  horizontalLayoutInput2->setContentsMargins(0, 0, 0, 0);
  horizontalLayoutInput2->setSpacing(0);
  horizontalLayoutInput2->setObjectName("horizontalLayoutInput2");
  horizontalLayoutInput2->setAlignment(Qt::AlignLeft);

  QLabel* input2Label = new QLabel(this);
  input2Label->setObjectName("input2Label");
  input2Label->setFixedSize(20, 24);
  input2Label->setText("Im:");
  input2Label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  input1Label->setSizePolicy(sizePolicy3);

  QLineEdit* input2Input = new QLineEdit(this);
  input2Input->setObjectName("input2Input");
  input2Input->setFixedHeight(24);
  input1Input->setSizePolicy(sizePolicy11);

  horizontalLayoutInput2->addWidget(input2Label);
  horizontalLayoutInput2->addWidget(input2Input);
}
