#ifndef __POINT_H__
#define __POINT_H__
#include <string>
#include <sstream>
#include <math.h>

class Point {
  private:
    float x,y,z;
  public:
    Point();
    Point(float, float, float);
    Point(float, float);
    std::string toString();
    float X(){ return x; }
    float Y(){ return y; }
    float Z(){ return z; }
    Point* normalizeBezier();
    Point* normalizeSphere(float radius);
    Point* normalizeInverseSphere(float radius);
};
#endif
