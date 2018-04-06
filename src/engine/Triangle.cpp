#include "headers/Triangle.h"

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
 *@brief Method that adds name to a given Triangle
 *
 * @param Name of the model
 *
 *@return void
 */
void Triangle::addName(string name){
  this->name = name;
}

/**
 *@brief Method that draws a triangle in GLUT
 *
 *@return void
 */
void Triangle::draw(){
  if(!strcmp(this->name.c_str(),"sun.3d")){
    glColor3ub(255,140,0);
  }else if(!strcmp(this->name.c_str(),"mercury.3d")){
      glColor3ub(139,0,0);
  }else if(!strcmp(this->name.c_str(),"venus.3d")){
      glColor3ub(249,194,26);
  }else if(!strcmp(this->name.c_str(),"earth.3d")){
      glColor3ub(30,144,255);
  }else if(!strcmp(this->name.c_str(),"moon.3d")){
      glColor3ub(176,196,222);
  }else if(!strcmp(this->name.c_str(),"mars.3d")){
      glColor3ub(205,92,92);
  }else if(!strcmp(this->name.c_str(),"jupiter.3d")){
      glColor3ub(227,220,203);
  }else if(!strcmp(this->name.c_str(),"saturn.3d")){
      glColor3ub(216,202,157);
  }else if(!strcmp(this->name.c_str(),"neptune.3d")){
      glColor3ub(65,105,225);
  }else if(!strcmp(this->name.c_str(),"uranus.3d")){
      glColor3ub(100,149,237);
  }else if(!strcmp(this->name.c_str(),"pluto.3d")){
      glColor3ub(245,245,220);
  }else{
    glColor3ub(this->color1, this->color2, this->color3);
  }
  glBegin(GL_TRIANGLES);
    glVertex3f(this->a.X(),this->a.Y(),this->a.Z());
    glVertex3f(this->b.X(),this->b.Y(),this->b.Z());
    glVertex3f(this->c.X(),this->c.Y(),this->c.Z());
  glEnd();
}
