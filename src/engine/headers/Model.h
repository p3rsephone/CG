#ifndef __MODEL_H__
#define __MODEL_H__
#include <headers/Point.h>
#include <vector>
using namespace std;
  class  Model{
      vector<Point*> point_vector;
    public:
      Model();
      void addElement(Point*);
      vector<Point*> model();
};
#endif
