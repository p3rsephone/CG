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

void Engine::buildRotMatrix(float *x, float *y, float *z, float *m) {

	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void Engine::cross(float *a, float *b, float *res) {

	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
}


void Engine::normalize(float *a) {

	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}


float Engine::length(float *v) {

	float res = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	return res;

}

void Engine::multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}

void Engine::getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

	// catmull-rom matrix
	float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f}};
	
	// Compute A = M * P
	float x[4] = {p0[0], p1[0], p2[0], p3[0]};
	float y[4] = {p0[1], p1[1], p2[1], p3[1]};
	float z[4] = {p0[2], p1[2], p2[2], p3[2]};
	
	float Ax[4], Ay[4], Az[4];
	multMatrixVector(*m, x, Ax);
	multMatrixVector(*m, y, Ay);
	multMatrixVector(*m, z, Az);
	
	// Compute pos = T * A
	float T[4] = {pow((double)t,3), pow((double)t,2), t, 1};
	pos[0] = T[0] * Ax[0] + T[1] * Ax[1] + T[2] * Ax[2] + T[3] * Ax[3];
	pos[1] = T[0] * Ay[0] + T[1] * Ay[1] + T[2] * Ay[2] + T[3] * Ay[3];
	pos[2] = T[0] * Az[0] + T[1] * Az[1] + T[2] * Az[2] + T[3] * Az[3];
	
	// compute deriv = T' * A
	float T_d[4] = {3*pow((double)t,2), 2*t, 1, 0};
	deriv[0] = T_d[0] * Ax[0] + T_d[1] * Ax[1] + T_d[2] * Ax[2] + T_d[3] * Ax[3];
	deriv[1] = T_d[0] * Ay[0] + T_d[1] * Ay[1] + T_d[2] * Ay[2] + T_d[3] * Ay[3];
	deriv[2] = T_d[0] * Az[0] + T_d[1] * Az[1] + T_d[2] * Az[2] + T_d[3] * Az[3];
	
}


// given  global t, returns the point in the curve
void Engine::getGlobalCatmullRomPoint(float gt, float *pos, float *deriv) {

	float t = gt * POINT_COUNT; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4]; 
	indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;	
	indices[1] = (indices[0]+1)%POINT_COUNT;
	indices[2] = (indices[1]+1)%POINT_COUNT; 
	indices[3] = (indices[2]+1)%POINT_COUNT;

	getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
}

void Engine::renderCatmullRomCurve() {
// desenhar a curva usando segmentos de reta - GL_LINE_LOOP
    int i = 0;

    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);

    for(i=0;i<100;i++)
    {
      float pos[3];
			float deriv[3];
			getGlobalCatmullRomPoint(i/100.f,pos,deriv);
			glVertex3f(pos[0],pos[1],pos[2]);
    }
    glEnd();
}

void Engine::translateRotateTeapot() {
	
	float M[16];
	float pos[3];
	float deriv[3];
	float Z[3];

	gtTeapot += 0.001;
	if (gtTeapot > 1) gtTeapot - 1;

	getGlobalCatmullRomPoint(gtTeapot, pos, deriv);
	glTranslatef(pos[0], pos[1], pos[2]);

	cross(deriv, Y, Z);
	cross(Z,deriv, Y);
	normalize(deriv);
	normalize(Z);
	normalize(Y);
	buildRotMatrix(deriv, Y, Z, M);
	glMultMatrixf(M);
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
	glPushMatrix();
		translateRotateTeapot();
		glutWireTeapot(1);
	glPopMatrix();
    //axis_system();

    glutSwapBuffers();
}

void  Engine::prepareWrapper(){
  Engine* e =  Engine::getInstance();
  e->prepare();
}

void Engine::prepare(){
  group->prepare();
	renderCatmullRomCurve();
}

void Engine::initGL(int argc, char **argv){

// put GLUT init here
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB| GLUT_MULTISAMPLE);
  glEnable(GL_MULTISAMPLE);
    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_POLYGON_SMOOTH );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );

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
	glEnableClientState(GL_VERTEX_ARRAY);

#ifndef _APPLE_
	glewInit();
#endif

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glPolygonMode(GL_FRONT, GL_LINE);

  prepareWrapper();
// enter GLUT's main loop
	glutMainLoop();

}


void Engine::parse(int argc, char **argv){
  if(argc == 2 && (strcmp(argv[1],"-h"))) {
    Parser().ReadXML(group, argv[1]);
    initGL(argc,argv);
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
