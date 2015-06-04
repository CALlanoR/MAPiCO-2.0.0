#include "Proceso.h"
#include "Loader.h"
#include "PlugIns.h"

//Funciones
Parameters ValidFrameConst(Parameters argv, FrameConstMA FPAUX);

/**
 * Catalogue
 */
Parameters Catalogue(Parameters argv, char *PathLibrary, void *Handle, int NumPlugIn)
{
  char *Functions[] = {"20:TERMV","21:TERMC","22:ATOM","23:TELL_","24:ASK_","25:ASKF", "26:TERMF",NULL};
   
   //Cargar las instrucciones del PlugIn
   argv = loadInstructions(argv, Functions, PathLibrary, Handle, NumPlugIn);
   
   return argv;
   
}//Catalogue

/**
 * ASKF
 */
 Parameters ASKF(Parameters argv)
 {
      //Registros que se necesitan de MAPiCO
      int    PCA;                   //Program Counter
      NodeList PVA;            //Program Variable
      Auxiliar PAA, PAUX;    //Puntero Auxiliar Actual      
      ObjectEval POA;       //Puntero a Objetos Evaludados 
      //Parameters (*Instruction)(Parameters); //Funcion de la instruccion
      
      //Declaracion de colas
      List RunQ;            //Cola de Ejecucion
      List ObjQ;            //Cola de Objetos
      List MsgQ;          //Cola de Mensajes  
      List AskQ;           //Cola de Preguntas
      
      //Vble para el Program Byte
      Program Data;
      
      //Vbles para definir procesos
      Proceso Proc;
      Proceso ProcObjCC;
      
      //Otras Vbles
      int i = 0;
      StoreMA sMA;      
      FrameConstMA FPAA;
                        
      //printf("Begin ASKF.\n");
      
      //Recuperacion del primer parametro
      Proc = getAtVblePlugIn(argv,1);
      
      //Recuperacion del tercer parametro
      Data = getAtVblePlugIn(argv,3); 
      
      //Recuperacion de la cola de ejecucion
      RunQ = getAtVblePlugIn(argv,4);
      
      //Recuperacion de la cola de Objetos
      ObjQ = getAtVblePlugIn(argv,5);
      
      //Recuperacion de la cola de Mensajes
      MsgQ = getAtVblePlugIn(argv,6);
      
     //Recuperacion de la cola de preguntas
      AskQ = getAtVblePlugIn(argv,7);
      
     //Recuperacion del storeMA
     sMA = getStoreMA(argv);
            
      //Se recuperan los valores de los registros
      PCA = getPC(Proc);
      PVA = getPV(Proc);
      PAA  = getPA(Proc);
      PAUX = getPAUX(Proc);
      POA = getPO(Proc);
      
      /*
      //Inicializar StoreMA en caso de que no haya sido iniciado      
      if(sMA->inicializado != OK)
      {
         //printf("Inicializo sMA\n");
         sMA = inicStoreMA(); 
         if(getResponseMA(sMA)==StoreERR)
         {
            //printf("Error, al inicializar el Store.\n");
            exit(0);
         }     
      }
      */  
      
      if(GETTYPE(PAA)==FRAMECONST)
      {
         FPAA = GETFRAMECONST(PAA);
         
         //Validacion del FrameConst de PAUX
         argv = ValidFrameConst(argv, FPAA);
         if(getResponse(argv)==ERROR)
         {
            //printf("%s, PC [%d]\n", getError(argv), PCA);
            return argv;
         }         
      
         //ImprimirFrameConst(FPAA);
         
         sMA = askMA(sMA, FPAA);
         
         switch (getResponseMA(sMA))
         {
            case ENTAILED_MA:
                  //printf("ENTAILED_MA\n");
                  //Incrementar el PCA para que salte a la instruccion POP
                  PCA = PCA + 5; // 5 = 1 + 1 + 2 + 1; PCA = PCA + ASKF + PUSHV + DIRPUSHV + CALL
                  break;
            case UNENTAILED_MA:
                 //printf("UNENTAILED_MA\n");
            case SUSPENDED_MA:
                 //printf("UNENTAILED_MA/SUSPEND_MA/DEFAULT\n");
                  //Si el objeto es no replicado se agrega a la cola de Objetos
                  /*
                  if(get8(Data, POA->PCS[POA->NumObjects]) != _COBJCC)
                  {
                     ProcObjCC =  newProceso(PCA, PVA, NULL, PAA, NULL, PAUX, NULL);
                     INSERT_AT_END(ObjQ, ProcObjCC);
                  }
                  */
                     
                  //Pasa a la siguiente instruccion
                  PCA = PCA + 1;                                                                     
                  break;
         }//switch(sMA->Response)
         
         DestruirFrameConstMA(GETFRAMECONST(PAA));   
         SETFRAMECONST(PAA, NULL); 
   
         if(GETNODEARG(PAA)!=NULL)
         {
            //El FrameConst queda NULL el tipo queda NODEARGM porque tiene datos
            SETTYPE(PAA,  NODEARGM);            
            //printf("PAA es NODEARGM\n");
         }//if(GETNODEARG(PAA)!=NULL)
         else
         {
            //printf("PAA queda NOT_TYPE\n");
            SETTYPE(PAA,  NOT_TYPE);
            SETTYPE(PAUX,  NOT_TYPE);
         }
                  
         setPC(Proc, PCA);
         setPA(Proc,PAA);
         setPAUX(Proc,PAUX);
                  
         //Se guardan las variables en la lista de vbles de los PlugIn's
         argv = setAtVblePlugIn(argv,Proc,1);  
         argv = setAtVblePlugIn(argv,RunQ,4);
         argv = setAtVblePlugIn(argv,ObjQ,5);
         argv = setAtVblePlugIn(argv,MsgQ,6);
         argv = setAtVblePlugIn(argv,AskQ,7);   
         argv = setStoreMA(argv,sMA);                     
                                         
      }//if(GETTYPE(PAA)== FRAMECONST)
                              
      //printf("End ASKF\n");
          
      //Retorno de los argumentos
      return argv;  
            
 }//ASKF 

