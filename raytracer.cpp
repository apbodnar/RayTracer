#include "raytracer.h"
#include <iostream>
#include <fstream>

using glm::dvec3;

RayTracer::RayTracer(unsigned int x,unsigned int y, dvec3 iPos, dvec3 lPos, unsigned int numPrims, unsigned int bounces) 
: scene(iPos,lPos, numPrims), viewX(x), viewY(y), numBounces(bounces)
{
  numBytes = viewX * viewY * bytesPerPixel;
  screenBuffer = new unsigned char[numBytes];
  drawScene();
  saveImage();
}

RayTracer::~RayTracer(){
  delete[] screenBuffer;
  screenBuffer = NULL;
}

/*
Viewport is clamped to -1,1 on x,y
*/

void RayTracer::drawScene(){
  dvec3 eyePos = scene.getEyePos();
  #pragma omp parallel for
  for(size_t i = 0; i < numBytes/bytesPerPixel; i++){
    double x = (i % viewX + 0.5) / (viewX / 2) - 1.0;
    double y = -(i / viewY + 0.5) / (viewY / 2) + 1.0;
    dvec3 screenPos = dvec3(x,y,0);
    dvec3 eyeRay = glm::normalize(screenPos - eyePos);
    dvec3 outColor = scene.processRay(eyeRay, screenPos, -1, numBounces);
    screenBuffer[i*bytesPerPixel + 0] = outColor[0];
    screenBuffer[i*bytesPerPixel + 1] = outColor[1];
    screenBuffer[i*bytesPerPixel + 2] = outColor[2];
  }
  return;
}

void RayTracer::saveImage(){
  std::ofstream ofs ("trace.ppm", std::ofstream::out | std::ofstream::binary);
  ofs << "P6" << std::endl;
  ofs << viewX << " " << viewY << std::endl;
  ofs << 255 << std::endl;
  ofs.write (reinterpret_cast<char*>(screenBuffer),numBytes);
  ofs.close();
  return;
}
