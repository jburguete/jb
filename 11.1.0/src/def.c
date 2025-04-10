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
 * \file def.c
 * \brief Source file to define the basic functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2025, Javier Burguete Tolosa.
 */
#include "def.h"

char *jb_error_message = NULL;  ///< Error message string.
char *jb_warning_message = NULL;        ///< Warning message string.
void (*jb_error_show) () = NULL;
///< Pointer to the function to show error messages.
void (*jb_warning_show) () = NULL;
///< Pointer to the function to show warning messages.

/**
 * Function to set locales.
 */
void
jb_set_locales (const char *program_name,       ///< program name.
                const char *locale_dir, ///< locale directory.
                const char *locale_all, ///< all locales set.
                const char *locale_numeric)     ///< numeric locale set.
{
  char *buffer, *buffer2;

  // Setting locale
  setlocale (LC_ALL, locale_all);

  // Setting numerical locale
  setlocale (LC_NUMERIC, locale_numeric);

  // Setting the program name and locale directory to find locale files
  buffer2 = g_get_current_dir ();
  buffer = g_build_filename (buffer2, locale_dir, NULL);
  g_free (buffer2);
  bindtextdomain (program_name, buffer);
  g_free (buffer);

  // Setting the format of the codeset files (UTF-8)
  bind_textdomain_codeset (program_name, "UTF-8");

  // Loading the locale strings
  textdomain (program_name);
}

/**
 * Function to init locales in the JB library.
 */
void
jb_init (void)
{
  jb_set_locales ("jb", JB_LOCALE, "", "C");
}

/**
 * Function to free a pointer with the free function and to set the pointer to
 * NULL.
 */
void
jb_free_null (void **p)         ///< pointer to free.
{
  free (*p);
  *p = NULL;
}

/**
 * An empty function useful to pass as pointer to functions.
 */
void
jb_function_null (void)
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
  void *q;
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
jb_flength (FILE *file)         ///< file.
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
jb_slist_free (GSList **list)   ///< list.
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
jb_bin_read (FILE *file,        ///< file.
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
jb_bin_write (FILE *file,       ///< file.
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
jb_get_ncores (void)
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

/**
 * Function to add messages to a string.
 *
 * \return new string pointer, it has to be freed with g_free.
 */
static char *
jb_string_add (char *string,    ///< string.
               const char *first_message,       ///< first message,
               ...)             ///< additional messages (NULL-terminated).
{
  va_list args;
  char **msg;
  char *buffer;
  unsigned int i, n;

  // arguments number
  va_start (args, first_message);
  for (n = 1; va_arg (args, const char*);) ++n;
  va_end (args);

  // array of arguments
  msg = (char**) malloc ((n + 2) * sizeof (char*));
  msg[0] = first_message;
  va_start (args, first_message);
  for (i = 1; i < n; ++i)
    msg[i] = (char*) va_arg (args, const char*);
  va_end (args);
  if (string)
    msg[i++] = string;
  msg[i] = NULL;

  // concatenation
  buffer = (char*) g_strjoinv ("", (gchar**) msg);

  // free memory and exit
  free (msg);
  g_free (string);
  return buffer;
}

/**
 * Function to add error messages.
 */
void
jb_error_add (const char *first_message,        ///< first message,
              ...)              ///< additional messages (NULL-terminated).
{
  va_list args;
  char *buffer;
  buffer = jb_error_message;
  va_start (args, first_message);
  jb_error_message = jb_string_add (jb_error_message, first_message, args);
  va_end (args);
  g_free (buffer);
}

/**
 * Function to free the memory used by error messages.
 */
void
jb_error_destroy ()
{
  g_free (jb_error_message);
  jb_error_message = NULL;
}

/**
 * Function to add warning messages.
 */
void
jb_warning_add (const char *first_message,      ///< first message,
                ...)            ///< additional messages (NULL-terminated).
{
  va_list args;
  char *buffer;
  buffer = jb_warning_message;
  va_start (args, first_message);
  jb_warning_message = jb_string_add (jb_warning_message, first_message, args);
  va_end (args);
  g_free (buffer);
}

/**
 * Function to free the memory used by warning messages.
 */
void
jb_warning_destroy ()
{
  g_free (jb_warning_message);
  jb_warning_message = NULL;
}

/**
 * Function to read a binary file on a buffer.
 *
 * \return buffer pointer (it has to be freed with free()) on success, NULL
 * pointer on error.
 */
char *
jb_read_file (const char *name, ///< file name string.
              long int *size)   ///< file size.
{
  FILE *file;
  char *buffer;
  const char *error_msg;
  file = fopen (name, "rb");
  if (!file)
    {
      error_msg = _("unable to open the file");
      goto exit_on_error;
    }
  fseek (file, 0l, SEEK_END);
  *size = ftell (file);
  buffer = (char *) malloc (*size);
  if (!buffer)
    {
      error_msg = _("not enough memory to open the file");
      goto exit_on_error;
    }
  rewind (file);
  if (!fread (buffer, *size, 1, file))
    {
      error_msg = _("unable to read the file");
      free (buffer);
      goto exit_on_error;
    }
  fclose (file);
  return buffer;

exit_on_error:
  jb_error_show ();
  return NULL;
}
