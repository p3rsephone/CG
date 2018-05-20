#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>

#include "Colour.h"


using namespace std;

class Material{

	float diffuse[4]; 	// default: {0.8, 0.8, 0.8, 1};
	float ambient[4]; 	// default: {0.2, 0.2, 0.2, 1};
	float specular[4]; 	// default: {0, 0, 0, 1};
	float emission[4]; 	// default: {0, 0, 0, 1};
	float shininess; 	// default: 0;

	public:
		Material();
		Material(Colour*, Colour*, Colour*, Colour*, float);
		void draw();

};

#endif
