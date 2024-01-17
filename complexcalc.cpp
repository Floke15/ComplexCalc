#include "complexcalc.h"
#include "openglwindow.h"
#include "complexvar.h"
#include "scrollwidget.h"

#include <Qt3DExtras>
#include <QVBoxLayout>
#include <QSlider>
#include <QPushButton>
#include <QLineEdit>
#include <QScrollArea>

ComplexCalc::ComplexCalc(QWidget* parent) :
  QMainWindow(parent)
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
  centralWidget_ = new QWidget(this);
  centralWidget_->setObjectName("centralWidget");
  
  // define verticalLayout as Layout of centralWidget
  verticalLayout_ = new QVBoxLayout(centralWidget_);
  verticalLayout_->setContentsMargins(10, 10, 10, 10);
  verticalLayout_->setSpacing(5);
  verticalLayout_->setObjectName("verticalLayout");

  //initialize timeSlider as part of centralWidget
  timeSlider_ = new QSlider(centralWidget_);
  timeSlider_->setObjectName("timeSlider");
  timeSlider_->setOrientation(Qt::Horizontal);
  
  // initialize subWidget as part of centralWidget
  subWidget_ = new QWidget(centralWidget_);
  subWidget_->setObjectName("subWidget");

  verticalLayout_->addWidget(subWidget_);
  verticalLayout_->addWidget(timeSlider_);

  // define gridLayout as Layout of subWidget
  gridLayout_ = new QGridLayout(subWidget_);
  gridLayout_->setContentsMargins(10, 10, 10, 10);
  gridLayout_->setSpacing(5);
  gridLayout_->setObjectName("gridLayout");

  // initialize addVarButton as part of subWidget
  addVarButton_ = new QPushButton(subWidget_);
  addVarButton_->setObjectName("addVarButton");
  addVarButton_->setText(QCoreApplication::translate("ComplexCalc", "neue Variable", nullptr));
  addVarButton_->setMinimumSize(220, 0);
  QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy1.setHorizontalStretch(1);
  sizePolicy1.setVerticalStretch(0);
  sizePolicy1.setHeightForWidth(addVarButton_->sizePolicy().hasHeightForWidth());
  addVarButton_->setSizePolicy(sizePolicy1);

  // initialize openGL3DWindow
  openGL3DWindow_ = new OpenGLWindow(true);

  // initialize the operationInput as part of subWidget
  operationInput_ = new QLineEdit(subWidget_);
  operationInput_->setObjectName("operationInput");
  QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  operationInput_->setFixedHeight(24);
  sizePolicy2.setHorizontalStretch(3);
  sizePolicy2.setVerticalStretch(0);
  sizePolicy2.setHeightForWidth(operationInput_->sizePolicy().hasHeightForWidth());
  operationInput_->setSizePolicy(sizePolicy2);
  operationInput_->setMaximumSize(QSize(16777215, 20));  // 16777215 is Max
  operationInput_->setPlaceholderText("Mathematical Operation");
  QRegularExpressionValidator* regex_validator = new QRegularExpressionValidator(QRegularExpression("[a-zA-Z0-9 ]*"));   //match one word (aka one potential variable)
  operationInput_->setValidator(regex_validator);
  
  scrollWidget_ = new ScrollWidget(subWidget_);
  scrollWidget_->setObjectName("scrollWidget");
  QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  sizePolicy3.setHorizontalStretch(0);
  sizePolicy3.setVerticalStretch(0);
  sizePolicy3.setHeightForWidth(scrollWidget_->sizePolicy().hasHeightForWidth());
  connect(scrollWidget_, &ScrollWidget::about_to_delete, openGL3DWindow_, &OpenGLWindow::removeAllVariables);
  connect(scrollWidget_, &ScrollWidget::variable_deleted, this, &ComplexCalc::reparseText);

  // define verticalScrollLayout as Layout of scrollWidget
  verticalScrollLayout_ = new QVBoxLayout(scrollWidget_);
  verticalScrollLayout_->setContentsMargins(0, 0, 0, 0);
  verticalScrollLayout_->setSpacing(0);
  verticalScrollLayout_->setObjectName("verticalScrollLayout");
  verticalScrollLayout_->setAlignment(Qt::AlignTop);

  // initialize the scrollArea as part of subWidget
  scrollArea_ = new QScrollArea(subWidget_);
  scrollArea_->setObjectName("scrollArea");
  scrollArea_->setMinimumSize(220, 0);
  QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  sizePolicy4.setHorizontalStretch(1);
  sizePolicy4.setVerticalStretch(0);
  sizePolicy4.setHeightForWidth(scrollArea_->sizePolicy().hasHeightForWidth());
  scrollArea_->setSizePolicy(sizePolicy4);
  scrollArea_->setWidgetResizable(true);
  scrollArea_->setWidget(scrollWidget_);

  // add elements to gridLayout in subWidget
  gridLayout_->addWidget(operationInput_, 0, 0, 1, 1);
  gridLayout_->addWidget(addVarButton_, 0, 1, 1, 1);
  gridLayout_->addWidget(QWidget::createWindowContainer(openGL3DWindow_), 1, 0, 1, 1);
  gridLayout_->addWidget(scrollArea_, 1, 1, 1, 1);

  this->setCentralWidget(centralWidget_);

  QMetaObject::connectSlotsByName(this);

  OpenGLWindow* openGL3DWindow = new OpenGLWindow(false);
  QWidget* fixWidget = QWidget::createWindowContainer(openGL3DWindow);
  QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
  fixWidget->setMinimumSize(1, 1);
  //fixWidget->setVisible(false);
  fixWidget->setSizePolicy(sizePolicy5);
  verticalScrollLayout_->addWidget(fixWidget);
}

void ComplexCalc::on_operationInput_textEdited(const QString& text)
{
  operationInput_->setText(operationInput_->text().toUpper());

  if (operationInput_->text().isEmpty())
  {
    openGL3DWindow_->removeAllVariables();
    return;
  }

  //TODO: implement parsing and calculation of calculations

  std::vector<ComplexVar*> variables;
  QString input = operationInput_->text();

  for (auto var_iter : scrollWidget_->variables_)
  {
      QString regex_str = "(^" + var_iter->getName() + "$)|(^" + var_iter->getName() + " .*$)|(^.* " + var_iter->getName() + " .*$)|(^.* " + var_iter->getName() + "$)";
      QRegularExpressionValidator* regex_validator = new QRegularExpressionValidator(QRegularExpression(regex_str));
    int pos = 0;

    if (int t = regex_validator->validate(input, pos) == 2)
     variables.push_back(var_iter);

    delete regex_validator;
  }

  openGL3DWindow_->removeAllVariables();

  for (auto var_iter : variables)
    openGL3DWindow_->insertVariable(var_iter);
}

void ComplexCalc::reparseText()
{
  on_operationInput_textEdited(operationInput_->text());
}

void ComplexCalc::clearMainWindow()
{
  openGL3DWindow_->removeAllVariables();
}

void ComplexCalc::on_addVarButton_clicked()
{
  ComplexVar* newVar = new ComplexVar(scrollWidget_);
  scrollWidget_->layout()->addWidget(newVar);
  scrollWidget_->variables_.push_back(newVar);

  connect(newVar, &ComplexVar::variable_name_changed, this, &ComplexCalc::reparseText);
}
