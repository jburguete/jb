#include "jb_xml.h"

#define TEST_FILE "test_data.xml"
#define XML_FILE (const xmlChar *) TEST_FILE
#define XML_TEST (const xmlChar *) "test"
#define XML_VERSION (const xmlChar *) "1.0"
#define XML_X (const xmlChar *) "x"
#define XML_I (const xmlChar *) "i"
#define XML_T (const xmlChar *) "t"

int
main ()
{
  xmlDoc *doc;
  xmlNode *node;
  FILE *file;
//      char *buffer;
  JBDOUBLE x;
  int i, e1, e2, e3;
  xmlKeepBlanksDefault (0);
  doc = xmlNewDoc (XML_VERSION);
  node = xmlNewDocNode (doc, 0, XML_TEST, 0);
  xmlDocSetRootElement (doc, node);
  jb_xml_node_set_float_with_default (node, XML_X, 1., 0.);
  jb_xml_node_set_int_with_default (node, XML_I, 1, 0);
  jb_xml_node_set_time_with_default (node, XML_T, 1., 0.);
  file = fopen ("test_data", "r");
  if (!file || fscanf (file, "%d", &i) != 1 || i)
    {
      printf ("Bad test_data file\n");
      return 1;
    }
//      jb_xml_node_set_content_file (node, file);
  fclose (file);
  xmlSaveFormatFile (TEST_FILE, doc, 1);
  xmlFreeDoc (doc);
  doc = xmlParseDoc (XML_FILE);
  node = xmlDocGetRootElement (doc);
  x = jb_xml_node_get_float_with_default (node, XML_X, &e1, 0.);
  printf ("x " FWL " 1\n", x);
  i = jb_xml_node_get_int_with_default (node, XML_I, &e2, 0);
  printf ("i %d 1\n", i);
  x = jb_xml_node_get_time_with_default (node, XML_T, &e3, 0.);
  if (!e1 || !e2 || !e3)
    {
      printf ("Bad xml property\n");
      return 2;
    }
  printf ("t " FWL " 1\n", x);
/*
	file = jb_xml_node_get_content_file (node, &buffer);
	if (!file || fscanf (file, "%d", &i) != 1 || i || !buffer)
	  {
			printf ("Bad xml content\n");
			return 3;
    }
	printf ("content %d %s\n", i, buffer);
	fclose (file);
*/
  xmlFree (doc);
  return 0;
}
