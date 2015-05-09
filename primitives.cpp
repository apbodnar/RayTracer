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
}

Sphere::Sphere(dvec3 center, double radius){
  this->center=center;
  this->color=dvec3(255,0,0);
  this->radius=radius;
}

double Sphere::checkCollision(dvec3 inRay, dvec3 origin){
  double scalar = glm::dot(inRay,origin - center);  
  double squared = (scalar * scalar) - glm::distance2(origin, center) + (radius * radius);
  double root = glm::sqrt(squared);
  return squared >= 0 ? -scalar + root : MAX_DOUBLE;
}

dvec3 Sphere::handleCollision(dvec3){
  return dvec3(1,1,1);
}
dvec3 Sphere::getColor(){
  return color;
}
dvec3 Sphere::getCenter(){
  return center;
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
dvec3 Triangle::handleCollision(dvec3){
  return dvec3(1,1,1);
}
dvec3 Triangle::getColor(){
  return color;
}