/**
 * ATOM
 */
Parameters ATOM(Parameters argv)
{
  //Registros que se necesitan de MAPiCO
  int    PCA;              //Program Counter
  NodeList PVA;      //Program Variable
  Auxiliar PAA;        //Program Argument Actual
  Auxiliar PAUX;      //Puntero Auxiliar

  //Vble para definir procesos
  Proceso Proc;
 
  //Otras Vbles
  int Predicado;
  FrameConstMA faux, FPAUX;
  Program Data;
 
  //printf ("Begin ATOM.\n");

  //Recuperacion del primer parametro
  Proc = getAtVblePlugIn(argv,1);

  //Recuperacion del tercer parametro
  Data = getAtVblePlugIn(argv,3);

  //Se recuperan los valores de los registros
  PCA  = getPC(Proc);
  PVA  = getPV(Proc);
  PAA  = getPA(Proc);
  PAUX = getPAUX(Proc);
      
  //Se captura el predicado de ATOM
  Predicado = get16(Data, PCA+1);      
   
   //Creacion del FrameConst a partir del predicado
   faux = InicFrameConstMA(PREDICADOMA, Predicado);
   
   if(GETTYPE(PAA)==NOT_TYPE || GETTYPE(PAA)==NODEARGM)
   {
      //printf("if(PAA==NULL || GETTYPE(PAA)==NODEARGM)\n");
      
      //En este caso el PAA en su parte de FrameConst no tiene nada por lo que se construye con el predicado
      
      //Se asgina el FrameConst a los registros
      SETFRAMECONST(PAA, faux);      
      SETTYPE(PAA, FRAMECONST);
      
      SETFRAMECONST(PAUX, faux);      
      SETTYPE(PAUX, FRAMECONST);
         
   }//if(GETTYPE(PAA)==NOT_TYPE || GETTYPE(PAA)==NODEARGM)
   else
   {
      //printf("else::if(GETTYPE(PAA)==NOT_TYPE || GETTYPE(PAA)==NODEARGM)\n");
      
       //Se recupera el FrameConst que contiene el PAUX          
      FPAUX = GETFRAMECONST(PAUX);
      
      //Validacion del FrameConst de PAUX
      argv = ValidFrameConst(argv, FPAUX);
      if(getResponse(argv)==ERROR)
      {
         //printf("%s, PC [%d]\n", getError(argv), PCA);
         return argv;
      }
                                    
      if(getLefSonFrameConstMA(FPAUX) == NULL)
      {
         setLefSonFrameConstMA(FPAUX, faux);  //Aqui el PAUX se queda igual como esta
      }//if(getLefSonFrameConstMA(FPAUX) == NULL)
      else
      {
         //En este caso el PAUX debe pasar al hijo derecho
         setRigSonFrameConstMA(FPAUX, faux);
         
         if(GETFRAMECONST(PAA)==GETFRAMECONST(PAUX))
         {                        
            SETFRAMECONST(PAUX, faux);
            SETTYPE(PAUX, FRAMECONST);
         }//if(GETFRAMECONST(PAA)==GETFRAMECONST(PAUX))
      }//End::else::if(getLefSonFrameConstMA(FPAUX) == NULL)      
   }//End::else::if(PAA==NULL)

   faux = NULL;
      
   //Incrementar el PCA para la siguiente instruccion
   PCA = PCA + 5; // 5 = 1 + 2 + 2;

   //Asignacion de los nuevos valores
   setPC(Proc, PCA);
   setPA(Proc,PAA);
   setPAUX(Proc,PAUX);

   //Se guardan las variables en la lista de vbles de los PlugIn's
   argv = setAtVblePlugIn(argv,Proc,1);

  //printf("End ATOM\n");
  
  //Retorno de los argumentos
  return argv;

}//ATOM

