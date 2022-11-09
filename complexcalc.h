#ifndef COMPLEXCALC_H
#define COMPLEXCALC_H

#include <QMainWindow>

class OpenGLWindow;
class QVBoxLayout;
class QGridLayout;
class QPushButton;
class QTextEdit;
class QListWidget;
class QSlider;

class ComplexCalc : public QMainWindow
{
  Q_OBJECT

public:
  ComplexCalc(QWidget* parent = nullptr);
  ~ComplexCalc();

private:
  OpenGLWindow* mainGL_;
  QWidget* centralWidget;
  QVBoxLayout* verticalLayout;
  QWidget* subWidget;
  QGridLayout* gridLayout;
  QPushButton* addVarButton;
  OpenGLWindow* openGL3DWindow;
  QTextEdit* operationInput;
  QListWidget* listWidget;
  QSlider* timeSlider;
};
#endif // COMPLEXCALC_H
