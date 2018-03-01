#ifndef __SCENE_H__
#define __SCENE_H__
#include "headers/Model.h"
#include <string>
  class  Scene{
    private:
      vector<Model*> model_vector;
    public:
      Scene();
      void addModel(Element*);
      vector<Model*> model();
};
#endif
