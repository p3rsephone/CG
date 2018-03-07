#ifndef __MODEL_H__
#define __MODEL_H__

#include <math.h>
#include <vector>
#include "Triangle.h"
using namespace std;
  class  Model{
      vector<Triangle*> triangle_vector;
    public:
      Model();
      void addElement(Triangle*);
      vector<Triangle*> model();
      void draw();
      void test();
};
#endif
