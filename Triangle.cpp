#include "Triangle.h"

// A point p is in the triangle if and only if p is a weighted
// average of a1, a2, and a3, i.e. there exist nonnegative numbers
// α, β and γ such that α + β + γ = 1 and p = αa1 + βa2 + γa3

// Find t and the weights such that o + t d = αa1 + βa2 + γa3

// We have 4 equations:
//    (1) ox + dx t = a1x α + a2x β + a3x γ
//    (2) oy + dy t = a1y α + a2y β + a3y γ
//    (3) oz + dz t = a1z α + a2z β + a3z γ
//    (4) α + β + γ = 1

// a1x a2x a3x -dxα   ox
// a1y a2y a3y −dyβ   oy
// a1z a2z a3z −dzγ = oz
//  1   1   1   0 t   1 

// Let’s assume it has a unique solution t∗, α∗, β∗, γ∗
// If t∗, α∗, β∗, and γ∗ are all nonnegative then there
// is an intersection point and it is given by o + t∗ d
// Otherwise, there is no intersection point
// If there is no solution or it is not unique, the ray is 
// parallel to the triangle’s plane; in practice, we can
// just report no intersection

// Two-step process:
// Step 1: Compute the intersection point p of the triangle’s plane and
//         the ray; if there is no intersection, report ’no intersection’
//         and stop.
// Step 2: Decide whether p is inside or outside the triangle; if it is
//         outside, report ‘no intersection’, otherwise, the intersection
//         point is p.

// Step 1: Intersect the ray and the triangle’s plane
// To determine the equation of the triangle’s plane, compute the triangle’s
// normal n := a1 a2 × a1 a3
// p is in the triangle’s plane if and only if a1 p · n = 0 or p · n = a1 · n,
// so substitute p := o + t d and solve:
//                              (a1 − o) · n
// (o + t d) · n = a1 · n ⇒ t = -------------
//                                  d · n
// Report no intersection if t < 0
// If t >= 0, the ray-plane intersection point is p = o + t d

// Step 2: Test if the intersection point is inside the triangle
// Compute the cross products v1 := pa1 × pa2, v2 := pa2 × pa3,
// and v3 := pa3 × pa1
// p is inside the triangle if and only if v1, v2, and v3 point in the
// same direction, i.e. the three dot products v1 · v2, v2 · v3, and
// v3 · v1 are all nonnegative

double Triangle::intersection(Ray& ray)
{
	// n := a1 a2 × a1 a3
	Vector n = a1.towards(a2).crossWith(a1.towards(a3));
	// Solve for t
	double t = (a1.minus(ray.origin).dotWith(n)) / (ray.direction.dotWith(n));
	
	// Report no intersection if t < 0
	if(t < 0)
	{
		return -1.0;
	}
	// If t >= 0, the ray-plane intersection point is p = o + t d
	else
	{
		Vector p = ray.origin.addTo(ray.direction.scaleBy(t));
		// Compute the cross products v1 := pa1 × pa2, v2 := pa2 × pa3, and v3 := pa3 × pa1
		Vector v1 = p.towards(a1).crossWith(p.towards(a2));
		Vector v2 = p.towards(a2).crossWith(p.towards(a3));
		Vector v3 = p.towards(a3).crossWith(p.towards(a1));
		// p is inside the triangle if and only if v1, v2, and v3 point in thesame direction
		// The three dot products v1 · v2, v2 · v3, and v3 · v1 must all be nonnegative
		if(v1.dotWith(v2) >= 0 && v2.dotWith(v3) >= 0 && v3.dotWith(v1) >= 0)
		{
			return t;
		}
		else
		{
			return -1.0;
		}
	}
}

// Triangle case
// n0 = (a3 - a1) × (a2 - a1)
// Check if n0 points to the side containing viewpoint; if not, negate n0
// if n0 · (viewpoint - a1) >= 0 then return n0, else return -n0
Vector Triangle::normal(Vector& intersection_point)
{
	Vector n0 = ((a3.minus(a1)).crossWith((a2.minus(a1))));
	if(n0.dotWith(viewpt.minus(a1)) >= 0)
	{
		return n0;
	}
	return n0.scaleBy(-1.0);
}

string Triangle::toString()
{
	stringstream ss;
	ss << "Vertex 1: " << a1.toString() << endl;
	ss << "Vertex 2: " << a2.toString() << endl;
	ss << "Vertex 3: " << a3.toString() << endl;
	ss << "Material: " << material.toString() << endl;
	return ss.str();
}