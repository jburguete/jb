#include "jb_math.h"

#include <time.h>
#include <gsl/gsl_rng.h>

void
sort_interchange (JBFLOAT * x,  ///<
                  unsigned int *ni,     ///<
                  unsigned int n,       ///<
                  unsigned int k)       ///<
{
  unsigned int i, j;
  i = 0;
  do
    {
      if (n - i < k)
        k = n - i;
      for (j = 0; j < k; ++j)
        ni[j] = j;
      jbm_index_sort_interchange (x + i, ni, k - 1);
      i += k;
    }
  while (i < n);

}

void
sort_interchangel (JBDOUBLE * x,        ///<
                   unsigned int *ni,    ///<
                   unsigned int n,      ///<
                   unsigned int k)      ///<
{
  unsigned int i, j;
  i = 0;
  do
    {
      if (n - i < k)
        k = n - i;
      for (j = 0; j < k; ++j)
        ni[j] = j;
      jbm_index_sort_interchangel (x + i, ni, k - 1);
      i += k;
    }
  while (i < n);

}

void
sort_insertion (JBFLOAT * x,    ///<
                unsigned int *ni,       ///<
                unsigned int n, ///<
                unsigned int k) ///<
{
  unsigned int i, j;
  i = 0;
  do
    {
      if (n - i < k)
        k = n - i;
      for (j = 0; j < k; ++j)
        ni[j] = j;
      jbm_index_sort_insertion (x + i, ni, k - 1);
      i += k;
    }
  while (i < n);

}

void
sort_insertionl (JBDOUBLE * x,  ///<
                 unsigned int *ni,      ///<
                 unsigned int n,        ///<
                 unsigned int k)        ///<
{
  unsigned int i, j;
  i = 0;
  do
    {
      if (n - i < k)
        k = n - i;
      for (j = 0; j < k; ++j)
        ni[j] = j;
      jbm_index_sort_insertionl (x + i, ni, k - 1);
      i += k;
    }
  while (i < n);

}

void
sort_merge (JBFLOAT * x,        ///<
            unsigned int *ni,   ///<
            unsigned int n,     ///<
            unsigned int k)     ///<
{
  unsigned int i, j;
  i = 0;
  do
    {
      if (n - i < k)
        k = n - i;
      for (j = 0; j < k; ++j)
        ni[j] = j;
      jbm_index_sort_merge (x + i, ni, k - 1);
      i += k;
    }
  while (i < n);

}

void
sort_mergel (JBDOUBLE * x,      ///<
             unsigned int *ni,  ///<
             unsigned int n,    ///<
             unsigned int k)    ///<
{
  unsigned int i, j;
  i = 0;
  do
    {
      if (n - i < k)
        k = n - i;
      for (j = 0; j < k; ++j)
        ni[j] = j;
      jbm_index_sort_mergel (x + i, ni, k - 1);
      i += k;
    }
  while (i < n);

}

void
sort_flash (JBFLOAT * x,        ///<
            unsigned int *ni,   ///<
            unsigned int n,     ///<
            unsigned int k)     ///<
{
  unsigned int i, j;
  i = 0;
  do
    {
      if (n - i < k)
        k = n - i;
      for (j = 0; j < k; ++j)
        ni[j] = j;
      jbm_index_sort_flash (x + i, ni, k - 1);
      i += k;
    }
  while (i < n);

}

void
sort_flashl (JBDOUBLE * x,      ///<
             unsigned int *ni,  ///<
             unsigned int n,    ///<
             unsigned int k)    ///<
{
  unsigned int i, j;
  i = 0;
  do
    {
      if (n - i < k)
        k = n - i;
      for (j = 0; j < k; ++j)
        ni[j] = j;
      jbm_index_sort_flashl (x + i, ni, k - 1);
      i += k;
    }
  while (i < n);

}

