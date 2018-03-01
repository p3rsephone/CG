#include "headers/figures.h"
#include <iostream>

/**
 * Creates vertice points for a square in the XZ plane
 * Usage: generator plane 2 plane.3d
 * @param  size Size of the side of the square
 * @return      Vertice Points
 */

vector<Point*> createPlane(double size){
    double height = size/2;
    vector<Point*> points;

    points.push_back(new Point(height,0,height));
    points.push_back(new Point(-height,0,height));
    points.push_back(new Point(-height,0,-height));

    points.push_back(new Point(-height,0,-height));
    points.push_back(new Point(height,0,-height));
    points.push_back(new Point(height,0,height));

    return points;
}

/**
 * [createBox description]
 * Usage: generator box 1 1 1 box.3d
 * Usage 2: generator box 1 1 1 3 box.3d
 * @param  x [description]
 * @param  y [description]
 * @param  z [description]
 * @param  d [description]
 * @return   [description]
 */
vector<Point*> createBox(double x, double y, double z, int d){
    vector<Point*> points;

    return points;
}
/**
 * [createSphere description]
 * Usage: generator sphere 1 20 20 sphere.3d
 * @param  radius   [description]
 * @param  slices   [description]
 * @param  stacks   [description]
 * @return          [description]
 */
vector<Point*> createSphere(double radius, int slices, int stacks){
    vector<Point*> points;

    return points;
}

/**
 * [createCone description]
 * Usage: generator cone 1 1 20 20 cone.3d
 * @param  base     [description]
 * @param  height   [description]
 * @param  slices   [description]
 * @param  stacks   [description]
 * @return          [description]
 */
vector<Point*> createCone(double base, double height, int slices, int stacks){
    vector<Point*> points;

    return points;
}
