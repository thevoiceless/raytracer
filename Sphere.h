#include <sstream>
#include <string>
#include <iostream>
#include "Vector.h"
#include "Material.h"
#include "Ray.h"
#include "Primitive.h"
#pragma once

class Sphere: public Primitive
{
public:
	Vector center;
	double radius;
	Material material;

	Sphere(Vector c, double r, Material m) : center(c), radius(r), material(m) {}

	double intersection(Ray& ray);
	Vector normal(Vector& intersection_point);
	Vector illumination(Vector& intersection_point);
	string toString();
};