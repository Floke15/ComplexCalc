#include "glwindowcontrol.h"

#include <Qt3DExtras/qforwardrenderer.h>

GLWindowControl::GLWindowControl(Qt3DExtras::Qt3DWindow* glWindow) :
  glWindow_(glWindow)
{
  glWindow_->defaultFrameGraph()->setClearColor(QColor(QRgb(0x0000FF)));
}
