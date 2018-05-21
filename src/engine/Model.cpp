#include "headers/Model.h"
#include <cassert>
using namespace std;

Model::Model(){
  texture=0;
}

Model::Model(string name, string texture_file,  vector<Point*> v_list, vector<Point*> n_list, vector<Point*> t_list){
  this->name = name;
  buffers_size[0] = v_list.size();
	buffers_size[1] = n_list.size();
	buffers_size[2] = t_list.size();
	prepare(v_list, n_list, t_list);
  loadTexture(texture_file);
}

Model::Model(string name){
  texture = 0;
  this->name = name;

  //this->buffer = new GLuint[3];

  //this->state = new int[3];
  //for(int i= 0 ; i < 3 ; i++)
  //  this->state[i] = 0;

  //this->size = size_points;
}

void Model::addElementPoint(float point){
  //this->points_array[this->state[0]++] = point;
}

void Model::addElementNormal(float point){
  //this->normals_array[this->state[2]++] = point;
}

void Model::addElementTexture(float point){
 // this->texture_array[this->state[1]++] = point;
}

float* Model::model(){
  //return this->points_array;
}

float* Model::textures(){
  //return this->texture_array;
}

float* Model::normal(){
  //return this->normals_array;
}

void Model::setTexture(GLuint t){
	texture = t;
}

void Model::setColourComponent(Material* c){
  colour_component = c;
}


void Model::prepare(vector<Point*> vertex_list, vector<Point*> normal_list, vector<Point*> texture_list){
  int index = 0;
	float* vertex_array = (float*) malloc(sizeof(float) * vertex_list.size() * 3);
	float* normal_array = (float*) malloc(sizeof(float) * normal_list.size() * 3);
	float* texture_array = (float*) malloc(sizeof(float) * texture_list.size() * 2);

	for(vector<Point*>::const_iterator vertex_it = vertex_list.begin(); vertex_it != vertex_list.end(); ++vertex_it){					
		vertex_array[index] = (*vertex_it)->X();
		vertex_array[index+1] = (*vertex_it)->Y();
		vertex_array[index+2] = (*vertex_it)->Z();
		index+=3;
	}

	index = 0;
	for(vector<Point*>::const_iterator normal_it = normal_list.begin(); normal_it != normal_list.end(); ++normal_it){					
		normal_array[index] = (*normal_it)->X();
		normal_array[index+1] = (*normal_it)->Y();
		normal_array[index+2] = (*normal_it)->Z();
		index+=3;
	}

	index = 0;
	for(vector<Point*>::const_iterator texture_it = texture_list.begin(); texture_it != texture_list.end(); ++texture_it){					
		texture_array[index] = (*texture_it)->X();
		texture_array[index+1] = (*texture_it)->Y();
		index+=2;
	}

	glGenBuffers(3, buffer); 
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffers_size[0] * 3, vertex_array, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffers_size[1] * 3, normal_array, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffers_size[2] * 2, texture_array, GL_STATIC_DRAW);

	free(vertex_array);
	free(normal_array);
  free(texture_array);
}

void Model::loadTexture(string texture_file){

	unsigned int t;
	unsigned char *texData;

    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1, &t);
	ilBindImage(t);
    if (!ilLoadImage((ILstring) texture_file.c_str())) {
        std::cout << ilGetError() << std::endl;
        exit(1);
    }
	this->image_width = ilGetInteger(IL_IMAGE_WIDTH);
	this->image_height = ilGetInteger(IL_IMAGE_HEIGHT);
  assert(image_width>0 && image_height>0);
   printf("id tex: %d %d\n", image_width, image_height);

	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);
      printf("id tex: %d\n",texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->image_width, this->image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Model::draw(){
    colour_component->draw();
    
  glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	if(buffers_size[1]){
		glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
		glNormalPointer(GL_FLOAT, 0, 0);
	}

	if(buffers_size[2]){
		glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
		glTexCoordPointer(2, GL_FLOAT, 0, 0); 
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	
	glEnable(GL_LIGHTING);
	glDrawArrays(GL_TRIANGLES, 0, buffers_size[0] * 3);
	glDisable(GL_LIGHTING);
  glBindTexture(GL_TEXTURE_2D, 0);
}

