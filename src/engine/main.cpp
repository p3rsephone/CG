#include "headers/main.h"
#include <iostream>
using namespace std;

Scene* scene;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(0.0,0.0,5.0,
		      0.0,0.0,-1.0,
			  0.0f,1.0f,0.0f);
   scene->draw();
    glutSwapBuffers();
}


void initGL(int argc, char **argv){
// put GLUT init here
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE);

// put callback registration here
  glutInitWindowPosition(100,100);
  glutInitWindowSize(800,800);
  glutCreateWindow("Hello World !");

  glutDisplayFunc(renderScene);
  glutReshapeFunc(changeSize);
  glutIdleFunc(renderScene);

// OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f,0.0f,0.0f,0.0f);

// enter GLUT's main loop
	glutMainLoop();

}

int main(int argc, char **argv) {
  initGL(argc,argv);

  Point* p1 = new Point(7.5, 0, 7.5);
  Point* p2 = new Point(-7.5, 0, 7.5);
  Point* p3 = new Point(-7.5, 0, -7.5);
  Point* p4 = new Point(-7.5, 0, -7.5);
  Point* p5 = new Point(7.5, 0, -7.5);
  Point* p6 = new Point(7.5, 0, 7.5);

  Model* model = new Model();

  model->addElement(p1);
  model->addElement(p2);
  model->addElement(p3);
  model->addElement(p4);
  model->addElement(p5);
  model->addElement(p6);
  cout << "hello"<< endl;
  scene = new Scene();
  scene->addModel(model);

  return 1;
}

