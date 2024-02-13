#include "complexvar.h"
#include "scrollwidget.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDoubleValidator>
#include <QSlider>
#include <math.h>

ComplexVar::ComplexVar(QWidget* parent, QSlider* timeSlider, QString name, std::complex<double> value, double omega, QColor color) :
  parent_(parent),
  name_(name),
  timeSlider_(timeSlider),
  value_(value),
  omega_(omega),
  color_(color),
  input_is_euler_(false)
{
  this->setObjectName("newVariable");
  this->setMinimumSize(200, 72);
  this->setFrameShape(QFrame::StyledPanel);
  //this->setMidLineWidth(1);
  QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());

  verticalLayout_ = new QVBoxLayout(this);
  verticalLayout_->setContentsMargins(0, 0, 0, 0);
  verticalLayout_->setSpacing(0);
  verticalLayout_->setObjectName("VarVerticalLayout");
  verticalLayout_->setAlignment(Qt::AlignTop);


  horizontalWidget1_ = new QWidget(this);
  horizontalWidget1_->setObjectName("horizontalWidget1");
  horizontalWidget1_->setFixedHeight(24);
  QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy4.setHeightForWidth(horizontalWidget1_->sizePolicy().hasHeightForWidth());
  horizontalWidget1_->setSizePolicy(sizePolicy4);

  horizontalWidget2_ = new QWidget(this);
  horizontalWidget2_->setObjectName("horizontalWidget2");
  horizontalWidget2_->setFixedHeight(24);
  horizontalWidget2_->setSizePolicy(sizePolicy4);

  horizontalWidget3_ = new QWidget(this);
  horizontalWidget3_->setObjectName("horizontalWidget3");
  horizontalWidget3_->setFixedHeight(24);
  horizontalWidget3_->setSizePolicy(sizePolicy4);

  verticalLayout_->addWidget(horizontalWidget1_);
  verticalLayout_->addWidget(horizontalWidget2_);
  verticalLayout_->addWidget(horizontalWidget3_);


  horizontalLayout1_ = new QHBoxLayout(horizontalWidget1_);
  horizontalLayout1_->setContentsMargins(0, 0, 0, 0);
  horizontalLayout1_->setSpacing(0);
  horizontalLayout1_->setObjectName("horizontalLayout1");
  horizontalLayout1_->setAlignment(Qt::AlignLeft);

  horizontalLayout2_ = new QHBoxLayout(horizontalWidget2_);
  horizontalLayout2_->setContentsMargins(0, 0, 0, 0);
  horizontalLayout2_->setSpacing(0);
  horizontalLayout2_->setObjectName("horizontalLayout2");
  horizontalLayout2_->setAlignment(Qt::AlignLeft);

  horizontalLayout3_ = new QHBoxLayout(horizontalWidget3_);
  horizontalLayout3_->setContentsMargins(0, 0, 0, 0);
  horizontalLayout3_->setSpacing(0);
  horizontalLayout3_->setObjectName("horizontalLayout3");
  horizontalLayout3_->setAlignment(Qt::AlignLeft);


  expandButton_ = new QPushButton(horizontalWidget1_);
  expandButton_->setObjectName("expandButton");
  expandButton_->setText("Expand");
  expandButton_->setFixedHeight(24);
  QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy1.setHorizontalStretch(1);
  sizePolicy1.setHeightForWidth(expandButton_->sizePolicy().hasHeightForWidth());
  expandButton_->setSizePolicy(sizePolicy1);

  switchButton_ = new QPushButton(horizontalWidget1_);
  switchButton_->setObjectName("switchButton");
  switchButton_->setText("Euler");
  switchButton_->setFixedHeight(24);
  switchButton_->setSizePolicy(sizePolicy1);

  deleteButton_ = new QPushButton(horizontalWidget1_);
  deleteButton_->setObjectName("deleteButton");
  deleteButton_->setText("X");
  deleteButton_->setFixedSize(20, 20);
  deleteButton_->setStyleSheet("border: 1px; background-color: rgb(196, 43, 28)");
  QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy5.setHorizontalStretch(0);
  sizePolicy5.setHeightForWidth(deleteButton_->sizePolicy().hasHeightForWidth());
  deleteButton_->setSizePolicy(sizePolicy5);

  horizontalLayout1_->addWidget(expandButton_);
  horizontalLayout1_->addWidget(switchButton_);
  horizontalLayout1_->addWidget(deleteButton_);

  QRegularExpressionValidator* var_validator = new QRegularExpressionValidator(QRegularExpression("[a-zA-Z0-9]*"));

  nameInput_ = new QLineEdit(this);
  nameInput_->setObjectName("nameInput");
  nameInput_->setFixedHeight(24);
  nameInput_->setPlaceholderText("Name");
  QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy2.setHorizontalStretch(1);
  sizePolicy2.setHeightForWidth(nameInput_->sizePolicy().hasHeightForWidth());
  nameInput_->setSizePolicy(sizePolicy2);
  nameInput_->setValidator(var_validator);

  omegaSubWidget_ = new QWidget();
  omegaSubWidget_->setObjectName("omegaSubWidget");
  omegaSubWidget_->setFixedHeight(24);
  QSizePolicy sizePolicy6(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy6.setHorizontalStretch(1);
  sizePolicy6.setHeightForWidth(omegaSubWidget_->sizePolicy().hasHeightForWidth());
  omegaSubWidget_->setSizePolicy(sizePolicy6);

  horizontalLayout2_->addWidget(nameInput_);
  horizontalLayout2_->addWidget(omegaSubWidget_);

  horizontalLayoutOmega_ = new QHBoxLayout(omegaSubWidget_);
  horizontalLayoutOmega_->setContentsMargins(0, 0, 0, 0);
  horizontalLayoutOmega_->setSpacing(0);
  horizontalLayoutOmega_->setObjectName("omegaSubWidget");
  horizontalLayoutOmega_->setAlignment(Qt::AlignLeft);

  omegaLabel_ = new QLabel(omegaSubWidget_);
  omegaLabel_->setObjectName("omegaLabel");
  omegaLabel_->setFixedSize(20, 24);
  omegaLabel_->setText("ω:");
  omegaLabel_->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  QSizePolicy sizePolicy7(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy7.setHeightForWidth(omegaLabel_->sizePolicy().hasHeightForWidth());
  omegaLabel_->setSizePolicy(sizePolicy7);

  omegaInput_ = new QLineEdit(this);
  omegaInput_->setObjectName("omegaInput");
  omegaInput_->setFixedHeight(24);
  QSizePolicy sizePolicy8(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy8.setHeightForWidth(nameInput_->sizePolicy().hasHeightForWidth());
  omegaInput_->setSizePolicy(sizePolicy8);
  QDoubleValidator* double_validator = new QDoubleValidator();
  double_validator->setNotation(QDoubleValidator::ScientificNotation);
  omegaInput_->setValidator(double_validator);
  omegaInput_->setText(QString::number(omega_));

  horizontalLayoutOmega_->addWidget(omegaLabel_);
  horizontalLayoutOmega_->addWidget(omegaInput_);

  
  varSubWidget1_ = new QWidget();
  varSubWidget1_->setObjectName("varSubWidget1");
  varSubWidget1_->setFixedHeight(24);
  QSizePolicy sizePolicy10(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy10.setHorizontalStretch(1);
  sizePolicy10.setHeightForWidth(varSubWidget1_->sizePolicy().hasHeightForWidth());
  varSubWidget1_->setSizePolicy(sizePolicy10);

  varSubWidget2_ = new QWidget();
  varSubWidget2_->setObjectName("varSubWidget2");
  varSubWidget2_->setFixedHeight(24);
  varSubWidget2_->setSizePolicy(sizePolicy10);

  horizontalLayout3_->addWidget(varSubWidget1_);
  horizontalLayout3_->addWidget(varSubWidget2_);

  horizontalLayoutInput1_ = new QHBoxLayout(varSubWidget1_);
  horizontalLayoutInput1_->setContentsMargins(0, 0, 0, 0);
  horizontalLayoutInput1_->setSpacing(0);
  horizontalLayoutInput1_->setObjectName("horizontalLayoutInput1");
  horizontalLayoutInput1_->setAlignment(Qt::AlignLeft);

  input1Label_ = new QLabel(this);
  input1Label_->setObjectName("input1Label");
  input1Label_->setFixedSize(20, 24);
  input1Label_->setText("Re:");
  input1Label_->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy3.setHeightForWidth(input1Label_->sizePolicy().hasHeightForWidth());
  input1Label_->setSizePolicy(sizePolicy3);

  input1Input_ = new QLineEdit(this);
  input1Input_->setObjectName("input1Input");
  input1Input_->setFixedHeight(24);
  QSizePolicy sizePolicy11(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy11.setHeightForWidth(input1Input_->sizePolicy().hasHeightForWidth());
  input1Input_->setSizePolicy(sizePolicy11);
  input1Input_->setValidator(double_validator);

  horizontalLayoutInput1_->addWidget(input1Label_);
  horizontalLayoutInput1_->addWidget(input1Input_);

  horizontalLayoutInput2_ = new QHBoxLayout(varSubWidget2_);
  horizontalLayoutInput2_->setContentsMargins(0, 0, 0, 0);
  horizontalLayoutInput2_->setSpacing(0);
  horizontalLayoutInput2_->setObjectName("horizontalLayoutInput2");
  horizontalLayoutInput2_->setAlignment(Qt::AlignLeft);

  input2Label_ = new QLabel(this);
  input2Label_->setObjectName("input2Label");
  input2Label_->setFixedSize(20, 24);
  input2Label_->setText("Im:");
  input2Label_->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  input1Label_->setSizePolicy(sizePolicy3);

  input2Input_ = new QLineEdit(this);
  input2Input_->setObjectName("input2Input");
  input2Input_->setFixedHeight(24);
  input2Input_->setSizePolicy(sizePolicy11);
  input2Input_->setValidator(double_validator);

  horizontalLayoutInput2_->addWidget(input2Label_);
  horizontalLayoutInput2_->addWidget(input2Input_);

  QMetaObject::connectSlotsByName(this);
}

std::complex<double> ComplexVar::getValue()
{
  return value_;
}

QString ComplexVar::getName()
{
  return name_;
}

void ComplexVar::on_expandButton_clicked()
{
  if (this->findChild<QWidget*>("glWidget_"))
  {
    expandButton_->setText("Expand");
    this->setMinimumSize(200, 72);
    this->setUpdatesEnabled(false);
    disconnect(openGL3DWindow_);
    delete openGL3DWindow_;
    delete glWidget_;
    this->setUpdatesEnabled(true);
  }
  else
  {
    expandButton_->setText("Retract");
    openGL3DWindow_ = new OpenGLWindow(false);
    glWidget_ = QWidget::createWindowContainer(openGL3DWindow_);
    QSizePolicy sizePolicy12(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    glWidget_->setFixedHeight(200);
    glWidget_->setObjectName("glWidget_");
    glWidget_->setSizePolicy(sizePolicy12);
    if(abs(value_) > 0)
      openGL3DWindow_->insertVariable(this);
    if (timeSlider_ != nullptr)
    {
      openGL3DWindow_->setTime(timeSlider_->value());
      connect(timeSlider_, &QSlider::valueChanged, openGL3DWindow_, &OpenGLWindow::setTime);
    }
    verticalLayout_->addWidget(glWidget_);
    this->setMinimumSize(200, 272);
  }
}

void ComplexVar::on_switchButton_clicked()
{
  if (input_is_euler_)
  {
    input1Label_->setFixedSize(20, 24);
    input2Label_->setFixedSize(20, 24);
    input1Label_->setText("Re:");
    input2Label_->setText("Im:");
    switchButton_->setText("Euler");

    if (value_.real() != 0 && value_.imag() != 0)
    {
      input1Input_->setText(QLocale::system().toString(value_.real()));
      input2Input_->setText(QLocale::system().toString(value_.imag()));
    }

  }
  else
  {
    input1Label_->setFixedSize(26, 24);
    input2Label_->setFixedSize(26, 24);
    input1Label_->setText("Mag:");
    input2Label_->setText("φ[°]:");
    switchButton_->setText("Component:");

    if (value_.real() != 0 && value_.imag() != 0)
    {
      input1Input_->setText(QLocale::system().toString(std::abs(value_)));
      input2Input_->setText(QLocale::system().toString(std::arg(value_)*180/M_PI));
    }

  }

  input_is_euler_ ^= true;
}

void ComplexVar::on_deleteButton_clicked()
{
  ScrollWidget* parent = dynamic_cast<ScrollWidget*>(parent_);
  parent->deleteVariable(this);
}

void ComplexVar::on_nameInput_textEdited(const QString& text)
{
  nameInput_->setText(nameInput_->text().toUpper());
  name_ = nameInput_->text();

  emit variable_name_changed();
}

void ComplexVar::on_omegaInput_editingFinished()
{
  omega_ = QLocale::system().toDouble(omegaInput_->text());

  emit variable_value_changed();
}

void ComplexVar::on_input1Input_editingFinished()
{
  if (input_is_euler_)
  {
    double phi;
    if (input2Input_->text().isEmpty())
      phi = 0;
    else
      phi = QLocale::system().toDouble(input2Input_->text())*M_PI/180;

    double magn = QLocale::system().toDouble(input1Input_->text());

    value_.real(magn * std::cos(phi));
    value_.imag(magn * std::sin(phi));
  }
  else
    value_.real(QLocale::system().toDouble(input1Input_->text()));

  if (this->findChild<QWidget*>("glWidget_") && !openGL3DWindow_->hasArrow() && abs(value_) > 0)
    openGL3DWindow_->insertVariable(this);
  
    emit variable_value_changed();
}

void ComplexVar::on_input2Input_editingFinished()
{
  if (input_is_euler_)
  {
    if (input1Input_->text().isEmpty())
      return;

    double phi = QLocale::system().toDouble(input2Input_->text()) * M_PI / 180;

    double magn = QLocale::system().toDouble(input1Input_->text());

    value_.real(magn * std::cos(phi));
    value_.imag(magn * std::sin(phi));
  }
  else
    value_.imag(QLocale::system().toDouble(input2Input_->text()));

  if (this->findChild<QWidget*>("glWidget_") && !openGL3DWindow_->hasArrow() && abs(value_) > 0)
    openGL3DWindow_->insertVariable(this);
  
  emit variable_value_changed();
}
