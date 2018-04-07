#ifndef __GROUP_H__
#define __GROUP_H__

#include <vector>
#include <iostream>
#include <typeinfo>
#include <string>
#include "Transformation.h"
#include "Model.h"

using namespace std;

class Group {
private:
    vector<Transformation*> transformations;
    vector<Model*> models;
    vector<Group*> groups;
    float speed;
    float position;
public:
    Group();

    Group(float speed);

    void addTransformation(Transformation* t);

    void addModel(Model* m);

    void addGroup(Group* g);

    void draw();

    void transformation(Transformation* t);

    vector<Transformation*> getTransformations();

    vector<Model*> getModels();

    vector<Group*> getGroups();
};
#endif
