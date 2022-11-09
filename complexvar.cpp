#include "complexvar.h"

ComplexVar::ComplexVar(QWidget* parent, std::string name, std::complex<double> value, double omega, double phi, QColor color) :
  parent_(parent),
  name_(name),
  value_(value),
  omega_(omega),
  phi_(phi),
  color_(color)
{
}
