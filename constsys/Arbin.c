/*-------------------------------------------------------------------*/
/* "DISENO Y MANEJO DE ESTRUCTURAS DE DATOS EN C" - V. 1.0           */
/* J. Villalobos - Universidad de los Andes (Sept.-1995)             */
/*-------------------------------------------------------------------*/
/* TAD Arbin [TipoA]                                                 */
/* TAD Arbin- Implementacion #2 (Encadenamiento al padre)            */
/*-------------------------------------------------------------------*/
#include "Arbin.h"

/*-------------------------------------------------------------------*/
Arbin inicArbin( int type, int value)
{
  Arbin resp;
  resp = NULL;

  resp=(Arbin)malloc(sizeof(TArbin));
  if (!resp)
    {
      printf("Error en la asignacion de memoria para el arbol");
      exit(1);
    }
  (resp->info).tipo = type;
  (resp->info).valor = value;
  (resp->izq) = NULL;
  (resp->der) = NULL;

  return resp;
}

Arbin inicpArbin( Arbin a)
{
 
  Arbin resp;

  resp=(Arbin)malloc(sizeof(TArbin));
  if (!resp)
    {
      printf("Error en la asignacion de memoria para el arbol");
      exit(1);
    }
  (resp->info).tipo = raizArbin(a).tipo;
  (resp->info).valor = raizArbin(a).valor;
  (resp->izq) = NULL;
  (resp->der) = NULL;

  if ( ((a->izq) == NULL) && ((a->der) == NULL))
      return resp;
  else
   {
       if ((a->izq) != NULL)
    resp->izq = inicpArbin(izqArbin(a));
       if ((a->der) != NULL)
    resp->der = inicpArbin(derArbin(a));
       return(resp);
   }
}
 


void insertArbin(Arbin a, Arbin son, int hijo)
{
  if(hijo==LEFT)
    a->izq=son;
  else
    a->der=son;
}

void destruirArbin( Arbin a )
{
  if( a != NULL )
    {   
      destruirArbin( a->izq );
      a->izq = NULL;
      destruirArbin( a->der );
      a->der = NULL;
      free( a );
      a = NULL;
    }

}

void imprimirArbin(Arbin a)
{
  if (a != NULL)
    printf("|T:%d, V:%d|\n",raizArbin(a).tipo,raizArbin(a).valor);
  if (  a->izq != NULL )
    imprimirArbin(izqArbin(a));
  if ( a->der != NULL )
    imprimirArbin(derArbin(a));
}


/*-------------------------------------------------------------------*/
