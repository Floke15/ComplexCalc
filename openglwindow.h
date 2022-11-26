#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <Qt3DExtras/qt3dwindow.h>
#include <complex>

#include "complexcalc.h"

class OpenGLWindow : public Qt3DExtras::Qt3DWindow
{
  Q_OBJECT

public:
  OpenGLWindow(bool isMainWindow = false);
  OpenGLWindow(const OpenGLWindow&) = delete;
  //~OpenGLWindow();

  void resizeEvent(QResizeEvent* event) override;

private:
  bool isMainWindow_;
};
#endif // OPENGLWINDOW_H
