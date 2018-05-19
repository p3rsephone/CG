#include "headers/Figure.h"

Figure::Figure(){
}

Figure::Figure(vector<Point*> v,vector<Point*> t,vector<Point*> n) : points(v), textures(t), normals(n) {};
/**
 * @brief Creates vertice points for a square in the XZ plane
 * Usage: generator plane 2 plane.3d
 * @param  size Size of the side of the square
 */

void Figure::createPlane(float size){
    float height = size/2;

    //npoints = 4;

    npoints = 6;

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
void Figure::createBox(float x, float y, float z, int d){

    //npoints = 8+6*(d^2)+12*d;

    Point* p = NULL;

    //Basically centers the box in the origin of the referential
    float realX = x/2;
    float realY = y/2;
    float realZ = z/2;

    //How much space is there between divisions
    float shiftX = x/d;
    float shiftY = y/d;
    float shiftZ = z/d;

    //Calculate the box's deconstructed width and height
    float boxHeight = y + 2*z;
    float boxWidth = 2*x + 2*z;

    //Get the ratio between each box's part height and width and the image's height/width
    float baseTopWidth = x/boxWidth;
    float baseTopHeight = y/boxHeight;
    float leftRightWidth = baseTopWidth;
    float leftRightHeight = z/boxHeight;
    float frontBackWidth = z/boxWidth;
    float frontBackHeight = baseTopHeight;

    //Get the starting point for each part of the box's iteration
    Point* startingBase = new Point(baseTopWidth*2+leftRightWidth,leftRightHeight+baseTopHeight,0);
    Point* startingTop = new Point(0,leftRightHeight+baseTopHeight,0);
    Point* startingFront = new Point(baseTopWidth+frontBackWidth,leftRightHeight+baseTopHeight,0);
    Point* startingBack = new Point(baseTopWidth*2+leftRightWidth,leftRightHeight+baseTopHeight,0);
    Point* startingLeft = new Point(baseTopWidth*2+leftRightWidth,leftRightHeight+baseTopHeight,0);
    Point* startingRight = new Point(baseTopWidth*2+leftRightWidth,leftRightHeight,0);

    float baseTopUShift = baseTopWidth/d;
    float baseTopVShift = baseTopHeight/d;
    float leftRightUShift = leftRightWidth/d;
    float leftRightVShift = leftRightHeight/d;
    float frontBackUShift = frontBackWidth/d;
    float frontBackVShift = frontBackHeight/d;

    for(int i = 0; i < d ; i++){
        for(int j = 0; j < d ; j++){

            npoints += 36;

            //Base
            p = new Point(-realX + shiftX * i, -realY, -realZ + shiftZ * j);
            points.push_back(p);
            textures.push_back(new Point(startingBase->X() - baseTopUShift * i,startingBase->Y() - baseTopVShift * j,0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX + shiftX * (i+1), -realY, -realZ + shiftZ * (j+1));
            points.push_back(p);
            textures.push_back(new Point(startingBase->X() - baseTopUShift * (i+1),startingBase->Y() - baseTopVShift * (j+1),0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX + shiftX * i, -realY, -realZ + shiftZ * (j+1));
            points.push_back(p);
            textures.push_back(new Point(startingBase->X() - baseTopUShift * i,startingBase->Y() - baseTopVShift * (j+1),0));
            normals.push_back(p->normalizeBox());

            p = new Point(-realX + shiftX * i, -realY, -realZ + shiftZ * j);
            points.push_back(p);
            textures.push_back(new Point(startingBase->X() - baseTopUShift * i,startingBase->Y() - baseTopVShift * j,0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX + shiftX * (i+1), -realY, -realZ + shiftZ * j);
            points.push_back(p);
            textures.push_back(new Point(startingBase->X() - baseTopUShift * (i+1),startingBase->Y() - baseTopVShift * j,0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX + shiftX * (i+1), -realY, -realZ + shiftZ * (j+1));
            points.push_back(p);
            textures.push_back(new Point(startingBase->X() - baseTopUShift * (i+1),startingBase->Y() - baseTopVShift * (j+1),0));
            normals.push_back(p->normalizeBox());

            //Top
            p = new Point(-realX + shiftX * i, realY, -realZ + shiftZ * j);
            points.push_back(p);
            textures.push_back(new Point(startingTop->X() + baseTopUShift * i,startingTop->Y() - baseTopVShift * j,0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX + shiftX * i, realY, -realZ + shiftZ * (j+1));
            points.push_back(p);
            textures.push_back(new Point(startingTop->X() + baseTopUShift * i,startingTop->Y() - baseTopVShift * (j+1),0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX + shiftX * (i+1), realY, -realZ + shiftZ * (j+1));
            points.push_back(p);
            textures.push_back(new Point(startingTop->X() + baseTopUShift * (i+1),startingTop->Y() - baseTopVShift * (j+1),0));
            normals.push_back(p->normalizeBox());

            p = new Point(-realX + shiftX * i, realY, -realZ + shiftZ * j);
            points.push_back(p);
            textures.push_back(new Point(startingTop->X() + baseTopUShift * i,startingTop->Y() - baseTopVShift * j,0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX + shiftX * (i+1), realY, -realZ + shiftZ * (j+1));
            points.push_back(p);
            textures.push_back(new Point(startingTop->X() + baseTopUShift * (i+1),startingTop->Y() - baseTopVShift * (j+1),0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX + shiftX * (i+1), realY, -realZ + shiftZ * j);
            points.push_back(p);
            textures.push_back(new Point(startingTop->X() + baseTopUShift * (i+1),startingTop->Y() - baseTopVShift * j,0));
            normals.push_back(p->normalizeBox());

            //Front face
            p = new Point(-realX + shiftX * i, -realY + shiftY * j, realZ);
            points.push_back(p);
            textures.push_back(new Point(startingFront->X() - frontBackUShift * i,startingFront->Y() - frontBackVShift * j,0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX + shiftX * (i+1), -realY + shiftY * j, realZ);
            points.push_back(p);
            textures.push_back(new Point(startingFront->X() - frontBackUShift * (i+1),startingFront->Y() - frontBackVShift * j,0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX + shiftX * i, -realY + shiftY * (j+1), realZ);
            points.push_back(p);
            textures.push_back(new Point(startingFront->X() - frontBackUShift * i,startingFront->Y() - frontBackVShift * (j+1),0));
            normals.push_back(p->normalizeBox());

            p = new Point(-realX + shiftX * (i+1), -realY + shiftY * j, realZ);
            points.push_back(p);
            textures.push_back(new Point(startingFront->X() - frontBackUShift * (i+1),startingFront->Y() - frontBackVShift * j,0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX + shiftX * (i+1), -realY + shiftY * (j+1), realZ);
            points.push_back(p);
            textures.push_back(new Point(startingFront->X() - frontBackUShift * (i+1),startingFront->Y() - frontBackVShift * (j+1),0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX + shiftX * i, -realY + shiftY * (j+1), realZ);
            points.push_back(p);
            textures.push_back(new Point(startingFront->X() - frontBackUShift * i,startingFront->Y() - frontBackVShift * (j+1),0));
            normals.push_back(p->normalizeBox());

            //Back Face
            p = new Point(-realX + shiftX * i, -realY + shiftY * j, -realZ);
            points.push_back(p);
            textures.push_back(new Point(startingBack->X() + frontBackUShift * i,startingBack->Y() - frontBackVShift * j,0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX + shiftX * i, -realY + shiftY * (j+1), -realZ);
            points.push_back(p);
            textures.push_back(new Point(startingBack->X() + frontBackUShift * i,startingBack->Y() - frontBackVShift * (j+1),0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX + shiftX * (i+1), -realY + shiftY * j, -realZ);
            points.push_back(p);
            textures.push_back(new Point(startingBack->X() + frontBackUShift * (i+1),startingBack->Y() - frontBackVShift * j,0));
            normals.push_back(p->normalizeBox());

            p = new Point(-realX + shiftX * (i+1), -realY + shiftY * j, -realZ);
            points.push_back(p);
            textures.push_back(new Point(startingBack->X() + frontBackUShift * (i+1),startingBack->Y() - frontBackVShift * j,0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX + shiftX * i, -realY + shiftY * (j+1), -realZ);
            points.push_back(p);
            textures.push_back(new Point(startingBack->X() + frontBackUShift * i,startingBack->Y() - frontBackVShift * (j+1),0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX + shiftX * (i+1), -realY + shiftY * (j+1), -realZ);
            points.push_back(p);
            textures.push_back(new Point(startingBack->X() + frontBackUShift * (i+1),startingBack->Y() - frontBackVShift * (j+1),0));
            normals.push_back(p->normalizeBox());

            //Left Face
            p = new Point(-realX, -realY + shiftY * i, -realZ + shiftZ * j);
            points.push_back(p);
            textures.push_back(new Point(startingLeft->X() - leftRightUShift * i,startingLeft->Y() + leftRightVShift * j,0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX, -realY + shiftY * i, -realZ + shiftZ * (j+1));
            points.push_back(p);
            textures.push_back(new Point(startingLeft->X() - leftRightUShift * i,startingLeft->Y() + leftRightVShift * (j+1),0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX, -realY + shiftY * (i+1), -realZ + shiftZ * j);
            points.push_back(p);
            textures.push_back(new Point(startingLeft->X() - leftRightUShift * (i+1),startingLeft->Y() + leftRightVShift * j,0));
            normals.push_back(p->normalizeBox());

            p = new Point(-realX, -realY + shiftY * (i+1), -realZ + shiftZ * j);
            points.push_back(p);
            textures.push_back(new Point(startingLeft->X() - leftRightUShift * (i+1),startingLeft->Y() + leftRightVShift * j,0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX, -realY + shiftY * i, -realZ + shiftZ * (j+1));
            points.push_back(p);
            textures.push_back(new Point(startingLeft->X() - leftRightUShift * i,startingLeft->Y() + leftRightVShift * (j+1),0));
            normals.push_back(p->normalizeBox());
            p = new Point(-realX, -realY + shiftY * (i+1), -realZ + shiftZ * (j+1));
            points.push_back(p);
            textures.push_back(new Point(startingLeft->X() - leftRightUShift * (i+1),startingLeft->Y() + leftRightVShift * (j+1),0));
            normals.push_back(p->normalizeBox());

            //Right Face
            p = new Point(realX, -realY + shiftY * i, -realZ + shiftZ * j);
            points.push_back(p);
            textures.push_back(new Point(startingRight->X() - leftRightUShift * i,startingRight->Y() - leftRightVShift * j,0));
            normals.push_back(p->normalizeBox());
            p = new Point(realX, -realY + shiftY * (i+1), -realZ + shiftZ * j);
            points.push_back(p);
            textures.push_back(new Point(startingRight->X() - leftRightUShift * (i+1),startingRight->Y() - leftRightVShift * j,0));
            normals.push_back(p->normalizeBox());
            p = new Point(realX, -realY + shiftY * i, -realZ + shiftZ * (j+1));
            points.push_back(p);
            textures.push_back(new Point(startingRight->X() - leftRightUShift * i,startingRight->Y() - leftRightVShift * (j+1),0));
            normals.push_back(p->normalizeBox());

            p = new Point(realX, -realY + shiftY * (i+1), -realZ + shiftZ * j);
            points.push_back(p);
            textures.push_back(new Point(startingRight->X() - leftRightUShift * (i+1),startingRight->Y() - leftRightVShift * j,0));
            normals.push_back(p->normalizeBox());
            p = new Point(realX, -realY + shiftY * (i+1), -realZ + shiftZ * (j+1));
            points.push_back(p);
            textures.push_back(new Point(startingRight->X() - leftRightUShift * (i+1),startingRight->Y() - leftRightVShift * (j+1),0));
            normals.push_back(p->normalizeBox());
            p = new Point(realX, -realY + shiftY * i, -realZ + shiftZ * (j+1));
            points.push_back(p);
            textures.push_back(new Point(startingRight->X() - leftRightUShift * i,startingRight->Y() - leftRightVShift * (j+1),0));
            normals.push_back(p->normalizeBox());
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
void Figure::createSphere(float radius, int slices, int stacks){

    //npoints = 2 + slices * stacks;

    Point* p = NULL;

    float fiShift = M_PI*2 / slices;
    float thetaShift = M_PI / stacks;

    float uShift = 1/stacks;
    float vShift = 1/slices;

    //Using spheric coordinates
    //x = radius * sin(theta) * cos(fi);
    //y = radius * sin(theta) * sin(fi);
    //z = radius * cos(theta);
    for(float fi = 0; fi < slices ; fi++){
        for(float theta = 0; theta < stacks ; theta ++){

            float rtheta = theta * thetaShift;
            float rfi = fi * fiShift;

            //Triangular ends of the sphere
            if(theta == 0){
                npoints += 3;

                p = new Point(radius * sin(rtheta+thetaShift) * sin(rfi+fiShift), radius * cos(theta+thetaShift) ,radius * sin(rtheta+thetaShift) * cos(rfi+fiShift));
                points.push_back(p);
                textures.push_back(new Point((fi+1)*uShift,(theta+1)*vShift,0));
                normals.push_back(p->normalizeSphere(radius));

                p = new Point(radius * sin(rtheta) * sin(rfi), radius * cos(rtheta), radius * sin(rtheta) * cos(rfi));
                points.push_back(p);
                textures.push_back(new Point((fi+0.5)*uShift,theta*vShift,0));
                normals.push_back(p->normalizeSphere(radius));

                p = new Point(radius * sin(rtheta+thetaShift) * sin(rfi), radius * cos(rtheta+thetaShift), radius * sin(rtheta+thetaShift) * cos(rfi));
                points.push_back(p);
                textures.push_back(new Point(fi*uShift,(theta+1)*vShift,0));
                normals.push_back(p->normalizeSphere(radius));


            }

            else if(theta == stacks - 1){
                npoints += 3;
                p = new Point(radius * sin(rtheta) * sin(rfi+fiShift), radius * cos(rtheta), radius * sin(rtheta) * cos(rfi+fiShift));
                points.push_back(p);
                textures.push_back(new Point((fi+1)*uShift,theta*vShift,0));
                normals.push_back(p->normalizeSphere(radius));

                p = new Point(radius * sin(rtheta) * sin(rfi), radius * cos(rtheta), radius * sin(rtheta) * cos(rfi));
                points.push_back(p);
                textures.push_back(new Point(fi*uShift,theta*vShift,0));
                normals.push_back(p->normalizeSphere(radius));

                p = new Point(radius * sin(rtheta+thetaShift) * sin(rfi+fiShift), radius * cos(rtheta+thetaShift), radius * sin(rtheta+thetaShift) * cos(rfi+fiShift));
                points.push_back(p);
                textures.push_back(new Point((fi+0.5)*uShift,(theta+1)*vShift,0));
                normals.push_back(p->normalizeSphere(radius));
            }

            //Rectangles within the sphere
            else {
                npoints += 6;

                p = new Point(radius * sin(rtheta+thetaShift) * sin(rfi+fiShift), radius * cos(rtheta+thetaShift), radius * sin(rtheta+thetaShift) * cos(rfi+fiShift));
                points.push_back(p);
                textures.push_back(new Point((fi+1)*uShift,(theta+1)*vShift,0));
                normals.push_back(p->normalizeSphere(radius));

                p = new Point(radius * sin(rtheta) * sin(rfi), radius * cos(rtheta), radius * sin(rtheta) * cos(rfi));
                points.push_back(p);
                textures.push_back(new Point(fi*uShift,theta*vShift,0));
                normals.push_back(p->normalizeSphere(radius));

                p = new Point(radius * sin(rtheta+thetaShift) * sin(rfi), radius * cos(rtheta+thetaShift), radius * sin(rtheta+thetaShift) * cos(rfi));
                points.push_back(p);
                textures.push_back(new Point(fi*uShift,(theta+1)*vShift,0));
                normals.push_back(p->normalizeSphere(radius));

                p = new Point(radius * sin(rtheta) * sin(rfi+fiShift), radius * cos(rtheta), radius * sin(rtheta) * cos(rfi+fiShift));
                points.push_back(p);
                textures.push_back(new Point((fi+1)*uShift,theta*vShift,0));
                normals.push_back(p->normalizeSphere(radius));

                p = new Point(radius * sin(rtheta) * sin(rfi), radius * cos(rtheta), radius * sin(rtheta) * cos(rfi));
                points.push_back(p);
                textures.push_back(new Point(fi*uShift,theta*vShift,0));
                normals.push_back(p->normalizeSphere(radius));

                p = new Point(radius * sin(rtheta+thetaShift) * sin(rfi+fiShift), radius * cos(rtheta+thetaShift), radius * sin(rtheta+thetaShift) * cos(rfi+fiShift));
                points.push_back(p);
                textures.push_back(new Point((fi+1)*uShift,(theta+1)*vShift,0));
                normals.push_back(p->normalizeSphere(radius));

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
void Figure::createCone(float r, float height, int slices, int stacks){

    //npoints = 2 * slices * stacks;

    float alpha = (2 * M_PI)/slices;
    float h = sqrt(pow(r,2) + pow(h,2))/stacks;
    float beta = r/slices;

    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j<slices; j++) {

            if (!i) {
                npoints += 3;
                // Base
                points.push_back(new Point(0.0f,0.0f,0.0f));
                points.push_back(new Point(r * sin(alpha * (j+1)), 0, r * cos(alpha * (j + 1))));
                points.push_back(new Point(r * sin(alpha * j), 0, r * cos(alpha * j)));
            }

            if (i == stacks-1) {
                npoints += 3;
                // Top
                points.push_back(new Point((r - beta * i) * sin(alpha * j), i * h, (r - beta * i) * cos(alpha * j)));
                points.push_back(new Point((r - beta * i) * sin(alpha * (j + 1)), i * h, (r - beta * i) * cos(alpha * (j + 1))));
                points.push_back(new Point(0, (i + 1) * h, 0));

            } else {
                npoints += 6;
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
void Figure::createCylinder(float r, float height, int slices, int stacks) {

    npoints = 2 * slices * stacks;

    float theta = (2 * M_PI) / slices;
    float heightShift = height / stacks;

    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < stacks; j++) {
            npoints += 6;

            //Lateral surface
            points.push_back(new Point(r * sin(theta * i), heightShift * j, r * cos(theta * i)));
            points.push_back(new Point(r * sin(theta * (i + 1)), heightShift * j, r * cos(theta * (i + 1))));
            points.push_back(new Point(r * sin(theta * i), heightShift * (j + 1), r * cos(theta * i)));

            points.push_back(new Point(r * sin(theta * (i + 1)), heightShift * j, r * cos(theta * (i + 1))));
            points.push_back(new Point(r * sin(theta * (i + 1)), heightShift * (j + 1), r * cos(theta * (i + 1))));
            points.push_back(new Point(r * sin(theta * i), heightShift * (j + 1), r * cos(theta * i)));

            //Lower base
            if (!j) {
                npoints += 3;
                points.push_back(new Point(r * sin(theta * (i + 1)), heightShift * j, r * cos(theta * (i + 1))));
                points.push_back(new Point(r * sin(theta * i), heightShift * j, r * cos(theta * i)));
                points.push_back(new Point(0.0f, 0.0f, 0.0f));
            }

            //Upper base
            if (j == stacks - 1) {
                npoints += 3;
                points.push_back(new Point(r * sin(theta * i), heightShift * (j + 1), r * cos(theta * i)));
                points.push_back(new Point(r * sin(theta * (i + 1)), heightShift * (j + 1), r * cos(theta * (i + 1))));
                points.push_back(new Point(0.0f, height, 0.0f));
            }
        }
    }
}
