#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <Qt3DExtras/qt3dwindow.h>
#include <complex>

#include "complexcalc.h"

class ComplexVar;
class CustomArrow;

class OpenGLWindow : public Qt3DExtras::Qt3DWindow
{
  Q_OBJECT

public:
  OpenGLWindow(bool isMainWindow = false);
  OpenGLWindow(const OpenGLWindow&) = delete;
  //~OpenGLWindow();

  void resizeEvent(QResizeEvent* event) override;
  void refreshVariable(ComplexVar* variable);

private:
  bool isMainWindow_;
  Qt3DCore::QEntity* rootEntity_;
  double scale_;
  std::map<ComplexVar*, CustomArrow*> variables_;
};
#endif // OPENGLWINDOW_H
