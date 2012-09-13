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
	//tests();

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
				Sphere* sphere = dynamic_cast<Sphere*>((primitives.at(primitive_id)));
				Triangle* triangle = dynamic_cast<Triangle*>((primitives.at(primitive_id)));
				if(sphere)
				{
					pix.r = sphere->material.k_diff_R * light_intensity;
					pix.g = sphere->material.k_diff_G * light_intensity;
					pix.b = sphere->material.k_diff_B * light_intensity;
				}
				else if(triangle)
				{
					pix.r = triangle->material.k_diff_R * light_intensity;
					pix.g = triangle->material.k_diff_G * light_intensity;
					pix.b = triangle->material.k_diff_B * light_intensity;
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

void tests()
{
	vectorTests();
	sphereTests();

	exit(0);
}

void vectorTests()
{
	cout << "\n----- Vector tests -----" << endl;
	Vector v1(1.1, 2.2, 3.3);
	Vector v2(4.4, 5.5, 6.6);
	Vector v3;
	double n;

	cout << "\nDefault vector tests:" << endl;
	Vector v;
	cout << "X coord should be zero";
	assert(v.x == 0);
	cout << "\t\t\t\t\tPass" << endl;
	cout << "Y coord should be zero";
	assert(v.y == 0);
	cout << "\t\t\t\t\tPass" << endl;
	cout << "Z coord should be zero";
	assert(v.z == 0);
	cout << "\t\t\t\t\tPass" << endl;
	cout << endl;

	cout << "Vector addition tests:" << endl;
	v3 = v1.addTo(v2);
	cout << v1.toString() << " + " << v2.toString() << endl;
	cout << " = " << v3.toString();
	assert(eq(v3.x, 5.5));
	assert(eq(v3.y, 7.7));
	assert(eq(v3.z, 9.9));
	cout << "\t\t\t\t\tPass" << endl;
	cout << endl;

	cout << "Vector to-from tests:" << endl;
	v3 = v1.towards(v2);
	cout << "From " << v1.toString() << " to " << v2.toString() << endl;
	cout << " = " << v3.toString();
	assert(eq(v3.x, 3.3));
	assert(eq(v3.y, 3.3));
	assert(eq(v3.z, 3.3));
	cout << "\t\t\t\t\tPass" << endl;
	cout << endl;

	cout << "Vector subtraction tests:" << endl;
	v3 = v1.minus(v2);
	cout << v1.toString() << " minus " << v2.toString() << endl;
	cout << " = " << v3.toString();
	assert(eq(v3.x, -3.3));
	assert(eq(v3.y, -3.3));
	assert(eq(v3.z, -3.3));
	cout << "\t\t\t\t\tPass" << endl;
	cout << endl;

	cout << "Vector scalar multiplication tests:" << endl;
	v3 = v1.scaleBy(3.4);
	cout << v1.toString() << " scaled by 3.4" << endl;
	cout << " = " << v3.toString();
	
	cout << "\t\t\t\t\tPass" << endl;
	cout << endl;

	cout << "Vector dot product tests:" << endl;
	n = v1.dotWith(v2);
	cout << v1.toString() << " dotted with " << v2.toString() << endl;
	cout << " = " << n;
	assert(eq(n, 38.72));
	cout << "\t\t\t\t\t\tPass" << endl;
	cout << endl;

	cout << "Vector cross product tests:" << endl;
	v3 = v1.crossWith(v2);
	cout << v1.toString() << " crossed with " << v2.toString() << endl;
	cout << " = " << v3.toString();
	assert(eq(v3.x, -3.63));
	assert(eq(v3.y, 7.26));
	assert(eq(v3.z, -3.63));
	cout << "\t\t\t\t\tPass" << endl;
	cout << endl;

	cout << "Vector magnitude tests:" << endl;
	cout << v1.toString() << " magnitude should be 4.115823125:";
	assert(eq(v1.magnitude(), 4.11582));
	cout << "\tPass" << endl;
	cout << v2.toString() << " magnitude should be 9.652460826:";
	assert(eq(v2.magnitude(), 9.652460826));
	cout << "\tPass" << endl;
	cout << endl;
}

void sphereTests()
{
	cout << "\n----- Sphere tests -----" << endl;
	
	Sphere s(Vector(5, 0, 0), 1.0, Material(0.0, 0.0, 0.5, 0.0, 0.0, 0.2, 0.3, 20));
	cout << endl << s.toString() << endl;
	
	Ray r(Vector(0, 0, 0), Vector(100, 0, 0));
	double t = s.intersection(r);
	cout << "t value from (0, 0, 0) in direction (100, 0, 0): " << t << endl;

	cout << "R value of pixel: " << s.material.k_diff_R << endl;
	cout << "G value of pixel: " << s.material.k_diff_G << endl;
	cout << "B value of pixel: " << s.material.k_diff_B << endl;
}

// Returns true if two doubles might as well be equal to each other
// Had to do this because of rounding issues in the vector tests
bool eq(double first, double second)
{
	return (fabs(first - second) < 3.125e-05);
}