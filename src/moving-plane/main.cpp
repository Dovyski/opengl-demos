#include <GL/freeglut.h>
#include <iostream>

#include "Point.h"
using namespace std;

// global variables
static struct {
	// current parameters for controlling glulookat
	double alpha, beta, dist;
	// viewing mode state (depending on which mouse button is being used)
	enum { NONE, ROTATING, ZOOMING } viewingMode;
	// last mouse position
	int mouseX, mouseY;
	// current recursion for drawing the spheres
} globals;

// draw checkerboard floor
static void drawFloor(void)
{
	int n = 10;
	double x1 = 0, x2 = 10, y1 = 0, y2 = 10;
	double dx = (x2 - x1) / n, dy = (y2 - y1) / n;
	glBegin(GL_QUADS);

	// same normal for everything
	glNormal3d(0, 0, 1);

	for (int ix = 0; ix < n; ix++) {
		for (int iy = 0; iy < n; iy++) {
			if ((ix + iy) % 2)
				glColor3f(1, 1, 1);
			else
				glColor3f(1, 0, 0);
			
			glVertex3d(x1 + ix * dx, y1 + iy * dy, 0);
			glVertex3d(x1 + (ix + 1) * dx, y1 + iy * dy, 0);
			glVertex3d(x1 + (ix + 1) * dx, y1 + (iy + 1) * dy, 0);
			glVertex3d(x1 + ix * dx, y1 + (iy + 1) * dy, 0);
		}
	}

	glEnd();
}

// function called by GLUT whenever a redraw is needed
static void display()
{
	// clear the window with the predefined color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// setup viewing transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	double r = globals.dist;
	double a = globals.alpha * M_PI / 180.0;
	double b = globals.beta * M_PI / 180.0;
	Point p(r * cos(a) * cos(b), r*sin(a)*cos(b), r*sin(b));
	Point c(5, 5, 1.5);
	p = p + c;

	GLfloat lightPos[] = { 10.0, 10.0, 10.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	gluLookAt(p.x(), p.y(), p.z(), c.x(), c.y(), c.z(), 0, 0, 1);

	drawFloor();

	// make sure everything gets drawn
	glFlush();
}

// we recompute projection matrix on every resize, and reset the viewport
static void resizeCB(int w, int h)
{
	// setup perspective transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, double(w) / h, 0.1, 100);
	//glOrtho(-10.0, 10.0, -10.0, 10.0, 5, 100);

	glViewport(0, 0, w, h);
}

// when mouse button is clicked, we determine which viewing mode to
// initialize and also remember where the mouse was clicked
static void mouseClickCB(int button, int state, int x, int y)
{
	globals.mouseX = x;
	globals.mouseY = y;
	
	if (state == GLUT_UP) {
		globals.viewingMode = globals.NONE;
	}
	else if (button == GLUT_LEFT_BUTTON) {
		globals.viewingMode = globals.ROTATING;
	}
	else if (button == GLUT_MIDDLE_BUTTON) {
		globals.viewingMode = globals.ZOOMING;
	}
	else {
		globals.viewingMode = globals.NONE;
	}
}

// when user drags the mouse, we either rotate or zoom
static void mouseMotionCB(int x, int y)
{
	int dx = x - globals.mouseX;
	int dy = y - globals.mouseY;
	globals.mouseX = x;
	globals.mouseY = y;

	if (globals.viewingMode == globals.ROTATING) {
		globals.alpha -= dx / 10.0;
		globals.beta += dy / 10.0;
		if (globals.beta < -80) globals.beta = -80;
		if (globals.beta > 80) globals.beta = 80;
		glutPostRedisplay();
	}
	else if (globals.viewingMode == globals.ZOOMING) {
		globals.dist = std::max(1.0, globals.dist - dy / 10.0);
		glutPostRedisplay();
	}
}

static void init(){
	globals.alpha = 30;
	globals.beta = 30;
	globals.dist = 10;
	globals.viewingMode = globals.NONE;

	// initial window size
	glutInitWindowSize(800, 600);

	// what buffers we need
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB
		| GLUT_MULTISAMPLE | GLUT_DEPTH);

	// create a window
	glutCreateWindow("MD2 Viewer");

	// register callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(resizeCB);
	glutMouseFunc(mouseClickCB);
	glutMotionFunc(mouseMotionCB);

	// use black as the background color
	glClearColor(0, 0, 0, 0);

	// enable depth buffer
	glEnable(GL_DEPTH_TEST);

	// this is for drawing transparencies
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// enable antialiasing (just in case)
	//    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);

	// enable lighting
	glEnable(GL_LIGHTING);

	// enable use of glColor() to specify ambient & diffuse material properties
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	// set some common light & material properties, which don't have to
	// be re-specified later
	glEnable(GL_LIGHT0);
	GLfloat ambientLight[] = { 0.1, 0.1, 0.1, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	GLfloat specularColor[] = { 0.7, 0.7, 0.7, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularColor);
	GLfloat shininess[] = { 95.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	// since we are going to use scaling, and possibly non-uniform, we'll
	// ask OpenGL to re-normalize our normals
	glEnable(GL_NORMALIZE);
}

// main function
int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	init();
	glutMainLoop();
	return 0;
}