/**
 * TERMV
 */
Parameters TERMV(Parameters argv)
{
  //Registros que se necesitan de MAPiCO
  int    PCA;           //Program Counter
  NodeList PVA;   //Program Variable
  Auxiliar PAA;     //Program Argument Actual
  Auxiliar PAUX;   //Puntero Auxiliar
 
  //Vble para definir procesos
  Proceso Proc;
 
  //Otras Vbles
  int VariableTERMV, Longitud;
  FrameConstMA faux, FPAUX;
  Program Data;
  //int *Var;
  int *Variable;
  
  //Var = NULL;
  faux = NULL;
  FPAUX = NULL;
  
  //Var = (int *)malloc(sizeof(int));  
  Variable = (int *)malloc(sizeof(int));
  
  //printf ("Begin TERMV.\n");

  //Recuperacion del primer parametro
  Proc = getAtVblePlugIn(argv,1);

  //Recuperacion del tercer parametro
  Data = getAtVblePlugIn(argv,3);

  //Se recuperan los valores de los registros
  PCA =  getPC(Proc);
  PVA =  getPV(Proc);
  PAA = getPA(Proc);
  PAUX =  getPAUX(Proc);

  //Longitud de la lista de Variable
  LENGTH(PVA,Longitud);
  //printf("Lon PVA [%d]\n", Longitud);
  VariableTERMV = get16(Data, PCA+1);
  //printf("Variable [%d]\n", VariableTERMV);
    
  //printf("----------------------------------------------------\n");
  //PRINT_NODELIST(PVA);
  //printf("----------------------------------------------------\n");

   if(Longitud >= VariableTERMV)
   {
      //Valor de Variable de la lista del PV    
      GETDATAAT(PVA, VariableTERMV, Variable);
      //memcpy(Variable, Var, sizeof(int));
      //printf("Var [%d]\n", *Variable);            

       //Se recupera el FrameConst que contiene el PAUX          
      FPAUX = GETFRAMECONST(PAUX);
      
      //Validacion del FrameConst de PAUX
      argv = ValidFrameConst(argv, FPAUX);
      if(getResponse(argv)==ERROR)
      {
         //printf("%s, PC [%d]\n", getError(argv), PCA);
         return argv;
      }

      faux = InicFrameConstMA(VARIABLEMA, *Variable);      
      
      if(getLefSonFrameConstMA(FPAUX)==NULL)
      {
         //printf("Left\n");
         setLefSonFrameConstMA(FPAUX, faux);  //Aqui el PAUX se queda igual como esta
         
         //ImprimirFrameConstMA(FPAUX);
         
      }//if(getLefSonFrameConstMA(FPAUX)==NULL)
      else
      {
         //printf("Rigth\n");
         //En este caso el PAUX debe pasar al hijo derecho
         setRigSonFrameConstMA(FPAUX, faux);
         
         //ImprimirFrameConstMA(FPAUX);
         
         if(GETFRAMECONST(PAA)==GETFRAMECONST(PAUX))
         {                        
            //printf("PAA==PAUX\n");
            SETFRAMECONST(PAUX, faux);            
            SETTYPE(PAUX, FRAMECONST);
         }//if(GETFRAMECONST(PAA)==GETFRAMECONST(PAUX))
      }//End::else::if(getLefSonFrameConstMA(FPAUX)==NULL)
       
      //Incrementar el PCA para la siguiente instruccion
      PCA = PCA + 3; // 3 = 1  + 2;
      
      faux = NULL;

      //Asignacion de nuevo valor del Frame al que debe apuntar PAUX
      SETFRAMECONST(PAUX, FPAUX);
      SETTYPE(PAUX, FRAMECONST);

      //Asignacion de los nuevos valores
      setPC(Proc, PCA);
      setPAUX(Proc, PAUX);

      //Se guardan las variables en la lista de vbles de los PlugIn's
      argv = setAtVblePlugIn(argv,Proc,1);
  }
  else
  {
     //printf("TERMV Error...");      
     int *Finish;
     Finish = (int *)malloc(sizeof(int));
     *Finish = OK;           
     argv = setAtVblePlugIn(argv,Finish,0);
    }//End::else::if(Longitud >= Variable)
 
  //printf("End TERMV\n");

    //Retorno de los argumentos
    return argv;

}//TERMV

