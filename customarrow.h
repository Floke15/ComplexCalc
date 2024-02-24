#ifndef CUSTOMARROW_H
#define CUSTOMARROW_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QConeMesh>
#include <QColor>

#define CONE_LENGTH 6.0f

class ComplexVar;

class CustomArrow
{
public:
  CustomArrow(Qt3DCore::QEntity* rootEntity, float length, float rotation);
  CustomArrow(Qt3DCore::QEntity* rootEntity, ComplexVar* variable, QColor color);
  ~CustomArrow();

  void update(double scale, double rotationAngle, bool moveOnTimeAxis = true);
  void setVisible(bool visibility);
  ComplexVar* getVariable();

private:
  CustomArrow(Qt3DCore::QEntity* rootEntity, float length, float rotation, ComplexVar* variable, QColor color, bool isVariable);

  Qt3DCore::QEntity* rootEntity_;
  Qt3DExtras::QCylinderMesh* cylinder_;
  Qt3DCore::QTransform* cylinderTransform_;
  Qt3DExtras::QConeMesh* cone_;
  Qt3DCore::QTransform* coneTransform_;
  ComplexVar* variable_;
  QColor color_;
  bool isVariable_;
};


#endif // CUSTOMARROW_H