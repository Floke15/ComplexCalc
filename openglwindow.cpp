#include "openglwindow.h"
#include "customarrow.h"
#include "complexvar.h"
#include "complexcalc.h"

#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcamera.h>
#include <Qt3DRender/qpointlight.h>
#include <qmouseevent.h>

OpenGLWindow::OpenGLWindow(bool isMainWindow) :
  isMainWindow_(isMainWindow),
  rootEntity_(new Qt3DCore::QEntity()),
  scale_(0),
  time_(0),
  isDragging_(false),
  currentAngleX_(0),
  currentAngleZ_(0),
  Qt3DExtras::Qt3DWindow()
{
  defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

  // Camera
  Qt3DRender::QCamera* cameraEntity = camera();

  setOrthographicProjection();

  cameraEntity->setPosition(QVector3D(0, 0, 300));
  cameraEntity->setUpVector(QVector3D(0, 1, 0));
  cameraEntity->setViewCenter(QVector3D(0, 0, 0));

  Qt3DCore::QEntity* lightEntity = new Qt3DCore::QEntity(rootEntity_);
  Qt3DRender::QPointLight* light = new Qt3DRender::QPointLight(lightEntity);
  light->setColor("white");
  light->setIntensity(1);
  lightEntity->addComponent(light);
  Qt3DCore::QTransform* lightTransform = new Qt3DCore::QTransform(lightEntity);
  lightTransform->setTranslation(cameraEntity->position());
  lightEntity->addComponent(lightTransform);

  CustomArrow* realPositiveAxis = new CustomArrow(rootEntity_, QVector2D(0, 0), 110, 0);
  CustomArrow* realNegativeAxis = new CustomArrow(rootEntity_, QVector2D(0, 0), 110, 180.0f);
  CustomArrow* imagPositiveAxis = new CustomArrow(rootEntity_, QVector2D(0, 0), 110, 90.0f);
  CustomArrow* imagNegativeAxis = new CustomArrow(rootEntity_, QVector2D(0, 0), 110, 270.0f);

  setRootEntity(rootEntity_);
}

void OpenGLWindow::resizeEvent(QResizeEvent* event)
{
  Qt3DExtras::Qt3DWindow::resizeEvent(event);

  if (!isMainWindow_ || currentAngleX_ < 1 || currentAngleX_ > 89)
    setOrthographicProjection();
}

void OpenGLWindow::setOrthographicProjection()
{
  int width = this->width();
  int height = this->height();
  int ref_size = 220;

  float ratio = static_cast<float>(width) / static_cast<float>(height);

  if (isMainWindow_)
    ref_size = 240;

  if (ratio >= 1.0)
  {
    height = ref_size;
    width = ratio * height;
  }
  else
  {
    width = ref_size;
    height = width / ratio;
  }

  camera()->lens()->setOrthographicProjection(-width / 2, width / 2, -height / 2, height / 2, 0.1, 1000);
}

void OpenGLWindow::mousePressEvent(QMouseEvent* mouseEvent)
{
  lastPos_ = mouseEvent->localPos();
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* mouseEvent)
{
  if (mouseEvent->buttons() == Qt::LeftButton && isMainWindow_)
  {
    float angle_change_x = -(mouseEvent->localPos() - lastPos_).x();
    float angle_change_z = (mouseEvent->localPos() - lastPos_).y();
    lastPos_ = mouseEvent->localPos();

    bool was_at_limit_x = currentAngleX_ < 1 || currentAngleX_ > 89;
    bool is_at_limit_x = (currentAngleX_ + angle_change_x) < 1 || (currentAngleX_ + angle_change_x) > 89;

    if (is_at_limit_x && !was_at_limit_x)
      setOrthographicProjection();
    else if (!is_at_limit_x && was_at_limit_x)
      camera()->lens()->setPerspectiveProjection(45, static_cast<float>(this->width()) / static_cast<float>(this->height()), 0.1, 1000);

    if (currentAngleX_ + angle_change_x < 0)
      angle_change_x = -currentAngleX_;
    else if (currentAngleX_ + angle_change_x > 90)
      angle_change_x = 90 - currentAngleX_;

    if (currentAngleZ_ + angle_change_z < 0)
      angle_change_z = -currentAngleZ_;
    else if (currentAngleZ_ + angle_change_z > 90)
      angle_change_z = 90 - currentAngleZ_;

    camera()->panAboutViewCenter(angle_change_x);
    camera()->panAboutViewCenter(angle_change_z, QVector3D(0, 0, 1));

    currentAngleX_ += angle_change_x;
    currentAngleZ_ += angle_change_z;
  }
}

void OpenGLWindow::insertVariable(ComplexVar* variable)
{
  //TODO: other function that adds at other pos that origin
  //TODO: check if arrow of variable with the same origin already exists

  CustomArrow* variable_arrow = new CustomArrow(rootEntity_, QVector2D(0, 0), variable, QColor(255, 0, 0, 255));

  connect(variable, &ComplexVar::variable_value_changed, this, &OpenGLWindow::rescaleAxes);

  arrows_.push_back(variable_arrow);

  rescaleAxes();
}

void OpenGLWindow::removeAllVariables()
{
  for (auto iter : arrows_)
  {
    disconnect(iter->getVariable(), &ComplexVar::variable_value_changed, this, &OpenGLWindow::rescaleAxes);

    delete iter;
  }

  arrows_.clear();
}

void OpenGLWindow::setTime(int time)
{
  time_ = time;
    
  for (auto iter : arrows_)
  {
    if (iter->getVariable() != nullptr)
      iter->update(scale_, time_ * 0.36);
  }
}

void OpenGLWindow::rescaleAxes()
{
  findScale();

  for (auto iter : arrows_)
  {
    if(iter->getVariable() != nullptr)
      iter->update(scale_, time_ * 0.36);
  }
}

void OpenGLWindow::findScale()
{
  double biggest_value = 0;

  for (auto iter : arrows_)
  {
    std::complex<double> value = iter->getVariable()->getValue();
    biggest_value = abs(value) > biggest_value ? abs(value) : biggest_value;
  }

  double log_value = log10(biggest_value);
  int ceil_value = ceil(log_value);
  if (((double)pow(10, ceil_value) - biggest_value) == 0)
      ceil_value++;

  scale_ = pow(10.0, (double) ceil_value);

  if ((double) ceil_value - 1 + 0.69897 > log_value)     // log(5) = 0,69897
      scale_ /= 2;
}

bool OpenGLWindow::hasArrow()
{
  return !arrows_.empty();
}

