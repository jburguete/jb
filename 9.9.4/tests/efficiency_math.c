#include "../src/math.h"
#include <gsl/gsl_rng.h>

#define SEED 7l
#define N 100000

void
efficiency_f32 (float (*f)(float), float xmin, float xmax, unsigned long int n,
                char *label)
{
  gsl_rng *rng;
  float *x, *y;
  float z, dx;
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
  for (i = 0, z = 0., dx = 1.; i < n; ++i, dx = -dx)
    z += dx * y[i];
  printf ("%s time=%lg sum=%g\n",
          label, (t - t0) / (((double) n) * CLOCKS_PER_SEC), z);
  gsl_rng_free (rng);
}

void
efficiency_f64 (double (*f)(double), double xmin, double xmax,
                unsigned long int n, char *label)
{
  gsl_rng *rng;
  double *x, *y;
  double z, dx;
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
  for (i = 0, z = 0., dx = 1.; i < n; ++i, dx = -dx)
    z += dx * y[i];
  printf ("%s time=%lg sum=%lg\n",
          label, (t - t0) / (((double) n) * CLOCKS_PER_SEC), z);
  gsl_rng_free (rng);
}

float
add_f32 (float x)
{
  return x + M_PIf;
}

float
sub_f32 (float x)
{
  return x - M_PIf;
}

float
mul_f32 (float x)
{
  return x * M_PIf;
}

float
div_f32 (float x)
{
  return x / M_PIf;
}

double
add_f64 (double x)
{
  return x + M_PI;
}

double
sub_f64 (double x)
{
  return x - M_PI;
}

double
mul_f64 (double x)
{
  return x * M_PI;
}

