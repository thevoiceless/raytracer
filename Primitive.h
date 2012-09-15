#include "Ray.h"
#include "Vector.h"
#pragma once

class Primitive
{
public:
	virtual double intersection(Ray& r) = 0;
	virtual Vector illumination(Vector& intersection_point, Vector& viewpt, Vector& lightSource, double light_intensity, double ambient_light_intensity) = 0;
};