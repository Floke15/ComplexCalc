#include "label.h"

#include <QVector3D>
#include <Qt3DExtras/QSphereMesh>

Label::Label(Qt3DCore::QEntity* rootEntity, QVector3D position, QString text, QColor color) :
  rootEntity_(rootEntity),
  position_(position)
{
  // Sphere shape data
  Qt3DExtras::QSphereMesh* sphere2 = new Qt3DExtras::QSphereMesh();
  sphere2->setRadius(0);
  sphere2->setRings(2);
  sphere2->setSlices(1);

  sphereTransform_ = new Qt3DCore::QTransform();
  sphereTransform_->setTranslation(position_);

  // Sphere
  Qt3DCore::QEntity* sphereEntity2 = new Qt3DCore::QEntity(rootEntity_);
  sphereEntity2->addComponent(sphere2);
  sphereEntity2->addComponent(sphereTransform_);

  Qt3DCore::QTransform* textTransform = new Qt3DCore::QTransform();
  textTransform->setTranslation(QVector3D(-6, -5.75, 0));

  textDescriptor_ = new Qt3DExtras::QText2DEntity(sphereEntity2);
  textDescriptor_->setFont(QFont("monospace", 8));
  textDescriptor_->setHeight(11.5);
  textDescriptor_->setWidth(12);
  textDescriptor_->setText(text);
  textDescriptor_->setColor(color);
  textDescriptor_->addComponent(textTransform);
}

void Label::update(QVector3D cameraPosition, QVector3D upVector)
{
  QVector3D look = cameraPosition - sphereTransform_->translation() - QVector3D(-6, -5.75, 0);
  look.normalize();
  QVector3D right = QVector3D::crossProduct(upVector, look);
  QVector3D up2 = QVector3D::crossProduct(look, right);
  QMatrix4x4 transform = { right.x(), up2.x(), look.x(), position_.x(),
                           right.y(), up2.y(), look.y(), position_.y(),
                           right.z(), up2.z(), look.z(), position_.z(),
                           0, 0, 0, 1 };
  sphereTransform_->setMatrix(transform);
}

void Label::setVisible(bool visibility)
{
  textDescriptor_->setEnabled(visibility);
}

