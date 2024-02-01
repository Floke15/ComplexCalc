#ifndef TRACE_H
#define TRACE_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QGeometry>

class ComplexVar;

class Trace : public Qt3DCore::QGeometry
{
public:
  Trace(Qt3DCore::QEntity* rootEntity, ComplexVar* variable);
  Trace(Qt3DCore::QEntity* rootEntity, QVector<QVector3D>* points);

  void update();

private:
  QVector3D getOrthogonalVector(const QVector3D& vec);
  QVector<QVector3D> interpolatePath(const QVector<QVector3D>& path);
  QVector<QVector3D> buildCircleNormals(const QVector3D& dir);
  void updateGeometry(const QVector<QVector3D>& vertices, const QVector<QVector3D>& normals, const QVector<quint32>& indices);
  Qt3DCore::QAttribute* createIndexBuffer(const QVector<quint32>& indices, Qt3DCore::QGeometry* parent);
  Qt3DCore::QAttribute* create3DBuffer(const QVector<QVector3D>& vertices, const QString& name, Qt3DCore::QGeometry* parent);

  ComplexVar* variable_;
  QVector<QVector3D>* points_;
};


















#endif // TRACE_H

Qt3DCore::QAttribute* createIndexBuffer(const QVector<quint32>& indices, Qt3DCore::QGeometry* parent);
