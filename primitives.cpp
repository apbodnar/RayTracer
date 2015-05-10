#include "primitives.h"
#include "glm/gtx/norm.hpp"

using glm::dvec3;

const double MAX_DOUBLE = std::numeric_limits<double>::max();
const double EPSILON = std::numeric_limits<double>::epsilon();

/* Sphere implementaion */
Sphere::Sphere(dvec3 center, double radius, dvec3 color){
  this->center=center;
  this->color=color;
  this->radius=radius;
  ambient = 0.5;
}

Sphere::Sphere(dvec3 center, double radius){
  this->center=center;
  this->color=dvec3(0,255,0);
  this->radius=radius;
  ambient = 0.5;
}

double Sphere::checkCollision(dvec3 inRay, dvec3 origin){
  double scalar = glm::dot(inRay,origin - center);  
  double squared = (scalar * scalar) - glm::distance2(origin, center) + (radius * radius);
  double root = glm::sqrt(squared);
  return squared >= 0 ? -scalar - root : MAX_DOUBLE;
}

dvec3 Sphere::getNormal(dvec3 p){
  return glm::normalize(p - center);
}

dvec3 Sphere::getColor(dvec3 normal, dvec3 light){
  double i = glm::min(5.0 / glm::length2(light),1.0);
  double grade = glm::dot(normal, glm::normalize(light))*i;
  double diffuse = (1.0 - ambient) * grade;
  return color * (ambient + diffuse);
}



/* Triangle implementation */

Triangle::Triangle(dvec3 v1 , dvec3 v2, dvec3 v3, dvec3 color){
  this->v1=v1;
  this->v2=v2;
  this->v3=v3;
  this->color=color;
}

Triangle::Triangle(dvec3 v1 , dvec3 v2, dvec3 v3){
  this->v1=v1;
  this->v2=v2;
  this->v3=v3;
  this->color=dvec3(0,255,0);
}

double Triangle::checkCollision(dvec3 inRay, dvec3 origin){
  return 1.0;
}

dvec3 Triangle::getColor(){
  return color;
}