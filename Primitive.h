#include "Ray.h"
#include "Vector.h"
#pragma once

class Primitive
{
public:
	virtual double intersection(Ray& r) = 0;
	virtual Vector normal(Vector& intersection_point) = 0;
	virtual Vector illumination(Vector& intersection_point) = 0;
};