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
        int tesselation;
        string filename;
        string patchfile;
        vector<Patch*> patches;
        void printfile();
        void renderBezier();
        string lineNo(int, int, string);
    public:
        PatchParser(string, string, int);
        void parsePatch();
};

#endif