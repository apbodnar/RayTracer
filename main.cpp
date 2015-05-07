#include <iostream>
#include <cstdlib>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
#include "raytracer.h"

using glm::vec3;
const float epsilon = std::numeric_limits<float>::epsilon();
const int numPrims = 10;

int main(){
  RayTracer rayTracer(256,256,vec3(1000,0,0),vec3(128,128,256));
  return 0;
}
