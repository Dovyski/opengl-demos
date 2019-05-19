/**
 * Demonstrate the use of textures.
 */

#include <GL/glut.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "Bmp.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define RECT_SIZE 5

GLuint texture_id;
Bmp *texture_bmp;
unsigned char *texture_data;
GLuint texture_id2;
Bmp *texture_bmp2;
unsigned char *texture_data2;

float ang = 0;

void buildTextures()
{
   glGenTextures( 1, &texture_id );
   glBindTexture( GL_TEXTURE_2D, texture_id );

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   glTexImage2D(GL_TEXTURE_2D,
                0,
                GL_RGB,
                texture_bmp->getWidth(),
                texture_bmp->getHeight(),
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                texture_data);

   glGenTextures(1, &texture_id2);
   glBindTexture(GL_TEXTURE_2D, texture_id2);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   glTexImage2D(GL_TEXTURE_2D,
                0,
                GL_RGB,
                texture_bmp2->getWidth(),
                texture_bmp2->getHeight(),
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                texture_data2);
}

void display(void)
{
   float aperture = 35;
   float znear = 1;
   float zfar= 400;

   ang += 1;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity( );
   gluPerspective(aperture, SCREEN_WIDTH/SCREEN_HEIGHT, znear, zfar);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // CAIXA   
   glScalef(5, 5, 5);
   glTranslated(-RECT_SIZE / 2, -RECT_SIZE / 2, -40);
   glRotated(ang, 0, 0, 1);
   glRotated(ang, 0, 1, 0);
   glRotated(15, 1, 0, 0);

   glBindTexture(GL_TEXTURE_2D, texture_id);

   glBegin(GL_QUADS);
      // EH NECESSARIO COLOCAR AS COORDENADAS (S, T, R) OU (S, T) DA TEXTURA PARA CADA UM DOS VERTICES
      // PARA ESTE CASO, PODE-SE UTILIZAR O glTexCoord2f() POIS ESTAMOS MAPEANDO SOMENTE UMA FIGURA 2D => MUDAR FICA A CARGO DO LEITOR
	   glTexCoord3f(0, 0, 0); glVertex3f(0, 0, 0);
	   glTexCoord3f(1, 0, 0); glVertex3f(RECT_SIZE, 0, 0);
	   glTexCoord3f(1, 1, 0); glVertex3f(RECT_SIZE, RECT_SIZE, 0);
	   glTexCoord3f(0, 1, 0); glVertex3f(0, RECT_SIZE, 0);

	   glTexCoord3f(0, 0, 0); glVertex3f(RECT_SIZE, 0, RECT_SIZE);
	   glTexCoord3f(1, 0, 0); glVertex3f(RECT_SIZE, RECT_SIZE, RECT_SIZE);
	   glTexCoord3f(1, 1, 0); glVertex3f(RECT_SIZE, RECT_SIZE, 0);
	   glTexCoord3f(0, 1, 0); glVertex3f(RECT_SIZE, 0, 0);

	   glTexCoord3f(0, 0, 0); glVertex3f(0, 0, RECT_SIZE);
	   glTexCoord3f(1, 0, 0); glVertex3f(0, RECT_SIZE, RECT_SIZE);
	   glTexCoord3f(1, 1, 0); glVertex3f(0, RECT_SIZE, 0);
	   glTexCoord3f(0, 1, 0); glVertex3f(0, 0, 0);
	   
	   glTexCoord3f(0, 0, 0); glVertex3f(0, 0, RECT_SIZE);
	   glTexCoord3f(1, 0, 0); glVertex3f(RECT_SIZE, 0, RECT_SIZE);
	   glTexCoord3f(1, 1, 0); glVertex3f(RECT_SIZE, RECT_SIZE, RECT_SIZE);
	   glTexCoord3f(0, 1, 0); glVertex3f(0, RECT_SIZE, RECT_SIZE);

      glTexCoord3f(0, 0, 0); glVertex3f(0, 0, 0);
	   glTexCoord3f(1, 0, 0); glVertex3f(0, 0, RECT_SIZE);
	   glTexCoord3f(1, 1, 0); glVertex3f(RECT_SIZE, 0, RECT_SIZE);
	   glTexCoord3f(0, 1, 0); glVertex3f(RECT_SIZE, 0, 0);

      glTexCoord3f(0, 0, 0); glVertex3f(0, RECT_SIZE, 0);
	   glTexCoord3f(1, 0, 0); glVertex3f(0, RECT_SIZE, RECT_SIZE);
	   glTexCoord3f(1, 1, 0); glVertex3f(RECT_SIZE, RECT_SIZE, RECT_SIZE);
	   glTexCoord3f(0, 1, 0); glVertex3f(RECT_SIZE, RECT_SIZE, 0);
   glEnd();

   // FUNDO
   glLoadIdentity();
   glTranslated(-90, -80, -250);
   glScalef(8, 8, 8);

   glBindTexture(GL_TEXTURE_2D, texture_id2);
   glBegin(GL_QUADS);
      glTexCoord3f(0, 0, 0); glVertex3f(0, 0, 0);
      glTexCoord3f(1, 0, 0); glVertex3f(5 * RECT_SIZE, 0, 0);
      glTexCoord3f(1, 1, 0); glVertex3f(5 * RECT_SIZE, 5 * RECT_SIZE, 0);
      glTexCoord3f(0, 1, 0); glVertex3f(0, 5 * RECT_SIZE, 0);
   glEnd();

   glutSwapBuffers();
}

void init()
{
	glClearColor(0, 0, 0, 1);

	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LESS);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

   texture_bmp = new Bmp("madeira.bmp");
   texture_bmp->convertBGRtoRGB();
	texture_data = texture_bmp->getImage();

   texture_bmp2 = new Bmp("ceu.bmp");
   //texture_bmp2->convertBGRtoRGB();
   // TAVA FICANDO TUDO VERMELHO AQUI => IMAGEM DE EXEMPLO DEVE SER RUIM
	texture_data2 = texture_bmp2->getImage();

	if (texture_data != NULL && texture_data2 != NULL) {
		glEnable(GL_TEXTURE);
		glEnable(GL_TEXTURE_2D);
		buildTextures();
	}
}


int main (int argc, char *argv[])
{
   glutInit(&argc, argv);

   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
   glutInitWindowSize (SCREEN_WIDTH, SCREEN_HEIGHT);
   glutCreateWindow ("Texture simple");

   init();

   glutDisplayFunc(display);
   glutIdleFunc(display);

   glutMainLoop();
   return 0;
}
