#include "complexvar.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
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


  QPushButton* expandButton = new QPushButton(this);
  expandButton->setObjectName("expandButton");
  expandButton->setText("Expand");
  expandButton->setFixedHeight(24);
  QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy1.setHorizontalStretch(1);
  sizePolicy1.setHeightForWidth(expandButton->sizePolicy().hasHeightForWidth());
  expandButton->setSizePolicy(sizePolicy1);

  horizontalLayout1->addWidget(expandButton);


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

  horizontalLayout2->addWidget(nameInput);

  
  QLabel* input1Label = new QLabel(this);
  input1Label->setObjectName("input1Label");
  input1Label->setFixedSize(30, 24);
  input1Label->setText("Re");
  QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy3.setHeightForWidth(nameInput->sizePolicy().hasHeightForWidth());
  input1Label->setSizePolicy(sizePolicy3);

  horizontalLayout3->addWidget(input1Label);
}
