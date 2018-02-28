#include <string>
#include <sstream>

class Point {
    double x,y,z;
  public:
    Point();
    Point(double, double, double);
    std::string toString();
};
