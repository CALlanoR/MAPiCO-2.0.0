
#include "Proceso.h"

Proceso initProceso(void)
{
  Proceso newProceso;

  //Asignacion de memoria
  newProceso = (struct strProceso *)malloc(sizeof(struct strProceso));

  return newProceso;
}//initProceso

Proceso newProceso(int PC, void *PV, void *PM, void *PA, void *PO, void *PAUX, void *PTEMP)
{
  Proceso newProceso;

  //Asignacion de memoria
  newProceso = (struct strProceso *)malloc(sizeof(struct strProceso));

  //Asignacion de valores
  newProceso->PC = PC;
  newProceso->PV = PV;
  newProceso->PM = PM;
  newProceso->PA = PA;
  newProceso->PO = PO;
  newProceso->PAUX = PAUX;
  newProceso->PTEMP = PTEMP;

  return newProceso;
}//newProceso

void setPC(Proceso Proc, int PC)
{
  Proc->PC = PC;
}//setPC

void setPV(Proceso Proc, void *PV)
{
  Proc->PV= PV;
}//setPV

void setPM(Proceso Proc, void *PM)
{
  Proc->PM = PM;
}//setPM

void setPA(Proceso Proc, void *PA)
{
  Proc->PA = PA;
}//setPA

void setPO(Proceso Proc, void *PO)
{
  Proc->PO = PO;
}//setPO

void setPAUX(Proceso Proc, void *PAUX)
{
  Proc->PAUX = PAUX;
}//setPAUX

void setPTEMP(Proceso Proc, void *PTEMP)
{
  Proc->PTEMP = PTEMP;
}//setPTEMP

int getPC(Proceso Proc)
{
  return Proc->PC;
}//getPC

void *getPV(Proceso Proc)
{
  return Proc->PV;
}//getPV

void *getPM(Proceso Proc)
{
  return Proc->PM;
}//getPM

void *getPA(Proceso Proc)
{
  return Proc->PA;
}//getPA

void *getPO(Proceso Proc)
{
  return Proc->PO;
}//getPO

void *getPAUX(Proceso Proc)
{
  return Proc->PAUX;
}//getPAUX

void *getPTEMP(Proceso Proc)
{
  return Proc->PTEMP;
}//getPTEMP

void delProceso(Proceso Proc)
{
  //Libera la memoria ocupada por el proceso
  free(Proc);
}//delProceso

/** EOF **/

