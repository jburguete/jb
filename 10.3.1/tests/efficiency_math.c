#include "../src/math.h"
#include <gsl/gsl_rng.h>

#define SEED 7l

static inline void
efficiency_f32 (float (*f) (float), long double (*g) (long double),
                float xmin, float xmax, unsigned long int n, char *label)
{
  gsl_rng *rng;
  float *x, *y;
  long double em, e;
  float dx, t;
  clock_t t0;
  unsigned int i;
  rng = gsl_rng_alloc (gsl_rng_taus2);
  gsl_rng_set (rng, SEED);
  x = (float *) malloc (n * sizeof (float));
  y = (float *) malloc (n * sizeof (float));
  for (i = 0, dx = xmax - xmin; i < n; ++i)
    x[i] = xmin + dx * gsl_rng_uniform (rng);
  t0 = clock ();
  for (i = 0; i < n; ++i)
    y[i] = f (x[i]);
  t = (clock () - t0) / (n * (float) CLOCKS_PER_SEC);
  for (i = 0, em = 0.L; i < n; ++i)
    {
      e = fabsl (y[i] - g (x[i]));
      if (e > em)
        em = e;
    }
  printf ("%s time=%g error=%Lg\n", label, t, em);
  free (y);
  free (x);
  gsl_rng_free (rng);
}

static inline void
efficiency_f64 (double (*f) (double), long double (*g) (long double),
                double xmin, double xmax, unsigned long int n, char *label)
{
  gsl_rng *rng;
  double *x, *y;
  long double em, e;
  double dx, t;
  clock_t t0;
  unsigned int i;
  rng = gsl_rng_alloc (gsl_rng_taus2);
  gsl_rng_set (rng, SEED);
  x = (double *) malloc (n * sizeof (double));
  y = (double *) malloc (n * sizeof (double));
  for (i = 0, dx = xmax - xmin; i < n; ++i)
    x[i] = xmin + dx * gsl_rng_uniform (rng);
  t0 = clock ();
  for (i = 0; i < n; ++i)
    y[i] = f (x[i]);
  t = (clock () - t0) / (n * (float) CLOCKS_PER_SEC);
  for (i = 0, em = 0.L; i < n; ++i)
    {
      e = fabsl (y[i] - g (x[i]));
      if (e > em)
        em = e;
    }
  printf ("%s time=%lg error=%Lg\n", label, t, em);
  free (y);
  free (x);
  gsl_rng_free (rng);
}

static inline float
add_f32 (float x)
{
  return x + M_PIf;
}

static inline float
sub_f32 (float x)
{
  return x - M_PIf;
}

static inline float
mul_f32 (float x)
{
  return x * M_PIf;
}

static inline float
div_f32 (float x)
{
  return x / M_PIf;
}

static inline float
max_f32 (float x)
{
  return fmaxf (x, M_PIf);
}

static inline float
min_f32 (float x)
{
  return fminf (x, M_PIf);
}

static inline double
add_f64 (double x)
{
  return x + M_PI;
}

static inline double
sub_f64 (double x)
{
  return x - M_PI;
}

static inline double
mul_f64 (double x)
{
  return x * M_PI;
}

static inline double
div_f64 (double x)
{
  return x / M_PI;
}

static inline double
max_f64 (double x)
{
  return fmax (x, M_PI);
}

static inline double
min_f64 (double x)
{
  return fmin (x, M_PI);
}

static inline long double
add_f80 (long double x)
{
  return x + M_PIl;
}

static inline long double
sub_f80 (long double x)
{
  return x - M_PIl;
}

static inline long double
mul_f80 (long double x)
{
  return x * M_PIl;
}

static inline long double
div_f80 (long double x)
{
  return x / M_PIl;
}

static inline long double
max_f80 (long double x)
{
  return fmax (x, M_PIl);
}

static inline long double
min_f80 (long double x)
{
  return fmin (x, M_PIl);
}

#ifdef __SSE4_2__

static inline void
efficiency_4xf32 (__m128 (*f) (__m128), long double (*g) (long double),
                  float xmin, float xmax, unsigned long int n, char *label)
{
  gsl_rng *rng;
  __m128 xv, yv;
  float *x, *y;
  long double em, e;
  float dx, t;
  clock_t t0;
  unsigned int i;
  n = (n / 4) * 4;
  rng = gsl_rng_alloc (gsl_rng_taus2);
  gsl_rng_set (rng, SEED);
  x = (float *) MALLOC (n * sizeof (float));
  y = (float *) MALLOC (n * sizeof (float));
  for (i = 0, dx = xmax - xmin; i < n; ++i)
    x[i] = xmin + dx * gsl_rng_uniform (rng);
  t0 = clock ();
  for (i = 0; i < n; i += 4)
    {
      xv = _mm_load_ps (x + i);
      yv = f (xv);
      _mm_store_ps (y + i, yv);
    }
  t = (clock () - t0) / (n * (float) CLOCKS_PER_SEC);
  for (i = 0, em = 0.L; i < n; ++i)
    {
      e = fabsl (y[i] - g (x[i]));
      if (e > em)
        em = e;
    }
  printf ("%s time=%g error=%Lg\n", label, t, em);
  FREE (y);
  FREE (x);
  gsl_rng_free (rng);
}

static inline void
efficiency_2xf64 (__m128d (*f) (__m128d), long double (*g) (long double),
                  double xmin, double xmax, unsigned long int n, char *label)
{
  gsl_rng *rng;
  __m128d xv, yv;
  double *x, *y;
  long double em, e;
  double dx, t;
  clock_t t0;
  unsigned int i;
  n = (n / 2) * 2;
  rng = gsl_rng_alloc (gsl_rng_taus2);
  gsl_rng_set (rng, SEED);
  x = (double *) MALLOC (n * sizeof (double));
  y = (double *) MALLOC (n * sizeof (double));
  for (i = 0, dx = xmax - xmin; i < n; ++i)
    x[i] = xmin + dx * gsl_rng_uniform (rng);
  t0 = clock ();
  for (i = 0; i < n; i += 2)
    {
      xv = _mm_load_pd (x + i);
      yv = f (xv);
      _mm_store_pd (y + i, yv);
    }
  t = (clock () - t0) / (n * (double) CLOCKS_PER_SEC);
  for (i = 0, em = 0.L; i < n; ++i)
    {
      e = fabsl (y[i] - g (x[i]));
      if (e > em)
        em = e;
    }
  printf ("%s time=%lg error=%Lg\n", label, t, em);
  FREE (y);
  FREE (x);
  gsl_rng_free (rng);
}

static inline __m128
add_4xf32 (__m128 x)
{
  return _mm_add_ps (x, _mm_set1_ps (M_PIf));
}

