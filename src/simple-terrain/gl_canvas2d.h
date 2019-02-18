#ifndef __CANVAS_2D__H__
#define __CANVAS_2D__H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#define PI_2 6.28318530717958


//funcoes da biblioteca
void point(float x, float y); //coordeandas do ponto
void line( float x1, float y1, float x2, float y2 ); //coordenadas da linha x1, y1, x2, y2

//desenha um retangulo alinhado nos eixos x e y
void rect( int x1, int y1, int x2, int y2 ); //coordenadas do retangulo x1, y1, x2, y2
void rectFill( int x1, int y1, int x2, int y2 ); //coordenadas do retangulo x1, y1, x2, y2

//desenha um poligono CONVEXO. Para um retangulo, deve-se passar 4 vertices
void polygon(float vx[], float vy[], int n_elems);
void polygonFill(float vx[], float vy[], int n_elems);

//centro e raio do circulo
void circle( int x, int y, int raio, int div );
void circleFill( int x, int y, int raio, int div );

//especifica a cor de desenho e de limpeza de tela
void color(float r, float g, float b);
void clear(float r, float g, float b);

//desenha texto
void text(int x, int y, const char *t);

//funcoes de gerenciamento da biblioteca (CALLBACKS)
void keyboard(int key);
void keyboardUp(int key);
void specialUp(int key);
void mouse(int bt, int st, int x, int y);
void render();
void mouseWheelCB(int wheel, int direction, int x, int y);


//funcao de inicializacao da Canvas2D. Recebe a largura e altura
void initCanvas(int w, int h);

//funcao para executar a Canvas2D
void runCanvas();


#endif
