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

double Sphere::intersection(Ray& r)
{
	return -1.0;
}