#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__

class Transformation {
public:
    virtual int getType() = 0;

    virtual double getX() = 0;

    virtual double getY() = 0;

    virtual double getZ() = 0;
};

class Rotate: public Transformation {
public:
    double getAngle() {
        return this->angle;
    }

    double getX() {
        return this->x;
    }

    double getY() {
        return this->y;
    }

    double getZ() {
        return this->z;
    }

    void setAngle(double angle) {
        this->angle = angle;
    }

    void setX(int x) {
        this->x = x;
    }

    void setY(int y) {
        this->y = y;
    }

    void setZ(int z) {
        this->z = z;
    }

    Rotate();
    Rotate(double, double, double, double);

    int getType(){
        return 2;
    };

private:
    double angle;
    double x;
    double y;
    double z;
};

class Scale: public Transformation {
public:
    double getX() {
        return this->x;
    }

    double getY() {
        return this->y;
    }

    double getZ() {
        return this->z;
    }

    void setX(double x) {
        this->x = x;
    }

    void setY(double y) {
        this->y = y;
    }

    void setZ(double z) {
        this->z = z;
    }

    Scale();
    Scale(double, double, double);

    int getType(){
        return 3;
    };

private:
    double x;
    double y;
    double z;
};

class Translate: public Transformation {
public:
    double getX(){
        return this->x;
    }

    double getY(){
        return this->y;
    }

    double getZ(){
        return this->z;
    }

    void setX(double x){
        this->x = x;
    }

    void setY(double y){
        this->y = y;
    }

    void setZ(double z){
        this->z = z;
    }

    Translate();
    Translate(double,double,double);

    int getType(){
        return 1;
    };

private:
    double x;
    double y;
    double z;
};
#endif
