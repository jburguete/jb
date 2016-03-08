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
 * \file jb_xml.h
 * \brief Header file with useful XML functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2014, Javier Burguete Tolosa.
 */
#ifndef JB_XML__H
#define JB_XML__H 1

#include "jb_math.h"
#include <libxml/parser.h>

#if JB_XML_NODE_GET_FLOAT
JBDOUBLE jb_xml_node_get_float (xmlNode *, const xmlChar *, int *);
#endif

#if JB_XML_NODE_GET_FLOAT_WITH_DEFAULT
JBDOUBLE jb_xml_node_get_float_with_default
  (xmlNode *, const xmlChar *, int *, JBDOUBLE);
#endif

#if JB_XML_NODE_SET_FLOAT
void jb_xml_node_set_float_with_format
  (xmlNode *, const xmlChar *, char *, JBDOUBLE);
void jb_xml_node_set_float (xmlNode *, const xmlChar *, JBDOUBLE);
#endif

#if JB_XML_NODE_SET_FLOAT_WITH_DEFAULT
void jb_xml_node_set_float_with_default
  (xmlNode *, const xmlChar *, JBDOUBLE, JBDOUBLE);
#endif

#if JB_XML_NODE_GET_INT
long jb_xml_node_get_int (xmlNode *, const xmlChar *, int *);
#endif

#if JB_XML_NODE_GET_INT_WITH_DEFAULT
long jb_xml_node_get_int_with_default (xmlNode *, const xmlChar *, int *, long);
#endif

#if JB_XML_NODE_SET_INT
void jb_xml_node_set_int (xmlNode *, const xmlChar *, long);
#endif

#if JB_XML_NODE_SET_INT_WITH_DEFAULT
void jb_xml_node_set_int_with_default (xmlNode *, const xmlChar *, long, long);
#endif

#if JB_XML_NODE_GET_TIME
JBDOUBLE jb_xml_node_get_time (xmlNode *, const xmlChar *, int *);
#endif

#if JB_XML_NODE_GET_TIME_WITH_DEFAULT
JBDOUBLE jb_xml_node_get_time_with_default
  (xmlNode *, const xmlChar *, int *, JBDOUBLE);
#endif

#if JB_XML_NODE_SET_TIME
void jb_xml_node_set_time (xmlNode *, const xmlChar *, JBDOUBLE);
#endif

#if JB_XML_NODE_SET_TIME_WITH_DEFAULT
void jb_xml_node_set_time_with_default
  (xmlNode *, const xmlChar *, JBDOUBLE, JBDOUBLE);
#endif

#if JB_XML_NODE_GET_CONTENT_FILE
FILE *jb_xml_node_get_content_file (xmlNode *, char **);
#endif

#if JB_XML_NODE_SET_CONTENT_FILE
void jb_xml_node_set_content_file (xmlNode *, FILE *);
#endif

#endif
