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
  float dx;
  clock_t t0, t;
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
  t = clock ();
  for (i = 0, em = 0.L; i < n; ++i)
    {
      e = fabsl (y[i] - g (x[i]));
      if (e > em)
        em = e;
    }
  printf ("%s time=%lg error=%Lg\n",
          label, (t - t0) / (((double) n) * CLOCKS_PER_SEC), em);
  gsl_rng_free (rng);
}

static inline void
efficiency_f64 (double (*f) (double), long double (*g) (long double),
                double xmin, double xmax, unsigned long int n, char *label)
{
  gsl_rng *rng;
  double *x, *y;
  long double em, e;
  double dx;
  clock_t t0, t;
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
  t = clock ();
  for (i = 0, em = 0.L; i < n; ++i)
    {
      e = fabsl (y[i] - g (x[i]));
      if (e > em)
        em = e;
    }
  printf ("%s time=%lg error=%Lg\n",
          label, (t - t0) / (((double) n) * CLOCKS_PER_SEC), em);
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
  efficiency_f32 (add_f32, add_f80, -FLT_MAX, FLT_MAX, n, "add_f32");
  efficiency_f64 (add_f64, add_f80, -DBL_MAX, DBL_MAX, n, "add_f64");
  efficiency_f32 (sub_f32, sub_f80, -FLT_MAX, FLT_MAX, n, "sub_f32");
  efficiency_f64 (sub_f64, sub_f80, -DBL_MAX, DBL_MAX, n, "sub_f64");
  efficiency_f32 (mul_f32, mul_f80, -FLT_MAX, FLT_MAX, n, "mul_f32");
  efficiency_f64 (mul_f64, mul_f80, -DBL_MAX, DBL_MAX, n, "mul_f64");
  efficiency_f32 (div_f32, div_f80, -FLT_MAX, FLT_MAX, n, "div_f32");
  efficiency_f64 (div_f64, div_f80, -DBL_MAX, DBL_MAX, n, "div_f64");
  efficiency_f32 (fabsf, fabsl, -FLT_MAX, FLT_MAX, n, "fabsf");
  efficiency_f32 (jbm_abs_f32, fabsl, -FLT_MAX, FLT_MAX, n, "jbm_abs_f32");
  efficiency_f64 (fabs, fabsl, -DBL_MAX, DBL_MAX, n, "fabs");
  efficiency_f64 (jbm_abs_f64, fabsl, -DBL_MAX, DBL_MAX, n, "jbm_abs_f64");
  efficiency_f32 (sqrtf, sqrtl, 0.f, FLT_MAX, n, "sqrtf");
  efficiency_f64 (sqrt, sqrtl, 0., DBL_MAX, n, "sqrt");
  efficiency_f32 (exp2f, exp2l, -FLT_MAX_EXP, FLT_MAX_EXP, n, "exp2f");
  efficiency_f32 (jbm_exp2_f32, exp2l, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                  "jbm_exp2_f32");
  efficiency_f64 (exp2, exp2l, -DBL_MAX_EXP, DBL_MAX_EXP, n, "exp2");
  efficiency_f64 (jbm_exp2_f64, exp2l, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                  "jbm_exp2_f64");
  efficiency_f32 (expf, expl, -FLT_MAX_EXP, FLT_MAX_EXP, n, "expf");
  efficiency_f32 (jbm_exp_f32, expl, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                  "jbm_exp_f32");
  efficiency_f64 (exp, expl, -DBL_MAX_EXP, DBL_MAX_EXP, n, "exp");
  efficiency_f64 (jbm_exp_f64, expl, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                  "jbm_exp_f64");
  efficiency_f32 (exp10f, exp10l, -FLT_MAX_10_EXP, FLT_MAX_10_EXP, n, "exp10f");
  efficiency_f32 (jbm_exp10_f32, exp10l, -FLT_MAX_10_EXP, FLT_MAX_10_EXP, n,
                  "jbm_exp10_f32");
  efficiency_f64 (exp10, exp10l, -DBL_MAX_10_EXP, DBL_MAX_10_EXP, n, "exp10");
  efficiency_f64 (jbm_exp10_f64, exp10l, -DBL_MAX_10_EXP, DBL_MAX_10_EXP, n,
                  "jbm_exp10_f64");
  efficiency_f32 (expm1f, expm1l, -FLT_MAX_EXP, FLT_MAX_EXP, n, "expm1f");
  efficiency_f32 (jbm_expm1_f32, expm1l, -FLT_MAX_EXP, FLT_MAX_EXP, n,
                  "jbm_expm1_f32");
  efficiency_f64 (expm1, expm1l, -DBL_MAX_EXP, DBL_MAX_EXP, n, "expm1");
  efficiency_f64 (jbm_expm1_f64, expm1l, -DBL_MAX_EXP, DBL_MAX_EXP, n,
                  "jbm_expm1_f64");
  efficiency_f32 (log2f, log2l, FLT_MIN, FLT_MAX, n, "log2f");
  efficiency_f32 (jbm_log2_f32, log2l, FLT_MIN, FLT_MAX, n, "jbm_log2_f32");
  efficiency_f64 (log2, log2l, DBL_MIN, DBL_MAX, n, "log2");
  efficiency_f64 (jbm_log2_f64, log2l, DBL_MIN, DBL_MAX, n, "jbm_log2_f64");
  efficiency_f32 (logf, logl, FLT_MIN, FLT_MAX, n, "logf");
  efficiency_f32 (jbm_log_f32, logl, FLT_MIN, FLT_MAX, n, "jbm_log_f32");
  efficiency_f64 (log, logl, DBL_MIN, DBL_MAX, n, "log");
  efficiency_f64 (jbm_log_f64, logl, DBL_MIN, DBL_MAX, n, "jbm_log_f64");
  efficiency_f32 (log10f, log10l, FLT_MIN, FLT_MAX, n, "log10f");
  efficiency_f32 (jbm_log10_f32, log10l, FLT_MIN, FLT_MAX, n, "jbm_log10_f32");
  efficiency_f64 (log10, log10l, DBL_MIN, DBL_MAX, n, "log10");
  efficiency_f64 (jbm_log10_f64, log10l, DBL_MIN, DBL_MAX, n, "jbm_log10_f64");
  efficiency_f32 (sinf, sinl, -4.f * M_PIf, 4.f * M_PIf, n, "sinf");
  efficiency_f32 (jbm_sin_f32, sinl, -4.f * M_PIf, 4.f * M_PIf, n,
                  "jbm_sin_f32");
  efficiency_f64 (sin, sinl, -4. * M_PI, 4. * M_PI, n, "sin");
  efficiency_f64 (jbm_sin_f64, sinl, -4. * M_PI, 4. * M_PI, n, "jbm_sin_f64");
  efficiency_f32 (cosf, cosl, -4.f * M_PIf, 4.f * M_PIf, n, "cosf");
  efficiency_f32 (jbm_cos_f32, cosl, -4.f * M_PIf, 4.f * M_PIf, n,
                  "jbm_cos_f32");
  efficiency_f64 (cos, cosl, -4. * M_PI, 4. * M_PI, n, "cos");
  efficiency_f64 (jbm_cos_f64, cosl, -4. * M_PI, 4. * M_PI, n, "jbm_cos_f64");
  efficiency_f32 (tanf, tanl, -4.f * M_PIf, 4.f * M_PIf, n, "tanf");
  efficiency_f32 (jbm_tan_f32, tanl, -4.f * M_PIf, 4.f * M_PIf, n,
                  "jbm_tan_f32");
  efficiency_f64 (tan, tanl, -4. * M_PI, 4. * M_PI, n, "tan");
  efficiency_f64 (jbm_tan_f64, tanl, -4. * M_PI, 4. * M_PI, n, "jbm_tan_f64");
  efficiency_f32 (atanf, atanl, -FLT_MAX, FLT_MAX, n, "atanf");
  efficiency_f32 (jbm_atan_f32, atanl, -FLT_MAX, FLT_MAX, n, "jbm_atan_f32");
  efficiency_f64 (atan, atanl, -DBL_MAX, DBL_MAX, n, "atan");
  efficiency_f64 (jbm_atan_f64, atanl, -DBL_MAX, DBL_MAX, n, "jbm_atan_f64");
  efficiency_f32 (asinf, asinl, -1.f, 1.f, n, "asinf");
  efficiency_f32 (jbm_asin_f32, asinl, -1.f, 1.f, n, "jbm_asin_f32");
  efficiency_f64 (asin, asinl, -1., 1., n, "asin");
  efficiency_f64 (jbm_asin_f64, asinl, -1., 1., n, "jbm_asin_f64");
  efficiency_f32 (acosf, acosl, -1.f, 1.f, n, "acosf");
  efficiency_f32 (jbm_acos_f32, acosl, -1.f, 1.f, n, "jbm_acos_f32");
  efficiency_f64 (acos, acosl, -1., 1., n, "acos");
  efficiency_f64 (jbm_acos_f64, acosl, -1., 1., n, "jbm_acos_f64");
  efficiency_f32 (sinhf, sinhl, -FLT_MAX_EXP, FLT_MAX_EXP, n, "sinhf");
  efficiency_f32 (jbm_sinh_f32, sinhl, -FLT_MAX_EXP, FLT_MAX_EXP, n,
		  "jbm_sinh_f32");
  efficiency_f64 (sinh, sinhl, -DBL_MAX_EXP, DBL_MAX_EXP, n, "sinh");
  efficiency_f64 (jbm_sinh_f64, sinhl, -DBL_MAX_EXP, DBL_MAX_EXP, n,
		  "jbm_sinh_f64");
  efficiency_f32 (coshf, coshl, -FLT_MAX_EXP, FLT_MAX_EXP, n, "coshf");
  efficiency_f32 (jbm_cosh_f32, coshl, -FLT_MAX_EXP, FLT_MAX_EXP, n,
		  "jbm_cosh_f32");
  efficiency_f64 (cosh, coshl, -DBL_MAX_EXP, DBL_MAX_EXP, n, "cosh");
  efficiency_f64 (jbm_cosh_f64, coshl, -DBL_MAX_EXP, DBL_MAX_EXP, n,
		  "jbm_cosh_f64");
  efficiency_f32 (tanhf, tanhl, -FLT_MAX_EXP, FLT_MAX_EXP, n, "tanhf");
  efficiency_f32 (jbm_tanh_f32, tanhl, -FLT_MAX_EXP, FLT_MAX_EXP, n,
		  "jbm_tanh_f32");
  efficiency_f64 (tanh, tanhl, -DBL_MAX_EXP, DBL_MAX_EXP, n, "tanh");
  efficiency_f64 (jbm_tanh_f64, tanhl, -DBL_MAX_EXP, DBL_MAX_EXP, n,
		  "jbm_tanh_f64");
  return 0;
}
