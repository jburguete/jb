#include "../src/json.h"

#define JSON_FILE (const char *) "test.json"
#define JSON_TEST (const char *) "test"
#define JSON_X (const char *) "x"
#define JSON_I (const char *) "i"
#define JSON_T (const char *) "t"

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
  JsonGenerator *generator;
  JsonParser *parser;
  JsonNode *node;
  JsonObject *object;
  JBDOUBLE x;
  int i, e1, e2, e3;
  generator = json_generator_new ();
  json_generator_set_pretty (generator, TRUE);
  object = json_object_new ();
  node = json_node_new (JSON_NODE_OBJECT);
  json_node_set_object (node, object);
  json_generator_set_root (generator, node);
  jb_json_object_set_float_with_default (object, JSON_X, c1, c0);
  jb_json_object_set_int_with_default (object, JSON_I, 1, 0);
  jb_json_object_set_time_with_default (object, JSON_T, c1, c0);
  json_generator_to_file (generator, JSON_FILE, NULL);
  g_object_unref (generator);
  parser = json_parser_new ();
  json_parser_load_from_file (parser, JSON_FILE, NULL);
  node = json_parser_get_root (parser);
  object = json_node_get_object (node);
  x = jb_json_object_get_float_with_default (object, JSON_X, &e1, c0);
  SNPRINTFL (str, JB_BUFFER_SIZE, FWL, x);
  printf ("x %s 1\n", str);
  i = jb_json_object_get_int_with_default (object, JSON_I, &e2, 0);
  printf ("i %d 1\n", i);
  x = jb_json_object_get_time_with_default (object, JSON_T, &e3, c0);
  SNPRINTFL (str, JB_BUFFER_SIZE, FWL, x);
  printf ("t %s 1\n", str);
  if (!e1 || !e2 || !e3)
    {
      printf ("Bad json property e1=%d e2=%d e3=%d\n", e1, e2, e3);
      return 2;
    }
  g_object_unref (parser);
  return 0;
}
