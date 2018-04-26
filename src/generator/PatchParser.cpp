#include "headers/PatchParser.h"

PatchParser::PatchParser(string f, string p, int t) : filename(f),patchfile(p),tesselation(t) {}

/**
 * @brief Parses the patch file
 */
void PatchParser::parsePatch() {
  int n;  // Number of Patches
  int pL;  // Position in string line
  int pPL; // Position in string pointLine
  int index;  // Index
  double pointCr[3]; // Point coordenates
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
        pointLine = lineNo(n,index,patchDir);

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
    printfile();
  } else {
    cout << "Error while opening file " << patchfile << endl;
  }
}

/**
 * @brief Makes the .3d file
 */
void PatchParser::printfile() {
  ofstream file;
  string fileDir = "files/" + filename;
  file.open(fileDir, ios_base::trunc);
  if (!file.is_open()) {
    cout << "Error while opening file " << filename << endl;
  } else {
    for (vector<Patch*>::iterator it = patches.begin();it!=patches.end();it++)
      for (vector<Point*>::iterator i = (*it)->getControlPoints().begin(); i!= (*it)->getControlPoints().end(); i++)
        file << (*i)->toString();
    
    file.close();
  }
}

/**
 * @brief Returns a certain line from the patchfile
 * @param nPatch Number of Patches
 * @param n      Line number
 * @return Line
 */
string PatchParser::lineNo(int nPatch, int n, string filename) {
  string line;
  int lineNumber = nPatch + 3 + n;
  ifstream patch;
  patch.open(filename);
  if (patch.is_open())
    for (int i=0; i<lineNumber; i++) getline(patch,line);
  else cout << "Error while opening file " << patchfile << endl;
  return line;
}