#ifndef __VERTEX_H__
#define __VERTEX_H__

class Element{
  private:
    float x;
    float y;
    float z;

  public:
    Element();
    Element(float,float,float);
    float x(void){return x;}
    float y(void){return y;}
    float z(void){return z;}
};
#endif
