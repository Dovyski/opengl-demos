/**
*   Autor: Cesar Tadeu Pozzer
*   UFSM - 15/06/2016
*
*   pozzer@inf.ufsm.br
*   pozzer3@gmail.com
*
**/

#define DIM 20

#include <math.h>
#include <time.h>

#include "gl_canvas2d.h"

class Ponto
{
    public:
    float x, y, z;
};

class Superficie
{
   Ponto mat[DIM+1][DIM+1]; //COORDENADAS originais centradas na origem

   Ponto transf[DIM+1][DIM+1]; //coordenadas transformadas para exibicao na tela.

   float ang = 0;

public:
   Superficie()
   {
      //geracao de terrenos aleatorios a cada execucao
      srand(time(NULL));

      //cria um terreno centrado na origem
      for(int x=0; x<=DIM; x++)
         for(int z=0; z<=DIM; z++)
         {
              mat[x][z].x = x - (float)( DIM/2.0 );
              mat[x][z].y = ( rand()%8 ) / 10.0;
              mat[x][z].z = z - (float)( DIM/2.0 );
         }
   }

   Ponto rotacionaX(Ponto p )
   {
      Ponto resp;
      ang += 0.00001;

      resp.x = p.x;
      resp.y = cos(ang)*p.y - sin(ang)*p.z;
      resp.z = sin(ang)*p.y + cos(ang)*p.z;

      return resp;
   }

   Ponto translada(Ponto p)
   {
       Ponto resp;

       resp.x = p.x;
       resp.y = p.y - 10 ;
       resp.z = p.z - 12;

       return resp;
   }

   //projecao em perspectiva, assumindo camera na origem olhando para z negativo.
   Ponto projeta( Ponto p )
   {
       float d = -10.0;
       Ponto resp;

       resp.x = (p.x*d) / p.z;
       resp.y = (p.y*d) / p.z;
       resp.z = 0;

       return resp;
   }

   void transforma()
   {
      for(int x=0; x<=DIM; x++)
         for(int z=0; z<=DIM; z++)
         {
              //copia os pontos originais
              transf[x][z] = mat[x][z];

              //rotacao no eixo x
              transf[x][z] = rotacionaX( transf[x][z] );

              //translacao no eixo z
              transf[x][z] = translada( transf[x][z] );

              //projecao em perspectiva
              transf[x][z] = projeta( transf[x][z] );
         }
   }


   void render()
   {
      glPointSize(4);

      //desenha os vertices
      for(int x=0; x<=DIM; x++)
         for(int z=0; z<=DIM; z++)
         {
             point(transf[x][z].x, transf[x][z].y);
         }

      //desenha as arestas
      for(int x=0; x<DIM; x++)
         for(int z=0; z<DIM; z++)
         {
             line(transf[x][z].x, transf[x][z].y, transf[x+1][z].x, transf[x+1][z].y );
             line(transf[x][z].x, transf[x][z].y, transf[x][z+1].x, transf[x][z+1].y );
         }
   }

};
