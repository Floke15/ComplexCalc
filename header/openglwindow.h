#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QTransform>
#include <complex>

class ComplexVar;
class CustomArrow;
class Trace;
class Label;

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
  bool isEmpty();

public slots:
  void removeAllVariables();
  void setTime(int time);
  void update();

private:
  void findScale();
  void setOrthographicProjection() const;

  bool isMainWindow_;
  Qt3DCore::QEntity* rootEntity_;
  double scale_;
  double time_;
  QPointF lastPos_;
  float currentAngleX_;
  float currentAngleZ_;
  QVector<CustomArrow*> arrows_;
  QVector<Trace*> traces_;
  CustomArrow* timeAxis_;
  Qt3DCore::QTransform* lightTransform_;
  Qt3DCore::QEntity* tickRealEntity_;
  Qt3DCore::QEntity* tickImagEntity_;
  Qt3DCore::QEntity* tickTimeEntity_;
  Label* realAxisLabel_;
  Label* imagAxisLabel_;
  Label* timeAxisLabel_;
  Label* tickRealLabel_;
  Label* tickImagLabel_;
  Label* tickTimeLabel_;
};
#endif // OPENGLWINDOW_H
