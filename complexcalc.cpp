#include "complexcalc.h"
#include "openglwindow.h"
#include "complexvar.h"

#include <Qt3DExtras>
#include <QVBoxLayout>
#include <QSlider>
#include <QPushButton>
#include <QLineEdit>
#include <QScrollArea>

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
  addVarButton->setMinimumSize(220, 0);
  QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy1.setHorizontalStretch(1);
  sizePolicy1.setVerticalStretch(0);
  sizePolicy1.setHeightForWidth(addVarButton->sizePolicy().hasHeightForWidth());
  addVarButton->setSizePolicy(sizePolicy1);

  // initialize openGL3DWindow
  openGL3DWindow = new OpenGLWindow();

  // initialize the operationInput as part of subWidget
  operationInput = new QLineEdit(subWidget);
  operationInput->setObjectName("operationInput");
  QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  operationInput->setFixedHeight(24);
  sizePolicy2.setHorizontalStretch(3);
  sizePolicy2.setVerticalStretch(0);
  sizePolicy2.setHeightForWidth(operationInput->sizePolicy().hasHeightForWidth());
  operationInput->setSizePolicy(sizePolicy2);
  operationInput->setMaximumSize(QSize(16777215, 20));  // 16777215 is Max
  operationInput->setPlaceholderText("Mathematical Operation");
  
  scrollWidget = new QWidget();
  scrollWidget->setObjectName("scrollWidget");
  QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  sizePolicy3.setHorizontalStretch(0);
  sizePolicy3.setVerticalStretch(0);
  sizePolicy3.setHeightForWidth(scrollWidget->sizePolicy().hasHeightForWidth());

  // define verticalScrollLayout as Layout of scrollWidget
  verticalScrollLayout = new QVBoxLayout(scrollWidget);
  verticalScrollLayout->setContentsMargins(0, 0, 0, 0);
  verticalScrollLayout->setSpacing(0);
  verticalScrollLayout->setObjectName("verticalScrollLayout");
  verticalScrollLayout->setAlignment(Qt::AlignTop);

  // initialize the scrollArea as part of subWidget
  scrollArea = new QScrollArea(subWidget);
  scrollArea->setObjectName("scrollArea");
  scrollArea->setMinimumSize(220, 0);
  QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  sizePolicy4.setHorizontalStretch(1);
  sizePolicy4.setVerticalStretch(0);
  sizePolicy4.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
  scrollArea->setSizePolicy(sizePolicy4);
  scrollArea->setWidgetResizable(true);
  scrollArea->setWidget(scrollWidget);

  // add elements to gridLayout in subWidget
  gridLayout->addWidget(operationInput, 0, 0, 1, 1);
  gridLayout->addWidget(addVarButton, 0, 1, 1, 1);
  gridLayout->addWidget(QWidget::createWindowContainer(openGL3DWindow), 1, 0, 1, 1);
  gridLayout->addWidget(scrollArea, 1, 1, 1, 1);

  this->setCentralWidget(centralWidget);

  QMetaObject::connectSlotsByName(this);
}

void ComplexCalc::on_addVarButton_clicked()
{
  ComplexVar* newVar = new ComplexVar(subWidget);

  verticalScrollLayout->addWidget(newVar);
}
