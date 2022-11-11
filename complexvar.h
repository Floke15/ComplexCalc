#ifndef COMPLEXVAR_H
#define COMPLEXVAR_H

#include "openglwindow.h"

#include <QWidget>
#include <complex>
#include <string>

class QSlider;

class ComplexVar : public QWidget
{
  Q_OBJECT

public:
  ComplexVar(QWidget* parent = 0, std::string name = "", std::complex<double> value = 0, double omega = 0, double phi = 0, QColor color = QColor(QRgb(0xFF0000)));
  //~ComplexVar();

private:
  QWidget* parent_;
  std::string name_;
  std::complex<double> value_;
  QColor color_;
  double omega_;
  double phi_;
};


#endif // COMPLEXVAR_H