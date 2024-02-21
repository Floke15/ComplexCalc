#include "label.h"

#include <QVector3D>
#include <Qt3DExtras/QSphereMesh>
#include <QFontMetricsF>

Label::Label(Qt3DCore::QEntity* rootEntity, QVector3D position, QString text, QColor color, float fontsize, int flags) :
  rootEntity_(rootEntity),
  position_(position),
  flags_(flags)
{
  // Sphere shape data
  Qt3DExtras::QSphereMesh* sphere = new Qt3DExtras::QSphereMesh();
  sphere->setRadius(0);
  sphere->setRings(2);
  sphere->setSlices(1);

  sphereTransform_ = new Qt3DCore::QTransform();
  sphereTransform_->setTranslation(position_);

  // Sphere
  Qt3DCore::QEntity* sphereEntity = new Qt3DCore::QEntity(rootEntity_);
  sphereEntity->addComponent(sphere);
  sphereEntity->addComponent(sphereTransform_);

  textDescriptor_ = new Qt3DExtras::QText2DEntity(sphereEntity);
  textDescriptor_->setFont(QFont("monospace", fontsize));
  textDescriptor_->setColor(color);

  textTransform_ = new Qt3DCore::QTransform();
  textDescriptor_->addComponent(textTransform_);

  setText(text);
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

void Label::setText(QString text)
{
  auto fontMetrics = QFontMetricsF{ textDescriptor_->font() };
  auto boundingRect = fontMetrics.boundingRect(
    QRectF{},
    Qt::AlignLeft | Qt::AlignTop,
    text);
  textDescriptor_->setWidth(boundingRect.width() + 1);
  textDescriptor_->setHeight(boundingRect.height() + 1);

  QVector3D textTranslation = { 0, -textDescriptor_->height() / 2, 0 };
  if (flags_ & Qt::AlignCenter)
    textTranslation.setX(-textDescriptor_->width() / 2);
  else if(flags_ & Qt::AlignRight)
    textTranslation.setX(-textDescriptor_->width());

  textTransform_->setTranslation(textTranslation);

  textDescriptor_->setText(text);
}

