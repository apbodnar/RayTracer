#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "primitives.h"
#include <vector>

using glm::dvec3;

class Mesh{
  private: 
    std::vector<Primitive*> primitveList;
  public:
    unsigned int getNumPrims(){ return primitveList.size(); }
    Primitive* primitiveAt(unsigned int i){ return primitveList[i]; }
    Mesh(std::string, bool);
};