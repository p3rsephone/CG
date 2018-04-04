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

  vector <Transformation*>::iterator tIt;

  for(tIt = this->transformations.begin(); tIt != this->transformations.end(); tIt++){
    this->transformation(*tIt);
  }

  vector <Model*>::iterator mIt;
  for(mIt = this->models.begin(); mIt != this->models.end(); mIt++){
    (*mIt)->draw();
  }


  vector <Group*>::iterator gIt;
  for(gIt = this->groups.begin(); gIt != this->groups.end(); gIt++){
    glPushMatrix();
    (*gIt)->draw();
    glPopMatrix();
  }
}

void Group::transformation(Transformation* t){
    if(Translate* tr = dynamic_cast<Translate*>(t)){
        glTranslatef(tr->getX(),tr->getY(),tr->getZ());
    } else if(Rotate* r = dynamic_cast<Rotate*>(t)){
        glRotatef(r->getAngle(),r->getX(),r->getY(),r->getZ());
    } else if(Scale* s = dynamic_cast<Scale*>(t)) {
        glTranslatef(s->getX(), s->getY(), s->getZ());
    }
}