int
main (int argn,                 ///< number of arguments.
      char **argc)              ///< argument strings array.
{
  gsl_rng *rng;
  JBDOUBLE *xl, *yl, *zl, *tl;
  JBFLOAT *x, *y, *z, *t;
  clock_t t0[8], tf[8];
  unsigned long seed;
  unsigned int i, j, k, n, *ni;
  if (argn != 5)
    {
      printf ("Bad arguments number\nSintax is:\n"
              "./index_sort array_length sort_number random_seed algorithm\n");
      return 1;
    }
  n = strtoul (argc[1], NULL, 0);
  k = strtoul (argc[2], NULL, 0);
  seed = strtoul (argc[3], NULL, 0);
  j = strtoul (argc[4], NULL, 0);
  if (!j || !n || !k || k > n)
    {
      printf ("Bad argument\n");
      return 2;
    }
  rng = gsl_rng_alloc (gsl_rng_taus2);
  gsl_rng_set (rng, seed);
  ni = (unsigned int *) malloc (k * sizeof (unsigned int));
  x = (JBFLOAT *) malloc (n * sizeof (JBFLOAT));
  y = (JBFLOAT *) malloc (n * sizeof (JBFLOAT));
  z = (JBFLOAT *) malloc (n * sizeof (JBFLOAT));
  t = (JBFLOAT *) malloc (n * sizeof (JBFLOAT));
  xl = (JBDOUBLE *) malloc (n * sizeof (JBDOUBLE));
  yl = (JBDOUBLE *) malloc (n * sizeof (JBDOUBLE));
  zl = (JBDOUBLE *) malloc (n * sizeof (JBDOUBLE));
  tl = (JBDOUBLE *) malloc (n * sizeof (JBDOUBLE));
  for (i = 0; i < n; ++i)
    {
      x[i] = (JBFLOAT) gsl_rng_uniform (rng);
      y[i] = (JBFLOAT) - i;
      z[i] = (JBFLOAT) i;
      t[i] = EXP (-100. * jbm_fsqr (x[i] - 0.5));
      xl[i] = (JBDOUBLE) gsl_rng_uniform (rng);
      yl[i] = (JBDOUBLE) - i;
      zl[i] = (JBDOUBLE) i;
      tl[i] = EXPL (-100.L * jbm_fsqrl (xl[i] - 0.5L));
    }
  gsl_rng_free (rng);
  switch (j)
    {
    case 1:
      t0[0] = clock ();
      sort_interchange (x, ni, n, k);
      t0[1] = tf[0] = clock ();
      sort_interchange (y, ni, n, k);
      t0[2] = tf[1] = clock ();
      sort_interchange (z, ni, n, k);
      t0[3] = tf[2] = clock ();
      sort_interchange (t, ni, n, k);
      t0[4] = tf[3] = clock ();
      sort_interchangel (xl, ni, n, k);
      t0[5] = tf[4] = clock ();
      sort_interchangel (yl, ni, n, k);
      t0[6] = tf[5] = clock ();
      sort_interchangel (zl, ni, n, k);
      t0[7] = tf[6] = clock ();
      sort_interchangel (tl, ni, n, k);
      tf[7] = clock ();
      printf ("interchange %u %u %le %le %le %le %le %le %le %le\n", i, k,
              ((double) (tf[0] - t0[0])) / CLOCKS_PER_SEC,
              ((double) (tf[1] - t0[1])) / CLOCKS_PER_SEC,
              ((double) (tf[2] - t0[2])) / CLOCKS_PER_SEC,
              ((double) (tf[3] - t0[3])) / CLOCKS_PER_SEC,
              ((double) (tf[4] - t0[4])) / CLOCKS_PER_SEC,
              ((double) (tf[5] - t0[5])) / CLOCKS_PER_SEC,
              ((double) (tf[6] - t0[6])) / CLOCKS_PER_SEC,
              ((double) (tf[7] - t0[7])) / CLOCKS_PER_SEC);
      j = 0;
      break;
    case 2:
      t0[0] = clock ();
      sort_insertion (x, ni, n, k);
      t0[1] = tf[0] = clock ();
      sort_insertion (y, ni, n, k);
      t0[2] = tf[1] = clock ();
      sort_insertion (z, ni, n, k);
      t0[3] = tf[2] = clock ();
      sort_insertion (t, ni, n, k);
      t0[4] = tf[3] = clock ();
      sort_insertionl (xl, ni, n, k);
      t0[5] = tf[4] = clock ();
      sort_insertionl (yl, ni, n, k);
      t0[6] = tf[5] = clock ();
      sort_insertionl (zl, ni, n, k);
      t0[7] = tf[6] = clock ();
      sort_insertionl (tl, ni, n, k);
      tf[7] = clock ();
      printf ("insertion %u %u %le %le %le %le %le %le %le %le\n", i, k,
              ((double) (tf[0] - t0[0])) / CLOCKS_PER_SEC,
              ((double) (tf[1] - t0[1])) / CLOCKS_PER_SEC,
              ((double) (tf[2] - t0[2])) / CLOCKS_PER_SEC,
              ((double) (tf[3] - t0[3])) / CLOCKS_PER_SEC,
              ((double) (tf[4] - t0[4])) / CLOCKS_PER_SEC,
              ((double) (tf[5] - t0[5])) / CLOCKS_PER_SEC,
              ((double) (tf[6] - t0[6])) / CLOCKS_PER_SEC,
              ((double) (tf[7] - t0[7])) / CLOCKS_PER_SEC);
      j = 0;
      break;
    case 3:
      t0[0] = clock ();
      sort_merge (x, ni, n, k);
      t0[1] = tf[0] = clock ();
      sort_merge (y, ni, n, k);
      t0[2] = tf[1] = clock ();
      sort_merge (z, ni, n, k);
      t0[3] = tf[2] = clock ();
      sort_merge (t, ni, n, k);
      t0[4] = tf[3] = clock ();
      sort_mergel (xl, ni, n, k);
      t0[5] = tf[4] = clock ();
      sort_mergel (yl, ni, n, k);
      t0[6] = tf[5] = clock ();
      sort_mergel (zl, ni, n, k);
      t0[7] = tf[6] = clock ();
      sort_mergel (tl, ni, n, k);
      tf[7] = clock ();
      printf ("merge %u %u %le %le %le %le %le %le %le %le\n", i, k,
              ((double) (tf[0] - t0[0])) / CLOCKS_PER_SEC,
              ((double) (tf[1] - t0[1])) / CLOCKS_PER_SEC,
              ((double) (tf[2] - t0[2])) / CLOCKS_PER_SEC,
              ((double) (tf[3] - t0[3])) / CLOCKS_PER_SEC,
              ((double) (tf[4] - t0[4])) / CLOCKS_PER_SEC,
              ((double) (tf[5] - t0[5])) / CLOCKS_PER_SEC,
              ((double) (tf[6] - t0[6])) / CLOCKS_PER_SEC,
              ((double) (tf[7] - t0[7])) / CLOCKS_PER_SEC);
      j = 0;
      break;
    case 4:
      t0[0] = clock ();
      sort_flash (x, ni, n, k);
      t0[1] = tf[0] = clock ();
      sort_flash (y, ni, n, k);
      t0[2] = tf[1] = clock ();
      sort_flash (z, ni, n, k);
      t0[3] = tf[2] = clock ();
      sort_flash (t, ni, n, k);
      t0[4] = tf[3] = clock ();
      sort_flashl (xl, ni, n, k);
      t0[5] = tf[4] = clock ();
      sort_flashl (yl, ni, n, k);
      t0[6] = tf[5] = clock ();
      sort_flashl (zl, ni, n, k);
      t0[7] = tf[6] = clock ();
      sort_flashl (tl, ni, n, k);
      tf[7] = clock ();
      printf ("flash %u %u %le %le %le %le %le %le %le %le\n", i, k,
              ((double) (tf[0] - t0[0])) / CLOCKS_PER_SEC,
              ((double) (tf[1] - t0[1])) / CLOCKS_PER_SEC,
              ((double) (tf[2] - t0[2])) / CLOCKS_PER_SEC,
              ((double) (tf[3] - t0[3])) / CLOCKS_PER_SEC,
              ((double) (tf[4] - t0[4])) / CLOCKS_PER_SEC,
              ((double) (tf[5] - t0[5])) / CLOCKS_PER_SEC,
              ((double) (tf[6] - t0[6])) / CLOCKS_PER_SEC,
              ((double) (tf[7] - t0[7])) / CLOCKS_PER_SEC);
      j = 0;
      break;
    default:
      printf ("Bad algorithm\n");
      j = 3;
    }
  free (ni);
  free (x);
  free (y);
  free (z);
  free (t);
  free (xl);
  free (yl);
  free (zl);
  free (tl);
  return j;
}
