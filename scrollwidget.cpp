#include "scrollwidget.h"
#include "complexvar.h"

#include <QLayout>
#include <QTimer>

ScrollWidget::ScrollWidget(QWidget* parent) : 
  QWidget(parent)
{
  QTimer* timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(100);
}

void ScrollWidget::addVariable()
{
  ComplexVar* newVar = new ComplexVar(this);
  this->layout()->addWidget(newVar);
  variables_.push_back(newVar);
}

void ScrollWidget::deleteVariable(ComplexVar* variable)
{
  auto iter = std::find(variables_.begin(), variables_.end(), variable);
  assert(iter != variables_.end());
  variables_.erase(iter);

  if (variables_to_delete_.empty())
  {
    variables_to_delete_.push_back(variable);
    return;
  }

  auto position = std::find(begin(variables_to_delete_), end(variables_to_delete_), variable);

  if (position == variables_to_delete_.end())
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

void ScrollWidget::update()
{
  for (auto position = variables_to_delete_.begin(); position != variables_to_delete_.end(); ++position)
  {
    this->layout()->removeWidget(*position);
    delete *position;
  }

  if(variables_to_delete_.size())
    variables_to_delete_.clear();
}