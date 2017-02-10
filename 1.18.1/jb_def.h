/* JB - A library with useful mathematical, XML, GTK+ and OpenGL functions.
 *
 * Copyright 2005-2017, Javier Burguete Tolosa.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY Javier Burguete Tolosa ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL Javier Burguete Tolosa OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file jb_def.h
 * \brief Header file to define the basic macros and functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2017.
 */
#ifndef JB_DEF__H
#define JB_DEF__H 1

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <libintl.h>

#define JBW_NO 1
///< Macro to use on terminal programs.
#define JBW_GTK 2
///< Macro to use the Gtk+ library on visual programs.

#define JBW_GRAPHIC_GLUT 1
///< Macro to using the FreeGLUT library in graphical widgets.
#define JBW_GRAPHIC_SDL 2
///< Macro to using the SDL library in graphical widgets.
#define JBW_GRAPHIC_GLFW 3
///< Macro to using the GLFW library in graphical widgets.

#include "jb_config.h"

// Simplifying gettext
#define _(str) gettext(str)

// Detecting configuration errors
#if (JBW < JBW_NO || JBW > JBW_GTK)
#error "Unknown JB windows"
#endif
#if (JBW != JBW_NO)
#if (JBW_GRAPHIC < JBW_GRAPHIC_GLUT || JBW_GRAPHIC > JBW_GRAPHIC_GLFW)
#error "Unknown JB windows graphic"
#endif
#endif

#ifdef G_OS_WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#if JB_DEBUG_FILE
#undef stderr
extern FILE *stderr;
#endif
#endif

// Selecting the precision of the JBFLOAT and JBDOUBLE types and reading and
// writting formats
/**
 * \def JBFLOAT
 * \brief Real type with lower precision (controlled by JB_PRECISION).
 * \def JBDOUBLE
 * \brief Real type with higher precision (controlled by JB_PRECISION).
 * \def FRF
 * \brief Format to read JBFLOAT numbers.
 * \def FWF
 * \brief Format to write JBFLOAT numbers in scientific notation.
 * \def FPF
 * \brief Format to write JBFLOAT numbers in common notation.
 * \def FGF
 * \brief Format to write JBFLOAT numbers in simplified notation.
 * \def FRL
 * \brief Format to read JBDOUBLE numbers.
 * \def FWL
 * \brief Format to write JBDOUBLE numbers in scientific notation.
 * \def FPL
 * \brief Format to write JBDOUBLE numbers in common notation.
 * \def FGL
 * \brief Format to write JBDOUBLE numbers in simplified notation.
 * \def FWF2
 * \brief Format to write a JBFLOAT number in scientific notation with a space.
 * \def FG_LENGTH
 * \brief Maximum string length of JBDOUBLE numbers in simplified notation.
 */
#if JB_PRECISION == 1
#define JBFLOAT float
#define JBDOUBLE float
#define FRF "%e"
#define FWF "%.6e"
#define FPF "%.6g"
#define FGF "%.5g"
#define FRL FRF
#define FWL FWF
#define FPL FPF
#define FGL FGF
#define FG_LENGTH 12
#elif JB_PRECISION == 2
#define JBFLOAT float
#define JBDOUBLE double
#define FRF "%e"
#define FWF "%.6e"
#define FPF "%.6g"
#define FGF "%.5g"
#define FRL "%le"
#define FWL "%.13e"
#define FPL "%.13g"
#define FGL "%.5g"
#define FG_LENGTH 12
#elif JB_PRECISION == 3
#define JBFLOAT double
#define JBDOUBLE double
#define FRF "%le"
#define FWF "%.13e"
#define FPF "%.13g"
#define FGF "%.5g"
#define FRL FRF
#define FWL FWF
#define FPL FPF
#define FGL FGF
#define FG_LENGTH 12
#elif JB_PRECISION == 4
#define JBFLOAT double
#define JBDOUBLE long double
#define FRF "%le"
#define FWF "%.13e"
#define FPF "%.13g"
#define FGF "%.5g"
#define FRL "%Le"
#define FWL "%.17Le"
#define FPL "%.17Lg"
#define FGL "%.5Lg"
#define FG_LENGTH 12
#elif JB_PRECISION == 5
#define JBFLOAT long double
#define JBDOUBLE long double
#define FRF "%Le"
#define FWF "%.17Le"
#define FPF "%.17Lg"
#define FGF "%.5Lg"
#define FRL FRF
#define FWL FWF
#define FPL FPF
#define FGL FGF
#define FG_LENGTH 12
#else
#error "Unknown precision"
#endif
#define FWF2 FWF " "

