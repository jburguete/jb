/* JB - A library with useful mathematical, XML, GTK+ and OpenGL functions.
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
 * \file jb_xml.c
 * \brief Source file with useful XML functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2023, Javier Burguete Tolosa.
 */
#include "jb_xml.h"

/**
 * Function to get a floating number, in JBDOUBLE format, from a property of a
 * XML node.
 *
 * \return floating number value in JBDOUBLE format.
 */
JBDOUBLE
jb_xml_node_get_float (xmlNode * node,  ///< XML node struct.
                       const xmlChar * prop,    ///< XML node property.
                       int *error)      ///< error code (1 on success, 0 on error).
{
  char *buffer;
  JBDOUBLE x = 0.L;
  *error = 0;
  buffer = (char *) xmlGetProp (node, prop);
  if (buffer)
    {
      *error = sscanf (buffer, FRL, &x);
      xmlFree (buffer);
    }
  return x;
}

/**
 * Function to get a floating number, in JBDOUBLE format, from a property of a
 * XML node or a default value if the node has not the property.
 *
 * \return floating number value in JBDOUBLE format.
 */
JBDOUBLE
jb_xml_node_get_float_with_default (xmlNode * node,     ///< XML node struct.
                                    const xmlChar * prop,
///< XML node property.
                                    int *error,
///< error code (1 on success, 0 on error).
                                    JBDOUBLE def)       ///< default value.
{
  if (!xmlHasProp (node, prop))
    {
      *error = 1;
      return def;
    }
  return jb_xml_node_get_float (node, prop, error);
}

/**
 * Function to set a floating number with format in a property of a XML node.
 */
void
jb_xml_node_set_float_with_format (xmlNode * node,      ///< XML node struct.
                                   const xmlChar * prop,
                                   ///< XML node property.
                                   char *format,        ///< C-format string.
                                   JBDOUBLE x)
///< floating number value in JBDOUBLE format.
{
  char buffer[JB_BUFFER_SIZE];
  snprintf (buffer, JB_BUFFER_SIZE, format, x);
  xmlSetProp (node, prop, (xmlChar *) buffer);
}

/**
 * Function to set a floating number with default format (see FWL macro) in a
 * property of a XML node.
 */
void
jb_xml_node_set_float (xmlNode * node,  ///< XML node struct.
                       const xmlChar * prop,    ///< XML node property.
                       JBDOUBLE x)
///< floating number value in JBDOUBLE format.
{
  jb_xml_node_set_float_with_format (node, prop, FWL, x);
}

/**
 * Function to set a floating number with default format (see FWL macro) in a
 * property of a XML node or none if the number is equal to a default value.
 */
void
jb_xml_node_set_float_with_default (xmlNode * node,     ///< XML node struct.
                                    const xmlChar * prop,
///< XML node property.
                                    JBDOUBLE x,
///< floating number value in JBDOUBLE format.
                                    JBDOUBLE def)       ///< default value.
{
  if (x != def)
    jb_xml_node_set_float (node, prop, x);
}

/**
 * Function to get an integer number, in long int format, from a property of a
 * XML node.
 *
 * \return integer number value in long int format.
 */
long int
jb_xml_node_get_int (xmlNode * node,    ///< XML node struct.
                     const xmlChar * prop,
                     ///< XML node property having the number.
                     int *error)
                     ///< error code (1 on success, 0 on error).
{
  char *buffer;
  long int x = 0;
  *error = 0;
  buffer = (char *) xmlGetProp (node, prop);
  if (buffer)
    {
      *error = sscanf (buffer, "%ld", &x);
      xmlFree (buffer);
    }
  return x;
}

/**
 * Function to get an integer number, in long int format, from a property of a
 * XML node or a default value if the node has not the property.
 *
 * \return integer number value in long int format.
 */
long int
jb_xml_node_get_int_with_default (xmlNode * node,       ///< XML node struct.
                                  const xmlChar * prop,
                                  ///< XML node property having the number.
                                  int *error,
                                  ///< error code (1 on success, 0 on error).
                                  long int def) ///< default value.
{
  if (!xmlHasProp (node, prop))
    {
      *error = 1;
      return def;
    }
  return jb_xml_node_get_int (node, prop, error);
}

/**
 * Function to set an integer number in a property of a XML node.
 */
void
jb_xml_node_set_int (xmlNode * node,    ///< XML node struct.
                     const xmlChar * prop,      ///< XML node property.
                     long int x)
                     ///< integer number value in long int format.
{
  char buffer[JB_BUFFER_SIZE];
  snprintf (buffer, JB_BUFFER_SIZE, "%ld", x);
  xmlSetProp (node, prop, (xmlChar *) buffer);
}

/**
 * Function to set an integer number in a property of a XML node or none if the
 * number is equal to a default value.
 */
void
jb_xml_node_set_int_with_default (xmlNode * node,       ///< XML node struct.
                                  const xmlChar * prop, ///< XML node property.
                                  long int x,
                                  ///< integer number value in long int format.
                                  long int def) ///< default value.
{
  if (x != def)
    jb_xml_node_set_int (node, prop, x);
}

/**
 * Function to get an unsigned integer number, in unsigned long int format, from
 * a property of a XML node.
 *
 * \return unsigned integer number value in unsigned long int format.
 */
unsigned long int
jb_xml_node_get_uint (xmlNode * node,   ///< XML node struct.
                      const xmlChar * prop,
                      ///< XML node property having the number.
                      int *error)
                      ///< error code (1 on success, 0 on error).
{
  char *buffer;
  unsigned long int x = 0;
  *error = 0;
  buffer = (char *) xmlGetProp (node, prop);
  if (buffer)
    {
      *error = sscanf (buffer, "%lu", &x);
      xmlFree (buffer);
    }
  return x;
}

