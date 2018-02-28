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

        points = createPlane(size);
    }

    else if (strcmp(argv[1],"box") == 0 && (argc == 6 || argc == 7)){
        double x = atof(argv[2]);
        double y = atof(argv[3]);
        double z = atof(argv[4]);
        int d = (argc == 7) ? stoi(argv[5]) : 1;
        filename = (argc == 7) ? argv[6] : argv[5];

        points = createBox(x, y, z, d);
    }

    else if (strcmp(argv[1],"sphere") == 0 && (argc == 6)){
        double radius = atof(argv[2]);
        int slices = (int) stoi(argv[3]);
        int stacks = (int) stoi(argv[4]);
        filename = argv[5];

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
    }

    printfile(filename, points);
    return 0;
}
