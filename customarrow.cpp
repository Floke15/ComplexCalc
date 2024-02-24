#include "customarrow.h"
#include "complexvar.h"

#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QDiffuseSpecularMaterial>

CustomArrow::CustomArrow(Qt3DCore::QEntity* rootEntity, float length, float rotation) :
  CustomArrow(rootEntity, length, rotation, nullptr, QColor(QRgb(0x000000)), false)
{
}

CustomArrow::CustomArrow(Qt3DCore::QEntity* rootEntity, ComplexVar* variable, QColor color) :
  CustomArrow(rootEntity, abs(variable->getValue()), (180 * arg(variable->getValue())) / M_PI, variable, color, true)
{
}

CustomArrow::CustomArrow(Qt3DCore::QEntity* rootEntity, float length, float rotation, ComplexVar* variable, QColor color, bool isVariable) :
  rootEntity_(rootEntity),
  cylinder_(new Qt3DExtras::QCylinderMesh()),
  cylinderTransform_(new Qt3DCore::QTransform()),
  cone_(new Qt3DExtras::QConeMesh()),
  coneTransform_(new Qt3DCore::QTransform()),
  variable_(variable),
  color_(color),
  isVariable_(isVariable)
{
  assert(rootEntity && "rootEntity cannot be null");

  //TODO: if length < CONE_LENGTH find new representation

  bool is_time_axis = !isVariable && length < 0;

  if (is_time_axis)
    length = abs(length);

  // Cylinder shape data
  if(isVariable_)
    cylinder_->setRadius(1);
  else
    cylinder_->setRadius(0.75f);
  cylinder_->setLength(length - CONE_LENGTH);
  cylinder_->setRings(100);
  cylinder_->setSlices(20);

  // CylinderMesh Transform
  cylinderTransform_->setTranslation(QVector3D(0, cylinder_->length() / 2, 0));

  Qt3DCore::QTransform rot;

  if (is_time_axis)
    rot.setRotationX(-90.0f);
  else
    rot.setRotationZ(rotation - 90.0f);

  cylinderTransform_->setMatrix(rot.matrix() * cylinderTransform_->matrix());

  Qt3DExtras::QDiffuseSpecularMaterial* cylinderMaterial = new Qt3DExtras::QDiffuseSpecularMaterial();
  cylinderMaterial->setDiffuse(color_);

  // Cylinder
  Qt3DCore::QEntity* cylinderEntity = new Qt3DCore::QEntity(rootEntity_);
  cylinderEntity->addComponent(cylinder_);
  cylinderEntity->addComponent(cylinderMaterial);
  cylinderEntity->addComponent(cylinderTransform_);

  // Cone shape data
  cone_->setTopRadius(0);
  if(isVariable_)
    cone_->setBottomRadius(3);
  else
    cone_->setBottomRadius(3 * 0.75f);
  if (!isVariable_ || abs(variable_->getValue()) != 0)
    cone_->setLength(CONE_LENGTH);
  else
    cone_->setLength(0);
  cone_->setRings(50);
  cone_->setSlices(20);

  // ConeMesh Transform
  coneTransform_->setTranslation(QVector3D(0, cylinder_->length() / 2 + cone_->length() / 2, 0));

  Qt3DExtras::QDiffuseSpecularMaterial* coneMaterial = new Qt3DExtras::QDiffuseSpecularMaterial();
  coneMaterial->setDiffuse(color_);

  // Cone
  Qt3DCore::QEntity* coneEntity = new Qt3DCore::QEntity(cylinderEntity);
  coneEntity->addComponent(cone_);
  coneEntity->addComponent(coneMaterial);
  coneEntity->addComponent(coneTransform_);
}

CustomArrow::~CustomArrow()
{
  delete cylinder_;
  delete cylinderTransform_;
  delete cone_;
  delete coneTransform_;
}

void CustomArrow::update(double scale, double rotationAngle, bool moveOnTimeAxis)
{
  if (!isVariable_ || abs(variable_->getValue()) != 0 || scale != 0)
  {
    cylinder_->setLength(abs(variable_->getValue()) * 100 / scale - CONE_LENGTH);
    cone_->setLength(CONE_LENGTH);
  }
  else
  {
    cylinder_->setLength(0);
    cone_->setLength(0);
  }
  
  QVector3D translation(0, cylinder_->length() / 2, 0);

  if (moveOnTimeAxis)
    translation.setZ(-rotationAngle / 360 * 200);

  QMatrix4x4 identity;
  cylinderTransform_->setMatrix(identity);
  cylinderTransform_->setTranslation(translation);

  Qt3DCore::QTransform* rot = new Qt3DCore::QTransform();
  rot->setRotationZ(((180 * arg(variable_->getValue())) / M_PI - 90.0f) + rotationAngle);
  
  cylinderTransform_->setMatrix(rot->matrix() * cylinderTransform_->matrix());
  coneTransform_->setTranslation(QVector3D(0, cylinder_->length() / 2 + cone_->length() / 2, 0));
}

void CustomArrow::setVisible(bool visibility)
{
  cylinder_->setEnabled(visibility);
  cone_->setEnabled(visibility);
}

ComplexVar* CustomArrow::getVariable()
{
  return variable_;
}


