#ifndef _CS_c
#define _CS_c
/****************************************************************
* IMPLEMENTACION MODULO: ConstraintSystem.c
* FECHA CREACION:  12-Mar-01
* DESCRIPCION: 
*   Crea un Sistema de Restricciones y realiza operaciones basicas sobre
*   este tales como: Ask y Tell
*
* AUTORES:         CATHERINE GARIA
*                  ALEJANDRA MARIA VASQUEZ
* MODIFICACIONES:
* AUTOR FECHA:
*
*****************************************************************/

/*===============================================================*
  Tabla de Contenido:
  
  0. Instrucciones para compilar el modulo
       gcc -c CS.c

  1. Librerias requeridas para su linkeo:
       -lm -lX11

  2. Listado de estructuras de datos definidas (publicas y privadas)

  3. Listado de funciones definidas (publicas y privadas)
       int tell(Store,Indexicals,Stamp,FrameConst)
       int basicTell(Store,Indexicals,Stamp,FrameConst)
       int VariableCheck(Store,Indexicals,Stamp,Cola)
       Lista suspended(Store, int)
       int ask(Store,Indexicals,Stamp,FrameConst)
       int basicAsk(Store, Indexicals, Stamp, FrameConst)
       int entailmentCheck(Store, Indexical)
        
  4. Instruccion para modificar el modulo
  4.1 Construcciones importantes para tener en cuenta (e.g. tipos, variables, funciones)
  4.2 Observaciones Adicionales
  
  ===============================================================*/

/*--------------------------------------------------------------*
  Archivos de Interfaz de librerias estandar y de otros modulos
 *--------------------------------------------------------------*/
#include "CS.h"
/*--------------------------------------------------------------*
         Declaracion  de Constantes y Macros privados
 *--------------------------------------------------------------*/

/*--------------------------------------------------------------*
  Declaracion de struct's, union's, enum's y typedef's privados
 *--------------------------------------------------------------*/

/*--------------------------------------------------------------*
         Declaracion  de variables publicas
 *--------------------------------------------------------------*/

/*--------------------------------------------------------------*
         Declaracion  de variables privadas
 *--------------------------------------------------------------*/

/*--------------------------------------------------------------*
         Prototipo de las funciones privadas
 *--------------------------------------------------------------*/

/*--------------------------------------------------------------*
         Definicion  de las funciones privadas
 *--------------------------------------------------------------*/

int tell (Store store,Indexicals indexicals,Stamp *s,int *indextemp, FrameConst f)
  /*---------------------------------------------------------------
  DESCRIPCION: Implementacion de la operacion tell sobre
               el Sistema de Restricciones.
  PARAMETROS: f: es la representacion de una restriccion aritme
              tica como un frameconst.
         store : Es el store del Sistema de Restricciones.
         indexicals: Son los indexicals que representan las
         restricciones impuestas sobre el store.
         s: Marca de tiempo para la evaluacion de los indexicals
         indextemp: Identificador de las variables generadas por
                    retricciones no lineales.
  USA:
  RETORNA: El estado de la operacion
  PRE:
  POS: La Ope = FAIL || Ope = SUCCESS.
  NOTAS:
  ---------------------------------------------------------------*/
{
  int Valuef, Solizq,resp;
    
  Valuef = getValueFrameConst(f);

  if (Valuef == LOGAND)
    {
      Solizq = basicTell(store,indexicals,s,indextemp,getLefSonFrameConst(f));
      if (Solizq == FAIL) return FAIL;
      else
   return tell(store,indexicals,s,indextemp,getRigSonFrameConst(f));
    }
  else
    {
      resp=basicTell(store,indexicals,s,indextemp,f);
      return (resp);
    }
}

