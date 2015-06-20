#include "mesh.h"

Mesh::Mesh(std::string path, bool smooth){
  std::ifstream meshFile;
  meshFile.open(path);
  std::vector<dvec3> vertices;
  while(meshFile){
    char mode;
    meshFile >> mode;
    if(mode == 'v'){
      dvec3 vert;
      meshFile >> vert.x >> vert.y >> vert.z;
      vertices.push_back(vert*8.75 - dvec3(0,0.75,-1));
    } else if(mode == 'f'){
      unsigned int v1, v2, v3;
      meshFile >> v1 >> v2 >> v3;
      primitveList.push_back(new Triangle(vertices[v1-1]/5.0,vertices[v2-1]/5.0,vertices[v3-1]/5.0));
    }
  }
  primitveList.push_back(new Sphere(dvec3(0.75,0.5,1.0),
                                        0.4,
                                        dvec3(128,128,255)));
}