#ifndef WINDOWINGSYSTEMMANAGER_H
#define WINDOWINGSYSTEMMANAGER_H

#define portable_usleep(t) select(0, NULL, NULL,NULL, t)
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

#define XRightArrow 0xff53
#define XLeftArrow  0xff51

enum { MOUSE_RIGHT_CLICK, MOUSE_LEFT_CLICK };

class WindowingSystemManager
{
  WindowingSystemManager();

public:
  static void mouseClick(int x, int y);
  static void simulateButtonClick(unsigned int key);
};


#endif // WINDOWINGSYSTEMMANAGER_H
