#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include "clock.h"
#include "line.h"
#include "circles.h"
#include "pixel.h"
#include "HSV2RGB.h"


#define MAP(val, val_min, val_max, boundary_min, boundary_max)	((val - val_min) * (boundary_max - boundary_min) / (val_max - val_min) + boundary_min)
#define NORM(val, val_min, val_max)				              				(MAP(val, val_min, val_max, 0, 1))


unsigned int screenwidth;       /* Max screen in X. */
unsigned int screenheight;      /* Max screen in Y. */
unsigned int screenmidx;        /* Middle of the screen in X. */
unsigned int screenmidy;        /* Middle of the screen in Y. */

unsigned int clockd;            /* Clock diameter. */
double clockr;                  /* Clock radius. */
double clockrin;                /* Inside clock radius. */
double clockrout;               /* Outside clock radius. */
double clockhoursr;             /* Radius of hours' hand. */
double clockminr;               /* Radius of minutes' hand. */
double clocksecr;               /* Radius of seconds' hand. */

float offsetFrameColor;         /* Chanching clock color offset. */

void clockinit(struct framebuffer *fbp)
{
screenwidth = fbp->vinfo.xres;
screenheight = fbp->vinfo.yres;
screenmidx = screenwidth >> 1;
screenmidy = screenheight >> 1;

clockd = screenmidx;
clockr = clockd / 2;
clockrin = clockr - 15;
clockrout = clockr + 15;
clockhoursr = clockr * 0.5;
clockminr = clockr * 0.75;
clocksecr = clockr * 0.9;

offsetFrameColor = 0;
}

void big_point(struct framebuffer *fbp, int x, int y, int radius)
{
	int r;

	for (r = 0; r < radius; r += 1)
	{
		circle(fbp, screenmidx + x, screenmidy + y, r, 255, 255, 255 ,0);
	}
}

void clockupdate(struct framebuffer *fbp)
{
  time_t timestamp;
  struct tm* now;

	int r;
	float a;

  double hA;             /* Hours angle. */
  double mA;             /* Minutes angle. */
  double sA;             /* Seconds angle. */

  double x;              /* x according cos(). */
  double y;              /* x according sin(). */

	
	timestamp = time(NULL);
	now = localtime(&timestamp);

	sA = MAP(now->tm_sec, 0.0, 60.0, 0.0, TWO_PI) - HALF_PI;
	mA = MAP(now->tm_min + NORM(now->tm_sec, 0.0, 60.0), 0.0, 60.0, 0.0, TWO_PI) - HALF_PI;
	hA = MAP(now->tm_hour % 12 + NORM(now->tm_min, 0.0, 60.0), 0.0, 24.0, 0.0, TWO_PI * 2) - HALF_PI;

	for (r = clockrin; r < clockrout; r += 1)
	{
		circlerotationcolor(fbp, &offsetFrameColor, screenmidx, screenmidy, r);
	}

  for (a = 0; a < 2 * PI; a += PI/6)
  {
    big_point(fbp, clockr * cos(a), clockr * sin(a), 4);
  }

  x = screenmidx + (int)(clocksecr * cos(sA));
  y = screenmidy + (int)(clocksecr * sin(sA));
  line(fbp, screenmidx, screenmidy, x, y, 0, 255, 21, 0);

  x = screenmidx + (int)(clockminr * cos(mA));
  y = screenmidy + (int)(clockminr * sin(mA));
  line(fbp, screenmidx, screenmidy, x, y, 255, 0, 0, 0);

  x = screenmidx + (int)(clockhoursr * cos(hA));
  y = screenmidy + (int)(clockhoursr * sin(hA));
  line(fbp, screenmidx, screenmidy, x, y, 64, 0, 255, 0);

  offsetFrameColor = fmod(offsetFrameColor + (360/60), 360);
}

