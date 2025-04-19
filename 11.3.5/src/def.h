/* JB - A library with useful mathematical, XML, JSON, GTK and OpenGL
 * functions.
 *
 * Copyright 2005-2025, Javier Burguete Tolosa.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
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
 * \file def.h
 * \brief Header file to define the basic macros and functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2025.
 */
#ifndef JB_DEF__H
#define JB_DEF__H 1

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>
#if HAVE_SYSINFO
#include <sys/sysinfo.h>
#endif
#include <glib.h>
#include <glib/gstdio.h>
#if HAVE_GTOP
#include <glibtop.h>
#include <glibtop/close.h>
#endif
#include <libintl.h>

#define JBW_NO 1
///< Macro to use on terminal programs.
#define JBW_GTK 2
///< Macro to use the GTK library on visual programs.

#include "jb_config.h"

// Simplifying gettext
#define _(str) gettext(str)
///< Macro to simplify gettext usage

// Detecting configuration errors
#if (JBW < JBW_NO || JBW > JBW_GTK)
#error "Unknown JB windows"
#endif

/**
 * \def JB_LOCALE
 * \brief Macro to define the directory to search the locale language files.
 */
#ifdef G_OS_WIN32
#define JB_LOCALE "../share/locale"
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#if JB_DEBUG_FILE
#undef stderr
extern FILE *stderr;
#endif
#else
#define JB_LOCALE "../locale"
#endif

#define JB_PROTECT(a, b, c) ((a < b)? 1: (a > c)? 1: 0)
///< Macro returning FALSE if a is in [b,c].

#define JB_POINTER_SIZE(a, b) ((size_t)&(a) - (size_t)&(b))
///< Macro to calculate the size in bytes between two fields of a structure.

#define JB_CHANGE(a, b, c) (c = a, a = b, b = c)
///< Macro to interchange two variables (change a and b using the auxiliary c).

/**
 * Function to interchange two pointers.
 */
static inline void
JBChange (void **restrict a,    ///< a pointer to interchange.
          void **restrict b)    ///< a pointer to interchange.
{
  void *restrict c;
  JB_CHANGE (*a, *b, c);
}

#define jb_change(a, b) (JBChange((void**)&a, (void**)&b))
///< Macro to interchange two pointers.

extern char *jb_error_message;
extern char *jb_warning_message;
extern void (*jb_error_show) ();
extern void (*jb_warning_show) ();

void jb_set_locales (const char *program_name, const char *locale_dir,
                     const char *locale_all, const char *locale_numeric);
void jb_init (void);
void jb_function_null (void);
void jb_free_null (void **);
void *jb_realloc (void *, const int);
char *jb_strdup (char *);
long int jb_flength (FILE * file);
void jb_slist_free (GSList ** list);
int jb_bin_read (FILE * file, char *buffer);
void jb_bin_write (FILE * file, char *buffer);
int jb_get_ncores (void);
void jb_error_add (const char *first_message, ...);
void jb_error_destroy ();
void jb_warning_add (const char *first_message, ...);
void jb_warning_destroy ();
char *jb_read_file (const char *name, long int *size);

/**
 * Function to code a date in struct tm format to a double number.
 */
static inline void
jbm_make_time (struct tm *sys_date,     ///< date in struct tm format.
               double *sys_sec,
               ///< pointer to the date in double format.
               int *error)      ///< 1 on success, 0 on error.
{
  time_t sys_t;
  sys_date->tm_year -= 1900;
  --sys_date->tm_mon;
  sys_date->tm_sec = 0;
  sys_date->tm_isdst = 0;
  sys_t = mktime (sys_date);
  if (sys_t == -1)
    *error = 0;
  else
    *error = 1;
  *sys_sec += (double) sys_t;
}

/**
 * Function to code a date in string format to a double number.
 *
 * \return date in double format.
 */
static inline double
jbm_get_time (const char *string,       ///< date in string format.
              int *error)       ///< 1 on success, 0 on error.
{
  struct tm sys_date[1];
  double sys_sec;
  *error = sscanf (string, "%d%d%d%d%d%lf",
                   &sys_date->tm_year,
                   &sys_date->tm_mon,
                   &sys_date->tm_mday,
                   &sys_date->tm_hour, &sys_date->tm_min, &sys_sec);
  printf ("error=%d\n", *error);
  if (*error < 0)
    *error = 0;
  if (*error == 6)
    jbm_make_time (sys_date, &sys_sec, error);
  return sys_sec;
}

/**
 * Function to read a date of a file in string format to a double number.
 *
 * \return date in double format.
 */
static inline double
jbm_get_time_file (FILE *file,  ///< file.
                   int *error)  ///< 1 on success, 0 on error.
{
  struct tm sys_date[1];
  double sys_sec;
  *error = fscanf (file, "%d%d%d%d%d%lf",
                   &sys_date->tm_year,
                   &sys_date->tm_mon,
                   &sys_date->tm_mday,
                   &sys_date->tm_hour, &sys_date->tm_min, &sys_sec);
  if (*error < 0)
    *error = 0;
  if (*error == 6)
    jbm_make_time (sys_date, &sys_sec, error);
  return sys_sec;
}

/**
 * Function to write in a string a date coded in a double number format.
 *
 * \return string on success, 0 on error
 */
static inline char *
jbm_set_time (double time)      ///< date coded in a double number format.
{
  struct tm *sys_date;
  char *buffer;
  time_t sys_t;
  buffer = (char *) g_try_malloc (JB_BUFFER_SIZE * sizeof (char));
  if (buffer)
    {
      sys_t = (time_t) time;
      time -= (double) sys_t;
      sys_date = localtime (&sys_t);
      snprintf (buffer, JB_BUFFER_SIZE, "%d %d %d %d %d %lg",
                sys_date->tm_year + 1900,
                sys_date->tm_mon + 1,
                sys_date->tm_mday,
                sys_date->tm_hour, sys_date->tm_min, time + sys_date->tm_sec);
      buffer =
        (char *) jb_realloc (buffer, (1 + strlen (buffer)) * sizeof (char));
    }
  return buffer;
}

#endif
