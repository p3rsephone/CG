#include "headers/Model.h"
#include <iostream>
using namespace std;

Model::Model(){
}

void Model::addElement(Point* point){
  point_vector.push_back(point);
}

vector<Point*> Model::model(){
  return this->point_vector;
}

void Model::draw(){
  vector <Point*>::iterator it;

  glBegin(GL_TRIANGLES);

    glColor3f(1,0,0);


  for(it = this->point_vector.begin(); it != this->point_vector.end(); it++){
    cerr<< "glVertex3f("<<(*it)->X()<<","<<(*it)->Y()<<","<<(*it)->Z() << ");" << endl;

    glVertex3f((*it)->X(),(*it)->Y(),(*it)->Z());
  }
  glEnd();

}

void Model::test(){
  glBegin(GL_TRIANGLES);
    glColor3f(1,0,0);
    glVertex3f(7.5,0,7.5);
    glVertex3f(-7.5,0,-7.5);
    glVertex3f(-7.5,0,7.5);
    glColor3f(0,1,0);
    glVertex3f(-7.5,0,-7.5);
    glVertex3f(7.5,0,7.5);
    glVertex3f(7.5,0,-7.5);
  glEnd();
}
