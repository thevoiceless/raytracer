#include "Vector.h"
#include "Material.h"
#pragma once

class Sphere: public Primitive
{
  public:
    Vector center;
    double radius;
    Material m;
    
    double intersection(Ray& r);
};