#include "headers/Figure.h"

Figure::Figure(){
}

/**
 * @brief Creates vertice points for a square in the XZ plane
 * Usage: generator plane 2 plane.3d
 * @param  size Size of the side of the square
 */

void Figure::createPlane(double size){
    double height = size/2;
    points.push_back(new Point(height,0,height));
    points.push_back(new Point(-height,0,-height));
    points.push_back(new Point(-height,0,height));

    points.push_back(new Point(-height,0,-height));
    points.push_back(new Point(height,0,height));
    points.push_back(new Point(height,0,-height));
}

/**
 * @brief Creates vertice points for a box which may have divisions
 * Usage: generator box 1 1 1 box.3d
 * Usage 2: generator box 1 1 1 3 box.3d
 * @param  x Size of the box in the X axis
 * @param  y Size of the box in the Y axis
 * @param  z Size of the box in the Z axis
 * @param  d Amount of divisions in each axis
 */
void Figure::createBox(double x, double y, double z, int d){
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

                //Base
                points.push_back(new Point(-realX + shiftX * i, -realY, -realZ + shiftZ * j));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY, -realZ + shiftZ * (j+1)));
                points.push_back(new Point(-realX + shiftX * i, -realY, -realZ + shiftZ * (j+1)));

                points.push_back(new Point(-realX + shiftX * i, -realY, -realZ + shiftZ * j));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY, -realZ + shiftZ * j));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY, -realZ + shiftZ * (j+1)));

                //Top
                points.push_back(new Point(-realX + shiftX * i, realY, -realZ + shiftZ * j));
                points.push_back(new Point(-realX + shiftX * i, realY, -realZ + shiftZ * (j+1)));
                points.push_back(new Point(-realX + shiftX * (i+1), realY, -realZ + shiftZ * (j+1)));

                points.push_back(new Point(-realX + shiftX * i, realY, -realZ + shiftZ * j));
                points.push_back(new Point(-realX + shiftX * (i+1), realY, -realZ + shiftZ * (j+1)));
                points.push_back(new Point(-realX + shiftX * (i+1), realY, -realZ + shiftZ * j));

                //Front face
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * j, realZ));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * j, realZ));
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * (j+1), realZ));


                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * j, realZ));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * (j+1), realZ));
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * (j+1), realZ));


                //Back Face
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * j, -realZ));
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * (j+1), -realZ));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * j, -realZ));

                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * j, -realZ));
                points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * (j+1), -realZ));
                points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * (j+1), -realZ));

                //Left Face
                points.push_back(new Point(-realX, -realY + shiftY * i, -realZ + shiftZ * j));
                points.push_back(new Point(-realX, -realY + shiftY * i, -realZ + shiftZ * (j+1)));
                points.push_back(new Point(-realX, -realY + shiftY * (i+1), -realZ + shiftZ * j));

                points.push_back(new Point(-realX, -realY + shiftY * (i+1), -realZ + shiftZ * j));
                points.push_back(new Point(-realX, -realY + shiftY * i, -realZ + shiftZ * (j+1)));
                points.push_back(new Point(-realX, -realY + shiftY * (i+1), -realZ + shiftZ * (j+1)));

                //Right Face
                points.push_back(new Point(realX, -realY + shiftY * i, -realZ + shiftZ * j));
                points.push_back(new Point(realX, -realY + shiftY * (i+1), -realZ + shiftZ * j));
                points.push_back(new Point(realX, -realY + shiftY * i, -realZ + shiftZ * (j+1)));

                points.push_back(new Point(realX, -realY + shiftY * (i+1), -realZ + shiftZ * j));
                points.push_back(new Point(realX, -realY + shiftY * (i+1), -realZ + shiftZ * (j+1)));
                points.push_back(new Point(realX, -realY + shiftY * i, -realZ + shiftZ * (j+1)));
        }
    }
}

/**
 * @brief Creates vertice points for a sphere with a certain radius, slices and stacks
 * Usage: generator sphere 1 20 20 sphere.3d
 * @param  radius   Radius of the sphere
 * @param  slices   Number of slices in the sphere
 * @param  stacks   Number of stacks in the sphere
 */
