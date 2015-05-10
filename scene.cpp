#include <vector>
#include <iostream>
#include <time.h>
#include "primitives.h"
#include "scene.h"

using glm::dvec3;

const double MAX_DOUBLE = std::numeric_limits<double>::max();

double rf(){
  return rand() / (double)RAND_MAX;
}

Scene::Scene(){
  numPrimitives = 5;
  light = dvec3(1,1,1);
  eyePos = dvec3(0,0,0);
  initPrimList();
}

Scene::Scene(dvec3 eyePos, dvec3 light, unsigned int numPrims){
  numPrimitives = numPrims;
  this->light = light;
  this->eyePos = eyePos;
  initPrimList();
}

void Scene::initPrimList(){
  srand(time(NULL));
  for(size_t i = 0; i < numPrimitives; i++){
    primitveList.push_back(new Sphere(dvec3(rf()*2 -1,rf()*2-1,rf()+0.5),
                                      rf()/3.0,
                                      dvec3(rf()*255,rf()*255,rf()*255)));
  }
}

dvec3 Scene::processRay(dvec3 ray, dvec3 origin, unsigned int depth, int current){
  double t = MAX_DOUBLE;
  dvec3 color = dvec3(0,0,0);
  for(size_t i = 0; i < numPrimitives; i++){
    if(i == current) continue;
    Primitive* prim = primitveList[i];
    double d = prim->checkCollision(ray, origin);
    if(d < t && d > 0){
      t = d;
      dvec3 p = origin + ray * d;
      dvec3 normal = prim->getNormal(p);
      dvec3 lightRay = p - light;
      color = prim->getColor(-normal, lightRay);
      if(depth > 0){
        dvec3 reflection = ray - glm::dot(ray,normal) * 2 * normal;
        color += processRay(reflection,p,depth-1,i) * 0.2; 
      }
    }
  }
  return color;
}

dvec3 Scene::getEyePos(){
  return eyePos;
}