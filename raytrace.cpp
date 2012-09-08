/*
Riley Moses
Project 1: Ray Tracing
CSCI 441
*/

#define MAINFILE

#include "RGB.h"
#include "Image.h"
#include "IOstuff.h"
#include "Material.h"

using namespace std;

int main()
{
	string filename;
	cout << "Enter name of input file: ";
	cin >> filename;
	// Create vector of pointers to Primitives
	vector<Primitive*> primitives;
	// Load info from the input file
	vector<int> resolution = read_input_file(filename, primitives);

	Vector viewpt(viewpoint[0], viewpoint[1], viewpoint[2]);
	Vector screenLowerLeftCorner(screen_lower_left_corner[0], screen_lower_left_corner[1], screen_lower_left_corner[2]);
	Vector screenHorizVector(screen_horizontal_vector[0], screen_horizontal_vector[1], screen_horizontal_vector[2]);
	Vector screenVertVector(screen_vertical_vector[0], screen_vertical_vector[1], screen_vertical_vector[2]);
	Vector lightSource(light_source[0], light_source[1], light_source[2]);

	int resolution_x = resolution.front();
	int resolution_y = resolution.back();

	Image img(resolution_x, resolution_y);
	for(int x = 0; x < resolution_x; x++)
		for(int y = 0; y < resolution_y; y++)
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
