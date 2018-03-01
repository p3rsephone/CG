#ifndef __MODEL_H__
#define __MODEL_H__
#include "headers/Element.h"
  class  Model{
    private:
      vector<Element*> elements_vector;
    public:
      Model();
      void addElement(Element*);
      vector<Element*> model();
};
#endif
