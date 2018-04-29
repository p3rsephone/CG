#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <math.h>
#include <vector>
#include <headers/Point.h>
using std::vector;

class Transformation {
public:
    virtual int getType() = 0;

    void apply(){};
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
    Rotate(double, double, double, double, double);

    void apply(){
        double t;
        if(time!=0){
            t = glutGet(GLUT_ELAPSED_TIME) % (int)(time * 1000);
            rodar = t / (time * 1000);
            glRotatef(rodar,getX(),getY(),getZ());
        }
        glRotatef(getAngle(),getX(),getY(),getZ());
    };

    int getType(){
        return 2;
    };

private:
    double angle;
    double time;
    double rodar=0;
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

    void apply(){};

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
    void buildRotMatrix(float *x, float *y, float *z, float *m) {

        m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
        m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
        m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
        m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
    }

    void cross(float *a, float *b, float *res) {

        res[0] = a[1]*b[2] - a[2]*b[1];
        res[1] = a[2]*b[0] - a[0]*b[2];
        res[2] = a[0]*b[1] - a[1]*b[0];
    }

    void normalize(float *a) {

        float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
        a[0] = a[0]/l;
        a[1] = a[1]/l;
        a[2] = a[2]/l;
    }

    float length(float *v) {

        float res = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
        return res;

    }

    void multMatrixVector(float *m, float *v, float *res) {

        for (int j = 0; j < 4; ++j) {
            res[j] = 0;
            for (int k = 0; k < 4; ++k) {
                res[j] += v[k] * m[j * 4 + k];
            }
        }

    }

    void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

        // catmull-rom matrix
        float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
                            { 1.0f, -2.5f,  2.0f, -0.5f},
                            {-0.5f,  0.0f,  0.5f,  0.0f},
                            { 0.0f,  1.0f,  0.0f,  0.0f}};
        
        // Compute A = M * P
        float x[4] = {p0[0], p1[0], p2[0], p3[0]};
        float y[4] = {p0[1], p1[1], p2[1], p3[1]};
        float z[4] = {p0[2], p1[2], p2[2], p3[2]};
        
        float Ax[4], Ay[4], Az[4];
        multMatrixVector(*m, x, Ax);
        multMatrixVector(*m, y, Ay);
        multMatrixVector(*m, z, Az);
        
        // Compute pos = T * A
        float T[4] = {powf(t,3), powf(t,2), t, 1};
        pos[0] = T[0] * Ax[0] + T[1] * Ax[1] + T[2] * Ax[2] + T[3] * Ax[3];
        pos[1] = T[0] * Ay[0] + T[1] * Ay[1] + T[2] * Ay[2] + T[3] * Ay[3];
        pos[2] = T[0] * Az[0] + T[1] * Az[1] + T[2] * Az[2] + T[3] * Az[3];
        
        // compute deriv = T' * A
        float T_d[4] = {3*powf(t,2), 2*t, 1, 0};
        deriv[0] = T_d[0] * Ax[0] + T_d[1] * Ax[1] + T_d[2] * Ax[2] + T_d[3] * Ax[3];
        deriv[1] = T_d[0] * Ay[0] + T_d[1] * Ay[1] + T_d[2] * Ay[2] + T_d[3] * Ay[3];
        deriv[2] = T_d[0] * Az[0] + T_d[1] * Az[1] + T_d[2] * Az[2] + T_d[3] * Az[3];
        
    }

    // given  global t, returns the point in the curve
    void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv) {

        float t = gt * POINT_COUNT; // this is the real global t
        int index = floor(t);  // which segment
        t = t - index; // where within  the segment

        // indices store the points
        if(POINT_COUNT!=0){
            int indices[4]; 
            indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;
            indices[1] = (indices[0]+1)%POINT_COUNT;
            indices[2] = (indices[1]+1)%POINT_COUNT; 
            indices[3] = (indices[2]+1)%POINT_COUNT;

            getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
        }
    }

    void renderCatmullRomCurve() {
    // desenhar a curva usando segmentos de reta - GL_LINE_LOOP
        int i = 0;

        glColor3f(1, 1, 1);
        glBegin(GL_LINE_LOOP);

        for(i=0;i<100;i++)
        {
            float pos[3];
            float deriv[3];
            getGlobalCatmullRomPoint(i/100.f,pos,deriv);
            glVertex3f(pos[0],pos[1],pos[2]);
        }
        glEnd();
    }

    void apply() {
        
        float A[16];
        float pos[3];
        float deriv[3];
        float V[3];
        float t;

        if(time!=0){
            t = glutGet(GLUT_ELAPSED_TIME) % (int)(time * 1000);
            rodar = t / (time * 1000);
            getGlobalCatmullRomPoint(rodar, pos, deriv);
            glTranslatef(pos[0], pos[1], pos[2]);

            cross(deriv, Y, V);
            cross(V,deriv, Y);
            normalize(deriv);
            normalize(V);
            normalize(Y);
            buildRotMatrix(deriv, Y, V, A);
            glMultMatrixf(A);
        }
    }

    void addElement(Point* ponto){
        float pontos[this->POINT_COUNT][3];
        for(int i=0; i<POINT_COUNT; i++){
            for(int j=0; j<3; j++){
                pontos[i][j]=p[i][j];
            }
        }

        (this->p) = (float **)malloc((this->POINT_COUNT+1) * sizeof(float*));
        for(int i = 0; i < (this->POINT_COUNT+1); i++) (this->p)[i] = (float *)malloc(3 * sizeof(float));

        for(int i=0; i<POINT_COUNT; i++){
            for(int j=0; j<3; j++){
                p[i][j]=pontos[i][j];
            }
        }

        this->p[this->POINT_COUNT][0]= (*ponto).X();
        this->p[this->POINT_COUNT][1]= (*ponto).Y();
        this->p[this->POINT_COUNT][2]= (*ponto).Z();
        this->POINT_COUNT++;
    }

    Translate();

    Translate(float t);

    int getType(){
        return 1;
    };

private:
    float Y[3] = { 0, 1, 0 };
    int POINT_COUNT;
    float **p;
    float time;
    float rodar=0;
};
#endif