void Figure::createSphere(double radius, int slices, int stacks){

    double fiShift = M_PI*2 / slices;
    double thetaShift = M_PI / stacks;

    //Using spheric coordinates
    //x = radius * sin(theta) * cos(fi);
    //y = radius * sin(theta) * sin(fi);
    //z = radius * cos(theta);
    for(double fi = 0; fi < slices ; fi++){
        for(double theta = 0; theta < stacks ; theta ++){

            double rtheta = theta * thetaShift;
            double rfi = fi * fiShift;

            //Triangular ends of the sphere
            if(theta == 0){
                points.push_back(new Point(radius * sin(rtheta+thetaShift) * sin(rfi+fiShift), radius * cos(theta+thetaShift) ,radius * sin(rtheta+thetaShift) * cos(rfi+fiShift)));
                points.push_back(new Point(radius * sin(rtheta) * sin(rfi), radius * cos(rtheta), radius * sin(rtheta) * cos(rfi)));
                points.push_back(new Point(radius * sin(rtheta+thetaShift) * sin(rfi), radius * cos(rtheta+thetaShift), radius * sin(rtheta+thetaShift) * cos(rfi)));
            }

            else if(theta == stacks - 1){
                points.push_back(new Point(radius * sin(rtheta) * sin(rfi+fiShift), radius * cos(rtheta), radius * sin(rtheta) * cos(rfi+fiShift)));
                points.push_back(new Point(radius * sin(rtheta) * sin(rfi), radius * cos(rtheta), radius * sin(rtheta) * cos(rfi)));
                points.push_back(new Point(radius * sin(rtheta+thetaShift) * sin(rfi+fiShift), radius * cos(rtheta+thetaShift), radius * sin(rtheta+thetaShift) * cos(rfi+fiShift)));
            }

            //Rectangles within the sphere
            else {
                points.push_back(new Point(radius * sin(rtheta+thetaShift) * sin(rfi+fiShift), radius * cos(rtheta+thetaShift), radius * sin(rtheta+thetaShift) * cos(rfi+fiShift)));
                points.push_back(new Point(radius * sin(rtheta) * sin(rfi), radius * cos(rtheta), radius * sin(rtheta) * cos(rfi)));
                points.push_back(new Point(radius * sin(rtheta+thetaShift) * sin(rfi), radius * cos(rtheta+thetaShift), radius * sin(rtheta+thetaShift) * cos(rfi)));

                points.push_back(new Point(radius * sin(rtheta) * sin(rfi+fiShift), radius * cos(rtheta), radius * sin(rtheta) * cos(rfi+fiShift)));
                points.push_back(new Point(radius * sin(rtheta) * sin(rfi), radius * cos(rtheta), radius * sin(rtheta) * cos(rfi)));
                points.push_back(new Point(radius * sin(rtheta+thetaShift) * sin(rfi+fiShift), radius * cos(rtheta+thetaShift), radius * sin(rtheta+thetaShift) * cos(rfi+fiShift)));
            }

        }
    }
}

/**
 * @brief Creates vertice points for a cone with a certain radius, slices and stacks
 * Usage: generator cone 1 1 20 20 cone.3d
 * @param  r        Radius of the base
 * @param  height   Height of the cone
 * @param  slices   Number of slices
 * @param  stacks   Number of stacks
 */
void Figure::createCone(double r, double height, int slices, int stacks){

    float alpha = (2 * M_PI)/slices;
    float h = sqrt(pow(r,2) + pow(h,2))/stacks;
    float beta = r/slices;

    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j<slices; j++) {

            if (!i) {
                // Base
                points.push_back(new Point(0.0f,0.0f,0.0f));
                points.push_back(new Point(r * sin(alpha * (j+1)), 0, r * cos(alpha * (j + 1))));
                points.push_back(new Point(r * sin(alpha * j), 0, r * cos(alpha * j)));
            }

            if (i == stacks-1) {
                // Top
                points.push_back(new Point((r - beta * i) * sin(alpha * j), i * h, (r - beta * i) * cos(alpha * j)));
                points.push_back(new Point((r - beta * i) * sin(alpha * (j + 1)), i * h, (r - beta * i) * cos(alpha * (j + 1))));
                points.push_back(new Point(0, (i + 1) * h, 0));

            } else {
                // Side
                points.push_back(new Point((r - beta * i) * sin(alpha * j), i * h, (r - beta * i) * cos(alpha * j)));
                points.push_back(new Point((r - beta * (i + 1)) * sin(alpha * (j + 1)), (i + 1) * h, (r - beta * (i + 1)) * cos(alpha * (j + 1))));
                points.push_back(new Point((r - beta * (i + 1)) * sin(alpha * j), (i + 1) * h, (r - beta * (i + 1)) * cos(alpha * j)));

                points.push_back(new Point((r - beta * i) * sin(alpha * j), i * h, (r - beta * i) * cos(alpha * j)));
                points.push_back(new Point((r - beta * i) * sin(alpha * (j + 1)), i * h, (r - beta * i) * cos(alpha * (j + 1))));
                points.push_back(new Point((r - beta * (i + 1)) * sin(alpha * (j + 1)), (i + 1) * h, (r - beta * (i + 1)) * cos(alpha * (j + 1))));
            }
        }
    }
}

