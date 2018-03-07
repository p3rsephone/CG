#ifndef __FIGURES_H__
#define __FIGURES_H__

using namespace std;

#include <vector>
#include <math.h>
#include <headers/Point.h>

vector<Point*> createPlane(double size);
vector<Point*> createBox(double x, double y, double z, int d);
vector<Point*> createSphere(double radius, int slices, int stacks);
vector<Point*> createCone(double base, double height, int slices, int stacks);

#endif
