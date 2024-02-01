// SOURCE: https://github.com/pinebit/JetPipes
// Author: Andrei Smirnov
// Edited to fit this usecase

#include "trace.h"
#include "spline.h"

#include <QVector3D>
#include <QMatrix4x4>

Trace::Trace(Qt3DCore::QEntity* rootEntity, ComplexVar* variable) :
  Qt3DCore::QGeometry(rootEntity),
  variable_(variable),
  points_(new QVector<QVector3D>())
{
  update();
}

Trace::Trace(Qt3DCore::QEntity* rootEntity, QVector<QVector3D>* points) :
  Qt3DCore::QGeometry(rootEntity),
  variable_(nullptr),
  points_(points)
{
  update();
}

void Trace::update()
{
  int tube_radius = 5, tube_segments = 16;

  QVector<QVector3D> vertices;
  QVector<QVector3D> normals;
  QVector<quint32> indices;

  if (variable_)
    assert("");
  //TODO: calculate Points from Variable (same amount as in slider)

  const QVector<QVector3D> interpolated = interpolatePath(*points_);

  QVector<QVector3D> prevNormals;
  for (int ii = 0; ii < interpolated.size(); ++ii) {
    const auto current = interpolated[ii];
    QVector3D direction;
    if (ii == interpolated.size() - 1) {
      direction = (current - interpolated[ii - 1]).normalized();
    }
    else {
      direction = (interpolated[ii + 1] - current).normalized();
    }
    if (direction.isNull()) {
      continue;
    }

    QVector<QVector3D> circleNormals = buildCircleNormals(direction);
    int startIndex = 0;
    if (ii > 0) {
      float minDist = 0.0f;
      int index = -1;
      for (int in = 0; in < circleNormals.size(); ++in) {
        float dist = circleNormals[in].distanceToPoint(prevNormals[0]);
        if (index < 0) {
          index = 0;
          minDist = dist;
        }
        else if (dist < minDist) {
          minDist = dist;
          index = in;
        }
      }
      startIndex = index;
    }

    const auto fixedNormals = startIndex == 0 ? circleNormals : (circleNormals.mid(startIndex) + circleNormals.mid(0, startIndex));

    for (auto n : fixedNormals) {
      const auto v = current + n * tube_radius;
      vertices << v;
      normals << n;
    }

    prevNormals = fixedNormals;
  }

  const QVector3D zeroNormal(0, 0, 0);
  for (int i = 0; i < tube_segments; ++i) {
    vertices.prepend(interpolated.first());
    normals.prepend(zeroNormal);
    vertices.append(interpolated.last());
    normals.append(zeroNormal);
  }

  const quint32 maxVertexIndex = vertices.size() - 1;
  for (int ci = 0; ci <= interpolated.size(); ++ci) {
    for (int si = 0; si < tube_segments; ++si) {
      int p0Index = ci * tube_segments + si;
      int p1Index = p0Index + 1;
      int p2Index = p0Index + tube_segments;
      int p3Index = p2Index + 1;
      if (si == tube_segments - 1) {
        p1Index -= tube_segments;
        p3Index -= tube_segments;
      }

      quint32 vertexIndex1 = p0Index;
      quint32 vertexIndex2 = p1Index;
      quint32 vertexIndex3 = p2Index;
      if (vertexIndex1 <= maxVertexIndex &&
        vertexIndex2 <= maxVertexIndex &&
        vertexIndex3 <= maxVertexIndex) {
        indices << vertexIndex1 << vertexIndex2 << vertexIndex3;
      }

      vertexIndex1 = p1Index;
      vertexIndex2 = p3Index;
      vertexIndex3 = p2Index;
      if (vertexIndex1 <= maxVertexIndex &&
        vertexIndex2 <= maxVertexIndex &&
        vertexIndex3 <= maxVertexIndex) {
        indices << vertexIndex1 << vertexIndex2 << vertexIndex3;
      }
    }
  }

  updateGeometry(vertices, normals, indices);
}

QVector3D Trace::getOrthogonalVector(const QVector3D& vec)
{
  bool b0 = (vec[0] < vec[1]) && (vec[0] < vec[2]);
  bool b1 = (vec[1] <= vec[0]) && (vec[1] < vec[2]);
  bool b2 = (vec[2] <= vec[0]) && (vec[2] <= vec[1]);

  return QVector3D::crossProduct(vec, QVector3D(int(b0), int(b1), int(b2)));
}

QVector<QVector3D> Trace::interpolatePath(const QVector<QVector3D>& path)
{
  QVector<SplineLib::Vec3f> points;
  for (auto pp : path) {
    points << SplineLib::Vec3f(pp.x(), pp.y(), pp.z());
  }

  int numSplines = points.size() + 1;
  SplineLib::cSpline3* splines = new SplineLib::cSpline3[numSplines];
  numSplines = SplinesFromPoints(points.size(), points.constData(), numSplines, splines);

  QVector<QVector3D> interpolated;
  for (int i = 0; i < numSplines; ++i) {
    const int split = static_cast<int>(Length(splines[i])) * 2;
    for (int k = 0; k < split; ++k) {
      const double u = (double)k / split;
      const auto v3 = Position(splines[i], u);
      interpolated << QVector3D(v3.x, v3.y, v3.z);
    }
  }

  delete[]splines;
  return interpolated;
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
    const auto normal = rot * cv;
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