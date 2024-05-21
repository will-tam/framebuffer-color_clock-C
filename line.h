#ifndef _LINE_H
#define _LINE_H

/*
  Draw line. 
  Parameters : *fbp = Framebuffer structure pointer address.
               (x0; y0) = one the point of the line.
               (x1; y1) = the other point of the line.
               r, g, b, alpha = RGB-Alpha color.
  Return : void.
*/
void line(struct framebuffer *fbp,
          int x0, int y0, int x1, int y1, 
          unsigned int r, unsigned int g, unsigned int b, unsigned int alpha);

#endif