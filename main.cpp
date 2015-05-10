#include <iostream>
#include <cstdlib>
#include <vector>
#include "glm/glm.hpp"
#include "raytracer.h"

using glm::dvec3;

int main(){
  RayTracer rayTracer(2048,2048,dvec3(0,0,-2),dvec3(0,0,0.5), 20, 2);
  return 0;
}
