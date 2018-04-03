#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__

class Transformation {
public:
    virtual int getType() = 0;
};

class Rotate: public Transformation {
public:
    int getAngle() {
        return this->angle;
    }

    int getX() {
        return this->x;
    }

    int getY() {
        return this->y;
    }

    int getZ() {
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
    int getX() {
        return this->x;
    }

    int getY() {
        return this->y;
    }

    int getZ() {
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
    int getX(){
        return this->x;
    }

    int getY(){
        return this->y;
    }

    int getZ(){
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

