#include "header/openglwindow.h"
#include "header/customarrow.h"
#include "header/complexvar.h"
#include "header/complexcalc.h"
#include "header/trace.h"
#include "header/label.h"

#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QPointLight>
#include <QMouseEvent>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/QDiffuseSpecularMaterial>

OpenGLWindow::OpenGLWindow(bool isMainWindow) :
  isMainWindow_(isMainWindow),
  rootEntity_(new Qt3DCore::QEntity()),
  scale_(0),
  time_(0),
  currentAngleX_(0),
  currentAngleZ_(0),
  arrows_(),
  traces_(),
  timeAxis_(new CustomArrow(rootEntity_, -220, 0)),
  lightTransform_(new Qt3DCore::QTransform()),
  tickRealEntity_(new Qt3DCore::QEntity(rootEntity_)),
  tickImagEntity_(new Qt3DCore::QEntity(rootEntity_)),
  tickTimeEntity_(new Qt3DCore::QEntity(rootEntity_)),
  realAxisLabel_(new Label(rootEntity_, QVector3D(110 - (CONE_LENGTH / 2), -9, -9), "Re", Qt::black)),
  imagAxisLabel_(new Label(rootEntity_, QVector3D(9, 110 - (CONE_LENGTH / 2), -9), "Im", Qt::black)),
  timeAxisLabel_(new Label(rootEntity_, QVector3D(9, 9, -(220 - (CONE_LENGTH / 2))), "t", Qt::black)),
  tickRealLabel_(new Label(rootEntity_, QVector3D(100, 7, 1), QString::number(scale_), Qt::black, 5, Qt::AlignRight)),
  tickImagLabel_(new Label(rootEntity_, QVector3D(-7, 100, 1), QString::number(scale_), Qt::black, 5, Qt::AlignRight)),
  tickTimeLabel_(new Label(rootEntity_, QVector3D(-7, -7, -200), "2π/ω", Qt::black, 5)),
  Qt3DExtras::Qt3DWindow(nullptr, Qt3DRender::API::OpenGL)
{
  defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

  setOrthographicProjection();

  camera()->setPosition(QVector3D(0, 0, 300));
  camera()->setUpVector(QVector3D(0, 1, 0));
  camera()->setViewCenter(QVector3D(0, 0, -110));

  Qt3DCore::QEntity* lightEntity = new Qt3DCore::QEntity(rootEntity_);
  Qt3DRender::QPointLight* light = new Qt3DRender::QPointLight(lightEntity);
  light->setColor("white");
  light->setIntensity(1);
  lightEntity->addComponent(light);
  lightTransform_->setTranslation(camera()->position());
  lightEntity->addComponent(lightTransform_);

  CustomArrow* realPositiveAxis = new CustomArrow(rootEntity_, 110, 0);
  CustomArrow* realNegativeAxis = new CustomArrow(rootEntity_, 110, 180.0f);
  CustomArrow* imagPositiveAxis = new CustomArrow(rootEntity_, 110, 90.0f);
  CustomArrow* imagNegativeAxis = new CustomArrow(rootEntity_, 110, 270.0f);
  timeAxis_->setVisible(false);
  timeAxisLabel_->setVisible(false);

  Qt3DExtras::QCylinderMesh* tick = new Qt3DExtras::QCylinderMesh();
  tick->setRadius(3);
  tick->setLength(0.5);
  tick->setRings(3);
  tick->setSlices(20);

  Qt3DExtras::QDiffuseSpecularMaterial* tickMaterial = new Qt3DExtras::QDiffuseSpecularMaterial();
  tickMaterial->setDiffuse(QColor(0, 0, 0));

  Qt3DCore::QTransform* tickRealTransform = new Qt3DCore::QTransform();
  tickRealTransform->setTranslation(QVector3D(100 - 0.25, 0, 0));
  tickRealTransform->setRotationZ(90);

  tickRealEntity_->addComponent(tick);
  tickRealEntity_->addComponent(tickMaterial);
  tickRealEntity_->addComponent(tickRealTransform);

  Qt3DCore::QTransform* tickImagTransform = new Qt3DCore::QTransform();
  tickImagTransform->setTranslation(QVector3D(0, 100 - 0.25, 0));

  tickImagEntity_->addComponent(tick);
  tickImagEntity_->addComponent(tickMaterial);
  tickImagEntity_->addComponent(tickImagTransform);

  Qt3DCore::QTransform* tickTimeTransform = new Qt3DCore::QTransform();
  tickTimeTransform->setTranslation(QVector3D(0, 0, -200 + 0.25));
  tickTimeTransform->setRotationX(90);

  tickTimeEntity_->addComponent(tick);
  tickTimeEntity_->addComponent(tickMaterial);
  tickTimeEntity_->addComponent(tickTimeTransform);

  tickTimeLabel_->setVisible(false);
  tickTimeEntity_->setEnabled(false);

  setRootEntity(rootEntity_);
}

void OpenGLWindow::resizeEvent(QResizeEvent* event)
{
  Qt3DExtras::Qt3DWindow::resizeEvent(event);

  if (!isMainWindow_ || currentAngleX_ < 1 || currentAngleX_ > 89)
    setOrthographicProjection();
}

