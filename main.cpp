#include <iostream>
#include <cstdlib>
#include <vector>
#include "glm/glm.hpp"
#include "raytracer.h"

using glm::dvec3;

int main(){
  RayTracer rayTracer(720,512,dvec3(0,0.125,-1.5), 5, 500, 5);
  return 0;
}
