#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "figures.h"

//TODO: Check these headers OMG
//TODO: Figure out namespaces -- HELP

//Importante!!!
//Compilar com o seguinte exemplo: g++ -std=c++11 -o generator_test main.cpp
//Apenas o C++11 contém stoi's e stod's por isso temos de limitar a versão
//TODO: Change ints to floats

/**
    Shows the usage of this file.
 */
void usage(){
    // TODO: Write instructions
}

<<<<<<< HEAD
/**
 * Shows the usage of this file.
 */
void usage(){
    // TODO: Write instructions
}

/**
 * Prints .3d and .xml files
 */
void printfile(string filename, vector<Point*>) {
    // TODO: Print everything
=======
int addToXML(){

    return 0;
}

int parsePlane(GLint size, string filename){
    ofstream file (filename);
    if (size<=0) {
        cout << "Size must be positive." << endl;
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

int parseBox(GLint x, GLint y, GLint z, GLint d, string filename){

    cout << "X: " << x << endl
         << "Y: " << y << endl
         << "Z: " << z << endl
         << "Div: " << d << endl
         << "Filename: " << filename << endl;

    return 0;
>>>>>>> 12a431ac8ae80710ed336c42529c2a8d75856588
}

int addToXML(){
    // TODO: Check if necessary
    return 0;
}


int main(int argc, char* argv[]) {
    string filename;
    vector<Point*> points;

    if (strcmp(argv[1],"plane") == 0 && (argc == 4)){
        double size = atof(argv[2]);
        if (size<=0) {
            cout << "Size must be positive." << endl;
            return 1;
        }
        filename = argv[3];

<<<<<<< HEAD
        points = createPlane(size);
    }

    else if (strcmp(argv[1],"box") == 0 && (argc == 6 || argc == 7)){
        double x = atof(argv[2]);
        double y = atof(argv[3]);
        double z = atof(argv[4]);
        int d = (argc == 7) ? stoi(argv[5]) : 1;
        filename = (argc == 7) ? argv[6] : argv[5];

        points = createBox(x, y, z, d);
=======
    if(argc <= 1){
        cout << "Command needs more arguments" << endl;
        usage();
    }

    //*
    // Verifies if the object is a plane
    // Example: generator plane 2 plane.3d
    if(strcmp(argv[1],"plane") == 0){
        if(argc == 4) {
            GLint size = (GLint) stoi(argv[2]);
            string filename = argv[3];

            parsePlane(size,filename);
        } else {
            usage();
        }
    }

    //*
    // Verifies if the object is a box
    // Example: generator box 1 1 1 box.3d
    // Example 2: generator box 1 1 1 3 box.3d
    if(strcmp(argv[1],"box") == 0){
        if(argc == 6 || argc == 7) {
            GLint x = (GLint) stoi(argv[2]);
            GLint y = (GLint) stoi(argv[3]);
            GLint z = (GLint) stoi(argv[4]);
            GLint d = (argc == 7) ? stoi(argv[5]) : 1;
            string filename = (argc == 7) ? argv[6] : argv[5];

            parseBox(x, y, z, d, filename);
        } else {
            usage();
        }
>>>>>>> 12a431ac8ae80710ed336c42529c2a8d75856588
    }

    else if (strcmp(argv[1],"sphere") == 0 && (argc == 6)){
        double radius = atof(argv[2]);
        int slices = (int) stoi(argv[3]);
        int stacks = (int) stoi(argv[4]);
        filename = argv[5];

<<<<<<< HEAD
        points = createSphere(radius, slices, stacks);
    }

    else if (strcmp(argv[1],"cone") == 0 && (argc == 7)){
        double base = atof(argv[2]);
        double height = atof(argv[3]);
        int slices = (int) stoi(argv[4]);
        int stacks = (int) stoi(argv[5]);
        filename = argv[6];

        points = createCone(base, height, slices, stacks);
    }

    else {
        usage();
        return 0;
=======
            GLdouble radius = (GLdouble) stod(argv[2]);
            GLint slices = (GLint) stoi(argv[3]);
            GLint stacks = (GLint) stoi(argv[4]);
            string filename = argv[5];

            parseSphere(radius, slices, stacks, filename);
        } else {
            usage();
        }
    }

    //*
    // Verifies if the object is a cone
    // Example: generator cone 1 1 20 20 cone.3d
    if(strcmp(argv[1],"cone") == 0){
        if(argc == 7){
            GLdouble base = (GLdouble) stod(argv[2]);
            GLdouble height = (GLdouble) stod(argv[3]);
            GLint slices = (GLint) stoi(argv[4]);
            GLint stacks = (GLint) stoi(argv[5]);
            string filename = argv[6];

            parseCone(base, height, slices, stacks, filename);
        } else {
            usage();
        }
>>>>>>> 12a431ac8ae80710ed336c42529c2a8d75856588
    }

    printfile(filename, points);
    return 0;
}
