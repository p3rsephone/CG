#include "headers/PatchParser.h"

PatchParser::PatchParser(string f, string p, int t) : filename(f),patchfile(p),tessellation(t) {}

/**
 * @brief Parses the patch file
 */
void PatchParser::parsePatch() {
  int n;  // Number of Patches
  int pL;  // Position in string line
  int pPL; // Position in string pointLine
  int index;  // Index
  int nPoints;  // Number of Points
  float pointCr[3]; // Point coordenates
  string line;  // Line of indexes currently being examined
  string pointLine;  // Line of points currently being examined

  ifstream patch;
  string patchDir = "files/"+ patchfile;
  patch.open(patchDir);

  if (patch.is_open()) {
    getline(patch, line);
    n = atoi(line.c_str());

    for (int i=0; i<n; i++) {
      getline(patch,line);
      Patch* p = new Patch();
      patches.push_back(p);

      for (int j=0; j<16;j++) {
        pL = line.find(',',0);
        index = atoi(line.substr(0,pL).c_str());
        pointLine = lineNo(n+3+index,patchDir);

        for (int k=0;k<3;k++) {
          pPL = pointLine.find(',',0);
          pointCr[k] = atof(pointLine.substr(0,pPL).c_str());
          pointLine.erase(0,pPL+1);
        }
        p->addPoint(new Point(pointCr[0],pointCr[1],pointCr[2]));
        line.erase(0,pL+1);
      }
    }
    patch.close();
    printfile(applyTessellation());
  } else {
    cout << "Error while opening file " << patchfile << endl;
  }
}

/**
 * @brief Makes the .3d file
 * @param points Points to print
 */
void PatchParser::printfile(vector<Point*> points) {
  ofstream file;
  string fileDir = "files/" + filename;
  file.open(fileDir, ios_base::trunc);
  if (!file.is_open()) {
    cout << "Error while opening file " << filename << endl;
  } else {
    file << points.size() << endl;
    for (vector<Point*>::iterator i = points.begin(); i!= points.end(); i++)
        file << (*i)->toString();
    
    file.close();
  }
}

/**
 * @brief Applies tessellation to the Bezier patch
 * @return Tessellated points
 */
vector<Point*> PatchParser::applyTessellation(){
  vector<Point*> tPoints;  // Tesselated points
  vector<Point*> ctrl;  // Control Points
  float u,v,uNext,vNext;  // U and V for the Bezier Curve
  float shift = 1.0/tessellation;

  for (vector<Patch*>::iterator it = patches.begin();it!=patches.end();it++){
    ctrl = (*it)->getControlPoints();
    
    for (int i=0;i<tessellation;i++) {
      for (int j=0;j<tessellation;j++) {
        u = j * shift;
				v = i * shift;
				uNext = (j+1) * shift;
        vNext = (i+1) * shift;

        Point* p0 = getBezierPoint(u, v, ctrl);
				Point* p1 = getBezierPoint(u, vNext, ctrl);
				Point* p2 = getBezierPoint(uNext, v, ctrl);
        Point* p3 = getBezierPoint(uNext, vNext, ctrl);

        tPoints.push_back(p0);
        tPoints.push_back(p2);
        tPoints.push_back(p3);

        tPoints.push_back(p0);
        tPoints.push_back(p3);
        tPoints.push_back(p1);
      }
    }
  }

  return tPoints;
}

/**
 * @brief Finds Bezier point with a certain u and v from control points
 * @param u      U coordinate
 * @param v      V coordinate
 * @param points Control cPoints
 * @return Point
 */
Point* PatchParser::getBezierPoint(float u, float v, vector<Point*> cPoints) {
  float matrixUV[4][3];  // Matrixes with the transformations for U and V respectivelly
  int j=0;
  Point* p0,*p1,*p2,*p3;
  for (int i=0;i<16;) {
    p0 = new Point(cPoints[i]->X(), cPoints[i]->Y(), cPoints[i]->Z());
    p1 = new Point(cPoints[++i]->X(), cPoints[i]->Y(), cPoints[i]->Z());
    p2 = new Point(cPoints[++i]->X(), cPoints[i]->Y(), cPoints[i]->Z());
    p3 = new Point(cPoints[++i]->X(), cPoints[i]->Y(), cPoints[i++]->Z());

    Point* p = bezierForm(u, p0,p1,p2,p3);
    matrixUV[j][0] = p->X();
    matrixUV[j][1] = p->Y();
    matrixUV[j][2] = p->Z();
  }
  return bezierForm(v, new Point(matrixUV[0][0],matrixUV[0][1],matrixUV[0][2]),
							  	     new Point(matrixUV[1][0],matrixUV[1][1],matrixUV[1][2]),
			    				     new Point(matrixUV[2][0],matrixUV[2][1],matrixUV[2][2]),
                       new Point(matrixUV[3][0],matrixUV[3][1],matrixUV[3][2]));
}

/**
 * @brief Applies the Bezier point-finding formula
 * @param t  T parameter
 * @param p0 Point 0
 * @param p0 Point 1
 * @param p0 Point 2
 * @param p0 Point 3
 * @return Point from Bezier Curve
 */
Point* PatchParser::bezierForm(float t, Point* p0, Point* p1, Point* p2, Point* p3) {
  float b0 = pow((1.0-t),3);
  float b1 = 3 * t * pow((1.0-t),2);
  float b2 = 3 * pow(t,2) * (1.0-t);
  float b3 = pow(t,3);

  float x = b3 * p3->X() + b2 * p2->X() + b1 * p1->X() + b0 * p0->X();
  float y = b3 * p3->Y() + b2 * p2->Y() + b1 * p1->Y() + b0 * p0->Y();
  float z = b3 * p3->Z() + b2 * p2->Z() + b1 * p1->Z() + b0 * p0->Z();

  return (new Point(x,y,z));
}

/**
 * @brief Returns a certain line from the patchfile
 * @param lineNumber Line number
 * @return Line
 */
string PatchParser::lineNo(int lineNumber, string filename) {
  string line;
  ifstream patch;
  patch.open(filename);
  if (patch.is_open())
    for (int i=0; i<lineNumber; i++) getline(patch,line);
  else cout << "Error while opening file " << patchfile << endl;
  return line;
}