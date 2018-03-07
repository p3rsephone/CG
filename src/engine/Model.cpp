#include "headers/Model.h"
using namespace std;

Model::Model(){
}

void Model::addElement(Triangle* triangle){
  triangle_vector.push_back(triangle);
}

vector<Triangle*> Model::model(){
  return this->triangle_vector;
}

void Model::draw(){
  vector <Triangle*>::iterator it;


  for(it = this->triangle_vector.begin(); it != this->triangle_vector.end(); it++){
    (*it)->draw();
  }

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