#define JB_PROTECT(a, b, c) ((a < b)? 1: (a > c)? 1: 0)
///< Macro returning FALSE if a is in [b,c].

#define JB_POINTER_SIZE(a, b) ((size_t)&(a) - (size_t)&(b))
///< Macro to calculate the size between two fields of a structure.

#define JB_CHANGE(a, b, c) (c = a, a = b, b = c)
///< Macro to interchange two variables (change a and b using the auxiliary c).

static inline void
_JBChange (void **a, void **b)
{
  register void *c;
  JB_CHANGE (*a, *b, c);
}

#if INLINE_JB_CHANGE
#define JBChange _JBChange
#else
void JBChange (void **a, void **b);
#endif

#define jb_change(a, b) (JBChange((void**)&a, (void**)&b))
///< Macro to interchange two pointers.

#if JB_FREE_NULL
void jb_free_null (void **);
#endif

#if JB_FUNCTION_NULL
void jb_function_null ();
#endif

#if JB_REALLOC
void *jb_realloc (void *, const int);
#endif

#if JB_TRY_REALLOC
void *jb_try_realloc (void *, const int);
#endif

#if JB_STRDUP
char *jb_strdup (char *);
#endif

static inline long int
_jb_flength (FILE * file)
{
  register long int p, q;
  q = ftell (file);
  fseek (file, 0l, SEEK_END);
  p = ftell (file);
  fseek (file, q, SEEK_SET);
  return p;
}

#if INLINE_JB_FLENGTH
#define jb_flength _jb_flength
#else
long int jb_flength (FILE * file);
#endif

#if JB_SLIST_FREE
void jb_slist_free (GSList ** list);
#endif

static inline int
_jb_bin_read (FILE * file, char *buffer)
{
  uint32_t n;
  fread (&n, sizeof (uint32_t), 1, file);
  if (n == 0 || n > JB_BUFFER_SIZE)
    return 0;
  return fread (buffer, n, 1, file);
}

#if INLINE_JB_BIN_READ
#define jb_bin_read _jb_bin_read
#else
int jb_bin_read (FILE * file, char *buffer);
#endif

static inline void
_jb_bin_write (FILE * file, char *buffer)
{
  uint32_t n;
  n = strlen (buffer) + 1;
  fwrite (&n, sizeof (uint32_t), 1, file);
  fwrite (buffer, n, 1, file);
}

#if INLINE_JB_BIN_WRITE
#define jb_bin_write _jb_bin_write
#else
void jb_bin_write (FILE * file, char *buffer);
#endif

static inline void _jb_make_time
    (struct tm *sys_date, JBDOUBLE * sys_sec, int *error)
{
  time_t sys_t;
  sys_date->tm_year -= 1900;
  sys_date->tm_mon -= 1;
  sys_date->tm_sec = 0;
  sys_date->tm_isdst = 0;
  sys_t = mktime (sys_date);
  if (sys_t == -1)
    *error = -1;
  *sys_sec += (JBDOUBLE) sys_t;
}

#if INLINE_JB_MAKE_TIME
#define jb_make_time _jb_make_time
#else
void jb_make_time (struct tm *sys_date, JBDOUBLE * sys_sec, int *error);
#endif

