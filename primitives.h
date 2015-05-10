#pragma once
#include "glm/glm.hpp"

using glm::dvec3;

class Primitive {
  public:
    virtual double checkCollision(dvec3, dvec3) = 0;
    virtual dvec3 getNormal(dvec3 p) = 0;
    virtual dvec3 getColor(dvec3,dvec3) = 0;
};

class Sphere: public Primitive{
  private: 
    dvec3 center;
    dvec3 color;
    double radius;
  public:
    Sphere(dvec3, double, dvec3);
    Sphere(dvec3, double);
    double checkCollision(dvec3, dvec3);
    dvec3 getColor(dvec3,dvec3);
    dvec3 getNormal(dvec3 p);
};

class Triangle: public Primitive{
  private: 
    dvec3 v1, v2, v3;
    dvec3 color;
  public:
    Triangle(dvec3, dvec3, dvec3, dvec3);
    Triangle(dvec3, dvec3, dvec3);
    double checkCollision(dvec3, dvec3);
    dvec3 getColor();
};