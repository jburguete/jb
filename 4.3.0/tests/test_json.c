#include "jb_json.h"

#define TEST_FILE "../test_data.json"
#define JSON_FILE (const char *) TEST_FILE
#define JSON_TEST (const char *) "test"
#define JSON_X (const char *) "x"
#define JSON_I (const char *) "i"
#define JSON_T (const char *) "t"

int
main (void)
{
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
  jb_json_object_set_float_with_default (object, JSON_X, 1., 0.);
  jb_json_object_set_int_with_default (object, JSON_I, 1, 0);
  jb_json_object_set_time_with_default (object, JSON_T, 1., 0.);
  json_generator_to_file (generator, TEST_FILE, NULL);
  g_object_unref (generator);
  parser = json_parser_new ();
  json_parser_load_from_file (parser, TEST_FILE, NULL);
  node = json_parser_get_root (parser);
  object = json_node_get_object (node);
  x = jb_json_object_get_float_with_default (object, JSON_X, &e1, 0.);
  printf ("x " FWL " 1\n", x);
  i = jb_json_object_get_int_with_default (object, JSON_I, &e2, 0);
  printf ("i %d 1\n", i);
  x = jb_json_object_get_time_with_default (object, JSON_T, &e3, 0.);
  printf ("t " FWL " 1\n", x);
  if (!e1 || !e2 || !e3)
    {
      printf ("Bad json property e1=%d e2=%d e3=%d\n", e1, e2, e3);
      return 2;
    }
  g_object_unref (parser);
  return 0;
}
