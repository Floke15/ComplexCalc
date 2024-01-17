#ifndef COMPLEXVAR_H
#define COMPLEXVAR_H

#include "openglwindow.h"

#include <QFrame>
#include <complex>
#include <string>

class QSlider;
class QHBoxLayout;
class QLabel;
class QVBoxLayout;
class QWidget;
class OpenGLWindow;
class QHBoxLayout;
class QPushButton;
class QLineEdit;

class ComplexVar : public QFrame
{
  Q_OBJECT

public:
  ComplexVar(QWidget* parent = 0, QSlider* timeSlider = nullptr, QString name = "", std::complex<double> value = 0, double omega = 1, QColor color = QColor(QRgb(0xFF0000)));
  //~ComplexVar();

  std::complex<double> getValue();
  QString getName();

signals:
  void variable_value_changed();
  void variable_name_changed();

private slots:
  void on_expandButton_clicked();
  void on_switchButton_clicked();
  void on_deleteButton_clicked();

  void on_nameInput_textEdited(const QString& text);
  void on_omegaInput_editingFinished();
  void on_input1Input_editingFinished();
  void on_input2Input_editingFinished();

private:
  QWidget* parent_;
  QString name_;
  QSlider* timeSlider_;
  std::complex<double> value_;
  QColor color_;
  double omega_;
  bool input_is_euler_;

  // Design elements
  QVBoxLayout* verticalLayout_;

  QWidget* horizontalWidget1_;
  QWidget* horizontalWidget2_;
  QWidget* horizontalWidget3_;
  OpenGLWindow* openGL3DWindow_;
  QWidget* glWidget_;
  
  QHBoxLayout* horizontalLayout1_;
  QHBoxLayout* horizontalLayout2_;
  QHBoxLayout* horizontalLayout3_;
  
  QPushButton* expandButton_;
  QPushButton* switchButton_;
  QPushButton* deleteButton_;
  
  QLineEdit* nameInput_;
  
  QWidget* omegaSubWidget_;
  QHBoxLayout* horizontalLayoutOmega_;
  QLabel* omegaLabel_;
  QLineEdit* omegaInput_;
  
  QWidget* varSubWidget1_;
  QWidget* varSubWidget2_;
  
  QHBoxLayout* horizontalLayoutInput1_;
  QLabel* input1Label_;
  QLineEdit* input1Input_;
  
  QHBoxLayout* horizontalLayoutInput2_;
  QLabel* input2Label_;
  QLineEdit* input2Input_;
};


#endif // COMPLEXVAR_H
