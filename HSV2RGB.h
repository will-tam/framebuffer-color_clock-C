#ifndef _HSV2RGV_H
#define _HSV2RGV_H

#define PI 			      	M_PI
#define TWO_PI	      	(PI * 2)
#define HALF_PI	     		(PI / 2)


/*
  Convert HSV format color into RGB format color.
  Parameters : h = hue.
               s = saturation.
               v = value.
               *r, *g, *b = pointer to red, green and blue resulting color.
  Return : void.
*/
void HSV2RGB(float h, float s, float v, 
             unsigned int *r, unsigned int *g, unsigned int *b);

#endif