/**
 * @brief Creates vertice points for a cylinder with a certain radius, slices and stacks
 * Usage: generator cylinder 1 1 20 20 cylinder.3d
 * @param  r        Radius of the base
 * @param  height   Height of the cylinder
 * @param  slices   Number of slices
 * @param  stacks   Number of stacks
 */
void Figure::createCylinder(double r, double height, int slices, int stacks){

    float theta = (2 * M_PI)/slices;
    float heightShift = height/stacks;

    for(int i = 0; i < slices; i++){
        for(int j = 0; j < stacks; j++){
            //Lateral surface
            points.push_back(new Point(r * sin(theta * i),heightShift * j,r * cos(theta * i)));
            points.push_back(new Point(r * sin(theta * (i+1)),heightShift * j,r * cos(theta * (i+1))));
            points.push_back(new Point(r * sin(theta * i),heightShift * (j+1),r * cos(theta * i)));

            points.push_back(new Point(r * sin(theta * (i+1)),heightShift * j,r * cos(theta * (i+1))));
            points.push_back(new Point(r * sin(theta * (i+1)),heightShift * (j+1),r * cos(theta * (i+1))));
            points.push_back(new Point(r * sin(theta * i),heightShift * (j+1),r * cos(theta * i)));

            //Lower base
            if(!j){
                points.push_back(new Point(r * sin(theta * (i + 1)), heightShift * j, r * cos(theta * (i + 1))));
                points.push_back(new Point(r * sin(theta * i), heightShift * j, r * cos(theta * i)));
                points.push_back(new Point(0.0f, 0.0f, 0.0f));
            }

            //Upper base
            if(j == stacks -1) {
                points.push_back(new Point(r * sin(theta * i), heightShift * (j + 1), r * cos(theta * i)));
                points.push_back(new Point(r * sin(theta * (i + 1)), heightShift * (j + 1), r * cos(theta * (i + 1))));
                points.push_back(new Point(0.0f, height, 0.0f));
            }
        }
    }
}

/**
 * @brief Creates vertice points for a cylinder with a certain radius, slices and stacks
 * Usage: generator circumference 1 20 circumference.3d
 * @param  r         Radius of the cylinder
 * @param  divisions Number of divisions
 */
//TODO build circumference


void Figure::createCircumference(double r, double divisions){
/*
    float theta = (2 * M_PI)/divisions;

    for(int i = 0; i < divisions; i++){
            //Lateral surface
            points.push_back(new Point(r * sin(theta * i),heightShift * j,r * cos(theta * i)));
            points.push_back(new Point(r * sin(theta * (i+1)),heightShift * j,r * cos(theta * (i+1))));
            points.push_back(new Point(r * sin(theta * i),heightShift * (j+1),r * cos(theta * i)));

            points.push_back(new Point(r * sin(theta * (i+1)),heightShift * j,r * cos(theta * (i+1))));
            points.push_back(new Point(r * sin(theta * (i+1)),heightShift * (j+1),r * cos(theta * (i+1))));
            points.push_back(new Point(r * sin(theta * i),heightShift * (j+1),r * cos(theta * i)));

            //Lower base
            if(!j){
                points.push_back(new Point(r * sin(theta * (i + 1)), heightShift * j, r * cos(theta * (i + 1))));
                points.push_back(new Point(r * sin(theta * i), heightShift * j, r * cos(theta * i)));
                points.push_back(new Point(0.0f, 0.0f, 0.0f));
            }

            //Upper base
            if(j == stacks -1) {
                points.push_back(new Point(r * sin(theta * i), heightShift * (j + 1), r * cos(theta * i)));
                points.push_back(new Point(r * sin(theta * (i + 1)), heightShift * (j + 1), r * cos(theta * (i + 1))));
                points.push_back(new Point(0.0f, height, 0.0f));
            }
        }
    }
    */
}
