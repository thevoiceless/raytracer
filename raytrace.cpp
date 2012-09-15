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

int main(int argc, char *argv[])
{
	// Create vector of pointers to Primitives
	vector<Primitive*> primitives;
	// Input file
	string filename = "input.txt";
	// Set to "true" to name the output PPM based on the name of the input file
	// Set to "fase" if a name is provided as a command-line argument
	bool useInputFileName;
	string outFileName = "output.ppm";

	// User did provide command-line arguments
	if(argc != 2)
	{
		// Load info from "input.txt"
		read_input_file((char*)filename.c_str(), primitives);
		useInputFileName = false;
	}
	// User passed command-line arguments
	else
	{
		// If a file name is provided, use the same name for the output file
		useInputFileName = true;
		// Load info from the named input file
		filename = argv[1];
		read_input_file(argv[1], primitives);
	}

	cout << "Running..." << endl;
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

	// Save the image to "output.ppm"
	if(!useInputFileName)
	{
		save_to_ppm_file(img, outFileName);
	}
	// Save with the same name as the input file
	else
	{
		outFileName = filename.substr(0, filename.length() - 4);
		outFileName.append(".ppm");
		save_to_ppm_file(img, outFileName);
	}

	return 0;
}