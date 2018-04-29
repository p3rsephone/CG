#include "headers/Model.h"
Model::Model(){
}

Model::Model(string name, int size){
  this->name = name;
  this->point_array = new float[size];
  this->buffer = new GLuint[1];
  this->state = 0;
  this->size = size;
}

void Model::addElement(float point){
  this->point_array[state] = point;
  state++;
}

float* Model::model(){
  return this->point_array;
}


void Model::prepare(){
  glGenBuffers(1,(this)->buffer);
  glBindBuffer(GL_ARRAY_BUFFER, *(this)->buffer);
  glBufferData(GL_ARRAY_BUFFER,this->size * sizeof(float),this->point_array,GL_STATIC_DRAW);
}

void Model::draw(){
  glBindBuffer(GL_ARRAY_BUFFER, (this)->buffer[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);

  if(!strcmp(this->name.c_str(),"sun.3d")){
    glColor3ub(255,140,0);
  }else if(!strcmp(this->name.c_str(),"mercury.3d")){
      glColor3ub(139,0,0);
  }else if(!strcmp(this->name.c_str(),"venus.3d")){
      glColor3ub(249,194,26);
  }else if(!strcmp(this->name.c_str(),"earth.3d")){
      glColor3ub(30,144,255);
  }else if(!strcmp(this->name.c_str(),"moon.3d")){
      glColor3ub(176,196,222);
  }else if(!strcmp(this->name.c_str(),"mars.3d")){
      glColor3ub(205,92,92);
  }else if(!strcmp(this->name.c_str(),"jupiter.3d")){
      glColor3ub(227,220,203);
  }else if(!strcmp(this->name.c_str(),"saturn.3d")){
      glColor3ub(216,202,157);
  }else if(!strcmp(this->name.c_str(),"neptune.3d")){
      glColor3ub(65,105,225);
  }else if(!strcmp(this->name.c_str(),"uranus.3d")){
      glColor3ub(100,149,237);
  }else if(!strcmp(this->name.c_str(),"pluto.3d")){
      glColor3ub(245,245,220);
  }else{
      glColor3ub(102,255,102);
  }

  glDrawArrays(GL_TRIANGLES,0,(this->size)-1);
}

