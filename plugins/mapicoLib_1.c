#include "Proceso.h"
#include "Loader.h"
#include "HeapSort.h"
#include "PlugIns.h"

int searchMeth(int PCObject, int Meth, Program Data);

/**
 * Catalogue
 */
Parameters Catalogue(Parameters argv, char *PathLibrary, void *Handle, int NumPlugIn)
{
   char *Functions[] = {"13:NEWV","14:PAR","15:FINISH","16:FUNC","17:CALL","18:DEL","19:COMM",NULL};
      
   //Cargar las instrucciones del PlugIn
   argv = loadInstructions(argv, Functions, PathLibrary, Handle, NumPlugIn);
   
   return argv;
   
}//Catalogue

/**
 * NEWV
 */
Parameters NEWV(Parameters argv)
{
  //Registros que se necesitan de MAPiCO
  int    PCA;           //Program Counter
  NodeList PVA;         //Program Variable

  //Vble para definir procesos
  Proceso Proc;

  //Vble para el Program Byte
  char *Program;

  //Otras Vbles
  int *VarCounter;      //Contador de variables creadas
  int *VarCounterTemp;
  NodeList NodeTemp;

  //printf ("Begin NEWV.\n");

  //Recuperacion del primer parametro (Proceso)
  Proc = getAtVblePlugIn(argv,1);

  //Recuperacion del segundo parametro (VarCounter)
  VarCounter = getAtVblePlugIn(argv,2);

  //Recuperacion del tercer parametro (Data)
  Program = getAtVblePlugIn(argv,3);

  //Se recuperan los valores de los registros
  PCA = getPC(Proc);
  PVA = getPV(Proc);

  //Prueba de los parametros
  //printf("PCA->[%d]\n",PCA);
  //printf("VarCounter->[%d]\n",*VarCounter);

  VarCounterTemp = (int *)malloc(sizeof(int));
  memcpy(VarCounterTemp, VarCounter, sizeof(int));

  *VarCounterTemp = *VarCounterTemp + 1;
  //printf("VarCounterTemp->[%d]\n",*VarCounterTemp);
  
  *VarCounter = *VarCounter + 1;
  //printf("VarCounter->[%d]\n",*VarCounter);
    
  //Creacion de la variable en la Memoria de Traduccion
  NODELIST(NodeTemp, VarCounterTemp);
  SETNEXT(NodeTemp, PVA);
  PVA = NodeTemp;

  VarCounterTemp = NULL;
  
  //Liberacion de NodeTemp
  NodeTemp = NULL;
      
  //printf("----------------------------------------------------\n");
  //PRINT_NODELIST(PVA);
  //printf("----------------------------------------------------\n");  
    
  //Incrementar el PCA para la siguiente instruccion
  PCA = PCA + 1;

  //Incrementar el numero de variables
  //*VarCounter = *VarCounter + 1;
  //printf("VarCounter->[%d]\n",*VarCounter);

  //Asignacion de los nuevos valores
  setPC(Proc, PCA);
  setPV(Proc, PVA);

  //Se guardan las variables en la lista de vbles de los PlugIn's
  argv = setAtVblePlugIn(argv,Proc,1);
  argv = setAtVblePlugIn(argv,VarCounter,2);

  //printf("End NEWV\n");

  //Retorno de los argumentos
  return argv;

}//NEWV

/**
 * PAR
 */
