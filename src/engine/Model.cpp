#include "headers/Model.h"
Model::Model(){
}

void Model::addElement(Point* point){
  point_vector.push_back(point);
}

vector<Point*> Model::model(){
  return this->point_vector;
}
