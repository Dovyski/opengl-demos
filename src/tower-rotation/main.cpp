/**
 * This demo shows how to periodically call an update() function to create
 * animations over time. In this case, the animation is to rotate a red square.
 *
 * Author: Fernando Bevilacqua <fernando.bevilacqua@uffs.edu.br>
 * License: MIT
 */

#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>

// Constants to define the width/height of the window
const int WIDTH = 800;
const int HEIGHT = 800;

// Define how many frames per seconds we want our
// applications to run.
const unsigned int FRAMES_PER_SECOND = 30;
const unsigned int UPDATE_INTERVAL_MS = 1000 / FRAMES_PER_SECOND;

// Control the angle to rotate the red square
float angle = 0;

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

void torre(){
	glPushMatrix();
		glScalef(3, 3, 3);
	//Cubos da base de cima da torre
		glPushMatrix();
			glColor3f(0., 0., 0.);
			glTranslatef(0.0, 0.0, 0.14);
			glTranslatef(0.0, 0.75, 0.0);
			glutSolidCube(0.08);
		glPopMatrix();

		glPushMatrix();
			glColor3f(0., 0., 0.);
			glTranslatef(0.0, 0.0, -0.14);
			glTranslatef(0.0, 0.75, 0.0);
			glutSolidCube(0.08);
		glPopMatrix();

		glPushMatrix();
			glColor3f(0., 0., 0.);
			glTranslatef(-0.14, 0.0, 0.0);
			glTranslatef(0.0, 0.75, 0.0);
			glutSolidCube(0.08);
		glPopMatrix();

		glPushMatrix();
			glColor3f(0., 0., 0.);
			glTranslatef(0.14, 0.0, 0.0);
			glTranslatef(0.0, 0.75, 0.0);
			glutSolidCube(0.08);
		glPopMatrix();

	//Base de cima
		glPushMatrix();
			glColor3f(0., 0., 0.);
			glScalef(0.45, 0.45, 0.45);
			glTranslatef(0.0, 1.45, 0.0);
			glRotatef(90, 0, 0, 1);
			glRotatef(90, 0, 1, 0);
			glutSolidTorus(0.20, 0.25, 10, 10);
		glPopMatrix();

	//Corpo meio
		glPushMatrix();
			glColor3f(0., 0., 0.);
			glTranslatef(0.0, 0.4, 0.0);
			glScalef(.4, 1.2, .4);
			glutSolidCube(0.5);
		glPopMatrix();


	//Bases de baixo
		glPushMatrix();
			glColor3f(0., 0., 0.);
			glScalef(0.45, 0.45, 0.45);
			glTranslatef(0.0, 0.2, 0.0);
			glRotatef(90, 0, 0, 1);
			glRotatef(90, 0, 1, 0);
			glutSolidTorus(0.20, 0.25, 10, 10);
		glPopMatrix();

		glPushMatrix();
			glColor3f(0., 0., 0.);
			glScalef(0.5,0.5,0.5);
			glTranslatef(0.0, 0.0, 0.0);
			glRotatef(90, 0, 0, 1);
			glRotatef(90, 0, 1, 0);
			glutSolidTorus(0.20, 0.25, 10, 10);
		glPopMatrix();
	glPopMatrix();
	
}

void display()
{	
	// Clear the screen painting it with the white color
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Inform we want to make changes to the modelview matrix, starting
	// with no transformation at all.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Move the camera away from the origin along the Z axis by 10 pixels.
	glTranslatef(0, 0, -10.0f);

	// Render the X and Y axis to guide ourselves.
	renderCoordinateAxis();

	glRotatef(angle, 0, 1, 0);

	glPushMatrix();
		glTranslatef(5, 0 ,0);
		torre();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-5, 0 ,0);
		torre();
	glPopMatrix();


	glutSwapBuffers();
}

void update(int value)
{
	// Update the angle of rotation
	angle += 1;

	// Request a new frame rendering
	glutPostRedisplay();

	// Re-schedule the update() function to be called after a few
	// milliseconds again.
	glutTimerFunc(UPDATE_INTERVAL_MS, update, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) {
		// ESC key
		exit(0);
	}
}

void mouse(int button, int state, int x, int y)
{
	std::cout << "Mouse pressed: button=" << button << ", state=" << state << ", x=" << x << " y=" << y << std::endl;
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Transformation - Simple");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	initView();

	// Schedule the update() function to be called after a few
	// milliseconds (calculated as 1000 milliseconds divided by FPS).
	glutTimerFunc(UPDATE_INTERVAL_MS, update, 0);

	glutMainLoop();
	return 0;
}