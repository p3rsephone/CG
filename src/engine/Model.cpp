#include "headers/Model.h"
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
  for(it = this->point_vector.begin(); it != this->point_vector.end(); it++){
    glVertex3f(*it->x,*it->y,*it->z);
  }
  glEnd();

}