int basicTell(Store store,Indexicals indexicals, Stamp *s,int *indextemp,FrameConst frmconst)
     /*---------------------------------------------------------------
  DESCRIPCION: Implementacion de la operacion basica tell sobre
               el Sistema de Restricciones.
  PARAMETROS: frmconst es la representacion de una restriccion 
              aritmetica como un FrameConst.
         store : Es el store del Sistema de Restricciones.
         indexicals: Son los indexicals que representan las
         restricciones impuestas sobre el store.
         s: Marca de tiempo para la evaluacion de los indexicals
         indextemp: Identificador de las variables generaradas por
                    restricciones no lineales.
  USA:
  RETORNA: El estado de la operacion
  PRE:
  POS: La Ope = FAIL || Ope = SUCCESS.
  NOTAS:
  ---------------------------------------------------------------*/
{
  int variable_key, posIndexical,RV_key, monot_ind, estado;
  Cola Q;
  Lista ListaRV;
  ListaFC ListaIndexNec=inicListaFC();
  FDVariable fdvariable; // En la implementacion de la structura. debe estar el puntero
  Indexical indexical;   // En la implementacion de la struct debe estar  el puntero.
  Domain x_sigma, r_sigma, I; // En la implementacion de la struct debe estar el puntero.

  ListaIndexNec = IndexNecAritToIndex(ListaIndexNec, indextemp, frmconst);


  for (primListaFC(ListaIndexNec); !finListaFC(ListaIndexNec); sigListaFC(ListaIndexNec))
    {
      indexical = InicpIndexical(infoListaFC(ListaIndexNec),*s);
      variable_key = getValueFrameConst(getLefSonFrameConst(infoListaFC(ListaIndexNec)));
      indexicals = addElementIndexicals(indexicals, indexical);
      posIndexical = sizeIndexicals(indexicals); 
      ListaRV = getVariablesIndexical(indexical);
      primLista(ListaRV); 
      RV_key = infoLista(ListaRV); 
      if (getVariableStore(store, RV_key)== NULL)
   {
     fdvariable = InicpFDVariable(RV_key,*s,indexicals); 
     store = insertVariableStore(store, RV_key, fdvariable);
     freeFDVariable(fdvariable);
   }
      /*Crea las variables que aparezcan en el rango del indexical  y que no existan en el store*/ 
      for ( sigLista(ListaRV); !finLista(ListaRV); sigLista(ListaRV))
   {
     RV_key = infoLista(ListaRV);
     if (getVariableStore(store, RV_key)== NULL)
       {
         fdvariable = InicpFDVariable(RV_key,*s,indexicals); 
         store = insertVariableStore(store, RV_key, fdvariable);
         freeFDVariable(fdvariable);
       }
     else
       updateDepFDVariable(getVariableStore(store, RV_key),posIndexical,indexical,RV_key);
   }
      destruirLista(ListaRV);

      /* Realizacion del TELL sobre el store */

      x_sigma = Inicp1Domain(getDomainFDVariable(getVariableStore(store, variable_key)));
      r_sigma =r_Sigma(store,indexical);
      I = Inicp1Domain(x_sigma);
      intersectionDomain(I, r_sigma);
      monot_ind = Monotonicity(getCodef(indexical),store);
      if (!isConsistentDomain(I))
   {/* <Vacio> */
     if (monot_ind == MONOTONE|| monot_ind == CONSTANT)
       {
         indexicals = removeElementAtIndexicals(indexicals, posIndexical);
         store = desrefVariableDepStore(store, posIndexical);

         /* Nuevo para que realmente quede la inconsistencia */
         setDomainFDVariable(getVariableStore(store, variable_key), I);
         /* Nuevo para que realmente quede la inconsistencia */

         freeDomain(x_sigma);
         freeDomain(r_sigma);
         freeDomain(I);
         freeIndexical(indexical);
         destruirListaFC(ListaIndexNec);
         return FAIL;
         
       } /*else continue */
   }
      else if (equalsDomain(I, x_sigma))  /*x_sigma */
   {
     if (monot_ind == ANTIMONOTONE || monot_ind == UNDEFINED)
         {
      indexicals = removeElementAtIndexicals(indexicals, posIndexical);
      store = desrefVariableDepStore(store, posIndexical);  
         }
   }
      else
   {/* otherwise */
     if (monot_ind == MONOTONE || monot_ind == CONSTANT)
       {
         (*s)++;
         store = updateVarStampStore(store,variable_key,*s);
         if (!updateVarDomStore(store, variable_key,I))
      {
        freeDomain(x_sigma);
        freeDomain(r_sigma);
        freeDomain(I);
        freeIndexical(indexical);
        destruirListaFC(ListaIndexNec);
        return FAIL;
              
      }
         if (monot_ind == CONSTANT)
      {
        setEntailed(indexical, TRUE);
        indexicals = setElementAtIndexicals(indexicals, indexical, posIndexical);
      }
       }
   }
      Q = inicCola();
      adicCola(Q, variable_key);
      estado = VariableCheck(store,indexicals,s,Q);
      destruirCola(Q);
      freeDomain(x_sigma);
      freeDomain(r_sigma);
      freeDomain(I);
      freeIndexical(indexical);
      if (estado == FAIL) 
   return estado;
    }
  destruirListaFC(ListaIndexNec);
  return SUCCESS;
}

