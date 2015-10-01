/* JB - A library with useful mathematical, XML, GTK+ and OpenGL functions.
 *
 * Copyright 2005-2014, Javier Burguete Tolosa.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 	1. Redistributions of source code must retain the above copyright notice,
 * 		this list of conditions and the following disclaimer.
 *
 * 	2. Redistributions in binary form must reproduce the above copyright notice,
 * 		this list of conditions and the following disclaimer in the
 * 		documentation and/or other materials provided with the distribution.
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
 * \copyright Copyright 2005-2014, Javier Burguete Tolosa.
 */
#include "jb_def.h"

/**
 * \fn void JBChange(void **a, void **b)
 * \brief Function to interchange two pointers.
 * \param a
 * \brief A pointer to interchange.
 * \param b
 * \brief A pointer to interchange.
 */
#if !INLINE_JB_CHANGE
void JBChange(void **a, void **b)
{
    _JBChange(a,b);
}
#endif

/**
 * \fn void jb_free_null(void **p)
 * \brief Function to free a pointer with the g_free function and to set the
 *   pointer to NULL.
 * \param p
 * \brief A pointer to free.
 */
#if JB_FREE_NULL
void jb_free_null(void **p)
{
    g_free(*p);
    *p=0;
}
#endif

/**
 * \fn void jb_function_null()
 * \brief An empty function useful to pass as pointer to functions.
 */
#if JB_FUNCTION_NULL
void jb_function_null() {}
#endif

/**
 * \fn void* jb_realloc(void *p, const int n)
 * \brief Function to realloc with g_realloc() a pointer and freeing it with
 *   g_free() on error.
 * \param p
 * \brief A pointer.
 * \param n
 * \brief Size of the reallocated pointer.
 * \return Reallocated pointer on success or NULL on error.
 */
#if JB_REALLOC
void* jb_realloc(void *p, const int n)
{
    register void *q;
    q = g_realloc(p, n);
    if (!q && n) g_free(p);
    return q;
}
#endif

/**
 * \fn void* jb_try_realloc(void *p, const int n)
 * \brief Function to realloc with g_try_realloc() a pointer and freeing it with
 *   g_free() on error.
 * \param p
 * \brief A pointer.
 * \param n
 * \brief Size of the reallocated pointer.
 * \return Reallocated pointer on success or NULL on error.
 */
#if JB_TRY_REALLOC
void* jb_try_realloc(void *p, const int n)
{
    register void *q;
    q = g_try_realloc(p, n);
    if (!q) g_free(p);
    return q;
}
#endif

/**
 * \fn char* jb_strdup(char *buffer)
 * \brief Function to copy a string truncating the size to JB_BUFFER_SIZE.
 * \param buffer
 * \brief String. The string have to be freed with g_free().
 * \return Pointer to the string copy or NULL on error.
 */
#if JB_STRDUP
char* jb_strdup(char *buffer)
{
    return g_strndup(buffer, JB_BUFFER_SIZE - 1);
}
#endif

/**
 * \fn long int jb_flength(FILE *file)
 * \brief Function to obtain the length of a file.
 * \param file
 * \brief File.
 * \return File length.
 */
#if !INLINE_JB_FLENGTH
long int jb_flength(FILE *file)
{
    return _jb_flength(file);
}
#endif

/**
 * \fn void jb_slist_free(GSList **list)
 * \brief Function to free a GSList, all their elements and set the list to
 *   NULL.
 * \param list
 * \brief List.
 */
#if JB_SLIST_FREE
void jb_slist_free(GSList **list)
{
    GSList *l;
    if (*list)
        {
            for (l = *list; l; l = l->next) g_free(l->data);
            g_slist_free(*list);
            *list = 0;
        }
}
#endif

/**
 * \fn int jb_bin_read(FILE *file, char *buffer)
 * \brief Function to read a string in a binary file. The length of the string
 *   is fixed in the first position (4 bytes) of the file.
 * \param file
 * \brief File.
 * \param buffer
 * \brief String.
 * \return 0 on error, >0 on success.
 */
#if !INLINE_JB_BIN_READ
int jb_bin_read(FILE *file,char *buffer)
{
    return _jb_bin_read(file, buffer);
}
#endif

/**
 * \fn void jb_bin_write(FILE *file, char *buffer)
 * \brief Function to write a string in a binary file. The length of the string
 *   is fixed in the first position (4 bytes) of the file.
 * \param file
 * \brief File.
 * \param buffer
 * \brief String.
 */
#if !INLINE_JB_BIN_WRITE
void jb_bin_write(FILE *file, char *buffer)
{
    _jb_bin_write(file, buffer);
}
#endif

/**
 * \fn void jb_make_time(struct tm *sys_date, JBDOUBLE *sys_sec, int *error)
 * \brief Function to code a date in struct tm format to a JBDOUBLE number.
 * \param sys_date
 * \brief Date in struct tm format.
 * \param sys_sec
 * \brief Pointer to the date in JBDOUBLE format.
 * \param error
 * \brief 1 on success, 0 on error.
 */
#if !INLINE_JB_MAKE_TIME
void jb_make_time(struct tm *sys_date, JBDOUBLE *sys_sec, int *error)
{
    _jb_make_time(sys_date, sys_sec, error);
}
#endif

/**
 * \fn JBDOUBLE jb_get_time(const char *string, int *error)
 * \brief Function to code a date in string format to a JBDOUBLE number.
 * \param string
 * \brief Date in string format.
 * \param error
 * \brief 1 on success, 0 on error.
 * \return Date in JBDOUBLE format.
 */
#if !INLINE_JB_GET_TIME
JBDOUBLE jb_get_time(const char *string, int *error)
{
    return _jb_get_time(string, error);
}
#endif

/**
 * \fn JBDOUBLE jb_get_time_file(FILE *file, int *error)
 * \brief Function to read a date of a file in string format to a JBDOUBLE
 *   number.
 * \param file
 * \brief File.
 * \param error
 * \brief 1 on success, 0 on error.
 * \return Date in JBDOUBLE format.
 */
#if !INLINE_JB_GET_TIME_FILE
JBDOUBLE jb_get_time_file(FILE *file, int *error)
{
    return _jb_get_time_file(file, error);
}
#endif

/**
 * \fn char* jb_set_time(JBDOUBLE time)
 * \brief Function to write in a string a date coded in a JBDOUBLE number
 *   format.
 * \param time
 * \brief Date coded in a JBDOUBLE number format.
 * \return String on success, 0 on error
 */
#if !INLINE_JB_SET_TIME
char* jb_set_time(JBDOUBLE time)
{
    return _jb_set_time(time);
}
#endif
