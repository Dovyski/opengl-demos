/**
 * Demonstrate the different configurations of face culling and
 * the use of depth sorting (z-buffer).
 *
 * Author: Mihalis Tsoukalos
 * Contributions: Fernando Bevilacqua
 */

#include <GL/glut.h>
#include <GL/gl.h>

// Global variables to control the rotation of the
// stripped cube according to user input.
GLfloat rX = -25.0;
GLfloat rY = 25.0;

void strippedCube()
{
	// The coordinates for the vertices of the cube
	GLfloat x = 0.3f;
	GLfloat y = 0.3f;
	GLfloat z = 0.3f;

	// BACK face
	glColor3f(0.4f, 0.3f, 0.5f);
	glBegin(GL_TRIANGLES);
		glVertex3f(x, y, z);
		glVertex3f(x, -y, z);
		glVertex3f(-x, y, z);
	glEnd();

	glColor3f(0.45f, 0.35f, 0.55f);
	glBegin(GL_TRIANGLES);
		glVertex3f(-x, -y, z);
		glVertex3f(x, -y, z);
		glVertex3f(-x, y, z);
	glEnd();

	// LEFT face
	glColor3f(0.3f, 0.5f, 0.6f);
	glBegin(GL_TRIANGLES);
		glVertex3f(-x, -y, -z);
		glVertex3f(-x, -y, z);
		glVertex3f(-x, y, -z);
	glEnd();

	glColor3f(0.35f, 0.55f, 0.65f);
	glBegin(GL_TRIANGLES);
		glVertex3f(-x, y, z);
		glVertex3f(-x, -y, z);
		glVertex3f(-x, y, -z);
	glEnd();

	// RIGHT face
	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(x, y, z);
		glVertex3f(x, y, -z);
		glVertex3f(x, -y, z);
	glEnd();

	glColor3f(0.25f, 0.25f, 0.25f);
	glBegin(GL_TRIANGLES);
		glVertex3f(x, -y, -z);
		glVertex3f(x, y, -z);
		glVertex3f(x, -y, z);
	glEnd();

	// BOTTOM face
	glColor3f(0.4f, 0.0f, 0.4f);
	glBegin(GL_TRIANGLES);
		glVertex3f(-x, -y, -z);
		glVertex3f(-x, -y, z);
		glVertex3f(x, -y, z);
	glEnd();

	glColor3f(0.45f, 0.05f, 0.45f);
	glBegin(GL_TRIANGLES);
		glVertex3f(x, -y, z);
		glVertex3f(-x, -y, -z);
		glVertex3f(x, -y, -z);
	glEnd();

	// FRONT face
	glColor3f(0.4f, 0.3f, 0.5f);
	glBegin(GL_TRIANGLES);
		glVertex3f(x, y, -z);
		glVertex3f(x, -y, -z);
		glVertex3f(-x, y, -z);
	glEnd();

	glColor3f(0.45f, 0.35f, 0.55f);
	glBegin(GL_TRIANGLES);
		glVertex3f(-x, -y, -z);
		glVertex3f(x, -y, -z);
		glVertex3f(-x, y, -z);
	glEnd();

  // TOP face
	glColor3f(0.4f, 0.0f, 0.4f);
	glBegin(GL_TRIANGLES);
		glVertex3f(x, y, z);
		glVertex3f(-x, y, z);
		glVertex3f(-x, y, -z);
	glEnd();

	glColor3f(0.45f, 0.05f, 0.45f);
	glBegin(GL_TRIANGLES);
		glVertex3f(x, y, -z);
		glVertex3f(-x, y, -z);
		glVertex3f(x, y, z);
	glEnd();
}

void display()
{
	// Set the background color
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	// Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Rotate according to user input (rX and rY)
	glRotatef(rX, 1.0f, 0.0f, 0.0f);
	glRotatef(rY, 0.0f, 1.0f, 0.0f);

	// Define which vertex faces should be culled out.
	// Possible options are:
	//   - GL_BACK: culls only the back faces.
	//   - GL_FRONT: culls only the front faces.
	//   - GL_FRONT_AND_BACK: culls both the front and back faces.
	glCullFace(GL_BACK);

	// Define the order of culling of faces. Possible options are:
	//  - GL_CCW: counter-clockwise ordering
	//  - GL_CW: clockwise ordering
	glFrontFace(GL_CW);

	// Render a cube.
	strippedCube();

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
	glutCreateWindow("Culling and z-buffer");

	// Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);

	// Enable face culling. When this is enabled, you can use
	// the functions glCullFace() and glFrontFace() to specify
	// how faces should be culled.
	glEnable(GL_CULL_FACE);

	// Callback functions
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);

	// Pass control to GLUT for events
	glutMainLoop();

	return 0;
}