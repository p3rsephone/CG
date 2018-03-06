#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <time.h>
#include <headers/Point.h>

class Triangle {
  private:
    Point a,b,c;
    int color1;
    int color2;
    int color3;
    int counter;
  public:
    Triangle();
    Triangle(Point, Point, Point);
    void draw();
    void addPoint(Point*);
    Point A(){ return a; }
    Point B(){ return b; }
    Point C(){ return c; }
};
#endif
