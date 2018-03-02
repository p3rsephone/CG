#include "headers/Scene.h"

Scene::Scene(){
}

void Scene::addModel(Model* model){
  model_vector.push_back(model);
}

vector<Model*> Scene::scene(){
  return this->model_vector;
}


