#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include<vector>
#include "tinyxml2.h"
#include "Scene.h"
#include "Parser.h"

class Engine{
  private:
    Scene* scene;
    float raio = 30;
    float beta = 1;
    float alfa = 1;
    int camera = 0;
    static Engine *engine;

    Engine();

    static void changeSizeWrapper(int w, int h);
    void changeSize(int w, int h);

    void axis_system();

    static void processKeysWrapper(unsigned char key, int xx, int yy);
    void processKeys(unsigned char key, int xx, int yy);

    static void renderSceneWrapper(void);
    void renderScene(void);
    static void initGL(int argc, char **argv);
  public:
    static Engine* getInstance();
    void parse(int argc, char **argv);
};
