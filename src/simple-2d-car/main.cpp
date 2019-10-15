
/**
 * A simple OpenGL program that draws a simple 2d car
 *
 * Date: Tuesday 15 October 2019
 */

#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

#define PI 3.415926535897932384626433832795


void drawHeadlights() {
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	double angle = 0.0f; //Car Headlight
	for (angle = 0.0f; angle <= 90; angle += 0.01f) { // BASICLY MAKES AN 90 DEGREE LINE 
		double rad = PI * angle / 180;	//SPECIAL THANKS TO -> Clickmit Wg
		glVertex3f(.75f + .125f * cos(rad), .225f + .125f * sin(rad), 0.0f); // stackoverflow.com/questions/10570359/how-do-i-draw-an-half-circle-in-opengl/13206574
	}//Car Headlight
	glEnd();
	glPopMatrix();
}


void DDcar() { //CREATES A 2D CAR
	glTranslatef(-.125f, 0, 0);	//MOVE THE CAR A LITTLE BACKWARDS TO MAKE THE FRONT PART

	glPushMatrix();
	glColor3f(1, 0, 0);

	glPushMatrix();
	glTranslatef(.5f, 0, 0);	//FRONT WHEEL
	glScalef(.25f, .25f, 0);
	glBegin(GL_LINE_STRIP);	//NUMBER OF VORTEXS BELLOW (16) BY DEFAULT				
	for (double i = 0; i < 2 * PI; i += PI / 16) //DRAWS A POLYGON WITH 16 VORTEXS
		glVertex3f(cos(i) * .5f, sin(i) * .5f, 0.0); // THE RADIUS OF THE CIRCLE IS 0.5f
	glEnd();						// REALIZE THAT I SCALE IT ABOVE
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-.5f, 0, 0);	// BACK WHEEL
	glScalef(.25f, .25f, 0);
	glBegin(GL_LINE_STRIP);
	for (double i = 0; i < 2 * PI; i += PI / 16) // SPECIAL THANKS TO DSB FROM
		glVertex3f(cos(i) * .5f, sin(i) * .5f, 0.0); // community.khronos.org/t/drawing-circles-in-opengl/50790/2
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_LINES);		// CAR LOWER PART			
	glVertex3f(.375f, 0, 0);
	glVertex3f(-.375f, 0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_LINES);	// CAR LOWER-BACK PART
	glVertex3f(-.625, 0, 0);
	glVertex3f(-.65f, 0, 0);
	glVertex3f(-.65f, 0, 0);
	glVertex3f(-.75f, .125f, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_LINES);	// CAR BACK PART
	glVertex3f(-.75, .125f, 0);
	glVertex3f(-.75f, .35f, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_LINES);	// CAR BACK-UPPER PART
	glVertex3f(-.75f, .35f, 0);
	glVertex3f(-.375, .6f, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_LINES);	// CAR UPPER PART
	glVertex3f(-.375, .6f, 0);
	glVertex3f(.175f, .6f, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_LINES);	// CAR FRONT-UPPER PART
	glVertex3f(.175f, .6f, 0);	// WINDSHIELD
	glVertex3f(.475, .4f, 0);	// WINDSHIELD
	glVertex3f(.475, .4f, 0);	// HOOD
	glVertex3f(.75, .35f, 0);	// HOOD
	glEnd();
	glPopMatrix();

	glPushMatrix(); // HEADLIGHTS CREATION AND POSITIONING
	glTranslatef(.38f, .175f, 0);
	glScalef(.5f, .5f, 0);
	drawHeadlights(); // FUNCTION CREATED ABOVE
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_LINES);	// CAR LOWER-FRONT PART
	glVertex3f(.625f, 0, 0);
	glVertex3f(.75f, 0, 0);
	glVertex3f(.75f, 0, 0);
	glVertex3f(.82f, .025f, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();	//CAR FRONT PART
	glBegin(GL_LINES);
	glVertex3f(.82f, .025f, 0);
	glVertex3f(.82f, .285f, 0);
	glEnd();
	glPopMatrix();

	glEnd();
	glPopMatrix();
}


void display()
{
	// Set Background Color
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	// Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	glRotatef(-45, 1, 1, 1);
	DDcar();

	glFlush();
	glutSwapBuffers();
}

void keyboard(int key, int x, int y)
{/*
	if (key == GLUT_KEY_RIGHT) {
		rY += 5;
	}
	else if (key == GLUT_KEY_LEFT) {
		rY -= 5;
	}
	else if (key == GLUT_KEY_DOWN) {
		rX -= 5;
	}
	else if (key == GLUT_KEY_UP) {
		rX += 5;
	}
	// Request display update
	glutPostRedisplay();*/
}


int main(int argc, char** argv)
{
	// Initialize GLUT and process user parameters
	glutInit(&argc, argv);

	// Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);

	// Create window
	glutCreateWindow("OpenGL Cube");

	// Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);

	// Callback functions
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);

	// Pass control to GLUT for events
	glutMainLoop();

	return 0;
}