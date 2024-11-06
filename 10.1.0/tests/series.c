#include "config.h"

#define DEBUG 0
#define CHECK_NUMBER 10000
#define FAST 1
#define MAX 42
#define TEST_MATRIX 0
#define TEST_RATIONAL 0

#if HAVE_QUADMATH
#define PRECISION 4
#else
#define PRECISION 3
#endif

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#if PRECISION == 1
#define ACOS acosf
#define ASIN asinf
#define ATAN atanf
#define COS cosf
#define ERF erff
#define ERFC erfcf
#define EXP expf
#define EXP2 exp2f
#define EXPM1 expm1f
#define FABS fabsf
#define FINITE finitef
#define FLOAT float
#define FORMAT "%.7e"
#define K0 0.f
#define K0_01 0.01f
#define K0_5 0.5f
#define K1 1.f
#define K2 2.f
#define K3 3.f
#define K4 4.f
#define K5_5 5.5f
#define K7 7.f
#define K7_5 7.5f
#define K9 9.f
#define K16 16.f
#define K18 18.f
#define K23 23.f
#define K52 52.f
#define K63 63.f
#define K100 100.f
#define K112 112.f
#define KM_LN2 M_LN2f
#define KM_PI M_PIf
#define KM_PI_4 M_PI_4f
#define KMAX FLT_MAX
#define LOG logf
#define LOG2 log2f
#define SIN sinf
#define SNPRINTF snprintf
#define SQRT sqrtf
#include <math.h>
#elif PRECISION == 2
#define ACOS acos
#define ASIN asin
#define ATAN atan
#define COS cos
#define ERF erf
#define ERFC erfc
#define EXP exp
#define EXP2 exp2
#define EXPM1 expm1
#define FABS fabs
#define FINITE finite
#define FLOAT double
#define FORMAT "%.16le"
#define K0 0.
#define K0_01 0.01
#define K0_5 0.5
#define K1 1.
#define K2 2.
#define K3 3.
#define K4 4.
#define K5_5 5.5
#define K7 7.
#define K7_5 7.5
#define K9 9.
#define K16 16.
#define K18 18.
#define K23 23.
#define K52 52.
#define K63 63.
#define K100 100.
#define K112 112.
#define KM_LN2 M_LN2
#define KM_PI M_PI
#define KM_PI_4 M_PI_4
#define KMAX DBL_MAX
#define LOG log
#define LOG2 log2
#define SIN sin
#define SNPRINTF snprintf
#define SQRT sqrt
#include <math.h>
#elif PRECISION == 3
#define ACOS acosl
#define ASIN asinl
#define ATAN atanl
#define COS cosl
#define ERF erfl
#define ERFC erfcl
#define EXP expl
#define EXP2 exp2l
#define EXPM1 expm1l
#define FABS fabsl
#define FINITE finitel
#define FLOAT long double
#define FORMAT "%.19Le"
#define K0 0.L
#define K0_01 0.01L
#define K0_5 0.5L
#define K1 1.L
#define K2 2.L
#define K3 3.L
#define K4 4.L
#define K5_5 5.5L
#define K7 7.L
#define K7_5 7.5L
#define K9 9.L
#define K16 16.L
#define K18 18.L
#define K23 23.L
#define K52 52.L
#define K63 63.L
#define K100 100.L
#define K112 112.L
#define KM_LN2 M_LN2l
#define KM_PI M_PIl
#define KM_PI_4 M_PI_4l
#define KMAX LDBL_MAX
#define LOG logl
#define LOG2 log2l
#define SIN sinl
#define SNPRINTF snprintf
#define SQRT sqrtl
#include <math.h>
#elif PRECISION == 4
#define ACOS acosq
#define ASIN asinq
#define ATAN atanq
#define COS cosq
#define ERF erfq
#define ERFC erfcq
#define EXP expq
#define EXP2 exp2q
#define EXPM1 expm1q
#define FABS fabsq
#define FINITE finiteq
#define FLOAT __float128
#define FORMAT "%.34Qe"
#define K0 0.Q
#define K0_01 0.01Q
#define K0_5 0.5Q
#define K1 1.Q
#define K2 2.Q
#define K3 3.Q
#define K4 4.Q
#define K5_5 5.5Q
#define K7 7.Q
#define K7_5 7.5Q
#define K9 9.Q
#define K16 16.Q
#define K18 18.Q
#define K23 23.Q
#define K52 52.Q
#define K63 63.Q
#define K100 100.Q
#define K112 112.Q
#define KM_LN2 M_LN2q
#define KM_PI M_PIq
#define KM_PI_4 M_PI_4q
#define KMAX FLT128_MAX
#define LOG logq
#define LOG2 log2q
#define SIN sinq
#define SNPRINTF quadmath_snprintf
#define SQRT sqrtq
#include <quadmath.h>
#else
#error "Precision not available"
#endif

