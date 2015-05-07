#include <vector>
#include "primitives.h"
#include "scene.h"

using glm::vec3;

Scene::Scene(){
  light = vec3(1,1,1);
  eyePos = vec3(0,0,0);
  initPrimList();
}

Scene::Scene(vec3 light, vec3 eyePos){
  this->light = light;
  this->eyePos = eyePos;
  initPrimList();
}

void Scene::initPrimList(){
  for(size_t i = 0; i < numPrimitives; i++){
    primitveList.push_back(new Sphere(vec3(1,1,1), 1));
  }
}

vec3 Scene::getLight(){
 return light;
}
vec3 Scene::getEyePos(){
  return eyePos;
}