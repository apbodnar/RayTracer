#include "scene.h"
#include <time.h>

using glm::dvec3;

const double MAX_DOUBLE = std::numeric_limits<double>::max();

double rf(){
  return rand() / (double)RAND_MAX;
}

Scene::Scene(dvec3 eyePos, unsigned int numPrims) 
: mesh("bunny.obj", true)
{
  srand(time(NULL));
  this->light = light;
  this->eyePos = eyePos;
  initObjects(numPrims);
}

double Scene::getDepth(dvec3 ray, dvec3 origin, int current, int& pIndex){
  double t = MAX_DOUBLE;
  //unsigned int numPrims = mesh.getNumPrims();
  unsigned int numPrims = primitiveList.size();
  for(size_t i = 0; i < numPrims; i++){
    if(i == current) continue;
    //Primitive* prim = mesh.primitiveAt(i);
    Primitive* prim = primitiveList[i];
    double d = prim->checkCollision(ray, origin);
    if(d < t && d > 0){
      pIndex = i;
      t = d;
    }
  }
  return t;
}

void Scene::initObjects(unsigned int numPrims){
  srand(time(NULL));
  primitiveList.push_back(new Sphere(dvec3(0.7,0.7,1.7),0.25,glm::normalize(dvec3(rf(),rf(),rf())),0.75, 0));
  primitiveList.push_back(new Sphere(dvec3(-0.7,-0.7,0.3),0.25,glm::normalize(dvec3(rf(),rf(),rf())),0.75, 0));
  primitiveList.push_back(new Sphere(dvec3(-0.3,0.3,1),0.3,glm::normalize(dvec3(rf(),rf(),rf())),0.75, 0));
  primitiveList.push_back(new Sphere(dvec3(0.3,-0.3,1),0.3,glm::normalize(dvec3(rf(),rf(),rf())),0.75, 0));
  primitiveList.push_back(new Triangle(dvec3(-3,-1,2),dvec3(0,2,2),dvec3(3,-1,2),dvec3(1,1,1),0.75,0));
  primitiveList.push_back(new Triangle(dvec3(-1,-3,0),dvec3(-1,3,0),dvec3(-1,0,3),dvec3(1,0.1,0.1),1.0,0));
  primitiveList.push_back(new Triangle(dvec3(-3,-1,0),dvec3(0,-1,3),dvec3(3,-1,0),dvec3(1,1,1),0.75,0));
  primitiveList.push_back(new Triangle(dvec3(-3,1,0),dvec3(3,1,0),dvec3(0,1,3),dvec3(1,1,1),0.75,0));
  primitiveList.push_back(new Triangle(dvec3(1,-3,0),dvec3(1,0,3),dvec3(1,3,0),dvec3(0.1,0.1,1),1.0,0));
  primitiveList.push_back(new Sphere(dvec3(0,1,1), 0.25, dvec3(1,1,1), 0, 5.0));
  primitiveList.push_back(new Sphere(dvec3(-1,-1,2), 0.15, dvec3(0.1,0.1,1), 1, 6.0));
  primitiveList.push_back(new Sphere(dvec3(1,-1,2), 0.15, dvec3(1,0.1,0.1), 1, 6.0));
  primitiveList.push_back(new Sphere(dvec3(0,-1,0.5), 0.15, dvec3(0.1,1.0,0.1), 1, 6.0));
}

dvec3 Scene::processRay(dvec3 ray, dvec3 origin, int current, unsigned int depth){
  int pIndex = -1;
  double t = getDepth(ray, origin, current, pIndex);
  dvec3 color = dvec3(0,0,0);
  if(t < MAX_DOUBLE){
    //Primitive* prim = mesh.primitiveAt(pIndex);
    Primitive* prim = primitiveList[pIndex];
    dvec3 p = origin + ray * t;
    dvec3 normal = prim->getNormal(p);
    dvec3 emittance = prim->getEmittance();
    dvec3 reflectance = prim->getReflectance();
    if(depth > 0){
      dvec3 rRay = glm::normalize(dvec3(rf()-0.5,rf()-0.5,rf()-0.5));
      rRay = glm::dot(rRay, normal) > 0 ? rRay : -rRay;
      double cosTheta = glm::dot(rRay, normal);
      dvec3 BDRF = 2.0*reflectance*cosTheta;
      color = emittance + BDRF * processRay(rRay, p, pIndex, depth-1); 
    }
  }
  return color;
}

dvec3 Scene::getEyePos(){
  return eyePos;
}