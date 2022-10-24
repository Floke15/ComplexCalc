#ifndef MAINGLWIDGET_H
#define MAINGLWIDGET_H

#include <QColor>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QElapsedTimer>

#include "complexcalc.h"

class MainGLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
  Q_OBJECT

public:
  MainGLWidget(QWidget* parent = nullptr);
  //~MainGLWidget();

protected:

  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;

private:
  QColor m_background;
  int m_frames = 0;
  QElapsedTimer m_time;
};
#endif // MAINGLWIDGET_H
