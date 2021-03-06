#ifndef __MODEL_H__
#define __MODEL_H__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <IL/il.h>
#include <string>
#include <vector>
#include <headers/Point.h>
#include <string.h>
#include <math.h>
#include "Material.h"

using namespace std;
/**
 *@brief Class that defines a geometric
 *       figure composed of triangles
 */
  class  Model{
      //Name of the object
      Material *colour_component;
      string name;
      GLuint buffer[3];
      GLuint buffers_size[3];
    //vector of triangles that compose a Model
      int size;
      int* state;
      GLuint texture;
    public:
      int image_width;
      int image_height;
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
      Model(string name, string texture_file,  vector<Point*> v_list, vector<Point*> n_list, vector<Point*> t_list);
      Model(string name);
/**
 *@brief Method that add a Triangle to a Model
 *
 * @param Triangle to be added
 *
 *@return void
 */
      void addElementPoint(float point);
      void addElementTexture(float point);
      void addElementNormal(float point);
/**
 *@brief Method that returns the vector triangle_vector
 *
 *@return vector of Triangles that compose Model
 */
      float* model();
      float* textures();
      float* normal();
/**
 *@brief Method that draws a model
 *
 *@return void
 */
      void loadTexture(string texture_file);
      void draw();
/**
 *@brief Method tu test a model
 *
 *@return void
 */
      void setTexture(GLuint t);

      void setColourComponent(Material* c);

      void test();

      void prepare(vector<Point*> vertex_list, vector<Point*> normal_list, vector<Point*> texture_list);

      string getName(){return this->name;};


};
#endif
