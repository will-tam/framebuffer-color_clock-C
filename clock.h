#ifndef _CLOCK_H
#define _CLOCK_H

#include "fbtools.h"

/*
  Init some usefull variables.
  Parameters : Framebuffer structure pointer address.
  Return : void.
*/
void clockinit(struct framebuffer *fbp);

/*
  Put a big point on the clock. Each one represents a hour.
  Parameters : *fbp = Framebuffer structure pointer address.
               (x; y) = center of the big point.
               radius = radius of the big point.
*/
void big_point(struct framebuffer *fbp, int x, int y, int radius);

/*
  Update the clock design.
  Parameters : Framebuffer structure pointer address.
  Return : void.
*/
void clockupdate(struct framebuffer *fbp);

#endif