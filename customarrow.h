#ifndef CUSTOMARROW_H
#define CUSTOMARROW_H

#include <Qt3DExtras/qcylindermesh.h>
#include <Qt3DCore/qtransform.h>
#include <qcolor.h>

class CustomArrow
{
public:
  CustomArrow(Qt3DCore::QEntity* rootEntity, QVector2D translation, float length, float rotation, QColor color = QColor(QRgb(0x000000)));
  ~CustomArrow();

private:
  Qt3DCore::QEntity* rootEntity_;
  Qt3DCore::QTransform* sphereTransform_;
  Qt3DExtras::QCylinderMesh* cylinder_;
  Qt3DCore::QTransform* cylinderTransform_;
  QColor color_;
};


#endif // CUSTOMARROW_H