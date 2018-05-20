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

    npoints = 6;

    points.push_back(new Point(height,0,height));
    normals.push_back(new Point(0,1,0));
    textures.push_back(new Point(1,1,0));

    points.push_back(new Point(-height,0,-height));
    normals.push_back(new Point(0,1,0));
    textures.push_back(new Point(1,0,0));

    points.push_back(new Point(-height,0,height));
    normals.push_back(new Point(0,1,0));
    textures.push_back(new Point(0,1,0));


    points.push_back(new Point(-height,0,-height));
    normals.push_back(new Point(0,1,0));
    textures.push_back(new Point(0,0,0));

    points.push_back(new Point(height,0,height));
    normals.push_back(new Point(0,1,0));
    textures.push_back(new Point(1,1,0));

    points.push_back(new Point(height,0,-height));
    normals.push_back(new Point(0,1,0));
    textures.push_back(new Point(1,0,0));

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
            points.push_back(new Point(-realX + shiftX * i, -realY, -realZ + shiftZ * j));
            textures.push_back(new Point(startingBase->X() - baseTopUShift * i,startingBase->Y() - baseTopVShift * j,0));
            normals.push_back(new Point(0,-1,0));
            points.push_back(new Point(-realX + shiftX * (i+1), -realY, -realZ + shiftZ * (j+1)));
            textures.push_back(new Point(startingBase->X() - baseTopUShift * (i+1),startingBase->Y() - baseTopVShift * (j+1),0));
            normals.push_back(new Point(0,-1,0));
            points.push_back(new Point(-realX + shiftX * i, -realY, -realZ + shiftZ * (j+1)));
            textures.push_back(new Point(startingBase->X() - baseTopUShift * i,startingBase->Y() - baseTopVShift * (j+1),0));
            normals.push_back(new Point(0,-1,0));

            points.push_back(new Point(-realX + shiftX * i, -realY, -realZ + shiftZ * j));
            textures.push_back(new Point(startingBase->X() - baseTopUShift * i,startingBase->Y() - baseTopVShift * j,0));
            normals.push_back(new Point(0,-1,0));
            points.push_back(new Point(-realX + shiftX * (i+1), -realY, -realZ + shiftZ * j));
            textures.push_back(new Point(startingBase->X() - baseTopUShift * (i+1),startingBase->Y() - baseTopVShift * j,0));
            normals.push_back(new Point(0,-1,0));
            points.push_back(new Point(-realX + shiftX * (i+1), -realY, -realZ + shiftZ * (j+1)));
            textures.push_back(new Point(startingBase->X() - baseTopUShift * (i+1),startingBase->Y() - baseTopVShift * (j+1),0));
            normals.push_back(new Point(0,-1,0));

            //Top
            points.push_back(new Point(-realX + shiftX * i, realY, -realZ + shiftZ * j));
            textures.push_back(new Point(startingTop->X() + baseTopUShift * i,startingTop->Y() - baseTopVShift * j,0));
            normals.push_back(new Point(0,1,0));
            points.push_back(new Point(-realX + shiftX * i, realY, -realZ + shiftZ * (j+1)));
            textures.push_back(new Point(startingTop->X() + baseTopUShift * i,startingTop->Y() - baseTopVShift * (j+1),0));
            normals.push_back(new Point(0,1,0));
            points.push_back(new Point(-realX + shiftX * (i+1), realY, -realZ + shiftZ * (j+1)));
            textures.push_back(new Point(startingTop->X() + baseTopUShift * (i+1),startingTop->Y() - baseTopVShift * (j+1),0));
            normals.push_back(new Point(0,1,0));

            points.push_back(new Point(-realX + shiftX * i, realY, -realZ + shiftZ * j));
            textures.push_back(new Point(startingTop->X() + baseTopUShift * i,startingTop->Y() - baseTopVShift * j,0));
            normals.push_back(new Point(0,1,0));;
            points.push_back(new Point(-realX + shiftX * (i+1), realY, -realZ + shiftZ * (j+1)));
            textures.push_back(new Point(startingTop->X() + baseTopUShift * (i+1),startingTop->Y() - baseTopVShift * (j+1),0));
            normals.push_back(new Point(0,1,0));
            points.push_back(new Point(-realX + shiftX * (i+1), realY, -realZ + shiftZ * j));
            textures.push_back(new Point(startingTop->X() + baseTopUShift * (i+1),startingTop->Y() - baseTopVShift * j,0));
            normals.push_back(new Point(0,1,0));

            //Front face
            points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * j, realZ));
            textures.push_back(new Point(startingFront->X() - frontBackUShift * i,startingFront->Y() - frontBackVShift * j,0));
            normals.push_back(new Point(0,0,1));
            points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * j, realZ));
            textures.push_back(new Point(startingFront->X() - frontBackUShift * (i+1),startingFront->Y() - frontBackVShift * j,0));
            normals.push_back(new Point(0,0,1));
            points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * (j+1), realZ));
            textures.push_back(new Point(startingFront->X() - frontBackUShift * i,startingFront->Y() - frontBackVShift * (j+1),0));
            normals.push_back(new Point(0,0,1));

            points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * j, realZ));
            textures.push_back(new Point(startingFront->X() - frontBackUShift * (i+1),startingFront->Y() - frontBackVShift * j,0));
            normals.push_back(new Point(0,0,1));
            points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * (j+1), realZ));
            textures.push_back(new Point(startingFront->X() - frontBackUShift * (i+1),startingFront->Y() - frontBackVShift * (j+1),0));
            normals.push_back(new Point(0,0,1));
            points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * (j+1), realZ));
            textures.push_back(new Point(startingFront->X() - frontBackUShift * i,startingFront->Y() - frontBackVShift * (j+1),0));
            normals.push_back(new Point(0,0,1));

            //Back Face
            points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * j, -realZ));
            textures.push_back(new Point(startingBack->X() + frontBackUShift * i,startingBack->Y() - frontBackVShift * j,0));
            normals.push_back(new Point(0,0,-1));
            points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * (j+1), -realZ));
            textures.push_back(new Point(startingBack->X() + frontBackUShift * i,startingBack->Y() - frontBackVShift * (j+1),0));
            normals.push_back(new Point(0,0,-1));
            points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * j, -realZ));
            textures.push_back(new Point(startingBack->X() + frontBackUShift * (i+1),startingBack->Y() - frontBackVShift * j,0));
            normals.push_back(new Point(0,0,-1));

            points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * j, -realZ));
            textures.push_back(new Point(startingBack->X() + frontBackUShift * (i+1),startingBack->Y() - frontBackVShift * j,0));
            normals.push_back(new Point(0,0,-1));
            points.push_back(new Point(-realX + shiftX * i, -realY + shiftY * (j+1), -realZ));
            textures.push_back(new Point(startingBack->X() + frontBackUShift * i,startingBack->Y() - frontBackVShift * (j+1),0));
            normals.push_back(new Point(0,0,-1));
            points.push_back(new Point(-realX + shiftX * (i+1), -realY + shiftY * (j+1), -realZ));
            textures.push_back(new Point(startingBack->X() + frontBackUShift * (i+1),startingBack->Y() - frontBackVShift * (j+1),0));
            normals.push_back(new Point(0,0,-1));

            //Left Face
            points.push_back(new Point(-realX, -realY + shiftY * i, -realZ + shiftZ * j));
            textures.push_back(new Point(startingLeft->X() - leftRightUShift * i,startingLeft->Y() + leftRightVShift * j,0));
            normals.push_back(new Point(-1,0,0));
            points.push_back(new Point(-realX, -realY + shiftY * i, -realZ + shiftZ * (j+1)));
            textures.push_back(new Point(startingLeft->X() - leftRightUShift * i,startingLeft->Y() + leftRightVShift * (j+1),0));
            normals.push_back(new Point(-1,0,0));
            points.push_back(new Point(-realX, -realY + shiftY * (i+1), -realZ + shiftZ * j));
            textures.push_back(new Point(startingLeft->X() - leftRightUShift * (i+1),startingLeft->Y() + leftRightVShift * j,0));
            normals.push_back(new Point(-1,0,0));

            points.push_back(new Point(-realX, -realY + shiftY * (i+1), -realZ + shiftZ * j));
            textures.push_back(new Point(startingLeft->X() - leftRightUShift * (i+1),startingLeft->Y() + leftRightVShift * j,0));
            normals.push_back(new Point(-1,0,0));;
            points.push_back(new Point(-realX, -realY + shiftY * i, -realZ + shiftZ * (j+1)));
            textures.push_back(new Point(startingLeft->X() - leftRightUShift * i,startingLeft->Y() + leftRightVShift * (j+1),0));
            normals.push_back(new Point(-1,0,0));
            points.push_back(new Point(-realX, -realY + shiftY * (i+1), -realZ + shiftZ * (j+1)));
            textures.push_back(new Point(startingLeft->X() - leftRightUShift * (i+1),startingLeft->Y() + leftRightVShift * (j+1),0));
            normals.push_back(new Point(-1,0,0));

            //Right Face
            points.push_back(new Point(realX, -realY + shiftY * i, -realZ + shiftZ * j));
            textures.push_back(new Point(startingRight->X() - leftRightUShift * i,startingRight->Y() - leftRightVShift * j,0));
            normals.push_back(new Point(1,0,0));
            points.push_back(new Point(realX, -realY + shiftY * (i+1), -realZ + shiftZ * j));
            textures.push_back(new Point(startingRight->X() - leftRightUShift * (i+1),startingRight->Y() - leftRightVShift * j,0));
            normals.push_back(new Point(1,0,0));
            points.push_back(new Point(realX, -realY + shiftY * i, -realZ + shiftZ * (j+1)));
            textures.push_back(new Point(startingRight->X() - leftRightUShift * i,startingRight->Y() - leftRightVShift * (j+1),0));
            normals.push_back(new Point(1,0,0));

            points.push_back(new Point(realX, -realY + shiftY * (i+1), -realZ + shiftZ * j));
            textures.push_back(new Point(startingRight->X() - leftRightUShift * (i+1),startingRight->Y() - leftRightVShift * j,0));
            normals.push_back(new Point(1,0,0));
            points.push_back(new Point(realX, -realY + shiftY * (i+1), -realZ + shiftZ * (j+1)));
            textures.push_back(new Point(startingRight->X() - leftRightUShift * (i+1),startingRight->Y() - leftRightVShift * (j+1),0));
            normals.push_back(new Point(1,0,0));
            points.push_back(new Point(realX, -realY + shiftY * i, -realZ + shiftZ * (j+1)));
            textures.push_back(new Point(startingRight->X() - leftRightUShift * i,startingRight->Y() - leftRightVShift * (j+1),0));
            normals.push_back(new Point(1,0,0));
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

    float uShift = (float)1/slices;
    float vShift = (float)1/stacks;

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
    float h = sqrt(pow(r,2) + pow(height,2))/stacks;
    float beta = r/slices;

    float vShift = (float)1/stacks;
    float uShift = (float)1/slices;

    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j<slices; j++) {

            if (!i) {
                
                // Base
                points.push_back(new Point(0.0f,0.0f,0.0f));
                normals.push_back(new Point(0.0f,-1.0f,0.0f));
                textures.push_back(new Point((j+0.5)* uShift,i*vShift,0));

                points.push_back(new Point(r * sin(alpha * (j+1)), 0, r * cos(alpha * (j + 1))));
                normals.push_back(new Point(0.0f,-1.0f,0.0f));
                textures.push_back(new Point(j* uShift,(i+1)*vShift,0));

                points.push_back(new Point(r * sin(alpha * j), 0, r * cos(alpha * j)));
                normals.push_back(new Point(0.0f,-1.0f,0.0f));
                textures.push_back(new Point((j+1)* uShift,(i+1)*vShift,0));
            }

            if (i == stacks-1) {
                
                // Top
                points.push_back(new Point((r - beta * i) * sin(alpha * j), i * h, (r - beta * i) * cos(alpha * j)));
                normals.push_back(new Point(0.0f,1.0f,0.0f));
                textures.push_back(new Point((j+1)* uShift,(i+1)*vShift,0));

                points.push_back(new Point((r - beta * i) * sin(alpha * (j + 1)), i * h, (r - beta * i) * cos(alpha * (j + 1))));
                normals.push_back(new Point(0.0f,1.0f,0.0f));
                textures.push_back(new Point(j* uShift,(i+1)*vShift,0));

                points.push_back(new Point(0, (i + 1) * h, 0));
                normals.push_back(new Point(0.0f,1.0f,0.0f));
                textures.push_back(new Point((j+0.5)* uShift,i*vShift,0));

            } else {
                
                // Side
                points.push_back(new Point((r - beta * i) * sin(alpha * j), i * h, (r - beta * i) * cos(alpha * j)));
                normals.push_back(new Point(sin(alpha * j), h, cos(alpha * j)));
                textures.push_back(new Point((j+1)* uShift,i*vShift,0));

                points.push_back(new Point((r - beta * (i + 1)) * sin(alpha * (j + 1)), (i + 1) * h, (r - beta * (i + 1)) * cos(alpha * (j + 1))));
                normals.push_back(new Point( sin(alpha * (j + 1)), h, cos(alpha * (j + 1))));
                textures.push_back(new Point(j* uShift,(i+1)*vShift,0));

                points.push_back(new Point((r - beta * (i + 1)) * sin(alpha * j), (i + 1) * h, (r - beta * (i + 1)) * cos(alpha * j)));
                normals.push_back(new Point(sin(alpha * j), h, cos(alpha * j)));
                textures.push_back(new Point((j+1)* uShift,(i+1)*vShift,0));


                points.push_back(new Point((r - beta * i) * sin(alpha * j), i * h, (r - beta * i) * cos(alpha * j)));
                normals.push_back(new Point(sin(alpha * j), h, cos(alpha * j)));
                textures.push_back(new Point((j+1)* uShift,i*vShift,0));

                points.push_back(new Point((r - beta * i) * sin(alpha * (j + 1)), i * h, (r - beta * i) * cos(alpha * (j + 1))));
                normals.push_back(new Point( sin(alpha * (j + 1)), h, cos(alpha * (j + 1))));
                textures.push_back(new Point(j* uShift,i*vShift,0));

                points.push_back(new Point((r - beta * (i + 1)) * sin(alpha * (j + 1)), (i + 1) * h, (r - beta * (i + 1)) * cos(alpha * (j + 1))));
                normals.push_back(new Point( sin(alpha * (j + 1)), h, cos(alpha * (j + 1))));
                textures.push_back(new Point(j* uShift,(i+1)*vShift,0));
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
    
    float vShift = (float)0.625/stacks;
    float uShift = (float)1/slices;

    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < stacks; j++) {
            npoints += 6;

            //Lateral surface
            points.push_back(new Point(r * sin(theta * i), heightShift * j, r * cos(theta * i)));
            normals.push_back(new Point( sin(theta * i), 0, cos(theta * i)));
            textures.push_back(new Point((i+1)*uShift, float(j) * vShift + 0.375f, 0));

            points.push_back(new Point(r * sin(theta * (i + 1)), heightShift * j, r * cos(theta * (i + 1))));
            normals.push_back(new Point( sin(theta * (i+1)), 0, cos(theta * i)));
            textures.push_back(new Point((i+1)*uShift, float(j) * vShift + 0.375f, 0));

            points.push_back(new Point(r * sin(theta * i), heightShift * (j + 1), r * cos(theta * i)));
            normals.push_back(new Point( sin(theta * i), 0, cos(theta * i)));
            textures.push_back(new Point(i*uShift, float(j+1) * vShift + 0.375f, 0));


            points.push_back(new Point(r * sin(theta * (i + 1)), heightShift * j, r * cos(theta * (i + 1))));
            normals.push_back(new Point( sin(theta * (i+1)), 0, cos(theta * (i+1))));
            textures.push_back(new Point((i+1)*uShift, float(j) * vShift + 0.375f, 0));

            points.push_back(new Point(r * sin(theta * (i + 1)), heightShift * (j + 1), r * cos(theta * (i + 1))));
            normals.push_back(new Point( sin(theta * (i+1)), 0, cos(theta * (i+1))));
            textures.push_back(new Point((i+1)*uShift, float(j+1) * vShift + 0.375f, 0));

            points.push_back(new Point(r * sin(theta * i), heightShift * (j + 1), r * cos(theta * i)));
            normals.push_back(new Point( sin(theta * i), 0, cos(theta * i)));
            textures.push_back(new Point(i*uShift, float(j+1) * vShift + 0.375f, 0));

            //Lower base
            if (!j) {
                npoints += 3;
                points.push_back(new Point(r * sin(theta * (i + 1)), heightShift * j, r * cos(theta * (i + 1))));
                normals.push_back(new Point(0.0f,-1.0f,0.0f));
                textures.push_back(new Point(0.8125 + 0.1875 * sin(theta * (i + 1)),0.1875 + 0.1875 * cos(theta * (i + 1)),0));

                points.push_back(new Point(r * sin(theta * i), heightShift * j, r * cos(theta * i)));
                normals.push_back(new Point(0.0f,-1.0f,0.0f));
                textures.push_back(new Point(0.8125 + 0.1875 * sin(theta * i),0.1875 + 0.1875 * cos(theta * i),0));

                points.push_back(new Point(0.0f, 0.0f, 0.0f));
                normals.push_back(new Point(0.0f,-1.0f,0.0f));
                textures.push_back(new Point(0.8125,0.1875,0));
            }

            //Upper base
            if (j == stacks - 1) {
                npoints += 3;
                points.push_back(new Point(r * sin(theta * i), heightShift * (j + 1), r * cos(theta * i)));
                normals.push_back(new Point(0.0f,1.0f,0.0f));
                textures.push_back(new Point(0.4375 + 0.1875 * sin(theta * i),0.1875 + 0.1875 * cos(theta * i),0));

                points.push_back(new Point(r * sin(theta * (i + 1)), heightShift * (j + 1), r * cos(theta * (i + 1))));
                normals.push_back(new Point(0.0f,1.0f,0.0f));
                textures.push_back(new Point(0.4375 + 0.1875 * sin(theta * (i + 1)),0.1875 + 0.1875 * cos(theta * (i + 1)),0));
                
                points.push_back(new Point(0.0f, height, 0.0f));
                normals.push_back(new Point(0.0f,1.0f,0.0f));
                textures.push_back(new Point(0.4375, 0.1875, 0));
            }
        }
    }
}
