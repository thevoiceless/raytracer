#include "Image.h"

Image::Image(int m, int n) : xsize(m), ysize(n)
{
	rgb = new RGB[m * n];
}

RGB &Image::pixel(int i, int j)
{
	return rgb[i + xsize * j];
}