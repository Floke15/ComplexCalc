#include "openglwindow.h"
#include "customarrow.h"

#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcamera.h>
#include <Qt3DRender/qpointlight.h>

OpenGLWindow::OpenGLWindow(bool isMainWindow) : Qt3DExtras::Qt3DWindow()
  , isMainWindow_(isMainWindow)
{
  defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

  // Root entity
  Qt3DCore::QEntity* rootEntity = new Qt3DCore::QEntity();

  // Camera
  Qt3DRender::QCamera* cameraEntity = camera();

  //für isometrische Ansicht: setOrthographicProjection
  if(isMainWindow_)
    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
  else
  {
    int width = this->width();
    int height = this->height();

    float ratio = static_cast<float>(width) / static_cast<float>(height);

    if (ratio >= 1.0)
    {
      height = 200;
      width = ratio * height;
    }
    else
    {
      width = 200;
      height = width / ratio;
    }

    cameraEntity->lens()->setOrthographicProjection(-width/2, width/2, -height/2, height/2, 0.1f, 1000.0f);
  }

  cameraEntity->setPosition(QVector3D(0, 0, 300));
  cameraEntity->setUpVector(QVector3D(0, 1, 0));
  cameraEntity->setViewCenter(QVector3D(0, 0, 0));

  Qt3DCore::QEntity* lightEntity = new Qt3DCore::QEntity(rootEntity);
  Qt3DRender::QPointLight* light = new Qt3DRender::QPointLight(lightEntity);
  light->setColor("white");
  light->setIntensity(1);
  lightEntity->addComponent(light);
  Qt3DCore::QTransform* lightTransform = new Qt3DCore::QTransform(lightEntity);
  lightTransform->setTranslation(cameraEntity->position());
  lightEntity->addComponent(lightTransform);

  CustomArrow* realPositiveAxis = new CustomArrow(rootEntity, QVector2D(0, 0), 100, 0);
  CustomArrow* realNegativeAxis = new CustomArrow(rootEntity, QVector2D(0, 0), 100, 180.0f);
  CustomArrow* imagPositiveAxis = new CustomArrow(rootEntity, QVector2D(0, 0), 100, 90.0f);
  CustomArrow* imagNegativeAxis = new CustomArrow(rootEntity, QVector2D(0, 0), 100, 270.0f);

  //TODO: Draw given variables

  setRootEntity(rootEntity);

}