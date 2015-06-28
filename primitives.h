#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"
#include <iostream>
#include <limits>

using glm::dvec3;

class Primitive {
  protected:
    dvec3 color;
    double emittance;
    double reflectance;
  public:
    virtual double checkCollision(dvec3, dvec3) = 0;
    virtual dvec3 getNormal(dvec3 p) = 0;
    virtual dvec3 getEmittance(){ return color*emittance; }
    virtual dvec3 getReflectance(){ return color*reflectance; }
};

class Sphere: public Primitive{
  private: 
    dvec3 center;
    double radius;
  public:
    Sphere(dvec3, double, dvec3, double, double);
    Sphere(dvec3, double);
    double checkCollision(dvec3, dvec3);
    dvec3 getNormal(dvec3 p);
};

class Triangle: public Primitive{
  private: 
    dvec3 v1, v2, v3;
    dvec3 n1, n2, n3;
  public:
    Triangle(dvec3, dvec3, dvec3, dvec3, double, double);
    Triangle(dvec3, dvec3, dvec3);
    double checkCollision(dvec3, dvec3);
    dvec3 getNormal(dvec3 p);
};