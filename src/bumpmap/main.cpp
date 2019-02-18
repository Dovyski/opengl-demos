/**
*   Programa para ilustrar:
*   - iluminacao Difusa sem o uso do GL

*   Autor: Cesar Tadeu Pozzer
*   UFSM - 13/07/2007
*
*   pozzer@inf.ufsm.br
*   pozzer3@gmail.com
*
**/


//-----------------------------------------------------------------
//EXERCICIO:
// ADICIONE A ILUMINACAO ESPECULAR
// PERMITA QUE O USUARIO POSSA MOVER A POSICAO DO OBSERVADOR
// FACA A COMBINACAO DA ILUMINACAO ESPECULAR COM A DIFUSA
//-----------------------------------------------------------------

#include <GL/glut.h>
//#include <GL/freeglut_ext.h> //callback da wheel do mouse.


#include "lighting_sem_gl_vector.h"
#include <stdio.h>

#define KD 1

Vector normal, light, viewer;
float ang=0;
int cont=0;

void init()
{
   glClearColor(1,0,0,1);
   glShadeModel(GL_SMOOTH);

   normal.x = 0;
   normal.y = 1;
   normal.z = 0;

   light.x = 200;
   light.y = 100;
   light.z = 200;
}

float ilumina_difusa(Vector pos, int flag)
{
   float shift_x = cos(pos.x/2.0);

   Vector tmp = light - pos;
   tmp.normalize();

   //bump mapping
   Vector bump = normal;
   bump.x += shift_x;
   bump.normalize();

   if( flag ==1 )
      return KD * bump.dot(tmp);
   else
      return KD * normal.dot(tmp);
}

void display (void)
{
   glClear(GL_COLOR_BUFFER_BIT );

   cont++;
   int flag = 0;
   if( cont < 100 )
      flag = 1;
   else if( cont < 200 )
      flag = 0;
   else
      cont = 0;

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluOrtho2D (0, 400, 0, 400);
   glMatrixMode(GL_MODELVIEW);

   glBegin(GL_POINTS);

   for(int x=100; x<300; x++)
   for(int z=100; z<300; z++)
   {
      float cor = ilumina_difusa( Vector(x, 0, z), flag );
      glColor3f(cor, cor, cor);
      glVertex2d(x, z);
   }
   glEnd();

   //move a fonte luminosa
   float x, z;
   x = 100 * cos(ang);
   z = 100 * sin(ang);
   light.x = x + 200;
   light.z = z + 200;
   ang+=0.03;

   glutSwapBuffers();
}

int main (int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (400, 400);
	glutInitWindowPosition (250, 100);
	glutCreateWindow ("Iluminação Difusa sem GL" );
	init();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}
