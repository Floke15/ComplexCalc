#include "customarrow.h"

#include <Qt3DCore/qentity.h>
#include <Qt3DExtras/qspheremesh.h>
#include <Qt3DExtras/qconemesh.h>
#include <Qt3DExtras/qphongmaterial.h>

CustomArrow::CustomArrow(Qt3DCore::QEntity* rootEntity, QVector2D translation, float length, float rotation, QColor color) :
  rootEntity_(rootEntity),
  sphereTransform_(new Qt3DCore::QTransform()),
  cylinder_(new Qt3DExtras::QCylinderMesh()),
  cylinderTransform_(new Qt3DCore::QTransform()),
  color_(color)
{
  assert(rootEntity && "rootEntity cannot be null");

  // Sphere shape data
  Qt3DExtras::QSphereMesh* sphere = new Qt3DExtras::QSphereMesh();
  sphere->setRadius(0);
  sphere->setRings(2);
  sphere->setSlices(1);

  // SphereMesh Transform
  sphereTransform_->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), rotation - 90.0f)); //

  // Sphere
  Qt3DCore::QEntity* sphereEntity = new Qt3DCore::QEntity(rootEntity_);
  sphereEntity->addComponent(sphere);
  sphereEntity->addComponent(sphereTransform_);

  // Cylinder shape data
  cylinder_->setRadius(1);
  cylinder_->setLength(length);
  cylinder_->setRings(100);
  cylinder_->setSlices(20);

  // CylinderMesh Transform
  cylinderTransform_->setTranslation(QVector3D(translation.x(), translation.y() + length/2, 0));//

  Qt3DExtras::QPhongMaterial* cylinderMaterial = new Qt3DExtras::QPhongMaterial();
  cylinderMaterial->setDiffuse(QColor(QRgb(0x000000)));

  // Cylinder
  Qt3DCore::QEntity* cylinderEntity = new Qt3DCore::QEntity(sphereEntity);
  cylinderEntity->addComponent(cylinder_);
  cylinderEntity->addComponent(cylinderMaterial);
  cylinderEntity->addComponent(cylinderTransform_);

  // Cone shape data
  Qt3DExtras::QConeMesh* cone = new Qt3DExtras::QConeMesh();
  cone->setTopRadius(0);
  cone->setBottomRadius(3);
  cone->setLength(6);
  cone->setRings(50);
  cone->setSlices(20);

  // ConeMesh Transform
  Qt3DCore::QTransform* coneTransform = new Qt3DCore::QTransform();
  coneTransform->setTranslation(QVector3D(0, cylinder_->length() / 2 + cone->length() / 2, 0));

  Qt3DExtras::QPhongMaterial* coneMaterial = new Qt3DExtras::QPhongMaterial();
  coneMaterial->setDiffuse(QColor(QRgb(0x000000)));

  // Cone
  Qt3DCore::QEntity* coneEntity = new Qt3DCore::QEntity(cylinderEntity);
  coneEntity->addComponent(cone);
  coneEntity->addComponent(coneMaterial);
  coneEntity->addComponent(coneTransform);
}

CustomArrow::~CustomArrow()
{
  delete sphereTransform_;
  delete cylinder_;
  delete cylinderTransform_;
}


