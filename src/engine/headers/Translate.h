class Translate: public Transformation {
public:
    int getX(){
        return this.x;
    }

    int getY(){
        return this.y;
    }

    int getZ(){
        return this.z;
    }

    void setX(double x){
        this.x = x;
    }

    void setY(double y){
        this.y = y;
    }

    void setZ(double z){
        this.z = z;
    }

    Translate();
    Translate(double,double,double);
private:
    double x;
    double y;
    double z;
};