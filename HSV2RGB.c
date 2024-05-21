#include <stdlib.h>
#include <math.h>

#include "HSV2RGB.h"


void HSV2RGB(float h, float s, float v, 
             unsigned int* r, unsigned int* g, unsigned int* b)
/*
	https://www.rapidtables.com/convert/color/hsv-to-rgb.html (source)
	https://en.wikipedia.org/w/index.php?title=HSL_and_HSV
*/
{
	float Chroma;
	float X;
	float hprime;
	float match_lightness;
	float fr, fg, fb;

	if (h < 0) h = 0;
	if (s < 0) s = 0;
	if (v < 0) v = 0;

	if (h > 360) h = 359;
	if (s > 100) s = 100;
	if (v > 100) v = 100;

	s = s / 100.0;	
	v = v / 100.0;

	Chroma = v * s;
	hprime = h / 60.0;

	X = Chroma * (1.0 - fabs(fmod(hprime,2.0) - 1.0));

	fr = 0; 
  fg = 0;
  fb = 0;

	switch ((int)floor(hprime))
	{
		case 0:
			fr = Chroma;
			fg = X;
			break;
		case 1:
			fr = X;
			fg = Chroma;
			break;
		case 2:
			fg = Chroma;
			fb = X;
			break;
		case 3:
			fg = X;
			fb = Chroma;
			break;
		case 4:
			fr = X;
			fb = Chroma;
			break;
		default:
			fr = Chroma;
			fb = X;
			break;
	}

	match_lightness = v - Chroma;
	*r = abs((int)round((fr + match_lightness) * 255.0));
	*g = abs((int)round((fg + match_lightness) * 255.0));
	*b = abs((int)round((fb + match_lightness) * 255.0));
}