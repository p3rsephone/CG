#include "headers/Patch.h"

Patch::Patch() {}

Patch::Patch(vector<Point*> v) : controlPoints(v) {}

vector<Point*> Patch::getControlPoints(){
  return controlPoints;
}

void Patch::addPoint(Point* p){
  controlPoints.push_back(p);
}