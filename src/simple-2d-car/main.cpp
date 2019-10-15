
/**
 * A simple OpenGL program that draws a simple 2d car
 *
 * Author: Otávio Secco
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
	for (angle = 0.0f; angle <= 90; angle += 0.01f) {
		double rad = PI * angle / 180;	//SPECIAL THANKS TO -> Clickmit Wg
		glVertex3f(.75f + .125f * cos(rad), .225f + .125f * sin(rad), 0.0f); // stackoverflow.com/questions/10570359/how-do-i-draw-an-half-circle-in-opengl/13206574
	}//Car Headlight
	glEnd();
	glPopMatrix();
}


void DDcar() { //Creates the Car
	glTranslatef(-.125f, 0, 0);	//MOVE THE CAR A LITTLE BACKWARDS TO MAKE THE FRONT PART

	glPushMatrix();
	glColor3f(1, 0, 0);

		glPushMatrix();
		glTranslatef(.5f, 0, 0);	//Front wheel
		glScalef(.25f, .25f, 0);
		glBegin(GL_LINE_STRIP);	//Number of vortexs: V				
		for (double i = 0; i < 2 * PI; i += PI / 16) //Draws a poligon with 16 vortexs
			glVertex3f(cos(i) * .5f, sin(i) * .5f, 0.0); // The radius of the circle is 5.f
		glEnd();											 // Notice that I Scale it above
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-.5f, 0, 0);	//Back Whell
		glScalef(.25f, .25f, 0);
		glBegin(GL_LINE_STRIP);
		for (double i = 0; i < 2 * PI; i += PI / 16) // Special thanks to DSB from
			glVertex3f(cos(i) * .5f, sin(i) * .5f, 0.0); // community.khronos.org/t/drawing-circles-in-opengl/50790/2
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glBegin(GL_LINES);		// Car lower part			
		glVertex3f(.375f, 0, 0);
		glVertex3f(-.375f, 0, 0);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glBegin(GL_LINES);	// Car lower back part
		glVertex3f(-.625, 0, 0);
		glVertex3f(-.65f, 0, 0);
		glVertex3f(-.65f, 0, 0);
		glVertex3f(-.75f, .125f, 0);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glBegin(GL_LINES);	// Car back part
		glVertex3f(-.75, .125f, 0);
		glVertex3f(-.75f, .35f, 0);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glBegin(GL_LINES);	// Car back-upper part
		glVertex3f(-.75f, .35f, 0);
		glVertex3f(-.375, .6f, 0);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glBegin(GL_LINES);	// Car upper part
		glVertex3f(-.375, .6f, 0);
		glVertex3f(.175f, .6f, 0);
		glEnd();
		glPopMatrix();

		glPushMatrix();
			glBegin(GL_LINES);	// Car front - upper part
			glVertex3f(.175f, .6f, 0);
			glVertex3f(.475, .4f, 0);	// windshield
			glVertex3f(.475, .4f, 0);
			glVertex3f(.75, .35f, 0);	// hood
			glEnd();
		glPopMatrix();

		glPushMatrix(); // Headlights creation and position
			glTranslatef(.38f, .175f, 0);	
			glScalef(.5f, .5f, 0);
			drawHeadlights(); // FUNCTION CREATED ABOVE
		glPopMatrix();

		glPushMatrix();
			glBegin(GL_LINES);	// Car lower front part
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
	DDDcar();

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
