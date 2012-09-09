#include <utility>
#include "Ray.h"
#include "Primitive.h"
#pragma once

using namespace std;

pair<double, int> closestIntersection(Ray& r, vector<Primitive*> primitives)
{
	double min_t = -1.0;
	int primitive_id;
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