#ifndef COMPLEXCALC_H
#define COMPLEXCALC_H

#include <QMainWindow>
#include <Vector>

class OpenGLWindow;
class QVBoxLayout;
class QGridLayout;
class QPushButton;
class QTextEdit;
class QScrollArea;
class QSlider;

class ComplexCalc : public QMainWindow
{
  Q_OBJECT

public:
  ComplexCalc(QWidget* parent = nullptr);
  //~ComplexCalc();

private slots:
  void on_addVarButton_clicked();

private:
  OpenGLWindow* mainGL_;
  QWidget* centralWidget;
  QVBoxLayout* verticalLayout;
  QWidget* subWidget;
  QGridLayout* gridLayout;
  QPushButton* addVarButton;
  OpenGLWindow* openGL3DWindow;
  QTextEdit* operationInput;
  QWidget* scrollWidget;
  QVBoxLayout* verticalScrollLayout;
  QScrollArea* scrollArea;
  QSlider* timeSlider;
  //std::vector<QPushButton*> dynamicButtons;
};
#endif // COMPLEXCALC_H