/**
 * Function to get an unsigned integer number, in unsigned long int format, from
 * a property of a XML node or a default value if the node has not the property.
 *
 * \return unsigned integer number value in unsigned long int format.
 */
unsigned long int
jb_xml_node_get_uint_with_default (xmlNode * node,      ///< XML node struct.
                                   const xmlChar * prop,
                                   ///< XML node property having the number.
                                   int *error,
                                   ///< error code (1 on success, 0 on error).
                                   unsigned long int def)
                                   ///< default value.
{
  if (!xmlHasProp (node, prop))
    {
      *error = 1;
      return def;
    }
  return jb_xml_node_get_uint (node, prop, error);
}

/**
 * Function to set an unsigned integer number in a property of a XML node.
 */
void
jb_xml_node_set_uint (xmlNode * node,   ///< XML node struct.
                      const xmlChar * prop,     ///< XML node property.
                      unsigned long int x)
///< unsigned integer number value in unsigned long int format.
{
  char buffer[JB_BUFFER_SIZE];
  snprintf (buffer, JB_BUFFER_SIZE, "%lu", x);
  xmlSetProp (node, prop, (xmlChar *) buffer);
}

/**
 * Function to set an unsigned integer number in a property of a XML node or
 * none if the number is equal to a default value.
 */
void
jb_xml_node_set_uint_with_default (xmlNode * node,      ///< XML node struct.
                                   const xmlChar * prop,
                                   ///< XML node property.
                                   unsigned long int x,
///< unsigned integer number value in unsigned long int format.
                                   unsigned long int def)
                                   ///< default value.
{
  if (x != def)
    jb_xml_node_set_uint (node, prop, x);
}

/**
 * Function to get a time, in format "year month day hour minute seconds", from
 * a property of a XML node.
 *
 * \return date in floating point format.
 */
JBDOUBLE
jb_xml_node_get_time (xmlNode * node,   ///< XML node struct.
                      const xmlChar * prop,     ///< XML node property.
                      int *error)
                      ///< error code (1 on success, 0 on error).
{
  char *buffer;
  JBDOUBLE t;
  *error = 0;
  buffer = (char *) xmlGetProp (node, prop);
  if (!buffer)
    return 0.;
  t = jbm_get_time (buffer, error);
  if (*error != 1)
    *error = 0;
  xmlFree (buffer);
  return t;
}

/**
 * Function to get a time, in format "year month day hour minute seconds", from
 * a property of a XML node or a default value if the node has not the property.
 *
 * \return date in floating point format.
 */
JBDOUBLE
jb_xml_node_get_time_with_default (xmlNode * node,      ///< XML node struct.
                                   const xmlChar * prop,
                                   ///< XML node property.
                                   int *error,
                                   ///< error code (1 on success, 0 on error).
                                   JBDOUBLE def)        ///< default value.
{
  if (!xmlHasProp (node, prop))
    {
      *error = 1;
      return def;
    }
  return jb_xml_node_get_time (node, prop, error);
}

/**
 * Function to set a time, in format "year month day hour minute seconds", on a
 * property of a XML node.
 */
void
jb_xml_node_set_time (xmlNode * node,   ///< XML node struct.
                      const xmlChar * prop,     ///< XML node property.
                      JBDOUBLE t)       ///< date in floating point format.
{
  const xmlChar *buffer;
  buffer = (const xmlChar *) jbm_set_time (t);
  xmlSetProp (node, prop, buffer);
}

/**
 * Function to set a time, in format "year month day hour minute seconds", on a
 * property of a XML node or a default value if the node has not the property.
 */
void
jb_xml_node_set_time_with_default (xmlNode * node,      ///< XML node struct.
                                   const xmlChar * prop,
                                   ///< XML node property.
                                   JBDOUBLE t,
                                   ///< date in floating point format.
                                   JBDOUBLE def)        ///< default value.
{
  if (t != def)
    jb_xml_node_set_time (node, prop, t);
}

/**
 * Function to get in a file and in a buffer the content of a XML node.
 *
 * \return file struct with the content.
 */
FILE *
jb_xml_node_get_content_file (xmlNode * node,   ///< XML node struct.
                              char **buffer)
///< pointer to the buffer with the content, it has to be freed with xmlFree.
{
  FILE *file;
  int l;
  *buffer = (char *) xmlNodeGetContent (node);
  if (!*buffer)
    return 0;
  l = strlen (*buffer);
#if HAVE_FMEMOPEN
  file = (FILE *) fmemopen (*buffer, l, "r");
#else
  int k;
  file = g_fopen ("node.tmp", "w");
  if (!file)
    goto exit1;
  k = fwrite (*buffer, sizeof (char), l, file);
  fclose (file);
  if (k != l)
    goto exit1;
  file = g_fopen ("node.tmp", "r");
exit1:
#endif
  if (!file)
    xmlFree (*buffer);
  return file;
}

/**
 * Function to set a file in the content of a XML node.
 */
void
jb_xml_node_set_content_file (xmlNode * node,   ///< XML node struct.
                              FILE * file)
                              ///< file struct with the content.
{
  long int l;
  char *buffer;
  fseek (file, 0, SEEK_END);
  l = ftell (file);
  buffer = (char *) g_malloc (l + 1);
  fseek (file, 0, SEEK_SET);
  l = fread (buffer, 1, l, file);
  buffer[l] = 0;
  xmlNodeSetContent (node, (const xmlChar *) buffer);
  g_free (buffer);
}
