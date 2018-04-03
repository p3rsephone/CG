#include "headers/Group.h"

Group::Group(){
}

void Group::addTransformation(Transformation* t){
    transformations.push_back(t);
}

void Group::addModel(Model* m){
    models.push_back(m);
}

void Group::addGroup(Group* g){
    groups.push_back(g);
}

vector<Transformation*> Group::getTransformations(){
    return transformations;
}

vector<Model*> Group::getModels(){
    return models;
}

vector<Group*> Group::getGroups(){
    return groups;
}


