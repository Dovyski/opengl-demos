/**
 * Example program illustrating a simple use of lighting. Creates six spheres of different
 * fully saturated colors.  Adds a white light that slow rotates around the spheres.
 *
 * Author: Samuel R. Buss
 * Contributions: Fernando Bevilacqua <fernando.bevilacqua@uffs.edu.br>
 *
 * Software is "as-is" and carries no warranty.  It may be used without
 *   restriction, but if you modify it, please change the filenames to
 *   prevent confusion between different versions.
 * Bug reports: Sam Buss, sbuss@ucsd.edu.
 * Web page: http://math.ucsd.edu/~sbuss/MathCG
 *
 * USAGE:
 *    Press "r" key to toggle (off and on) running the animation
 *    Press "s" key to single-step animation
 *    The up arrow key and down array key control the
 *         time step used in the animation rate.  This will
 *         speed up or slow down the rate at which the light
 *         revolves around the spheres.
 *     Press ESCAPE to exit.
 */

#include <math.h>      // For math routines (such as sqrt & trig).
#include <stdio.h>
#include <stdlib.h>      // For the "exit" function
#include <GL/glut.h>   // OpenGL Graphics Utility Library


// Values that control the material properties.
float Noemit[4] = { 0.0, 0.0, 0.0, 1.0 };
float SphShininess = 50;   // Specular exponent for the spheres.
float SphAmbDiff[6][4] = {      // The ambient/diffuse colors of the six spheres 
   {0.5, 0.0, 0.0, 1.0},         // Red
   {0.5, 0.5, 0.0, 1.0},         // Yellow
   {0.0, 0.5, 0.0, 1.0},         // Green
   {0.0, 0.5, 0.5, 1.0},         // Cyan
   {0.0, 0.0, 0.5, 1.0},         // Blue
   {0.5, 0.0, 0.5, 1.0}         // Magenta
};
float SphSpecular[4] = { 1, 1, 1, 1.0 };

// Lighting values
float ambientLight[4] = { 0.2, 0.2, 0.2, 1.0 };
float Lt0amb[4] = { 0.3, 0.3, 0.3, 1.0 };
float Lt0diff[4] = { 1.0, 1.0, 1.0, 1.0 };
float Lt0spec[4] = { 1.0, 1.0, 1.0, 1.0 };

float zeroPos[4] = { 0, 0, 0, 1 };         // Origin (homogeneous representation)
float dirI[4] = { 1, 0, 0, 0 };            // Direction of unit vector I (point at infinity)

int LightIsPositional = 0;

int RunMode = 1;      // Used as a boolean (1 or 0) for "on" and "off"

// The next global variable controls the animation's state and speed.
float CurrentAngle = 0.0f;         // Angle in degrees
float AnimateStep = 0.5f;         // Rotation step per update

/*
* Handles the animation and the redrawing of the
* graphics window contents.
*/
void display(void)
{
	int i;

	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (RunMode == 1) {
		// Calculate animation parameters
		CurrentAngle += AnimateStep;
		if (CurrentAngle > 360.0) {
			CurrentAngle -= 360.0*floor(CurrentAngle / 360.0);   // Don't allow overflow
		}
	}

	// Rotate the image
	glMatrixMode(GL_MODELVIEW);         // Current matrix affects objects positions
	glLoadIdentity();                  // Initialize to the identity

	// Position the light (before drawing the illuminated objects)
	glPushMatrix();
	glRotatef(CurrentAngle, 0.0, 0.0, 1.0);      // Rotate through animation angle
	glTranslatef(7.0, 0.0, 0.0);               // Translate rotation center to origin
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Lt0spec);   // Make sphere glow (emissive)
	glutSolidSphere(0.3, 5, 5);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Noemit);   // Turn off emission

	if (LightIsPositional == 1) {
		glLightfv(GL_LIGHT0, GL_POSITION, zeroPos);   // Position is transformed by ModelView matrix
	}
	else {
		glLightfv(GL_LIGHT0, GL_POSITION, dirI);      // Direction is transformed by ModelView matrix
	}
	glPopMatrix();

	// Draw six spheres of different colors
	for (i = 0; i < 6; i++) {
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, SphAmbDiff[i]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SphSpecular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, SphShininess);
		glPushMatrix();
		glRotatef(60.0*(float)i, 0.0, 0.0, 1.0);   // Rotate each one another 60 degrees
		glTranslatef(2.5, 0.0, 0.0);
		glutSolidSphere(1.0, 20, 20);
		glPopMatrix();
	}
	// Flush the pipeline, swap the buffers
	glFlush();
	glutSwapBuffers();

	if (RunMode == 1) {
		glutPostRedisplay();   // Trigger an automatic redraw for animation
	}

}

