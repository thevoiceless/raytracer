#include "IOstuff.h"

void save_to_ppm_file(Image& theImage, string filename)
{
	ofstream outFile(filename.c_str(), ios::binary);
	assert(outFile);
	outFile << "P6" << endl;
	outFile << theImage.xsize << " " << theImage.ysize << endl << 255 << endl;
	for(int i = 0; i < theImage.xsize * theImage.ysize; i++)
	{
		unsigned char r = clampnround(256 * theImage.rgb[i].r);
		unsigned char g = clampnround(256 * theImage.rgb[i].g);
		unsigned char b = clampnround(256 * theImage.rgb[i].b);
		outFile.write((char*)&r, sizeof(char));
		outFile.write((char*)&g, sizeof(char));
		outFile.write((char*)&b, sizeof(char));
	}
	outFile.close();
}

unsigned char clampnround(double x)
{
	if(x > 255)
		x = 255;
	if(x < 0) 
		x = 0;
	return (unsigned char)floor(x + .5);
}

void read_input_file(string& filename, vector<Primitive*>& primitives)
{
	ifstream inFile(filename.c_str());
	assert(inFile);

	int numSpheres = 0;
	int numTriangles = 0;

	double viewpoint[3];
	double screen_lower_left_corner[3];
	double screen_horizontal_vector[3];
	double screen_vertical_vector[3];
	double light_source[3];

	inFile >> resolution_x >> resolution_y;
	inFile >> viewpoint[0] >> viewpoint[1] >> viewpoint[2];
	inFile >> screen_lower_left_corner[0] >> screen_lower_left_corner[1] >> screen_lower_left_corner[2];
	inFile >> screen_horizontal_vector[0] >> screen_horizontal_vector[1] >> screen_horizontal_vector[2];
	inFile >> screen_vertical_vector[0] >> screen_vertical_vector[1] >> screen_vertical_vector[2];
	inFile >> light_source[0] >> light_source[1] >> light_source[2];
	inFile >> light_intensity;
	inFile >> ambient_light_intensity;
	inFile >> number_of_primitives;

	// Initialize globals
	viewpt = Vector(viewpoint[0], viewpoint[1], viewpoint[2]);
	cout << "Viewpoint: " << viewpt.toString() << endl;
	screenLowerLeftCorner = Vector(screen_lower_left_corner[0], screen_lower_left_corner[1], screen_lower_left_corner[2]);
	cout << "Screen lower left corner: " << screenLowerLeftCorner.toString() << endl;
	screenHorizVector = Vector(screen_horizontal_vector[0], screen_horizontal_vector[1], screen_horizontal_vector[2]);
	cout << "Screen horizontal vector: " << screenHorizVector.toString() << endl;
	screenVertVector = Vector(screen_vertical_vector[0], screen_vertical_vector[1], screen_vertical_vector[2]);
	cout << "Screen vertical vector: " << screenVertVector.toString() << endl;
	lightSource = Vector(light_source[0], light_source[1], light_source[2]);
	cout << "Light source: " << lightSource.toString() << endl;

	screenLowerLeftCorner = screenLowerLeftCorner.addTo(screenVertVector);
	screenVertVector = screenVertVector.scaleBy(-1.0);

	for(int i = 0; i < number_of_primitives; i++)
	{
		char primitive_type;
		inFile >> primitive_type;
		switch(primitive_type)
		{
		case 's':
		case 'S':
			{
				double center[3];
				double radius;
				double k_diffuse[3];
				double k_ambient[3];
				double k_specular;
				double n_specular;

				inFile >> center[0] >> center[1] >> center[2];
				inFile >> radius;
				inFile >> k_diffuse[0] >> k_diffuse[1] >> k_diffuse[2];
				inFile >> k_ambient[0] >> k_ambient[1] >> k_ambient[2];
				inFile >> k_specular >> n_specular;

				primitives.push_back(new Sphere(Vector(center[0], center[1], center[2]), radius, Material(k_diffuse[0], k_diffuse[1], k_diffuse[2], k_ambient[0], k_ambient[1], k_ambient[2], k_specular, n_specular)));
				cout << "\nAdded sphere" << endl;
				cout << dynamic_cast<Sphere*>(primitives.back())->toString() << endl;
				numSpheres++;
			}
			break;
		case 'T':
		case 't':
			{
				double a1[3];
				double a2[3];
				double a3[3];
				double k_diffuse[3];
				double k_ambient[3];
				double k_specular;
				double n_specular;
				
				inFile >> a1[0] >> a1[1] >> a1[2];
				inFile >> a2[0] >> a2[1] >> a2[2];
				inFile >> a3[0] >> a3[1] >> a3[2];
				inFile >> k_diffuse[0] >> k_diffuse[1] >> k_diffuse[2];
				inFile >> k_ambient[0] >> k_ambient[1] >> k_ambient[2];
				inFile >> k_specular >> n_specular;

				primitives.push_back(new Triangle(Vector(a1[0], a1[1], a1[2]), Vector(a2[0], a2[1], a2[2]), Vector(a3[0], a3[1], a3[2]), Material(k_diffuse[0], k_diffuse[1], k_diffuse[2], k_ambient[0], k_ambient[1], k_ambient[2], k_specular, n_specular)));
				cout << "\nAdded triangle" << endl;
				cout << dynamic_cast<Triangle*>(primitives.back())->toString() << endl;
				numTriangles++;
			}
			break;
		default:
			assert(0);
		}
	}
	inFile.close();

	cout << "Added " << numSpheres << " sphere(s)" << endl;
	cout << "Added " << numTriangles << " triangle(s)" << endl;
}