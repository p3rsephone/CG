#include "headers/Model.h"

Model::Model(){
}

void Model::addElement(Point* point){
  point_vector.push_back(point);
}

vector<Point*> Model::addElement(Point* point){
  return this->point_vector;
}
