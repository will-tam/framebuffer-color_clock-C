#include <linux/fb.h>
#include <math.h>

#include "fbtools.h"
#include "pixel.h"
#include "circles.h"
#include "HSV2RGB.h"


void circle(struct framebuffer *fbp,
            int xc, int yc, int radius,
            unsigned int r, unsigned int g, unsigned int b, unsigned int alpha)
{
  int x, y;       /* (x,y) of the circle it-self. */
  int px, py;     /* (px,py) of the pixel to put. */
  int err;        /* Error beetween real circle and the pixel to draw it. */


  x = 0;
	y = radius;
	err = radius - 1;
	
	while (y >= x)
	{
		/* Drawing all 8 pixels present in circle by symmetric position. */
    px = xc + x;
    py = yc + y;
    putpixel(fbp, px, py, r, g, b, alpha);
    py = yc - y;
    putpixel(fbp, px, py, r, g, b, alpha);

    px = xc + y;
    py = yc - x;
    putpixel(fbp, px, py, r, g, b, alpha);
    py = yc + x;
    putpixel(fbp, px, py, r, g, b, alpha);

    px = xc - x;
    py = yc + y;
    putpixel(fbp, px, py, r, g, b, alpha);
    py = yc - y;
    putpixel(fbp, px, py, r, g, b, alpha);

    px = xc - y;
    py = yc + x;
    putpixel(fbp, px, py, r, g, b, alpha);
    py = yc - x;
    putpixel(fbp, px, py, r, g, b, alpha);

		/* Checking next (x, y) position to draw circle. */
		if (err >= (x << 1))
		{
			err = err - (x << 1) - 1;
			x++;
		}
		else if (err < ((radius - y) << 1))
		{
			err = err + (y << 1) - 1;
			y--;
		}
			else
			{
				err = err + ((y - x - 1) << 1);
				y--;
				x++;
			}
	}
}

void circlerotationcolor(struct framebuffer *fbp,
                         float *offsetFrameColor,
                         int xc, int yc, int radius)
{
  int x, y;       /* (x,y) of the circle it-self. */
  int px, py;     /* (px,py) of the pixel to put. */
  int err;        /* Error beetween real circle and the pixel to draw it. */

	double a;       /* Angle according color */

  unsigned int red, green, blue, alpha;   /* RGB-Alpha color. */

  x = 0;
	y = radius;
	err = radius - 1;
	
  red = 125;
  green = 41;
  blue = 203;
  alpha = 0;

	while (y >= x)
	{
		/* Drawing all 8 pixels present in circle by symmetric position. */
		a = (atan2(y, x) * 180 / PI);
		HSV2RGB(fmod(360 - (a - *offsetFrameColor), 360), 100, 100, &red, &green, &blue);
    px = xc + x;
    py = yc + y;
    putpixel(fbp, px, py, red, green, blue, alpha);

		a = (atan2(y, -x) * 180 / PI);
		HSV2RGB(fmod(360 - (a - *offsetFrameColor), 360), 100, 100, &red, &green, &blue);
    px = xc - x;
    py = yc + y;
    putpixel(fbp, px, py, red, green, blue, alpha);

		a = (atan2(-y, x) * 180 / PI) + 360;
		HSV2RGB(fmod(360 - (a - *offsetFrameColor), 360), 100, 100, &red, &green, &blue);
    px = xc + x;
    py = yc - y;
    putpixel(fbp, px, py, red, green, blue, alpha);

		a = (atan2(-y, -x) * 180 / PI) + 360;
		HSV2RGB(fmod(360 - (a - *offsetFrameColor), 360), 100, 100, &red, &green, &blue);
    px = xc - x;
    py = yc - y;
    putpixel(fbp, px, py, red, green, blue, alpha);

		a = (atan2(x, y) * 180 / PI);
		HSV2RGB(fmod(360 - (a - *offsetFrameColor), 360), 100, 100, &red, &green, &blue);
    px = xc + y;
    py = yc + x;
    putpixel(fbp, px, py, red, green, blue, alpha);

		a = (atan2(x, -y) * 180 / PI);
		HSV2RGB(fmod(360 - (a - *offsetFrameColor), 360), 100, 100, &red, &green, &blue);
    px = xc - y;
    py = yc + x;
    putpixel(fbp, px, py, red, green, blue, alpha);

		a = (atan2(-x, y) * 180 / PI) + 360;
		HSV2RGB(fmod(360 - (a - *offsetFrameColor), 360), 100, 100, &red, &green, &blue);
    px = xc + y;
    py = yc - x;
    putpixel(fbp, px, py, red, green, blue, alpha);

		a = fmod((atan2(-x, -y) * 180 / PI) + 360, 360);   // Remove a color glitch at 180°. Value of atan == 540° instead 180°.
		HSV2RGB(fmod(360 - (a - *offsetFrameColor), 360), 100, 100, &red, &green, &blue);
    px = xc - y;
    py = yc - x;
    putpixel(fbp, px, py, red, green, blue, alpha);

		/* Checking next (x, y) position to draw circle. */
		if (err >= (x << 1))
		{
			err = err - (x << 1) - 1;
			x++;
		}
		else if (err < ((radius - y) << 1))
		{
			err = err + (y << 1) - 1;
			y--;
		}
			else
			{
				err = err + ((y - x - 1) << 1);
				y--;
				x++;
			}
	}
}
