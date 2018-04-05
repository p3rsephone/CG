#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <string>
#include <string.h>
#include <math.h>
#include <time.h>
#include <headers/Point.h>

using namespace std;

/**
 *@brief Class that defines a triangle in GLUT
 */
class Triangle {
  private:
    // Points a,b,c
    Point a,b,c;
    // Name of the model
    string name;
    // Color 1
    int color1;
    // Color 2
    int color2;
    // Color 3
    int color3;
    // Counter to know if triangle is complete
    int counter;
  public:
/**
 *@brief Contructor of empty triangle
 *
 *@return void
 */
    Triangle();
/**
 *@brief Constructor of triangle with 3 given Points
 *
 * @param Point a off Triangle
 * @param Point b off Triangle
 * @param Point c off Triangle
 *
 *@return void
 */
    Triangle(Point, Point, Point);
/**
 *@brief Method that adds point to a given Triangle
 *
 * @param Point to be added to Triangle
 *
 *@return void
 */
    void addPoint(Point*);
/**
 *@brief Method that adds name to a given Triangle
 *
 * @param Name of the model
 *
 *@return void
 */
    void addName(string);
/**
 *@brief Method that draws a triangle in GLUT
 *
 *@return void
 */
    void draw();
/**
 *@brief Method that gives Point A off Triangle
 *
 *@return void
 */
    Point A(){ return a; }
/**
 *@brief Method that gives Point B off Triangle
 *
 *@return void
 */
    Point B(){ return b; }
/**
 *@brief Method that gives Point C off Triangle
 *
 *@return void
 */
    Point C(){ return c; }
};
#endif