int VariableCheck(Store store, Indexicals indexicals, Stamp *s, Cola Q)
     /*---------------------------------------------------------------
       DESCRIPCION: Implementacion del algoritmo resolutivo basico.
       PARAMETROS: Q: es una cola de variables
                   store : Es el store del Sistema de Restricciones.
         indexicals: Son los indexicals que representan las
         restricciones impuestas sobre el store.
         s: Marca de tiempo para la evaluacion de los indexicals
       USA:
       RETORNA: El estado de la operacion
       PRE:
       POS: La Ope = FAIL || Ope = SUCCESS.
       NOTAS:
       ---------------------------------------------------------------*/
{
  int tokeny, posIndexical, xkey, monot_f;
  FDVariable fdvariabley;
  Domain x_sigma, r_sigma, I;
  Lista IndexSusy;
  Indexical f;

  while(!vaciaCola(Q))
    {/* Mientra la cola no este vacia */
      tokeny = infoCola(Q);
      fdvariabley = getVariableStore(store, tokeny);
      elimCola(Q); /* Q = Q \ {y} */
      IndexSusy = suspended(store, tokeny); /* Indexicals que dependen de la variable y */

      for ( primLista(IndexSusy); !finLista(IndexSusy); sigLista(IndexSusy))
   {
     posIndexical = infoLista(IndexSusy);
     f = elementAtIndexicals(indexicals, posIndexical);
     if (getEntailed(f)) /* Si f esta marcada como deducido */
         {
      indexicals = removeElementAtIndexicals(indexicals, posIndexical);
      store = desrefVariableDepStore(store, posIndexical);
         }
     else
       {
         if(getStampFDVariable(fdvariabley) >= getStamp(f))
      {
        xkey = getX(f);
        x_sigma = Inicp1Domain(getDomainFDVariable(getVariableStore(store, xkey)));
        r_sigma = r_Sigma(store,f);
        I = Inicp1Domain(x_sigma);
        intersectionDomain(I, r_sigma);
        setStamp(f, *s);
        indexicals = setElementAtIndexicals(indexicals, f, posIndexical);
        monot_f = Monotonicity(getCodef(f),store);
        if (!isConsistentDomain(I))
          {/* <Vacio> */
            if (monot_f == MONOTONE|| monot_f == CONSTANT)
         {
           freeDomain(x_sigma);
           freeDomain(r_sigma);
           freeDomain(I);
           freeIndexical(f);
           destruirLista(IndexSusy);
           return FAIL;
         }
          }
        else if (equalsDomain(I, x_sigma)) /* x_sigma */
          {
            if (monot_f == ANTIMONOTONE)
         {
           setEntailed(f,TRUE);
           indexicals = removeElementAtIndexicals(indexicals, posIndexical);
           store = desrefVariableDepStore(store, posIndexical);  
         }
           
          }
        else
          {/* otherwise */
            if (monot_f == MONOTONE || monot_f == CONSTANT)
         {
           (*s)++;
           store = updateVarStampStore(store, xkey,*s);
           if (!updateVarDomStore(store, xkey,I))
             {
               freeDomain(x_sigma);
               freeDomain(r_sigma);
               freeDomain(I);
               freeIndexical(f);
               destruirLista(IndexSusy);
               return FAIL;
             }
           if (!existeElementoCola(Q,xkey))
             {
               adicCola(Q,xkey);
             }
           if (monot_f == CONSTANT)
             {
               setEntailed(f, TRUE);
               indexicals = removeElementAtIndexicals(indexicals, posIndexical);
               store = desrefVariableDepStore(store, posIndexical); 
             }
         }
          }
        freeDomain(x_sigma);
        freeDomain(r_sigma);
        freeDomain(I);
      }
       }
     freeIndexical(f);
   }
      destruirLista(IndexSusy);
    }
  return SUCCESS;
}

