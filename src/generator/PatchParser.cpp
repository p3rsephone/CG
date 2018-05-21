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
    applyTessellationNormals();
    printfile(points, normals, textures);
  } else {
    cout << "Error while opening file " << patchfile << endl;
  }
}

/**
 * @brief Makes the .3d file
 * @param points Points to print
 */
void PatchParser::printfile(vector<Point*> points, vector<Point*> normals, vector<Point*> textures) {
  ofstream file;
  string fileDir = "files/" + filename;
  file.open(fileDir, ios_base::trunc);
  if (!file.is_open()) {
    cout << "Error while opening file " << filename << endl;
  } else {
    file << points.size()*3 << endl;
    file << "Points:" << endl;
    for (vector<Point*>::iterator i = points.begin(); i!= points.end(); i++)
        file << (*i)->toString();

    file << "Normals:" << endl;
    for (vector<Point*>::iterator i = normals.begin(); i!= normals.end(); i++)
        file << (*i)->toString();
    
    file << "Textures:" << endl;
    for (vector<Point*>::iterator i = textures.begin(); i!= textures.end(); i++)
        file << (*i)->toString();
    
    file.close();
  }
}

/**
 * @brief Applies tessellation to the Bezier patch
 */
void PatchParser::applyTessellationNormals(){
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

        // Apply normals
        Point* n0 = getBezierNormal(u, v, ctrl);
        Point* n1 = getBezierNormal(u, vNext, ctrl);
        Point* n2 = getBezierNormal(uNext, v, ctrl);
        Point* n3 = getBezierNormal(uNext, vNext, ctrl);

        points.push_back(p0);
        normals.push_back(n0);
        textures.push_back(new Point(u,v,0.0f));
        points.push_back(p2);
        normals.push_back(n2);
        textures.push_back(new Point(uNext,v,0.0f));
        points.push_back(p3);
        normals.push_back(n3);
        textures.push_back(new Point(uNext,vNext,0.0f));        

        points.push_back(p0);
        normals.push_back(n0);
        textures.push_back(new Point(u,v,0.0f));
        points.push_back(p3);
        normals.push_back(n3);
        textures.push_back(new Point(uNext,vNext,0.0f));
        points.push_back(p1);
        normals.push_back(n1);
        textures.push_back(new Point(u,vNext,0.0f));
      }
    }
  }
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
  for (int i=0;i<16;j++) {
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
  float b0 = powf((1.0-t),3);
  float b1 = 3 * t * powf((1.0-t),2);
  float b2 = 3 * powf(t,2) * (1.0-t);
  float b3 = powf(t,3);

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

/**
 * @brief Calculates normal points for bezier patchfile
 * @return Normal points
 */
Point* PatchParser::getBezierNormal(float u, float v, vector<Point*> ctrl) {
  float pointsX[4][4];
  float pointsY[4][4];
  float pointsZ[4][4];
  int indice =0;
  Point *pu, *pv;
  float x,y,z;

  for(int i = 0; i < 4; i++){ 
    for(int j = 0; j < 4; j++, indice++){ 
  		pointsX[i][j] = ctrl[indice]->X();
   		pointsY[i][j] = ctrl[indice]->Y();
    	pointsZ[i][j] = ctrl[indice]->Z();
   	}
  }

  pu = (new Point(getBezierTangent(u,v,pointsX,0), getBezierTangent(u,v,pointsY,0), getBezierTangent(u,v,pointsZ,0)))->normalizeBezier();
  pv = (new Point(getBezierTangent(u,v,pointsX,1), getBezierTangent(u,v,pointsY,1), getBezierTangent(u,v,pointsZ,1)))->normalizeBezier();

  x = pv->Y() * pu->Z() - pv->Z() * pu->Y();
  y = pv->Z() * pu->X() - pv->X() * pu->Z();
  z = pv->X() * pu->Y() - pv->Y() * pu->X();

  return new Point(x,y,z);
}

/**
 * @brief Calculates tangents using u and v
 * @return Tangent 
 */
float PatchParser::getBezierTangent(float u, float v, float points[4][4], int derivate) {
  float res=0;
  float m[4][4] = {{-1, 3, -3, 1},  //Matrix for derivates
                   {3, -6, 3, 0 },
                   {-3, 3, 0, 0},
                   {1, 0, 0, 0}};
  float aux[4], segAux[4];
  int i;
  
  // Derivate u
  // bu*M
  if (derivate) {
    for(i = 0; i<4; i++){
      aux[i] = (powf(u,3.0)*m[0][i]) + (powf(u,2.0)*m[1][i]) + (u*m[2][i]) + m[3][i];
    }
  } else {
    for(i = 0; i<4; i++){
      aux[i] = (3 * powf(u,2.0)*m[0][i]) + (2*u*m[1][i]) + (1*m[2][i]);
    }
  }

  // (bu*M)*P
  for(i = 0; i<4; i++){
    segAux[i] = (aux[0]*points[0][i]) + (aux[1]*points[1][i]) + (aux[2]*points[2][i]) + (aux[3]*points[3][i]);
  }

  // ((bu*M)*P)*MT
  for(i = 0; i<4; i++){
    aux[i] = (segAux[0]*m[0][i]) + (segAux[1]*m[1][i]) + (segAux[2]*m[2][i]) + (segAux[3]*m[3][i]);
  }

// Derivate v
// (((bu*M)*P)*MT)*bv
  if(derivate) {
    res = aux[0] * (3 * powf(v,2.0));
    res += aux[1] * (2 * v);
    res += aux[2];
  } else {
    res = aux[0] * powf(v,3.0);
    res += aux[1] * powf(v,2.0);
    res += aux[2] * v;
    res += aux[3];
  }
  return res;
}