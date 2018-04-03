#ifndef __GROUP_H__
#define __GROUP_H__

#include <vector>
#include "Transformation.h"
#include "Model.h"

using namespace std;

class Group {
private:
    vector<Transformation*> transformations;
    vector<Model*> models;
    vector<Group*> groups;
public:
    Group();

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
