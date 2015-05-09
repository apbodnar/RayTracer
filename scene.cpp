#include <vector>
#include <iostream>
#include <time.h>
#include "primitives.h"
#include "scene.h"

using glm::dvec3;

const double MAX_DOUBLE = std::numeric_limits<double>::max();

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
    primitveList.push_back(new Sphere(dvec3(rand()*2 -1,rand()*2-1,rand()*2-1), rand()/10.0));
  }
}

dvec3 Scene::processRay(dvec3 eyeRay){
  double t = MAX_DOUBLE;
  for(size_t i = 0; i < numPrimitives; i++){
    Primitive* prim = primitveList[i];
    t = glm::min(prim->checkCollision(eyeRay,eyePos), t);
    
    //std::cout << t << std::endl;
  }
  return t < MAX_DOUBLE ? dvec3(255,0,0) : dvec3(0,255,0);
}

dvec3 Scene::getLight(){
 return light;
}
dvec3 Scene::getEyePos(){
  return eyePos;
}