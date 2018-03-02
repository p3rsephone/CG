#ifndef __SCENE_H__
#define __SCENE_H__
#include <string>
#include "Model.h"
#include <vector>
using namespace std;
  class  Scene{
      vector<Model*> model_vector;
    public:
      Scene();
      void addModel(Model*);
      vector<Model*> scene();
};
#endif
