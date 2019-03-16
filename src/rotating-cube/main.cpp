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

void display()
{
	// Set Background Color
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	// Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Rotate when user changes rX and rY
	glRotatef(rX, 1.0f, 0.0f, 0.0f);
	glRotatef(rY, 0.0f, 1.0f, 0.0f);

	// BACK
	glColor3f(0.4f, 0.3f, 0.5f);
	glBegin(GL_TRIANGLES);
		glVertex3f(x, y, z);
		glVertex3f(x, -y, z);
		glVertex3f(-x, y, z);
	glEnd();

	glColor3f(0.5f, 0.3f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(-x, -y, z);
		glVertex3f(x, -y, z);
		glVertex3f(-x, y, z);
	glEnd();

	// FRONT
	// Using 4 trianges!
	glColor3f(0.1f, 0.5f, 0.3f);
	glBegin(GL_TRIANGLES);
		glVertex3f(-x, y, -z);
		glVertex3f(0, 0, -z);
		glVertex3f(-x, -y, -z);
	glEnd();

	glColor3f(0.0f, 0.5f, 0.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f(-x, -y, -z);
		glVertex3f(0, 0, -z);
		glVertex3f(x, -y, -z);
	glEnd();

	glColor3f(0.1f, 0.3f, 0.3f);
	glBegin(GL_TRIANGLES);
		glVertex3f(-x, y, -z);
		glVertex3f(x, y, -z);
		glVertex3f(0, 0, -z);
	glEnd();

	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(0, 0, -z);
		glVertex3f(x, y, -z);
		glVertex3f(x, -y, -z);
	glEnd();

	// LEFT
	glColor3f(0.3f, 0.5f, 0.6f);
	glBegin(GL_TRIANGLES);
		glVertex3f(-x, -y, -z);
		glVertex3f(-x, -y, z);
		glVertex3f(-x, y, -z);
	glEnd();

	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_TRIANGLES);
		glVertex3f(-x, y, z);
		glVertex3f(-x, -y, z);
		glVertex3f(-x, y, -z);
	glEnd();

	// RIGHT
	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(x, y, z);
		glVertex3f(x, y, -z);
		glVertex3f(x, -y, z);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f(x, -y, -z);
		glVertex3f(x, y, -z);
		glVertex3f(x, -y, z);
	glEnd();

	// TOP
	glColor3f(0.6f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f(x, y, z);
		glVertex3f(x, y, -z);
		glVertex3f(-x, y, -z);
	glEnd();

	glColor3f(0.6f, 0.1f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(-x, y, z);
		glVertex3f(x, y, z);
		glVertex3f(-x, y, -z);
	glEnd();

	// BOTTOM
	glColor3f(0.4f, 0.0f, 0.4f);
	glBegin(GL_TRIANGLES);
		glVertex3f(-x, -y, -z);
		glVertex3f(-x, -y, z);
		glVertex3f(x, -y, z);
	glEnd();

	glColor3f(0.3f, 0.0f, 0.3f);
	glBegin(GL_TRIANGLES);
		glVertex3f(x, -y, -z);
		glVertex3f(-x, -y, -z);
		glVertex3f(x, -y, z);
	glEnd();

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