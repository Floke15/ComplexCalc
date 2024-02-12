#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DCore/QTransform>
#include <complex>

class ComplexVar;
class CustomArrow;
class Trace;

class OpenGLWindow : public Qt3DExtras::Qt3DWindow
{
  Q_OBJECT

public:
  OpenGLWindow(bool isMainWindow = false);
  OpenGLWindow(const OpenGLWindow&) = delete;
  //~OpenGLWindow();

  void resizeEvent(QResizeEvent* event) override;
  void mousePressEvent(QMouseEvent* mouseEvent) override;
  void mouseMoveEvent(QMouseEvent* mouseEvent) override;
  void insertVariable(ComplexVar* variable, bool with_trace = false);
  bool hasArrow();

public slots:
  void removeAllVariables();
  void setTime(int time);
  void rescaleAxes();

private:
  void findScale();
  void setOrthographicProjection();

  bool isMainWindow_;
  Qt3DCore::QEntity* rootEntity_;
  double scale_;
  double time_;
  bool isDragging_;
  QPointF lastPos_;
  float currentAngleX_;
  float currentAngleZ_;
  QVector<CustomArrow*> arrows_;
  QVector<Trace*> traces_;
  CustomArrow* timeAxis_;
  Qt3DCore::QTransform* lightTransform_;
};
#endif // OPENGLWINDOW_H
