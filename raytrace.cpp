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
#include "functions.h"

using namespace std;

int main()
{
	string filename;
	cout << "Enter name of input file: ";
	cin >> filename;
	// Create vector of pointers to Primitives
	vector<Primitive*> primitives;
	// Load info from the input file
	read_input_file(filename, primitives);

	Image img(resolution_x, resolution_y);
	for(int x = 0; x < resolution_x; x++)
		for(int y = 0; y < resolution_y; y++)
		{
			double t == -1.0;
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
			else
			{
				cout << "Intersection" << endl;
				Sphere *sphere = dynamic_cast<Sphere*>((primitives.at(primitive_id)));
				Triangle *triangle = dynamic_cast<Triangle*>((primitives.at(primitive_id)));
				if(sphere)
				{
					cout << "Intersection with spehere" << endl;
					pix.r = sphere->material.k_diff_R;
					pix.g = sphere->material.k_diff_G;
					pix.b = sphere->material.k_diff_B;
				}
				else if(triangle)
				{
					cout << "Intersection with tirangle" << endl;
					pix.r = triangle->material.k_diff_R;
					pix.g = triangle->material.k_diff_G;
					pix.b = triangle->material.k_diff_B;
				}
			}

			// this is just to produce a fun image...
			//pix.r = 0.5 + 0.5 * sin(sin(x / 30.0) + y * (y / 700.0));
			//pix.g = 0.5 + 0.5 * sin(y / 71.0);
			//pix.b = 0.5 + 0.5 * sin(x * x * (x / 120000.0) + y * (y / 1700.0));
		}

	// Save the image
	save_to_ppm_file(img, "output.ppm");

	return 0;
}
