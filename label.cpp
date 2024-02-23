#include "label.h"

#include <QVector3D>
#include <Qt3DExtras/QSphereMesh>
#include <QFontMetricsF>

Label::Label(Qt3DCore::QEntity* rootEntity, QVector3D position, QString text, QColor color, float fontsize, int flags) :
  rootEntity_(rootEntity),
  position_(position),
  flags_(flags),
  localTransform_(new Qt3DCore::QTransform()),
  textTransform_(new Qt3DCore::QTransform()),
  textDescriptor_(new Qt3DExtras::QText2DEntity(rootEntity_))
{
  textDescriptor_->setFont(QFont("monospace", fontsize));
  textDescriptor_->setColor(color);
  textDescriptor_->addComponent(textTransform_);

  setText(text);
}

void Label::update(QVector3D cameraPosition, QVector3D upVector)
{
  QVector3D look = cameraPosition - position_ - localTransform_->translation();
  look.normalize();
  QVector3D right = QVector3D::crossProduct(upVector, look);
  QVector3D up2 = QVector3D::crossProduct(look, right);
  QMatrix4x4 transform = { right.x(), up2.x(), look.x(), position_.x(),
                           right.y(), up2.y(), look.y(), position_.y(),
                           right.z(), up2.z(), look.z(), position_.z(),
                           0, 0, 0, 1 };
  textTransform_->setMatrix(transform * localTransform_->matrix());
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

  localTransform_->setTranslation(textTranslation);
  textTransform_->setTranslation(textTranslation + position_);

  textDescriptor_->setText(text);
}

