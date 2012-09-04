#include <string>
#include <fstream>
#include <cassert>
#include <cmath>
#include <vector>
#include "Image.h"
#pragma once

using namespace std;

vector<int> read_input_file();
void save_to_ppm_file(Image& theImage, string filename);
unsigned char clampnround(double x);