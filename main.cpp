#include <iostream>
#include <cstdlib>
#include <vector>
#include "glm/glm.hpp"
#include "raytracer.h"

using glm::dvec3;

int main(){
  RayTracer rayTracer(4096,4096,dvec3(0,0,-2),dvec3(0,0.75,0.5), 30, 2);
  return 0;
}