void
number_print (FILE *f, const char *label, const FLOAT x)
{
  char s[64];
  SNPRINTF (s, 64, FORMAT, x);
  fprintf (f, "%s=%s\n", label, s);
}

void
number_change (FLOAT *restrict f1, FLOAT *restrict f2)
{
  FLOAT f3;
  f3 = *f1;
  *f1 = *f2;
  *f2 = f3;
}

FLOAT
number_find (FLOAT (*f) (const FLOAT), const FLOAT y,
             const FLOAT xmin, const FLOAT xmax)
{
  FLOAT x0, x1, x2, f0, f2;
  unsigned int i;
  x1 = xmin;
  x2 = xmax;
  f0 = f (x1) - y;
  f2 = f (x2) - y;
  if (f0 * f2 > K0)
    {
      printf ("Unable to find\n");
      return K0;
    }
  if (f0 < K0)
    {
#if DEBUG
      fprintf (stderr, "lower\n");
#endif
      for (i = 0; i < 128; ++i)
        {
          x0 = K0_5 * (x1 + x2);
          f0 = f (x0);
          if (f0 > y)
            x2 = x0;
          else
            x1 = x0;
#if DEBUG
          number_print (stderr, "x1", x1);
          number_print (stderr, "x2", x2);
#endif
        }
    }
  else
    {
#if DEBUG
      fprintf (stderr, "higher\n");
#endif
      for (i = 0; i < 128; ++i)
        {
          x0 = K0_5 * (x1 + x2);
          f0 = f (x0);
          if (f0 < y)
            x2 = x0;
          else
            x1 = x0;
#if DEBUG
          number_print (stderr, "x1", x1);
          number_print (stderr, "x2", x2);
#endif
        }
    }
  return x0;
}

FLOAT
number_max (FLOAT (*f) (const FLOAT))
{
  FLOAT x0, x1, x2;
  unsigned int i;
  x2 = x1 = K1;
  while (FINITE (x2) && FINITE (f (x2)))
    {
      x1 = x2;
      x2 += x2;
#if DEBUG
      number_print (stderr, "x1", x1);
      number_print (stderr, "x2", x2);
#endif
    }
  while (!FINITE (x1) && !FINITE (f (x1)))
    {
      x2 = x1;
      x1 *= K0_5;
#if DEBUG
      number_print (stderr, "x1", x1);
      number_print (stderr, "x2", x2);
#endif
    }
  for (i = 0; i < 128; ++i)
    {
      x0 = K0_5 * (x1 + x2);
      if (FINITE (x0) && FINITE (f (x0)))
        x1 = x0;
      else
        x2 = x0;
#if DEBUG
      number_print (stderr, "x1", x1);
      number_print (stderr, "x2", x2);
#endif
    }
  return x1;
}

FLOAT
number_min (FLOAT (*f) (const FLOAT))
{
  FLOAT x0, x1, x2;
  unsigned int i;
  x2 = x1 = K1;
  while (x1 > K0 && FINITE (f (x1)))
    {
      x2 = x1;
      x1 *= K0_5;
#if DEBUG
      number_print (stderr, "x1", x1);
      number_print (stderr, "x2", x2);
#endif
    }
  while (FINITE (x2) && !FINITE (f (x2)))
    {
      x1 = x2;
      x2 += x2;
#if DEBUG
      number_print (stderr, "x1", x1);
      number_print (stderr, "x2", x2);
#endif
    }
  for (i = 0; i < 128; ++i)
    {
      x0 = K0_5 * (x1 + x2);
      if (x0 > K0 && FINITE (x0) && FINITE (f (x0)))
        x2 = x0;
      else
        x1 = x0;
    }
  return x2;
}

