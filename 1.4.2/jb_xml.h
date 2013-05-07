#ifndef JB_XML__H
#define JB_XML__H 1

#include "jb_math.h"
#include <libxml/parser.h>

#if JB_XML_NODE_GET_FLOAT
	JBDOUBLE jb_xml_node_get_float(xmlNode*,const xmlChar*,int*);
#endif

#if JB_XML_NODE_SET_FLOAT
	void jb_xml_node_set_float_with_format
		(xmlNode*,const xmlChar*,char*,JBDOUBLE);
	void jb_xml_node_set_float(xmlNode*,const xmlChar*,JBDOUBLE);
#endif

#if JB_XML_NODE_GET_INT
	long jb_xml_node_get_int(xmlNode*,const xmlChar*,int*);
#endif

#if JB_XML_NODE_SET_INT
	void jb_xml_node_set_int(xmlNode*,const xmlChar*,long);
#endif

#if JB_XML_NODE_GET_TIME
	JBDOUBLE jb_xml_node_get_time(xmlNode*,const xmlChar*,int*);
#endif

#if JB_XML_NODE_SET_TIME
	void jb_xml_node_set_time(xmlNode*,const xmlChar*,JBDOUBLE);
#endif

#if JB_XML_NODE_GET_FLOAT_WITH_DEFAULT
	JBDOUBLE jb_xml_node_get_float_with_default
		(xmlNode*,const xmlChar*,int*,JBDOUBLE);
#endif

#if JB_XML_NODE_SET_FLOAT_WITH_DEFAULT
	void jb_xml_node_set_float_with_default
		(xmlNode*,const xmlChar*,JBDOUBLE,JBDOUBLE);
#endif

#if JB_XML_NODE_GET_INT_WITH_DEFAULT
	long jb_xml_node_get_int_with_default(xmlNode*,const xmlChar*,int*,long);
#endif

#if JB_XML_NODE_SET_INT_WITH_DEFAULT
	void jb_xml_node_set_int_with_default(xmlNode*,const xmlChar*,long,long);
#endif

#if JB_XML_NODE_GET_TIME_WITH_DEFAULT
	JBDOUBLE jb_xml_node_get_time_with_default
		(xmlNode*,const xmlChar*,int*,JBDOUBLE);
#endif

#if JB_XML_NODE_SET_TIME_WITH_DEFAULT
	void jb_xml_node_set_time_with_default
		(xmlNode*,const xmlChar*,JBDOUBLE,JBDOUBLE);
#endif

#if JB_XML_NODE_GET_CONTENT_FILE
	FILE* jb_xml_node_get_content_file(xmlNode*,char**);
#endif

#if JB_XML_NODE_SET_CONTENT_FILE
	void jb_xml_node_set_content_file(xmlNode*,FILE*);
#endif

#endif
