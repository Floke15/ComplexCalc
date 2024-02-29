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

  std::complex<double> getValue() const;
  void setValue(std::complex<double> value);
  QString getName();
  void setName(QString name);

signals:
  void variable_changed();

public slots:
  void on_expandButton_clicked();
  void on_switchButton_clicked();
  void on_deleteButton_clicked();

  void on_nameInput_textEdited(const QString& text);
  void on_omegaInput_editingFinished();
  void on_input1Input_editingFinished();
  void on_input2Input_editingFinished();
  bool eventFilter(QObject* object, QEvent* event);

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
  OpenGLWindow* openGL3DWindow_;
  QWidget* glWidget_;
  QPushButton* expandButton_;
  QPushButton* switchButton_;
  QLineEdit* nameInput_;
  QLineEdit* omegaInput_;
  QLabel* input1Label_;
  QLineEdit* input1Input_;
  QLabel* input2Label_;
  QLineEdit* input2Input_;
};


#endif // COMPLEXVAR_H
