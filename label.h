#ifndef LABEL_H
#define LABEL_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QText2DEntity>

class Label
{
public:
  Label(Qt3DCore::QEntity* rootEntity, QVector3D position, QString text, QColor color = Qt::black, float fontsize = 8, int flags = Qt::AlignCenter);

  void update(QVector3D cameraPosition, QVector3D upVector);
  void setVisible(bool visibility);
  void setText(QString text);

private:
  Qt3DCore::QEntity* rootEntity_;
  QVector3D position_;
  int flags_;
  Qt3DCore::QTransform* sphereTransform_;
  Qt3DExtras::QText2DEntity* textDescriptor_;
  Qt3DCore::QTransform* textTransform_;
};

#endif // LABEL_H
