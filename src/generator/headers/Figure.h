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
        vector<Point*> textures;
        vector<Point*> normals;
    public:
        Figure();
        Figure(vector<Point*>,vector<Point*>,vector<Point*>);
        long getNPoints(){ return npoints; };
        vector<Point*> getPoints(){ return points; };
        vector<Point*> getTextures(){ return textures; };
        vector<Point*> getNormals(){ return normals; };
        void createPlane(float size);
        void createBox(float x, float y, float z, int d);
        void createSphere(float radius, int slices, int stacks);
        void createCone(float base, float height, int slices, int stacks);
        void createCylinder(float r, float height, int slices, int stacks);
};

#endif
