#pragma once
#include "primitives.h"
#include <vector>

using glm::dvec3;

struct KDNode{
    dvec3 min, max;
    Primitive* primitveList;
    KDNode* right, left;
    KDNode(dvec3 min, max );
};