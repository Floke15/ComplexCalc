#include <QtWidgets>
#include <QtOpenGL>

#include "mainglwidget.h"

MainGLWidget::MainGLWidget(QWidget* parent) : QOpenGLWidget {parent}
{
  m_background = qRgb(20, 20, 50);
}

void MainGLWidget::initializeGL()
{
  initializeOpenGLFunctions();
}


void MainGLWidget::paintGL()
{
  QPainter painter;
  painter.begin(this);

  painter.beginNativePainting();

  glClearColor(m_background.redF(), m_background.greenF(), m_background.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glFrontFace(GL_CW);
  glCullFace(GL_FRONT);

  painter.endNativePainting();

  if (const int elapsed = m_time.elapsed()) {
    QString framesPerSecond;
    framesPerSecond.setNum(m_frames / (elapsed / 1000.0), 'f', 2);
    painter.setPen(Qt::white);
    painter.drawText(20, 40, framesPerSecond + " paintGL calls / s");
  }

  painter.end();

  if (!(m_frames % 100)) {
    m_time.start();
    m_frames = 0;
  }
  ++m_frames;
  
  update();
}

void MainGLWidget::resizeGL(int width, int height)
{
  //glViewport(0, 0, width, height);
}
