#include "complexcalc.h"

#include<Qt3DExtras>

ComplexCalc::ComplexCalc(QWidget* parent)
  : QMainWindow(parent)
{

  // initialize Application window
  if (this->objectName().isEmpty())
    this->setObjectName("ComplexCalcClass");
  this->resize(1000, 750);
  QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  this->setSizePolicy(sizePolicy);

  // initialize centralWidget
  centralWidget = new QWidget(this);
  centralWidget->setObjectName("centralWidget");
  
  // define verticalLayout as Layout of centralWidget
  verticalLayout = new QVBoxLayout(centralWidget);
  verticalLayout->setContentsMargins(10, 10, 10, 10);
  verticalLayout->setSpacing(5);
  verticalLayout->setObjectName("verticalLayout");

  //initialize timeSlider as part of centralWidget
  timeSlider = new QSlider(centralWidget);
  timeSlider->setObjectName("timeSlider");
  timeSlider->setOrientation(Qt::Horizontal);
  
  // initialize subWidget as part of centralWidget
  subWidget = new QWidget(centralWidget);
  subWidget->setObjectName("subWidget");

  verticalLayout->addWidget(subWidget);
  verticalLayout->addWidget(timeSlider);

  // define gridLayout as Layout of subWidget
  gridLayout = new QGridLayout(subWidget);
  gridLayout->setContentsMargins(10, 10, 10, 10);
  gridLayout->setSpacing(5);
  gridLayout->setObjectName("gridLayout");

  // initialize addVarButton as part of subWidget
  addVarButton = new QPushButton(subWidget);
  addVarButton->setObjectName("addVarButton");
  addVarButton->setText(QCoreApplication::translate("ComplexCalc", "neue Variable", nullptr));
  QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
  sizePolicy1.setHorizontalStretch(0);
  sizePolicy1.setVerticalStretch(0);
  sizePolicy1.setHeightForWidth(addVarButton->sizePolicy().hasHeightForWidth());
  addVarButton->setSizePolicy(sizePolicy1);

  // initialize openGL3DWindow
  openGL3DWindow = new OpenGLWindow();

  // initialize the operationInput as part of subWidget
  operationInput = new QTextEdit(subWidget);
  operationInput->setObjectName("operationInput");
  QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
  sizePolicy2.setHorizontalStretch(0);
  sizePolicy2.setVerticalStretch(0);
  sizePolicy2.setHeightForWidth(operationInput->sizePolicy().hasHeightForWidth());
  operationInput->setSizePolicy(sizePolicy2);
  operationInput->setMaximumSize(QSize(INT_MAX, 20));
  operationInput->setInputMethodHints(Qt::ImhNone);
  operationInput->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  operationInput->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  operationInput->setLineWrapMode(QTextEdit::NoWrap);
  
  // initialize the listWidget as part of subWidget
  listWidget = new QListWidget(subWidget);
  listWidget->setObjectName("listWidget");
  QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
  sizePolicy3.setHorizontalStretch(0);
  sizePolicy3.setVerticalStretch(0);
  sizePolicy3.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
  listWidget->setSizePolicy(sizePolicy3);

  // add elements to gridLayout in subWidget
  gridLayout->addWidget(operationInput, 0, 0, 1, 1);
  gridLayout->addWidget(addVarButton, 0, 1, 1, 1);
  gridLayout->addWidget(QWidget::createWindowContainer(openGL3DWindow), 1, 0, 1, 1);
  gridLayout->addWidget(listWidget, 1, 1, 1, 1);

  this->setCentralWidget(centralWidget);

  QMetaObject::connectSlotsByName(this);
}

ComplexCalc::~ComplexCalc()
{
}
