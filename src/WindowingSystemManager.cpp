#include "WindowingSystemManager.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

void
mouse_click(Display *display, int x, int y, int click_type, struct timeval *t)
{
  Window root;
  XEvent event;

  root = DefaultRootWindow(display);
  XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);

  memset(&event, 0, sizeof(event));

  event.xbutton.type        = ButtonPress;
  event.xbutton.button      = click_type;
  event.xbutton.same_screen = True;

  XQueryPointer(display, root, &event.xbutton.root, &event.xbutton.window,
                &event.xbutton.x_root, &event.xbutton.y_root,
                &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

  event.xbutton.subwindow = event.xbutton.window;

  while(event.xbutton.subwindow) {
    event.xbutton.window = event.xbutton.subwindow;
    XQueryPointer(display, event.xbutton.window,&event.xbutton.root,
                  &event.xbutton.subwindow, &event.xbutton.x_root,
                  &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y,
                  &event.xbutton.state);
  }

  if(XSendEvent(display, PointerWindow, True, 0xfff, &event)==0)
    fprintf(stderr, "XSendEvent()\n");

  XFlush(display);
  portable_usleep(t); /* keeps the click pressed */

  event.type = ButtonRelease;
  event.xbutton.state = 0x100;

  if(XSendEvent(display, PointerWindow, True, 0xfff, &event)==0)
    fprintf(stderr, "XSendEvent()\n");

  XFlush(display);
}


WindowingSystemManager::WindowingSystemManager()
{

}

void WindowingSystemManager::mouseClick(int x, int y)
{
    Display        *display;
    struct timeval t;

    display = XOpenDisplay(NULL);

    if(!display) {
      fprintf(stderr, "Can't open display!\n");
      exit(EXIT_FAILURE);
    }

    t.tv_sec  = 0;
    t.tv_usec = 100000;  /* 0.5 secs */

    mouse_click(display, x, y, MOUSE_LEFT_CLICK, &t);

    XCloseDisplay(display);
}

void WindowingSystemManager::simulateButtonClick(unsigned int key)
{
    unsigned int keycode;

    // Connect to X
    Display *display;
    display = XOpenDisplay(NULL);

           // Get the keycode
    keycode = XKeysymToKeycode(display, key);
    printf("Simulating keycode %d press\n", keycode);

           // Simulate the keypress
    XTestFakeKeyEvent(display, keycode, 1, 0);
    // Release the key
    XTestFakeKeyEvent(display, keycode, 0, 0);

           // Clear the X buffer which actually sends the key press
    XFlush(display);

           // Disconnect from X
    XCloseDisplay(display);
}
