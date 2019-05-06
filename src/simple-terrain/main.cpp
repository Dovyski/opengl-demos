/**
*   Autor: Cesar Tadeu Pozzer
*   UFSM - 15/06/2016
*
*   pozzer@inf.ufsm.br
*   pozzer3@gmail.com
*
**/


#include "superficie.h"

#include "gl_canvas2d.h"

#define DIM_TELA 600


Superficie *s;

void init()
{
   s = new Superficie();
}

////////////////////////////////////////////////////////////////////////////////////////
void render(void)
{
   color(1,0,0);

   s->transforma();
   s->render();
}


int main(void)
{
   init();

   initCanvas(DIM_TELA, DIM_TELA);

   runCanvas();

}

