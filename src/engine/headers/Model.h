#ifndef __MODEL_H__
#define __MODEL_H__
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <vector>
#include "Triangle.h"

using namespace std;

/**
 *@brief Class that defines a geometric
 *       figure composed of triangles
 */
  class  Model{
      //Name of the object
      string name;
    //vector of triangles that compose a Model
      float *point_array;
      int state;
    public:
/**
 *@brief Contructor of empty model with no name
 *
 *@return void
 */
      Model();
/**
 *@brief Contructor of empty model with name
 *
 *@return void
 */
      Model(string name, int size);
/**
 *@brief Method that add a Triangle to a Model
 *
 * @param Triangle to be added
 *
 *@return void
 */
      void addElement(float point);
/**
 *@brief Method that returns the vector triangle_vector
 *
 *@return vector of Triangles that compose Model
 */
      float* model();
/**
 *@brief Method that draws a model
 *
 *@return void
 */
      void draw();
/**
 *@brief Method tu test a model
 *
 *@return void
 */
      void test();
};
#endif
