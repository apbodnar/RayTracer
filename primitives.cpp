#include "primitives.h"
#include "glm/gtx/norm.hpp"
#include <iostream>

using glm::dvec3;

const double MAX_DOUBLE = std::numeric_limits<double>::max();
const double EPSILON = std::numeric_limits<double>::epsilon();


dvec3 Primitive::getColor(dvec3 normal, dvec3 light, dvec3 ray, bool shaded){
  dvec3 lightDir = glm::normalize(light);
  double i = glm::min(5.0 / (1.0 + glm::length2(light)),1.0);
  dvec3 half = glm::normalize(lightDir + ray);
  double specular  = glm::pow(glm::dot(half,normal),128)*i;
  double grade = glm::clamp(glm::dot(normal, lightDir),0.0,1.0)*i;
  double diffuse = (1.0 - ambient) * grade;
  if(!shaded)
    return color * (ambient + diffuse) + specular*255;
  else
    return color * ambient;
}


/* Sphere implementaion */
Sphere::Sphere(dvec3 center, double radius, dvec3 color){
  this->center=center;
  this->color=color;
  this->radius=radius;
  ambient = 0.25;
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

/* Triangle implementation */

Triangle::Triangle(dvec3 v1 , dvec3 v2, dvec3 v3, dvec3 color){
  this->v1=v1;
  this->v2=v2;
  this->v3=v3;
  this->color=color;
  ambient = 0.25;
}

Triangle::Triangle(dvec3 v1 , dvec3 v2, dvec3 v3){
  this->v1=v1;
  this->v2=v2;
  this->v3=v3;
  this->color=dvec3(0,255,0);
  ambient = 0.5;
}

double Triangle::checkCollision(dvec3 inRay, dvec3 origin){ 
  dvec3 e1 = v2 - v1;
  dvec3 e2 = v3 - v1;
  dvec3 p = glm::cross(inRay,e2);
  double det = glm::dot(p,e1);
  double invDet = 1.0 / det;
  if(det > -EPSILON && det < EPSILON) return MAX_DOUBLE;
  dvec3 span = origin - v1;
  double u = glm::dot(span, p) * invDet;
  if(u < 0.0 || u > 1.0) return MAX_DOUBLE;
  dvec3 q = glm::cross(span,e1);
  double v = glm::dot(inRay, q) * invDet;
  if(v < 0.0 || u + v  > 1.0) return MAX_DOUBLE;
  double t = glm::dot(e2, q) * invDet;
  return t;
}

dvec3 Triangle::getNormal(dvec3 p){
  dvec3 e1 = v2 - v1;
  dvec3 e2 = v3 - v1;
  return glm::normalize(glm::cross(e1,e2));
}