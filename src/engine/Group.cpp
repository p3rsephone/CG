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

void Group::addLight(Light* l){
    lights.push_back(l);
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

vector<Light*> Group::getLight(){
    return lights;
}

void Group::prepare(){
  vector <Model*>::iterator mIt;
  for(mIt = this->models.begin(); mIt != this->models.end(); mIt++){
    //(*mIt)->prepare();
  }

  vector <Group*>::iterator gIt;
  for(gIt = this->groups.begin(); gIt != this->groups.end(); gIt++){
    (*gIt)->prepare();
  }
}


void Group::draw(){

  vector <Transformation*>::iterator tIt;

  for(tIt = this->transformations.begin(); tIt != this->transformations.end(); tIt++){
    this->transformation(*tIt);
  }

    vector <Light*>::iterator lIt;
    for(lIt = this->lights.begin(); lIt != this->lights.end(); lIt++){
        (*lIt)->draw();
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
        //cout << "translate " << tr->getX() << " " << tr->getY() << " " << tr->getZ() << endl;
        tr->renderCatmullRomCurve();
        tr->apply();
    } else if(Rotate* r = dynamic_cast<Rotate*>(t)){
        //cout << "rotate " << r->getAngle() << " " << r->getX() << " " << r->getY() << " " << r->getZ() << endl;
        r->apply();
    } else if(Scale* s = dynamic_cast<Scale*>(t)) {
        //cout << "scale " << s->getX() << " " << s->getY() << " " << s->getZ() << endl;
        glScalef(s->getX(), s->getY(), s->getZ());
    }
}
