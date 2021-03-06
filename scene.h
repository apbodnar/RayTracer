#include <vector>
#include <iostream>
#include <limits>
#include "glm/glm.hpp"
#include "primitives.h"
#include "mesh.h"

using glm::dvec3;

class Scene{
  private:
    std::vector<Primitive*> primitiveList;
    dvec3 light;
    dvec3 eyePos;
    void initObjects(unsigned int);
    double getDepth(dvec3, dvec3, int, int&);
    Mesh mesh;
  public:
    Scene(dvec3, unsigned int);
    Primitive* primitiveAt(unsigned int i){ return primitiveList[i]; };
    dvec3 getEyePos();
    dvec3 processRay(dvec3, dvec3, int, unsigned int);
};