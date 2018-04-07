#ifndef __MODEL_H__
#define __MODEL_H__

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
      //Type of the object
      int type;
    //vector of triangles that compose a Model
      vector<Triangle*> triangle_vector;
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
      Model(string name,int type);
/**
 *@brief Method that add a Triangle to a Model
 *
 * @param Triangle to be added
 *
 *@return void
 */
      void addElement(Triangle*);
/**
 *@brief Method that returns the vector triangle_vector
 *
 *@return vector of Triangles that compose Model
 */
      vector<Triangle*> model();
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
