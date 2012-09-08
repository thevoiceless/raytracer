#include <cmath>
#pragma once

class Vector
{
public:
	double x, y, z;

	Vector(void);
	Vector(double xpos, double ypos, double zpos) : x(xpos), y(ypos), z(zpos) {}

	Vector addTo(Vector v2);
	Vector subtract(Vector v2);
	double dotWith(Vector v2);
	Vector crossWith(Vector v2);
	double magnitude();
};