// glutKeyboardFunc is called below to set this function to handle
//      all "normal" key presses.
void myKeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 'r':
		RunMode = 1 - RunMode;      // Toggle to opposite value
		if (RunMode == 1) {
			glutPostRedisplay();
		}
		break;
	case 's':
		RunMode = 1;
		display();
		RunMode = 0;
		break;
	case 'l':                  // Toggle local light mode
		LightIsPositional = 1 - LightIsPositional;
		if (RunMode == 0) {
			display();
		}
		break;
	case 27:   // Escape key
		exit(1);
	}
}

// glutSpecialFunc is called below to set this function to handle
//      all "special" key presses.  See glut.h for the names of
//      special keys.
void mySpecialKeyFunc(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		if (AnimateStep < 5.0) {         // Don't let speed get very big.
			AnimateStep *= sqrt(2.0);      // Increase the angle increment
		}
		break;
	case GLUT_KEY_DOWN:
		if (AnimateStep > 1.0e-3) {      // Avoid underflow problems.
			AnimateStep /= sqrt(2.0);   // Decrease the angle increment
		}
		break;
	}
}

// Initialize OpenGL's rendering modes
void initRendering()
{
	glEnable(GL_DEPTH_TEST);   // Depth testing must be turned on

	glEnable(GL_LIGHTING);      // Enable lighting calculations
	glEnable(GL_LIGHT0);      // Turn on light #0.

	// Set global ambient light
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	// Light 0 light values.  Its position is set in drawScene().
	glLightfv(GL_LIGHT0, GL_AMBIENT, Lt0amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Lt0spec);
}

// Called when the window is resized
//      w, h - width and height of the window in pixels.
void resizeWindow(int w, int h)
{
	float viewWidth = 7.0;         // Actually this is half of the width
	float viewHeight = 7.0;         // Again, this is half of the height
	glViewport(0, 0, w, h);
	h = (h == 0) ? 1 : h;
	w = (w == 0) ? 1 : w;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (h < w) {
		viewWidth *= (float)w / (float)h;
	}
	else {
		viewHeight *= (float)h / (float)w;
	}
	glOrtho(-viewWidth, viewWidth, -viewHeight, viewHeight, -1.0, 1.0);
}

// Main routine
// Set up OpenGL, define the callbacks and start the main loop
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	// We're going to animate it, so double buffer 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Window position (from top corner), and size (width% and hieght)
	glutInitWindowPosition(10, 60);
	glutInitWindowSize(360, 360);
	glutCreateWindow("Light spheres");

	// Initialize OpenGL parameters.
	initRendering();

	// Set up callback functions for key presses
	glutKeyboardFunc(myKeyboardFunc);         // Handles "normal" ascii symbols
	glutSpecialFunc(mySpecialKeyFunc);      // Handles "special" keyboard keys

	// Set up the callback function for resizing windows
	glutReshapeFunc(resizeWindow);

	// Call this for background processing
	glutIdleFunc(display);

	// Call this whenever window needs redrawing
	glutDisplayFunc(display);

	fprintf(stdout, "Arrow keys control speed.  Press \"r\" to run,  \"s\" to single step.\n");

	// Start the main loop.  glutMainLoop never returns.
	glutMainLoop();

	return 0;
}