#include "glwindowcontrol.h"

#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcamera.h>
#include <Qt3DRender/qpointlight.h>
#include <Qt3DExtras/qcylindermesh.h>
#include <Qt3DExtras/qconemesh.h>
#include <Qt3DExtras/qphongmaterial.h>

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
  cameraEntity->setPosition(QVector3D(0, 50, 200));
  cameraEntity->setUpVector(QVector3D(0, 1, 0));
  cameraEntity->setViewCenter(QVector3D(0, 50, 0));

  Qt3DCore::QEntity* lightEntity = new Qt3DCore::QEntity(rootEntity);
  Qt3DRender::QPointLight* light = new Qt3DRender::QPointLight(lightEntity);
  light->setColor("white");
  light->setIntensity(1);
  lightEntity->addComponent(light);
  Qt3DCore::QTransform* lightTransform = new Qt3DCore::QTransform(lightEntity);
  lightTransform->setTranslation(cameraEntity->position());
  lightEntity->addComponent(lightTransform);

  // Cylinder shape data
  Qt3DExtras::QCylinderMesh* cylinder = new Qt3DExtras::QCylinderMesh();
  cylinder->setRadius(1);
  cylinder->setLength(100);
  cylinder->setRings(100);
  cylinder->setSlices(20);

  // CylinderMesh Transform
  Qt3DCore::QTransform* cylinderTransform = new Qt3DCore::QTransform();
  cylinderTransform->setScale(1);
  //cylinderTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 45.0f));
  cylinderTransform->setTranslation(QVector3D(0, 50, 0));

  Qt3DExtras::QPhongMaterial* cylinderMaterial = new Qt3DExtras::QPhongMaterial();
  cylinderMaterial->setDiffuse(QColor(QRgb(0x000000)));

  // Cylinder
  {
    Qt3DCore::QEntity* cylinderEntity = new Qt3DCore::QEntity(rootEntity);
    cylinderEntity->addComponent(cylinder);
    cylinderEntity->addComponent(cylinderMaterial);
    cylinderEntity->addComponent(cylinderTransform);
  }

  // Cone shape data
  Qt3DExtras::QConeMesh* cone = new Qt3DExtras::QConeMesh();
  cone->setTopRadius(0);
  cone->setBottomRadius(3);
  cone->setLength(6);
  cone->setRings(50);
  cone->setSlices(20);

  // ConeMesh Transform
  Qt3DCore::QTransform* coneTransform = new Qt3DCore::QTransform();
  coneTransform->setScale(1);
  //coneTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 45.0f));
  coneTransform->setTranslation(QVector3D(0, 100.0f + cone->length()/2, 0));

  Qt3DExtras::QPhongMaterial* coneMaterial = new Qt3DExtras::QPhongMaterial();
  coneMaterial->setDiffuse(QColor(QRgb(0x000000)));

  // Cone
  {
    Qt3DCore::QEntity* coneEntity = new Qt3DCore::QEntity(rootEntity);
    coneEntity->addComponent(cone);
    coneEntity->addComponent(coneMaterial);
    coneEntity->addComponent(coneTransform);
  }

  glWindow->setRootEntity(rootEntity);

}
