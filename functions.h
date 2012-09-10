#include <utility>
#include <iostream>
#include "Ray.h"
#include "Primitive.h"
#pragma once

using namespace std;

// Compute closest intersection point with the given ray
pair<double, int> closestIntersection(Ray& r, vector<Primitive*>& primitives)
{
	double min_t = -1.0;
	int primitive_id = 0;
	for(int i = 0; i < primitives.size(); ++i)
	{
		double t = primitives.at(i)->intersection(r);
		if(t != -1.0 && (min_t == -1 || t < min_t))
		{
			min_t = t;
			primitive_id = i;
		}
	}
	return make_pair(min_t, primitive_id);
}

// Compute eye ray for a pixel (i, j)
// Origin: The viewpoint
// Direction: ((Lower left corner + (((i + 0.5) / (x resolution)) * Horizontal vector) + (((j + 0.5) / (y resolution)) * Vertical vector)) - Viewpoint)
Ray eyeRay(int i, int j)
{
	return Ray(viewpt, 
		screenLowerLeftCorner.addTo(screenHorizVector.scaleBy((i + 0.5) / resolution_x).addTo(screenVertVector.scaleBy((j + 0.5) / resolution_y))).minus(viewpt));
}