#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include<vector>
#include<iostream>
#include "tinyxml2.h"
#include "Scene.h"
#include "Parser.h"
#include "string.h"
using namespace std;
class Engine{
  private:
    Scene* scene;
    // angle of rotation for the camera direction
    float angle=0.0;
    // actual vector representing the camera's direction
    float lx=0.0f,lz=-1.0f;
    // XZ position of the camera
    float x=0.0f,z=5.0f;
    float raio = 30;
    float beta = 1;
    float alfa = 1;
    int camera = 0;
    static Engine *engine;

    Engine();

    static void changeSizeWrapper(int w, int h);
    void changeSize(int w, int h);

    void axis_system();

    static void specialKeysWrapper(int key, int xx, int yy);
    void specialKeys(int key, int xx, int yy);

    static void processKeysWrapper(unsigned char key, int xx, int yy);
    void processKeys(unsigned char key, int xx, int yy);

    static void renderSceneWrapper(void);
    void renderScene(void);
    static void initGL(int argc, char **argv);
    static void usage();
  public:
    static Engine* getInstance();
    void parse(int argc, char **argv);
};
