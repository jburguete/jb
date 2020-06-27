/* JB - A library with useful mathematical, XML, GTK+ and OpenGL functions.
 *
 * Copyright 2005-2020, Javier Burguete Tolosa.
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
 * \file jb_def.c
 * \brief Source file to define the basic functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2020, Javier Burguete Tolosa.
 */
#include "jb_def.h"

/**
 * Function to init locales in the JB library.
 */
void
jb_init ()
{
  char *buffer, *buffer2;
  setlocale (LC_ALL, "");
  setlocale (LC_NUMERIC, "C");
  buffer2 = g_get_current_dir ();
  buffer = g_build_filename (buffer2, JB_LOCALE, NULL);
  g_free (buffer2);
  bindtextdomain ("jb", buffer);
  g_free (buffer);
  bind_textdomain_codeset ("jb", "UTF-8");
  textdomain ("jb");
}

/**
 * Function to free a pointer with the g_free function and to set the pointer to
 * NULL.
 */
void
jb_free_null (void **p)         ///< pointer to free.
{
  g_free (*p);
  *p = NULL;
}

/**
 * An empty function useful to pass as pointer to functions.
 */
void
jb_function_null ()
{
}

/**
 * Function to realloc with g_try_realloc a pointer and freeing it with g_free
 * on error.
 *
 * \return reallocated pointer on success or NULL on error.
 */
void *
jb_realloc (void *p,            ///< a pointer.
            const int n)        ///< size of the reallocated pointer.
{
  register void *q;
  q = g_try_realloc (p, n);
  if (!q)
    g_free (p);
  return q;
}

/**
 * Function to copy a string truncating the size to JB_BUFFER_SIZE.
 *
 * \return Pointer to the string copy or NULL on error. It has to be freed with
 * g_free.
 */
char *
jb_strdup (char *buffer)        ///< string to copy.
{
  return g_strndup (buffer, JB_BUFFER_SIZE - 1);
}

/**
 * Function to obtain the length of a file.
 *
 * \return file length.
 */
long int
jb_flength (FILE * file)        ///< file.
{
  long int p, q;
  q = ftell (file);
  fseek (file, 0l, SEEK_END);
  p = ftell (file);
  fseek (file, q, SEEK_SET);
  return p;
}

/**
 * Function to free a GSList, all their elements using g_free and set the list
 * to NULL.
 */
void
jb_slist_free (GSList ** list)  ///< list.
{
  if (*list)
    {
      g_slist_free_full (*list, g_free);
      *list = NULL;
    }
}

/**
 * Function to read a string in a binary file. The length of the string is fixed
 * in the first position (4 bytes) of the file.
 *
 * \return 0 on error, >0 on success.
 */
int
jb_bin_read (FILE * file,       ///< file.
             char *buffer)      ///< string.
{
  uint32_t n;
  fread (&n, sizeof (uint32_t), 1, file);
  if (n == 0 || n > JB_BUFFER_SIZE)
    return 0;
  return fread (buffer, n, 1, file);
}

/**
 * Function to write a string in a binary file. The length of the string is
 * fixed in the first position (4 bytes) of the file.
 */
void
jb_bin_write (FILE * file,      ///< file.
              char *buffer)     ///< string.
{
  uint32_t n;
  n = strlen (buffer) + 1;
  fwrite (&n, sizeof (uint32_t), 1, file);
  fwrite (buffer, n, 1, file);
}

/**
 * Function to calculate the number of cores.
 * 
 * \return number of cores.
 */
int
jb_get_ncores ()
{
#if HAVE_GTOP
  int ncores;
  glibtop *top;
  top = glibtop_init ();
  ncores = top->ncpu + 1;
  glibtop_close ();
  return ncores;
#elif HAVE_GET_NPROCS
  return get_nprocs ();
#elif defined(G_OS_WIN32)
  SYSTEM_INFO sysinfo;
  GetSystemInfo (&sysinfo);
  return sysinfo.dwNumberOfProcessors;
#else
  return (int) sysconf (_SC_NPROCESSORS_ONLN);
#endif
  /*
     BSD:
     int cores, mib[2];
     size_t len = sizeof(cores);
     mib[0] = CTL_HW;
     mib[1] = HW_NCPU;
     if (sysctl(mib, 2, &cores, &len, NULL, 0) != 0)
     {
     perror("sysctl");
     cores = -1;
     }

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

   */
}
