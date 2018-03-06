#include "headers/main.h"

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
	gluLookAt(30.0,30.0,0.0,
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
//    scene->draw();
    //glutWireTeapot(1);
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
  glPolygonMode(GL_FRONT, GL_FILL);

// enter GLUT's main loop
	glutMainLoop();

}

int main(int argc, char **argv) {
  srand(time(NULL));
  scene = new Scene();
  if(argc > 1) {
    Parser().ReadXML(scene, argv[1]);
  }
  //scene->addModel(model);
  initGL(argc,argv);
  return 1;
}