/**
 * TERMC
 */
Parameters TERMC(Parameters argv)
{
  //Registros que se necesitan de MAPiCO
  int    PCA;           //Program Counter
  NodeList PVA;         //Program Variable
  Auxiliar PAUX;        //Puntero Auxiliar
  Auxiliar PAA;     //Program Argument Actual

  //Vble para definir procesos
  Proceso Proc;
 
  //Otras Vbles
  int Constante;
  FrameConstMA faux, FPAUX;
  int Longitud=0; 
  Program Data;
 
  //printf ("Begin TERMC.\n");

  //Recuperacion del primer parametro
  Proc = getAtVblePlugIn(argv,1);

  //Recuperacion del tercer parametro
  Data = getAtVblePlugIn(argv,3);

  //Se recuperan los valores de los registros
  PCA = getPC(Proc);
  PVA = getPV(Proc);
  PAUX = getPAUX(Proc);
  PAA = getPA(Proc);
   
   //Constante 
   Constante = get16(Data, PCA+1);   
   faux = InicFrameConstMA(CONSTANTEMA, Constante);   
    
   //Se recupera el FrameConst que contiene el PAUX          
   FPAUX = GETFRAMECONST(PAUX);
   
   //Validacion del FrameConst de PAUX
   argv = ValidFrameConst(argv, FPAUX);
   if(getResponse(argv)==ERROR)
   {
      //printf("%s, PC [%d]\n", getError(argv), PCA);
      return argv;
   }
 
    if(getLefSonFrameConstMA(FPAUX)==NULL)
    {
       setLefSonFrameConstMA(FPAUX, faux);  //Aqui el PAUX se queda igual como esta
    }//if(getLefSonFrameConstMA(FPAUX)==NULL)
    else
    {
       //En este caso el PAUX debe pasar al hijo derecho
       setRigSonFrameConstMA(FPAUX, faux);
       
       if(GETFRAMECONST(PAA)==GETFRAMECONST(PAUX))
       {                        
          SETFRAMECONST(PAUX, faux);
          SETTYPE(PAUX, FRAMECONST);
       }//if(GETFRAMECONST(PAA)==GETFRAMECONST(PAUX))
    }//End::else::if(getLefSonFrameConstMA(FPAUX)==NULL)     
 
    if(Constante == -1)
       ImprimirFrameConstMA(FPAUX);
    
    faux = NULL;
    
    //Incrementar el PCA para la siguiente instruccion
    PCA = PCA + 3; // 3 = 1 + 2;

    //Asignacion de los nuevos valores
    setPC(Proc, PCA);
    setPAUX(Proc,PAUX);

    //Se guardan las variables en la lista de vbles de los PlugIn's
    argv = setAtVblePlugIn(argv,Proc,1);
 
    //printf("End TERMC\n");
    
    //ImprimirFrameConst(GETFRAMECONST(PAA));

    //Retorno de los argumentos
    return argv;

}//TERMC