static inline JBDOUBLE
_jb_get_time (const char *string, int *error)
{
  struct tm sys_date[1];
  JBDOUBLE sys_sec;
  *error = sscanf (string, "%d%d%d%d%d" FRL,
                   &sys_date->tm_year,
                   &sys_date->tm_mon,
                   &sys_date->tm_mday,
                   &sys_date->tm_hour, &sys_date->tm_min, &sys_sec);
  if (*error < 0)
    *error = 0;
  if (*error == 6)
    jb_make_time (sys_date, &sys_sec, error);
  return sys_sec;
}

#if INLINE_JB_GET_TIME
#define jb_get_time _jb_get_time
#else
JBDOUBLE jb_get_time (const char *string, int *error);
#endif

static inline JBDOUBLE
_jb_get_time_file (FILE * file, int *error)
{
  struct tm sys_date[1];
  JBDOUBLE sys_sec;
  *error = fscanf (file, "%d%d%d%d%d" FRL,
                   &sys_date->tm_year,
                   &sys_date->tm_mon,
                   &sys_date->tm_mday,
                   &sys_date->tm_hour, &sys_date->tm_min, &sys_sec);
  if (*error < 0)
    *error = 0;
  if (*error == 6)
    jb_make_time (sys_date, &sys_sec, error);
  return sys_sec;
}

#if INLINE_JB_GET_TIME_FILE
#define jb_get_time_file _jb_get_time_file
#else
JBDOUBLE jb_get_time_file (FILE * file, int *error);
#endif

static inline char *
_jb_set_time (JBDOUBLE time)
{
  char *buffer;
  time_t sys_t;
  struct tm *sys_date;
  buffer = (char *) g_try_malloc (JB_BUFFER_SIZE * sizeof (char));
  if (buffer)
    {
      sys_t = (time_t) time;
      time -= (JBDOUBLE) sys_t;
      sys_date = localtime (&sys_t);
      snprintf (buffer, JB_BUFFER_SIZE, "%d %d %d %d %d " FWL,
                sys_date->tm_year + 1900,
                sys_date->tm_mon + 1,
                sys_date->tm_mday,
                sys_date->tm_hour, sys_date->tm_min, time + sys_date->tm_sec);
      buffer =
          (char *) jb_realloc (buffer, (1 + strlen (buffer)) * sizeof (char));
    }
  return buffer;
}

#if INLINE_JB_SET_TIME
#define jb_set_time _jb_set_time
#else
char *jb_set_time (JBDOUBLE time);
#endif

/**
 * \fn static inline int jb_cores()
 * \brief Function to calculate the number of cores.
 */
static inline int
jb_cores ()
{
#ifdef G_OS_WIN32
  SYSTEM_INFO sysinfo;
  GetSystemInfo (&sysinfo);
  return sysinfo.dwNumberOfProcessors;
  /*
     #elif defined(BSD)
     int cores, mib[2];
     size_t len = sizeof(cores);
     mib[0] = CTL_HW;
     mib[1] = HW_NCPU;
     if (sysctl(mib, 2, &cores, &len, NULL, 0) != 0)
     {
     perror("sysctl");
     cores = -1;
     }
     return cores;
   */
#else
  return (int) sysconf (_SC_NPROCESSORS_ONLN);
#endif
  /*
     MacOS X:
     MPProcessorsScheduled();

     HPUX:
     struct pst_dynamic psd;

     if (pstat_getdynamic(&psd, sizeof(psd), 1, 0) == -1) {
     perror("pstat_getdynamic");
     cores = -1;
     } else {
     cores = (int)psd.psd_proc_cnt;
     }

     "integrity" OS, symbian: hard-coded to one core.

     VXWorks: a loop to check if CPU #n exists until it fails (see link)

     IRIX:
     cores = (int)sysconf(_SC_NPROC_ONLN);
   */
}

#endif
