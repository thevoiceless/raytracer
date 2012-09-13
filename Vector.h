#include <cmath>
#include <sstream>
#include <string>
#pragma once

using namespace std;

class Vector
{
public:
	double x, y, z;

	Vector();
	Vector(double xpos, double ypos, double zpos) : x(xpos), y(ypos), z(zpos) {}

	Vector addTo(Vector& v2);
	Vector& towards(Vector& v2);
	Vector minus(Vector& v2);
	Vector scaleBy(double t);
	double dotWith(Vector& v2);
	Vector crossWith(Vector& v2);
	double magnitude();
	string toString();
};