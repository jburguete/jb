/* JB - A library with useful mathematical, XML, GTK+ and OpenGL functions.
 *
 * Copyright 2005-2022, Javier Burguete Tolosa.
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
 * \file jb_def.h
 * \brief Header file to define the basic macros and functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2022.
 */
#ifndef JB_DEF__H
#define JB_DEF__H 1

#define _GNU_SOURCE
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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
///< Macro to use the GTK+ library on visual programs.

#include "jb_config.h"

// Simplifying gettext
#define _(str) gettext(str)

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
JBChange (void **a,             ///< a pointer to interchange.
          void **b)             ///< a pointer to interchange.
{
  void *c;
  JB_CHANGE (*a, *b, c);
}

#define jb_change(a, b) (JBChange((void**)&a, (void**)&b))
///< Macro to interchange two pointers.

void jb_init ();
void jb_function_null ();
void jb_free_null (void **);
void *jb_realloc (void *, const int);
char *jb_strdup (char *);
long int jb_flength (FILE * file);
void jb_slist_free (GSList ** list);
int jb_bin_read (FILE * file, char *buffer);
void jb_bin_write (FILE * file, char *buffer);
int jb_get_ncores ();

#endif
