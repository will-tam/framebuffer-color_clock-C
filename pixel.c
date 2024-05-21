#include <linux/fb.h>

#include "pixel.h"


void putpixel(struct framebuffer *fbp, 
              int x, int y,
              unsigned int r, unsigned int g, unsigned int b, unsigned int alpha)
{
  if (((x >= 0) && 
       (y >= 0)) &&   
     (((unsigned int)x < fbp->vinfo.xres) && 
      ((unsigned int)y < fbp->vinfo.yres)))      /* Everybody inside the display. */
  {
    fbp->pxloffset = (x + fbp->vinfo.xoffset) * (fbp->vinfo.bits_per_pixel >> 3) + 
                   ((y + fbp->vinfo.yoffset) * fbp->finfo.line_length);

    *(fbp->dbp + fbp->pxloffset) = b;
    *(fbp->dbp + fbp->pxloffset + 1) = g;
    *(fbp->dbp + fbp->pxloffset + 2) = r;
    *(fbp->dbp + fbp->pxloffset + 3) = alpha;
  }
}