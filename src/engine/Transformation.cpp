#include "headers/Transformation.h"

Rotate::Rotate(): angle(0), x(0), y(0), z(0){}

Rotate::Rotate(double angle, double x,double y,double z) : angle(angle), x(x), y(y), z(z){}

Translate::Translate(float t){
        this->time=t;
        this->POINT_COUNT=0;
}

Scale::Scale(): x(0), y(0), z(0){}

Scale::Scale(double x,double y,double z) : x(x), y(y), z(z){}