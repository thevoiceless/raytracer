#include "Vector.h"

using namespace std;

Vector::Vector()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector Vector::addTo(Vector v2)
{
	return Vector((x + v2.x),
		(y + v2.y),
		(z + v2.z));
}

Vector Vector::towards(Vector v2)
{
	return Vector((v2.x - x),
		(v2.y - y),
		(v2.z - z));
}

Vector Vector::minus(Vector v2)
{
	return Vector((x - v2.x),
		(y - v2.y),
		(z - v2.z));
}

Vector Vector::scaleBy(double t)
{
	return Vector((t * x),
		(t * y),
		(t * z));
}

double Vector::dotWith(Vector v2)
{
	return ((x * v2.x)
		+ (y * v2.y)
		+ (z * v2.z));
}

Vector Vector::crossWith(Vector v2)
{
	double xhat = ((y * v2.z) - (z * v2.y));
	double yhat = ((z * v2.x) - (x * v2.z));
	double zhat = ((x * v2.y) - (y * v2.x));
	return Vector(xhat, yhat, zhat);
}

double Vector::magnitude()
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Vector Vector::normalize()
{
	double mag = this->magnitude();
	return Vector((x / mag), (y / mag), (z / mag));
}

string Vector::toString()
{
	stringstream ss;
	ss << "(" << x << ", " << y << ", " << z << ")";
	return ss.str();
}