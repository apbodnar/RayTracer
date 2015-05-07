#include "raytracer.h"
#include <iostream>
#include <fstream>

using glm::vec3;

RayTracer::RayTracer(int x, int y, vec3 iPos, vec3 lPos) : scene(lPos,iPos), viewX(x), viewY(y)
{
  numBytes = viewX * viewY * bytesPerPixel;
  screenBuffer = new char[numBytes];
  initBuffer();
  //drawScene();
  saveImage();
}

RayTracer::~RayTracer(){
  delete[] screenBuffer;
  screenBuffer = NULL;
}

void RayTracer::initBuffer(){
  for(size_t i = 0; i < numBytes; i++){
    screenBuffer[i] = i/bytesPerPixel % 256;
  }
  return;
}

void RayTracer::drawScene(){
  unsigned int numPrims = scene.getNumPrimitives();
  for(size_t i = 0; i < numBytes/bytesPerPixel; i++){
    int x = i % viewX;
    int y = i / viewY;
    vec3 eyeRay = scene.getEyePos();
    std::cout << x << ", " << y << std::endl;
  }
  return;
}

void RayTracer::saveImage(){
  std::ofstream ofs ("trace.ppm", std::ofstream::out | std::ofstream::binary);
  ofs << "P6" << std::endl;
  ofs << viewX << " " << viewY << std::endl;
  ofs << 255 << std::endl;
  ofs.write (screenBuffer,numBytes);
  ofs.close();
  return;
}
