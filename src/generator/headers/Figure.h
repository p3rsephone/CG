#ifndef __FIGURES_H__
#define __FIGURES_H__

#include <vector>
#include <math.h>
#include <iostream>
#include "../../../lib/headers/Point.h"

using namespace std;

class Figure {
    private:
        long npoints;
        vector<Point*> points;
    public:
        Figure();
        long getNPoints(){ return npoints; };
        vector<Point*> getPoints(){ return points; };
        void createPlane(double size);
        void createBox(double x, double y, double z, int d);
        void createSphere(double radius, int slices, int stacks);
        void createCone(double base, double height, int slices, int stacks);
        void createCylinder(double r, double height, int slices, int stacks);
};

#endif
