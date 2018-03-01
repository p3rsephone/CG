#ifndef __MODEL_H__
#define __MODEL_H__
#include "Point.h"
  class  Model{
    private:
      vector<Point*> point_vector;
    public:
      Model();
      void addElement(Point*);
      vector<Point*> model();
};
#endif
