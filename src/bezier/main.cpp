/**
*   Programa para ilustrar:
*   - Curva de Bezier
**/

#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <cmath>

void init()
{
	glClearColor(0,0,0,1);
}

double x[4] = {0, 1, 4, 5}, y[4] = {0, 4, 4, 0};

//renderiza o triangulo usando interpolacao de Gouraud
void render(){
   glLoadIdentity();
   glTranslated(-0.25, -0.2, 0.0);
   glScaled(0.2, 0.2, 0);
   glColor3f(1,1,0);
   glBegin(GL_POINTS);
      glVertex2d(x[0], y[0]);
      glVertex2d(x[1], y[1]);
      glVertex2d(x[2], y[2]);
      glVertex2d(x[3], y[3]);
   glEnd();
   glColor3f(1,1,1);
   glBegin(GL_POINTS);
      for (double t = 0; t < 1; t += 0.0001){
         double Xi = pow(1 - t, 3)*x[0] + 3*t*pow(1 - t, 2)*x[1] + 3*pow(t, 2)*(1 - t)*x[2] + pow(t, 3)*x[3];
         double Yi = pow(1 - t, 3)*y[0] + 3*t*pow(1 - t, 2)*y[1] + 3*pow(t, 2)*(1 - t)*y[2] + pow(t, 3)*y[3];
         glVertex2d(Xi, Yi);
      }   
   glEnd();
   
}

void display (void){
   glClear(GL_COLOR_BUFFER_BIT );
   render();
   glutSwapBuffers();
}

////////////////////////////////////////////////////////////////////////////////////////
int main (int argc, char* argv[])
{
	glutInit(&argc, argv);

	//glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize (600, 600);
	glutInitWindowPosition (250, 100);
	glutCreateWindow ("Exemplo com Curva de Bezier");

	init();

	glutDisplayFunc(render);
	glutIdleFunc(display);

	glutMainLoop();

	return 0;
}