Parameters PAR(Parameters argv)
{
  //Registro que se necesita de MAPiCO
  int PCA;                                   //Puntero a Codigo Actual
  NodeList PVA;                              //Puntero a Variables Actual
  NodeList PMA;                              //Puntero a Metodos Actual
  Auxiliar PAA;                              //Puntero a Argumentos Actual
  ObjectEval POA;                            //Puntero a Objetos Actual
  Auxiliar PAUX;                             //Puntero Auxiliar
  void *PTEMP;                               //Puntero Temporal  

  //Declaracion de colas
  List RunQ;            //Cola de Ejecucion

  //Declaracion de la direccion de PAR
  int DirPar = 0;

  //Vble para definir procesos
  Proceso Proc;
  Proceso ProcPar;

  //Vble para el Program Byte
  Program Data;

  //printf ("Begin PAR.\n");

  //Recuperacion del primer parametro (Proceso)
  Proc = getAtVblePlugIn(argv,1);

  //Recuperacion del tercer parametro (Data)
  Data = getAtVblePlugIn(argv,3); 

  //Prueba de parametros
  //for(int i=0;i<64;i++)
    //printf("[%c]",Data->File[i]);

  //Recuperacion de la cola de ejecucion (RunQ)
  RunQ = getAtVblePlugIn(argv,4);

  //Se recuperan los valores de los registros
  PCA = getPC(Proc);
  PVA = getPV(Proc);
  PMA = getPM(Proc);
  PAA = getPA(Proc);
  POA = getPO(Proc);
  PAUX = getPAUX(Proc);

  //Prueba de los parametros
  //printf("PCA->[%d]\n",PCA);
  
  DirPar = get32(Data, PCA+1);
  //printf("DirPar->[%d]\n",DirPar);

  if(GETTYPE(PAA) == NOT_TYPE)
  {     
     //Inicializar PAA y PAUX
     INICAUXILIAR(PAA, NOT_TYPE); 
     INICAUXILIAR(PAUX, NOT_TYPE); 
  }
  
  //Insercion de un nuevo proceso en RunQ
  ProcPar =  newProceso(DirPar, PVA, PMA, PAA, POA, PAUX, NULL);
  INSERT_AT_END(RunQ, ProcPar);
  
  //PRINT_LIST(RunQ);

  //Incrementar el PCA para la siguiente instruccion
  PCA = PCA + 5; //5 = 1 + 4;

  //Asignacion de los nuevos valores
  setPC(Proc, PCA);

  //Se guardan las variables en la lista de vbles de los PlugIn's
  argv = setAtVblePlugIn(argv,Proc,1);
  argv = setAtVblePlugIn(argv,RunQ,4);

  //printf("End PAR\n");

  //Retorno de los argumentos
  return argv;

}//PAR


/**
 * FUNC
 */
Parameters FUNC(Parameters argv)
{
  //Registro que se necesita de MAPiCO
  int PCA;           //Program Counter

  //Declaracion de la direccion de FUNC
  int DirFunc = 0;

  //Vble para definir procesos
  Proceso Proc;

  //Vble para el Program Byte
  Program Data;

  //printf ("Begin FUNC.\n");

  //Recuperacion del primer parametro (Proceso)
  Proc = getAtVblePlugIn(argv,1);

  //Recuperacion del tercer parametro (Data)
  Data = getAtVblePlugIn(argv,3); 

  //Prueba de parametros
  //for(int i=0;i<64;i++)
    //printf("[%c]",Data->File[i]);

  //Se recuperan los valores de los registros
  PCA = getPC(Proc);

  DirFunc = get32(Data, PCA+1);
  //printf("DirFunc->[%d]\n",DirFunc);

  //Prueba de los parametros
  //printf("PCA->[%d]\n",PCA);

  //Incrementar el PCA para la siguiente instruccion
  PCA = DirFunc;

  //Asignacion de los nuevos valores
  setPC(Proc, PCA);

  //Se guardan las variables en la lista de vbles de los PlugIn's
  argv = setAtVblePlugIn(argv,Proc,1);

  //printf("End FUNC\n");

  //Retorno de los argumentos
  return argv;

}//PAR

/**
 * CALL
 */
