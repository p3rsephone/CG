#include "Point.h"

Point::Point(): x(0), y(0), z(0){}

Point::Point(double x, double y, double z) : x(x), y(y), z(z){}

std::string Point::toString() {
    std::ostringstream sstream;
    sstream << x << ' ' << y << ' ' << z << '\n';
    return sstream.str();
}
