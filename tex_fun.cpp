/* Texture functions for cs580 GzLib	*/
#include    "stdafx.h" 
#include	"stdio.h"
#include	"Gz.h"

GzColor	*image=NULL;
int xs, ys;
int reset = 1;



void BilinearInterpolation(float* A, float* B, float* C, float* D, float s, float t, float* returnColor) {

	for (int i = 0; i < 3; i++) {

		returnColor[i] = s * t * (C[i]) + (1 - s) * t * (D[i]) + s * (1 - t) * (B[i]) + (1 - s)*(1 - t)*(A[i]);
	}
}

/* Image texture function */
int tex_fun(float u, float v, GzColor color)
{
  unsigned char		pixel[3];
  unsigned char     dummy;
  char  		foo[8];
  int   		i, j;
  FILE			*fd;

  if (reset) {          /* open and load texture file */
    fd = fopen ("texture", "rb");
    if (fd == NULL) {
      fprintf (stderr, "texture file not found\n");
      exit(-1);
    }
    fscanf (fd, "%s %d %d %c", foo, &xs, &ys, &dummy);
    image = (GzColor*)malloc(sizeof(GzColor)*(xs+1)*(ys+1));
    if (image == NULL) {
      fprintf (stderr, "malloc for texture image failed\n");
      exit(-1);
    }

    for (i = 0; i < xs*ys; i++) {	/* create array of GzColor values */
      fread(pixel, sizeof(pixel), 1, fd);
      image[i][RED] = (float)((int)pixel[RED]) * (1.0 / 255.0);
      image[i][GREEN] = (float)((int)pixel[GREEN]) * (1.0 / 255.0);
      image[i][BLUE] = (float)((int)pixel[BLUE]) * (1.0 / 255.0);
      }

    reset = 0;          /* init is done */
	fclose(fd);
  }

/* bounds-test u,v to make sure nothing will overflow image array bounds */
/* determine texture cell corner values and perform bilinear interpolation */
/* set color to interpolated GzColor value and return */

	//bound test u,v
  if (u < 0 || u > 1) { return GZ_FAILURE; }
  if (v < 0 || v > 1) { return GZ_FAILURE; }

   //scale u, v
  u *= (xs - 1);
  v *= (ys - 1);

  //image lookup, bilinear interpolation. Set color.
  //GzColor* A, B, C, D;
  float s, t;

  float* A = image[(int)(floor(u) + floor(v) * xs)];
  float* B = image[(int)(ceil(u) + floor(v) * xs)];
  float* C = image[(int)(ceil(u) + ceil(v) * xs)];
  float* D = image[(int)(floor(u) + ceil(v) * xs)];

  s = u - floor(u);
  t = v - floor(v);

  BilinearInterpolation(A, B, C, D, s, t, color);

  
	return GZ_SUCCESS;
}

/* Procedural texture function */
int ptex_fun(float u, float v, GzColor color)
{
	int interval = 10;
	int uInterval = (int)ceil(u * interval);
	int vInterval = (int)ceil(v * interval);

	if ((uInterval % 2) == (vInterval % 2)) {
		color[RED] = 0;
		color[GREEN] = 2500;
		color[BLUE] = 2500;
	}
	else {
		color[RED] = .2;
		color[GREEN] = .2;
		color[BLUE] = .2;
	}

	return GZ_SUCCESS;
}

/* Free texture memory */
int GzFreeTexture()
{
	if(image!=NULL)
		free(image);
	return GZ_SUCCESS;
}

