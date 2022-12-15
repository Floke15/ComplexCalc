#include "openglwindow.h"
#include "customarrow.h"
#include "complexvar.h"

#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcamera.h>
#include <Qt3DRender/qpointlight.h>

OpenGLWindow::OpenGLWindow(bool isMainWindow) :
  isMainWindow_(isMainWindow),
  rootEntity_(new Qt3DCore::QEntity()),
  scale_(0),
  Qt3DExtras::Qt3DWindow()
{
  defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

  // Camera
  Qt3DRender::QCamera* cameraEntity = camera();

  if(isMainWindow_)
    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
  else
    cameraEntity->lens()->setOrthographicProjection(-120, 120, -120, 120, -10, 500);

  cameraEntity->setPosition(QVector3D(0, 0, 300));
  cameraEntity->setUpVector(QVector3D(0, 1, 0));
  cameraEntity->setViewCenter(QVector3D(0, 0, 0));

  Qt3DCore::QEntity* lightEntity = new Qt3DCore::QEntity(rootEntity_);
  Qt3DRender::QPointLight* light = new Qt3DRender::QPointLight(lightEntity);
  light->setColor("white");
  light->setIntensity(1);
  lightEntity->addComponent(light);
  Qt3DCore::QTransform* lightTransform = new Qt3DCore::QTransform(lightEntity);
  lightTransform->setTranslation(cameraEntity->position());
  lightEntity->addComponent(lightTransform);

  CustomArrow* realPositiveAxis = new CustomArrow(rootEntity_, QVector2D(0, 0), 100, 0);
  CustomArrow* realNegativeAxis = new CustomArrow(rootEntity_, QVector2D(0, 0), 100, 180.0f);
  CustomArrow* imagPositiveAxis = new CustomArrow(rootEntity_, QVector2D(0, 0), 100, 90.0f);
  CustomArrow* imagNegativeAxis = new CustomArrow(rootEntity_, QVector2D(0, 0), 100, 270.0f);

  setRootEntity(rootEntity_);
}

void OpenGLWindow::resizeEvent(QResizeEvent* event)
{
  Qt3DExtras::Qt3DWindow::resizeEvent(event);

  if (!isMainWindow_)
  {
    int width = this->width();
    int height = this->height();

    float ratio = static_cast<float>(width) / static_cast<float>(height);

    if (ratio >= 1.0)
    {
      height = 220;
      width = ratio * height;
    }
    else
    {
      width = 220;
      height = width / ratio;
    }

    camera()->lens()->setOrthographicProjection(-width / 2, width / 2, -height / 2, height / 2, 0.1f, 1000.0f);
  }
}

void OpenGLWindow::refreshVariable(ComplexVar* variable)
{
  auto pos = variables_.find(variable);

  if (variables_.end() == pos)
  {
    CustomArrow* variable_arrow = new CustomArrow(rootEntity_, QVector2D(0, 0), variable, QColor(255, 0, 0, 255));

    variables_.insert(std::pair<ComplexVar*, CustomArrow*>(variable, variable_arrow));
  }
  else
  {
    pos->second->update();
  }
}
