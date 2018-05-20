#include "headers/Model.h"
using namespace std;
Model::Model(){
}

Model::Model(string name, int size_points, string texture_file){
  this->name = name;


  this->points_array = new float*[3];
  for(int i= 0 ; i < 3; i++)
    this->points_array[i] = new float[size_points];

  this->buffer = new GLuint[3];

  this->state = new int[3];
  for(int i= 0 ; i < 3 ; i++)
    this->state[i] = 0;

  this->size = size_points;
  this->loadTexture(texture_file);
}

Model::Model(string name, int size_points){
  this->name = name;


  this->points_array = new float*[3];
  for(int i= 0 ; i < 3; i++)
    this->points_array[i] = new float[size_points];

  this->buffer = new GLuint[3];

  this->state = new int[3];
  for(int i= 0 ; i < 3 ; i++)
    this->state[i] = 0;

  this->size = size_points;
}

void Model::addElementPoint(float point){
  this->points_array[0][this->state[0]++] = point;
}

void Model::addElementTexture(float point){
  this->points_array[1][this->state[1]++] = point;
}

void Model::addElementNormal(float point){
  this->points_array[2][this->state[2]++] = point;
}

float* Model::model(){
  return this->points_array[0];
}

float* Model::textures(){
  return this->points_array[1];
}

float* Model::normal(){
  return this->points_array[2];
}

void Model::setTexture(GLuint t){
	texture = t;
}

void Model::setColourComponent(Material* c){
  colour_component = c;
}


void Model::prepare(){
  glGenBuffers(3,(this)->buffer);
  for(int i=0; i< 3; i++){
    glBindBuffer(GL_ARRAY_BUFFER, (this)->buffer[i]);
    glBufferData(GL_ARRAY_BUFFER,this->size * sizeof(float),this->points_array[i],GL_STATIC_DRAW);
  }

}

void Model::loadTexture(string texture_file){

	unsigned int t;
	unsigned char *texData;

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1, &t);
	ilBindImage(t);
	ilLoadImage((ILstring) texture_file.c_str());
	this->image_width = ilGetInteger(IL_IMAGE_WIDTH);
	this->image_height = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->image_width, this->image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Model::draw(){
  for(int i=0; i< 3; i++){
    glBindBuffer(GL_ARRAY_BUFFER, (this)->buffer[i]);
    glVertexPointer(3, GL_FLOAT, 0, 0);
  }

  glEnable(GL_LIGHTING);
  glDrawArrays(GL_TRIANGLES,0,(this->size)-1);
  glDisable(GL_LIGHTING);
  glBindTexture(GL_TEXTURE_2D,0);
}

