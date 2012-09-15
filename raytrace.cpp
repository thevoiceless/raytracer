/*
Riley Moses
Project 1: Ray Tracing
CSCI 441
*/

#define MAINFILE

#include <cstdlib>
#include <cmath>
#include "RGB.h"
#include "Image.h"
#include "IOstuff.h"
#include "Material.h"
#include "functions.h"

using namespace std;

void tests();
void vectorTests();
void sphereTests();
bool eq(double first, double second);

int main(int argc, char *argv[])
{
	// Create vector of pointers to Primitives
	vector<Primitive*> primitives;
	// Input file
	string filename = "input.txt";

	// User did not enter a filename as a command-line argument
	if(argc != 2)
	{
		// Load info from "input.txt"
		read_input_file((char*)filename.c_str(), primitives);
	}
	// User passed a filename as a command-line argument
	else
	{
		// Load info from the named input file
		filename = argv[1];
		read_input_file(argv[1], primitives);
	}

	Image img(resolution_x, resolution_y);
	for(int x = 0; x < resolution_x; x++)
		for(int y = 0; y < resolution_y; y++)
		{
			double t = -1.0;
			int primitive_id;
			Ray r = eyeRay(x, y);

			pair<double, int> result = closestIntersection(r, primitives);
			t = result.first;
			primitive_id = result.second;

			RGB &pix = img.pixel(x, y);

			// No intersection
			if(t == -1.0)
			{
				pix.r = 0.0;
				pix.g = 0.0;
				pix.b = 0.0;
			}
			// Intersection
			else
			{
				// p = o + td
				Vector intersection_point = r.origin.addTo(r.direction.scaleBy(t));

				// Determine if the intersection was with a sphere or triangle
				Sphere* sphere = dynamic_cast<Sphere*>((primitives.at(primitive_id)));
				Triangle* triangle = dynamic_cast<Triangle*>((primitives.at(primitive_id)));
				if(sphere)
				{
					Vector colors = sphere->illumination(intersection_point, viewpt, lightSource, light_intensity, ambient_light_intensity);
					pix.r = colors.x;
					pix.g = colors.y;
					pix.b = colors.z;
				}
				else if(triangle)
				{
					Vector colors = triangle->illumination(intersection_point, viewpt, lightSource, light_intensity, ambient_light_intensity);
					pix.r = colors.x;
					pix.g = colors.y;
					pix.b = colors.z;
				}
			}

			// this is just to produce a fun image...
			//pix.r = 0.5 + 0.5 * sin(sin(x / 30.0) + y * (y / 700.0));
			//pix.g = 0.5 + 0.5 * sin(y / 71.0);
			//pix.b = 0.5 + 0.5 * sin(x * x * (x / 120000.0) + y * (y / 1700.0));
		}

	// Save the image
	save_to_ppm_file(img, "output.ppm");

	// Only used to make the output filename match the name of the input file
	// string outFileName = filename.substr(0, filename.length() - 4);
	// outFileName.append(".ppm");
	// save_to_ppm_file(img, outFileName);

	return 0;
}