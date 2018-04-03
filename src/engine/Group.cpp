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

void Group::draw(){

  vector <Transformation*>::iterator it;

  for(it = this->transformations.begin(); it != this->transformations.end(); it++){
    this->transformations(*it)
  }

  vector <Model*>::iterator tIt;
  for(tIt = this->models.begin(); tIt != this->models.end(); tIt++){
    (*tIt)->draw();
  }


  vector <Group*>::iterator gIt;
  for(gIt = this->groups.begin(); gIt != this->groups.end(); gIt++){
    glPushMatrix();
    (*gIt)->draw();
    glPopMatrix();
  }
}

void Group::transformation(Transformation* t){
  int value = t->getType();
  double x = t->getX();
  double y = t->getY();
  double z = t->getZ();

 switch(value){
  case(1):
    glTranslatef(x,y,z);
    break;
  case(2):
    glRotatef(((Rotate*) t)->getAngle(),x,y,z);
    break;
  case(3):
    glScalef(x,y,z);
    break;
  default:
    break;
 }
}
