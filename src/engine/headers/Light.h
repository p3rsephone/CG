#ifndef __LIGHT_H__
#define __LIGHT_H__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>


class Light{

  float x,y,z;

	public:
		Light();
		Light(float x, float y, float z);
		void draw();
};

#endif