void OpenGLWindow::setOrthographicProjection() const
{
  int width = this->width();
  int height = this->height();
  float ratio = static_cast<float>(width) / static_cast<float>(height);
  int ref_size = 220;

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

  camera()->lens()->setOrthographicProjection(-static_cast<float>(width) / 2, static_cast<float>(width) / 2, -static_cast<float>(height) / 2, static_cast<float>(height) / 2, 0.1, 1000);
}

void OpenGLWindow::mousePressEvent(QMouseEvent* mouseEvent)
{
  lastPos_ = mouseEvent->position();
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* mouseEvent)
{
  if (mouseEvent->buttons() == Qt::LeftButton && isMainWindow_)
  {
    float angle_change_x = -(mouseEvent->position() - lastPos_).x() / 2;
    float angle_change_z = (mouseEvent->position() - lastPos_).y() / 2;
    lastPos_ = mouseEvent->position();

    bool was_at_limit_x = currentAngleX_ < 1 || currentAngleX_ > 89;
    bool is_at_limit_x = (currentAngleX_ + angle_change_x) < 1 || (currentAngleX_ + angle_change_x) > 89;

    if (is_at_limit_x && !was_at_limit_x)
    {
      setOrthographicProjection();
      if ((currentAngleX_ + angle_change_x) < 1)
      {
        timeAxis_->setVisible(false);
        timeAxisLabel_->setVisible(false);
        tickTimeLabel_->setVisible(false);
        tickTimeEntity_->setEnabled(false);
      }
    }
    else if (!is_at_limit_x && was_at_limit_x)
    {
      camera()->lens()->setPerspectiveProjection(45, static_cast<float>(this->width()) / static_cast<float>(this->height()), 0.1, 1000);
      timeAxis_->setVisible(true);
      timeAxisLabel_->setVisible(true);
      tickTimeLabel_->setVisible(true);
      tickTimeEntity_->setEnabled(true);
    }

    if (currentAngleX_ + angle_change_x < 0)
      angle_change_x = -currentAngleX_;
    else if (currentAngleX_ + angle_change_x > 90)
      angle_change_x = 90 - currentAngleX_;

    if (currentAngleZ_ + angle_change_z < -90)
      angle_change_z = -90 - currentAngleZ_;
    else if (currentAngleZ_ + angle_change_z > 0)
      angle_change_z = -currentAngleZ_;

    camera()->panAboutViewCenter(angle_change_x);
    camera()->panAboutViewCenter(angle_change_z, QVector3D(0, 0, 1));
    lightTransform_->setTranslation(camera()->position());

    currentAngleX_ += angle_change_x;
    currentAngleZ_ += angle_change_z;

    realAxisLabel_->update(camera()->position(), camera()->upVector());
    imagAxisLabel_->update(camera()->position(), camera()->upVector());
    timeAxisLabel_->update(camera()->position(), camera()->upVector());

    tickRealLabel_->update(camera()->position(), camera()->upVector());
    tickImagLabel_->update(camera()->position(), camera()->upVector());
    tickTimeLabel_->update(camera()->position(), camera()->upVector());

    bool enableRealAxis = !(currentAngleX_ > 89 && currentAngleZ_ > -1);
    bool enableImagAxis = !(currentAngleX_ > 89 && currentAngleZ_ < -89);

    realAxisLabel_->setVisible(enableRealAxis);
    tickRealLabel_->setVisible(enableRealAxis);
    tickRealEntity_->setEnabled(enableRealAxis);

    imagAxisLabel_->setVisible(enableImagAxis);
    tickImagLabel_->setVisible(enableImagAxis);
    tickImagEntity_->setEnabled(enableImagAxis);
  }
}

void OpenGLWindow::insertVariable(ComplexVar* variable, bool with_trace)
{
  //TODO: other function that adds at other pos that origin
  //TODO: check if arrow of variable with the same origin already exists

  CustomArrow* variable_arrow = new CustomArrow(rootEntity_, variable, QColor(255, 0, 0, 255));

  if (with_trace)
  {
    traces_.push_back(new Trace(rootEntity_, variable, scale_));
  }

  arrows_.push_back(variable_arrow);

  update();
}

void OpenGLWindow::removeAllVariables()
{
  for (auto iter : arrows_)
  {
    delete iter;
  }

  for (auto iter : traces_)
    delete iter;

  arrows_.clear();
  traces_.clear();
}

void OpenGLWindow::setTime(int time)
{
  time_ = time;
    
  for (auto iter : arrows_)
  {
    if (iter->getVariable() != nullptr)
      iter->update(scale_, time_ * 0.36, isMainWindow_);
  }

  for (auto iter : traces_)
  {
    iter->update(scale_, time_ * 0.36);
  }
}

void OpenGLWindow::update()
{
  findScale();

  tickRealLabel_->setText(QString::number(scale_));
  tickImagLabel_->setText(QString::number(scale_));

  for (auto iter : arrows_)
  {
    if(iter->getVariable() != nullptr)
      iter->update(scale_, time_ * 0.36, isMainWindow_);
  }

  for (auto iter : traces_)
  {
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

