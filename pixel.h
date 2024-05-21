#ifndef _PIXEL_H
#define _PIXEL_H

#include "fbtools.h"

/* 
  Put pixel in framebuffer fb.
  Parameters : *fbp = Framebuffer structure pointer address.
               (x; y) = position of the pixel.
               r, g, b, alpha = RGB-Alpha color.
  Return : void.
*/
void putpixel(struct framebuffer *fbp, 
              int x, int y,
              unsigned int r, unsigned int g, unsigned int b, unsigned int alpha);

#endif