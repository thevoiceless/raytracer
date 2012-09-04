#include "RGB.h"
#pragma once

using namespace std;

class Image
{
 public:
 	// Resolution
 	int xsize, ysize;
 	// Pixel intensities
 	RGB* rgb;
 	// Allocates image of specified size
	Image(int m, int n);
	// Access to a specific pixel
	RGB &pixel(int i, int j);
};