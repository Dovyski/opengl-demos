/**
 * A simple OpenGL program that draws a colorful cube
 * that rotates as you move the arrow keys.
 *
 * Author: Mihalis Tsoukalos
 * Date: Wednesday 04 June 2014
 */

#include <GL/glut.h>
#include <GL/gl.h>


// Rotate X
GLfloat rX = 0;
// Rotate Y
GLfloat rY = 0;

// The coordinates for the vertices of the cube
GLfloat x = 0.3f;
GLfloat y = 0.3f;
GLfloat z = 0.3f;

void torre(){
	glPushMatrix();
	
	glColor3f(1,1,1);

	glPushMatrix();
		glScalef(.5f,.5f,.5f); //Topo 1
		glTranslatef(-.375f, .875f,-.375f);
		glutWireCube(.25);
	glPopMatrix();

	glPushMatrix();
		glScalef(.5f,.5f,.5f);
		glTranslatef(.375f, .875f, .375f);
		glutWireCube(.25);
	glPopMatrix();

	glPushMatrix();
		glScalef(.5f,.5f,.5f);
		glTranslatef(-.375f,.875f,.375f);
		glutWireCube(.25);
	glPopMatrix();

	glPushMatrix();
		glScalef(.5f,.5f,.5f);
		glTranslatef(.375f, .875f,-.375f);
		glutWireCube(.25);
	glPopMatrix();

	glPushMatrix();
		glScalef(1.f,1.5f,1.f);
		glutWireCube(.5);
	glPopMatrix();

	glPushMatrix();
		glScalef(1.5f,0.25f,1.5f);
		glTranslatef(0,-1.25f,0);
		glutWireCube(.5);
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
	
	glRotatef(-45,1,1,1);
	torre();

	glFlush();
	glutSwapBuffers();
}

void keyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_RIGHT) {
		rY += 5;
	} else if (key == GLUT_KEY_LEFT) {
		rY -= 5;
	} else if (key == GLUT_KEY_DOWN) {
		rX -= 5;
	} else if (key == GLUT_KEY_UP) {
		rX += 5;
	}

	// Request display update
	glutPostRedisplay();
}


int main(int argc, char **argv)
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