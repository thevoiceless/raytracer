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
// Determine the equation of the triangle’s plane
// Compute the triangle’s normal n := a1 a2 × a1 a3
// p is in the triangle’s plane if and only if a1 p · n = 0, or p · n = a1 · n
// Substitute p := o + t d and solve:
//                              (a1 − o) · n
// (o + t d) · n = a1 · n ⇒ t = -------------
//                                  d ·n
// Report no intersection if t < 0
// If t >= 0, the ray-plane intersection point is p = o + t d.

// Step 2: Test if the intersection point is inside the triangle
// Compute the cross products v1 := pa1 × pa2, v2 := pa2 × pa3,
// and v3 := pa3 × pa1
// p is inside the triangle if and only if v1 , v2 and v3 point in the
// same direction, i.e. the three dot products v1 · v2, v2 · v3, and
// v3 · v1 are all nonnegative

double Triangle::intersection(Ray& ray)
{
	return -1.0;
}