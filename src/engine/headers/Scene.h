#ifndef __SCENE_H__
#define __SCENE_H__
#include <string>
#include "Model.h"
#include <vector>
using namespace std;
/**
 *@brief Class that defines a group of models
 *       represented on screen
 */
  class  Scene{
    //vector of Models in a scene
      vector<Model*> model_vector;
    public:
/**
 *@brief Default Constructor
 *
 * @return void
 */
      Scene();
/**
 *@brief Method that adds a Model to a Scene
 *
 * @param Model to add
 *
 * @return void
 */
      void addModel(Model*);
/**
 *@brief Method that returns the vector model_vector
 *
 * @return vetor that represents a scene
 */
      vector<Model*> scene();

/**
 *@brief Method that draws a scene
 *
 * @return void
 */
      void draw();
};
#endif
