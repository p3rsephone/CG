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
 * Creates vertice points for a box which may have divisions
 * Usage: generator box 1 1 1 box.3d
 * Usage 2: generator box 1 1 1 3 box.3d
 * @param  x Size of the box in the X axis
 * @param  y Size of the box in the Y axis
 * @param  z Size of the box in the Z axis
 * @param  d Amount of divisions in each axis
 * @return   Vertice Points
 */
vector<Point*> createBox(double x, double y, double z, int d){
    vector<Point*> points;

    //Basically centers the box in the origin of the referential
    double realX = x/2;
    double realY = y/2;
    double realZ = z/2;

    //How much space is there between divisions
    double shiftX = x/d;
    double shiftY = y/d;
    double shiftZ = z/d;

    for(int i = 0; i < d ; i++){
        for(int j = 0; j < d ; j++){
            for(int k = 0; k < d ; k++){

                //Base
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * j, -realZ + shiftZ * k));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * j, -realZ + shiftZ * (k+1)));
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * j, -realZ + shiftZ * (k+1)));

                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * j, -realZ + shiftZ * k));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * j, -realZ + shiftZ * k));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * j, -realZ + shiftZ * (k+1)));

                //Top
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * (j+1), -realZ + shiftZ * k));
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * (j+1), -realZ + shiftZ * (k+1)));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * (j+1), -realZ + shiftZ * (k+1)));

                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * (j+1), -realZ + shiftZ * k));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * (j+1), -realZ + shiftZ * (k+1)));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * (j+1), -realZ + shiftZ * k));

                //Front face
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * j, -realZ + shiftZ * (k+1)));
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * (j+1), -realZ + shiftZ * (k+1)));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * j, -realZ + shiftZ * (k+1)));

                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * j, -realZ + shiftZ * (k+1)));
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * (j+1), -realZ + shiftZ * (k+1)));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * (j+1), -realZ + shiftZ * (k+1)));

                //Back Face
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * j, -realZ + shiftZ * k));
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * (j+1), -realZ + shiftZ * k));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * j, -realZ + shiftZ * k));

                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * j, -realZ + shiftZ * k));
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * (j+1), -realZ + shiftZ * k));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * (j+1), -realZ + shiftZ * k));

                //Left Face
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * j, -realZ + shiftZ * k));
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * j, -realZ + shiftZ * (k+1)));
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * (j+1), -realZ + shiftZ * k));

                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * (j+1), -realZ + shiftZ * k));
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * j, -realZ + shiftZ * (k+1)));
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * (j+1), -realZ + shiftZ * (k+1)));

                //Right Face
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * j, -realZ + shiftZ * k));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * (j+1), -realZ + shiftZ * k));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * j, -realZ + shiftZ * (k+1)));

                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * (j+1), -realZ + shiftZ * k));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * (j+1), -realZ + shiftZ * (k+1)));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * j, -realZ + shiftZ * (k+1)));
            }
        }
    }

    return points;
}

/**
 * Creates vertice points for a sphere with a certain radius, slices and stacks
 * Usage: generator sphere 1 20 20 sphere.3d
 * @param  radius   Radius of the sphere
 * @param  slices   Number of slices in the sphere
 * @param  stacks   Number of stacks in the sphere
 * @return      Vertice Points
 */
vector<Point*> createSphere(double radius, int slices, int stacks){
    vector<Point*> points;

    double x;
    double y;
    double z;

    double fiShift = M_PI*2 / slices;
    double thetaShift = M_PI*2 / stacks;

    //Using spheric coordinates
    //x = radius * sin(theta) * cos(fi);
    //y = radius * sin(theta) * sin(fi);
    //z = radius * cos(theta);
    for(double fi = 0; fi < M_PI*2 ; fi+= fiShift){
        for(double theta = 0; theta < M_PI*2 ; theta += thetaShift){
            //Triangular ends of the sphere
            if(theta == 0){
                points.push_back(new Point(radius * sin(theta) * cos(fi) , radius * sin(theta) * sin(fi) , radius * cos(theta)));
                points.push_back(new Point(radius * sin(theta+thetaShift) * cos(fi+fiShift) , radius * sin(theta+thetaShift) * sin(fi+fiShift) , radius * cos(theta+thetaShift)));
                points.push_back(new Point(radius * sin(theta+thetaShift) * cos(fi) , radius * sin(theta+thetaShift) * sin(fi) , radius * cos(theta+thetaShift)));
            }

            else if(theta == M_PI*2 - thetaShift){
                points.push_back(new Point(radius * sin(theta) * cos(fi) , radius * sin(theta) * sin(fi) , radius * cos(theta)));
                points.push_back(new Point(radius * sin(theta) * cos(fi+fiShift) , radius * sin(theta) * sin(fi+fiShift) , radius * cos(theta)));
                points.push_back(new Point(radius * sin(theta+thetaShift) * cos(fi+fiShift) , radius * sin(theta+thetaShift) * sin(fi+fiShift) , radius * cos(theta+thetaShift)));
            }

            //Rectangles within the sphere
            else {
                points.push_back(new Point(radius * sin(theta) * cos(fi) , radius * sin(theta) * sin(fi) , radius * cos(theta)));
                points.push_back(new Point(radius * sin(theta+thetaShift) * cos(fi+fiShift) , radius * sin(theta+thetaShift) * sin(fi+fiShift) , radius * cos(theta+thetaShift)));
                points.push_back(new Point(radius * sin(theta+thetaShift) * cos(fi) , radius * sin(theta+thetaShift) * sin(fi) , radius * cos(theta+thetaShift)));

                points.push_back(new Point(radius * sin(theta) * cos(fi) , radius * sin(theta) * sin(fi) , radius * cos(theta)));
                points.push_back(new Point(radius * sin(theta) * cos(fi+fiShift) , radius * sin(theta) * sin(fi+fiShift) , radius * cos(theta)));
                points.push_back(new Point(radius * sin(theta+thetaShift) * cos(fi+fiShift) , radius * sin(theta+thetaShift) * sin(fi+fiShift) , radius * cos(theta+thetaShift)));
            }

        }
    }

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
