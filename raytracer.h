#include "glm/glm.hpp"
#include "scene.h"

using glm::dvec3;

class RayTracer{
  private:
    static const unsigned int bytesPerPixel = 3;
    unsigned char* screenBuffer;
    unsigned int numBounces;
    dvec3 eyePos, lightPos;
    Scene scene;
    void drawScene(unsigned int, unsigned int);
    void saveImage();
    unsigned int viewX, viewY, numBytes;
  public:
    RayTracer(unsigned int,unsigned int,dvec3, unsigned int, unsigned int, unsigned int);
    ~RayTracer();
};