#include "StoreMA.h"

/**
* inicStoreMA
*/
StoreMA inicStoreMA(void)
{
   StoreMA newStoreMA;

   //Asignacion de memoria para cada variable del Store   
   newStoreMA = (StoreMA)malloc(sizeof(struct str_StoreMA));    
   newStoreMA->i = (Indexicals *)malloc(sizeof(Indexicals));
   newStoreMA->indextemp = (int *)malloc(sizeof(int));   
   newStoreMA->t=(Stamp *)malloc(sizeof(Stamp));

   //Inicializacion de cada variable del Store
   newStoreMA->i = InicIndexicals();;
   newStoreMA->s = inicStore();
      
   if(!newStoreMA->indextemp)
   {
      newStoreMA->Error = (char *)malloc(sizeof(char)*100);
      strcpy(newStoreMA->Error, "Error en la asignacion de memoria de Index_Temp");      
      newStoreMA->Response = StoreERR;
      
      return newStoreMA;
   }
  *(newStoreMA->indextemp)=-1;
      
   if(!newStoreMA->t)
   {
         newStoreMA->Error = (char *)malloc(sizeof(char)*100);
         strcpy(newStoreMA->Error, "Error en la asignacion de memoria de Stamp");      
         newStoreMA->Response = StoreERR;
         
         return newStoreMA;                  
   }
   *(newStoreMA->t)=0;
  
  //Inicializacion del Store Correcta
  newStoreMA->Response = StoreOK;
  newStoreMA->inicializado = StoreOK;
  
  return newStoreMA;   
}//inicStoreMA

/**
* tellMA
*/
StoreMA tellMA(StoreMA storeMA, FrameConstMA frameconst)
{
   //printf("tellMA\n");
   int Response =   tell( storeMA->s, storeMA->i, storeMA->t, storeMA->indextemp, frameconst);   
   //printf("Response [%d]\n", Response);
   
   return storeMA;
}//tellMA

/**
* askMA
*/
StoreMA askMA(StoreMA storeMA, FrameConstMA frameconst)
{
   storeMA->Response = ask(storeMA->s, storeMA->i, storeMA->t, frameconst);
   return storeMA;   
}//askMA

/**
* InicFrameConstMA
*/
FrameConstMA InicFrameConstMA(int type, int value)
{
   return InicFrameConst(type, value);
}//InicFrameConstMA

/**
* InicpFrameConstMA
*/
FrameConstMA InicpFrameConstMA(FrameConstMA fc)
{
   return InicpFrameConst(fc);
}//InicpFrameConstMA

/**
* getLefSonFrameConstMA
*/
FrameConstMA getLefSonFrameConstMA(FrameConstMA f)
{
   return getLefSonFrameConst(f);
}//getLefSonFrameConstMA

/**
* getRigSonFrameConstMA
*/
FrameConstMA getRigSonFrameConstMA(FrameConstMA f)
{
   return getRigSonFrameConst(f);
}//getRigSonFrameConstMA

/**
* setLefSonFrameConstMA
*/
void setLefSonFrameConstMA(FrameConstMA f, FrameConstMA lefson)
{
   setLefSonFrameConst(f, lefson);
}//setLefSonFrameConstMA

/**
* setRigSonFrameConstMA
*/
void setRigSonFrameConstMA(FrameConstMA f, FrameConst rigson)
{
   setRigSonFrameConst(f, rigson);
}//setRigSonFrameConstMA

/**
* DestruirFrameConstMA
*/
void DestruirFrameConstMA(FrameConstMA f)
{
   DestruirFrameConst(f);
}//DestruirFrameConstMA

/**
* ImprimirFrameConstMA
*/
void ImprimirFrameConstMA(FrameConstMA f)
{
   ImprimirFrameConst(f);
}//ImprimirFrameConstMA

/**
* getResponseMA
*/
int getResponseMA(StoreMA sm)
{
   return sm->Response;
}//getResponseMA

/**
* getInicializadoMA
*/
int getInicializadoMA(StoreMA sm)
{
   return sm->inicializado;
}

/**
* freeStoreMA
*/
void freeStoreMA(StoreMA storeMA)
{
   freeStore(storeMA->s);
   free(storeMA->t);
   free(storeMA->i);
   free(storeMA->indextemp);   
}//freeStoreMA





