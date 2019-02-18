/**
*   Programa para ilustrar:
*   - Uso da gluLookAt
*   - cullFace, frontFace, polygonMode
*   - Projecao pespectiva
*   - Interacao com o mouse/teclado
*
*   Autor: Cesar Tadeu Pozzer
*   UFSM - 24/06/2007
*
*   pozzer@inf.ufsm.br
*   pozzer3@gmail.com
*
**/

#include <GL/glut.h>
//#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#define SCREEN_X 500
#define SCREEN_Y 500

int   polygonMode = GL_FILL;
int   cullingMode = GL_BACK;
int   faceMode    = GL_CW;

float rx = 0, rz = 0;

GLfloat mat_diffuse[]    = { 1, 1, 1, 1 };
GLfloat light_position[] = { 1, 1, 1, 0 };
GLfloat light_difuse[]   = { 1, 0, 0 };  //RED

void init()
{
   float abertura = 50.0;
   float znear  = 1;
   float zfar   = 20;
   float aspect = 1;

   glShadeModel (GL_SMOOTH);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity( );
   gluPerspective(abertura, aspect, znear, zfar);
   glMatrixMode(GL_MODELVIEW);

   glClearColor(0, 0, 0, 1);

   //A face da frente eh desenhada em LINE e a de traz em FILL. Mudando o frontfacing, muda esta ordem
   glPolygonMode(GL_FRONT, GL_LINE);
   glPolygonMode(GL_BACK, GL_FILL);
   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   //remove as faces frontais de objetos renderizados com poligonos preenchidos
   glEnable(GL_CULL_FACE);
   glFrontFace(faceMode);
   glCullFace(cullingMode);

   glEnable(GL_DEPTH_TEST);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glMaterialfv(GL_FRONT, GL_DIFFUSE,  mat_diffuse);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_difuse);
}

////////////////////////////////////////////////////////////////////////////////////////
void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glLoadIdentity( );
   gluLookAt(0, 3, 3,  //from. Posicao onde a camera esta posicionada
             0, 0, 0,  //to. Posicao absoluta onde a camera esta vendo
             0, 1, 0); //up. Vetor Up.

   glRotatef ((GLfloat) rx, 0.0f, 1.0f, 0.0f);
   glRotatef ((GLfloat) rz, 1.0f, 0.0f, 0.0f);
   rx+=0.1;

   glColor3f(0, 0, 1);
   glutSolidTeapot(1.2);

   glutSwapBuffers();
}


//faz a leitura da entrada do usuario
void keyboard(unsigned char key, int x, int y)
{
   //printf("%c", key);
   key = tolower(key);
   switch(key)
   {
      case 27:
	     exit(0);
	  break;

      case 'c': //culling
         if( cullingMode == GL_FRONT )
            cullingMode = GL_BACK;
         else
            cullingMode = GL_FRONT;
         glCullFace(cullingMode);
         break;
      case 'f': //face mode
         if( faceMode == GL_CW )
            faceMode = GL_CCW;
         else
            faceMode = GL_CW;
         glFrontFace(faceMode);
         break;
   }
}

void MotionFunc(int x, int y)
{
   //float dx, dy;
   //printf("\nX = %d Y = %d", x, y);
   rx = x;
   rz = y;
}

////////////////////////////////////////////////////////////////////////////////////////
//int main (int argc, char **argv)
int main ()
{
   int  argc=0;
   //char *argv[1] = {"teste"};
   glutInit(&argc, NULL);

   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

   glutInitWindowSize (SCREEN_X, SCREEN_Y);
   glutInitWindowPosition (450, 10);
   /* create window */
   glutCreateWindow ("Culling - Front facing - polygon mode Demo");
   init();
   printf("Digite c, f para mudar os modos de culling e front_facing");

   glutDisplayFunc(display);
   glutMotionFunc(MotionFunc);
   glutIdleFunc(display);
   glutKeyboardFunc(keyboard);

   glutMainLoop();
   return 0;
}
