#ifndef __ENGINE_H_
#define __ENGINE_H_
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <math.h>
#include<vector>
#include<iostream>
#include "tinyxml2.h"
#include "Group.h"
#include "Parser.h"
#include "string.h"
using namespace std;
/**
 *@brief Class that defines Singleton for encapsulating GLUT functions
 *
 */
class Engine{
  private:
    Group* group;
    // angle of rotation for the camera direction
    float angle=0.0;
    // actual vector representing the camera's direction
    float lx=0.0f,lz=-1.0f,ly=0.0f;
    // XZ position of the camera
    float x=0.0f,z=5.0f, y=0.2f;
    // Radius of camera to 0.0
    float raio = 100;
    // angle that controls y axis default camera
    float alfa = 1;
    // angle that controls x axis default camera
    float beta = 1;
    // Variable to switch camera
    int camera = 0;
    // Variable to pause/unpause
    int pause = 0;
    // Engine variable for the singleton
    static Engine *engine;

/**
 *@brief Default Contructor
 *
 * @return void
 */
    Engine();

/**
 *@brief Wrapper for changeSize method
 *
 * @param width
 *
 * @param height
 *
 * @return void
 */
    static void changeSizeWrapper(int w, int h);

/**
 *@brief changeSize method
 *
 * @param width
 *
 * @param height
 *
 * @return void
 */
    void changeSize(int w, int h);

/**
 *@brief Method that draws x,y,z axys
 *
 * @return void
 */
    void axis_system();

/**
 *@brief Wrapper for specialKeys method
 *
 * @param key
 *
 * @param xx
 *
 * @param yy
 *
 * @return void
 */
    static void specialKeysWrapper(int key, int xx, int yy);
/**
 * @brief Handles special keys events (UP, DOWN, F1, ...)
 * @param key Key pressed
 * @param xx Mouse x coordinate
 * @param yy Mouse y coordinate
 */
    void specialKeys(int key, int xx, int yy);

/**
 *@brief Wrapper for keys method
 *
 * @param key
 *
 * @param xx
 *
 * @param yy
 *
 * @return void
 */
    static void processKeysWrapper(unsigned char key, int xx, int yy);
/**
 * @brief Handles normal keys events (q, w, e, r, ...)
 * @param key Key pressed
 * @param xx Mouse x coordinate
 * @param yy Mouse y coordinate
 */
    void processKeys(unsigned char key, int xx, int yy);


/**
 *@brief Wrapper for renderGroup method
 *
 * @return void
 */
    static void renderGroupWrapper(void);
/**
 *@brief Method that calls group draw method
 *
 * @return void
 */
    void renderGroup(void);
/**
 *@brief Method that initializes Glut
 *
 * @param argc
 *
 * @param argv
 *
 * @return void
 */

    static void initGL(int argc, char **argv);

/**
 *@brief Method that prints the help usage menu
 *
 * @return void
 */
    static void usage();
  public:
/**
 *@brief Method that creates a Engine instance if it doesn't exits
         or returns one if it's already created once
 *
 * @return void
 */
    static Engine* getInstance();
/**
 *@brief Method that parses the xml file and cretes the Group object
 *
 * @param argc
 *
 * @param argv
 *
 * @return void
 */
    void parse(int argc, char **argv);

    static void prepareWrapper();

    void prepare();
};
#endif
