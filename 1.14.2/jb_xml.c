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
 * \file jb_xml.c
 * \brief Source file with useful XML functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2014, Javier Burguete Tolosa.
 */
#define _GNU_SOURCE
#include <string.h>
#include "jb_xml.h"

#if JB_XML_NODE_GET_FLOAT
/**
 * \fn JBDOUBLE jb_xml_node_get_float(xmlNode *node, const xmlChar *prop, \
 *   int *error)
 * \brief Function to get a floating number, in JBDOUBLE format, from a property
 *   of a XML node.
 * \param node
 * \brief XML node struct.
 * \param prop
 * \brief XML node property.
 * \param error
 * \brief error code (1 on success, 0 on error).
 * \return floating number value in JBDOUBLE format.
 */
JBDOUBLE jb_xml_node_get_float(xmlNode *node, const xmlChar *prop, int *error)
{
    char *buffer;
    JBDOUBLE x = 0.;
    *error = 0;
    buffer = (char*)xmlGetProp(node, prop);
    if (buffer)
        {
            *error = sscanf(buffer, FRL, &x);
            xmlFree(buffer);
        }
    return x;
}
#endif

#if JB_XML_NODE_GET_FLOAT_WITH_DEFAULT
/**
 * \fn JBDOUBLE jb_xml_node_get_float_with_default(xmlNode *node, \
 *   const xmlChar *prop, int *error, JBDOUBLE def)
 * \brief Function to get a floating number, in JBDOUBLE format, from a property
 *   of a XML node or a default value if the node has not the property.
 * \param node
 * \brief XML node struct.
 * \param prop
 * \brief XML node property.
 * \param error
 * \brief error code (1 on success, 0 on error).
 * \param def
 * \brief default value.
 * \return floating number value in JBDOUBLE format.
 */
JBDOUBLE jb_xml_node_get_float_with_default
(xmlNode *node, const xmlChar *prop, int *error, JBDOUBLE def)
{
    if (!xmlHasProp(node, prop))
        {
            *error = 1;
            return def;
        }
    return jb_xml_node_get_float(node, prop, error);
}
#endif

#if JB_XML_NODE_SET_FLOAT

/**
 * \fn void jb_xml_node_set_float_with_format(xmlNode *node, \
 *   const xmlChar *prop, char *format, JBDOUBLE x)
 * \brief Function to set a floating number with format in a property of a XML
 *   node.
 * \param node
 * \brief XML node struct.
 * \param prop
 * \brief XML node property.
 * \param format
 * \brief C-format string.
 * \param x
 * \brief floating number value in JBDOUBLE format.
 */
void jb_xml_node_set_float_with_format
(xmlNode *node, const xmlChar *prop, char *format, JBDOUBLE x)
{
    char buffer[JB_BUFFER_SIZE];
    snprintf(buffer, JB_BUFFER_SIZE, format, x);
    xmlSetProp(node, prop, (xmlChar*)buffer);
}

/**
 * \fn void jb_xml_node_set_float(xmlNode *node, const xmlChar *prop, \
 *   JBDOUBLE x)
 * \brief Function to set a floating number with default format (see FWL macro)
 *   in a property of a XML node.
 * \param node
 * \brief XML node struct.
 * \param prop
 * \brief XML node property.
 * \param x
 * \brief floating number value in JBDOUBLE format.
 */
void jb_xml_node_set_float(xmlNode *node, const xmlChar *prop, JBDOUBLE x)
{
    jb_xml_node_set_float_with_format(node, prop, FWL, x);
}

#endif

#if JB_XML_NODE_SET_FLOAT_WITH_DEFAULT
/**
 * \fn void jb_xml_node_set_float_with_default(xmlNode *node, \
 *   const xmlChar *prop, JBDOUBLE x, JBDOUBLE def)
 * \brief Function to set a floating number with default format (see FWL macro)
 *   in a property of a XML node or none if the number is equal to a default
 *   value.
 * \param node
 * \brief XML node struct.
 * \param prop
 * \brief XML node property.
 * \param x
 * \brief floating number value in JBDOUBLE format.
 * \param def
 * \brief default value.
 */
