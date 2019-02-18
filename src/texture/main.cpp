/**
*   Programa para ilustrar:
*   - Uso da textura
*   - carregamento de arquivos BMP

*   Autor: Cesar Tadeu Pozzer
*   UFSM - 15/06/2007
*
*   pozzer@inf.ufsm.br
*   pozzer3@gmail.com
*
**/

#include <GL/glut.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "Bmp.h"

#define SCREEN_X 900
#define SCREEN_Y 300

#define RECT_SIZE 10
#define TEXT_COORD 2

#define MAX_TEXTURES 3


Bmp *img1;
unsigned char *data;
GLuint textureID[MAX_TEXTURES];

float ang=0;

void buildTextures();


void init()
{
   glClearColor(0, 0, 0, 1);

   glShadeModel(GL_SMOOTH);
   glDepthFunc(GL_LESS);

   glEnable(GL_DEPTH_TEST);
   glDisable(GL_CULL_FACE);

   img1 = new Bmp("data/img3.bmp");
   img1->convertBGRtoRGB();
   data = img1->getImage();

   if( data != NULL )
   {
      glEnable(GL_TEXTURE);
      glEnable(GL_TEXTURE_2D);

      buildTextures();
   }
}

void buildTextures()
{
   //----------------------------------------------------------------------------------
   //GL_REPEAT e mipmap
   glGenTextures( 1, &textureID[0] );
   glBindTexture( GL_TEXTURE_2D, textureID[0] );

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   gluBuild2DMipmaps(GL_TEXTURE_2D,
                     GL_RGB,
                     img1->getWidth(),
                     img1->getHeight(),
                     GL_RGB,
                     GL_UNSIGNED_BYTE,
                     data);

   //----------------------------------------------------------------------------------
   //GL_CLAMP e glTextImage2D. Soh aceita texturas em potencia de 2.
   glGenTextures( 1, &textureID[1] );
   glBindTexture( GL_TEXTURE_2D, textureID[1] );

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   glTexImage2D(GL_TEXTURE_2D,
                0,
                GL_RGB,
                img1->getWidth(),
                img1->getHeight(),
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data);

   //----------------------------------------------------------------------------------
   //geracao automatica de coordenadas
   glGenTextures( 1, &textureID[2] );
   glBindTexture( GL_TEXTURE_2D, textureID[2] );

   float escala = 1.0 / 10;
   float p1[4] = { escala, 0,      0, 0 };
   float p2[4] = { 0,      escala, 0, 0 };
   glTexGenfv(GL_S, GL_OBJECT_PLANE, p1);
   glTexGenfv(GL_T, GL_OBJECT_PLANE, p2);

   glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
   glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   gluBuild2DMipmaps(GL_TEXTURE_2D,
                     GL_RGB,
                     img1->getWidth(),
                     img1->getHeight(),
                     GL_RGB,
                     GL_UNSIGNED_BYTE,
                     data);
}

////////////////////////////////////////////////////////////////////////////////////////
void display(void)
{
   float abertura = 35;
   float znear  = 1;
   float zfar   = 200;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity( );
   gluPerspective(abertura, SCREEN_X/SCREEN_Y, znear, zfar);

   glMatrixMode(GL_MODELVIEW);

   int dx = -60;
   for(int i=0; i<MAX_TEXTURES; i++)
   {
      glLoadIdentity( );
      glTranslated(dx,0,-120);
      glRotated(ang+=0.1, 0,1,0);
      glScalef(5,5,5);
      glTranslated(-RECT_SIZE/2,-RECT_SIZE/2,0);
      dx+=60;

	  glBindTexture( GL_TEXTURE_2D, textureID[i] );

      if( i < MAX_TEXTURES-1 )
      {
         glDisable(GL_TEXTURE_GEN_S);
         glDisable(GL_TEXTURE_GEN_T);
         glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex3f(0, 0, 0);

            glTexCoord2f(TEXT_COORD, 0);
            glVertex3f(RECT_SIZE, 0, 0);

            glTexCoord2f(TEXT_COORD, TEXT_COORD);
            glVertex3f(RECT_SIZE, RECT_SIZE, 0);

            glTexCoord2f(0, TEXT_COORD);
            glVertex3f(0, RECT_SIZE, 0);
         glEnd();
      }
      else    //com geracao automatica de coordenadas e textura
      {
         glEnable(GL_TEXTURE_GEN_S);
         glEnable(GL_TEXTURE_GEN_T);
         glBegin(GL_QUADS);
            glVertex3f(0, 0, 0);
            glVertex3f(RECT_SIZE, 0, 0);
            glVertex3f(RECT_SIZE, RECT_SIZE, 0);
            glVertex3f(0, RECT_SIZE, 0);
         glEnd();
         //glutSolidTeapot(2);
      }
   }

   glutSwapBuffers();
}

////////////////////////////////////////////////////////////////////////////////////////
int main (int argc, char *argv[])
{
   glutInit(&argc, argv);

   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

   glutInitWindowSize (SCREEN_X, SCREEN_Y);
   glutInitWindowPosition (50, 50);
   glutCreateWindow ("Texture Demo");
   init();

   glutDisplayFunc(display);
   glutIdleFunc(display);

   glutMainLoop();
   return 0;
}
