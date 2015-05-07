#pragma once
#include "glm/glm.hpp"

using glm::vec3;

class Primitive {
  public:
    virtual vec3 checkCollison(float) = 0;
    virtual vec3 handleCollison(vec3) = 0;
    virtual vec3 getColor() = 0;
};

class Sphere: public Primitive{
  private: 
    vec3 center;
    vec3 color;
    float radius;
  public:
    Sphere(vec3, float, vec3);
    Sphere(vec3, float);
    float getRadius;
    vec3 checkCollison(float);
    vec3 handleCollison(vec3);
    vec3 getColor();
    vec3 getCenter();
};

class Triangle: public Primitive{
  private: 
    vec3 v1, v2, v3;
    vec3 color;
  public:
    Triangle(vec3, vec3, vec3, vec3);
    Triangle(vec3, vec3, vec3);
    vec3 checkCollison(float);
    vec3 handleCollison(vec3);
    vec3 getColor();
};