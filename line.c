#include <stdlib.h>
#include <linux/fb.h>

#include "fbtools.h"
#include "pixel.h"
#include "line.h"


void line(struct framebuffer *fbp,
          int x0, int y0, int x1, int y1, 
          unsigned int r, unsigned int g, unsigned int b, unsigned int alpha)
{  
  int dx;         /* diff beetween x coordinates. */
  int sx;         /* According the starting x, add or sub 1 to the next x. */
  int dy;         /* diff beetween y coordinates. */
  int sy;         /* According the starting y, add or sub 1 to the next y. */

  int err;        /* Error beetween real line and the pixel to draw it. */
  int e2;         /* err * 2. */


  dx = abs(x1 - x0);
  dy = -abs(y1 - y0);
  sx = x0 < x1 ? 1 : -1;
  sy = y0 < y1 ? 1 : -1;

  err = dx + dy;

  for (;;){

    putpixel(fbp, x0, y0, r, g, b, alpha);

    if (x0 == x1 && y0 == y1) break;
    e2 = err + err;     /* Better add than mul, for only by 2 - also could use <<1. */
    if (e2 >= dy)       /* err * 2 + delta_x > 0. */
    { 
      err += dy;
      x0 += sx; 
    }
    if (e2 <= dx)       /* err * 2 + delta_y < 0. */
    {
      err += dx;
      y0 += sy;
    }
  }
}
