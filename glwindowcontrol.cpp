#include "glwindowcontrol.h"
#include "customarrow.h"

#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcamera.h>
#include <Qt3DRender/qpointlight.h>

GLWindowControl::GLWindowControl(Qt3DExtras::Qt3DWindow* glWindow) :
  glWindow_(glWindow)
{
  glWindow_->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

  // Root entity
  Qt3DCore::QEntity* rootEntity = new Qt3DCore::QEntity();

  // Camera
  Qt3DRender::QCamera* cameraEntity = glWindow->camera();

  //für isometrische Ansicht: setOrthographicProjection
  cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
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

  CustomArrow* arr1 = new CustomArrow(rootEntity, QVector2D(0, 0), 100, 45.0f);

  glWindow->setRootEntity(rootEntity);

}
