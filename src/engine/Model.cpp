#include "headers/Model.h"
using namespace std;

Model::Model(){
}

Model::Model(string name, int size){
  this->name = name;
  this->point_array = new float[size];
  this->state = 0;
}

void Model::addElement(float point){
  this->point_array[state] = point;
  state++;
}

float* Model::model(){
  return this->point_array;
}

void Model::draw(){
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
    glColor3ub(this->color1, this->color2, this->color3);
  }
  glBindBuffer(GL_ARRAY_BUFFER, this->point_array);
  glBufferData(GL_ARRAY_BUFFER,this->size,this->point_array.GL_STATI_DRAW);
  glDrawArray(GL_TRIANGLES,0,this->size);
}

