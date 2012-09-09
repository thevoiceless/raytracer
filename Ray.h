#include "Vector.h"
#pragma once

class Ray
{
public:
	Vector origin;
	Vector direction;

	Ray(Vector o, Vector d) : origin(o), direction(d) {}
};