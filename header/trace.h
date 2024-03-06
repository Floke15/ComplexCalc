#ifndef TRACE_H
#define TRACE_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QGeometry>
#include <complex>

class ComplexVar;

class Trace : public Qt3DCore::QGeometry
{
public:
  Trace(Qt3DCore::QEntity* rootEntity, ComplexVar* variable, double scale);

  void update(double scale, double rotationAngle = 360);

private:
  void calculatePoints(double scale);
  void init3DElements(Qt3DCore::QEntity* rootEntity);
  QVector3D getOrthogonalVector(const QVector3D& vec);
  QVector<QVector3D> buildCircleNormals(const QVector3D& dir);
  void resetGeometry(const QVector<QVector3D>& vertices, const QVector<QVector3D>& normals, const QVector<quint32>& indices);
  Qt3DCore::QAttribute* createIndexBuffer(const QVector<quint32>& indices, Qt3DCore::QGeometry* parent);
  Qt3DCore::QAttribute* create3DBuffer(const QVector<QVector3D>& vertices, const QString& name, Qt3DCore::QGeometry* parent);

  ComplexVar* variable_;
  double scale_;
  std::complex<double> lastVal_;
  QVector<QVector3D>* vertices_;
  QVector<QVector3D>* normals_;
  QVector<QVector<quint32>*>* indices_;
};

#endif // TRACE_H
