/**
*   Programa para ilustrar:
*   - Funcoes da GLUT
*   - Gouraud Shading
*   - Flat Shading
*   - Transformacoes
*
*   Autor: Cesar Tadeu Pozzer
*   UFSM - 15/06/2007
*
*   pozzer@inf.ufsm.br
*   pozzer3@gmail.com
**/

#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include <stdlib.h>

void render();


int largura, altura;

int figura = 49;
float rotation = 0;
int keyPressed_1 = 0;
int keyPressed_2 = 0;

void reshape (int w, int h)
{
   largura = w;
   altura  = h;

   glViewport (0, 0, (GLsizei) w, (GLsizei) h);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluOrtho2D (0.0, (GLdouble) w, 0.0, (GLdouble) h);

   glMatrixMode(GL_MODELVIEW);
}

void init()
{
	glClearColor(1,1,1,1);
	glPolygonMode(GL_FRONT, GL_FILL);
}

//renderiza o triangulo usando interpolacao de Gouraud
void render()
{
   if( keyPressed_1 == 1 )
      printf("1");
   if( keyPressed_2 == 1 )
      printf("2");

   glLoadIdentity();


   glTranslated(largura/2, altura/2, 0);

   glRotated(rotation+=0.3, 0, 0, 1);


   //glTranslated(-largura/2, -altura/2, 0);

   if( figura == '1' )
   {
       glColor3f(1.0, 0.0, 0.0);  // red
       glBegin(GL_POINTS);
       for(int x=0; x< largura; x+=6)
       {
          for(int y=0; y< altura; y+=6)
          {
             glVertex2d(x, y);
           }
       }
       glEnd();
   }

   if( figura == '2' )
   {
       glShadeModel(GL_FLAT);
       //glShadeModel(GL_SMOOTH);   // default
       glBegin(GL_TRIANGLES);
    	   glColor3f(1.0, 0.0, 0.0);  // red
    	   glVertex2f(0, 0);
    	   glColor3f(0.0, 1.0, 0.0); // green
    	   glVertex2f(largura, 0);
    	   glColor3f(0.0, 0.0, 1.0); // blue
    	   glVertex2f(largura/2, altura);
       glEnd( );
   }
}

void display (void)
{
   glClear(GL_COLOR_BUFFER_BIT );
   render();
   glutSwapBuffers();
}

void up(unsigned char key, int x, int y)
{
    //printf("\n Liberou Tecla: %d" , key);
    if( key == 49 )
       keyPressed_1 = 0;
    if( key == 50 )
       keyPressed_2 = 0;

}

void keyboard(unsigned char key, int x, int y)
{
    //printf("\nTecla: %d" , key);

    if( key == 49 )
       keyPressed_1 = 1;
    if( key == 50 )
       keyPressed_2 = 1;

	switch(key)
	{
		case 27:
			exit(0);
		break;

		case 49: //tecla 2
			figura = key;
		break;

		case 50: //tecla 1
			figura = key;
		break;

		case 51: //tecla 3
            glutFullScreen();
		break;

		case 52: //tecla 4
			glutReshapeWindow(300,300);
	        glutPositionWindow(250, 100);
		break;
	}
}

void mouseMotionFunc(int x, int y)
{
   printf("\nMouse moveu: %d %d", x, y);
}

void mouseFunc(int button, int state, int x, int y)
{
   printf("\nMouse pressionado: botao %d  estado %d  (%d %d)", button, state, x, y);
}

void mouseWheelCB(int wheel, int direction, int x, int y)
{
	printf("\nMouseWheel: %d %d \n", x, y);
}

void entryFunc(int state)
{
   printf("\nMouse %d ", state);
}

void menuFunc(int id)
{
   printf("\nMenu selecionado: %d ", id);

}

////////////////////////////////////////////////////////////////////////////////////////
int main (int argc, char* argv[])
{
	glutInit(&argc, argv);

	//glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize (600, 600);
	glutInitWindowPosition (250, 100);
	glutCreateWindow ("GLUT: Pressione 1, 2, 3, 4 ou botao direito do mouse. ");

	init();

    glutReshapeFunc(reshape);
	glutDisplayFunc(render);

	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(up);
	glutMotionFunc(mouseMotionFunc);
	glutMouseFunc(mouseFunc);
	glutEntryFunc(entryFunc);
    glutMouseWheelFunc(mouseWheelCB);


    int sub = glutCreateMenu(menuFunc);
    glutAddMenuEntry("Submenu 1", 1);
    glutAddMenuEntry("Submenu 2", 2);

    int menu = glutCreateMenu(menuFunc);
    glutAddMenuEntry("Opcao 1", 3);
    glutAddMenuEntry("Opcao 2", 4);
    glutAddSubMenu("sub menu", sub);

    glutAttachMenu(GLUT_RIGHT_BUTTON);  //associa ao botao direito (0, 1, ou 2)

	glutIdleFunc(display);

	glutMainLoop();

	return 0;
}
