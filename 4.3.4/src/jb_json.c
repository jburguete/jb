/* JB - A library with useful mathematical, XML, JSON, GTK+ and OpenGL
 * functions.
 *
 * Copyright 2005-2023, Javier Burguete Tolosa.
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
 * \file jb_json.c
 * \brief Source file with useful JSON functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2023, Javier Burguete Tolosa.
 */
#include "jb_json.h"

/**
 * Function to get a floating number, in JBDOUBLE format, from a property of a
 * JSON object.
 *
 * \return floating number value in JBDOUBLE format.
 */
JBDOUBLE
jb_json_object_get_float (JsonObject * object,  ///< JSON object struct.
                          const char *prop,     ///< JSON object property.
                          int *error)
                          ///< error code (1 on success, 0 on error).
{
  const char *buffer;
  JBDOUBLE x = 0.L;
  *error = 0;
  buffer = (const char *) json_object_get_string_member (object, prop);
  if (buffer)
    *error = sscanf (buffer, FRL, &x);
  return x;
}

/**
 * Function to get a floating number, in JBDOUBLE format, from a property of a
 * JSON object or a default value if the object has not the property.
 *
 * \return floating number value in JBDOUBLE format.
 */
JBDOUBLE
jb_json_object_get_float_with_default (JsonObject * object,
                                       ///< JSON object struct.
                                       const char *prop,
                                       ///< JSON object property.
                                       int *error,
///< error code (1 on success, 0 on error).
                                       JBDOUBLE def)    ///< default value.
{
  if (!json_object_get_member (object, prop))
    {
      *error = 1;
      return def;
    }
  return jb_json_object_get_float (object, prop, error);
}

/**
 * Function to set a floating number with format in a property of a JSON object.
 */
void
jb_json_object_set_float_with_format (JsonObject * object,
                                      ///< JSON object struct.
                                      const char *prop,
                                      ///< JSON object property.
                                      char *format,     ///< C-format string.
                                      JBDOUBLE x)
///< floating number value in JBDOUBLE format.
{
  const char buffer[JB_BUFFER_SIZE];
  snprintf (buffer, JB_BUFFER_SIZE, format, x);
  json_object_set_string_member (object, prop, (const gchar *) buffer);
}

/**
 * Function to set a floating number with default format (see FWL macro) in a
 * property of a JSON object.
 */
void
jb_json_object_set_float (JsonObject * object,  ///< JSON object struct.
                          const char *prop,     ///< JSON object property.
                          JBDOUBLE x)
///< floating number value in JBDOUBLE format.
{
  jb_json_object_set_float_with_format (object, prop, FWL, x);
}

/**
 * Function to set a floating number with default format (see FWL macro) in a
 * property of a JSON object or none if the number is equal to a default value.
 */
void
jb_json_object_set_float_with_default (JsonObject * object,
                                       ///< JSON object struct.
                                       const char *prop,
                                       ///< JSON object property.
                                       JBDOUBLE x,
///< floating number value in JBDOUBLE format.
                                       JBDOUBLE def)    ///< default value.
{
  if (x != def)
    jb_json_object_set_float (object, prop, x);
}

/**
 * Function to get an integer number, in long int format, from a property of a
 * JSON object.
 *
 * \return integer number value in long int format.
 */
long int
jb_json_object_get_int (JsonObject * object,
                        ///< JSON object struct.
                        const char *prop,
                        ///< JSON object property having the number.
                        int *error)
                        ///< error code (1 on success, 0 on error).
{
  const char *buffer;
  long int x = 0;
  *error = 0;
  buffer = (const char *) json_object_get_string_member (object, prop);
  if (buffer)
    *error = sscanf (buffer, "%ld", &x);
  return x;
}

/**
 * Function to get an integer number, in long int format, from a property of a
 * JSON object or a default value if the object has not the property.
 *
 * \return integer number value in long int format.
 */
long int
jb_json_object_get_int_with_default (JsonObject * object,
                                     ///< JSON object struct.
                                     const char *prop,
///< JSON object property having the number.
                                     int *error,
                                     ///< error code (1 on success, 0 on error).
                                     long int def)      ///< default value.
{
  if (!json_object_get_member (object, prop))
    {
      *error = 1;
      return def;
    }
  return jb_json_object_get_int (object, prop, error);
}

/**
 * Function to set an integer number in a property of a JSON object.
 */
void
jb_json_object_set_int (JsonObject * object,    ///< JSON object struct.
                        const char *prop,       ///< JSON object property.
                        long int x)
                        ///< integer number value in long int format.
{
  const char buffer[JB_BUFFER_SIZE];
  snprintf (buffer, JB_BUFFER_SIZE, "%ld", x);
  json_object_set_string_member (object, prop, (const gchar *) buffer);
}

/**
 * Function to set an integer number in a property of a JSON object or none if
 * the number is equal to a default value.
 */
