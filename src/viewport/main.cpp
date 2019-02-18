/**
*   Programa para ilustrar:
*   - Uso da Viewport
*   - Gouraud Shading
*   - Projecao ortográfica 2D

*   Autor: Cesar Tadeu Pozzer
*   UFSM - 15/06/2007
*
*   pozzer@inf.ufsm.br
*   pozzer3@gmail.com
*
**/

#include <GL/glut.h>
//#include <GL/freeglut_ext.h> //callback da wheel do mouse.

float ang = 0;

void reshape (int w, int h)
{
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluOrtho2D (-200, 200, -200, 200);
   glMatrixMode(GL_MODELVIEW);
}

void init()
{
   glClearColor(1,1,1,1);
   glShadeModel(GL_SMOOTH);
}

void renderBox()
{
   glLoadIdentity();
   //glTranslated(130,0,0);
   glRotatef(ang+=0.1, 0,0,1);
   //glTranslated(120,0,0);
   glBegin(GL_POLYGON);
      glColor3f(1,0,0);
      glVertex2f(-150, -150);
      glColor3f(1,1,0);
      glVertex2f(150, -150);
      glColor3f(0,0,1);
      glVertex2f(150, 150);
      glColor3f(0,1,1);
      glVertex2f(-150, 150);
   glEnd();
}

//renderiza 4 retangulos em viewports diferentes
void display (void)
{
   glClear(GL_COLOR_BUFFER_BIT );

   glViewport (200, 200, 200, 200);
   renderBox();

   glViewport (0,200, 200, 200);
   renderBox();

   glViewport (0, 0, 400, 200);
   renderBox();

   glViewport (100, 100, 200, 200);
   renderBox();

   glutSwapBuffers();
}

int main (int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (400, 400);
	glutInitWindowPosition (250, 100);
	glutCreateWindow ("Teste de ViewPort" );
	init();
    glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}
