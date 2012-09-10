#include "Sphere.h"

// We want a procedure that:
//    Takes ray (o, d) and sphere (c, r ) as the input
//    Returns the intersection point closest to the ray’s origin if an intersection point exists or reports there is no intersection

// An intersection point is a point p that is both on the ray and on the sphere
//    (i) p = o + t d
//    (ii) |p − c|^2 = r^2

// At^2 + Bt + C = 0
// A = |d|^2
// B = 2co · d
// C = |co|^2 − r^2

// ∆ = B^2 − 4AC ; we have the following three cases:
//    (1) if ∆ < 0, no solution exists
//    (2) if ∆ = 0, there is only one solution
//    (3) if ∆ > 0, there are two solutions.
// Case (2): the solution is given by t = −B/(2A)
// Case (3): the two solutions are given by t± = (−B ± √∆)/(2A).

// If all solutions t are negative, we have no intersection points (report ‘no intersection’); this includes case (1)
// If there is a positive solution t, let t∗ be the smallest positive solution (sometimes – in case (3) – there may
// be two t’s and both can be positive; in this case discard the larger one)

// The intersection point is given by p∗ = o + t∗ d

double Sphere::intersection(Ray& ray)
{
	// A = |d|^2
	double A = pow(ray.direction.magnitude(), 2);
	//cout << "A: " << A << endl;
	// B = 2co · d
	double B = 2.0 * ((center.towards(ray.origin)).dotWith(ray.direction));
	//cout << "Center of sphere towards ray origin: " << (center.towards(ray.origin)).toString() << endl;
	//cout << "Ray direction: " << ray.direction.toString() << endl;
	//cout << "co dotted with ray direction: " << ((center.towards(ray.origin)).dotWith(ray.direction)) << endl;
	//cout << "B: " << B << endl;
	// C = |co|^2 − r^2
	double C = pow((center.towards(ray.origin)).magnitude(), 2) - pow(radius, 2);
	//cout << "C: " << C << endl;
	// ∆ = B^2 − 4AC
	double delta = pow(B, 2) - (4 * A * C);
	//cout << "Delta: " << delta << endl;
	
	// If ∆ < 0, no solution exists
	if(delta < 0)
	{
		return -1.0;
	}
	// If ∆ = 0, there is only one solution, t = −B/(2A)
	else if(delta == 0)
	{
		double t = -(B / (2 * A));
		if(t < 0)
		{
			return -1.0;
		}
		else
		{
			return t;
		}
	}
	// If ∆ > 0, there are two solutions, t± = (−B ± √∆)/(2A)
	else
	{
		double t1 = ((-B + sqrt(delta)) / (2 * A));
		double t2 = ((-B - sqrt(delta)) / (2 * A));
		//cout << "Delta is positive" << endl;
		//cout << "t1: " << t1 << endl;
		//cout << "t2: " << t2 << endl;
		// If all solutions t are negative, we have no intersection points
		if(t1 >= 0 && t2 >= 0)
		{
			return (t1 <= t2) ? t1 : t2;
		}
		else if(t1 >= 0)
		{
			return t1;
		}
		else if(t2 >= 0)
		{
			return t2;
		}
		else
		{
			return -1.0;
		}
	}
}

string Sphere::toString()
{
	stringstream ss;
	ss << "Center: " << center.toString() << endl;
	ss << "Radius: " << radius << endl;
	ss << "Material: " << material.toString() << endl;
	return ss.str();
}