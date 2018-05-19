#include "headers/Material.h"

Material::Material(){
}

Material::Material(Colour* diff, Colour* amb, Colour* spec, Colour* emi, float shi){
	diffuse[3] = -1;
	ambient[3] = -1;

	if(diff != NULL){
		diffuse[0] = diff->getR();
		diffuse[1] = diff->getG();
		diffuse[2] = diff->getB();
		diffuse[3] = 1;
	}

	if(amb != NULL){
		ambient[0] = amb->getR();
		ambient[1] = amb->getG();
		ambient[2] = amb->getB();
		ambient[3] = 1;
	}

	specular[0] = spec->getR();
	specular[1] = spec->getG();
	specular[2] = spec->getB();
	specular[3] = 1;

	emission[0] = emi->getR();
	emission[1] = emi->getG();
	emission[2] = emi->getB();
	emission[3] = 1;

	shininess = shi;
}

void Material::draw() {
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	if(diffuse[3] != -1)
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	if(ambient[3] != -1)
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
}
