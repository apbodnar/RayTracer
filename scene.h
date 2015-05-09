#include <vector>
#include "glm/glm.hpp"
#include "primitives.h"

using glm::dvec3;

class Scene{
  private:
    unsigned int numPrimitives;
    std::vector<Primitive*> primitveList;
    dvec3 light;
    dvec3 eyePos;
    void initPrimList();
  public:
    Scene();
    Scene(dvec3,dvec3, unsigned int);
    Primitive* primitiveAt(unsigned int i){ return primitveList[i]; };
    unsigned int getNumPrimitives(){ return numPrimitives; }
    dvec3 getLight();
    dvec3 getEyePos();
    dvec3 processRay(dvec3);
};