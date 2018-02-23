#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>

using namespace std;

//Importante!!!
//Compilar com o seguinte exemplo: g++ -std=c++11 -o generator_test main.cpp
//Apenas o C++11 contém stoi's e stod's por isso temos de limitar a versão

int addToXML(){

    return 0;
}

int parseSphere(GLdouble radius, GLint slices, GLint stacks, string filename){
    cout << "Radius: " << radius << endl << "Slices: " << slices << endl << "Stacks: " << stacks << endl << "Filename: " << filename << endl;

    return 0;
}

int main(int argc, char* argv[]) {

    if(argc <= 1){
        cout << "Command needs more arguments" << endl;
    } else {

        //*
        // Verifies if the object is a sphere
        // Example: generator sphere 1 20 20 sphere.3d
        if(strcmp(argv[1],"sphere") == 0){
            if(argc == 6){
                //Os tipos têm de ser GLdouble e GLint (definidos na library GL/gl.h) para serem universais e n dependerem do SO
                GLdouble radius = (GLdouble)stod(argv[2]);
                GLint slices = (GLint)stoi(argv[3]);
                GLint stacks = (GLint)stoi(argv[4]);
                string filename = argv[5];

                parseSphere(radius, slices, stacks, filename);
            }
        }

    }



    return 0;
}