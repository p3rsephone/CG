#include "headers/Engine.h"

Engine::Engine(){
  srand(time(NULL));
  this->group = new Group();
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
	gluPerspective(45.0f,ratio,1.0f,1000.0f);

	// Return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

/*
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
 */
void Engine::processKeysWrapper(unsigned char key, int xx, int yy) {
  Engine* e = Engine::getInstance();
  e->processKeys(key,xx,yy);
}

void Engine::processKeys(unsigned char key, int xx, int yy) {
	switch(key){
		case('q'):
			ly+= 0.1f;
			break;
		case('e'):
			ly-= 0.1f;
			break;
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
		case('-'):
			raio+=1;
			break;
		case('+'):
			raio-=1;
			break;
		case('c'):
			camera++;
			break;
    case('j'):
			glPolygonMode(GL_FRONT, GL_POINT);
      break;
    case('l'):
			glPolygonMode(GL_FRONT, GL_FILL);
      break;
    case('k'):
			glPolygonMode(GL_FRONT, GL_LINE);
      break;
        case(' '):
            if(pause%2==0){
                glutIdleFunc(NULL);
            }else {
                glutIdleFunc(renderGroupWrapper);
            }
            pause++;
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
					y += ly * fraction;
					break;
				case GLUT_KEY_DOWN :
					x -= lx * fraction;
					z -= lz * fraction;
					y -= ly * fraction;
					break;
				default:
					break;
			}
		glutPostRedisplay();
}

void Engine::renderGroupWrapper(void) {
  Engine* e = Engine::getInstance();
  e->renderGroup();
}

void Engine::renderGroup(void) {

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
		gluLookAt(	x, y, z,
			x+lx, y+ly ,  z+lz,
			0.0f, 1.0f,  0.0f);
	}
  group->draw();
    //axis_system();

    glutSwapBuffers();
}

void  Engine::prepareWrapper(){
  Engine* e =  Engine::getInstance();
  e->prepare();
}

void Engine::prepare(){
  group->prepare();
}

void Engine::initGL(int argc, char **argv){

// put GLUT init here
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);

// put callback registration here
  glutInitWindowPosition(100,100);
  glutInitWindowSize(1400,1000);
  glutCreateWindow("Grupo 28");

  glutDisplayFunc(renderGroupWrapper);
  glutReshapeFunc(changeSizeWrapper);
  glutIdleFunc(renderGroupWrapper);

// event handler
  glutKeyboardFunc(processKeysWrapper);
	glutSpecialFunc(specialKeysWrapper);



#ifndef __APPLE__
	glewInit();
#endif
	//  OpenGL settings
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);



}


void Engine::parse(int argc, char **argv){
  if(argc == 2 && (strcmp(argv[1],"-h"))) {
    initGL(argc,argv);
   	
	Parser().ReadXML(group, argv[1]);
  prepareWrapper();
// enter GLUT's main loop
	glutMainLoop();
  }else{
    usage();
  }
}

void Engine::usage(){
    cout << "#_____________________________ HELP _____________________________#" << endl;
	cout << "|                                                                |" << endl;
    cout << "|   SYNOPSIS                                                     |" << endl;
    cout << "|          ./engine {XML FILE}                                   |" << endl;
	cout << "|                      [-h]                                      |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   COMMANDS INSIDE ENGINE:                                      |" << endl;
	cout << "| -> a, b, w, s                                                  |" << endl;
	cout << "|      Normal camera movement                                    |" << endl;
	cout << "|                                                                |" << endl;
	cout << "| -> Arrow UP, DOWN, LEFT, RIGHT                                 |" << endl;
	cout << "|      FPS camera movement                                       |" << endl;
	cout << "|                                                                |" << endl;
	cout << "| -> c                                                           |" << endl;
	cout << "|      Change camera mode                                        |" << endl;
	cout << "|                                                                |" << endl;
	cout << "| -> +, -                                                        |" << endl;
	cout << "|      Zoom in, out                                              |" << endl;
	cout << "|                                                                |" << endl;
	cout << "| -> j,l,k                                                       |" << endl;
	cout << "|      Change glPolygonMode {Point,Fill,Line}                    |" << endl;
	cout << "|                                                                |" << endl;
    cout << "#________________________________________________________________#" << endl;
}
