// SOURCE: https://github.com/pinebit/JetPipes
// Author: Andrei Smirnov
// Edited to fit this usecase

#include "trace.h"
#include "complexvar.h"

#include <QVector3D>
#include <QMatrix4x4>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DExtras/QDiffuseSpecularMaterial>
#include <Qt3DCore/QTransform>

Trace::Trace(Qt3DCore::QEntity* rootEntity, ComplexVar* variable) :
  Qt3DCore::QGeometry(rootEntity),
  rootEntity_(rootEntity),
  variable_(variable),
  scale_(0),
  lastVal_(0),
  vertices_(new QVector<QVector3D>()),
  normals_(new QVector<QVector3D>()),
  indices_(new QVector<QVector<quint32>*>())
{
  calculatePoints(1);
  init3DElements(rootEntity);
}

void Trace::init3DElements(Qt3DCore::QEntity* rootEntity)
{
  Qt3DRender::QGeometryRenderer* traceMesh = new Qt3DRender::QGeometryRenderer();
  traceMesh->setGeometry(this);

  Qt3DCore::QTransform* traceTransform_ = new Qt3DCore::QTransform();
  traceTransform_->setTranslation(QVector3D(0, 0, 0));

  Qt3DExtras::QDiffuseSpecularMaterial* traceMaterial = new Qt3DExtras::QDiffuseSpecularMaterial();
  traceMaterial->setAlphaBlendingEnabled(true);
  traceMaterial->setDiffuse(QColor(0, 0, 255, 150));

  Qt3DCore::QEntity* traceEntity = new Qt3DCore::QEntity(rootEntity);
  traceEntity->addComponent(traceMesh);
  traceEntity->addComponent(traceMaterial);
  traceEntity->addComponent(traceTransform_);
}

void Trace::calculatePoints(double scale)
{
  int trace_points = 1000;
  std::complex<double> scaled_value = variable_->getValue() * (100 / scale);

  QVector<QVector3D> points;

  vertices_->clear();
  normals_->clear();
  indices_->clear();

  for (int i = 0; i <= trace_points; ++i)
  {
    QVector3D value(scaled_value.real(), scaled_value.imag(), -static_cast<float>(i) * 200 / trace_points);
    QMatrix4x4 rotation;
    rotation.rotate(static_cast<float>(i) / trace_points * 360, 0, 0, 1);
    points.push_back(rotation.map(value));
  }

  int length = 1000;
  int tube_radius = 1, tube_segments = 16;

  for (int ii = 0; ii < length; ++ii) {
    QVector3D& current = points[ii];
    QVector3D direction;
    if (ii == length - 1 && ii > 0) {
      direction = (current - points[ii - 1]).normalized();
    }
    else {
      direction = (points[ii + 1] - current).normalized();
    }
    if (direction.isNull()) {
      continue;
    }

    for (auto n : buildCircleNormals(direction)) {
      const auto v = current + n * tube_radius;
      *vertices_ << v;
      *normals_ << n;
    }
  }

  const quint32 maxVertexIndex = vertices_->size() - 1;
  for (int ci = 0; ci < length; ++ci) {
    for (int si = 0; si < tube_segments; ++si) {
      int p0Index = ci * tube_segments + si;
      int p1Index = p0Index + 1;
      int p2Index = p0Index + tube_segments;
      int p3Index = p2Index + 1;
      if (si == tube_segments - 1) {
        p1Index -= tube_segments;
        p3Index -= tube_segments;
      }

      QVector<quint32>* indices = new QVector<quint32>();

      quint32 vertexIndex1 = p0Index;
      quint32 vertexIndex2 = p1Index;
      quint32 vertexIndex3 = p2Index;
      if (vertexIndex1 <= maxVertexIndex &&
        vertexIndex2 <= maxVertexIndex &&
        vertexIndex3 <= maxVertexIndex) {
        *indices << vertexIndex1 << vertexIndex2 << vertexIndex3;
      }

      vertexIndex1 = p1Index;
      vertexIndex2 = p3Index;
      vertexIndex3 = p2Index;
      if (vertexIndex1 <= maxVertexIndex &&
        vertexIndex2 <= maxVertexIndex &&
        vertexIndex3 <= maxVertexIndex) {
        *indices << vertexIndex1 << vertexIndex2 << vertexIndex3;
      }

      indices_->push_back(indices);
    }
  }

  const QVector3D zeroNormal(0, 0, 0);
  for (int i = 0; i < tube_segments; ++i) {
    vertices_->prepend(points.first());
    normals_->prepend(zeroNormal);
    //vertices_->append(points_->at(length));
    //normals_->append(zeroNormal);
  }

  QVector<quint32> indices;
  updateGeometry(*vertices_, *normals_, indices);
}