static inline __m128
sub_4xf32 (__m128 x)
{
  return _mm_sub_ps (x, _mm_set1_ps (M_PIf));
}

static inline __m128
mul_4xf32 (__m128 x)
{
  return _mm_mul_ps (x, _mm_set1_ps (M_PIf));
}

static inline __m128
div_4xf32 (__m128 x)
{
  return _mm_div_ps (x, _mm_set1_ps (M_PIf));
}

static inline __m128
sqrt_4xf32 (__m128 x)
{
  return _mm_sqrt_ps (x);
}

static inline __m128
max_4xf32 (__m128 x)
{
  return _mm_max_ps (x, _mm_set1_ps (M_PIf));
}

static inline __m128
min_4xf32 (__m128 x)
{
  return _mm_min_ps (x, _mm_set1_ps (M_PIf));
}

static inline __m128d
add_2xf64 (__m128d x)
{
  return _mm_add_pd (x, _mm_set1_pd (M_PI));
}

static inline __m128d
sub_2xf64 (__m128d x)
{
  return _mm_sub_pd (x, _mm_set1_pd (M_PI));
}

static inline __m128d
mul_2xf64 (__m128d x)
{
  return _mm_mul_pd (x, _mm_set1_pd (M_PI));
}

static inline __m128d
div_2xf64 (__m128d x)
{
  return _mm_div_pd (x, _mm_set1_pd (M_PI));
}

static inline __m128d
sqrt_2xf64 (__m128d x)
{
  return _mm_sqrt_pd (x);
}

static inline __m128d
max_2xf64 (__m128d x)
{
  return _mm_max_pd (x, _mm_set1_pd (M_PI));
}

static inline __m128d
min_2xf64 (__m128d x)
{
  return _mm_min_pd (x, _mm_set1_pd (M_PI));
}

#endif

#ifdef __AVX__

static inline void
efficiency_8xf32 (__m256 (*f) (__m256), long double (*g) (long double),
                  float xmin, float xmax, unsigned long int n, char *label)
{
  gsl_rng *rng;
  __m256 xv, yv;
  float *x, *y;
  long double em, e;
  float dx, t;
  clock_t t0;
  unsigned int i;
  n = (n / 8) * 8;
  rng = gsl_rng_alloc (gsl_rng_taus2);
  gsl_rng_set (rng, SEED);
  x = (float *) MALLOC (n * sizeof (float));
  y = (float *) MALLOC (n * sizeof (float));
  for (i = 0, dx = xmax - xmin; i < n; ++i)
    x[i] = xmin + dx * gsl_rng_uniform (rng);
  t0 = clock ();
  for (i = 0; i < n; i += 8)
    {
      xv = _mm256_load_ps (x + i);
      yv = f (xv);
      _mm256_store_ps (y + i, yv);
    }
  t = (clock () - t0) / (n * (float) CLOCKS_PER_SEC);
  for (i = 0, em = 0.L; i < n; ++i)
    {
      e = fabsl (y[i] - g (x[i]));
      if (e > em)
        em = e;
    }
  printf ("%s time=%g error=%Lg\n", label, t, em);
  FREE (y);
  FREE (x);
  gsl_rng_free (rng);
}

static inline void
efficiency_4xf64 (__m256d (*f) (__m256d), long double (*g) (long double),
                  double xmin, double xmax, unsigned long int n, char *label)
{
  gsl_rng *rng;
  __m256d xv, yv;
  double *x, *y;
  long double em, e;
  double dx, t;
  clock_t t0;
  unsigned int i;
  n = (n / 4) * 4;
  rng = gsl_rng_alloc (gsl_rng_taus2);
  gsl_rng_set (rng, SEED);
  x = (double *) MALLOC (n * sizeof (double));
  y = (double *) MALLOC (n * sizeof (double));
  for (i = 0, dx = xmax - xmin; i < n; ++i)
    x[i] = xmin + dx * gsl_rng_uniform (rng);
  t0 = clock ();
  for (i = 0; i < n; i += 4)
    {
      xv = _mm256_load_pd (x + i);
      yv = f (xv);
      _mm256_store_pd (y + i, yv);
    }
  t = (clock () - t0) / (n * (double) CLOCKS_PER_SEC);
  for (i = 0, em = 0.L; i < n; ++i)
    {
      e = fabsl (y[i] - g (x[i]));
      if (e > em)
        em = e;
    }
  printf ("%s time=%lg error=%Lg\n", label, t, em);
  FREE (y);
  FREE (x);
  gsl_rng_free (rng);
}

static inline __m256
add_8xf32 (__m256 x)
{
  return _mm256_add_ps (x, _mm256_set1_ps (M_PIf));
}

static inline __m256
sub_8xf32 (__m256 x)
{
  return _mm256_sub_ps (x, _mm256_set1_ps (M_PIf));
}

static inline __m256
mul_8xf32 (__m256 x)
{
  return _mm256_mul_ps (x, _mm256_set1_ps (M_PIf));
}

static inline __m256
div_8xf32 (__m256 x)
{
  return _mm256_div_ps (x, _mm256_set1_ps (M_PIf));
}

static inline __m256
sqrt_8xf32 (__m256 x)
{
  return _mm256_sqrt_ps (x);
}

static inline __m256
max_8xf32 (__m256 x)
{
  return _mm256_max_ps (x, _mm256_set1_ps (M_PIf));
}

static inline __m256
min_8xf32 (__m256 x)
{
  return _mm256_min_ps (x, _mm256_set1_ps (M_PIf));
}

static inline __m256d
add_4xf64 (__m256d x)
{
  return _mm256_add_pd (x, _mm256_set1_pd (M_PI));
}

static inline __m256d
sub_4xf64 (__m256d x)
{
  return _mm256_sub_pd (x, _mm256_set1_pd (M_PI));
}

static inline __m256d
mul_4xf64 (__m256d x)
{
  return _mm256_mul_pd (x, _mm256_set1_pd (M_PI));
}

static inline __m256d
div_4xf64 (__m256d x)
{
  return _mm256_div_pd (x, _mm256_set1_pd (M_PI));
}

static inline __m256d
sqrt_4xf64 (__m256d x)
{
  return _mm256_sqrt_pd (x);
}

static inline __m256d
max_4xf64 (__m256d x)
{
  return _mm256_max_pd (x, _mm256_set1_pd (M_PI));
}

static inline __m256d
min_4xf64 (__m256d x)
{
  return _mm256_min_pd (x, _mm256_set1_pd (M_PI));
}

#endif

#ifdef __AVX512F__