Parameters CALL(Parameters argv)
{
  //Registros que se necesitan de MAPiCO
  int    PCA;           //Program Counter
  ObjectEval POA;       //Puntero a Objetos Evaludados 
  ObjectEval newPOA;    //Puntero a Objetos Evaludados para el nuevo proceso
  Auxiliar newPAA;      //Puntero a argumentos para el nuevo proceso
  Auxiliar PAA;         //Puntero a argumentos para el nuevo proceso
  Parameters (*Instruction)(Parameters); //Funcion de la instruccion

  //Declaracion de colas
  List RunQ;            //Cola de Ejecucion
  List ObjQ;            //Cola de Objetos
  List MsgQ;            //Cola de Mensajes

  //Vble para el Program Byte
  Program Data;

  //Vbles para definir procesos
  Proceso Proc;
  Proceso ProcObj;
  Proceso newProc;
  
  //Otras Vbles
  int EvaluarMensaje = NOT;

  //printf("Begin CALL.\n");

  //Recuperacion del primer parametro (Proceso)
  Proc = getAtVblePlugIn(argv,1);

  //Recuperacion del tercer parametro (Data)
  Data = getAtVblePlugIn(argv,3); 

  //Recuperacion de la cola de ejecucion (RunQ)
  RunQ = getAtVblePlugIn(argv,4);

  //Recuperacion de la cola de Objetos (ObjQ)
  ObjQ = getAtVblePlugIn(argv,5);

  //Recuperacion de la cola de Mensajes (MsgQ)
  MsgQ = getAtVblePlugIn(argv,6);

  //Se recuperan los valores de los registros
  PCA = getPC(Proc);
  POA = getPO(Proc);
  
  //PRINT_PCS(POA);
  
  //printf("LENGTH_LIST (ObjQ)=[%d]\n", LENGTH_LIST(ObjQ));
  //printf("LENGTH_LIST Antes de hacer algo (RunQ)=[%d]\n", LENGTH_LIST(RunQ));
  
  //PRINT_LIST(RunQ);
  
  if( LENGTH_LIST(ObjQ)>0 )
  {
     if( GETNUMOBJECTS(POA) == 0 )
     {
        //printf("if( GETNUMOBJECTS(POA) == 0 )\n");
        ProcObj = (Proceso)GETDATA(FIRST_NODE(ObjQ));
        
        INICOBJECTEVAL(newPOA);
        NEWAUXILIAR(newPAA); 
         
        //printf("Direccion Objeto [%d]\n", getPC(ProcObj));
        
        //Recuperacion de la direccion del Sender
        PCA = get32(Data, getPC(ProcObj)+1);        
        PCA = PCA+1+4;
              
        //Inicializar nuevo proceso        
        newProc = initProceso();        
            
        //Asignacion del nuevo PC
        setPC(newProc, PCA);
        
        //Asignacion del PV del Objeto al nuevo Proceso
        setPV(newProc, getPV(ProcObj));

        //Inserta el PC del Objeto actual en el vector de Objetos Evaluados
        SAVE_PC(newPOA, getPC(ProcObj));
        
        //printf("POA->PCS[1] = [%d]\n", GET_PC_AT(POA, 1));

        //Asignacion del POA 
        setPO(newProc, newPOA);
        
        //Asignaciòn del PAA        
        PAA = getPA(Proc);
        
        SETTYPE(newPAA, NODEARGM);
        SETNODEARG(newPAA, GETNODEARG(PAA));
        setPA(newProc, newPAA);
        
        //PRINT_NODE_ARG(GETNODEARG(newPAA));
        
        setPM(newProc, getPM(Proc));
        setPAUX(newProc, getPAUX(Proc));
        setPTEMP(newProc, getPTEMP(Proc));
        
        //Inserta el nuevo proceso en RunQ
        INSERT_AT_END(RunQ, newProc);    
        
        INICAUXILIAR(PAA, NOT_TYPE);
        setPA(Proc, PAA);        
        //PRINT_NODE_ARG(GETNODEARG(PAA));

        //Si el objeto es replicado no se borra de la cola de Objetos
        if(get8(Data, getPC(ProcObj)) != _COBJCC)
        {
           DEL_FIRST_NODE(ObjQ);
        }
     }//if( GETNUMOBJECTS(POA) == 0 )
     else
     {
        //printf("if( GETNUMOBJECTS(POA) != 0 )\n");
  
        int i = 0;
                              
        //Se organiza el vector de Objetos evaluados
        HeapSort(GETPCS(POA), GETNUMOBJECTS(POA) );
       
       //PRINT_PCS(POA);
       
       //printf("\n");
       
       //printf("LENGTH_LIST(ObjQ)=[%d]\n", LENGTH_LIST(ObjQ));
       //PRINT_LIST(ObjQ);
       
       while( (i<LENGTH_LIST(ObjQ)) && (EvaluarMensaje==NOT) )
       {
          GET_AT(ObjQ,i,ProcObj);
          
          //printf("GET_AT()... i=[%d] getPC(ProcObj)=[%d]\n", i, getPC(ProcObj));          
         
          if(searchBinary(GETPCS(POA), GETNUMOBJECTS(POA), getPC(ProcObj)) == NOT_FOUND )
          {             
             //printf("dentro de searchBinary...\n");
          
             //Recuperacion de la direccion del Sender
             PCA = get32(Data, getPC(ProcObj)+1);
        
             PCA = PCA + 5; //5=1+4;       
                                               
             //Asignacion del nuevo PC
             setPC(Proc, PCA);
            
             //Asignacion del PV del Objeto al nuevo Proceso
             setPV(Proc, getPV(ProcObj));

             //Inserta el PC del Objeto actual en el vector de Objetos Evaluados            
             SAVE_PC(POA, getPC(ProcObj));
                         
             //Asignacion del POA 
             setPO(Proc, POA);
  
             //printf("LENGTH_LIST antes (RunQ)=[%d]\n", LENGTH_LIST(RunQ)); 
             //Inserta el nuevo proceso en RunQ
             INSERT_AT_END(RunQ, Proc);
             //printf("LENGTH_LIST despues (RunQ)=[%d]\n", LENGTH_LIST(RunQ));
                        
             EvaluarMensaje = OK;
            
             //Si el objeto es replicado no se borra de la cola de Objetos
             if(get8(Data, getPC(ProcObj)) != _COBJCC)
             {
                DEL_AT(ObjQ,i);
             }
          }
          else
          {
             //printf("Siguiente Objeto\n");
             i++;  //Siguiente Objeto
          }
       }//while

       if(EvaluarMensaje == NOT)
       {
          //El Mensaje se encola en MsgQ porque no se encontro objeto
          INSERT_AT_END(MsgQ, Proc);
       }
     }//else
  }
  else
  {
     //El Mensaje se coloca en MsgQ porque no se encontro Objeto
     INSERT_AT_END(MsgQ, Proc);
  }

  //printf("LENGTH_LIST despues de hacer CALL (RunQ)=[%d]\n", LENGTH_LIST(RunQ));
  //PRINT_LIST(RunQ);
  
  //Asignacion de los nuevos valores
  setPC(Proc, PCA); 
  setPA(Proc, PAA);

  //Se guardan las variables en la lista de vbles de los PlugIn's
  argv = setAtVblePlugIn(argv,Proc,1);  
  argv = setAtVblePlugIn(argv,RunQ,4);
  argv = setAtVblePlugIn(argv,ObjQ,5);
  argv = setAtVblePlugIn(argv,MsgQ,6);

  //printf("End CALL\n");

  //Se busca la instruccion encargada de realizar el schedule
  Instruction = getInstruction(argv, getOpCodeSchedule(argv));

  //Ejecucion de la instruccion
  argv = Instruction(argv);

  //Retorno de los argumentos
  return argv;  

}//CALL


