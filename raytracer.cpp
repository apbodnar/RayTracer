#include "raytracer.h"
#include <iostream>
#include <fstream>

using glm::dvec3;

RayTracer::RayTracer(unsigned int x,unsigned int y, dvec3 iPos, dvec3 lPos, unsigned int numPrims, unsigned int samples, unsigned int bounces) 
: scene(iPos,lPos, numPrims), viewX(x), viewY(y)
{
  numBytes = viewX * viewY * bytesPerPixel;
  screenBuffer = new unsigned char[numBytes];
  drawScene(samples, bounces);
  saveImage();
}

RayTracer::~RayTracer(){
  delete[] screenBuffer;
  screenBuffer = NULL;
}

/*
Viewport is clamped to -1,1 on x,y
*/

void RayTracer::drawScene(unsigned int samples, unsigned int bounces){
  dvec3 eyePos = scene.getEyePos();
  int c = 0;
  #pragma omp parallel for schedule(dynamic, 1)
  for(size_t i = 0; i < numBytes/bytesPerPixel; i++){
    dvec3 outColor;
    double x = (i % viewX + 0.5) / (viewX / 2) - 1.0;
    double y = -(i / viewY + 0.5) / (viewY / 2) + 1.0;
    dvec3 screenPos = dvec3(x,y,0);
    dvec3 eyeRay = glm::normalize(screenPos - eyePos);
    for(size_t j = 0; j < samples; j++){
      outColor += scene.processRay(eyeRay, screenPos, -1, bounces) * (1.0/samples);
    }
    #pragma omp atomic
    c++;
    if(c % (viewX * numBytes) == 0)
      std::cout << c/(numBytes/bytesPerPixel) << std::endl;
    outColor = glm::clamp(outColor, 0.0, 1.0);
    screenBuffer[i*bytesPerPixel + 0] = glm::pow(outColor[0],1/2.2)*255;
    screenBuffer[i*bytesPerPixel + 1] = glm::pow(outColor[1],1/2.2)*255;
    screenBuffer[i*bytesPerPixel + 2] = glm::pow(outColor[2],1/2.2)*255;
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
