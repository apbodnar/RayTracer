#include "primitives.h"

using glm::vec3;

/* Sphere implementaion */
Sphere::Sphere(vec3 center, float radius, vec3 color){
  this->center=center;
  this->color=color;
  this->radius=radius;
}

Sphere::Sphere(vec3 center, float radius){
  this->center=center;
  this->color=vec3(255,0,0);
  this->radius=radius;
}

vec3 Sphere::checkCollison(float){
  return vec3(1,1,1);
}
vec3 Sphere::handleCollison(vec3){
  return vec3(1,1,1);
}
vec3 Sphere::getColor(){
  return color;
}
vec3 Sphere::getCenter(){
  return center;
}

/* Triangle implementation */

Triangle::Triangle(vec3 v1 , vec3 v2, vec3 v3, vec3 color){
  this->v1=v1;
  this->v2=v2;
  this->v3=v3;
  this->color=color;
}

Triangle::Triangle(vec3 v1 , vec3 v2, vec3 v3){
  this->v1=v1;
  this->v2=v2;
  this->v3=v3;
  this->color=vec3(0,255,0);
}

vec3 Triangle::checkCollison(float){
  return vec3(1,1,1);
}
vec3 Triangle::handleCollison(vec3){
  return vec3(1,1,1);
}
vec3 Triangle::getColor(){
  return color;
}