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
        void printfile(vector<Point*>);
        vector<Point*> applyTessellation();
        Point* getBezierPoint(float, float, vector<Point*>);
        Point* bezierForm(float, Point*, Point*, Point*, Point*);
        string lineNo(int, string);
    public:
        PatchParser(string, string, int);
        void parsePatch();
};

#endif