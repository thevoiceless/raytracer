#include "Vector.h"
#include "Material.h"
#pragma once

class Triangle: public Primitive
{
public:
	Vector a1,a2,a3;
	Material m;

	double intersection(Ray& r);
};