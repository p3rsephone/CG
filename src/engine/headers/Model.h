#ifndef __MODEL_H__
#define __MODEL_H__
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

#include <headers/Point.h>
#include <vector>
using namespace std;
  class  Model{
      vector<Point*> point_vector;
    public:
      Model();
      void addElement(Point*);
      vector<Point*> model();
      void draw();
};
#endif
