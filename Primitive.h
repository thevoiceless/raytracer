#include "Ray.h"
#pragma once

class Primitive
{
	virtual double intersection(Ray& r) = 0;
};