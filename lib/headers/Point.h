#include <string>
#include <sstream>

class Point {
  private:
    double x,y,z;
  public:
    Point();
    Point(double, double, double);
    std::string toString();
    double X(){ return x; }
    double Y(){ return y; }
    double Z(){ return z; }
};
