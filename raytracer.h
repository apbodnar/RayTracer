#include "glm/glm.hpp"
#include "scene.h"

using glm::vec3;

class RayTracer{
  private:
    static const unsigned int bytesPerPixel = 3;
    char* screenBuffer;
    vec3 eyePos;
    vec3 lightPos;
    Scene scene;
    void initBuffer();
    void drawScene();
    void saveImage();
    int viewX, viewY, numBytes;
  public:
    RayTracer(int,int,vec3,vec3);
    ~RayTracer();
};