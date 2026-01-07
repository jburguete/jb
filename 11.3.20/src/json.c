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
 *   2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
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
 * \file json.c
 * \brief Source file with useful JSON functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2025, Javier Burguete Tolosa.
 */
#include "json.h"

/**
 * Function to get a floating number, in JBDOUBLE format, from a property of a
 * JSON object.
 *
 * \return floating number value in JBDOUBLE format.
 */
JBDOUBLE
jb_json_object_get_float (JsonObject *object,   ///< JSON object struct.
                          const char *prop,     ///< JSON object property.
                          int *error)
                          ///< error code (1 on success, 0 on error).
{
  JsonNode *node;
  const char *buffer;
  JBDOUBLE x = (JBDOUBLE) 0.;
  *error = 0;
  node = json_object_get_member (object, prop);
  if (json_node_get_node_type (node) == JSON_NODE_VALUE
      && json_node_get_value_type (node) == G_TYPE_STRING)
    {
      buffer = (const char *) json_node_get_string (node);
      if (buffer)
        *error = jbm_get_double (buffer, &x);
    }
  return x;
}

/**
 * Function to get a floating number, in JBDOUBLE format, from a property of a
 * JSON object or a default value if the object has not the property.
 *
 * \return floating number value in JBDOUBLE format.
 */
