#include "customarrow.h"
#include "complexvar.h"

#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QPhongmaterial.h>

CustomArrow::CustomArrow(Qt3DCore::QEntity* rootEntity, QVector2D translation, float length, float rotation) :
  CustomArrow(rootEntity, translation, length, rotation, nullptr, QColor(QRgb(0x000000)))
{
}

CustomArrow::CustomArrow(Qt3DCore::QEntity* rootEntity, QVector2D translation, ComplexVar* variable, QColor color) :
  CustomArrow(rootEntity, translation, abs(variable->getValue()), (180 * arg(variable->getValue())) / M_PI, variable, color)
{
}

CustomArrow::CustomArrow(Qt3DCore::QEntity* rootEntity, QVector2D translation, float length, float rotation, ComplexVar* variable, QColor color) :
  rootEntity_(rootEntity),
  sphereTransform_(new Qt3DCore::QTransform()),
  cylinder_(new Qt3DExtras::QCylinderMesh()),
  cylinderTransform_(new Qt3DCore::QTransform()),
  variable_(variable),
  color_(color)
{
  assert(rootEntity && "rootEntity cannot be null");

  //TODO: if length < CONE_LENGTH find new representation

  // Sphere shape data
  Qt3DExtras::QSphereMesh* sphere = new Qt3DExtras::QSphereMesh();
  sphere->setRadius(0);
  sphere->setRings(2);
  sphere->setSlices(1);

  // SphereMesh Transform
  sphereTransform_->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), rotation - 90.0f));

  // Sphere
  Qt3DCore::QEntity* sphereEntity = new Qt3DCore::QEntity(rootEntity_);
  sphereEntity->addComponent(sphere);
  sphereEntity->addComponent(sphereTransform_);

  // Cylinder shape data
  cylinder_->setRadius(1);
  cylinder_->setLength(length - CONE_LENGTH);
  cylinder_->setRings(100);
  cylinder_->setSlices(20);

  // CylinderMesh Transform
  cylinderTransform_->setTranslation(QVector3D(translation.x(), translation.y() + cylinder_->length() / 2, 0));

  Qt3DExtras::QPhongMaterial* cylinderMaterial = new Qt3DExtras::QPhongMaterial();
  cylinderMaterial->setDiffuse(color_);

  // Cylinder
  Qt3DCore::QEntity* cylinderEntity = new Qt3DCore::QEntity(sphereEntity);
  cylinderEntity->addComponent(cylinder_);
  cylinderEntity->addComponent(cylinderMaterial);
  cylinderEntity->addComponent(cylinderTransform_);

  // Cone shape data
  cone_ = new Qt3DExtras::QConeMesh();
  cone_->setTopRadius(0);
  cone_->setBottomRadius(3);
  cone_->setLength(CONE_LENGTH);
  cone_->setRings(50);
  cone_->setSlices(20);

  // ConeMesh Transform
  coneTransform_ = new Qt3DCore::QTransform();
  coneTransform_->setTranslation(QVector3D(0, cylinder_->length() / 2 + cone_->length() / 2, 0));

  Qt3DExtras::QPhongMaterial* coneMaterial = new Qt3DExtras::QPhongMaterial();
  coneMaterial->setDiffuse(color_);

  // Cone
  Qt3DCore::QEntity* coneEntity = new Qt3DCore::QEntity(cylinderEntity);
  coneEntity->addComponent(cone_);
  coneEntity->addComponent(coneMaterial);
  coneEntity->addComponent(coneTransform_);
}

CustomArrow::~CustomArrow()
{
  delete sphereTransform_;
  delete cylinder_;
  delete cylinderTransform_;
}

void CustomArrow::update()
{
  sphereTransform_->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), (180*arg(variable_->getValue()))/M_PI - 90.0f));
  cylinder_->setLength(abs(variable_->getValue()) - CONE_LENGTH);
  cylinderTransform_->setTranslation(QVector3D(0, cylinder_->length() / 2, 0));
  coneTransform_->setTranslation(QVector3D(0, cylinder_->length() / 2 + cone_->length() / 2, 0));
}


