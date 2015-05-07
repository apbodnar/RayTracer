#include <vector>
#include "glm/glm.hpp"
#include "primitives.h"

using glm::vec3;

class Scene{
  private:
    unsigned int numPrimitives;
    std::vector<Primitive*> primitveList;
    vec3 light;
    vec3 eyePos;
    void initPrimList();
  public:
    Scene();
    Scene(vec3,vec3);
    Primitive* primitiveAt(unsigned int i){ return primitveList[i]; };
    unsigned int getNumPrimitives(){ return numPrimitives; }
    vec3 getLight();
    vec3 getEyePos();
};