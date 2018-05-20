#ifndef __LIGHT_H__
#define __LIGHT_H__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class Light{

  string type;
  float x,y,z;

	public:
		Light();
		Light(string type, float x, float y, float z);
		void draw();
};

#endif