static inline void
efficiency_16xf32 (__m512 (*f) (__m512), long double (*g) (long double),
                   float xmin, float xmax, unsigned long int n, char *label)
{
  gsl_rng *rng;
  __m512 xv, yv;
  float *x, *y;
  long double em, e;
  float dx, t;
  clock_t t0;
  unsigned int i;
  n = (n / 16) * 16;
  rng = gsl_rng_alloc (gsl_rng_taus2);
  gsl_rng_set (rng, SEED);
  x = (float *) MALLOC (n * sizeof (float));
  y = (float *) MALLOC (n * sizeof (float));
  for (i = 0, dx = xmax - xmin; i < n; ++i)
    x[i] = xmin + dx * gsl_rng_uniform (rng);
  t0 = clock ();
  for (i = 0; i < n; i += 16)
    {
      xv = _mm512_load_ps (x + i);
      yv = f (xv);
      _mm512_store_ps (y + i, yv);
    }
  t = (clock () - t0) / (n * (float) CLOCKS_PER_SEC);
  for (i = 0, em = 0.L; i < n; ++i)
    {
      e = fabsl (y[i] - g (x[i]));
      if (e > em)
        em = e;
    }
  printf ("%s time=%g error=%Lg\n", label, t, em);
  FREE (y);
  FREE (x);
  gsl_rng_free (rng);
}

static inline void
efficiency_8xf64 (__m512d (*f) (__m512d), long double (*g) (long double),
                  double xmin, double xmax, unsigned long int n, char *label)
{
  gsl_rng *rng;
  __m512d xv, yv;
  double *x, *y;
  long double em, e;
  double dx, t;
  clock_t t0;
  unsigned int i;
  n = (n / 8) * 8;
  rng = gsl_rng_alloc (gsl_rng_taus2);
  gsl_rng_set (rng, SEED);
  x = (double *) MALLOC (n * sizeof (double));
  y = (double *) MALLOC (n * sizeof (double));
  for (i = 0, dx = xmax - xmin; i < n; ++i)
    x[i] = xmin + dx * gsl_rng_uniform (rng);
  t0 = clock ();
  for (i = 0; i < n; i += 8)
    {
      xv = _mm512_load_pd (x + i);
      yv = f (xv);
      _mm512_store_pd (y + i, yv);
    }
  t = (clock () - t0) / (n * (double) CLOCKS_PER_SEC);
  for (i = 0, em = 0.L; i < n; ++i)
    {
      e = fabsl (y[i] - g (x[i]));
      if (e > em)
        em = e;
    }
  printf ("%s time=%lg error=%Lg\n", label, t, em);
  FREE (y);
  FREE (x);
  gsl_rng_free (rng);
}

static inline __m512
add_16xf32 (__m512 x)
{
  return _mm512_add_ps (x, _mm512_set1_ps (M_PIf));
}

static inline __m512
sub_16xf32 (__m512 x)
{
  return _mm512_sub_ps (x, _mm512_set1_ps (M_PIf));
}

static inline __m512
mul_16xf32 (__m512 x)
{
  return _mm512_mul_ps (x, _mm512_set1_ps (M_PIf));
}

static inline __m512
div_16xf32 (__m512 x)
{
  return _mm512_div_ps (x, _mm512_set1_ps (M_PIf));
}

static inline __m512
sqrt_16xf32 (__m512 x)
{
  return _mm512_sqrt_ps (x);
}

static inline __m512
max_16xf32 (__m512 x)
{
  return _mm512_max_ps (x, _mm512_set1_ps (M_PIf));
}

static inline __m512
min_16xf32 (__m512 x)
{
  return _mm512_min_ps (x, _mm512_set1_ps (M_PIf));
}

static inline __m512d
add_8xf64 (__m512d x)
{
  return _mm512_add_pd (x, _mm512_set1_pd (M_PI));
}

static inline __m512d
sub_8xf64 (__m512d x)
{
  return _mm512_sub_pd (x, _mm512_set1_pd (M_PI));
}

static inline __m512d
mul_8xf64 (__m512d x)
{
  return _mm512_mul_pd (x, _mm512_set1_pd (M_PI));
}

static inline __m512d
div_8xf64 (__m512d x)
{
  return _mm512_div_pd (x, _mm512_set1_pd (M_PI));
}

static inline __m512d
sqrt_8xf64 (__m512d x)
{
  return _mm512_sqrt_pd (x);
}

static inline __m512d
max_8xf64 (__m512d x)
{
  return _mm512_max_pd (x, _mm512_set1_pd (M_PI));
}

static inline __m512d
min_8xf64 (__m512d x)
{
  return _mm512_min_pd (x, _mm512_set1_pd (M_PI));
}

#endif

