/*******************************************************
** Fichero: fc2i.h (Fortran & C Communication Interface)
** Fecha: 21 de octubre de 2010
** Revision: 28 de octubre de 2010
**	     Añadido recibir y enviar int_type
** Autor: Asier Lacasta Soto (asierlacasta@gmail.com)
** Desc.: Interfaz de comunicación entre programas
**	 C y Fortran de manera bidireccional. Esta
**	 interfaz permite al programador transferir
**	 Datos entre programas de estos dos tipos.
** Ackn.: Jose Manuel Colom (jm@unizar.es)
**	  Mario Morales (mmorales@unizar.es)
******************************************************/

#ifndef _LIBRERIA_FC2I
#define _LIBRERIA_FC2I 1

#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*****************************************************/
int creaInterfaz(char *nombre);
/* Pre: nombre!=NULL
   post: Devuelve el identificador de la interfaz
*****************************************************/
void eliminaInterfaz(char *nombre);
/* Pre: nombre!=NULL
   post: -
*****************************************************/
int abrirInterfazEnv(char *nombre);
/* Pre: nombre!=NULL
   post: -
*****************************************************/
int abrirInterfazRec(char *nombre);
/* Pre: nombre!=NULL
   post: -
*****************************************************/
int cerrarInterfazRec(int idInt);
/* Pre: nombre!=NULL
   post: -
*****************************************************/
int cerrarInterfazEnv(int idInt);
/* Pre: nombre!=NULL
   post: -
*****************************************************/
int enviaChar(char *cadena,int idInt);
/* Pre: Existe interfaz idInt
   post: Devuelve 1 si ok.  
*****************************************************/
int enviaFloat(float numero,int idInt);
/* Pre: Existe interfaz idInt
   post: Cuidado! La resolución es baja.
*****************************************************/
int enviaInt(int numero,int idInt);
/* Pre: Existe interfaz idInt
   post: Devuelve 1 si ok.
*****************************************************/
void recibeChar(int idInt, char* cadena);
/* Pre: Existe interfaz idInt
   post: 
*****************************************************/
int recibeFloat(int idInt, double *numero);
/* Pre: Existe interfaz idInt
   post: 
*****************************************************/
double recibeInt(int idInt, int *numero);
/* Pre: Existe interfaz idInt
   post: 
*****************************************************/	

#endif
