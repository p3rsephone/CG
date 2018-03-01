#include "headers/Model.h"

Model::Model(){
}

void Model::addElement(Element* elem){
  elements_vector.push_back(elem);
}

vector<Element*> Model::addElement(Element* elem){
  return this->elements_vector;
}
