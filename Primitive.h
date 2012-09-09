#include "Ray.h"
#pragma once

class Primitive
{
public:
	virtual double intersection(Ray& r) = 0;
};