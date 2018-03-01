#include "headers/Scene.h"

Scene::Scene(){
}

void Scene::addModel(Model* model){
  modelents_vector.push_back(model);
}

vector<Model*> Scene::addModel(Model* model){
  return this->model_vector;
}


