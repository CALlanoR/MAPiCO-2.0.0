// Proceso.h
// Copyright (c) 2002,  Alba Sarasti. <asarasti@puj.edu.co>, 
//                      Carlos A. Llano R. <callanor@puj.edu.co>
// Pontificia Universidad Javeriana, Colombia(Santiago de Cali)

// This is free software.  You are permitted to use,
// redistribute, and modify it as specified in the file "COPYING".

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*! \file Proceso.h
    \brief Libreria que define el manejo de procesos de MAPiCO
*/

/*! \struct strProceso
    \brief Estructura que almacena un proceso
*/
struct strProceso{
  int PC;      //Puntero a codigo
  void *PV;    //Puntero a variables
  void *PM;    //Puntero a metodos
  void *PA;    //Puntero a arguentos y restricciones
  void *PO;    //Puntero a objetos
  void *PAUX;  //Puntero auxiliar
  void *PTEMP; //Puntero Temporal
};

/*! \typedef Proceso Tipo para definir un proceso
*/
typedef struct strProceso *Proceso;


Proceso initProceso(void);

/*! \fn Proceso newProceso(int PC, void *PV, void *PM, void *PA, void *PO, void *PAUX, void *PTEMP)
    \brief Funci'on que inicializa un proceso en MAPiCO
    \param Puntero a codigo
    \param Puntero a variables
    \param Puntero a metodos
    \param Puntero a arguentos y restricciones
    \param Puntero a objetos
    \param Puntero auxiliar
    \param Puntero Temporal
    \return Proceso inicializado
*/
Proceso newProceso(int PC, void *PV, void *PM, void *PA, void *PO, void *PAUX, void *PTEMP);

/*! \fn void setPC(Proceso Proc, int PC)
    \brief Funci'on que permite asignar el valor del puntero a codigo
    \param Proc Proceso de MAPiCO
    \param PC Nuevo valor del apuntador
*/
void setPC(Proceso Proc, int PC);

/*! \fn void setPV(Proceso Proc, void *PV)
    \brief Funci'on que permite asignar el valor del puntero a variables
    \param Proc Proceso de MAPiCO 
    \param PV Nuevo valor del apuntador
*/
void setPV(Proceso Proc, void *PV);

/*! \fn void setPM(Proceso Proc, void *PM)
    \brief Funci'on que permite asignar el valor del puntero a metodos
    \param Proc Proceso de MAPiCO
    \param PM Nuevo valor del apuntador
*/
void setPM(Proceso Proc, void *PM);

/*! \fn void setPA(Proceso Proc, void *PA)
    \brief Funci'on que permite asignar el valor del puntero a argumentos y restricciones
    \param Proc Proceso de MAPiCO
    \param PA Nuevo valor del apuntador
*/
void setPA(Proceso Proc, void *PA);

/*! \fn void setPO(Proceso Proc, void *PO)
    \brief Funci'on que permite asignar el valor del puntero a objetos
    \param Proc Proceso de MAPiCO
    \param PO Nuevo valor del apuntador
*/
void setPO(Proceso Proc, void *PO);

/*! \fn void setPAUX(Proceso Proc, void *PAUX)
    \brief Funci'on que permite asignar el valor del puntero auxiliar
    \param Proc Proceso de MAPiCO
    \param PAUX Nuevo valor del apuntador
*/
void setPAUX(Proceso Proc, void *PAUX);

/*! \fn void setPTEMP(Proceso Proc, void *PTEMP)
    \brief Funci'on que permite asignar el valor del puntero temporal
    \param Proc Proceso de MAPiCO
    \param PTEMP Nuevo valor del apuntador
*/
void setPTEMP(Proceso Proc, void *PTEMP);

/*! \fn int getPC(Proceso Proc)
    \brief Funci'on que permite obtener el valor del apuntador a codigo
    \param Proc Proceso de MAPiCO
    \return Valor del apuntador a codigo
*/
int getPC(Proceso Proc);

/*! \fn void *getPV(Proceso Proc)
    \brief Funci'on que permite obtener el valor del apuntador de variables
    \param Proc Proceso de MAPiCO
    \return El valor del apuntador de variables
*/
void *getPV(Proceso Proc);

/*! \fn void *getPM(Proceso Proc)
    \brief Funci'on que permite obtener el valor del apuntador de metodos
    \param Proc Proceso de MAPiCO
    \return El valor del apuntador de metodos
*/
void *getPM(Proceso Proc);

/*! \fn void *getPA(Proceso Proc)
    \brief Funci'on que permite obtener el valor del apuntador de argumentos y restricciones
    \param Proc Proceso de MAPiCO
    \return El valor del apuntador de argumentos y restricciones
*/
void *getPA(Proceso Proc);

/*! \fn void *getPO(Proceso Proc)
    \brief Funci'on que permite obtener el valor del apuntador de objetos
    \param Proc Proceso de MAPiCO
    \return El valor del apuntador de objetos
*/
void *getPO(Proceso Proc);

/*! \fn void *getPAUX(Proceso Proc)
    \brief Funci'on que permite obtener el valor del apuntador auxiliar
    \param Proc Proceso de MAPiCO
    \return El valor del apuntador auxiliar
*/
void *getPAUX(Proceso Proc);

/*! \fn void *getPTEMP(Proceso Proc)
    \brief Funci'on que permite obtener el valor del apuntador temporal
    \param Proc Proceso de MAPiCO
    \return El valor del apuntador temporal
*/
void *getPTEMP(Proceso Proc);

/*! \fn void delProceso(Proceso Proc)
    \brief Funci'on que permite liberar la memoria de un proceso
    \param Proc Proceso de MAPiCO
*/
void delProceso(Proceso Proc);

