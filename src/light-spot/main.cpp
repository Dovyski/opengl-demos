/**
*   Programa para ilustrar:
*   - Iluminacao Spot
*   - Uso da gluLookAt
*   - Pilha de transformacoes
*   - Projecao pespectiva

*   Autor: Cesar Tadeu Pozzer
*   UFSM - 15/06/2007
*
*   pozzer@inf.ufsm.br
*   pozzer3@gmail.com
*
**/

#include <GL/glut.h>
#include <stdlib.h>
#include <ctype.h>

#define SCREEN_X 500
#define SCREEN_Y 500

GLfloat mat_specular[] = { 1, 1, 1, 1 };
GLfloat mat_diffuse[] = { 1, 1, 1, 1 };
GLfloat mat_shininess[] = { 10 };

GLfloat light_0_position[] = { 0, 8, 0, 1 };  //em cima da origem
GLfloat light_0_direction[] = {0, -1, 0};   //para a origem

GLfloat light_0_difuse[]   = { 1, 0, 0 };
GLfloat light_0_specular[] = { 0, 0, 1 };
GLfloat light_0_ambient[]  = { 0.2, 0.2, 0.2 };
GLint   light_0_cutoff     = 4; //angulo de abertura. Max eh 180.

float rx = 0, rz = 0;

void init()
{
   float abertura = 45.0;
   float znear  = 1;
   float zfar   = 20;
   float aspect = 1;

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity( );
   gluPerspective(abertura, aspect, znear, zfar);
   glMatrixMode(GL_MODELVIEW);
   glShadeModel(GL_SMOOTH);

   glClearColor(0, 0, 0, 1);

   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_specular);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  mat_diffuse);
   //glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);


   glLightfv(GL_LIGHT0, GL_POSITION,       light_0_position);
   glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_0_direction);

   glLightfv(GL_LIGHT0, GL_DIFFUSE,        light_0_difuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR,       light_0_specular);
   glLightfv(GL_LIGHT0, GL_AMBIENT,        light_0_ambient);
   glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,    light_0_cutoff);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   glEnable(GL_DEPTH_TEST);
}

////////////////////////////////////////////////////////////////////////////////////////
void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glLoadIdentity( );
   gluLookAt(0, 0, 3,  //from. Posicao onde a camera esta posicionada
             0, 0, 0,  //to. Posicao absoluta onde a camera esta vendo
             0, 1, 0); //up. Vetor Up.

   //a luz sofre transformacao apenas do lookat
   glLightfv(GL_LIGHT0, GL_POSITION,       light_0_position);
   glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_0_direction);

   //transformacao dos modelos
   glRotatef ((GLfloat) rx, 0.0f, 1.0f, 0.0f);
   glRotatef ((GLfloat) rz, 1.0f, 0.0f, 0.0f);
   glScalef(0.2, 0.2, 0.2);
   glTranslatef(-5, 0, -5);

   //a luz sofre transformacao da cena. Com isso fica presa ao objeto
   //glLightfv(GL_LIGHT0, GL_POSITION,       light_0_position);
   //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_0_direction);



   glNormal3f(0,1,0);

   glBegin(GL_QUADS);
   int x=0, z=0;
   for(x=0; x<10; x++)
      for(z=0; z<10; z++)
      {
         glVertex3f(x,   0, z);
         glVertex3f(x,   0, z+1);
         glVertex3f(x+1, 0, z+1);
         glVertex3f(x+1, 0, z);
      }
   glEnd();

   glPushMatrix();
      glTranslated(4, 1, 4);
      glutSolidTeapot(2);
   glPopMatrix();

   glutSwapBuffers();
}


//faz a leitura da entrada do usuario
void keyboard(unsigned char key, int x, int y)
{
   key = tolower(key);
   switch(key)
   {
      case 27:
	     exit(0);
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
int main (int argc, char **argv)
{
   glutInit(&argc, argv);

   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

   glutInitWindowSize (SCREEN_X, SCREEN_Y);
   glutInitWindowPosition (450, 10);
   /* create window */
   glutCreateWindow ("Iluminacao Spot");
   init();

   glutDisplayFunc(display);
   glutMotionFunc(MotionFunc);
//   glutMouseFunc(MouseFunc);
   glutIdleFunc(display);
   glutKeyboardFunc(keyboard);

   glutMainLoop();
   return 0;
}
