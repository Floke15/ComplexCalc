#ifndef COMPLEXCALC_H
#define COMPLEXCALC_H

#include "openglwindow.h"

#include <QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE
namespace Ui { class ComplexCalcUI; }
QT_END_NAMESPACE

class OpenGLWindow;

class ComplexCalc : public QMainWindow
{
  Q_OBJECT

public:
  ComplexCalc(QWidget* parent = nullptr);
  ~ComplexCalc();

private:
  OpenGLWindow* mainGL_;
  QWidget* centralWidget;
  QVBoxLayout* verticalLayout_2;
  QWidget* widget;
  QGridLayout* gridLayout;
  QPushButton* pushButton;
  OpenGLWindow* openGL3DWindow;
  QTextEdit* textEdit;
  QListWidget* listWidget;
  QSlider* horizontalSlider;
};
#endif // COMPLEXCALC_H
