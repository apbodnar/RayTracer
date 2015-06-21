#include <iostream>
#include <cstdlib>
#include <vector>
#include "glm/glm.hpp"
#include "raytracer.h"

using glm::dvec3;

int main(){
  RayTracer rayTracer(2048,2048,dvec3(0,0,-4),dvec3(-0.75,-0.75,1), 20, 1);
  return 0;
}
