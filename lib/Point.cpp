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
    Point* p = new Point(-this->x/radius,-this->y/radius,-this->z/radius);

    return p;
}

Point * Point::normalizeBezier(){
    float l = sqrt(powf(x,2) + powf(y,2) + powf(z,2));
    if(l!=0) {
        x = x/l;
        y = y/l;
        z = z/l;
    } else {
        x = 0;
        y = 0;
        z = 0;
    }
}
