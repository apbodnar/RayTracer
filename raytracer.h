#include "glm/glm.hpp"
#include "scene.h"

using glm::dvec3;

class RayTracer{
  private:
    static const unsigned int bytesPerPixel = 3;
    unsigned char* screenBuffer;
    dvec3 eyePos, lightPos;
    Scene scene;
    void initBuffer();
    void drawScene();
    void saveImage();
    unsigned int viewX, viewY, numBytes;
  public:
    RayTracer(unsigned int,unsigned int,dvec3,dvec3, unsigned int);
    ~RayTracer();
};