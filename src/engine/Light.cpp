#include "headers/Light.h"

using namespace std;

Light::Light(){
}

Light::Light(string type, float x, float y, float z){
  this->type = type;
  this->x = x;
  this->y = y;
  this->z = z;
}

void Light::draw(){

    int type = 1;
    if(this->type == "VECTOR") type = 0;

	GLfloat amb[4] = {0.1,0.1,0.1, 1};
	GLfloat diff[4] = {1, 1, 1, 0};
	GLfloat pos[4] = {this->x, this->y , this->z, 1};

	// light position
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	// light colors
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
}