double
div_f64 (double x)
{
  return x / M_PI;
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
  efficiency_f32 (sqrtf, 0.f, FLT_MAX, n, "sqrtf");
  efficiency_f64 (sqrt, 0., DBL_MAX, n, "sqrt");
  efficiency_f32 (add_f32, -FLT_MAX, FLT_MAX, n, "add_f32");
  efficiency_f64 (add_f64, -DBL_MAX, DBL_MAX, n, "add_f64");
  efficiency_f32 (sub_f32, -FLT_MAX, FLT_MAX, n, "sub_f32");
  efficiency_f64 (sub_f64, -DBL_MAX, DBL_MAX, n, "sub_f64");
  efficiency_f32 (mul_f32, -FLT_MAX, FLT_MAX, n, "mul_f32");
  efficiency_f64 (mul_f64, -DBL_MAX, DBL_MAX, n, "mul_f64");
  efficiency_f32 (div_f32, -FLT_MAX, FLT_MAX, n, "div_f32");
  efficiency_f64 (div_f64, -DBL_MAX, DBL_MAX, n, "div_f64");
  efficiency_f32 (exp2f, -FLT_MAX_EXP, FLT_MAX_EXP, n, "exp2f");
  efficiency_f32 (jbm_exp2_f32, -FLT_MAX_EXP, FLT_MAX_EXP, n, "jbm_exp2_f32");
  efficiency_f64 (exp2, -DBL_MAX_EXP, DBL_MAX_EXP, n, "exp2");
  efficiency_f64 (jbm_exp2_f64, -DBL_MAX_EXP, DBL_MAX_EXP, n, "jbm_exp2_f64");
  efficiency_f32 (expf, -FLT_MAX_EXP, FLT_MAX_EXP, n, "expf");
  efficiency_f32 (jbm_exp_f32, -FLT_MAX_EXP, FLT_MAX_EXP, n, "jbm_exp_f32");
  efficiency_f64 (exp, -DBL_MAX_EXP, DBL_MAX_EXP, n, "exp");
  efficiency_f64 (jbm_exp_f64, -DBL_MAX_EXP, DBL_MAX_EXP, n, "jbm_exp_f64");
  efficiency_f32 (exp10f, -FLT_MAX_10_EXP, FLT_MAX_10_EXP, n, "exp10f");
  efficiency_f32 (jbm_exp10_f32, -FLT_MAX_10_EXP, FLT_MAX_10_EXP, n,
                  "jbm_exp10_f32");
  efficiency_f64 (exp10, -DBL_MAX_10_EXP, DBL_MAX_10_EXP, n, "exp10");
  efficiency_f64 (jbm_exp10_f64, -DBL_MAX_10_EXP, DBL_MAX_10_EXP, n,
                  "jbm_exp10_f64");
  efficiency_f32 (expm1f, -FLT_MAX_EXP, FLT_MAX_EXP, n, "expm1f");
  efficiency_f32 (jbm_expm1_f32, -FLT_MAX_EXP, FLT_MAX_EXP, n, "jbm_expm1_f32");
  efficiency_f64 (expm1, -DBL_MAX_EXP, DBL_MAX_EXP, n, "expm1");
  efficiency_f64 (jbm_expm1_f64, -DBL_MAX_EXP, DBL_MAX_EXP, n, "jbm_expm1_f64");
  efficiency_f32 (log2f, FLT_MIN, FLT_MAX, n, "log2f");
  efficiency_f32 (jbm_log2_f32, FLT_MIN, FLT_MAX, n, "jbm_log2_f32");
  efficiency_f64 (log2, DBL_MIN, DBL_MAX, n, "log2");
  efficiency_f64 (jbm_log2_f64, DBL_MIN, DBL_MAX, n, "jbm_log2_f64");
  efficiency_f32 (logf, FLT_MIN, FLT_MAX, n, "logf");
  efficiency_f32 (jbm_log_f32, FLT_MIN, FLT_MAX, n, "jbm_log_f32");
  efficiency_f64 (log, DBL_MIN, DBL_MAX, n, "log");
  efficiency_f64 (jbm_log_f64, DBL_MIN, DBL_MAX, n, "jbm_log_f64");
  efficiency_f32 (log10f, FLT_MIN, FLT_MAX, n, "log10f");
  efficiency_f32 (jbm_log10_f32, FLT_MIN, FLT_MAX, n, "jbm_log10_f32");
  efficiency_f64 (log10, DBL_MIN, DBL_MAX, n, "log10");
  efficiency_f64 (jbm_log10_f64, DBL_MIN, DBL_MAX, n, "jbm_log10_f64");
  efficiency_f32 (sinf, -4.f * M_PIf, 4.f * M_PIf, n, "sinf");
  efficiency_f32 (jbm_sin_f32, -4.f * M_PIf, 4.f * M_PIf, n, "jbm_sin_f32");
  efficiency_f64 (sin, -4. * M_PI, 4. * M_PI, n, "sin");
  efficiency_f64 (jbm_sin_f64, -4. * M_PI, 4. * M_PI, n, "jbm_sin_f64");
  efficiency_f32 (cosf, -4.f * M_PIf, 4.f * M_PIf, n, "cosf");
  efficiency_f32 (jbm_cos_f32, -4.f * M_PIf, 4.f * M_PIf, n, "jbm_cos_f32");
  efficiency_f64 (cos, -4. * M_PI, 4. * M_PI, n, "cos");
  efficiency_f64 (jbm_cos_f64, -4. * M_PI, 4. * M_PI, n, "jbm_cos_f64");
  efficiency_f32 (tanf, -4.f * M_PIf, 4.f * M_PIf, n, "tanf");
  efficiency_f32 (jbm_tan_f32, -4.f * M_PIf, 4.f * M_PIf, n, "jbm_tan_f32");
  efficiency_f64 (tan, -4. * M_PI, 4. * M_PI, n, "tan");
  efficiency_f64 (jbm_tan_f64, -4. * M_PI, 4. * M_PI, n, "jbm_tan_f64");
  efficiency_f32 (atanf, -FLT_MAX, FLT_MAX, n, "atanf");
  efficiency_f32 (jbm_atan_f32, -FLT_MAX, FLT_MAX, n, "jbm_atan_f32");
  efficiency_f64 (atan, -DBL_MAX, DBL_MAX, n, "atan");
  efficiency_f64 (jbm_atan_f64, -DBL_MAX, DBL_MAX, n, "jbm_atan_f64");
  efficiency_f32 (asinf, -1.f, 1.f, n, "asinf");
  efficiency_f32 (jbm_asin_f32, -1.f, 1.f, n, "jbm_asin_f32");
  efficiency_f64 (asin, -1., 1., n, "asin");
  efficiency_f64 (jbm_asin_f64, -1., 1., n, "jbm_asin_f64");
  efficiency_f32 (acosf, -1.f, 1.f, n, "acosf");
  efficiency_f32 (jbm_acos_f32, -1.f, 1.f, n, "jbm_acos_f32");
  efficiency_f64 (acos, -1., 1., n, "acos");
  efficiency_f64 (jbm_acos_f64, -1., 1., n, "jbm_acos_f64");
  return 0;
}

