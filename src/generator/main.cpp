#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/figures.h"

//TODO: Check these headers OMG
//TODO: Figure out namespaces -- HELP

//Importante!!!
//Compilar com o seguinte exemplo: g++ -std=c++11 -o generator_test main.cpp
//Apenas o C++11 contém stoi's e stod's por isso temos de limitar a versão

/**
 * Shows the usage of this file.
 */
void usage(){
    cout << "#_____________________________ HELP _____________________________# " << endl;
	cout << "|                                                                |" << endl;
    cout << "|   SYNOPSIS                                                     |" << endl;
    cout << "|          ./generator {COMMAND} ... {OUTPUT FILE}               |" << endl;
	cout << "|                      [-h]                                      |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   COMMANDS:                                                    |" << endl;
	cout << "| - plane [SIZE]                                                 |" << endl;
	cout << "|      Creates a square in the XZ plane, centred in the origin.  |" << endl;
	cout << "|                                                                |" << endl;
	cout << "| - box [SIZE X] [SIZE Y] [SIZE Z] [DIVISIONS]                   |" << endl;
	cout << "|      Creates a box with the dimensions and divisions specified.|" << endl;
	cout << "|                                                                |" << endl;
	cout << "| - sphere [RADIUS] [SLICE] [STACK]                              |" << endl;
	cout << "|      Creates a sphere with the radius, number of slices and    |" << endl;
	cout << "|      stacks given.                                             |" << endl;
	cout << "|                                                                |" << endl;
	cout << "| - cone [RADIUS] [HEIGHT] [SLICE] [STACK]                       |" << endl;
	cout << "|      Creates a cone with the radius, height, number of slices  |" << endl;
	cout << "|      and stacks given.                                         |" << endl;
	cout << "|                                                                |" << endl;
	cout << "| - cylinder [RADIUS] [HEIGHT] [SLICE] [STACK]                   |" << endl;
	cout << "|      Creates a cylinder with the radius, height, number of     |" << endl;
	cout << "|      slices and stacks given.                                  |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   OUTPUT FILE:                                                 |" << endl;
	cout << "| In the file section you can specify any file in which you wish |" << endl;
	cout << "| to save the coordinates generated with the previous commands.  |" << endl;
	cout << "|                                                                |" << endl;
    cout << "| The file should be in the 'files' directory.                   |" << endl;
	cout << "| If the file doesn't exist it will be created. If it does it    |" << endl;
	cout << "| will be truncated.                                             |" << endl;
	cout << "|                                                                |" << endl;
    cout << "#________________________________________________________________#" << endl;

}

/**
 * Adds filenames to .xml file
 * @param  filename Name of file to add
 */
void addToXML(string filename){
    ofstream file;
    string xml = "files/main.xml";
    file.open(xml);
    if (!file.is_open()) {
        cout << "Error while adding file " << filename << " to xml." <<endl;
    } else {
        //TODO: Add stuff to xml
        file.close();
    }
}

/**
 * Makes the .3d and .xml files
 * @param filename Filename for .3d file
 * @param points   List of points
 */
void printfile(string filename, vector<Point*> points) {
    ofstream file;
    string fileDir = "files/" + filename;
    file.open(fileDir, ios_base::trunc);
    if (!file.is_open()) {
        cout << "Error while opening file " << filename << endl;
    } else {
        for (vector<Point*>::iterator i = points.begin() ; i!= points.end(); i++)
            file << (*i)->toString();

        file.close();
        addToXML(filename);
    }

}

int main(int argc, char* argv[]) {
    string filename;
    vector<Point*> points;

    if (argc == 4 && (strcmp(argv[1],"plane") == 0)){
        double size = atof(argv[2]);
        if (size<=0) {
            cout << "Size must be positive." << endl;
            return 1;
        }
        filename = argv[3];

        points = createPlane(size);
    }

    else if ((argc == 6 || argc == 7) && (strcmp(argv[1],"box") == 0)){
        double x = atof(argv[2]);
        double y = atof(argv[3]);
        double z = atof(argv[4]);
        int d = (argc == 7) ? stoi(argv[5]) : 1;
        filename = (argc == 7) ? argv[6] : argv[5];

        points = createBox(x, y, z, d);
    }

    else if (argc == 6 && (strcmp(argv[1],"sphere") == 0)){
        double radius = atof(argv[2]);
        int slices = (int) stoi(argv[3]);
        int stacks = (int) stoi(argv[4]);
        filename = argv[5];

        points = createSphere(radius, slices, stacks);
    }

    else if (argc == 7 && (strcmp(argv[1],"cone") == 0)){
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
