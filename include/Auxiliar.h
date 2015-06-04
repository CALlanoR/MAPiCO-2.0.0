// Generic Aux macros
// Copyright (c) 2002,  Alba Sarasti. <asarasti@puj.edu.co>, 
//                      Carlos A. Llano R. <callanor@puj.edu.co>
// Pontificia Universidad Javeriana, Colombia(Santiago de Cali)

// This is free software.  You are permitted to use,
// redistribute, and modify it as specified in the file "COPYING".


#ifndef AUXILIAR_H
#define AUXILIAR_H

//Inicializador
#define NEWAUXILIAR(Auxi)                          \
do{                                                \
    Auxi = (struct Aux *)malloc(sizeof(struct Aux));   \
}while(0)

//Inicializador
#define INICAUXILIAR(Auxi, SinTipoAux)             \
do{                                                \
    NEWAUXILIAR(Auxi);                             \
    Auxi->nArg = NULL;                             \
    Auxi->Tipo = SinTipoAux;                       \
}while(0)   
          
//Asigna un NodeArg
#define SETNODEARG(Aux, NodeArg)   \
do{                                                                              \
  Aux->nArg = NodeArg;                           \
}while( 0 )

//Asigna un FrameConst
#define SETFRAMECONST(Aux, FrameConstMA)   \
do{                                                                               \
  Aux->Fconst = FrameConstMA;                     \
}while( 0 )

//Devuelve el tipo de Aux
#define GETTYPE(Aux)  Aux->Tipo

//Asigna el tipo a Aux
#define SETTYPE(Aux,  TipoAux)   \
do{                                                                              \
  Aux->Tipo = TipoAux;                                          \
}while( 0 )

//Devuelve el nArg de Aux
#define GETNODEARG(Aux)  Aux->nArg

//Devuelve el FConst de Aux
#define GETFRAMECONST(Aux)  Aux->Fconst

//Elimina el FrameConst de Aux
#define FREEFRAMECONST(Aux)              \
do{                                                                \
   DestruirFrameConst(Aux->Fconst);         \
   free(Aux->Fconst);                                    \
   Aux->Fconst = NULL;                               \
   Aux->Tipo = NODEARGM;                       \
}while( 0 )         

//Libera Aux
#define FREEAUX(Aux) \
do{                                    \
   free(Aux);                     \
}while(0)

#endif // AUXILIAR_H