void jb_xml_node_set_float_with_default
(xmlNode *node, const xmlChar *prop, JBDOUBLE x, JBDOUBLE def)
{
    if (x != def) jb_xml_node_set_float(node, prop, x);
}
#endif

#if JB_XML_NODE_GET_INT
/**
 * \fn long jb_xml_node_get_int(xmlNode *node, const xmlChar *prop, int *error)
 * \brief Function to get an integer number, in long int format, from a property
 *   of a XML node.
 * \param node
 * \brief XML node struct.
 * \param prop
 * \brief XML node property having the number.
 * \param error
 * \brief error code (1 on success, 0 on error).
 * \return integer number value in long int format.
 */
long jb_xml_node_get_int(xmlNode *node, const xmlChar *prop, int *error)
{
    char *buffer;
    long x = 0;
    *error = 0;
    buffer = (char*)xmlGetProp(node, prop);
    if (buffer)
        {
            *error = sscanf(buffer, "%ld", &x);
            xmlFree(buffer);
        }
    return x;
}
#endif

#if JB_XML_NODE_GET_INT_WITH_DEFAULT
/**
 * \fn long jb_xml_node_get_int_with_default(xmlNode *node, \
 *   const xmlChar *prop, int *error, long def)
 * \brief Function to get an integer number, in long int format, from a property
 *   of a XML node or a default value if the node has not the property.
 * \param node
 * \brief XML node struct.
 * \param prop
 * \brief XML node property having the number.
 * \param error
 * \brief error code (1 on success, 0 on error).
 * \param def
 * \brief default value.
 * \return integer number value in long int format.
 */
long jb_xml_node_get_int_with_default
(xmlNode *node, const xmlChar *prop, int *error, long def)
{
    if (!xmlHasProp(node, prop))
        {
            *error = 1;
            return def;
        }
    return jb_xml_node_get_int(node, prop, error);
}
#endif

#if JB_XML_NODE_SET_INT
/**
 * \fn void jb_xml_node_set_int(xmlNode *node, const xmlChar *prop, long x)
 * \brief Function to set an integer number in a property of a XML node.
 * \param node
 * \brief XML node struct.
 * \param prop
 * \brief XML node property.
 * \param x
 * \brief integer number value in long int format.
 */
void jb_xml_node_set_int(xmlNode *node, const xmlChar *prop, long x)
{
    char buffer[JB_BUFFER_SIZE];
    snprintf(buffer,JB_BUFFER_SIZE, "%ld", x);
    xmlSetProp(node, prop, (xmlChar*)buffer);
}
#endif

#if JB_XML_NODE_SET_INT_WITH_DEFAULT
/**
 * \fn void jb_xml_node_set_int_with_default(xmlNode *node, \
 *   const xmlChar *prop, long x, long def)
 * \brief Function to set an integer number in a property of a XML node or none
 *   if the number is equal to a default value.
 * \param node
 * \brief XML node struct.
 * \param prop
 * \brief XML node property.
 * \param x
 * \brief integer number value in long int format.
 * \param def
 * \brief default value.
 */
void jb_xml_node_set_int_with_default
(xmlNode *node, const xmlChar *prop, long x, long def)
{
    if (x != def) jb_xml_node_set_int(node, prop, x);
}
#endif

#if JB_XML_NODE_GET_TIME
/**
 * \fn JBDOUBLE jb_xml_node_get_time(xmlNode *node, const xmlChar *prop, \
 *   int *error)
 * \brief Function to get a time, in format "year month day hour minute
 *   seconds", from a property of a XML node.
 * \param node
 * \brief XML node struct.
 * \param prop
 * \brief XML node property.
 * \param error
 * \brief error code (1 on success, 0 on error).
 * \return date in floating point format.
 */
JBDOUBLE jb_xml_node_get_time(xmlNode *node, const xmlChar *prop, int *error)
{
    char *buffer;
    JBDOUBLE t;
    *error = 0;
    buffer = (char*)xmlGetProp(node, prop);
    if (!buffer) return 0.;
    t = jb_get_time(buffer, error);
    if (*error != 6) *error = 0;
    xmlFree(buffer);
    return t;
}
#endif