/**
 * DEL
 */
Parameters DEL(Parameters argv)
{
  //Registros que se necesitan de MAPiCO
  int PCA;              //Program Counter
  int PCForward;        //Program Counter del Forward
  NodeList PVA;         //Program Variable
  Auxiliar PAA;         //Puntero Auxiliar Actual
  ObjectEval POA;       //Puntero a Objetos Evaludados 

  //Declaracion de colas
  List RunQ;            //Cola de Ejecucion

  //Vble para el Program Byte
  Program Data;

  //Vbles para definir procesos
  Proceso Proc;
  Proceso ProcFwd;
  
  Parameters (*Instruction)(Parameters); //Funcion de la instruccion

  //printf("Begin DEL.\n");

  //Recuperacion del primer parametro (Proceso)
  Proc = getAtVblePlugIn(argv,1);

  //Recuperacion del tercer parametro (Data)
  Data = getAtVblePlugIn(argv,3); 

  //Recuperacion de la cola de ejecucion (RunQ)
  RunQ = getAtVblePlugIn(argv,4);

  //Se recuperan los valores de los registros
  PCA = getPC(Proc);
  POA = getPO(Proc);
  PVA = getPV(Proc);
  PAA = getPA(Proc);

  //Recuperacion del PC del Forward 
  PCForward = GET_PC_AT(POA, GETNUMOBJECTS(POA)) + 1 + 4 + 4;
  
  //Creacion del nuevo proceso para ejecutar el forward
  ProcFwd = newProceso(PCForward, PVA, NULL, PAA, POA, NULL, NULL);

  INSERT_AT_END(RunQ, ProcFwd);

  PCA = PCA + 8;

  //Asignacion de los nuevos valores
  setPC(Proc, PCA);
  //Se guardan las variables en la lista de vbles de los PlugIn's
  argv = setAtVblePlugIn(argv,Proc,1);
  argv = setAtVblePlugIn(argv,RunQ,4);

  //printf("End DEL\n");

  //Se busca la instruccion encargada de realizar el schedule
  Instruction = getInstruction(argv, getOpCodeSchedule(argv));

  //Ejecucion de la instruccion
  argv = Instruction(argv);

  //Retorno de los argumentos
  return argv;

}//DEL