FLOAT
polynomial (const FLOAT x, const FLOAT *p, const unsigned int o)
{
  FLOAT y, xn;
  unsigned int i;
  for (i = 0, y = p[0], xn = x; ++i <= o; xn *= x)
    y += p[i] * xn;
  return y;
}

FLOAT
rational (const FLOAT x, const FLOAT *p, const unsigned int o,
          const unsigned int on)
{
  unsigned int o1;
  if (o == on)
    return polynomial (x, p, o);
  o1 = on + 1;
  return polynomial (x, p, on) / (K1 + x * polynomial (x, p + o1, o - o1));
}

FLOAT
odd (const FLOAT x, const FLOAT *p, const unsigned int o, const unsigned int on)
{
  return rational (x * x, p, o, on);
}

FLOAT
even (FLOAT (*f) (const FLOAT), const FLOAT x)
{
  return x * f (x);
}

void
vector_print (FILE *f, const char *label, const FLOAT *x, const unsigned int n)
{
  char s[512];
  unsigned int i;
  for (i = 0; i < n; ++i)
    {
      snprintf (s, 512, "%s[%u]", label, i);
      number_print (f, s, x[i]);
    }
}

void
vector_init (FLOAT *v, const unsigned int n, const FLOAT x1, const FLOAT x2)
{
  FLOAT dx;
  unsigned int i, n1;
  n1 = n - 1;
  dx = x2 - x1;
  v[0] = x1;
  for (i = 1; i < n1; ++i)
    v[i] = x1 + (FLOAT) i *dx / (FLOAT) n1;
  v[n1] = x2;
}

void
matrix_print (FILE *f, const char *label, const FLOAT *x, const unsigned int n)
{
  const FLOAT *y;
  char s[512];
  unsigned int i;
  for (i = 0, y = x; i < n; ++i, y += n)
    {
      snprintf (s, 512, "%s[%u]", label, i);
      vector_print (f, s, y, n);
    }
}

FLOAT *
vector_new (const unsigned int n)
{
  return (FLOAT *) malloc (n * sizeof (FLOAT));
}

void
vector_copy (FLOAT *restrict v1, const FLOAT *restrict v2, const unsigned int n)
{
  memcpy (v1, v2, n * sizeof (FLOAT));
}

void
vector_change (FLOAT *restrict v1, FLOAT *restrict v2, unsigned int n)
{
  FLOAT v3[n];
  size_t s;
  s = n * sizeof (FLOAT);
  memcpy (v3, v1, s);
  memcpy (v1, v2, s);
  memcpy (v2, v3, s);
}

FLOAT *
matrix_new (const unsigned int n)
{
  return vector_new (n * n);
}

void
matrix_copy (FLOAT *restrict m1, const FLOAT *restrict m2, const unsigned int n)
{
  vector_copy (m1, m2, n * n);
}

void
matrix_vector_solve (FLOAT *restrict m, FLOAT *restrict v, unsigned int n)
{
  FLOAT *row1, *row2;
  FLOAT r, r2;
  unsigned int i, j, k;
#if DEBUG
  matrix_print (stderr, "m", m, n);
  vector_print (stderr, "v", v, n);
#endif
  for (i = 1, row1 = m; i < n; ++i, row1 += n + 1)
    {
      k = i - 1;
      r = FABS (row1[0]);
      for (j = i, row2 = row1; j < n; ++j)
        {
          row2 += n;
          r2 = FABS (row2[0]);
          if (r2 > r)
            {
              r = r2;
              k = j;
            }
        }
#if DEBUG
      printf ("i=%u k=%u\n", i, k);
#endif
      if (k >= i)
        {
          row2 = row1 + (k - i + 1) * n;
          number_change (v + i - 1, v + k);
          vector_change (row1, row2, n - i + 1);
        }
      for (j = i, row2 = row1; j < n; ++j)
        {
          row2 += n;
          r = row2[0] / row1[0];
          v[j] -= r * v[i - 1];
          for (k = 1; k <= n - i; ++k)
            row2[k] -= r * row1[k];
        }
#if DEBUG
      matrix_print (stderr, "m", m, n);
      vector_print (stderr, "v", v, n);
#endif
    }
#if DEBUG
  matrix_print (stderr, "m", m, n);
  vector_print (stderr, "v", v, n);
#endif
  for (i = n, row1 = m + n * n - 1; i-- > 0; row1 -= n + 1)
    {
      for (j = 0; ++j < n - i;)
        v[i] -= row1[j] * v[i + j];
      v[i] /= row1[0];
    }
#if DEBUG
  vector_print (stderr, "v", v, n);
#endif
}

