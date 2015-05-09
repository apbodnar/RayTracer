#include "raytracer.h"
#include <iostream>
#include <fstream>

using glm::dvec3;

RayTracer::RayTracer(unsigned int x,unsigned int y, dvec3 iPos, dvec3 lPos, unsigned int numPrims) : scene(iPos,lPos, numPrims), viewX(x), viewY(y)
{
  numBytes = viewX * viewY * bytesPerPixel;
  screenBuffer = new unsigned char[numBytes];
  //initBuffer();
  drawScene();
  saveImage();
}

RayTracer::~RayTracer(){
  delete[] screenBuffer;
  screenBuffer = NULL;
}

void RayTracer::initBuffer(){
  for(size_t i = 0; i < numBytes; i++){
    screenBuffer[i] = 255 - (i/bytesPerPixel % 256);
  }
  return;
}

/*
Viewport is clamped to -1,1 on x,y
*/

void RayTracer::drawScene(){
  dvec3 eyePos = scene.getEyePos();
  for(size_t i = 0; i < numBytes/bytesPerPixel; i++){
    double x = (i % viewX + 0.5) / (viewX / 2) - 1.0;
    double y = -(i / viewY + 0.5) / (viewY / 2) + 1.0;
    dvec3 eyeRay = glm::normalize(dvec3(x,y,0) - eyePos);
    dvec3 outColor = scene.processRay(eyeRay);
    screenBuffer[i*bytesPerPixel + 0] = outColor[0];
    screenBuffer[i*bytesPerPixel + 1] = outColor[1];
    screenBuffer[i*bytesPerPixel + 2] = outColor[2];
    //std::cout << eyeRay[0] << ", " << eyeRay[1] << std::endl;
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
