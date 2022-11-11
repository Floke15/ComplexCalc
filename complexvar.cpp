#include "complexvar.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
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


  QPushButton* expandButton = new QPushButton(this);
  expandButton->setObjectName("expandButton");
  expandButton->setText("Expand");
  expandButton->setFixedHeight(24);
  QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy1.setHorizontalStretch(1);
  sizePolicy1.setHeightForWidth(expandButton->sizePolicy().hasHeightForWidth());
  expandButton->setSizePolicy(sizePolicy1);


  QTextEdit* nameInput = new QTextEdit(this);
  nameInput->setObjectName("nameInput");
  nameInput->setFixedHeight(24);
  nameInput->setPlaceholderText("Name");
  nameInput->setLineWrapMode(QTextEdit::NoWrap);
  nameInput->setInputMethodHints(Qt::ImhNone);
  nameInput->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  nameInput->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy2.setHorizontalStretch(1);
  sizePolicy2.setHeightForWidth(nameInput->sizePolicy().hasHeightForWidth());
  nameInput->setSizePolicy(sizePolicy2);

  
  QLabel* input1Label = new QLabel(this);
  input1Label->setObjectName("input1Label");
  input1Label->setFixedSize(30, 24);
  input1Label->setText("Re");
  QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy3.setHeightForWidth(nameInput->sizePolicy().hasHeightForWidth());
  input1Label->setSizePolicy(sizePolicy3);


  verticalLayout->addWidget(expandButton);
  verticalLayout->addWidget(nameInput);
  verticalLayout->addWidget(input1Label);
}
