#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <Qt3DExtras/qt3dwindow.h>
#include <complex>

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
  void insertVariable(ComplexVar* variable);
  void removeAllVariables();
  void findScale();
  bool hasArrow();

public slots:
  void refreshVariables();

private:
  bool isMainWindow_;
  Qt3DCore::QEntity* rootEntity_;
  unsigned long scale_;
  std::vector<CustomArrow*> arrows_;
};
#endif // OPENGLWINDOW_H
