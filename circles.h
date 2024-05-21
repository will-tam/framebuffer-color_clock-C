#ifndef _CIRCLE_H
#define _CIRCLE_H

/* 
  Draw circle.
  Parameters : *fbp = Framebuffer structure pointer address.
               (xc; yc) = center of the circle.
               radius = radius of the circle.
               r, g, b, alpha = RGB-Alpha color.
  Return : void.
*/
void circle(struct framebuffer *fbp,
            int xc, int yc, int radius,
            unsigned int r, unsigned int g, unsigned int b, unsigned int alpha);

/* 
  Draw circle with rotation of colors.
  Parameters : *fbp = Framebuffer structure pointer address.
               *offsetFrameColor = chanching clock color offset pointer address.
               (xc; yc) = center of the circle.
               radius = radius of the circle.
  Return : void.
*/
void circlerotationcolor(struct framebuffer *fbp,
                         float *offsetFrameColor,
                         int xc, int yc, int radius);	

#endif