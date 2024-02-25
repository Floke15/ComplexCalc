#include "header/complexvar.h"
#include "header/scrollwidget.h"

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
  input_is_euler_(false),
  verticalLayout_(new QVBoxLayout(this)),
  openGL3DWindow_(nullptr),
  glWidget_(nullptr),
  expandButton_(new QPushButton()),
  switchButton_(new QPushButton()),
  nameInput_(new QLineEdit(this)),
  omegaInput_(new QLineEdit(this)),
  input1Label_(new QLabel(this)),
  input1Input_(new QLineEdit(this)),
  input2Label_(new QLabel(this)),
  input2Input_(new QLineEdit(this))
{
  this->setObjectName("newVariable");
  this->setMinimumSize(200, 72);
  this->setFrameShape(QFrame::StyledPanel);
  //this->setMidLineWidth(1);
  QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());

  verticalLayout_->setContentsMargins(0, 0, 0, 0);
  verticalLayout_->setSpacing(0);
  verticalLayout_->setObjectName("VarVerticalLayout");
  verticalLayout_->setAlignment(Qt::AlignTop);


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
  horizontalWidget3->setObjectName("horizontalWidget3");
  horizontalWidget3->setFixedHeight(24);
  horizontalWidget3->setSizePolicy(sizePolicy4);

  verticalLayout_->addWidget(horizontalWidget1);
  verticalLayout_->addWidget(horizontalWidget2);
  verticalLayout_->addWidget(horizontalWidget3);

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


  expandButton_->setParent(horizontalWidget1);
  expandButton_->setObjectName("expandButton");
  expandButton_->setText("Expand");
  expandButton_->setFixedHeight(24);
  QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy1.setHorizontalStretch(1);
  sizePolicy1.setHeightForWidth(expandButton_->sizePolicy().hasHeightForWidth());
  expandButton_->setSizePolicy(sizePolicy1);

  switchButton_->setParent(horizontalWidget1);
  switchButton_->setObjectName("switchButton");
  switchButton_->setText("Euler");
  switchButton_->setFixedHeight(24);
  switchButton_->setSizePolicy(sizePolicy1);

  QPushButton* deleteButton = new QPushButton(horizontalWidget1);
  deleteButton->setObjectName("deleteButton");
  deleteButton->setText("X");
  deleteButton->setFixedSize(20, 20);
  deleteButton->setStyleSheet("border: 1px; background-color: rgb(196, 43, 28)");
  QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy5.setHorizontalStretch(0);
  sizePolicy5.setHeightForWidth(deleteButton->sizePolicy().hasHeightForWidth());
  deleteButton->setSizePolicy(sizePolicy5);

  horizontalLayout1->addWidget(expandButton_);
  horizontalLayout1->addWidget(switchButton_);
  horizontalLayout1->addWidget(deleteButton);

  QRegularExpressionValidator* var_validator = new QRegularExpressionValidator(QRegularExpression("[a-zA-Z0-9]*"));

  nameInput_->setObjectName("nameInput");
  nameInput_->setFixedHeight(24);
  nameInput_->setPlaceholderText("Name");
  QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy2.setHorizontalStretch(1);
  sizePolicy2.setHeightForWidth(nameInput_->sizePolicy().hasHeightForWidth());
  nameInput_->setSizePolicy(sizePolicy2);
  nameInput_->setValidator(var_validator);

  QWidget* omegaSubWidget = new QWidget();
  omegaSubWidget->setObjectName("omegaSubWidget");
  omegaSubWidget->setFixedHeight(24);
  QSizePolicy sizePolicy6(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy6.setHorizontalStretch(1);
  sizePolicy6.setHeightForWidth(omegaSubWidget->sizePolicy().hasHeightForWidth());
  omegaSubWidget->setSizePolicy(sizePolicy6);

  horizontalLayout2->addWidget(nameInput_);
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

  omegaInput_->setObjectName("omegaInput");
  omegaInput_->setFixedHeight(24);
  QSizePolicy sizePolicy8(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy8.setHeightForWidth(nameInput_->sizePolicy().hasHeightForWidth());
  omegaInput_->setSizePolicy(sizePolicy8);
  QDoubleValidator* double_validator = new QDoubleValidator();
  double_validator->setNotation(QDoubleValidator::ScientificNotation);
  omegaInput_->setValidator(double_validator);
  omegaInput_->setText(QString::number(omega_));
  omegaInput_->setReadOnly(true);

  horizontalLayoutOmega->addWidget(omegaLabel);
  horizontalLayoutOmega->addWidget(omegaInput_);

  
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

  input1Label_->setObjectName("input1Label");
  input1Label_->setFixedSize(20, 24);
  input1Label_->setText("Re:");
  input1Label_->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy3.setHeightForWidth(input1Label_->sizePolicy().hasHeightForWidth());
  input1Label_->setSizePolicy(sizePolicy3);

  input1Input_->setObjectName("input1Input");
  input1Input_->setFixedHeight(24);
  QSizePolicy sizePolicy11(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy11.setHeightForWidth(input1Input_->sizePolicy().hasHeightForWidth());
  input1Input_->setSizePolicy(sizePolicy11);
  input1Input_->setValidator(double_validator);
  input1Input_->installEventFilter(this);

  horizontalLayoutInput1->addWidget(input1Label_);
  horizontalLayoutInput1->addWidget(input1Input_);

  QHBoxLayout* horizontalLayoutInput2 = new QHBoxLayout(varSubWidget2);
  horizontalLayoutInput2->setContentsMargins(0, 0, 0, 0);
  horizontalLayoutInput2->setSpacing(0);
  horizontalLayoutInput2->setObjectName("horizontalLayoutInput2");
  horizontalLayoutInput2->setAlignment(Qt::AlignLeft);

  input2Label_->setObjectName("input2Label");
  input2Label_->setFixedSize(20, 24);
  input2Label_->setText("Im:");
  input2Label_->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  input1Label_->setSizePolicy(sizePolicy3);

  input2Input_->setObjectName("input2Input");
  input2Input_->setFixedHeight(24);
  input2Input_->setSizePolicy(sizePolicy11);
  input2Input_->setValidator(double_validator);
  input2Input_->installEventFilter(this);

  horizontalLayoutInput2->addWidget(input2Label_);
  horizontalLayoutInput2->addWidget(input2Input_);

  QMetaObject::connectSlotsByName(this);
}

std::complex<double> ComplexVar::getValue() const
{
  return value_;
}

void ComplexVar::setValue(std::complex<double> value)
{
  value_ = value;

  if (!input_is_euler_)
  {
    input1Input_->setText(QLocale::system().toString(value_.real()));
    input2Input_->setText(QLocale::system().toString(value_.imag()));
  }
  else
  {
    input1Input_->setText(QLocale::system().toString(std::abs(value_)));
    input2Input_->setText(QLocale::system().toString(std::arg(value_) * 180 / M_PI));
  }
}

QString ComplexVar::getName()
{
  return name_;
}

void ComplexVar::setName(QString name)
{
  name_ = name;
  nameInput_->setText(name_);
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
    switchButton_->setText("Component");

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
  QString new_name = nameInput_->text().toUpper();

  for (auto iter : dynamic_cast<ScrollWidget*>(parent_)->variables_)
    if (iter->getName() == new_name)
    {
      nameInput_->setText(new_name.removeLast());
      return;
    }

  nameInput_->setText(new_name);
  name_ = nameInput_->text();

  emit variable_changed();
}

void ComplexVar::on_omegaInput_editingFinished()
{
  omega_ = QLocale::system().toDouble(omegaInput_->text());

  emit variable_changed();
}

void ComplexVar::on_input1Input_editingFinished()
{

  if (input_is_euler_)
  {
    double phi = 0;
    if (!input2Input_->text().isEmpty())
      phi = QLocale::system().toDouble(input2Input_->text())*M_PI/180;

    double magn = QLocale::system().toDouble(input1Input_->text());

    value_.real(magn * std::cos(phi));
    value_.imag(magn * std::sin(phi));
  }
  else
    value_.real(QLocale::system().toDouble(input1Input_->text()));

  if (this->findChild<QWidget*>("glWidget_") && !openGL3DWindow_->hasArrow() && abs(value_) > 0)
    openGL3DWindow_->insertVariable(this);

  emit variable_changed();
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
  
  emit variable_changed();
}

bool ComplexVar::eventFilter(QObject* object, QEvent* event)
{
  if (object == input1Input_ && event->type() == QEvent::FocusOut && input1Input_->text() == "")
  {
    input1Input_->setText("0");
    on_input1Input_editingFinished();
  }

  if (object == input2Input_ && event->type() == QEvent::FocusOut && input2Input_->text() == "")
  {
    input2Input_->setText("0");
    on_input2Input_editingFinished();
  }

  return false;
}