void
jb_json_object_set_int_with_default (JsonObject * object,
                                     ///< JSON object struct.
                                     const char *prop,
                                     ///< JSON object property.
                                     long int x,
///< integer number value in long int format.
                                     long int def)      ///< default value.
{
  if (x != def)
    jb_json_object_set_int (object, prop, x);
}

/**
 * Function to get an unsigned integer number, in unsigned long int format, from
 * a property of a JSON object.
 *
 * \return unsigned integer number value in unsigned long int format.
 */
unsigned long int
jb_json_object_get_uint (JsonObject * object,
                         ///< JSON object struct.
                         const char *prop,
                         ///< JSON object property having the number.
                         int *error)
                         ///< error code (1 on success, 0 on error).
{
  const char *buffer;
  unsigned long int x = 0;
  *error = 0;
  buffer = (const char *) json_object_get_string_member (object, prop);
  if (buffer)
    *error = sscanf (buffer, "%ld", &x);
  return x;
}

/**
 * Function to get an unsigned integer number, in unsigned long int format, from
 * a property of a JSON object or a default value if the object has not the
 * property.
 *
 * \return unsigned integer number value in unsigned long int format.
 */
unsigned long int
jb_json_object_get_uint_with_default (JsonObject * object,
                                     ///< JSON object struct.
                                     const char *prop,
///< JSON object property having the number.
                                     int *error,
                                     ///< error code (1 on success, 0 on error).
                                     unsigned long int def)
                                     ///< default value.
{
  if (!json_object_get_member (object, prop))
    {
      *error = 1;
      return def;
    }
  return jb_json_object_get_uint (object, prop, error);
}

/**
 * Function to set an unsigned integer number in a property of a JSON object.
 */
void
jb_json_object_set_uint (JsonObject * object,   ///< JSON object struct.
                         const char *prop,      ///< JSON object property.
                         unsigned long int x)
///< unsigned integer number value in unsigned long int format.
{
  const char buffer[JB_BUFFER_SIZE];
  snprintf (buffer, JB_BUFFER_SIZE, "%ld", x);
  json_object_set_string_member (object, prop, (const gchar *) buffer);
}

/**
 * Function to set an unsgned integer number in a property of a JSON object or
 * none if the number is equal to a default value.
 */
void
jb_json_object_set_uint_with_default (JsonObject * object,
                                      ///< JSON object struct.
                                      const char *prop,
                                      ///< JSON object property.
                                      unsigned long int x,
///< integer number value in unsigned long int format.
                                      unsigned long int def)
                                      ///< default value.
{
  if (x != def)
    jb_json_object_set_uint (object, prop, x);
}

/**
 * Function to get a time, in format "year month day hour minute seconds", from
 * a property of a JSON object.
 *
 * \return date in floating point format.
 */
JBDOUBLE
jb_json_object_get_time (JsonObject * object,   ///< JSON object struct.
                         const char *prop,      ///< JSON object property.
                         int *error)
                         ///< error code (1 on success, 0 on error).
{
  const char *buffer;
  JBDOUBLE t;
  *error = 0;
  buffer = (const char *) json_object_get_string_member (object, prop);
  if (!buffer)
    return 0.;
  t = jbm_get_time (buffer, error);
  if (*error != 1)
    *error = 0;
  return t;
}

/**
 * Function to get a time, in format "year month day hour minute seconds", from
 * a property of a JSON object or a default value if the object has not the property.
 *
 * \return date in floating point format.
 */
JBDOUBLE
jb_json_object_get_time_with_default (JsonObject * object,
                                      ///< JSON object struct.
                                      const char *prop,
                                      ///< JSON object property.
                                      int *error,
///< error code (1 on success, 0 on error).
                                      JBDOUBLE def)     ///< default value.
{
  if (!json_object_get_member (object, prop))
    {
      *error = 1;
      return def;
    }
  return jb_json_object_get_time (object, prop, error);
}

/**
 * Function to set a time, in format "year month day hour minute seconds", on a
 * property of a JSON object.
 */
void
jb_json_object_set_time (JsonObject * object,   ///< JSON object struct.
                         const char *prop,      ///< JSON object property.
                         JBDOUBLE t)    ///< date in floating point format.
{
  const char *buffer;
  buffer = (const char *) jbm_set_time (t);
  json_object_set_string_member (object, prop, buffer);
}

/**
 * Function to set a time, in format "year month day hour minute seconds", on a
 * property of a JSON object or a default value if the object has not the
 * property.
 */
void
jb_json_object_set_time_with_default (JsonObject * object,
                                      ///< JSON object struct.
                                      const char *prop,
                                      ///< JSON object property.
                                      JBDOUBLE t,
                                      ///< date in floating point format.
                                      JBDOUBLE def)     ///< default value.
{
  if (t != def)
    jb_json_object_set_time (object, prop, t);
}
