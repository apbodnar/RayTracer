#include "scene.h"
#include <time.h>

using glm::dvec3;

const double MAX_DOUBLE = std::numeric_limits<double>::max();

double rf(){
  return rand() / (double)RAND_MAX;
}

Scene::Scene(dvec3 eyePos, dvec3 light, unsigned int numPrims) 
: mesh("gourd.obj", true)
{
  this->light = light;
  this->eyePos = eyePos;
  initObjects(numPrims);
}

double Scene::getDepth(dvec3 ray, dvec3 origin, int current, int& pIndex){
  double t = MAX_DOUBLE;
  unsigned int numPrims = mesh.getNumPrims();
  for(size_t i = 0; i < numPrims; i++){
    if(i == current) continue;
    Primitive* prim = mesh.primitiveAt(i);
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
  for(size_t i = 0; i < numPrims; i++){
    primitveList.push_back(new Sphere(dvec3(rf()*2 -1,rf()*2-1,rf()+0.5),
                                        rf()/5.0 + 0.1,
                                        dvec3(rf()*255,rf()*255,rf()*255)));
  }
}

dvec3 Scene::processRay(dvec3 ray, dvec3 origin, int current, unsigned int depth){
  int pIndex = -1, n;
  double t = getDepth(ray, origin, current, pIndex);
  dvec3 color = dvec3(0,0,0);
  if(t < MAX_DOUBLE){
    Primitive* prim = mesh.primitiveAt(pIndex);
    dvec3 p = origin + ray * t;
    dvec3 normal = prim->getNormal(p);
    dvec3 lightRay = p - light;
    bool shaded = getDepth(glm::normalize(-lightRay),p, pIndex, n) < glm::length(lightRay);
    color = prim->getColor(-normal, lightRay, ray, shaded);
    if(depth > 0){
      dvec3 reflection = ray - glm::dot(ray,normal) * 2 * normal;
      color += processRay(reflection, p, pIndex, depth-1) * 0.3; 
    }
  }
  return glm::clamp(color,0.0,255.0);
}

dvec3 Scene::getEyePos(){
  return eyePos;
}