/**
 * TERMF
 */
Parameters TERMF(Parameters argv)
{
  //Registros que se necesitan de MAPiCO
  int    PCA;              //Program Counter
  NodeList PVA;      //Program Variable
  Auxiliar PAA;        //Program Argument Actual
  Auxiliar PAUX;      //Puntero Auxiliar

  //Vble para definir procesos
  Proceso Proc;
 
  //Otras Vbles
  int Predicado;
  FrameConstMA faux, FPAUX;
  Program Data;
 
  //printf ("Begin TERMF.\n");

  //Recuperacion del primer parametro
  Proc = getAtVblePlugIn(argv,1);

  //Recuperacion del tercer parametro
  Data = getAtVblePlugIn(argv,3);

  //Se recuperan los valores de los registros
  PCA  = getPC(Proc);
  PVA  = getPV(Proc);
  PAA  = getPA(Proc);
  PAUX = getPAUX(Proc);
  
   Predicado = get16(Data, PCA+1);      
   
   //printf("Predicado [%d]\n", Predicado);
   
   faux=InicFrameConstMA(FUNCIONMA, Predicado);
   
   //printf("PAA Type [%d]\n", GETTYPE(PAA));
   
   //ImprimirFrameConstMA(faux);
   
   if(GETTYPE(PAA)==NOT_TYPE || GETTYPE(PAA)==NODEARGM)
   {
      //printf("if(GETTYPE(PAA)==NOT_TYPE || GETTYPE(PAA)==NODEARGM)\n");
      
      //En este caso el PAA en su parte de FrameConst no tiene nada por lo que se construye con el predicado
      
      //Se asgina el FrameConst a los registros
      SETFRAMECONST(PAA, faux);
      SETTYPE(PAA, FRAMECONST);
      
      SETFRAMECONST(PAUX, faux);
      SETTYPE(PAUX, FRAMECONST);
         
   }//if(GETTYPE(PAA)==NOT_TYPE || GETTYPE(PAA)==NODEARGM)
   else
   {  
      //printf("else::if(GETTYPE(PAA)==NOT_TYPE || GETTYPE(PAA)==NODEARGM)\n");
       
      //Se recupera el FrameConst que contiene el PAUX          
      FPAUX = GETFRAMECONST(PAUX);
      
      //ImprimirFrameConstMA(FPAUX);
            
      if(getLefSonFrameConstMA(FPAUX)==NULL)
      {
         //printf("Left\n");
         setLefSonFrameConstMA(FPAUX, faux);  //Aqui el PAUX se queda igual como esta
         
         //ImprimirFrameConstMA(FPAUX);
      }//if(getLefSonFrameConstMA(FPAUX)==NULL)
      else
      {
         //printf("Rigth\n");
         //En este caso el PAUX debe pasar al hijo derecho
         setRigSonFrameConstMA(FPAUX, faux);
         
         //ImprimirFrameConstMA(FPAUX);
         
         if(GETFRAMECONST(PAA)==GETFRAMECONST(PAUX))
         {                 
            //printf("PAA==PAUX\n");       
            SETFRAMECONST(PAUX, faux);
            SETTYPE(PAUX, FRAMECONST);
         }//if(GETFRAMECONST(PAA)==GETFRAMECONST(PAUX))
      }//End::else::if(getLefSonFrameConstMA(FPAUX)==NULL)
   }//End::else::if(PAA==NULL)
   
   faux = NULL;
   
  //Incrementar el PCA para la siguiente instruccion
  PCA = PCA + 5; // 5 = 1 + 2 + 2;

  //Asignacion de los nuevos valores
  setPC(Proc, PCA);
  setPA(Proc,PAA);
  setPAUX(Proc,PAUX);

  //Se guardan las variables en la lista de vbles de los PlugIn's
  argv = setAtVblePlugIn(argv,Proc,1);
  
  //exit(0);

  //printf("End TERMF\n");
  
  //Retorno de los argumentos
  return argv;

}//TERMF


