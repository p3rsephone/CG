#ifndef __PATCHPARSER_H__
#define __PATCHPARSER_H__

#include "Patch.h"
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class PatchParser {
    private:
        int tessellation;
        string filename;
        string patchfile;
        vector<Patch*> patches;
        vector<Point*> points;
        vector<Point*> normals;
        vector<Point*> textures;
        void printfile(vector<Point*>, vector<Point*>, vector<Point*>);
        void applyTessellationNormals();
        Point* getBezierPoint(float, float, vector<Point*>);
        Point* getBezierNormal(float, float, vector<Point*>);
        float getBezierTangent(float, float, float points[4][4], int);
        Point* bezierForm(float, Point*, Point*, Point*, Point*);
        string lineNo(int, string);
    public:
        PatchParser(string, string, int);
        void parsePatch();
};

#endif