int
main (int argn, char **argc)
{
  unsigned long int n;
  if (argn != 2)
    {
      printf ("The syntax is:\n./efficiency n\n");
      return 1;
    }
  n = (unsigned long int) atol (argc[1]);

  printf ("float functions\n");
  efficiency_f32 (add_f32, add_f80, -FLT_MAX, FLT_MAX, n, "add_f32");
  efficiency_f32 (sub_f32, sub_f80, -FLT_MAX, FLT_MAX, n, "sub_f32");
  efficiency_f32 (mul_f32, mul_f80, -FLT_MAX, FLT_MAX, n, "mul_f32");
  efficiency_f32 (div_f32, div_f80, -FLT_MAX, FLT_MAX, n, "div_f32");
  efficiency_f32 (sqrtf, sqrtl, 0.f, FLT_MAX, n, "sqrtf");
  efficiency_f32 (max_f32, max_f80, -FLT_MAX, FLT_MAX, n, "max_f32");
  efficiency_f32 (min_f32, min_f80, -FLT_MAX, FLT_MAX, n, "min_f32");
  efficiency_f32 (fabsf, fabsl, -FLT_MAX, FLT_MAX, n, "fabsf");
  efficiency_f32 (jbm_abs_f32, fabsl, -FLT_MAX, FLT_MAX, n, "jbm_abs_f32");
  efficiency_f32 (exp2f, exp2l, -FLT_MAX_EXP, FLT_MAX_EXP, n, "exp2f");
  efficiency_f32 (jbm_exp2_f32, exp2l, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                  "jbm_exp2_f32");
  efficiency_f32 (expf, expl, -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, n, "expf");
  efficiency_f32 (jbm_exp_f32, expl, -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, n,
                  "jbm_exp_f32");
  efficiency_f32 (exp10f, exp10l, -FLT_MAX_10_EXP, FLT_MAX_10_EXP, n, "exp10f");
  efficiency_f32 (jbm_exp10_f32, exp10l, -FLT_MAX_10_EXP, FLT_MAX_10_EXP, n,
                  "jbm_exp10_f32");
  efficiency_f32 (expm1f, expm1l, -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, n,
                  "expm1f");
  efficiency_f32 (jbm_expm1_f32, expm1l, -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP,
                  n, "jbm_expm1_f32");
  efficiency_f32 (cbrtf, cbrtl, -FLT_MAX, FLT_MAX, n, "cbrtf");
  efficiency_f32 (jbm_cbrt_f32, cbrtl, -FLT_MAX, FLT_MAX, n, "jbm_cbrt_f32");
  efficiency_f32 (log2f, log2l, FLT_MIN, FLT_MAX, n, "log2f");
  efficiency_f32 (jbm_log2_f32, log2l, FLT_MIN, FLT_MAX, n, "jbm_log2_f32");
  efficiency_f32 (logf, logl, FLT_MIN, FLT_MAX, n, "logf");
  efficiency_f32 (jbm_log_f32, logl, FLT_MIN, FLT_MAX, n, "jbm_log_f32");
  efficiency_f32 (log10f, log10l, FLT_MIN, FLT_MAX, n, "log10f");
  efficiency_f32 (jbm_log10_f32, log10l, FLT_MIN, FLT_MAX, n, "jbm_log10_f32");
  efficiency_f32 (sinf, sinl, -4.f * M_PIf, 4.f * M_PIf, n, "sinf");
  efficiency_f32 (jbm_sin_f32, sinl, -4.f * M_PIf, 4.f * M_PIf, n,
                  "jbm_sin_f32");
  efficiency_f32 (cosf, cosl, -4.f * M_PIf, 4.f * M_PIf, n, "cosf");
  efficiency_f32 (jbm_cos_f32, cosl, -4.f * M_PIf, 4.f * M_PIf, n,
                  "jbm_cos_f32");
  efficiency_f32 (tanf, tanl, -4.f * M_PIf, 4.f * M_PIf, n, "tanf");
  efficiency_f32 (jbm_tan_f32, tanl, -4.f * M_PIf, 4.f * M_PIf, n,
                  "jbm_tan_f32");
  efficiency_f32 (atanf, atanl, -FLT_MAX, FLT_MAX, n, "atanf");
  efficiency_f32 (jbm_atan_f32, atanl, -FLT_MAX, FLT_MAX, n, "jbm_atan_f32");
  efficiency_f32 (asinf, asinl, -1.f, 1.f, n, "asinf");
  efficiency_f32 (jbm_asin_f32, asinl, -1.f, 1.f, n, "jbm_asin_f32");
  efficiency_f32 (acosf, acosl, -1.f, 1.f, n, "acosf");
  efficiency_f32 (jbm_acos_f32, acosl, -1.f, 1.f, n, "jbm_acos_f32");
  efficiency_f32 (sinhf, sinhl, -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, n,
                  "sinhf");
  efficiency_f32 (jbm_sinh_f32, sinhl, -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, n,
                  "jbm_sinh_f32");
  efficiency_f32 (coshf, coshl, -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, n,
                  "coshf");
  efficiency_f32 (jbm_cosh_f32, coshl, -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, n,
                  "jbm_cosh_f32");
  efficiency_f32 (tanhf, tanhl, -FLT_MAX_EXP, FLT_MAX_EXP, n, "tanhf");
  efficiency_f32 (jbm_tanh_f32, tanhl, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                  "jbm_tanh_f32");
  efficiency_f32 (erff, erfl, -FLT_MAX_EXP, FLT_MAX_EXP, n, "erff");
  efficiency_f32 (jbm_erf_f32, erfl, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                  "jbm_erf_f32");
  efficiency_f32 (erfcf, erfcl, -FLT_MAX_EXP, FLT_MAX_EXP, n, "erfcf");
  efficiency_f32 (jbm_erfc_f32, erfcl, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                  "jbm_erfc_f32");

  printf ("double functions\n");
  efficiency_f64 (add_f64, add_f80, -DBL_MAX, DBL_MAX, n, "add_f64");
  efficiency_f64 (sub_f64, sub_f80, -DBL_MAX, DBL_MAX, n, "sub_f64");
  efficiency_f64 (mul_f64, mul_f80, -DBL_MAX, DBL_MAX, n, "mul_f64");
  efficiency_f64 (div_f64, div_f80, -DBL_MAX, DBL_MAX, n, "div_f64");
  efficiency_f64 (sqrt, sqrtl, 0., DBL_MAX, n, "sqrt");
  efficiency_f64 (max_f64, max_f80, -DBL_MAX, DBL_MAX, n, "max_f64");
  efficiency_f64 (min_f64, min_f80, -DBL_MAX, DBL_MAX, n, "min_f64");
  efficiency_f64 (fabs, fabsl, -DBL_MAX, DBL_MAX, n, "fabs");
  efficiency_f64 (jbm_abs_f64, fabsl, -DBL_MAX, DBL_MAX, n, "jbm_abs_f64");
  efficiency_f64 (exp2, exp2l, -DBL_MAX_EXP, DBL_MAX_EXP, n, "exp2");
  efficiency_f64 (jbm_exp2_f64, exp2l, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                  "jbm_exp2_f64");
  efficiency_f64 (exp, expl, -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, n, "exp");
  efficiency_f64 (jbm_exp_f64, expl, -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, n,
                  "jbm_exp_f64");
  efficiency_f64 (exp10, exp10l, -DBL_MAX_10_EXP, DBL_MAX_10_EXP, n, "exp10");
  efficiency_f64 (jbm_exp10_f64, exp10l, -DBL_MAX_10_EXP, DBL_MAX_10_EXP, n,
                  "jbm_exp10_f64");
  efficiency_f64 (expm1, expm1l, -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, n,
                  "expm1");
  efficiency_f64 (jbm_expm1_f64, expm1l, -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP,
                  n, "jbm_expm1_f64");
  efficiency_f64 (cbrt, cbrtl, -FLT_MAX, FLT_MAX, n, "cbrt");
  efficiency_f64 (jbm_cbrt_f64, cbrtl, -FLT_MAX, FLT_MAX, n, "jbm_cbrt_f64");
  efficiency_f64 (log2, log2l, DBL_MIN, DBL_MAX, n, "log2");
  efficiency_f64 (jbm_log2_f64, log2l, DBL_MIN, DBL_MAX, n, "jbm_log2_f64");
  efficiency_f64 (log, logl, DBL_MIN, DBL_MAX, n, "log");
  efficiency_f64 (jbm_log_f64, logl, DBL_MIN, DBL_MAX, n, "jbm_log_f64");
  efficiency_f64 (log10, log10l, DBL_MIN, DBL_MAX, n, "log10");
  efficiency_f64 (jbm_log10_f64, log10l, DBL_MIN, DBL_MAX, n, "jbm_log10_f64");
  efficiency_f64 (sin, sinl, -4. * M_PI, 4. * M_PI, n, "sin");
  efficiency_f64 (jbm_sin_f64, sinl, -4. * M_PI, 4. * M_PI, n, "jbm_sin_f64");
  efficiency_f64 (cos, cosl, -4. * M_PI, 4. * M_PI, n, "cos");
  efficiency_f64 (jbm_cos_f64, cosl, -4. * M_PI, 4. * M_PI, n, "jbm_cos_f64");
  efficiency_f64 (tan, tanl, -4. * M_PI, 4. * M_PI, n, "tan");
  efficiency_f64 (jbm_tan_f64, tanl, -4. * M_PI, 4. * M_PI, n, "jbm_tan_f64");
  efficiency_f64 (atan, atanl, -DBL_MAX, DBL_MAX, n, "atan");
  efficiency_f64 (jbm_atan_f64, atanl, -DBL_MAX, DBL_MAX, n, "jbm_atan_f64");
  efficiency_f64 (asin, asinl, -1., 1., n, "asin");
  efficiency_f64 (jbm_asin_f64, asinl, -1., 1., n, "jbm_asin_f64");
  efficiency_f64 (acos, acosl, -1., 1., n, "acos");
  efficiency_f64 (jbm_acos_f64, acosl, -1., 1., n, "jbm_acos_f64");
  efficiency_f64 (sinh, sinhl, -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, n,
                  "sinh");
  efficiency_f64 (jbm_sinh_f64, sinhl, -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, n,
                  "jbm_sinh_f64");
  efficiency_f64 (cosh, coshl, -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, n,
                  "cosh");
  efficiency_f64 (jbm_cosh_f64, coshl, -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, n,
                  "jbm_cosh_f64");
  efficiency_f64 (tanh, tanhl, -DBL_MAX_EXP, DBL_MAX_EXP, n, "tanh");
  efficiency_f64 (jbm_tanh_f64, tanhl, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                  "jbm_tanh_f64");
  efficiency_f64 (erf, erfl, -DBL_MAX_EXP, DBL_MAX_EXP, n, "erf");
  efficiency_f64 (jbm_erf_f64, erfl, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                  "jbm_erf_f64");
  efficiency_f64 (erfc, erfcl, -DBL_MAX_EXP, DBL_MAX_EXP, n, "erfc");
  efficiency_f64 (jbm_erfc_f64, erfcl, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                  "jbm_erfc_f64");

#ifdef __SSE4_2__

  printf ("__m128 functions\n");
  efficiency_4xf32 (add_4xf32, add_f80, -FLT_MAX, FLT_MAX, n, "add_4xf32");
  efficiency_4xf32 (sub_4xf32, sub_f80, -FLT_MAX, FLT_MAX, n, "sub_4xf32");
  efficiency_4xf32 (mul_4xf32, mul_f80, -FLT_MAX, FLT_MAX, n, "mul_4xf32");
  efficiency_4xf32 (div_4xf32, div_f80, -FLT_MAX, FLT_MAX, n, "div_4xf32");
  efficiency_4xf32 (sqrt_4xf32, sqrtl, 0.f, FLT_MAX, n, "sqrt_4xf32");
  efficiency_4xf32 (max_4xf32, max_f80, -FLT_MAX, FLT_MAX, n, "max_4xf32");
  efficiency_4xf32 (min_4xf32, min_f80, -FLT_MAX, FLT_MAX, n, "min_4xf32");
  efficiency_4xf32 (jbm_abs_4xf32, fabsl, -FLT_MAX, FLT_MAX, n,
                    "jbm_abs_4xf32");
  efficiency_4xf32 (jbm_exp2_4xf32, exp2l, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                    "jbm_exp2_4xf32");
  efficiency_4xf32 (jbm_exp_4xf32, expl, -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP,
                    n, "jbm_exp_4xf32");
  efficiency_4xf32 (jbm_exp10_4xf32, exp10l, -FLT_MAX_10_EXP, FLT_MAX_10_EXP, n,
                    "jbm_exp10_4xf32");
  efficiency_4xf32 (jbm_expm1_4xf32, expm1l, -JBM_FLT_MAX_E_EXP,
                    JBM_FLT_MAX_E_EXP, n, "jbm_expm1_4xf32");
  efficiency_4xf32 (jbm_cbrt_4xf32, cbrtl, -FLT_MAX, FLT_MAX, n,
                    "jbm_cbrt_4xf32");
  efficiency_4xf32 (jbm_log2_4xf32, log2l, FLT_MIN, FLT_MAX, n,
                    "jbm_log2_4xf32");
  efficiency_4xf32 (jbm_log_4xf32, logl, FLT_MIN, FLT_MAX, n, "jbm_log_4xf32");
  efficiency_4xf32 (jbm_log10_4xf32, log10l, FLT_MIN, FLT_MAX, n,
                    "jbm_log10_4xf32");
  efficiency_4xf32 (jbm_sin_4xf32, sinl, -4.f * M_PIf, 4.f * M_PIf, n,
                    "jbm_sin_4xf32");
  efficiency_4xf32 (jbm_cos_4xf32, cosl, -4.f * M_PIf, 4.f * M_PIf, n,
                    "jbm_cos_4xf32");
  efficiency_4xf32 (jbm_tan_4xf32, tanl, -4.f * M_PIf, 4.f * M_PIf, n,
                    "jbm_tan_4xf32");
  efficiency_4xf32 (jbm_atan_4xf32, atanl, -FLT_MAX, FLT_MAX, n,
                    "jbm_atan_4xf32");
  efficiency_4xf32 (jbm_asin_4xf32, asinl, -1.f, 1.f, n, "jbm_asin_4xf32");
  efficiency_4xf32 (jbm_acos_4xf32, acosl, -1.f, 1.f, n, "jbm_acos_4xf32");
  efficiency_4xf32 (jbm_sinh_4xf32, sinhl,
                    -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, n, "jbm_sinh_4xf32");
  efficiency_4xf32 (jbm_cosh_4xf32, coshl,
                    -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, n, "jbm_cosh_4xf32");
  efficiency_4xf32 (jbm_tanh_4xf32, tanhl, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                    "jbm_tanh_4xf32");
  efficiency_4xf32 (jbm_erf_4xf32, erfl, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                    "jbm_erf_4xf32");
  efficiency_4xf32 (jbm_erfc_4xf32, erfcl, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                    "jbm_erfc_4xf32");

  printf ("__m128d functions\n");
  efficiency_2xf64 (add_2xf64, add_f80, -DBL_MAX, DBL_MAX, n, "add_2xf64");
  efficiency_2xf64 (sub_2xf64, sub_f80, -DBL_MAX, DBL_MAX, n, "sub_2xf64");
  efficiency_2xf64 (mul_2xf64, mul_f80, -DBL_MAX, DBL_MAX, n, "mul_2xf64");
  efficiency_2xf64 (div_2xf64, div_f80, -DBL_MAX, DBL_MAX, n, "div_2xf64");
  efficiency_2xf64 (sqrt_2xf64, sqrtl, 0., DBL_MAX, n, "sqrt_2xf64");
  efficiency_2xf64 (max_2xf64, max_f80, -DBL_MAX, DBL_MAX, n, "max_2xf64");
  efficiency_2xf64 (min_2xf64, min_f80, -DBL_MAX, DBL_MAX, n, "min_2xf64");
  efficiency_2xf64 (jbm_abs_2xf64, fabsl, -DBL_MAX, DBL_MAX, n,
                    "jbm_abs_2xf64");
  efficiency_2xf64 (jbm_exp2_2xf64, exp2l, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                    "jbm_exp2_2xf64");
  efficiency_2xf64 (jbm_exp_2xf64, expl, -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP,
                    n, "jbm_exp_2xf64");
  efficiency_2xf64 (jbm_exp10_2xf64, exp10l, -DBL_MAX_10_EXP, DBL_MAX_10_EXP, n,
                    "jbm_exp10_2xf64");
  efficiency_2xf64 (jbm_expm1_2xf64, expm1l, -JBM_DBL_MAX_E_EXP,
                    JBM_DBL_MAX_E_EXP, n, "jbm_expm1_2xf64");
  efficiency_2xf64 (jbm_cbrt_2xf64, cbrtl, -DBL_MAX, DBL_MAX, n,
                    "jbm_cbrt_2xf64");
  efficiency_2xf64 (jbm_log2_2xf64, log2l, DBL_MIN, DBL_MAX, n,
                    "jbm_log2_2xf64");
  efficiency_2xf64 (jbm_log_2xf64, logl, DBL_MIN, DBL_MAX, n, "jbm_log_2xf64");
  efficiency_2xf64 (jbm_log10_2xf64, log10l, DBL_MIN, DBL_MAX, n,
                    "jbm_log10_2xf64");
  efficiency_2xf64 (jbm_sin_2xf64, sinl, -4. * M_PI, 4. * M_PI, n,
                    "jbm_sin_2xf64");
  efficiency_2xf64 (jbm_cos_2xf64, cosl, -4. * M_PI, 4. * M_PI, n,
                    "jbm_cos_2xf64");
  efficiency_2xf64 (jbm_tan_2xf64, tanl, -4. * M_PI, 4. * M_PI, n,
                    "jbm_tan_2xf64");
  efficiency_2xf64 (jbm_atan_2xf64, atanl, -DBL_MAX, DBL_MAX, n,
                    "jbm_atan_2xf64");
  efficiency_2xf64 (jbm_asin_2xf64, asinl, -1., 1., n, "jbm_asin_2xf64");
  efficiency_2xf64 (jbm_acos_2xf64, acosl, -1., 1., n, "jbm_acos_2xf64");
  efficiency_2xf64 (jbm_sinh_2xf64, sinhl,
                    -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, n, "jbm_sinh_2xf64");
  efficiency_2xf64 (jbm_cosh_2xf64, coshl,
                    -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, n, "jbm_cosh_2xf64");
  efficiency_2xf64 (jbm_tanh_2xf64, tanhl, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                    "jbm_tanh_2xf64");
  efficiency_2xf64 (jbm_erf_2xf64, erfl, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                    "jbm_erf_2xf64");
  efficiency_2xf64 (jbm_erfc_2xf64, erfcl, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                    "jbm_erfc_2xf64");

#endif

#ifdef __AVX__

  printf ("__m256 functions\n");
  efficiency_8xf32 (add_8xf32, add_f80, -FLT_MAX, FLT_MAX, n, "add_8xf32");
  efficiency_8xf32 (sub_8xf32, sub_f80, -FLT_MAX, FLT_MAX, n, "sub_8xf32");
  efficiency_8xf32 (mul_8xf32, mul_f80, -FLT_MAX, FLT_MAX, n, "mul_8xf32");
  efficiency_8xf32 (div_8xf32, div_f80, -FLT_MAX, FLT_MAX, n, "div_8xf32");
  efficiency_8xf32 (sqrt_8xf32, sqrtl, 0.f, FLT_MAX, n, "sqrt_8xf32");
  efficiency_8xf32 (max_8xf32, max_f80, -FLT_MAX, FLT_MAX, n, "max_8xf32");
  efficiency_8xf32 (min_8xf32, min_f80, -FLT_MAX, FLT_MAX, n, "min_8xf32");
  efficiency_8xf32 (jbm_abs_8xf32, fabsl, -FLT_MAX, FLT_MAX, n,
                    "jbm_abs_8xf32");
  efficiency_8xf32 (jbm_exp2_8xf32, exp2l, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                    "jbm_exp2_8xf32");
  efficiency_8xf32 (jbm_exp_8xf32, expl, -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP,
                    n, "jbm_exp_8xf32");
  efficiency_8xf32 (jbm_exp10_8xf32, exp10l, -FLT_MAX_10_EXP, FLT_MAX_10_EXP, n,
                    "jbm_exp10_8xf32");
  efficiency_8xf32 (jbm_expm1_8xf32, expm1l, -JBM_FLT_MAX_E_EXP,
                    JBM_FLT_MAX_E_EXP, n, "jbm_expm1_8xf32");
  efficiency_8xf32 (jbm_cbrt_8xf32, cbrtl, -FLT_MAX, FLT_MAX, n,
                    "jbm_cbrt_8xf32");
  efficiency_8xf32 (jbm_log2_8xf32, log2l, FLT_MIN, FLT_MAX, n,
                    "jbm_log2_8xf32");
  efficiency_8xf32 (jbm_log_8xf32, logl, FLT_MIN, FLT_MAX, n, "jbm_log_8xf32");
  efficiency_8xf32 (jbm_log10_8xf32, log10l, FLT_MIN, FLT_MAX, n,
                    "jbm_log10_8xf32");
  efficiency_8xf32 (jbm_sin_8xf32, sinl, -4.f * M_PIf, 4.f * M_PIf, n,
                    "jbm_sin_8xf32");
  efficiency_8xf32 (jbm_cos_8xf32, cosl, -4.f * M_PIf, 4.f * M_PIf, n,
                    "jbm_cos_8xf32");
  efficiency_8xf32 (jbm_tan_8xf32, tanl, -4.f * M_PIf, 4.f * M_PIf, n,
                    "jbm_tan_8xf32");
  efficiency_8xf32 (jbm_atan_8xf32, atanl, -FLT_MAX, FLT_MAX, n,
                    "jbm_atan_8xf32");
  efficiency_8xf32 (jbm_asin_8xf32, asinl, -1.f, 1.f, n, "jbm_asin_8xf32");
  efficiency_8xf32 (jbm_acos_8xf32, acosl, -1.f, 1.f, n, "jbm_acos_8xf32");
  efficiency_8xf32 (jbm_sinh_8xf32, sinhl,
                    -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, n, "jbm_sinh_8xf32");
  efficiency_8xf32 (jbm_cosh_8xf32, coshl,
                    -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, n, "jbm_cosh_8xf32");
  efficiency_8xf32 (jbm_tanh_8xf32, tanhl, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                    "jbm_tanh_8xf32");
  efficiency_8xf32 (jbm_erf_8xf32, erfl, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                    "jbm_erf_8xf32");
  efficiency_8xf32 (jbm_erfc_8xf32, erfcl, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                    "jbm_erfc_8xf32");

  printf ("__m256d functions\n");
  efficiency_4xf64 (add_4xf64, add_f80, -DBL_MAX, DBL_MAX, n, "add_4xf64");
  efficiency_4xf64 (sub_4xf64, sub_f80, -DBL_MAX, DBL_MAX, n, "sub_4xf64");
  efficiency_4xf64 (mul_4xf64, mul_f80, -DBL_MAX, DBL_MAX, n, "mul_4xf64");
  efficiency_4xf64 (div_4xf64, div_f80, -DBL_MAX, DBL_MAX, n, "div_4xf64");
  efficiency_4xf64 (sqrt_4xf64, sqrtl, 0., DBL_MAX, n, "sqrt_4xf64");
  efficiency_4xf64 (max_4xf64, max_f80, -DBL_MAX, DBL_MAX, n, "max_4xf64");
  efficiency_4xf64 (min_4xf64, min_f80, -DBL_MAX, DBL_MAX, n, "min_4xf64");
  efficiency_4xf64 (jbm_abs_4xf64, fabsl, -DBL_MAX, DBL_MAX, n,
                    "jbm_abs_4xf64");
  efficiency_4xf64 (jbm_exp2_4xf64, exp2l, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                    "jbm_exp2_4xf64");
  efficiency_4xf64 (jbm_exp_4xf64, expl, -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP,
                    n, "jbm_exp_4xf64");
  efficiency_4xf64 (jbm_exp10_4xf64, exp10l, -DBL_MAX_10_EXP, DBL_MAX_10_EXP, n,
                    "jbm_exp10_4xf64");
  efficiency_4xf64 (jbm_expm1_4xf64, expm1l, -JBM_DBL_MAX_E_EXP,
                    JBM_DBL_MAX_E_EXP, n, "jbm_expm1_4xf64");
  efficiency_4xf64 (jbm_cbrt_4xf64, cbrtl, -DBL_MAX, DBL_MAX, n,
                    "jbm_cbrt_4xf64");
  efficiency_4xf64 (jbm_log2_4xf64, log2l, DBL_MIN, DBL_MAX, n,
                    "jbm_log2_4xf64");
  efficiency_4xf64 (jbm_log_4xf64, logl, DBL_MIN, DBL_MAX, n, "jbm_log_4xf64");
  efficiency_4xf64 (jbm_log10_4xf64, log10l, DBL_MIN, DBL_MAX, n,
                    "jbm_log10_4xf64");
  efficiency_4xf64 (jbm_sin_4xf64, sinl, -4. * M_PI, 4. * M_PI, n,
                    "jbm_sin_4xf64");
  efficiency_4xf64 (jbm_cos_4xf64, cosl, -4. * M_PI, 4. * M_PI, n,
                    "jbm_cos_4xf64");
  efficiency_4xf64 (jbm_tan_4xf64, tanl, -4. * M_PI, 4. * M_PI, n,
                    "jbm_tan_4xf64");
  efficiency_4xf64 (jbm_atan_4xf64, atanl, -DBL_MAX, DBL_MAX, n,
                    "jbm_atan_4xf64");
  efficiency_4xf64 (jbm_asin_4xf64, asinl, -1., 1., n, "jbm_asin_4xf64");
  efficiency_4xf64 (jbm_acos_4xf64, acosl, -1., 1., n, "jbm_acos_4xf64");
  efficiency_4xf64 (jbm_sinh_4xf64, sinhl,
                    -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, n, "jbm_sinh_4xf64");
  efficiency_4xf64 (jbm_cosh_4xf64, coshl,
                    -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, n, "jbm_cosh_4xf64");
  efficiency_4xf64 (jbm_tanh_4xf64, tanhl, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                    "jbm_tanh_4xf64");
  efficiency_4xf64 (jbm_erf_4xf64, erfl, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                    "jbm_erf_4xf64");
  efficiency_4xf64 (jbm_erfc_4xf64, erfcl, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                    "jbm_erfc_4xf64");

#endif

#ifdef __AVX512F__

  printf ("__m512 functions\n");
  efficiency_16xf32 (add_16xf32, add_f80, -FLT_MAX, FLT_MAX, n, "add_16xf32");
  efficiency_16xf32 (sub_16xf32, sub_f80, -FLT_MAX, FLT_MAX, n, "sub_16xf32");
  efficiency_16xf32 (mul_16xf32, mul_f80, -FLT_MAX, FLT_MAX, n, "mul_16xf32");
  efficiency_16xf32 (div_16xf32, div_f80, -FLT_MAX, FLT_MAX, n, "div_16xf32");
  efficiency_16xf32 (sqrt_16xf32, sqrtl, 0.f, FLT_MAX, n, "sqrt_16xf32");
  efficiency_16xf32 (max_16xf32, max_f80, -FLT_MAX, FLT_MAX, n, "max_16xf32");
  efficiency_16xf32 (min_16xf32, min_f80, -FLT_MAX, FLT_MAX, n, "min_16xf32");
  efficiency_16xf32 (jbm_abs_16xf32, fabsl, -FLT_MAX, FLT_MAX, n,
                     "jbm_abs_16xf32");
  efficiency_16xf32 (jbm_exp2_16xf32, exp2l, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                     "jbm_exp2_16xf32");
  efficiency_16xf32 (jbm_exp_16xf32, expl,
                     -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP,
                     n, "jbm_exp_16xf32");
  efficiency_16xf32 (jbm_exp10_16xf32, exp10l, -FLT_MAX_10_EXP, FLT_MAX_10_EXP,
                     n, "jbm_exp10_16xf32");
  efficiency_16xf32 (jbm_expm1_16xf32, expm1l, -JBM_FLT_MAX_E_EXP,
                     JBM_FLT_MAX_E_EXP, n, "jbm_expm1_16xf32");
  efficiency_16xf32 (jbm_cbrt_16xf32, cbrtl, -FLT_MAX, FLT_MAX, n,
                     "jbm_cbrt_16xf32");
  efficiency_16xf32 (jbm_log2_16xf32, log2l, FLT_MIN, FLT_MAX, n,
                     "jbm_log2_16xf32");
  efficiency_16xf32 (jbm_log_16xf32, logl, FLT_MIN, FLT_MAX, n,
                     "jbm_log_16xf32");
  efficiency_16xf32 (jbm_log10_16xf32, log10l, FLT_MIN, FLT_MAX, n,
                     "jbm_log10_16xf32");
  efficiency_16xf32 (jbm_sin_16xf32, sinl, -4.f * M_PIf, 4.f * M_PIf, n,
                     "jbm_sin_16xf32");
  efficiency_16xf32 (jbm_cos_16xf32, cosl, -4.f * M_PIf, 4.f * M_PIf, n,
                     "jbm_cos_16xf32");
  efficiency_16xf32 (jbm_tan_16xf32, tanl, -4.f * M_PIf, 4.f * M_PIf, n,
                     "jbm_tan_16xf32");
  efficiency_16xf32 (jbm_atan_16xf32, atanl, -FLT_MAX, FLT_MAX, n,
                     "jbm_atan_16xf32");
  efficiency_16xf32 (jbm_asin_16xf32, asinl, -1.f, 1.f, n, "jbm_asin_16xf32");
  efficiency_16xf32 (jbm_acos_16xf32, acosl, -1.f, 1.f, n, "jbm_acos_16xf32");
  efficiency_16xf32 (jbm_sinh_16xf32, sinhl,
                     -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, n,
                     "jbm_sinh_16xf32");
  efficiency_16xf32 (jbm_cosh_16xf32, coshl, -JBM_FLT_MAX_E_EXP,
                     JBM_FLT_MAX_E_EXP, n, "jbm_cosh_16xf32");
  efficiency_16xf32 (jbm_tanh_16xf32, tanhl, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                     "jbm_tanh_16xf32");
  efficiency_16xf32 (jbm_erf_16xf32, erfl, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                     "jbm_erf_16xf32");
  efficiency_16xf32 (jbm_erfc_16xf32, erfcl, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                     "jbm_erfc_16xf32");

  printf ("__m512d functions\n");
  efficiency_8xf64 (add_8xf64, add_f80, -DBL_MAX, DBL_MAX, n, "add_8xf64");
  efficiency_8xf64 (sub_8xf64, sub_f80, -DBL_MAX, DBL_MAX, n, "sub_8xf64");
  efficiency_8xf64 (mul_8xf64, mul_f80, -DBL_MAX, DBL_MAX, n, "mul_8xf64");
  efficiency_8xf64 (div_8xf64, div_f80, -DBL_MAX, DBL_MAX, n, "div_8xf64");
  efficiency_8xf64 (sqrt_8xf64, sqrtl, 0., DBL_MAX, n, "sqrt_8xf64");
  efficiency_8xf64 (max_8xf64, max_f80, -DBL_MAX, DBL_MAX, n, "max_8xf64");
  efficiency_8xf64 (min_8xf64, min_f80, -DBL_MAX, DBL_MAX, n, "min_8xf64");
  efficiency_8xf64 (jbm_abs_8xf64, fabsl, -DBL_MAX, DBL_MAX, n,
                    "jbm_abs_8xf64");
  efficiency_8xf64 (jbm_exp2_8xf64, exp2l, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                    "jbm_exp2_8xf64");
  efficiency_8xf64 (jbm_exp_8xf64, expl, -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP,
                    n, "jbm_exp_8xf64");
  efficiency_8xf64 (jbm_exp10_8xf64, exp10l, -DBL_MAX_10_EXP, DBL_MAX_10_EXP, n,
                    "jbm_exp10_8xf64");
  efficiency_8xf64 (jbm_expm1_8xf64, expm1l, -JBM_DBL_MAX_E_EXP,
                    JBM_DBL_MAX_E_EXP, n, "jbm_expm1_8xf64");
  efficiency_8xf64 (jbm_cbrt_8xf64, cbrtl, -DBL_MAX, DBL_MAX, n,
                    "jbm_cbrt_8xf64");
  efficiency_8xf64 (jbm_log2_8xf64, log2l, DBL_MIN, DBL_MAX, n,
                    "jbm_log2_8xf64");
  efficiency_8xf64 (jbm_log_8xf64, logl, DBL_MIN, DBL_MAX, n, "jbm_log_8xf64");
  efficiency_8xf64 (jbm_log10_8xf64, log10l, DBL_MIN, DBL_MAX, n,
                    "jbm_log10_8xf64");
  efficiency_8xf64 (jbm_sin_8xf64, sinl, -4. * M_PI, 4. * M_PI, n,
                    "jbm_sin_8xf64");
  efficiency_8xf64 (jbm_cos_8xf64, cosl, -4. * M_PI, 4. * M_PI, n,
                    "jbm_cos_8xf64");
  efficiency_8xf64 (jbm_tan_8xf64, tanl, -4. * M_PI, 4. * M_PI, n,
                    "jbm_tan_8xf64");
  efficiency_8xf64 (jbm_atan_8xf64, atanl, -DBL_MAX, DBL_MAX, n,
                    "jbm_atan_8xf64");
  efficiency_8xf64 (jbm_asin_8xf64, asinl, -1., 1., n, "jbm_asin_8xf64");
  efficiency_8xf64 (jbm_acos_8xf64, acosl, -1., 1., n, "jbm_acos_8xf64");
  efficiency_8xf64 (jbm_sinh_8xf64, sinhl,
                    -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, n, "jbm_sinh_8xf64");
  efficiency_8xf64 (jbm_cosh_8xf64, coshl,
                    -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, n, "jbm_cosh_8xf64");
  efficiency_8xf64 (jbm_tanh_8xf64, tanhl, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                    "jbm_tanh_8xf64");
  efficiency_8xf64 (jbm_erf_8xf64, erfl, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                    "jbm_erf_8xf64");
  efficiency_8xf64 (jbm_erfc_8xf64, erfcl, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                    "jbm_erfc_8xf64");

#endif

  return 0;
}
