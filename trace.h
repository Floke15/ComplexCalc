#ifndef TRACE_H
#define TRACE_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QGeometry>

class ComplexVar;

class Trace : public Qt3DCore::QGeometry
{
public:
  Trace(Qt3DCore::QEntity* rootEntity, ComplexVar* variable);

  void update(double scale, double rotationAngle = 360);

private:
  void calculatePoints(double scale);
  void init3DElements(Qt3DCore::QEntity* rootEntity);
  QVector3D getOrthogonalVector(const QVector3D& vec);
  QVector<QVector3D> buildCircleNormals(const QVector3D& dir);
  void updateGeometry(const QVector<QVector3D>& vertices, const QVector<QVector3D>& normals, const QVector<quint32>& indices);
  Qt3DCore::QAttribute* createIndexBuffer(const QVector<quint32>& indices, Qt3DCore::QGeometry* parent);
  Qt3DCore::QAttribute* create3DBuffer(const QVector<QVector3D>& vertices, const QString& name, Qt3DCore::QGeometry* parent);

  Qt3DCore::QEntity* rootEntity_;
  ComplexVar* variable_;
  QVector<QVector3D>* points_;
  double scale_;
};

#endif // TRACE_H
