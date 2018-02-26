#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>

using namespace std;

//Importante!!!
//Compilar com o seguinte exemplo: g++ -std=c++11 -o generator_test main.cpp
//Apenas o C++11 contém stoi's e stod's por isso temos de limitar a versão
//TODO: Mudar os ints para floats


int addToXML(){

    return 0;
}

int parsePlane(GLint size, string filename){
    ofstream file (filename);
    if (size<=0) {
        cout << "Size must be positive." << endl
        return 1;
    }

    int height = size/2;

    // Triângulo 1:
    // h,0,h
    // -h,0,h
    // -h,0,-h
    //
    // Triângulo 2:
    // -h,0,-h
    // h,0,-h
    // h,0,h

    return 0;
}

int parseBox(GLint x, GLint y, GLint z, string filename){

    return 0;
}

int parseSphere(GLdouble radius, GLint slices, GLint stacks, string filename){
    cout << "Radius: " << radius << endl
         << "Slices: " << slices << endl
         << "Stacks: " << stacks << endl
         << "Filename: " << filename << endl;

    return 0;
}

int parseCone(GLdouble base, GLdouble height, GLint slices, GLint stacks, string filename){
    cout << "Base: " << base << endl
         << "Height: " << height << endl
         << "Slices: " << slices << endl
         << "Stacks: " << stacks << endl
         << "Filename: " << filename << endl;

    return 0;
}

//Os tipos têm de ser GLdouble e GLint (definidos na library GL/gl.h)
//para serem universais e n dependerem do SO
int main(int argc, char* argv[]) {

    if(argc <= 1){
        cout << "Command needs more arguments" << endl;
    }

    //*
    // Verifies if the object is a plane
    // Example: generator plane 2 plane.3d
    if(strcmp(argv[1],"plane") == 0){
        if(argc == 4) {
            GLint size = (GLint) stoi(argv[2]);
            string filename = argv[3];
            parsePlane(size,filename);
        }
    }

    //*
    // Verifies if the object is a box
    // Example: generator box 1 1 1 box.3d
    if(strcmp(argv[1],"box") == 0){
        if(argc == 6) {
            GLint x = (GLint) stoi(argv[2]);
            GLint y = (GLint) stoi(argv[3]);
            GLint z = (GLint) stoi(argv[4]);
            string filename = argv[5];

            parseBox(x, y, z, filename);
        }
    }

    //*
    // Verifies if the object is a sphere
    // Example: generator sphere 1 20 20 sphere.3d
    if(strcmp(argv[1],"sphere") == 0){
        if(argc == 6){

            GLdouble radius = (GLdouble)stod(argv[2]);
            GLint slices = (GLint)stoi(argv[3]);
            GLint stacks = (GLint)stoi(argv[4]);
            string filename = argv[5];

            parseSphere(radius, slices, stacks, filename);
        }
    }

    //*
    // Verifies if the object is a cone
    // Example: generator cone 1 1 20 20 cone.3d
    if(strcmp(argv[1],"cone") == 0){
        if(argc == 7){
            GLdouble base = (GLdouble)stod(argv[2]);
            GLdouble height = (GLdouble)stod(argv[3]);
            GLint slices = (GLint)stoi(argv[4]);
            GLint stacks = (GLint)stoi(argv[5]);
            string filename = argv[6];

            parseCone(base, height, slices, stacks, filename);
        }
    }

    return 0;
}
