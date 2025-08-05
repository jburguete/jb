/* JB - A library with useful mathematical, XML, JSON, GTK and OpenGL functions.
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
 * \file json.h
 * \brief Header file with useful JSON functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2025, Javier Burguete Tolosa.
 */
#ifndef JB_JSON__H
#define JB_JSON__H 1

#include "math.h"
#include <glib.h>
#include <json-glib/json-glib.h>

JBDOUBLE jb_json_object_get_float (JsonObject *, const char *, int *);
JBDOUBLE jb_json_object_get_float_with_default
  (JsonObject *, const char *, int *, JBDOUBLE);
void jb_json_object_set_float_with_format
  (JsonObject *, const char *, char *, JBDOUBLE);
void jb_json_object_set_float (JsonObject *, const char *, JBDOUBLE);
void jb_json_object_set_float_with_default
  (JsonObject *, const char *, JBDOUBLE, JBDOUBLE);
long int jb_json_object_get_int (JsonObject *, const char *, int *);
long int jb_json_object_get_int_with_default (JsonObject *, const char *,
                                              int *, long int);
void jb_json_object_set_int (JsonObject *, const char *, long int);
void jb_json_object_set_int_with_default (JsonObject *, const char *,
                                          long int, long int);
unsigned long int jb_json_object_get_uint (JsonObject *, const char *, int *);
unsigned long int jb_json_object_get_uint_with_default (JsonObject *,
                                                        const char *,
                                                        int *,
                                                        unsigned long int);
void jb_json_object_set_uint (JsonObject *, const char *, unsigned long int);
void jb_json_object_set_uint_with_default (JsonObject *, const char *,
                                           unsigned long int,
                                           unsigned long int);
JBDOUBLE jb_json_object_get_time (JsonObject *, const char *, int *);
JBDOUBLE jb_json_object_get_time_with_default
  (JsonObject *, const char *, int *, JBDOUBLE);
void jb_json_object_set_time (JsonObject *, const char *, JBDOUBLE);
void jb_json_object_set_time_with_default
  (JsonObject *, const char *, JBDOUBLE, JBDOUBLE);
JBDOUBLE *jb_json_object_get_floats (JsonObject *, const char *,
                                     unsigned int *);
long int *jb_json_object_get_ints (JsonObject *, const char *, unsigned int *);
unsigned long int *jb_json_object_get_uints (JsonObject *, const char *,
                                             unsigned int *);

#endif