/**
 * COMM
 */
Parameters COMM(Parameters argv)
{
  //Registros que se necesitan de MAPiCO
  int PCA;               //Program Counter
  NodeList PVA;      //Program Variable
  NodeList PMA;      //Puntero a Metodos Actual
  ObjectEval POA;   //Puntero a Objetos Evaludados
  Auxiliar PAA;                     //Puntero Auxiliar Actual  
  Auxiliar PAUX;
  
  //Vbles para encontrar el Metodo
  int PCMeth = 0;      //Program Counter del Metodo a ejecutar
  int PCObject;            //Program Counter del Object que posiblemente tiene el Metodo
  int *nameMeth;      //Nombre del metodo que se va a buscar
  
  //Declaracion de colas
  List RunQ;            //Cola de Ejecucion

  //Vble para el Program Byte
  Program Data;

  //Vbles para definir procesos
  Proceso Proc;
  Proceso MethProc;
  
  Parameters (*Instruction)(Parameters); //Funcion de la instruccion
  
  //printf("Begin COMM.\n");
    
  //Recuperacion del primer parametro (Proc)
  Proc = getAtVblePlugIn(argv,1);

  //Se recuperan los valores de los registros
  PCA = getPC(Proc);
  PVA = getPV(Proc);
  PAA = getPA(Proc);
  PAUX = getPAUX(Proc);
  PMA = getPM(Proc);
  POA = getPO(Proc);
  
  //Recuperacion del tercer parametro (Data)
  Data = getAtVblePlugIn(argv,3); 
  
  //nameMethTemp = (int *)malloc(sizeof(int));
  nameMeth = (int *)malloc(sizeof(int));
  
  //Se captura el nombre del metodo
  nameMeth = GETDATA(PMA);
  
  //Recuperacion del PC del Objeto 
  
  //printf("NumObjects [%d]\n", GETNUMOBJECTS(POA));
  
  PCObject = GET_PC_AT(POA, GETNUMOBJECTS(POA));
  
  //printf("PCObject [%d]\n", PCObject);
  //printf("nameMeth [%d]\n", *nameMeth);
  
  //Busqueda del Metodo dentro del Objeto
  PCMeth = searchMeth(PCObject, *nameMeth, Data);
  
  //printf("PCMeth [%d]\n", PCMeth);
  
  if(PCMeth>0)
  {
     //Recuperacion de la cola de ejecucion (RunQ)
     RunQ = getAtVblePlugIn(argv,4);     
     
     //Eliminar el vector de objetos evaluados
     DELPCS(POA);
     SETNUMOBJECTS(POA, 0);
     
     //Se crea el nuevo proceso a ejecutar
     MethProc = newProceso(PCMeth, PVA, PMA, PAA, POA, PAUX, NULL);
     
     INSERT_AT_END(RunQ, MethProc);
          
     //printf("---------------------\n");
     //PRINT_LIST(RunQ);
                            
     //Se guarda RunQ solamente     
     argv = setAtVblePlugIn(argv,RunQ,4);
          
     //Se busca la instruccion encargada de realizar el schedule
     Instruction = getInstruction(argv, getOpCodeSchedule(argv));
      
     //Ejecucion de la instruccion
     argv = Instruction(argv);     
          
     free(nameMeth);
     nameMeth = NULL;
     
  }//if(PCMeth...  
  else
  {
      PCA = PCA + 1; //Pasa a la siguiente instruccion PUSHM
            
      setPC(Proc, PCA);
      
      //Se guardan las variables en la lista de vbles de los PlugIn's
      argv = setAtVblePlugIn(argv,Proc,1);      
  }
  
  //printf("End COMM\n");

  //Retorno de los argumentos
  return argv;

}//COMM

