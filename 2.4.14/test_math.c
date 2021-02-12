#include "jb_math.h"

#define SOLVE_MATRIX 1
//#define SPLINE_CUBIC 1

#ifdef SOLVE_MATRIX

JBFLOAT x[] = {
  1., 3., 2., 16.,
  2., 4., 8., 18.,
  3., -1, 4., 0.
};
JBFLOAT y[] = { 3., 5., -1. };

typedef struct
{
  JBFLOAT A, B, C, D, E, F, G, H;
} Check;

int
main ()
{
  int i;
  Check check[4];
  jbm_matrix_solve (x, 3);
  printf ("x0=" FWF2 "x0=" FWF "\n", x[3], y[0]);
  printf ("x1=" FWF2 "x1=" FWF "\n", x[7], y[1]);
  printf ("x2=" FWF2 "x2=" FWF "\n", x[11], y[2]);
  check[0].D = 2.;
  check[0].E = 1.;
  check[1].C = 1.;
  check[1].D = 2.;
  check[1].E = 1.;
  check[2].C = -1.;
  check[2].D = 2.;
  check[2].E = -1.;
  check[3].C = -1.;
  check[3].D = 1.;
  check[0].H = 5.;
  check[1].H = 9.;
  check[2].H = -7.;
  check[3].H = 6.;
  jbm_varray_solve_tridiagonal (&check[1].C, &check[0].D, &check[0].E,
                                &check[0].H, sizeof (Check), 3);
  for (i = 0; i < 4; ++i)
    printf ("x%d=" FWF "\n", i, check[i].H);
  return 0;
}

#endif

#ifdef SPLINE_CUBIC

#define FWF2 FWF" "

JBFLOAT x[] = { 0., 1., 2., 3., 4., 5. };
JBFLOAT y[] = { 0., 1., 3., 6., 8., 7. };

JBFLOAT A[] = { 1., 2., -1. };
JBFLOAT B[] = { 3., 1., 4., 7. };
JBFLOAT C[] = { -1., 2., -3., 4., 2. };
JBFLOAT D[] = { -2., -1., 3., 1. };
JBFLOAT E[] = { -3., 1., 2. };
JBFLOAT H[] = { -20., 13., 14., 52., 48. };

main ()
{
  int i;
  FILE *file;
  JBFLOAT *c, *d, *e;
  jbm_matrix_solve_pentadiagonal (A, B, C, D, E, H, 5);
  for (i = 0; i < 5; ++i)
    printf ("i=%d x=" FWF "\n", i, H[i]);
  jbm_spline_cubic (x, y, 6, &c, &d, &e);
  file = fopen ("out", "w");
  for (i = 0; i < 5; ++i)
    {
      printf ("i=%d c=" FWF " d=" FWF " e=" FWF "\n", i, c[i], d[i], e[i]);
      fprintf (file, FWF2 FWF2 FWF2 FWF2 FWF "\n",
               x[i], y[i], c[i], d[i], e[i]);
    }
  fclose (file);
  jbm_regression (x, y, 6, &c, 2);
  for (i = 0; i <= 2; ++i)
    printf ("i=%d c=" FWF "\n", i, c[i]);
  jbm_regression (x, y, 6, &c, 3);
  for (i = 0; i <= 3; ++i)
    printf ("i=%d c=" FWF "\n", i, c[i]);
  return 0;
}

#else

#ifdef TRANSVERSAL_SECTION_REGIONS

int n = 24;
JBFLOAT l[25] =
  { 0., -1., -1., 0., 2., 0., 0., 2., 1., 3., 2., 4., 5., 5., 3., 3., 6., 4.,
  2., 3., 6., 6., 7., 5., 5.
};

JBFLOAT z[25] =
  { 6., 6., 3., 5., 3., 3., 2., 2., 3., 2., 0., 0., 1., 3., 3., 4., 3., 5.,
  4.,
  6., 5., 4., 5., 6., 7.
};

main ()
{
  JBFLOAT *zz;
  int *ni, *nj, *nij, nmax, nmin;
  stderr = fopen ("log", "w");
  jbm_transversal_section_regions (l, z, n, &zz, &ni, &nj, &nij, &nmax, &nmin);
  return 0;
}

#endif

#ifdef FARRAY_MEAN_SQUARE_ERROR

int na = 6, nr = 2;
JBFLOAT xa[7] = { 0., 1., 2., 3., 4., 5., 6. };
JBFLOAT ya[7] = { 3., 2., -1., 4., 7., 3., 1. };
JBFLOAT xr[3] = { 1.5, 3.2, 4.8 };
JBFLOAT yr[3] = { 2., 3., 1. };

main ()
{
  printf ("MSE = " FWL "\n",
          jbm_farray_mean_square_error (xa, ya, na, xr, yr, nr));
  return 0;
}

#endif

#ifdef VARRAY_MEAN_SQUARE_ERROR

typedef struct
{
  JBFLOAT x, y, z;
} P3;

typedef struct
{
  JBFLOAT x, y;
} P2;

int na = 6, nr = 2;
P2 va[7] = { 0., 3., 1., 2., 2., -1., 3., 4., 4., 7., 5., 3., 6., 1. };
P3 vr[3] = { 1.5, 2., 0., 3.2, 3., 0., 4.8, 1., 0 };

main ()
{
  printf ("MSE = " FWL "\n",
          jbm_varray_mean_square_error
          (&(va->x), &(va->y), sizeof (P2), na,
           &(vr->x), &(vr->y), sizeof (P3), nr));
  return 0;
}

#endif

#ifdef FILE_MEAN_SQUARE_ERROR

main ()
{
  printf
    ("MSE = " FWL "\n",
     jbm_file_mean_square_error ("msea", 1, 2, 2, "mser", 1, 2, 3));
  return 0;
}

#endif

#endif
