#include "headers/Light.h"

Light::Light(){
}

Light::Light(float x, float y, float z){
  this->x = x;
  this->y = y;
  this->z = z;
}

void Light::draw(){

	GLfloat amb[4] = {0.1,0.1,0.1, 1};
	GLfloat diff[4] = {1, 1, 1, 0};
	GLfloat pos[4] = {this->x, this->y , this->z, 0};

	// light position
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	// light colors
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
}