Lista suspended(Store store, int id)
/*---------------------------------------------------------------
  DESCRIPCION: Implementacion de la funcion suspended, la cual
               retorna una lista de las posiciones dentro de la 
          variable global indexicals de los indexical's
          que dependen de la variable representada por id.
          
        
  PARAMETROS: id es el identificador de la variable.
              store : Es el store del Sistema de Restricciones.
  USA:
  RETORNA: Lista con las posiciones de los indexical's que 
           dependen de la varible identificada por id.
  PRE: 
  POS: List = < PosIndx1/id, PosIndx2/id, ...> || List = NULL 
  NOTAS:
  ---------------------------------------------------------------*/
{
  int v_prune_type;
  Lista res;
  Lista tempunion1, tempunion2, tempunion3;
  FDVariable variable;
  variable=getVariableStore(store, id);
  v_prune_type=getPruneTypeFDVariable(variable);
  switch(v_prune_type){
  case PMIN:
    tempunion1 = unionLista(getChainMinFDVariable(variable), getChainMinMaxFDVariable(variable));
    tempunion2 = unionLista(tempunion1, getChainDomFDVariable(variable));
    res=unionLista(tempunion2,getChainValFDVariable(variable));
    destruirLista(tempunion1);
    destruirLista(tempunion2);
    break;

  case PMAX:
    tempunion1 = unionLista(getChainMaxFDVariable(variable), getChainMinMaxFDVariable(variable));
    tempunion2 = unionLista(tempunion1,getChainDomFDVariable(variable));
    res=unionLista(tempunion2,getChainValFDVariable(variable));
    destruirLista(tempunion1);
    destruirLista(tempunion2);
    break;

  case PDOM:
    res=unionLista(getChainDomFDVariable(variable),getChainValFDVariable(variable)); 
    break;

  case PMINMAX:
    tempunion1 = unionLista( getChainMaxFDVariable(variable), getChainMinMaxFDVariable(variable));
    tempunion2 = unionLista(tempunion1,getChainDomFDVariable(variable));
    tempunion3 = unionLista(tempunion2,getChainValFDVariable(variable));
    res=unionLista(tempunion3,getChainMinFDVariable(variable));
    destruirLista(tempunion1);
    destruirLista(tempunion2);
    destruirLista(tempunion3);
    break;

  default:
    res=inicLista(); 
    break;
  }
  return res;
}


