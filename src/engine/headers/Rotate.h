class Rotate: public Transformation {
    public:
        int getAngle() {
            return this.angle;
        }

        int getX(){
            return this.x;
        }

        int getY(){
            return this.y;
        }

        int getZ(){
            return this.z;
        }

        void setAngle(double angle) {
            this.angle = angle;
        }

        void setX(int x){
            this.x = x;
        }

        void setY(int y){
            this.y = y;
        }

        void setZ(int z){
            this.z = z;
        }

        Rotate;
        Rotate(double,double,double,double);
    private:
        double angle;
        double x;
        double y;
        double z;
    };
};