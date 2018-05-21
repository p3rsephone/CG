#include "headers/Point.h"

/**
 * @brief Empty constructor for Point
 */
Point::Point(): x(0), y(0), z(0){}

/**
 * @brief Constructor for Point
 * @param x Value of X
 * @param y Value of Y
 * @param z Value of Z
 */
Point::Point(float x, float y, float z) : x(x), y(y), z(z){}

Point::Point(float x, float y) : x(x), y(y){}
/**
 * @brief Transforms Point into String
 * @return String
 */
std::string Point::toString() {
    std::ostringstream sstream;
    sstream << x << ' ' << y << ' ' << z << '\n';
    return sstream.str();
}

Point* Point::normalizeSphere(float radius){
    Point* p = new Point(this->x/radius,this->y/radius,this->z/radius);

    return p;
}

Point* Point::normalizeInverseSphere(float radius){
    Point* p = new Point(-this->x/radius,-this->y/radius,-this->z/radius);

    return p;
}

Point * Point::normalizeBezier(){
    float l = sqrt(powf(x,2) + powf(y,2) + powf(z,2));
    float px,py,pz;
    if(l!=0) {
        px = x/l;
        py = y/l;
        pz = z/l;
    } else {
        px = 0;
        py = 0;
        pz = 0;
    }
    return new Point(px,py,pz);
}
