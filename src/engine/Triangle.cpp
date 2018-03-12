#include "headers/Triangle.h"
#include <iostream>
using namespace std;
/**
 *@brief Contructor of empty triangle
 *
 *@return void
 */
Triangle::Triangle(){
  this->color1 = rand()%255;
  this->color2 = rand()%255;
  this->color3 = rand()%255;
  this->counter = 0;
}

/**
 *@brief Constructor of triangle with 3 given Points
 *
 * @param Point a off Triangle
 * @param Point b off Triangle
 * @param Point c off Triangle
 *
 *@return void
 */
Triangle::Triangle(Point a, Point b, Point c){
  this->a = a;
  this->b = b;
  this->c = c;
  this->color1 = rand()%255;
  this->color2 = rand()%255;
  this->color3 = rand()%255;
  this->counter = 3;
}

/**
 *@brief Method that adds point to a given Triangle
 *
 * @param Point to be added to Triangle
 *
 *@return void
 */
void Triangle::addPoint(Point* x){
  switch(this->counter){
    case(0):
      this->a= *x;
      this->counter++;
      break;
    case(1):
      this->b= *x;
      this->counter++;
      break;
    case(2):
      this->c= *x;
      this->counter++;
      break;
    default:
      break;
  }
}

/**
 *@brief Method that draws a triangle in GLUT
 *
 *@return void
 */
void Triangle::draw(){
  glColor3ub(this->color1, this->color2, this->color3);
  glBegin(GL_TRIANGLES);
    glVertex3f(this->a.X(),this->a.Y(),this->a.Z());
    glVertex3f(this->b.X(),this->b.Y(),this->b.Z());
    glVertex3f(this->c.X(),this->c.Y(),this->c.Z());
  glEnd();
}