JBDOUBLE
jb_json_object_get_float_with_default (JsonObject *object,
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
jb_json_object_set_float_with_format (JsonObject *object,
                                      ///< JSON object struct.
                                      const char *prop,
                                      ///< JSON object property.
                                      char *format,     ///< C-format string.
                                      JBDOUBLE x)
///< floating number value in JBDOUBLE format.
{
  char buffer[JB_BUFFER_SIZE];
  SNPRINTFL (buffer, JB_BUFFER_SIZE, format, x);
  json_object_set_string_member (object, prop, (const gchar *) buffer);
}

/**
 * Function to set a floating number with default format (see FPL macro) in a
 * property of a JSON object.
 */
void
jb_json_object_set_float (JsonObject *object,   ///< JSON object struct.
                          const char *prop,     ///< JSON object property.
                          JBDOUBLE x)
///< floating number value in JBDOUBLE format.
{
  jb_json_object_set_float_with_format (object, prop, FPL, x);
}

/**
 * Function to set a floating number with default format (see FPL macro) in a
 * property of a JSON object or none if the number is equal to a default value.
 */
void
jb_json_object_set_float_with_default (JsonObject *object,
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
jb_json_object_get_int (JsonObject *object,
                        ///< JSON object struct.
                        const char *prop,
                        ///< JSON object property having the number.
                        int *error)
                        ///< error code (1 on success, 0 on error).
{
  JsonNode *node;
  const char *buffer;
  long int x = 0;
  *error = 0;
  node = json_object_get_member (object, prop);
  if (json_node_get_node_type (node) == JSON_NODE_VALUE
      && json_node_get_value_type (node) == G_TYPE_STRING)
    {
      buffer = (const char *) json_node_get_string (node);
      if (buffer)
        *error = sscanf (buffer, "%ld", &x);
    }
  return x;
}

/**
 * Function to get an integer number, in long int format, from a property of a
 * JSON object or a default value if the object has not the property.
 *
 * \return integer number value in long int format.
 */
long int
jb_json_object_get_int_with_default (JsonObject *object,
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
jb_json_object_set_int (JsonObject *object,     ///< JSON object struct.
                        const char *prop,       ///< JSON object property.
                        long int x)
                        ///< integer number value in long int format.
{
  char buffer[JB_BUFFER_SIZE];
  snprintf (buffer, JB_BUFFER_SIZE, "%ld", x);
  json_object_set_string_member (object, prop, (const gchar *) buffer);
}

/**
 * Function to set an integer number in a property of a JSON object or none if
 * the number is equal to a default value.
 */
void
jb_json_object_set_int_with_default (JsonObject *object,
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
jb_json_object_get_uint (JsonObject *object,
                         ///< JSON object struct.
                         const char *prop,
                         ///< JSON object property having the number.
                         int *error)
                         ///< error code (1 on success, 0 on error).
{
  JsonNode *node;
  const char *buffer;
  unsigned long int x = 0;
  *error = 0;
  node = json_object_get_member (object, prop);
  if (json_node_get_node_type (node) == JSON_NODE_VALUE
      && json_node_get_value_type (node) == G_TYPE_STRING)
    {
      buffer = (const char *) json_node_get_string (node);
      if (buffer)
        *error = sscanf (buffer, "%lu", &x);
    }
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
jb_json_object_get_uint_with_default (JsonObject *object,
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
jb_json_object_set_uint (JsonObject *object,    ///< JSON object struct.
                         const char *prop,      ///< JSON object property.
                         unsigned long int x)
///< unsigned integer number value in unsigned long int format.
{
  char buffer[JB_BUFFER_SIZE];
  snprintf (buffer, JB_BUFFER_SIZE, "%lu", x);
  json_object_set_string_member (object, prop, (const gchar *) buffer);
}

/**
 * Function to set an unsgned integer number in a property of a JSON object or
 * none if the number is equal to a default value.
 */
void
jb_json_object_set_uint_with_default (JsonObject *object,
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
jb_json_object_get_time (JsonObject *object,    ///< JSON object struct.
                         const char *prop,      ///< JSON object property.
                         int *error)
                         ///< error code (1 on success, 0 on error).
{
  JsonNode *node;
  const char *buffer;
  JBDOUBLE t = 0.;
  *error = 0;
  node = json_object_get_member (object, prop);
  if (json_node_get_node_type (node) == JSON_NODE_VALUE
      && json_node_get_value_type (node) == G_TYPE_STRING)
    {
      buffer = (const char *) json_node_get_string (node);
      if (buffer)
        {
          t = jbm_get_time (buffer, error);
          if (*error != 1)
            *error = 0;
        }
    }
  return t;
}

/**
 * Function to get a time, in format "year month day hour minute seconds", from
 * a property of a JSON object or a default value if the object has not the property.
 *
 * \return date in floating point format.
 */
JBDOUBLE
jb_json_object_get_time_with_default (JsonObject *object,
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
jb_json_object_set_time (JsonObject *object,    ///< JSON object struct.
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
jb_json_object_set_time_with_default (JsonObject *object,
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

/**
 * Function to get an array of floating numbers, in JBDOUBLE format, from a
 * property of a JSON object.
 *
 * \return array of floating numbers value in JBDOUBLE format on success, NULL
 * on error.
 */
JBDOUBLE *
jb_json_object_get_floats (JsonObject *object,  ///< JSON object struct.
                           const char *prop,    ///< JSON object property.
                           unsigned int *n_elements)
///< number of array elements on success, 0 on error.
{
  JsonNode *node;
  JsonArray *array;
  GList *list, *list_initial;
  const char *buffer;
  JBDOUBLE *x = NULL;
  unsigned int n;
  *n_elements = 0;
  node = json_object_get_member (object, prop);
  if (json_node_get_node_type (node) != JSON_NODE_ARRAY)
    return x;
  array = json_node_get_array (node);
  list_initial = json_array_get_elements (array);
  for (n = 0, list = list_initial; list; ++n, list = list->next)
    {
      node = (JsonNode *) list->data;
      if (json_node_get_node_type (node) != JSON_NODE_VALUE
          || json_node_get_value_type (node) != G_TYPE_STRING)
        goto exit_on_error;
      buffer = (const char *) json_node_get_string (node);
      if (!buffer)
        goto exit_on_error;
      x = (JBDOUBLE *) realloc (x, (n + 1) * sizeof (JBDOUBLE));
      if (!x)
        goto exit_on_error;
      if (sscanf (buffer, FRL, x + n) != 1)
        goto exit_on_error;
    }
  g_list_free (list_initial);
  *n_elements = n;
  return x;

exit_on_error:
  g_list_free (list_initial);
  free (x);
  return NULL;
}

/**
 * Function to get an array of integer numbers from a property of a JSON object.
 *
 * \return array of integer numbers value on success, NULL on error.
 */
long int *
jb_json_object_get_ints (JsonObject *object,    ///< JSON object struct.
                         const char *prop,      ///< JSON object property.
                         unsigned int *n_elements)
///< number of array elements on success, 0 on error.
{
  JsonNode *node;
  JsonArray *array;
  GList *list, *list_initial;
  const char *buffer;
  long int *x = NULL;
  unsigned int n;
  *n_elements = 0;
  node = json_object_get_member (object, prop);
  if (json_node_get_node_type (node) != JSON_NODE_ARRAY)
    return x;
  array = json_node_get_array (node);
  list_initial = json_array_get_elements (array);
  for (n = 0, list = list_initial; list; ++n, list = list->next)
    {
      node = (JsonNode *) list->data;
      if (json_node_get_node_type (node) != JSON_NODE_VALUE
          || json_node_get_value_type (node) != G_TYPE_STRING)
        goto exit_on_error;
      buffer = (const char *) json_node_get_string (node);
      if (!buffer)
        goto exit_on_error;
      x = (long int *) realloc (x, (n + 1) * sizeof (long int));
      if (!x)
        goto exit_on_error;
      if (sscanf (buffer, "%ld", x + n) != 1)
        goto exit_on_error;
    }
  g_list_free (list_initial);
  *n_elements = n;
  return x;

exit_on_error:
  g_list_free (list_initial);
  free (x);
  return NULL;
}

/**
 * Function to get an array of unsigned integer numbers from a property of a
 * JSON object.
 *
 * \return array of unsigned integer numbers value on success, NULL on error.
 */
unsigned long int *
jb_json_object_get_uints (JsonObject *object,   ///< JSON object struct.
                          const char *prop,     ///< JSON object property.
                          unsigned int *n_elements)
///< number of array elements on success, 0 on error.
{
  JsonNode *node;
  JsonArray *array;
  GList *list, *list_initial;
  const char *buffer;
  unsigned long int *x = NULL;
  unsigned int n;
  *n_elements = 0;
  node = json_object_get_member (object, prop);
  if (json_node_get_node_type (node) != JSON_NODE_ARRAY)
    return x;
  array = json_node_get_array (node);
  list_initial = json_array_get_elements (array);
  for (n = 0, list = list_initial; list; ++n, list = list->next)
    {
      node = (JsonNode *) list->data;
      if (json_node_get_node_type (node) != JSON_NODE_VALUE
          || json_node_get_value_type (node) != G_TYPE_STRING)
        goto exit_on_error;
      buffer = (const char *) json_node_get_string (node);
      if (!buffer)
        goto exit_on_error;
      x = (unsigned long int *)
        realloc (x, (n + 1) * sizeof (unsigned long int));
      if (!x)
        goto exit_on_error;
      if (sscanf (buffer, "%lu", x + n) != 1)
        goto exit_on_error;
    }
  g_list_free (list_initial);
  *n_elements = n;
  return x;

exit_on_error:
  g_list_free (list_initial);
  free (x);
  return NULL;
}