void Trace::update(double scale, double rotationAngle)
{
  if (scale != scale_ || lastVal_ != variable_->getValue())
  {
    calculatePoints(scale);
    scale_ = scale;
    lastVal_ = variable_->getValue();
  }

  int length = rotationAngle / 360 * 1000;
  int tube_radius = 1, tube_segments = 16;

  QVector<quint32> indices;

  for (int ci = 0; ci < length * tube_segments; ++ci) {
    for (auto i : *(indices_->at(ci)))
      if (i < length * tube_segments)
        indices << i;
  }

  auto attr = attributes().back();
  removeAttribute(attr);
  attr->deleteLater();

  auto indexAttr = Trace::createIndexBuffer(indices, this);
  addAttribute(indexAttr);
}

QVector3D Trace::getOrthogonalVector(const QVector3D& vec)
{
  bool b0 = (vec[0] < vec[1]) && (vec[0] < vec[2]);
  bool b1 = (vec[1] <= vec[0]) && (vec[1] < vec[2]);
  bool b2 = (vec[2] <= vec[0]) && (vec[2] <= vec[1]);

  return QVector3D::crossProduct(vec, QVector3D(int(b0), int(b1), int(b2)));
}

QVector<QVector3D> Trace::buildCircleNormals(const QVector3D& dir)
{
  QVector<QVector3D> normals;
  const auto cv = getOrthogonalVector(dir).normalized();
  QMatrix4x4 rot;

  int tube_segments = 16;

  for (int cs = 0; cs < tube_segments; ++cs) {
    double angle = cs * 360.0 / tube_segments;
    rot.setToIdentity();
    rot.rotate(angle, dir);
    const auto normal = rot.map(cv);
    normals.append(normal);
  }

  return normals;
}


void Trace::updateGeometry(const QVector<QVector3D>& vertices,
  const QVector<QVector3D>& normals,
  const QVector<quint32>& indices)
{
  for (auto attr : attributes()) {
    removeAttribute(attr);
    attr->deleteLater();
  }

  auto positionAttr = Trace::create3DBuffer(vertices, Qt3DCore::QAttribute::defaultPositionAttributeName(), this);
  addAttribute(positionAttr);
  setBoundingVolumePositionAttribute(positionAttr);

  auto normalAttr = Trace::create3DBuffer(normals, Qt3DCore::QAttribute::defaultNormalAttributeName(), this);
  addAttribute(normalAttr);

  auto indexAttr = Trace::createIndexBuffer(indices, this);
  addAttribute(indexAttr);
}

Qt3DCore::QAttribute* Trace::createIndexBuffer(const QVector<quint32>& indices, Qt3DCore::QGeometry* parent)
{
  auto attribute = new Qt3DCore::QAttribute(parent);

  Qt3DCore::QBuffer* dataBuffer = new Qt3DCore::QBuffer(attribute);
  const int rawSize = indices.size() * static_cast<int>(sizeof(uint));
  auto rawData = QByteArray::fromRawData(reinterpret_cast<const char*>(indices.constData()), rawSize);
  rawData.detach();
  dataBuffer->setData(rawData);

  attribute->setAttributeType(Qt3DCore::QAttribute::IndexAttribute);
  attribute->setBuffer(dataBuffer);
  attribute->setVertexBaseType(Qt3DCore::QAttribute::UnsignedInt);
  attribute->setVertexSize(1);
  attribute->setByteOffset(0);
  attribute->setByteStride(sizeof(uint));
  attribute->setCount(static_cast<uint>(indices.size()));

  return attribute;
}

Qt3DCore::QAttribute* Trace::create3DBuffer(const QVector<QVector3D>& vertices, const QString& name, Qt3DCore::QGeometry* parent)
{
  auto attribute = new Qt3DCore::QAttribute(parent);

  QVector<float> values;
  values.reserve(vertices.size() * 3);

  for (const QVector3D& v : vertices) {
    values << v.x() << v.y() << v.z();
  }

  Qt3DCore::QBuffer* dataBuffer = new Qt3DCore::QBuffer(attribute);
  const int rawSize = values.size() * static_cast<int>(sizeof(float));
  auto rawData = QByteArray::fromRawData(reinterpret_cast<const char*>(values.constData()), rawSize);
  rawData.detach();
  dataBuffer->setData(rawData);

  attribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
  attribute->setBuffer(dataBuffer);
  attribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
  attribute->setVertexSize(3);
  attribute->setByteOffset(0);
  attribute->setByteStride(3 * sizeof(float));
  attribute->setName(name);
  attribute->setCount(static_cast<uint>(vertices.size()));

  return attribute;
}
