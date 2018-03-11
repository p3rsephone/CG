#include "headers/Engine.h"

Engine::Engine(){
  srand(time(NULL));
  this->scene = new Scene();
}

Engine* Engine::getInstance(){
  if(engine == 0){
    engine = new Engine();
  }
  return engine;
}

void Engine::changeSizeWrapper(int w, int h) {
  Engine* e = Engine::getInstance();
  e->changeSize(w,h);
}

void Engine::changeSize(int w, int h) {

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

void Engine::axis_system(){
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glBegin(GL_LINES);
		glColor3f(1.0,0.0,0.0);
		glVertex3f(0,0,0);
		glVertex3f(30,0,0);

		glColor3f(0.0,1.0,0.0);
		glVertex3f(0,0,0);
		glVertex3f(0,30,0);

		glColor3f(0.0,1.0,1.0);
		glVertex3f(0,0,0);
		glVertex3f(0,0,30);
	glEnd();
}

void Engine::processKeysWrapper(unsigned char key, int xx, int yy) {
  Engine* e = Engine::getInstance();
  e->processKeys(key,xx,yy);
}
void Engine::processKeys(unsigned char key, int xx, int yy) {
		switch(key){
			case('a'):
				alfa-=0.1;
				break;
			case('d'):
				alfa+=0.1;
				break;
			case('w'):
				if(beta < 1.5) beta+=0.1;
				break;
			case('s'):
				if(beta > -1.5) beta-=0.1;
				break;
			case('+'):
				raio+=0.2;
				break;
			case('-'):
				raio-=0.2;
				break;
			case('c'):
				camera++;
				break;
			default:
				break;
		}
	glutPostRedisplay();
}

void Engine::specialKeysWrapper(int key, int xx, int yy) {
  Engine* e = Engine::getInstance();
  e->specialKeys(key,xx,yy);
}

void Engine::specialKeys(int key, int xx, int yy)
{
		float fraction = 1.0f;

			switch(key){
				case GLUT_KEY_LEFT :
					angle -= 0.1f;
					lx = sin(angle);
					lz = -cos(angle);
					break;
				case GLUT_KEY_RIGHT :
					angle += 0.1f;
					lx = sin(angle);
					lz = -cos(angle);
					break;
				case GLUT_KEY_UP :
					x += lx * fraction;
					z += lz * fraction;
					break;
				case GLUT_KEY_DOWN :
					x -= lx * fraction;
					z -= lz * fraction;
					break;
				default:
					break;
			}
		glutPostRedisplay();
}

void Engine::renderSceneWrapper(void) {
  Engine* e = Engine::getInstance();
  e->renderScene();
}

void Engine::renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	if(camera%2==0){
		gluLookAt(raio*cos(beta)*sin(alfa),raio*sin(beta),raio*cos(beta)*cos(alfa),
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
	}
	else{
		gluLookAt(	x, 1.0f, z,
			x+lx, 1.0f,  z+lz,
			0.0f, 1.0f,  0.0f);
	}
//    scene->draw();
    //glutWireTeapot(1);
    scene->draw();
		axis_system();

    glutSwapBuffers();
}


void Engine::initGL(int argc, char **argv){
// put GLUT init here
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE);

// put callback registration here
  glutInitWindowPosition(100,100);
  glutInitWindowSize(800,800);
  glutCreateWindow("Hello World !");

  glutDisplayFunc(renderSceneWrapper);
  glutReshapeFunc(changeSizeWrapper);
  glutIdleFunc(renderSceneWrapper);

// event handler
	glutKeyboardFunc(processKeysWrapper);
	glutSpecialFunc(specialKeysWrapper);
// OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
  glPolygonMode(GL_FRONT, GL_FILL);

// enter GLUT's main loop
	glutMainLoop();

}


void Engine::parse(int argc, char **argv){
  if(argc > 1) {
    Parser().ReadXML(scene, argv[1]);
  }
  //scene->addModel(model);
  initGL(argc,argv);
}