/**
 * TELL_
 */
Parameters TELL_(Parameters argv)
{
  //Registros que se necesitan de MAPiCO
  int    PCA;           //Program Counter
  NodeList PVA;         //Program Variable
  Auxiliar PAA;         //Program Argument Actual
  Auxiliar PAUX;        //Puntero Auxiliar

  //Vble para definir procesos
  Proceso Proc;
 
  //Otras Vbles
  int Predicado,res;
  FrameConstMA FPAA, FPAUX;
  int Longitud=0;
  Program Data;
 
  StoreMA sMA;
  List RunQ;     
  List AskQ;              
  List MsgQ;     

  //printf("Begin TELL.\n");

  //Recuperacion del primer parametro
  Proc = getAtVblePlugIn(argv,1);

  //Recuperacion del tercer parametro
  Data = getAtVblePlugIn(argv,3);

  //Recuperacion de la cola de ejecucion
  RunQ = getAtVblePlugIn(argv,4);

  //Recuperacion de la cola de mensajes
  MsgQ = getAtVblePlugIn(argv,6);

  //Recuperacion de la cola de Ask
  AskQ = getAtVblePlugIn(argv,7);

  //Recuperacion del storeMA
  sMA = getStoreMA(argv);
  
  //Se recuperan los valores de los registros
  PCA  = getPC(Proc);
  PVA  = getPV(Proc);
  PAA  = getPA(Proc);
  PAUX = getPAUX(Proc);
    
  //Se recupera el FrameConst que contiene el PAA
   FPAA = GETFRAMECONST(PAA);
   
   //ImprimirFrameConstMA(FPAA);
   
   //Validacion del FrameConst de PAA
   argv = ValidFrameConst(argv, FPAA);
   if(getResponse(argv)==ERROR)
   {
      //printf("%s, PC [%d]\n", getError(argv), PCA);
      return argv;
   }
   
   /*
   //Inicializar StoreMA en caso de que no haya sido iniciado      
   if(sMA->inicializado != OK)
   {
      //printf("Inicializo sMA\n");
      sMA = inicStoreMA(); 
      if(getResponseMA(sMA)==StoreERR)
      {
         //printf("Error, al inicializar el Store.\n");
         exit(0);
      }     
   }
   */  

   //ImprimirStore(sMA->s);
      
   sMA = tellMA(sMA, FPAA);
     
   //printf("En TELL la longitud de MsgQ [%d]\n", LENGTH_LIST(MsgQ));
   
   if(LENGTH_LIST(MsgQ)!=0)
   {
      //printf("En TELL ADD_AT_END(RunQ,MsgQ)\n");
      ADD_AT_END(RunQ,MsgQ); 
      FREE_LIST(MsgQ);      
   }
   
   if(LENGTH_LIST(AskQ)!=0)
   {  
      //printf("En TELL ADD_AT_END(RunQ,AskQ)\n"); 
      ADD_AT_END(RunQ,AskQ); 
      FREE_LIST(AskQ);
   }

   DestruirFrameConstMA(GETFRAMECONST(PAA));   
   SETFRAMECONST(PAA, NULL);
   
   if(GETNODEARG(PAA)!=NULL)
   {
      //printf("if(GETNODEARG(PAA)!=NULL)\n");
      SETTYPE(PAA,  NODEARGM);
   }//if(GETNODEARG(PAA)!=NULL)
   else
   {
      //printf("PAA queda NOT_TYPE\n");
      SETTYPE(PAA,  NOT_TYPE);
      SETTYPE(PAUX,  NOT_TYPE);
   }
   
   //Incrementar el PCA para la siguiente instruccion
   PCA = PCA + 1;
   
   //Asignacion de los nuevos valores
   setPC(Proc, PCA);
   setPA(Proc,PAA);
   setPAUX(Proc,PAUX);
      
   //Se guardan las variables en la lista de vbles de los PlugIn's
   argv = setAtVblePlugIn(argv,Proc,1);
   argv = setAtVblePlugIn(argv,RunQ,4);
   argv = setAtVblePlugIn(argv,MsgQ,6);
   argv = setAtVblePlugIn(argv,AskQ,7);
   argv = setStoreMA(argv,sMA);
   
   //printf("End TELL\n");
   
   //ImprimirStore(sMA->s);
  
   //Retorno de los argumentos
   return argv;
  
}//TELL_