void
matrix_x_vector (const FLOAT *restrict m, const FLOAT *restrict v,
                 FLOAT *restrict r, unsigned int n)
{
  const FLOAT *row;
  unsigned int i, j;
  for (i = 0, row = m; i < n; ++i, row += n)
    {
      r[i] = row[0] * v[0];
      for (j = 1; j < n; ++j)
        r[i] += row[j] * v[j];
    }
}

void
matrix_x_matrix (const FLOAT *restrict m1, const FLOAT *restrict m2,
                 FLOAT *restrict m3, unsigned int n)
{
  const FLOAT *row, *col;
  unsigned int i, j, k;
  for (i = 0, row = m1, col = m2; i < n; ++i, row += n, ++col)
    {
      for (j = 0; j < n; ++j, ++m3)
        {
          *m3 = K0;
          for (k = 0; k < n; ++k)
            *m3 += row[k] * col[k * n];
        }
    }
}

void
matrix_vector_rational (FLOAT *m, FLOAT *v,
                        FLOAT (*f) (FLOAT),
                        const FLOAT *x, const unsigned int n,
                        const double c, const int p, const unsigned int on)
{
  FLOAT *row;
  FLOAT x1, f1, xn, x0;
  unsigned int i, j;
  for (i = 0, row = m; i < n; ++i, row += n)
    {
      row[0] = K1;
      x1 = x[i];
      x0 = c + x1;
      if (p)
        x1 *= x1;
      if (p < 0)
        f1 = even (f, x0);
      else
        f1 = f (x0);
      v[i] = f1;
      for (j = 1, xn = x1; j <= on; ++j, xn *= x1)
        row[j] = xn;
      for (xn = -f1 * x1; j < n; ++j, xn *= x1)
        row[j] = xn;
    }
#if DEBUG
  matrix_print (stderr, "m", m, n);
  vector_print (stderr, "v", v, n);
#endif
}

FLOAT
error (const FLOAT x,
       FLOAT (*f1) (const FLOAT),
       const FLOAT *a, const FLOAT c, const int p, const unsigned int o,
       const unsigned int on)
{
  FLOAT x0;
  x0 = x + c;
  if (p > 0)
    return odd (x, a, o, on) - f1 (x0);
  if (p < 0)
    return odd (x, a, o, on) - even (f1, x0);
  return rational (x, a, o, on) - f1 (x0);
}

void
error_find (const FLOAT x1, const FLOAT x2,
            FLOAT (*f1) (const FLOAT),
            const FLOAT *a, const FLOAT c, const int p,
            const unsigned int o, const unsigned int on, FLOAT *x, FLOAT *e)
{
  FLOAT dx, xi, ei, ai, m;
  unsigned int i;
  *e = ei = error (x1, f1, a, c, p, o, on);
  m = ai = FABS (ei);
  *x = x1;
  dx = x2 - x1;
  for (i = 1; i < CHECK_NUMBER; ++i)
    {
      xi = x1 + (FLOAT) i *dx / (FLOAT) CHECK_NUMBER;
      ei = error (xi, f1, a, c, p, o, on);
      ai = FABS (ei);
      if (ai > m)
        {
          m = ai;
          *e = ei;
          *x = xi;
        }
    }
  ei = error (x2, f1, a, c, p, o, on);
  ai = FABS (ei);
  if (ai > m)
    {
      *e = ei;
      *x = x2;
    }
}

void
error_print (FILE *f, char *label, const FLOAT x,
             FLOAT (*f1) (const FLOAT),
             const FLOAT *a, const FLOAT c, const int p, const unsigned int o,
             const unsigned int on)
{
  number_print (f, label, error (x, f1, a, c, p, o, on));
}