int ask(Store store, Indexicals indexicals, Stamp *s, FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Implementacion de la operacion ask sobre
               el Sistema de Restricciones.
          
  PARAMETROS: f: es la representacion de una restriccion aritme
              tica como un frameconst
         store: Es la representacion del store en el Sistema
         de Restricciones.
         indexicals: Son los indexicals que representan las
         restricciones impuestas sobre el store.
         s: Marca de tiempo para la evaluacion de los indexicals
         
  USA:
  RETORNA: El estado de la operacion
  PRE:
  POS: La Ope = ENTAILED || Ope = UNENTAILED || Ope=SUSPENDED.
  NOTAS:
  ---------------------------------------------------------------*/
{
  int resizq,resder,resp;

 
  if(getValueFrameConst(f)==LOGAND)
    {
      resizq=basicAsk(store, indexicals, s, getLefSonFrameConst(f));
      if(resizq==FAIL)
   {
     return FAIL;
   }
      else
   if(resizq==SUSPENDED)
     {
       resder=ask(store, indexicals, s,getRigSonFrameConst(f));
       if(resder==FAIL)
         {
      return FAIL;
         }
       else
         {
      return SUSPENDED;
         }
     }
   else

     {
       resp= ask(store, indexicals, s,getRigSonFrameConst(f));
       return resp;
     }
    }
  else 
    {
      resp= basicAsk(store, indexicals, s,f);
      return resp;
    }
}

int basicAsk(Store store, Indexicals indexicals, Stamp *s, FrameConst f)
/*---------------------------------------------------------------
  DESCRIPCION: Implementacion de la operacion basica ask sobre
               el Sistema de Restricciones.
  PARAMETROS: f: es la representacion de una restriccion 
              aritmetica como un FrameConst.
         store : Es el store del Sistema de Restricciones.
         indexicals: Son los indexicals que representan las
         restricciones impuestas sobre el store.
         s: Marca de tiempo para la evaluacion de los indexicals
  USA:
  RETORNA: El estado de la operacion
  PRE:
  POS: La Ope = UNENTAILED || Ope = ENTAILED || Ope=SUSPENDED
  NOTAS:
  ---------------------------------------------------------------*/
{
  int RV_key,estado,estadoneg;
  FrameConst frmconst,frizq,frder,frmneg;
  Indexical indexical;
  Lista rangevariables;
  
  frmconst=IndexSufAritToIndex(f);
  indexical=InicpIndexical(frmconst, *s);
  rangevariables=getVariablesIndexical(indexical);
  for (primLista(rangevariables); !finLista(rangevariables); sigLista(rangevariables))
    {
      RV_key = infoLista(rangevariables);
      if(getVariableStore(store, RV_key)==NULL)
   {
     destruirLista(rangevariables); 
     freeIndexical(indexical);
     return SUSPENDED;
   }
    }
  
  destruirLista(rangevariables);
  estado=entailmentCheck(store, indexical);
  freeIndexical(indexical);
  if(estado==SUSPENDED)
    {
      frizq=getLefSonFrameConst(f);
      frder=getRigSonFrameConst(f);
      frmneg=InicFrameConst(getTypeFrameConst(f),NegRel(getValueFrameConst(f)));
      insertSonFrameConst(frmneg,frizq,LEFT);
      insertSonFrameConst(frmneg,frder,RIGHT);
      frmconst=IndexSufAritToIndex(frmneg);
      indexical=InicpIndexical(frmconst,*s);
      estadoneg=entailmentCheck(store, indexical);
      freeIndexical(indexical);

      if(estadoneg==ENTAILED)
   return UNENTAILED;
      else return SUSPENDED;
    }
  return(estado);
}


int entailmentCheck(Store store, Indexical indexical)
/*---------------------------------------------------------------
  DESCRIPCION: Implemtacion del algoritmo que chequea la deduccion
               de un indexicals de la actual configuracion de la 
          bodega de restricciones.
       
  PARAMETROS: indexical: Indexical a analizar
         store : Es el store del Sistema de Restricciones.
   
  USA:
  RETORNA: El estado de la operacion
  PRE:
  POS: La Ope = ENTAILED || Ope = SUSPENDED.
  NOTAS:
  ---------------------------------------------------------------*/
{
  int variable_key, aux;
  Domain x_sigma,r_sigma,I;

  variable_key=getX(indexical);
  x_sigma=Inicp1Domain(getDomainFDVariable(getVariableStore(store, variable_key)));
  r_sigma = r_Sigma(store,indexical);
  I=Inicp1Domain(x_sigma);
  intersectionDomain(I,r_sigma);
  aux=equalsDomain(I,x_sigma);
  freeDomain(I);
  freeDomain(x_sigma);
  freeDomain(r_sigma);
  if(aux)
    return ENTAILED;
  else
    return SUSPENDED;
}

#endif


/****EOF****/
