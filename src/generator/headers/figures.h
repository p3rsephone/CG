#ifndef __FIGURES_H__
#define __FIGURES_H__

#include <vector>
#include <math.h>
#include <headers/Point.h>

using namespace std;

vector<Point*> createPlane(double size);
vector<Point*> createBox(double x, double y, double z, int d);
vector<Point*> createSphere(double radius, int slices, int stacks);
vector<Point*> createCone(double base, double height, int slices, int stacks);
vector<Point*> createCylinder(double r, double height, int slices, int stacks);

#endif
