#include "../jb_math.h"

#include <time.h>
#include <gsl/gsl_rng.h>

int
check_array (JBFLOAT * x,       ///<
             unsigned int *ni,  ///<
             int n)             ///<
{
  int i;
  for (i = 0; i < n; ++i)
    if (x[ni[i]] < x[ni[i + 1]])
      return 0;
  return 1;
}

int
check_arrayl (JBDOUBLE * x,     ///<
              unsigned int *ni, ///<
              int n)            ///<
{
  int i;
  for (i = 0; i < n; ++i)
    if (x[ni[i]] < x[ni[i + 1]])
      return 0;
  return 1;
}

int
check_interchange (JBFLOAT * x, ///<
                   unsigned int *ni,    ///<
                   int n)       ///<
{
  int i;
  for (i = 0; i <= n; ++i)
    ni[i] = i;
  jbm_index_sort_interchange (x, ni, n);
  return check_array (x, ni, n);
}

int
check_interchangel (JBDOUBLE * x,       ///<
                    unsigned int *ni,   ///<
                    int n)      ///<
{
  int i;
  for (i = 0; i <= n; ++i)
    ni[i] = i;
  jbm_index_sort_interchangel (x, ni, n);
  return check_arrayl (x, ni, n);
}

int
check_insertion (JBFLOAT * x,   ///<
                 unsigned int *ni,      ///<
                 int n)         ///<
{
  int i;
  for (i = 0; i <= n; ++i)
    ni[i] = i;
  jbm_index_sort_insertion (x, ni, n);
  return check_array (x, ni, n);
}

int
check_insertionl (JBDOUBLE * x, ///<
                  unsigned int *ni,     ///<
                  int n)        ///<
{
  int i;
  for (i = 0; i <= n; ++i)
    ni[i] = i;
  jbm_index_sort_insertionl (x, ni, n);
  return check_arrayl (x, ni, n);
}

int
check_merge (JBFLOAT * x,       ///<
             unsigned int *ni,  ///<
             int n)             ///<
{
  int i;
  for (i = 0; i <= n; ++i)
    ni[i] = i;
  jbm_index_sort_merge (x, ni, n);
  return check_array (x, ni, n);
}

int
check_mergel (JBDOUBLE * x,     ///<
              unsigned int *ni, ///<
              int n)            ///<
{
  int i;
  for (i = 0; i <= n; ++i)
    ni[i] = i;
  jbm_index_sort_mergel (x, ni, n);
  return check_arrayl (x, ni, n);
}

int
check_flash (JBFLOAT * x,       ///<
             unsigned int *ni,  ///<
             int n)             ///<
{
  int i;
  for (i = 0; i <= n; ++i)
    ni[i] = i;
  jbm_index_sort_flash (x, ni, n);
  return check_array (x, ni, n);
}

int
check_flashl (JBDOUBLE * x,     ///<
              unsigned int *ni, ///<
              int n)            ///<
{
  int i;
  for (i = 0; i <= n; ++i)
    ni[i] = i;
  jbm_index_sort_flashl (x, ni, n);
  return check_arrayl (x, ni, n);
}

void
print_array (JBFLOAT * x,       ///<
             unsigned int *ni,  ///<
             int n,             ///<
             char *label)       ///<
{
  int i;
  printf ("%s\n", label);
  for (i = 0; i <= n; ++i)
    printf ("%d %u " FWF " " FWF "\n", i, ni[i], x[ni[i]], x[i]);
}

void
print_arrayl (JBDOUBLE * x,     ///<
              unsigned int *ni, ///<
              int n,            ///<
              char *label)      ///<
{
  int i;
  printf ("%s\n", label);
  for (i = 0; i <= n; ++i)
    printf ("%d %u " FWL "\n", i, ni[i], x[i]);
}

int
main (int argn,                 ///<
      char **argc)              ///<
{
  gsl_rng *rng;
  JBDOUBLE *y;
  JBFLOAT *x;
  unsigned int *ni;
  unsigned int i, j, k, n;
  if (argn != 3)
    {
      printf ("Bad arguments number\nSyntax is\n"
              "./check_sort number_of_tests method\n");
      return 1;
    }
  n = strtoul (argc[1], NULL, 0);
  if (!n)
    {
      printf ("Bad number of tests\n");
      return 2;
    }
  k = strtoul (argc[2], NULL, 0);
  ni = (unsigned int *) malloc ((n + 1) * sizeof (unsigned int));
  x = (JBFLOAT *) malloc ((n + 1) * sizeof (JBFLOAT));
  y = (JBDOUBLE *) malloc ((n + 1) * sizeof (JBDOUBLE));
  rng = gsl_rng_alloc (gsl_rng_taus2);
  for (i = 1; i <= n; ++i)
    {
      for (j = 0; j <= i; ++j)
        {
          x[j] = gsl_rng_uniform (rng);
          y[j] = gsl_rng_uniform (rng);
        }
      switch (k)
        {
        case 1:
          if (!check_interchange (x, ni, i))
            {
              print_array (x, ni, i, "jbm_index_sort_interchange");
              goto end;
            }
          if (!check_interchangel (y, ni, i))
            {
              print_arrayl (y, ni, i, "jbm_index_sort_interchangel");
              goto end;
            }
          break;
        case 2:
          if (!check_insertion (x, ni, i))
            {
              print_array (x, ni, i, "jbm_index_sort_insertion");
              goto end;
            }
          if (!check_insertionl (y, ni, i))
            {
              print_arrayl (y, ni, i, "jbm_index_sort_insertionl");
              goto end;
            }
          break;
        case 3:
          if (!check_merge (x, ni, i))
            {
              print_array (x, ni, i, "jbm_index_sort_merge");
              goto end;
            }
          if (!check_mergel (y, ni, i))
            {
              print_arrayl (y, ni, i, "jbm_index_sort_mergel");
              goto end;
            }
          break;
        case 4:
          if (!check_flash (x, ni, i))
            {
              print_array (x, ni, i, "jbm_index_sort_flash");
              goto end;
            }
          if (!check_flashl (y, ni, i))
            {
              print_arrayl (y, ni, i, "jbm_index_sort_flashl");
              goto end;
            }
          break;
        default:
          printf ("Unknown method\n");
          goto end;
        }
    }
end:
  gsl_rng_free (rng);
  free (y);
  free (x);
  free (ni);
  return 0;
}
