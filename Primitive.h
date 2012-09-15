#include "Ray.h"
#include "Vector.h"
#pragma once

class Primitive
{
public:
	virtual double intersection(Ray& r) = 0;
	virtual Vector normal() = 0;
};