#include <string>
#include <fstream>
#include <cassert>
#include <cmath>
#include <vector>
#include <iostream>
#include "Image.h"
#include "Primitive.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Vector.h"
#include "globals.h"
#pragma once

using namespace std;

vector<int> read_input_file(string filename, vector<Primitive*> primitives);
void save_to_ppm_file(Image& theImage, string filename);
unsigned char clampnround(double x);