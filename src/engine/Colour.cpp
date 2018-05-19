#include "headers/Colour.h"

Colour::Colour(){
}

Colour::Colour(float rr, float gg, float bb){
	r = rr;
	g = gg;
	b = bb;
}

float Colour::getR(){
	return r;
}

float Colour::getG(){
	return g;
}

float Colour::getB(){
	return b;
}

void Colour::setR(float a){
	r = a;
}

void Colour::setG(float a){
	g = a;
}

void Colour::setB(float a){
	b = a;
}

Colour* Colour::clone(){
	return new Colour(r,g,b);
}

Colour::~Colour(){
}
