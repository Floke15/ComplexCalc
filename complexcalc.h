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
class ScrollWidget;

class ComplexCalc : public QMainWindow
{
  Q_OBJECT

public:
  ComplexCalc(QWidget* parent = nullptr);
  //~ComplexCalc();

private slots:
  void on_addVarButton_clicked();
  void on_operationInput_textEdited(const QString& text);
  void reparseText();
  void clearMainWindow();

private:
  // Design elements
  QWidget* centralWidget_;
  QVBoxLayout* verticalLayout_;
  QWidget* subWidget_;
  QGridLayout* gridLayout_;
  QPushButton* addVarButton_;
  OpenGLWindow* openGL3DWindow_;
  QLineEdit* operationInput_;
  ScrollWidget* scrollWidget_;
  QVBoxLayout* verticalScrollLayout_;
  QScrollArea* scrollArea_;
  QSlider* timeSlider_;
};
#endif // COMPLEXCALC_H