#if JB_XML_NODE_GET_TIME_WITH_DEFAULT
/**
 * \fn JBDOUBLE jb_xml_node_get_time_with_default(xmlNode *node, \
 *   const xmlChar *prop, int *error, JBDOUBLE def)
 * \brief Function to get a time, in format "year month day hour minute
 *   seconds", from a property of a XML node or a default value if the node has
 *   not the property.
 * \param node
 * \brief XML node struct.
 * \param prop
 * \brief XML node property.
 * \param error
 * \brief error code (1 on success, 0 on error).
 * \param def
 * \brief default value.
 * \return date in floating point format.
 */
JBDOUBLE jb_xml_node_get_time_with_default
(xmlNode *node, const xmlChar *prop, int *error, JBDOUBLE def)
{
    if (!xmlHasProp(node, prop))
        {
            *error = 1;
            return def;
        }
    return jb_xml_node_get_time(node, prop, error);
}
#endif

#if JB_XML_NODE_SET_TIME
/**
 * \fn void jb_xml_node_set_time(xmlNode *node, const xmlChar *prop, JBDOUBLE t)
 * \brief Function to set a time, in format "year month day hour minute
 *   seconds", on a property of a XML node.
 * \param node
 * \brief XML node struct.
 * \param prop
 * \brief XML node property.
 * \param t
 * \brief date in floating point format.
 */
void jb_xml_node_set_time(xmlNode *node, const xmlChar *prop, JBDOUBLE t)
{
    const xmlChar *buffer;
    buffer = (const xmlChar*)jb_set_time(t);
    xmlSetProp(node, prop, buffer);
}
#endif

#if JB_XML_NODE_SET_TIME_WITH_DEFAULT
/**
 * \fn void jb_xml_node_set_time_with_default(xmlNode *node, \
 *   const xmlChar *prop, JBDOUBLE t, JBDOUBLE def)
 * \brief Function to set a time, in format "year month day hour minute
 *   seconds", on a property of a XML node or a default value if the node has
 *   not the property.
 * \param node
 * \brief XML node struct.
 * \param prop
 * \brief XML node property.
 * \param t
 * \brief date in floating point format.
 * \param def
 * \brief default value.
 */
void jb_xml_node_set_time_with_default
(xmlNode *node, const xmlChar *prop, JBDOUBLE t, JBDOUBLE def)
{
    if (t != def) jb_xml_node_set_time(node, prop, t);
}
#endif

#if JB_XML_NODE_GET_CONTENT_FILE
/**
 * \fn FILE* jb_xml_node_get_content_file(xmlNode *node, char **buffer)
 * \brief Function to get in a file and in a buffer the content of a XML node.
 * \param node
 * \brief XML node struct.
 * \param buffer
 * \brief pointer to the buffer with the content, it has to be freed with
 *   xmlFree.
 * \return file struct with the content.
 */
FILE* jb_xml_node_get_content_file(xmlNode *node, char **buffer)
{
    int l;
    FILE *file;
    *buffer = (char*)xmlNodeGetContent(node);
    if (!*buffer) return 0;
    l = strlen(*buffer);
#if defined(G_OS_WIN32) || defined(BSD) || defined(__sun)
    int k;
    file = g_fopen("node.tmp", "w");
    if (!file) goto exit1;
    k = fwrite(*buffer, sizeof(char), l, file);
    fclose(file);
    if (k != l) goto exit1;
    file = g_fopen("node.tmp", "r");
exit1:
#else
    file = (FILE*)fmemopen(*buffer, l, "r");
#endif
    if (!file) xmlFree(*buffer);
    return file;
}
#endif

#if JB_XML_NODE_SET_CONTENT_FILE
/**
 * \fn void jb_xml_node_set_content_file(xmlNode *node, FILE *file)
 * \brief Function to set in the content of a XML node a file.
 * \param node
 * \brief XML node struct.
 * \param file
 * \brief file struct with the content.
 */
void jb_xml_node_set_content_file(xmlNode *node, FILE *file)
{
    long int l;
    char *buffer;
    l = ftell(file);
    buffer = (char*)g_malloc(l + 1);
    fseek(file, 0, SEEK_SET);
    l = fread(buffer, 1, l, file);
    buffer[l] = 0;
    xmlNodeSetContent(node, (const xmlChar*)buffer);
    g_free(buffer);
}
#endif
