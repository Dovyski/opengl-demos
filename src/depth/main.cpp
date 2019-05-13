/**
 * This demo illustrates the use of depth buffer, i.e. z-sorting. After the application
 * is running, press keys 1, 2 or 3 to change the behavior of the depth testing function.
 *
 * Author: Guilherme Antunes da Silva
 * Contributions: Fernando Bevilacqua <fernando.bevilacqua@uffs.edu.br>
 * License: MIT
 */

#include <GL/glut.h>
#include <GL/gl.h>

// Constants to define the width/height of the window
const int WIDTH = 800;
const int HEIGHT = 800;

void renderCoordinateAxis()
{
	// X axis - green color
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
		// Left side, negative X
		glVertex2f(-10.0, 0.0);
		glVertex2f(0.0, 0.0);

		// Right side, positive X
		glVertex2f(0.0, 0.0);
		glVertex2f(10.0, 0.0);
	glEnd();

	// Y axis - blue color
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		// Top side, positive Y
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 10.0);

		// Bottom side, negative Y
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, -10.0);
	glEnd();
}

void renderScene()
{
	// Render a red cube
	glColor3f(1, 0, 0);
	glutSolidCube(4.0f);

	// Render a blue cube which is further in the z-axis.
	// When z-buffering is disabled, this cube will be rendered
	// in front of the red cube, despite the fact that it has
	// a position in the z axis that is further away.
	glTranslatef(5.5f, 0.0f, -5.0f);
	glColor3f(0, 0, 1);
	glutSolidCube(4.0f);

	// Render a green plan (floor). When z-buffering is disabled,
	// this plan will be rendered on top of everything, even if its
	// position in the z axis is very far away.
	glColor3f(0, 1, 0);
	glTranslatef(0.0f, -2.0f, -30.0f);
	glScalef(100.0f, 0.2f, 200.0f);
	glutSolidCube(1.0f);
}

void display()
{
	// Clear the screen painting it with the white color
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Inform we want to make changes to the modelview matrix, starting
	// with no transformation at all.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Move the camera away from the origin along the Z axis by 10 pixels.
	glTranslatef(0, 0, -10.0f);

	// Rotate everything by a few degrees around the Y axis.
	glRotatef(15.0f, 0.0f, 1.0f, 0.0f);

	// Render the X and Y axis to guide ourselves.
	renderCoordinateAxis();

	// Render a scene with two cubes and a floor in different z coordinates
	// to illustrate how z-sorting works.
	renderScene();

	// Start the rendering on a new frame
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) {
		// ESC key
		exit(0);
	} else if (key == '1') {
		glDepthFunc(GL_ALWAYS);
	} else if (key == '2') {
		glDepthFunc(GL_LESS);
	} else if (key == '3') {
		glDepthFunc(GL_NEVER);
	}
}

void initView()
{
	// We want a window to the world that is a rectangle starting at (0,0)
	// and ending at (WIDTH, HEIGHT).
	glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);
	
	// Adjust the global projection (camera)
	glMatrixMode(GL_PROJECTION);
	
	// Reset any existing projection settings and adjust the field-of-view (FOV)
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 200.0);
	
	// From now on, every transformation is to be applied on each object, e.g. modelview.
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	
	glutCreateWindow("Depth testing");
	
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);

	initView();

	// Enable the use of depth testing, i.e. z-sorting.
	// After enabled, depth testing can be controlled using
	// the function glDepthFunc().
	// 
	// Possible values for the glDepthFunc() are:
	//   GL_ALWAYS	   The depth test always passes.
	//   GL_NEVER      The depth test never passes.
	//   GL_LESS       Passes if the fragment's depth value is less than the stored depth value.
	//   GL_EQUAL      Passes if the fragment's depth value is equal to the stored depth value.
	//   GL_LEQUAL     Passes if the fragment's depth value is less than or equal to the stored depth value.
	//   GL_GREATER    Passes if the fragment's depth value is greater than the stored depth value.
	//   GL_NOTEQUAL   Passes if the fragment's depth value is not equal to the stored depth value.
	//   GL_GEQUAL     Passes if the fragment's depth value is greater than or equal to the stored depth value.
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	return 0;
}