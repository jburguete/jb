#include "jb_xml.h"

#define XML_FILE (const char *) "test.xml"
#define XML_TEST (const xmlChar *) "test"
#define XML_VERSION (const xmlChar *) "1.0"
#define XML_X (const xmlChar *) "x"
#define XML_I (const xmlChar *) "i"
#define XML_T (const xmlChar *) "t"

int
main (void)
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f, c1 = 1.f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0., c1 = 1.;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L, c1 = 1.L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q, c1 = 1.Q;
#endif
  char str[JB_BUFFER_SIZE];
  xmlDoc *doc;
  xmlNode *node;
  FILE *file;
  char *buffer;
  JBDOUBLE x;
  int i, e1, e2, e3;
  xmlKeepBlanksDefault (0);
  doc = xmlNewDoc (XML_VERSION);
  node = xmlNewDocNode (doc, 0, XML_TEST, 0);
  xmlDocSetRootElement (doc, node);
  jb_xml_node_set_float_with_default (node, XML_X, c1, c0);
  jb_xml_node_set_int_with_default (node, XML_I, 1, 0);
  jb_xml_node_set_time_with_default (node, XML_T, c1, c0);
  file = fopen (TEST_FILE, "r");
  if (!file || fscanf (file, "%d", &i) != 1 || i)
    {
      printf ("Bad test_data file\n");
      return 1;
    }
  jb_xml_node_set_content_file (node, file);
  xmlSaveFormatFile (XML_FILE, doc, 1);
  fclose (file);
  xmlFreeDoc (doc);
  doc = xmlParseFile (XML_FILE);
  node = xmlDocGetRootElement (doc);
  x = jb_xml_node_get_float_with_default (node, XML_X, &e1, c0);
  SNPRINTFL (str, JB_BUFFER_SIZE, FWL, x);
  printf ("x %s 1\n", str);
  i = jb_xml_node_get_int_with_default (node, XML_I, &e2, 0);
  printf ("i %d 1\n", i);
  x = jb_xml_node_get_time_with_default (node, XML_T, &e3, c0);
  SNPRINTFL (str, JB_BUFFER_SIZE, FWL, x);
  printf ("t %s 1\n", str);
  if (!e1 || !e2 || !e3)
    {
      printf ("Bad xml property e1=%d e2=%d e3=%d\n", e1, e2, e3);
      return 2;
    }
  file = jb_xml_node_get_content_file (node, &buffer);
  if (!file || (e1 = fscanf (file, "%d", &i)) != 1 || i || !buffer)
    {
      printf ("Bad xml content file=%lu e1=%d i=%d buffer=%s\n",
              (size_t) file, e1, i, buffer);
      return 3;
    }
  printf ("content %d %s\n", i, buffer);
  fclose (file);
  xmlFree (doc);
  return 0;
}