FLOAT
procedure (FLOAT *v, const unsigned int n, FLOAT (*f1) (const FLOAT),
           const FLOAT x1, const FLOAT x2, const FLOAT d,
           const int p, const unsigned int on)
{
  FLOAT m[MAX * MAX];
  FLOAT c[MAX];
  FLOAT x, e;
  unsigned int n1, o1;
  n1 = n;
  o1 = on;
  if (on == n - 1)
    ++n1, ++o1;
  vector_init (c, n1, x1, x2);
  matrix_vector_rational (m, v, f1, c, n1, d, p, o1);
  matrix_vector_solve (m, v, n1);
#if DEBUG
  error_print (stdout, "error(x1)", x1, f1, v, d, p, n1 - 1, o1);
  error_print (stdout, "error(x2)", x2, f1, v, d, p, n1 - 1, o1);
#endif
  error_find (x1, x2, f1, v, d, p, n1 - 1, o1, &x, &e);
#if DEBUG
  number_print (stdout, "max error x", x);
  number_print (stdout, "max error e", e);
#endif
  return e;
}

void
iterate (const char *label, FLOAT (*f) (const FLOAT),
         const FLOAT x1, const FLOAT x2, const FLOAT d, const int p)
{
  FLOAT v[MAX], r[MAX];
  const FLOAT a[PRECISION] = {
    EXP2 (-K23),
#if PRECISION > 1
    EXP2 (-K52),
#endif
#if PRECISION > 2
    EXP2 (-K63),
#endif
#if PRECISION > 3
    MAX * EXP2 (-K112)
#endif
  };
  FLOAT e, ae, emin, aemin;
  unsigned int i, j, l, imin, lmin;
  printf ("%s\n", label);
  for (j = 0; j < PRECISION; ++j)
    {
      number_print (stdout, "precision", a[j]);
      aemin = emin = KMAX;
      imin = lmin = 0;
      for (i = 2; i < MAX; ++i)
        {
          for (l = 0; l < i; ++l)
            {
              e = procedure (v, i, f, x1, x2, d, p, l);
              printf ("%s=%u-%u\n", "error", i - 1, l);
              number_print (stdout, "error", e);
              ae = FABS (e);
              if (ae < aemin)
                {
                  emin = e;
                  aemin = ae;
                  imin = i;
                  lmin = l;
                  if (l == i - 1)
                    vector_copy (r, v, i + 1);
                  else
                    vector_copy (r, v, i);
                }
            }
          if (FABS (emin) < a[j])
            break;
        }
      if (lmin == imin - 1)
        {
          printf ("polynomial=%u\n", imin);
          ++imin;
        }
      else
        printf ("rational=%u-%u\n", imin - 1, lmin);
      vector_print (stdout, label, r, imin);
      number_print (stdout, "best error", emin);
      printf ("\n");
    }
}

FLOAT
erfc_iq (const FLOAT x)
{
  FLOAT xi;
  xi = K1 / x;
  return ERFC (xi) * EXP (xi * xi) * x;
}

#if TEST_MATRIX

int
main ()
{
  const FLOAT cm4[16] = { K2, K0, K1, -K3, -K1, -K2, K7, K3,
    -K2, K3, K0, K3, -K2, -K1, K3, K2
  };
  const FLOAT cm3[9] = { K3, -K2, K2, -K2, K4, -K2, K7, K2, -K2 };
  const FLOAT cm2[4] = { K2, K3, K4, -K1 };
  const FLOAT cm1[1] = { K3 };
  const FLOAT cv4[4] = { K2, -K1, K3, K1 };
  const FLOAT cv3[3] = { K16, -K18, K4 };
  const FLOAT cv2[2] = { K5_5, K7_5 };
  const FLOAT cv1[1] = { K1 };
  FLOAT m[16], v[4];
  matrix_copy (m, cm1, 1);
  vector_copy (v, cv1, 1);
  matrix_vector_solve (m, v, 1);
  vector_print (stdout, "(1/3)", v, 1);
  matrix_copy (m, cm2, 2);
  vector_copy (v, cv2, 2);
  matrix_vector_solve (m, v, 2);
  vector_print (stdout, "(2,0.5)", v, 2);
  matrix_copy (m, cm3, 3);
  vector_copy (v, cv3, 3);
  matrix_vector_solve (m, v, 3);
  vector_print (stdout, "(2,-2,3)", v, 3);
  memcpy (m, cm4, 16 * sizeof (FLOAT));
  matrix_copy (m, cm4, 4);
  matrix_x_vector (m, cv4, v, 4);
  matrix_vector_solve (m, v, 4);
  vector_print (stdout, "", cv4, 4);
  vector_print (stdout, "=", v, 4);
}

