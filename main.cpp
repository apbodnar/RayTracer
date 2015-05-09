#include <iostream>
#include <cstdlib>
#include <vector>
#include "glm/glm.hpp"
#include "raytracer.h"

using glm::dvec3;

int main(){
  RayTracer rayTracer(1024,1024,dvec3(0,0,-1),dvec3(0,1,-1), 20);
  return 0;
}
