/**
*   Programa para ilustrar:
*   - Uso da Material
*   - Gouraud Shading
*   - Projecao ortográfica

*   Autor: Cesar Tadeu Pozzer
*   UFSM - 15/06/2007
*
*   pozzer@inf.ufsm.br
*   pozzer3@gmail.com
*
**/

#include "GL/glut.h"
#include <math.h>
#include <stdio.h>

float angObj   = 0;
float angLight = 0;

GLfloat mat_specular[] = { 1, 1, 1, 1 };
GLfloat mat_shininess[] = { 10 };

GLfloat light_0_position[] = { 1, 1, 1, 0};
GLfloat light_0_difuse[]   = { 1, 0, 0 };  //RED
GLfloat light_0_specular[] = { 0, 0, 1 };  //WHITE
GLfloat light_0_ambient[]  = { 0.2, 0.2, 0.2 };

GLfloat light_1_position[] = { 1, 1, 1, 0 };
GLfloat light_1_difuse[]   = { 0, 1, 0 };  //GREEN
GLfloat light_1_specular[] = { 1, 1, 1 };  //WHITE
GLfloat light_1_ambient[]  = { 0.2, 0.2, 0.2 };


void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);

   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

   glLightfv(GL_LIGHT0, GL_POSITION, light_0_position);
   glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_0_difuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light_0_specular);
   glLightfv(GL_LIGHT0, GL_AMBIENT,  light_0_ambient);

   glLightfv(GL_LIGHT1, GL_POSITION, light_1_position);
   glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_1_difuse);
   glLightfv(GL_LIGHT1, GL_SPECULAR, light_1_specular);
   glLightfv(GL_LIGHT1, GL_AMBIENT,  light_1_ambient);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);

   glEnable(GL_DEPTH_TEST);
}

void display(void)
{
     Sleep(3);
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glLoadIdentity();

   glPushMatrix();
   glTranslated(4,0,0);
   glRotated(angObj+=0.1, 1, 1, 1);
   //glLightfv(GL_LIGHT1, GL_POSITION, light_1_position);

   glutSolidCube (5);
   glPopMatrix();


   glPushMatrix();
   glTranslated(-4,0,0);
   glRotated(angObj+=0.1, 1, 1, 0);
   glutSolidSphere (3.0, 20, 16);
   glPopMatrix();

   //muda a posicao da fonte luminosa
   light_0_position[0] = cos(angLight)*9; //x
   light_0_position[1] = sin(angLight)*9; //y
   light_0_position[2] = 0; //z
   light_0_position[3] = 0; //w
   angLight+=0.004;

   light_1_position[0] = cos(angLight/2.2)*9; //x
   light_1_position[1] = sin(angLight/2.2)*9; //y
   light_1_position[2] = 0; //z
   light_1_position[3] = 0; //w

   glPushMatrix();
   glTranslated(100,0,1000);
   //posiciona a fonte luminosa
   glLightfv(GL_LIGHT0, GL_POSITION, light_0_position);
   glLightfv(GL_LIGHT1, GL_POSITION, light_1_position);
   glPopMatrix();

   //desenha a fonte
   glTranslated(light_0_position[0], light_0_position[1],light_0_position[2]);
   glutSolidSphere (1.0, 20, 16);

   glLoadIdentity();
   glTranslated(light_1_position[0], light_1_position[1],light_1_position[2]);
   glutSolidSphere (1.0, 20, 16);
    /* */
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   glOrtho (-10, 10,  -10,10,  -10.0, 10.0);  //projecao ortografica

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
   if( key == 'w')
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   else
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char** argv)
{
   printf("Digite w ou outra letra para mudar o modo de visualizacao");
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (600, 600);
   glutInitWindowPosition (100, 100);
   glutCreateWindow("Iluminação. Pressione W ou outra tecla");
   init ();
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutIdleFunc(display);
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}