#elif TEST_RATIONAL

int
main ()
{
  const FLOAT c[3] = { K1, K9, K16 };
  FLOAT m[9], v[3];
  matrix_vector_rational (m, v, SQRT, c, 3, K0, 0, 0);
#if DEBUG
  matrix_print (stdout, "m", m, 3);
  vector_print (stdout, "v", v, 3);
#endif
  matrix_vector_solve (m, v, 3);
  vector_print (stdout, "(420/473 -55/473 2/473)", v, 3);
  matrix_vector_rational (m, v, SQRT, c, 3, K0, 0, 1);
#if DEBUG
  matrix_print (stdout, "m", m, 3);
  vector_print (stdout, "v", v, 3);
#endif
  matrix_vector_solve (m, v, 3);
  vector_print (stdout, "(12/19 8/19 1/19)", v, 3);
  matrix_vector_rational (m, v, SQRT, c, 3, K0, 0, 2);
#if DEBUG
  matrix_print (stdout, "m", m, 3);
  vector_print (stdout, "v", v, 3);
#endif
  matrix_vector_solve (m, v, 3);
  vector_print (stdout, "(96/140 45/140 -1/140)", v, 3);
}

#else

int
main (int argn, char **argc __attribute__((unused)))
{
  FLOAT x;

  // check arguments
  if (argn != 1)
    {
      printf ("The syntax is:\n./series n\n");
      return 1;
    }

  // precision
  number_print (stdout, "FLT_EPSILON", (FLOAT) FLT_EPSILON);
  number_print (stdout, "f32 precision", EXP2 (-K23));
  number_print (stdout, "FLT_MIN", (FLOAT) FLT_MIN);
#if PRECISION > 1
  number_print (stdout, "DBL_EPSILON", (FLOAT) DBL_EPSILON);
  number_print (stdout, "f64 precision", EXP2 (-K52));
  number_print (stdout, "DBL_MIN", (FLOAT) DBL_MIN);
#endif
#if PRECISION > 2
  number_print (stdout, "LDBL_EPSILON", (FLOAT) LDBL_EPSILON);
  number_print (stdout, "f80 precision", EXP2 (-K63));
  number_print (stdout, "LDBL_MIN", (FLOAT) LDBL_MIN);
#endif
#if PRECISION > 3
  number_print (stdout, "FLT128_EPSILON", FLT128_EPSILON);
  number_print (stdout, "f128 precision", EXP2 (-K112));
  number_print (stdout, "FLT128_MIN", FLT128_MIN);
#endif
  printf ("\n");

  // exp2
  iterate ("exp2(x)", EXP2, K0, K1, K0, 0);

  // exp
  iterate ("exp(x)", EXP, -KM_LN2 / K2, KM_LN2 / K2, K0, 0);

  // expm1
  iterate ("expm1(x)", EXPM1, -KM_LN2 / K2, KM_LN2 / K2, K0, 0);

  // log
  iterate ("log(1+x)", LOG, -K1 / K3, K1 / K3, K1, 0);

  // log2
  iterate ("log2(x)", LOG2, K0_5, K1, K0, 0);

  // sin
  iterate ("sin(x)", SIN, K0, KM_PI_4, K0, -1);

  // cos
  iterate ("cos(x)", COS, K0, KM_PI_4, K0, 1);

  // atan
  iterate ("atan(x)", ATAN, K0, K0_5, K0, -1);
  iterate ("atan(1+x)", ATAN, -K0_5, K0_5, K1, 0);

  // erf
  iterate ("erf(x)", ERF, K0, K1, K0, -1);
  x = (FLOAT) 1.4012985e-45f;
  x = number_find (ERFC, x, K1, K100);
  number_print (stdout, "max x for erfcf", x);
  iterate ("x*exp(1/x^2)*erfc(1/x)", erfc_iq, K1 / x, K1, K0, 1);
  x = (FLOAT) 4.9406564584124654e-324;
  x = number_find (ERFC, x, K1, K100);
  number_print (stdout, "max x for erfc", x);
  iterate ("x*exp(1/x^2)*erfc(1/x)", erfc_iq, K1 / x, K1, K0, 1);

  return 0;
}

#endif
