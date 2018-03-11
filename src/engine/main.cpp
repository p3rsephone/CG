#include "headers/main.h"

Engine* Engine::engine = 0;

int main(int argc, char **argv) {
  Engine* engine = Engine::getInstance();
  engine->parse(argc,argv);
  return 1;
}

