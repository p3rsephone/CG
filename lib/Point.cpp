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

/**
 * @brief Transforms Point into String
 * @return String
 */
std::string Point::toString() {
    std::ostringstream sstream;
    sstream << x << ' ' << y << ' ' << z << '\n';
    return sstream.str();
}
