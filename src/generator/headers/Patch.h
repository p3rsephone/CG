#ifndef __PATCH_H__
#define __PATCH_H__

#include <vector>
#include <math.h>
#include "../../../lib/headers/Point.h"

using namespace std;

class Patch {
    private:
        vector<Point*> controlPoints;
    public:
        Patch();
        Patch(vector<Point*>);
        vector<Point*> getControlPoints();
        void addPoint(Point*);
};

#endif