/**
 * FINISH
 */
Parameters FINISH(Parameters argv)
{
  int *Finish; 
  Finish = (int *)malloc(sizeof(int));
  *Finish = OK;

  //printf("Begin FINISH\n");

  argv = setAtVblePlugIn(argv,Finish,0);

  //printf("End FINISH\n");

  //Retorno de los argumentos
  return argv;

}//FINISH

/**
* searchMeth
*/
int searchMeth(int PCObject, int Meth, Program Data)
{
   int MethDir = -1;
   int countMeth  = 0;
   int PCParams  = 10; //4+4+2; DirSender + DirForward + NumMeth
   int increment = 2;
   int PC;
   short NumMeth,IdMeth;
   
   //////////////////////////////////////////////////////////////////////////////
   /// Estructura que debe leer el searchMeth:
   ////////////////////////////////////////////////////////////////////////////// 
   /// XOBJCC DirSender DirForward NumMeth
   /// METH Meth(1) DirBeginMeth(1)
   /// ...
   /// METH Meth(n) DirBeginMeth(n)
   //////////////////////////////////////////////////////////////////////////////
   /// Ej:
   /// COBJCC 4 16 2
   /// METH 1 26
   /// METH 2 34
   /////////////////////////////////////////////////////////////////////////////
   
   //Captura el numero de metodos que contiene el Objeto
   NumMeth = get8(Data, PCObject+9); // 9 = 1+4+4 ; XOBJCC+DirSender+DirForward
   
   //printf("NumMeth [%d]\n", NumMeth);
   
   PC = PCObject + PCParams; //Ubica el PC en el primer METH del Objeto
      
   while ((NumMeth > 0) && (MethDir < 0))
   {
       IdMeth = get8(Data, PC+1); // 1 = METH
       
       //printf("IdMeth [%d]\n", IdMeth);       
                     
       if (Meth == IdMeth)
       {
         MethDir = get32(Data, PC + 2); //2 = 1 + 1 ;METH + Meth(#)
         //printf("MethDir [%d]\n", MethDir);
         return MethDir;
       }
       
       //Incrementa el PC al proximo METH              
       PC = PC + 6; // 6 = 1 + 1 + 4; METH + Meth(#) + DirBeginMeth(#)
       
       NumMeth--;
   }//while ((NumMeth > 0) && (MethDir < 0))
   return MethDir;
}//searchMeth

