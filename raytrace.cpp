/*
Riley Moses
Project 1: Ray Tracing
CSCI 441
*/

#define MAINFILE

#include <iostream>
#include "RGB.h"
#include "Image.h"
#include "IOstuff.h"
#include "Material.h"

using namespace std;

int main()
{
	int x, y;

	vector<Primitive*> primitives;

	vector<int> resolution = read_input_file(primitives);
	int resolution_x = resolution.front();
	int resolution_y = resolution.back();

	Image img(resolution_x, resolution_y);
	for(x = 0; x < resolution_x; x++)
		for(y = 0; y < resolution_y; y++)
		{
			RGB &pix = img.pixel(x, y);

			/* 
				 call your raytracer here
				 then assign the rgb values
				 it returns to the pixel 
			*/

			// this is just to produce a fun image...
			pix.r = 0.5 + 0.5 * sin(sin(x / 30.0) + y * (y / 700.0));
			pix.g = 0.5 + 0.5 * sin(y / 71.0);
			pix.b = 0.5 + 0.5 * sin(x * x * (x / 120000.0) + y * (y / 1700.0));
		}

	/* save the image */
	save_to_ppm_file(img, "output.ppm");

	return 0;
}
