/*******************************************************
** Fichero: fc2i.c (Fortran & C Communication Interface)
** Fecha: 21 de octubre de 2010
** Autor: Asier Lacasta Soto (asierlacasta@gmail.com)
** Revision: 28 de octubre de 2010
**       Añadido recibir y enviar int_type
** Desc.: Interfaz de comunicación entre programas
**   C y Fortran de manera bidireccional. Esta
**   interfaz permite al programador transferir
**   Datos entre programas de estos dos tipos.
** Ackn.: Jose Manuel Colom (jm@unizar.es)
**    Mario Morales (mmorales@unizar.es)
******************************************************/
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

/*****************************************************/
int
creaInterfaz (char *nombre)
{
  umask (0);
  return (mknod (nombre, S_IFIFO | 0666, 0));
}

/*****************************************************/
void
eliminaInterfaz (char *nombre)
{
  NULL;
}

/*****************************************************/
int
abrirInterfazEnv (char *nombre)
{
  return (open (nombre, O_WRONLY));
}

/*****************************************************/
int
cerrarInterfazEnv (int idInt)
{
  return (close (idInt));
}

/*****************************************************/
int
abrirInterfazRec (char *nombre)
{
  return (open (nombre, O_RDONLY));
}

/*****************************************************/
int
cerrarInterfazRec (int idInt)
{
  return (close (idInt));
}

/*****************************************************/
int
enviaChar (char *cadena, int idInt)
{
  int leng;
  strcat (cadena, "\n");
  leng = strlen (cadena);
  return (write (idInt, cadena, leng));
}

/*****************************************************/
int
enviaFloat (float numero, int idInt)
{
  char flo[100];
  sprintf (flo, "%f\n", numero);
  return (write (idInt, flo, strlen (flo)));
}

/*****************************************************/
int
enviaInt (int numero, int idInt)
{
  char flo[100];
  sprintf (flo, "%d\n", numero);
  return (write (idInt, flo, strlen (flo)));
}

/*****************************************************/
void
recibeChar (int idInt, char *cadena)
{
  read (idInt, cadena, 23);
}

/*****************************************************/
double
recibeFloat (int idInt, double *numero)
{
  char flo[22];
  double aux;
  int res;
  while (!read (idInt, flo, 23));
  aux = atof (flo);
  *numero = aux;
  return (*numero);
}

/*****************************************************/
double
recibeInt (int idInt, int *numero)
{
  char flo[22];
  int aux;
  int res;
  int L;
  while (!read (idInt, flo, 23));
  aux = atol (flo);
  *numero = aux;
  return (*numero);
}

/*****************************************************/
