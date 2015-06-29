#include "raytracer.h"
#include <iostream>
#include <fstream>

using glm::dvec3;

RayTracer::RayTracer(unsigned int x,unsigned int y, dvec3 iPos, unsigned int numPrims, unsigned int samples, unsigned int bounces) 
: scene(iPos, numPrims), viewX(x), viewY(y)
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
  double gc = 1/2.2;
  #pragma omp parallel for schedule(dynamic, 1)
  for(size_t i = 0; i < viewY; i++){
    for(size_t j = 0; j < viewX; j++){
      dvec3 outColor;
      double x = (j + 0.5) / (viewX / 2.0) - 1.0;
      double y = -(i + 0.5) / (viewY / (2.0 * viewY/viewX)) + 1.0*viewY/viewX;
      dvec3 screenPos = dvec3(x,y,0);
      dvec3 eyeRay = glm::normalize(screenPos - eyePos);
      for(size_t k = 0; k < samples; k++){
        outColor += scene.processRay(eyeRay, screenPos, -1, bounces) * (1.0/samples);
      }
      outColor = glm::clamp(outColor, 0.0, 1.0);
      int pc = (i*viewX + j)*bytesPerPixel;
      screenBuffer[pc + 0] = glm::pow(outColor[0],gc)*255;
      screenBuffer[pc + 1] = glm::pow(outColor[1],gc)*255;
      screenBuffer[pc + 2] = glm::pow(outColor[2],gc)*255;
    }
    #pragma omp atomic
    c++;
    std::cout << i*100.0/viewY << "%" << '\r';
    std::cout.flush();
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
