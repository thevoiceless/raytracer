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
	// B = 2co · d
	double B = 2.0 * ((center.towards(ray.origin)).dotWith(ray.direction));
	// C = |co|^2 − r^2
	double C = pow((center.towards(ray.origin)).magnitude(), 2) - pow(radius, 2);
	// ∆ = B^2 − 4AC
	double delta = pow(B, 2) - (4 * A * C);
	
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

// Sphere case
// return p - center
Vector Sphere::normal(Vector& intersection_point)
{
	return intersection_point.minus(center);
}

// Vector illumination ( Vector p )
// n := normal(p);
// if (n · (b - p)) < 0 then p in shadow of its primitive
//   return the value of the Ambient term
// else
//   N:= normalize(n);
//   L:= lightVector(p);
//   V:= viewVector(p);
//   return value of the illumination formula:
//     I_total = I * (k_d * (N · L) + k_s * (H · N)^n) + k_a * I_a
Vector Sphere::illumination(Vector& intersection_point)
{
	Vector n = this->normal(intersection_point);
	// Intersection point is in the shadow of its primitive
	if(n.dotWith(lightSource.minus(intersection_point)) < 0)
	{
		return Vector(this->material.k_ambient_R,
			this->material.k_ambient_G,
			this->material.k_ambient_B);
	}
	else
	{
		Vector N = n.normalize();
		Vector L = lightVector(intersection_point);
		Vector V = viewVector(intersection_point);
		Vector H = (V.addTo(L)).scaleBy(1 / (V.addTo(L)).magnitude());

		double Itotal_red, Itotal_green, Itotal_blue;
		double NdotL = N.dotWith(L);
		double HdotN = pow(H.dotWith(N), this->material.n_spec);
		Itotal_red = (light_intensity * ((this->material.k_diff_R * NdotL) + (this->material.k_spec * HdotN))) + (this->material.k_ambient_R * ambient_light_intensity);
		Itotal_green = (light_intensity * ((this->material.k_diff_G * NdotL) + (this->material.k_spec * HdotN))) + (this->material.k_ambient_G * ambient_light_intensity);
		Itotal_blue = (light_intensity * ((this->material.k_diff_B * NdotL) + (this->material.k_spec * HdotN))) + (this->material.k_ambient_B * ambient_light_intensity);

		return Vector(Itotal_red, Itotal_green, Itotal_blue);
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