#ifndef COMPLEXCALC_H
#define COMPLEXCALC_H

#include <QMainWindow>
#include <Vector>
#include <QWidget>

class OpenGLWindow;
class QVBoxLayout;
class QGridLayout;
class QPushButton;
class QLineEdit;
class QScrollArea;
class QSlider;

class ComplexCalc : public QMainWindow
{
  Q_OBJECT

public:
  ComplexCalc(QWidget* parent = nullptr);
  //~ComplexCalc();
  void delete_Variable(QWidget* variable);

private slots:
  void on_addVarButton_clicked();
  //void update();

private:
  //std::vector<QWidget*> variables_to_delete_;

  // Design elements
  QWidget* centralWidget;
  QVBoxLayout* verticalLayout;
  QWidget* subWidget;
  QGridLayout* gridLayout;
  QPushButton* addVarButton;
  OpenGLWindow* openGL3DWindow;
  QLineEdit* operationInput;
  QWidget* scrollWidget;
  QVBoxLayout* verticalScrollLayout;
  QScrollArea* scrollArea;
  QSlider* timeSlider;
  //std::vector<QPushButton*> dynamicButtons;
};
#endif // COMPLEXCALC_H
