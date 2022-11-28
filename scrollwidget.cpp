#include "scrollwidget.h"
#include "complexvar.h"

#include <QLayout>
#include <QTimer>

ScrollWidget::ScrollWidget(QWidget* parent, int number_of_widgets) : 
  QWidget(parent)
{
  for (int iter = 0; iter < number_of_widgets; iter++)
  {
    ComplexVar* newVar = new ComplexVar(this);
    this->layout()->addWidget(newVar);
  }

  QTimer* timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(100);
}

void ScrollWidget::addVariable()
{
  ComplexVar* newVar = new ComplexVar(this);
  this->layout()->addWidget(newVar);
}

void ScrollWidget::deleteVariable(ComplexVar* variable)
{
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