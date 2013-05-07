#define _GNU_SOURCE
#include <string.h>
#include "jb_xml.h"

#if JB_XML_NODE_GET_FLOAT
JBDOUBLE jb_xml_node_get_float(xmlNode *node,const xmlChar *prop,int *error)
{
	char *buffer;
	JBDOUBLE x=0.;
	*error = 0;
	buffer=(char*)xmlGetProp(node,prop);
	if (buffer)
	{
		*error = sscanf(buffer, FRL, &x);
		xmlFree(buffer);
	}
	return x;
}
#endif

#if JB_XML_NODE_SET_FLOAT
void jb_xml_node_set_float_with_format
	(xmlNode *node,const xmlChar *prop,char *format,JBDOUBLE x)
{
	char buffer[JB_BUFFER_SIZE];
	snprintf(buffer,JB_BUFFER_SIZE,format,x);
	xmlSetProp(node,prop,(xmlChar*)buffer);
}

void jb_xml_node_set_float(xmlNode *node,const xmlChar *prop,JBDOUBLE x)
{
	jb_xml_node_set_float_with_format(node,prop,FWL,x);
}
#endif

#if JB_XML_NODE_GET_INT
long jb_xml_node_get_int(xmlNode *node,const xmlChar *prop,int *error)
{
	char *buffer;
	long x=0;
	*error = 0;
	buffer=(char*)xmlGetProp(node,prop);
	if (buffer)
	{
		*error = sscanf(buffer, "%ld", &x);
		xmlFree(buffer);
	}
	return x;
}
#endif

#if JB_XML_NODE_SET_INT
void jb_xml_node_set_int(xmlNode *node,const xmlChar *prop,long x)
{
	char buffer[JB_BUFFER_SIZE];
	snprintf(buffer,JB_BUFFER_SIZE,"%ld",x);
	xmlSetProp(node,prop,(xmlChar*)buffer);
}
#endif

#if JB_XML_NODE_GET_TIME
JBDOUBLE jb_xml_node_get_time(xmlNode *node,const xmlChar *prop,int *error)
{
	char *buffer;
	JBDOUBLE t;
	*error = 0;
	buffer=(char*)xmlGetProp(node,prop);
	if (!buffer) return 0.;
	t = jb_get_time(buffer, error);
	if (*error != 6) *error = 0;
	xmlFree(buffer);
	return t;
}
#endif

#if JB_XML_NODE_SET_TIME
void jb_xml_node_set_time(xmlNode *node,const xmlChar *prop,JBDOUBLE t)
{
	const xmlChar *buffer;
	buffer = (const xmlChar*)jb_set_time(t);
	xmlSetProp(node, prop, buffer);
}
#endif

#if JB_XML_NODE_GET_FLOAT_WITH_DEFAULT
JBDOUBLE jb_xml_node_get_float_with_default
	(xmlNode *node,const xmlChar *prop,int *error,JBDOUBLE def)
{
	if (!xmlHasProp(node,prop))
	{
		*error = 1;
		return def;
	}
	return jb_xml_node_get_float(node, prop, error);
}
#endif

#if JB_XML_NODE_SET_FLOAT_WITH_DEFAULT
void jb_xml_node_set_float_with_default
	(xmlNode *node,const xmlChar *prop,JBDOUBLE x,JBDOUBLE def)
{
	if (x!=def) jb_xml_node_set_float(node,prop,x);
}
#endif

#if JB_XML_NODE_GET_INT_WITH_DEFAULT
long jb_xml_node_get_int_with_default
	(xmlNode *node,const xmlChar *prop,int *error,long def)
{
	if (!xmlHasProp(node,prop))
	{
		*error = 1;
		return def;
	}
	return jb_xml_node_get_int(node, prop, error);
}
#endif

#if JB_XML_NODE_SET_INT_WITH_DEFAULT
void jb_xml_node_set_int_with_default
	(xmlNode *node,const xmlChar *prop,long x,long def)
{
	if (x!=def) jb_xml_node_set_int(node,prop,x);
}
#endif

#if JB_XML_NODE_GET_TIME_WITH_DEFAULT
JBDOUBLE jb_xml_node_get_time_with_default
	(xmlNode *node,const xmlChar *prop,int *error,JBDOUBLE def)
{
	if (!xmlHasProp(node,prop))
	{
		*error = 1;
		return def;
	}
	return jb_xml_node_get_time(node, prop, error);
}
#endif

#if JB_XML_NODE_SET_TIME_WITH_DEFAULT
void jb_xml_node_set_time_with_default
	(xmlNode *node,const xmlChar *prop,JBDOUBLE t,JBDOUBLE def)
{
	if (t!=def) jb_xml_node_set_time(node,prop,t);
}
#endif

#if JB_XML_NODE_GET_CONTENT_FILE
FILE* jb_xml_node_get_content_file(xmlNode *node,char **buffer)
{
	int l;
	FILE *file;
	*buffer=(char*)xmlNodeGetContent(node);
	if (!*buffer) return 0;
	l=strlen(*buffer);
	#if defined(G_OS_WIN32) || defined(BSD)
		int k;
		file=g_fopen("node.tmp","w");
		if (!file) goto exit1;
		k=fwrite(*buffer,sizeof(char),l,file);
		fclose(file);
		if (k!=l) goto exit1;
		file=g_fopen("node.tmp","r");
exit1:
	#else
		file=(FILE*)fmemopen(*buffer,l,"r");
	#endif
	if (!file) xmlFree(*buffer);
	return file;
}
#endif

#if JB_XML_NODE_SET_CONTENT_FILE
void jb_xml_node_set_content_file(xmlNode *node,FILE *file)
{
	long int l;
	char *buffer;
	l=ftell(file);
	buffer=(char*)g_malloc(l+1);
	fseek(file,0,SEEK_SET);
	l=fread(buffer,1,l,file);
	buffer[l]=0;
	xmlNodeSetContent(node,buffer);
	g_free(buffer);
}
#endif
