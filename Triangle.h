#include <sstream>
#include <string>
#include <cmath>
#include "Vector.h"
#include "Material.h"
#include "Ray.h"
#include "Primitive.h"
#pragma once

class Triangle: public Primitive
{
public:
	Vector a1,a2,a3;
	Material material;

	Triangle(Vector one, Vector two, Vector three, Material m) : a1(one), a2(two), a3(three), material(m) {}

	double intersection(Ray& ray);
	Vector normal(Vector& intersection_point, Vector& viewpt);
	Vector illumination(Vector& intersection_point, Vector& viewpt, Vector& lightSource, double light_intensity, double ambient_light_intensity);
	string toString();
};