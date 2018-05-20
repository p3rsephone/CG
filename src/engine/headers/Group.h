#ifndef __GROUP_H__
#define __GROUP_H__

#include <vector>
#include <iostream>
#include <typeinfo>
#include <string>
#include "Transformation.h"
#include "Model.h"
#include "Light.h"

using namespace std;

class Group {
private:
    vector<Transformation*> transformations;
    vector<Model*> models;
    vector<Group*> groups;
    vector<Light*> lights;
    float position;
public:
    Group();

    void addTransformation(Transformation* t);

    void addModel(Model* m);

    void addGroup(Group* g);

    void addLight(Light* l);

    void prepare();

    void draw();

    void transformation(Transformation* t);

    vector<Transformation*> getTransformations();

    vector<Model*> getModels();

    vector<Group*> getGroups();

    vector<Light*> getLight();
};
#endif