/**
 * ASK_
 */
Parameters ASK_(Parameters argv)
{
      //Registros que se necesitan de MAPiCO
      int    PCA;                   //Program Counter
      NodeList PVA;            //Program Variable
      Auxiliar PAA, PAUX;    //Puntero Auxiliar Actual      
      ObjectEval POA;       //Puntero a Objetos Evaludados 
      Parameters (*Instruction)(Parameters); //Funcion de la instruccion
      
      //Declaracion de colas
      List RunQ;            //Cola de Ejecucion
      List ObjQ;            //Cola de Objetos
      List MsgQ;          //Cola de Mensajes  
      List AskQ;           //Cola de Preguntas
      
      //Vble para el Program Byte
      Program Data;
      
      //Vbles para definir procesos
      Proceso Proc;
      Proceso ProcObjCC;
      
      //Otras Vbles
      int i = 0;
      StoreMA sMA;      
      FrameConstMA FPAA;
                  
      //printf("Begin ASK_.\n");
      
      //Recuperacion del primer parametro
      Proc = getAtVblePlugIn(argv,1);
      
      //Recuperacion del tercer parametro
      Data = getAtVblePlugIn(argv,3); 
      
      //Recuperacion de la cola de ejecucion
      RunQ = getAtVblePlugIn(argv,4);
      
      //Recuperacion de la cola de Objetos
      ObjQ = getAtVblePlugIn(argv,5);
      
      //Recuperacion de la cola de Mensajes
      MsgQ = getAtVblePlugIn(argv,6);
      
     //Recuperacion de la cola de preguntas
      AskQ = getAtVblePlugIn(argv,7);
      
     //Recuperacion del storeMA
     sMA = getStoreMA(argv);
            
      //Se recuperan los valores de los registros
      PCA = getPC(Proc);
      PVA = getPV(Proc);
      PAA  = getPA(Proc);
      PAUX = getPAUX(Proc);
      POA = getPO(Proc);
      
      /*
      //Inicializar StoreMA en caso de que no haya sido iniciado      
      if(sMA->inicializado != OK)
      {
         //printf("Inicializo sMA\n");
         sMA = inicStoreMA(); 
         if(getResponseMA(sMA)==StoreERR)
         {
            //printf("Error, al inicializar el Store.\n");
            exit(0);
         }     
      }
      */  
      
      if(GETTYPE(PAA)==FRAMECONST)
      {
         FPAA = GETFRAMECONST(PAA);
         
         //Validacion del FrameConst de PAUX
         argv = ValidFrameConst(argv, FPAA);
         if(getResponse(argv)==ERROR)
         {
            //printf("%s, PC [%d]\n", getError(argv), PCA);
            return argv;
         }         
      
         //ImprimirFrameConst(FPAA);
         
         sMA = askMA(sMA, FPAA);
         
         switch (getResponseMA(sMA))
         {
            case ENTAILED_MA:
                  //printf("ENTAILED_MA\n");
                  //Incrementar el PCA para que salte a la siguiente instruccion
                  PCA = PCA + 1; 
                  break;
            case UNENTAILED_MA:
                 //printf("UNENTAILED_MA\n");
                 //Se busca la instruccion encargada de realizar el schedule
                 Instruction = getInstruction(argv, getOpCodeSchedule(argv));
                 
                 //Ejecucion de la instruccion
                 argv = Instruction(argv);               
                 
                 break;
            case SUSPENDED_MA:
                  //printf("SUSPEND_MA\n");
                  if(LENGTH_LIST(AskQ)!=0)
                  {   
                     ADD_AT_END(RunQ,AskQ); 
                     LIST(AskQ);
                  }
                  break;
         }//switch(sMA->Response)
         
         DestruirFrameConstMA(GETFRAMECONST(PAA));   
         SETFRAMECONST(PAA, NULL); 
   
         if(GETNODEARG(PAA)!=NULL)
         {
            //El FrameConst queda NULL el tipo queda NODEARGM porque tiene datos
            SETTYPE(PAA,  NODEARGM);            
            //printf("PAA es NODEARGM\n");
         }//if(GETNODEARG(PAA)!=NULL)
         else
         {
            //printf("PAA queda NOT_TYPE\n");
            SETTYPE(PAA,  NOT_TYPE);
            SETTYPE(PAUX,  NOT_TYPE);
         }
                  
         setPC(Proc, PCA);
         setPA(Proc,PAA);
         setPAUX(Proc,PAUX);
                  
         //Se guardan las variables en la lista de vbles de los PlugIn's
         argv = setAtVblePlugIn(argv,Proc,1);  
         argv = setAtVblePlugIn(argv,RunQ,4);
         argv = setAtVblePlugIn(argv,ObjQ,5);
         argv = setAtVblePlugIn(argv,MsgQ,6);
         argv = setAtVblePlugIn(argv,AskQ,7);   
         argv = setStoreMA(argv,sMA);                     
         
      }//if(GETTYPE(PAA)== FRAMECONST)
                                
      //printf("End ASK_\n");
        
      //Retorno de los argumentos
      return argv;  
               
}//ASK_

/**
 * ValidFPAUX
 */
Parameters ValidFrameConst(Parameters argv, FrameConstMA FPAUX)
{
   if(FPAUX==NULL)
   {
      int *Finish;
      argv = setError(argv, "Error PAUX is NULL");
      Finish = (int *)malloc(sizeof(int));
      *Finish = OK;                 
      argv = setAtVblePlugIn(argv,Finish,0);
      argv = setResponse(argv, ERROR);
      return argv;         
   }//if(FPAUX==NULL)
   
   argv = setResponse(argv, OK);
   return argv;
   
}//ValidFrameConst
