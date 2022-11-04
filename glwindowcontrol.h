#ifndef GLWINDOWCONTROL_H
#define GLWINDOWCONTROL_H

#include <Qt3DExtras/qt3dwindow.h>
#include <complex>

#include "complexcalc.h"

class GLWindowControl
{
public:
  GLWindowControl(Qt3DExtras::Qt3DWindow* glWindow);
  //~GLWindowControl();

private:
  Qt3DExtras::Qt3DWindow* glWindow_;
};
#endif // GLWINDOWCONTROL_H
