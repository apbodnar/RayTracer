#include <iostream>
#include <cstdlib>
#include <vector>
#include "glm/glm.hpp"
#include "raytracer.h"

using glm::dvec3;

int main(){
  RayTracer rayTracer(512,512,dvec3(0,0,-3),dvec3(-0,0,1.1), 10, 500, 5);
  return 0;
}
