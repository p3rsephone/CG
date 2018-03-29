#include "headers/Transformation.h"

Rotate::Rotate(): angle(0), x(0), y(0), z(0){}

Rotate::Rotate(double angle, double x,double y,double z) : angle(angle), x(x), y(y), z(z){}

Translate::Translate(): x(0), y(0), z(0){}

Translate::Translate(double x,double y,double z) : x(x), y(y), z(z){}

Scale::Scale(): x(0), y(0), z(0){}

Scale::Scale(double x,double y,double z) : x(x), y(y), z(z){}