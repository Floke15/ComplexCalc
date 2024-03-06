#include "header/scrollwidget.h"
#include "header/complexvar.h"
#include "header/complexcalc.h"

#include <QLayout>
#include <QTimer>

ScrollWidget::ScrollWidget(QWidget* parent, QSlider* timeSlider, ComplexCalc* complexCalc) :
  timeSlider_(timeSlider),
  complexCalc_(complexCalc),
  QWidget(parent)
{
  QTimer* timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(100);

  setObjectName("scrollWidget");
  QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  sizePolicy1.setHorizontalStretch(0);
  sizePolicy1.setVerticalStretch(0);
  sizePolicy1.setHeightForWidth(sizePolicy().hasHeightForWidth());

  // define verticalScrollLayout as Layout of scrollWidget
  QVBoxLayout* verticalScrollLayout = new QVBoxLayout(this);
  verticalScrollLayout->setContentsMargins(0, 0, 0, 0);
  verticalScrollLayout->setSpacing(0);
  verticalScrollLayout->setObjectName("verticalScrollLayout");
  verticalScrollLayout->setAlignment(Qt::AlignTop);

  Qt3DExtras::Qt3DWindow* Qt3DWindow = new Qt3DExtras::Qt3DWindow();
  QWidget* fixWidget = QWidget::createWindowContainer(Qt3DWindow);
  QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
  fixWidget->setMinimumSize(1, 1);
  fixWidget->setVisible(false);
  fixWidget->setSizePolicy(sizePolicy2);
  verticalScrollLayout->addWidget(fixWidget);
}

void ScrollWidget::deleteVariable(ComplexVar* variable)
{
  auto iter = std::find(variables_.begin(), variables_.end(), variable);
  assert(iter != variables_.end());
  variables_.erase(iter);

  variable->disconnect();

  if (variables_to_delete_.empty())
  {
    variables_to_delete_.push_back(variable);
    return;
  }

  if (variables_to_delete_.indexOf(variable) == -1)
  {
    variables_to_delete_.push_back(variable);
  }
}

ComplexVar* ScrollWidget::getVariable(QString name)
{
  ComplexVar* pos = nullptr;

  for (auto iter : variables_)
  {
    if (iter->getName() == name)
    {
      pos = iter;
      break;
    }
  }

  return pos;
}

void ScrollWidget::addVariable()
{
  ComplexVar* newVar = new ComplexVar(this, timeSlider_);
  layout()->addWidget(newVar);
  variables_.push_back(newVar);

  connect(newVar, &ComplexVar::variable_changed, complexCalc_, &ComplexCalc::reparseText);
}

void ScrollWidget::update()
{
  if (variables_to_delete_.size())
    emit about_to_delete();
  else
    return;

  for (auto position : variables_to_delete_)
  {
    this->layout()->removeWidget(position);
    delete position;
  }

  if (variables_to_delete_.size())
  {
    variables_to_delete_.clear();
    emit variable_deleted();
  }
}