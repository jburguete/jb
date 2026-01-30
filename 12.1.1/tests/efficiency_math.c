#include "../src/math.h"
#include <inttypes.h>
#include <gsl/gsl_rng.h>
#include <glib.h>

#define DEBUG 0
#define SEED 7l
#define POL_HORNER 1
#define POL_ESTRIN 2
#define POL POL_HORNER

// parallel bucles

#if DEBUG

#define BUCLE_INIT(type, f) \
  for (i = imin; i < imax; ++i) \
    { \
      x[i] = (type) f (r[i], xmin, xmax, tau); \
      printf ("x[%lu]=%g\n", i, x[i]); \
    }
#define BUCLE_FUNCTION(f) \
  for (i = imin; i < imax; ++i) \
    y[i] = f (x[i])
#define BUCLE_ERROR(type, f, e) \
  for (i = imin; i < imax; ++i) \
    { \
      z = (type) f ((long double) x[i]); \
      ei = e (y[i], z); \
      printf ("i=%lu x=%g y=%g f=%g e=%g\n", i, x[i], y[i], z, (type) ei); \
      if (ei > em) \
        xm = x[i], em = ei; \
    }
#else

#define BUCLE_INIT(type, f) \
  for (i = imin; i < imax; ++i) \
    x[i] = (type) f (r[i], xmin, xmax, tau)
#define BUCLE_FUNCTION(f) \
  for (i = imin; i < imax; ++i) \
    y[i] = f (x[i])
#define BUCLE_ERROR(type, f, e) \
  for (i = imin; i < imax; ++i) \
    { \
      z = (type) f ((long double) x[i]); \
      ei = e (y[i], z); \
      if (ei > em) \
        xm = x[i], em = ei; \
    }

#endif

// function type

enum Type
{
  TYPE_ADD,
  TYPE_SUB,
  TYPE_MUL,
  TYPE_DIV,
  TYPE_SQRT,
  TYPE_MAX,
  TYPE_MIN,
  TYPE_ROUND,
  TYPE_FLOOR,
  TYPE_CEIL,
  TYPE_TRUNC,
  TYPE_ABS,
  TYPE_MOD,
  TYPE_EXP2,
  TYPE_EXP,
  TYPE_EXP10,
  TYPE_EXPM1,
  TYPE_LOG2,
  TYPE_LOG,
  TYPE_LOG10,
  TYPE_POW,
  TYPE_CBRT,
  TYPE_SIN,
  TYPE_COS,
  TYPE_TAN,
  TYPE_ATAN,
  TYPE_ASIN,
  TYPE_ACOS,
  TYPE_SINH,
  TYPE_COSH,
  TYPE_TANH,
  TYPE_ERF,
  TYPE_ERFC,
  TYPE_JBM_ABS,
  TYPE_JBM_MOD,
  TYPE_JBM_EXP2,
  TYPE_JBM_EXP,
  TYPE_JBM_EXP10,
  TYPE_JBM_EXPM1,
  TYPE_JBM_LOG2,
  TYPE_JBM_LOG,
  TYPE_JBM_LOG10,
  TYPE_JBM_POW,
  TYPE_JBM_CBRT,
  TYPE_JBM_SIN,
  TYPE_JBM_COS,
  TYPE_JBM_TAN,
  TYPE_JBM_ATAN,
  TYPE_JBM_ASIN,
  TYPE_JBM_ACOS,
  TYPE_JBM_SINH,
  TYPE_JBM_COSH,
  TYPE_JBM_TANH,
  TYPE_JBM_ERF,
  TYPE_JBM_ERFC,
  TYPE_JBM_POL1,
  TYPE_JBM_POL2,
  TYPE_JBM_POL3,
  TYPE_JBM_POL4,
  TYPE_JBM_POL5,
  TYPE_JBM_POL6,
  TYPE_JBM_POL7,
  TYPE_JBM_POL8,
  TYPE_JBM_POL9,
  TYPE_JBM_POL10,
  TYPE_JBM_POL11,
  TYPE_JBM_POL12,
  TYPE_JBM_POL13,
  TYPE_JBM_POL14,
  TYPE_JBM_POL15,
};

// parallel structs

typedef struct
{
  long double *z;
  const double *r;
  float *x;
  float *y;
  double xmin;
  double xmax;
  unsigned int type;
  unsigned long int imin;
  unsigned long int imax;
} Parallel_f32;

typedef struct
{
  long double *z;
  const double *r;
  double *x;
  double *y;
  double xmin;
  double xmax;
  unsigned int type;
  unsigned long int imin;
  unsigned long int imax;
} Parallel_f64;

// global coefficients

const float a32[17] = { 1.f, 2.f, 4.f, 8.f, 16.f, 32.f, 64.f, 128.f, 256.f,
  512.f, 1024.f, 2048.f, 4096.f, 8192.f, 16384.f, 32768.f, 65536.f
};

const double a64[17] = { 1., 2., 4., 8., 16., 32., 64., 128., 256.,
  512., 1024., 2048., 4096., 8192., 16384., 32768., 65536.
};

const long double a80[17] = { 1.L, 2.L, 4.L, 8.L, 16.L, 32.L, 64.L, 128.L,
  256.L, 512.L, 1024.L, 2048.L, 4096.L, 8192.L, 16384.L, 32768.L, 65536.L
};

// global variables

GMutex mutex;
uint64_t global_error;
float x32_max;
double x64_max;

// crono function

static inline double
crono ()
{
  struct timespec t;
  clock_gettime (CLOCK_MONOTONIC, &t);
  return t.tv_sec + 1e-9 * t.tv_nsec;
}

// distributions

static inline double
erfinv_f64 (const double y)
{
  const double a = 0.147;
  double ln, t, x;
  ln = log (1. - y * y);
  t = 2.0 / M_PI * a + ln * 0.5;
  x = sqrt (sqrt (t * t - ln / a) - t);
  return copysign (x, y);
}

static inline double
uniform_f64 (const double r, const double xmin, const double xmax,
             const double tau __attribute__((unused)))
{
  double xm, dx;
  xm = 0.5 * (xmin + xmax);
  dx = xmax - xm;
  return xm + (2. * r - 1.) * dx;
}

static inline double
normal_f64 (const double r, const double xmin, const double xmax,
            const double tau)
{
  return fmax (xmin, fmin (xmax, tau * erfinv_f64 (2. * r - 1.)));
}

static inline double
loguniform_f64 (const double r, const double xmin, const double xmax,
                const double tau __attribute__((unused)))
{
  return exp2 (log2 (xmin) + r * (log2 (xmax) - log2 (xmin)));
}

// long double functions

static inline long double
add_f80 (const long double x)
{
  return x + M_PIl;
}

static inline long double
sub_f80 (const long double x)
{
  return x - M_PIl;
}

static inline long double
mul_f80 (const long double x)
{
  return x * M_PIl;
}

static inline long double
div_f80 (const long double x)
{
  return x / M_PIl;
}

static inline long double
max_f80 (const long double x)
{
  return fmaxl (x, M_PIl);
}

static inline long double
min_f80 (const long double x)
{
  return fminl (x, M_PIl);
}

static inline long double
mod_f80 (const long double x)
{
  return fmodl (x, M_PIl);
}

static inline long double
pol1_f80 (const long double x)
{
  return a80[0] + x * a80[1];
}

static inline long double
pol2_f80 (const long double x)
{
  long double y;
  y = a80[1] + x * a80[2];
  return a80[0] + x * y;
}

static inline long double
pol3_f80 (const long double x)
{
  long double y;
  y = a80[2] + x * a80[3];
  y = a80[1] + x * y;
  return a80[0] + x * y;
}

static inline long double
pol4_f80 (const long double x)
{
  long double y;
  y = a80[3] + x * a80[4];
  y = a80[2] + x * y;
  y = a80[1] + x * y;
  return a80[0] + x * y;
}

static inline long double
pol5_f80 (const long double x)
{
  long double y;
  y = a80[4] + x * a80[5];
  y = a80[3] + x * y;
  y = a80[2] + x * y;
  y = a80[1] + x * y;
  return a80[0] + x * y;
}

static inline long double
pol6_f80 (const long double x)
{
  long double y;
  y = a80[5] + x * a80[6];
  y = a80[4] + x * y;
  y = a80[3] + x * y;
  y = a80[2] + x * y;
  y = a80[1] + x * y;
  return a80[0] + x * y;
}

static inline long double
pol7_f80 (const long double x)
{
  long double y;
  y = a80[6] + x * a80[7];
  y = a80[5] + x * y;
  y = a80[4] + x * y;
  y = a80[3] + x * y;
  y = a80[2] + x * y;
  y = a80[1] + x * y;
  return a80[0] + x * y;
}

static inline long double
pol8_f80 (const long double x)
{
  long double y;
  y = a80[7] + x * a80[8];
  y = a80[6] + x * y;
  y = a80[5] + x * y;
  y = a80[4] + x * y;
  y = a80[3] + x * y;
  y = a80[2] + x * y;
  y = a80[1] + x * y;
  return a80[0] + x * y;
}

static inline long double
pol9_f80 (const long double x)
{
  long double y;
  y = a80[8] + x * a80[9];
  y = a80[7] + x * y;
  y = a80[6] + x * y;
  y = a80[5] + x * y;
  y = a80[4] + x * y;
  y = a80[3] + x * y;
  y = a80[2] + x * y;
  y = a80[1] + x * y;
  return a80[0] + x * y;
}

static inline long double
pol10_f80 (const long double x)
{
  long double y;
  y = a80[9] + x * a80[10];
  y = a80[8] + x * y;
  y = a80[7] + x * y;
  y = a80[6] + x * y;
  y = a80[5] + x * y;
  y = a80[4] + x * y;
  y = a80[3] + x * y;
  y = a80[2] + x * y;
  y = a80[1] + x * y;
  return a80[0] + x * y;
}

static inline long double
pol11_f80 (const long double x)
{
  long double y;
  y = a80[10] + x * a80[11];
  y = a80[9] + x * y;
  y = a80[8] + x * y;
  y = a80[7] + x * y;
  y = a80[6] + x * y;
  y = a80[5] + x * y;
  y = a80[4] + x * y;
  y = a80[3] + x * y;
  y = a80[2] + x * y;
  y = a80[1] + x * y;
  return a80[0] + x * y;
}

static inline long double
pol12_f80 (const long double x)
{
  long double y;
  y = a80[11] + x * a80[12];
  y = a80[10] + x * y;
  y = a80[9] + x * y;
  y = a80[8] + x * y;
  y = a80[7] + x * y;
  y = a80[6] + x * y;
  y = a80[5] + x * y;
  y = a80[4] + x * y;
  y = a80[3] + x * y;
  y = a80[2] + x * y;
  y = a80[1] + x * y;
  return a80[0] + x * y;
}

static inline long double
pol13_f80 (const long double x)
{
  long double y;
  y = a80[12] + x * a80[13];
  y = a80[11] + x * y;
  y = a80[10] + x * y;
  y = a80[9] + x * y;
  y = a80[8] + x * y;
  y = a80[7] + x * y;
  y = a80[6] + x * y;
  y = a80[5] + x * y;
  y = a80[4] + x * y;
  y = a80[3] + x * y;
  y = a80[2] + x * y;
  y = a80[1] + x * y;
  return a80[0] + x * y;
}

static inline long double
pol14_f80 (const long double x)
{
  long double y;
  y = a80[13] + x * a80[14];
  y = a80[12] + x * y;
  y = a80[11] + x * y;
  y = a80[10] + x * y;
  y = a80[9] + x * y;
  y = a80[8] + x * y;
  y = a80[7] + x * y;
  y = a80[6] + x * y;
  y = a80[5] + x * y;
  y = a80[4] + x * y;
  y = a80[3] + x * y;
  y = a80[2] + x * y;
  y = a80[1] + x * y;
  return a80[0] + x * y;
}

static inline long double
pol15_f80 (const long double x)
{
  long double y;
  y = a80[14] + x * a80[15];
  y = a80[13] + x * y;
  y = a80[12] + x * y;
  y = a80[11] + x * y;
  y = a80[10] + x * y;
  y = a80[9] + x * y;
  y = a80[8] + x * y;
  y = a80[7] + x * y;
  y = a80[6] + x * y;
  y = a80[5] + x * y;
  y = a80[4] + x * y;
  y = a80[3] + x * y;
  y = a80[2] + x * y;
  y = a80[1] + x * y;
  return a80[0] + x * y;
}

static inline long double
pow_f80 (const long double x)
{
  return pow (x, M_PIl);
}

static inline long double
f80 (unsigned int type, long double x)
{
  switch (type)
    {
    case TYPE_ADD:
      return add_f80 (x);
    case TYPE_SUB:
      return sub_f80 (x);
    case TYPE_MUL:
      return mul_f80 (x);
    case TYPE_DIV:
      return div_f80 (x);
    case TYPE_SQRT:
      return sqrtl (x);
    case TYPE_MAX:
      return max_f80 (x);
    case TYPE_MIN:
      return min_f80 (x);
    case TYPE_ROUND:
      return roundl (x);
    case TYPE_FLOOR:
      return floorl (x);
    case TYPE_CEIL:
      return ceill (x);
    case TYPE_TRUNC:
      return truncl (x);
    case TYPE_ABS:
      return fabsl (x);
    case TYPE_MOD:
      return mod_f80 (x);
    case TYPE_EXP2:
      return exp2l (x);
    case TYPE_EXP:
      return expl (x);
    case TYPE_EXP10:
      return exp10l (x);
    case TYPE_EXPM1:
      return expm1l (x);
    case TYPE_LOG2:
      return log2l (x);
    case TYPE_LOG:
      return logl (x);
    case TYPE_LOG10:
      return log10l (x);
    case TYPE_POW:
      return pow_f80 (x);
    case TYPE_CBRT:
      return cbrtl (x);
    case TYPE_SIN:
      return sinl (x);
    case TYPE_COS:
      return cosl (x);
    case TYPE_TAN:
      return tanl (x);
    case TYPE_ATAN:
      return atanl (x);
    case TYPE_ASIN:
      return asinl (x);
    case TYPE_ACOS:
      return acosl (x);
    case TYPE_SINH:
      return sinhl (x);
    case TYPE_COSH:
      return coshl (x);
    case TYPE_TANH:
      return tanhl (x);
    case TYPE_ERF:
      return erfl (x);
    case TYPE_ERFC:
      return erfcl (x);
    case TYPE_JBM_ABS:
      return fabsl (x);
    case TYPE_JBM_MOD:
      return mod_f80 (x);
    case TYPE_JBM_EXP2:
      return exp2l (x);
    case TYPE_JBM_EXP:
      return expl (x);
    case TYPE_JBM_EXP10:
      return exp10l (x);
    case TYPE_JBM_EXPM1:
      return expm1l (x);
    case TYPE_JBM_LOG2:
      return log2l (x);
    case TYPE_JBM_LOG:
      return logl (x);
    case TYPE_JBM_LOG10:
      return log10l (x);
    case TYPE_JBM_POW:
      return pow_f80 (x);
    case TYPE_JBM_CBRT:
      return cbrtl (x);
    case TYPE_JBM_SIN:
      return sinl (x);
    case TYPE_JBM_COS:
      return cosl (x);
    case TYPE_JBM_TAN:
      return tanl (x);
    case TYPE_JBM_ATAN:
      return atanl (x);
    case TYPE_JBM_ASIN:
      return asinl (x);
    case TYPE_JBM_ACOS:
      return acosl (x);
    case TYPE_JBM_SINH:
      return sinhl (x);
    case TYPE_JBM_COSH:
      return coshl (x);
    case TYPE_JBM_TANH:
      return tanhl (x);
    case TYPE_JBM_ERF:
      return erfl (x);
    case TYPE_JBM_ERFC:
      return erfcl (x);
    case TYPE_JBM_POL1:
      return pol1_f80 (x);
    case TYPE_JBM_POL2:
      return pol2_f80 (x);
    case TYPE_JBM_POL3:
      return pol3_f80 (x);
    case TYPE_JBM_POL4:
      return pol4_f80 (x);
    case TYPE_JBM_POL5:
      return pol5_f80 (x);
    case TYPE_JBM_POL6:
      return pol6_f80 (x);
    case TYPE_JBM_POL7:
      return pol7_f80 (x);
    case TYPE_JBM_POL8:
      return pol8_f80 (x);
    case TYPE_JBM_POL9:
      return pol9_f80 (x);
    case TYPE_JBM_POL10:
      return pol10_f80 (x);
    case TYPE_JBM_POL11:
      return pol11_f80 (x);
    case TYPE_JBM_POL12:
      return pol12_f80 (x);
    case TYPE_JBM_POL13:
      return pol13_f80 (x);
    case TYPE_JBM_POL14:
      return pol14_f80 (x);
    case TYPE_JBM_POL15:
      return pol15_f80 (x);
    }
  return 0.L;
}

// error functions

static inline uint32_t
bits_32 (const float x)
{
  uint32_t i;
  memcpy (&i, &x, 4l);
  if (!(i & 0x7f800000u))
    i = 0u;
  if (i & JBM_BITS_SIGN_F32)
    i = JBM_BITS_SIGN_F32 - i;
  else
    i -= JBM_BITS_SIGN_F32;
  return i;
}

static inline uint32_t
ulp_32 (const float x, const float y)
{
  uint32_t i, j;
  if (fabsf (x) < (float) JBM_SQRT_FLT_EPSILON
      && fabsf (y) < (float) JBM_SQRT_FLT_EPSILON)
    return 0u;
  i = bits_32 (x);
  j = bits_32 (y);
  return (j > i) ? j - i : i - j;
}

static inline void
error_f32 (void *data, void *user_data __attribute__((unused)))
{
  Parallel_f32 *p;
  float *x, *y;
  float xm, z;
  uint32_t ei, em;
  unsigned int type;
  unsigned long int i, imin, imax;
  p = (Parallel_f32 *) data;
  type = p->type;
  imin = p->imin;
  imax = p->imax;
  x = p->x;
  y = p->y;
  em = 0u;
  xm = p->x[0];
  switch (type)
    {
    case TYPE_ADD:
      BUCLE_ERROR (float, add_f80, ulp_32);
      break;
    case TYPE_SUB:
      BUCLE_ERROR (float, sub_f80, ulp_32);
      break;
    case TYPE_MUL:
      BUCLE_ERROR (float, mul_f80, ulp_32);
      break;
    case TYPE_DIV:
      BUCLE_ERROR (float, div_f80, ulp_32);
      break;
    case TYPE_SQRT:
      BUCLE_ERROR (float, sqrtl, ulp_32);
      break;
    case TYPE_MAX:
      BUCLE_ERROR (float, max_f80, ulp_32);
      break;
    case TYPE_MIN:
      BUCLE_ERROR (float, min_f80, ulp_32);
      break;
    case TYPE_ROUND:
      BUCLE_ERROR (float, roundl, ulp_32);
      break;
    case TYPE_FLOOR:
      BUCLE_ERROR (float, floorl, ulp_32);
      break;
    case TYPE_CEIL:
      BUCLE_ERROR (float, ceill, ulp_32);
      break;
    case TYPE_TRUNC:
      BUCLE_ERROR (float, truncl, ulp_32);
      break;
    case TYPE_ABS:
      BUCLE_ERROR (float, fabsl, ulp_32);
      break;
    case TYPE_MOD:
      BUCLE_ERROR (float, mod_f80, ulp_32);
      break;
    case TYPE_EXP2:
      BUCLE_ERROR (float, exp2l, ulp_32);
      break;
    case TYPE_EXP:
      BUCLE_ERROR (float, expl, ulp_32);
      break;
    case TYPE_EXP10:
      BUCLE_ERROR (float, exp10l, ulp_32);
      break;
    case TYPE_EXPM1:
      BUCLE_ERROR (float, expm1l, ulp_32);
      break;
    case TYPE_LOG2:
      BUCLE_ERROR (float, log2l, ulp_32);
      break;
    case TYPE_LOG:
      BUCLE_ERROR (float, logl, ulp_32);
      break;
    case TYPE_LOG10:
      BUCLE_ERROR (float, log10l, ulp_32);
      break;
    case TYPE_POW:
      BUCLE_ERROR (float, pow_f80, ulp_32);
      break;
    case TYPE_CBRT:
      BUCLE_ERROR (float, cbrtl, ulp_32);
      break;
    case TYPE_SIN:
      BUCLE_ERROR (float, sinl, ulp_32);
      break;
    case TYPE_COS:
      BUCLE_ERROR (float, cosl, ulp_32);
      break;
    case TYPE_TAN:
      BUCLE_ERROR (float, tanl, ulp_32);
      break;
    case TYPE_ATAN:
      BUCLE_ERROR (float, atanl, ulp_32);
      break;
    case TYPE_ASIN:
      BUCLE_ERROR (float, asinl, ulp_32);
      break;
    case TYPE_ACOS:
      BUCLE_ERROR (float, acosl, ulp_32);
      break;
    case TYPE_SINH:
      BUCLE_ERROR (float, sinhl, ulp_32);
      break;
    case TYPE_COSH:
      BUCLE_ERROR (float, coshl, ulp_32);
      break;
    case TYPE_TANH:
      BUCLE_ERROR (float, tanhl, ulp_32);
      break;
    case TYPE_ERF:
      BUCLE_ERROR (float, erfl, ulp_32);
      break;
    case TYPE_ERFC:
      BUCLE_ERROR (float, erfcl, ulp_32);
      break;
    case TYPE_JBM_ABS:
      BUCLE_ERROR (float, fabsl, ulp_32);
      break;
    case TYPE_JBM_MOD:
      BUCLE_ERROR (float, mod_f80, ulp_32);
      break;
    case TYPE_JBM_EXP2:
      BUCLE_ERROR (float, exp2l, ulp_32);
      break;
    case TYPE_JBM_EXP:
      BUCLE_ERROR (float, expl, ulp_32);
      break;
    case TYPE_JBM_EXP10:
      BUCLE_ERROR (float, exp10l, ulp_32);
      break;
    case TYPE_JBM_EXPM1:
      BUCLE_ERROR (float, expm1l, ulp_32);
      break;
    case TYPE_JBM_LOG2:
      BUCLE_ERROR (float, log2l, ulp_32);
      break;
    case TYPE_JBM_LOG:
      BUCLE_ERROR (float, logl, ulp_32);
      break;
    case TYPE_JBM_LOG10:
      BUCLE_ERROR (float, log10l, ulp_32);
      break;
    case TYPE_JBM_POW:
      BUCLE_ERROR (float, pow_f80, ulp_32);
      break;
    case TYPE_JBM_CBRT:
      BUCLE_ERROR (float, cbrtl, ulp_32);
      break;
    case TYPE_JBM_SIN:
      BUCLE_ERROR (float, sinl, ulp_32);
      break;
    case TYPE_JBM_COS:
      BUCLE_ERROR (float, cosl, ulp_32);
      break;
    case TYPE_JBM_TAN:
      BUCLE_ERROR (float, tanl, ulp_32);
      break;
    case TYPE_JBM_ATAN:
      BUCLE_ERROR (float, atanl, ulp_32);
      break;
    case TYPE_JBM_ASIN:
      BUCLE_ERROR (float, asinl, ulp_32);
      break;
    case TYPE_JBM_ACOS:
      BUCLE_ERROR (float, acosl, ulp_32);
      break;
    case TYPE_JBM_SINH:
      BUCLE_ERROR (float, sinhl, ulp_32);
      break;
    case TYPE_JBM_COSH:
      BUCLE_ERROR (float, coshl, ulp_32);
      break;
    case TYPE_JBM_TANH:
      BUCLE_ERROR (float, tanhl, ulp_32);
      break;
    case TYPE_JBM_ERF:
      BUCLE_ERROR (float, erfl, ulp_32);
      break;
    case TYPE_JBM_ERFC:
      BUCLE_ERROR (float, erfcl, ulp_32);
      break;
    case TYPE_JBM_POL1:
      BUCLE_ERROR (float, pol1_f80, ulp_32);
      break;
    case TYPE_JBM_POL2:
      BUCLE_ERROR (float, pol2_f80, ulp_32);
      break;
    case TYPE_JBM_POL3:
      BUCLE_ERROR (float, pol3_f80, ulp_32);
      break;
    case TYPE_JBM_POL4:
      BUCLE_ERROR (float, pol4_f80, ulp_32);
      break;
    case TYPE_JBM_POL5:
      BUCLE_ERROR (float, pol5_f80, ulp_32);
      break;
    case TYPE_JBM_POL6:
      BUCLE_ERROR (float, pol6_f80, ulp_32);
      break;
    case TYPE_JBM_POL7:
      BUCLE_ERROR (float, pol7_f80, ulp_32);
      break;
    case TYPE_JBM_POL8:
      BUCLE_ERROR (float, pol8_f80, ulp_32);
      break;
    case TYPE_JBM_POL9:
      BUCLE_ERROR (float, pol9_f80, ulp_32);
      break;
    case TYPE_JBM_POL10:
      BUCLE_ERROR (float, pol10_f80, ulp_32);
      break;
    case TYPE_JBM_POL11:
      BUCLE_ERROR (float, pol11_f80, ulp_32);
      break;
    case TYPE_JBM_POL12:
      BUCLE_ERROR (float, pol12_f80, ulp_32);
      break;
    case TYPE_JBM_POL13:
      BUCLE_ERROR (float, pol13_f80, ulp_32);
      break;
    case TYPE_JBM_POL14:
      BUCLE_ERROR (float, pol14_f80, ulp_32);
      break;
    case TYPE_JBM_POL15:
      BUCLE_ERROR (float, pol15_f80, ulp_32);
      break;
    }
  if ((uint64_t) em > global_error)
    {
      g_mutex_lock (&mutex);
      global_error = (uint64_t) em;
      x32_max = xm;
      g_mutex_unlock (&mutex);
    }
}

static inline uint64_t
bits_64 (const double x)
{
  uint64_t i;
  memcpy (&i, &x, 8l);
  if (!(i & 0x7ff0000000000000ull))
    i = 0ull;
  if (i & JBM_BITS_SIGN_F64)
    i = JBM_BITS_SIGN_F64 - i;
  else
    i -= JBM_BITS_SIGN_F64;
  return i;
}

static inline uint64_t
ulp_64 (const double x, const double y)
{
  uint64_t i, j;
  if (fabs (x) < (double) JBM_SQRT_DBL_EPSILON
      && fabs (y) < (double) JBM_SQRT_DBL_EPSILON)
    return 0ull;
  i = bits_64 (x);
  j = bits_64 (y);
  return (j > i) ? j - i : i - j;
}

static inline void
error_f64 (void *data, void *user_data __attribute__((unused)))
{
  Parallel_f64 *p;
  double *x, *y;
  double xm, z;
  uint64_t ei, em;
  unsigned int type;
  unsigned long int i, imin, imax;
  p = (Parallel_f64 *) data;
  type = p->type;
  imin = p->imin;
  imax = p->imax;
  x = p->x;
  y = p->y;
  em = 0ull;
  xm = p->x[0];
  switch (type)
    {
    case TYPE_ADD:
      BUCLE_ERROR (double, add_f80, ulp_64);
      break;
    case TYPE_SUB:
      BUCLE_ERROR (double, sub_f80, ulp_64);
      break;
    case TYPE_MUL:
      BUCLE_ERROR (double, mul_f80, ulp_64);
      break;
    case TYPE_DIV:
      BUCLE_ERROR (double, div_f80, ulp_64);
      break;
    case TYPE_SQRT:
      BUCLE_ERROR (double, sqrtl, ulp_64);
      break;
    case TYPE_MAX:
      BUCLE_ERROR (double, max_f80, ulp_64);
      break;
    case TYPE_MIN:
      BUCLE_ERROR (double, min_f80, ulp_64);
      break;
    case TYPE_ROUND:
      BUCLE_ERROR (double, roundl, ulp_64);
      break;
    case TYPE_FLOOR:
      BUCLE_ERROR (double, floorl, ulp_64);
      break;
    case TYPE_CEIL:
      BUCLE_ERROR (double, ceill, ulp_64);
      break;
    case TYPE_TRUNC:
      BUCLE_ERROR (double, truncl, ulp_64);
      break;
    case TYPE_ABS:
      BUCLE_ERROR (double, fabsl, ulp_64);
      break;
    case TYPE_MOD:
      BUCLE_ERROR (double, mod_f80, ulp_64);
      break;
    case TYPE_EXP2:
      BUCLE_ERROR (double, exp2l, ulp_64);
      break;
    case TYPE_EXP:
      BUCLE_ERROR (double, expl, ulp_64);
      break;
    case TYPE_EXP10:
      BUCLE_ERROR (double, exp10l, ulp_64);
      break;
    case TYPE_EXPM1:
      BUCLE_ERROR (double, expm1l, ulp_64);
      break;
    case TYPE_LOG2:
      BUCLE_ERROR (double, log2l, ulp_64);
      break;
    case TYPE_LOG:
      BUCLE_ERROR (double, logl, ulp_64);
      break;
    case TYPE_LOG10:
      BUCLE_ERROR (double, log10l, ulp_64);
      break;
    case TYPE_POW:
      BUCLE_ERROR (double, pow_f80, ulp_64);
      break;
    case TYPE_CBRT:
      BUCLE_ERROR (double, cbrtl, ulp_64);
      break;
    case TYPE_SIN:
      BUCLE_ERROR (double, sinl, ulp_64);
      break;
    case TYPE_COS:
      BUCLE_ERROR (double, cosl, ulp_64);
      break;
    case TYPE_TAN:
      BUCLE_ERROR (double, tanl, ulp_64);
      break;
    case TYPE_ATAN:
      BUCLE_ERROR (double, atanl, ulp_64);
      break;
    case TYPE_ASIN:
      BUCLE_ERROR (double, asinl, ulp_64);
      break;
    case TYPE_ACOS:
      BUCLE_ERROR (double, acosl, ulp_64);
      break;
    case TYPE_SINH:
      BUCLE_ERROR (double, sinhl, ulp_64);
      break;
    case TYPE_COSH:
      BUCLE_ERROR (double, coshl, ulp_64);
      break;
    case TYPE_TANH:
      BUCLE_ERROR (double, tanhl, ulp_64);
      break;
    case TYPE_ERF:
      BUCLE_ERROR (double, erfl, ulp_64);
      break;
    case TYPE_ERFC:
      BUCLE_ERROR (double, erfcl, ulp_64);
      break;
    case TYPE_JBM_ABS:
      BUCLE_ERROR (double, fabsl, ulp_64);
      break;
    case TYPE_JBM_MOD:
      BUCLE_ERROR (double, mod_f80, ulp_64);
      break;
    case TYPE_JBM_EXP2:
      BUCLE_ERROR (double, exp2l, ulp_64);
      break;
    case TYPE_JBM_EXP:
      BUCLE_ERROR (double, expl, ulp_64);
      break;
    case TYPE_JBM_EXP10:
      BUCLE_ERROR (double, exp10l, ulp_64);
      break;
    case TYPE_JBM_EXPM1:
      BUCLE_ERROR (double, expm1l, ulp_64);
      break;
    case TYPE_JBM_LOG2:
      BUCLE_ERROR (double, log2l, ulp_64);
      break;
    case TYPE_JBM_LOG:
      BUCLE_ERROR (double, logl, ulp_64);
      break;
    case TYPE_JBM_LOG10:
      BUCLE_ERROR (double, log10l, ulp_64);
      break;
    case TYPE_JBM_POW:
      BUCLE_ERROR (double, pow_f80, ulp_64);
      break;
    case TYPE_JBM_CBRT:
      BUCLE_ERROR (double, cbrtl, ulp_64);
      break;
    case TYPE_JBM_SIN:
      BUCLE_ERROR (double, sinl, ulp_64);
      break;
    case TYPE_JBM_COS:
      BUCLE_ERROR (double, cosl, ulp_64);
      break;
    case TYPE_JBM_TAN:
      BUCLE_ERROR (double, tanl, ulp_64);
      break;
    case TYPE_JBM_ATAN:
      BUCLE_ERROR (double, atanl, ulp_64);
      break;
    case TYPE_JBM_ASIN:
      BUCLE_ERROR (double, asinl, ulp_64);
      break;
    case TYPE_JBM_ACOS:
      BUCLE_ERROR (double, acosl, ulp_64);
      break;
    case TYPE_JBM_SINH:
      BUCLE_ERROR (double, sinhl, ulp_64);
      break;
    case TYPE_JBM_COSH:
      BUCLE_ERROR (double, coshl, ulp_64);
      break;
    case TYPE_JBM_TANH:
      BUCLE_ERROR (double, tanhl, ulp_64);
      break;
    case TYPE_JBM_ERF:
      BUCLE_ERROR (double, erfl, ulp_64);
      break;
    case TYPE_JBM_ERFC:
      BUCLE_ERROR (double, erfcl, ulp_64);
      break;
    case TYPE_JBM_POL1:
      BUCLE_ERROR (double, pol1_f80, ulp_64);
      break;
    case TYPE_JBM_POL2:
      BUCLE_ERROR (double, pol2_f80, ulp_64);
      break;
    case TYPE_JBM_POL3:
      BUCLE_ERROR (double, pol3_f80, ulp_64);
      break;
    case TYPE_JBM_POL4:
      BUCLE_ERROR (double, pol4_f80, ulp_64);
      break;
    case TYPE_JBM_POL5:
      BUCLE_ERROR (double, pol5_f80, ulp_64);
      break;
    case TYPE_JBM_POL6:
      BUCLE_ERROR (double, pol6_f80, ulp_64);
      break;
    case TYPE_JBM_POL7:
      BUCLE_ERROR (double, pol7_f80, ulp_64);
      break;
    case TYPE_JBM_POL8:
      BUCLE_ERROR (double, pol8_f80, ulp_64);
      break;
    case TYPE_JBM_POL9:
      BUCLE_ERROR (double, pol9_f80, ulp_64);
      break;
    case TYPE_JBM_POL10:
      BUCLE_ERROR (double, pol10_f80, ulp_64);
      break;
    case TYPE_JBM_POL11:
      BUCLE_ERROR (double, pol11_f80, ulp_64);
      break;
    case TYPE_JBM_POL12:
      BUCLE_ERROR (double, pol12_f80, ulp_64);
      break;
    case TYPE_JBM_POL13:
      BUCLE_ERROR (double, pol13_f80, ulp_64);
      break;
    case TYPE_JBM_POL14:
      BUCLE_ERROR (double, pol14_f80, ulp_64);
      break;
    case TYPE_JBM_POL15:
      BUCLE_ERROR (double, pol15_f80, ulp_64);
      break;
    }
  if (em > global_error)
    {
      g_mutex_lock (&mutex);
      global_error = em;
      x64_max = xm;
      g_mutex_unlock (&mutex);
    }
}

// float functions

static inline float
add_f32 (const float x)
{
  return x + M_PIf;
}

static inline float
sub_f32 (const float x)
{
  return x - M_PIf;
}

static inline float
mul_f32 (const float x)
{
  return x * M_PIf;
}

static inline float
div_f32 (const float x)
{
  return x / M_PIf;
}

static inline float
max_f32 (const float x)
{
  return fmaxf (x, M_PIf);
}

static inline float
min_f32 (const float x)
{
  return fminf (x, M_PIf);
}

static inline float
f32_mod (const float x)
{
  return fmodf (x, M_PIf);
}

static inline float
f32_mod_jbm (const float x)
{
  return jbm_f32_mod (x, M_PIf);
}

static inline float
pol1_f32 (const float x)
{
  return a32[0] + x * a32[1];
}

static inline float
pol2_f32 (const float x)
{
  float y;
  y = a32[1] + x * a32[2];
  return a32[0] + x * y;
}

static inline float
pol3_f32 (const float x)
{
#if POL == POL_HORNER
  float y;
  y = a32[2] + x * a32[3];
  y = a32[1] + x * y;
  return a32[0] + x * y;
#elif POL == POL_ESTRIN
  float y, y2, x2;
  x2 = x * x;
  y2 = a32[1] + x2 * a32[3];
  y = a32[0] + x2 * a32[2];
  return y + x * y2;
#endif
}

static inline float
pol4_f32 (const float x)
{
#if POL == POL_HORNER
  float y;
  y = a32[3] + x * a32[4];
  y = a32[2] + x * y;
  y = a32[1] + x * y;
  return a32[0] + x * y;
#elif POL == POL_ESTRIN
  float y, y2, x2;
  x2 = x * x;
  y = a32[2] + x2 * a32[4];
  y2 = a32[1] + x2 * a32[3];
  y = a32[0] + x2 * y;
  return y + x * y2;
#endif
}

static inline float
pol5_f32 (const float x)
{
#if POL == POL_HORNER
  float y;
  y = a32[4] + x * a32[5];
  y = a32[3] + x * y;
  y = a32[2] + x * y;
  y = a32[1] + x * y;
  return a32[0] + x * y;
#elif POL == POL_ESTRIN
  float y, y2, x2;
  x2 = x * x;
  y2 = a32[3] + x2 * a32[5];
  y = a32[2] + x2 * a32[4];
  y2 = a32[1] + x2 * y2;
  y = a32[0] + x2 * y;
  return y + x * y2;
#endif
}

static inline float
pol6_f32 (const float x)
{
#if POL == POL_HORNER
  float y;
  y = a32[5] + x * a32[6];
  y = a32[4] + x * y;
  y = a32[3] + x * y;
  y = a32[2] + x * y;
  y = a32[1] + x * y;
  return a32[0] + x * y;
#elif POL == POL_ESTRIN
  float y, y2, x2;
  x2 = x * x;
  y = a32[4] + x2 * a32[6];
  y2 = a32[3] + x2 * a32[5];
  y = a32[2] + x2 * y;
  y2 = a32[1] + x2 * y2;
  y = a32[0] + x2 * y;
  return y + x * y2;
#endif
}

static inline float
pol7_f32 (const float x)
{
#if POL == POL_HORNER
  float y;
  y = a32[6] + x * a32[7];
  y = a32[5] + x * y;
  y = a32[4] + x * y;
  y = a32[3] + x * y;
  y = a32[2] + x * y;
  y = a32[1] + x * y;
  return a32[0] + x * y;
#elif POL == POL_ESTRIN
  float y, y2, x2;
  x2 = x * x;
  y2 = a32[5] + x2 * a32[7];
  y = a32[4] + x2 * a32[6];
  y2 = a32[3] + x2 * y2;
  y = a32[2] + x2 * y;
  y2 = a32[1] + x2 * y2;
  y = a32[0] + x2 * y;
  return y + x * y2;
#endif
}

static inline float
pol8_f32 (const float x)
{
#if POL == POL_HORNER
  float y;
  y = a32[7] + x * a32[8];
  y = a32[6] + x * y;
  y = a32[5] + x * y;
  y = a32[4] + x * y;
  y = a32[3] + x * y;
  y = a32[2] + x * y;
  y = a32[1] + x * y;
  return a32[0] + x * y;
#elif POL == POL_ESTRIN
  float y, y2, y3, y4, x2, x4;
  x2 = x * x;
  x4 = x2 * x2;
  y = a32[4] + x4 * a32[8];
  y4 = a32[3] + x4 * a32[7];
  y3 = a32[2] + x4 * a32[6];
  y2 = a32[1] + x4 * a32[5];
  y = a32[0] + x4 * y;
  y2 = y2 + x2 * y4;
  y = y + x2 * y3;
  return y + x2 * y2;
#endif
}

static inline float
pol9_f32 (const float x)
{
#if POL == POL_HORNER
  float y;
  y = a32[8] + x * a32[9];
  y = a32[7] + x * y;
  y = a32[6] + x * y;
  y = a32[5] + x * y;
  y = a32[4] + x * y;
  y = a32[3] + x * y;
  y = a32[2] + x * y;
  y = a32[1] + x * y;
  return a32[0] + x * y;
#elif POL == POL_ESTRIN
  float y, y2, y3, y4, x2, x4;
  x2 = x * x;
  x4 = x2 * x2;
  y2 = a32[5] + x4 * a32[9];
  y = a32[4] + x4 * a32[8];
  y4 = a32[3] + x4 * a32[7];
  y3 = a32[2] + x4 * a32[6];
  y2 = a32[1] + x4 * y2;
  y = a32[0] + x4 * y;
  y2 = y2 + x2 * y4;
  y = y + x2 * y3;
  return y + x2 * y2;
#endif
}

static inline float
pol10_f32 (const float x)
{
#if POL == POL_HORNER
  float y;
  y = a32[9] + x * a32[10];
  y = a32[8] + x * y;
  y = a32[7] + x * y;
  y = a32[6] + x * y;
  y = a32[5] + x * y;
  y = a32[4] + x * y;
  y = a32[3] + x * y;
  y = a32[2] + x * y;
  y = a32[1] + x * y;
  return a32[0] + x * y;
#elif POL == POL_ESTRIN
  float y, y2, y3, y4, x2, x4;
  x2 = x * x;
  x4 = x2 * x2;
  y3 = a32[6] + x4 * a32[10];
  y2 = a32[5] + x4 * a32[9];
  y = a32[4] + x4 * a32[8];
  y4 = a32[3] + x4 * a32[7];
  y3 = a32[2] + x4 * y3;
  y2 = a32[1] + x4 * y2;
  y = a32[0] + x4 * y;
  y2 = y2 + x2 * y4;
  y = y + x2 * y3;
  return y + x2 * y2;
#endif
}

static inline float
pol11_f32 (const float x)
{
#if POL == POL_HORNER
  float y;
  y = a32[10] + x * a32[11];
  y = a32[9] + x * y;
  y = a32[8] + x * y;
  y = a32[7] + x * y;
  y = a32[6] + x * y;
  y = a32[5] + x * y;
  y = a32[4] + x * y;
  y = a32[3] + x * y;
  y = a32[2] + x * y;
  y = a32[1] + x * y;
  return a32[0] + x * y;
#elif POL == POL_ESTRIN
  float y, y2, y3, y4, x2, x4;
  x2 = x * x;
  x4 = x2 * x2;
  y4 = a32[7] + x4 * a32[11];
  y3 = a32[6] + x4 * a32[10];
  y2 = a32[5] + x4 * a32[9];
  y = a32[4] + x4 * a32[8];
  y4 = a32[3] + x4 * y4;
  y3 = a32[2] + x4 * y3;
  y2 = a32[1] + x4 * y2;
  y = a32[0] + x4 * y;
  y2 = y2 + x2 * y4;
  y = y + x2 * y3;
  return y + x2 * y2;
#endif
}

static inline float
pol12_f32 (const float x)
{
#if POL == POL_HORNER
  float y;
  y = a32[11] + x * a32[12];
  y = a32[10] + x * y;
  y = a32[9] + x * y;
  y = a32[8] + x * y;
  y = a32[7] + x * y;
  y = a32[6] + x * y;
  y = a32[5] + x * y;
  y = a32[4] + x * y;
  y = a32[3] + x * y;
  y = a32[2] + x * y;
  y = a32[1] + x * y;
  return a32[0] + x * y;
#elif POL == POL_ESTRIN
  float y, y2, y3, y4, x2, x4;
  x2 = x * x;
  x4 = x2 * x2;
  y = a32[8] + x4 * a32[12];
  y4 = a32[7] + x4 * a32[11];
  y3 = a32[6] + x4 * a32[10];
  y2 = a32[5] + x4 * a32[9];
  y = a32[4] + x4 * y;
  y4 = a32[3] + x4 * y4;
  y3 = a32[2] + x4 * y3;
  y2 = a32[1] + x4 * y2;
  y = a32[0] + x4 * y;
  y2 = y2 + x2 * y4;
  y = y + x2 * y3;
  return y + x2 * y2;
#endif
}

static inline float
pol13_f32 (const float x)
{
#if POL == POL_HORNER
  float y;
  y = a32[12] + x * a32[13];
  y = a32[11] + x * y;
  y = a32[10] + x * y;
  y = a32[9] + x * y;
  y = a32[8] + x * y;
  y = a32[7] + x * y;
  y = a32[6] + x * y;
  y = a32[5] + x * y;
  y = a32[4] + x * y;
  y = a32[3] + x * y;
  y = a32[2] + x * y;
  y = a32[1] + x * y;
  return a32[0] + x * y;
#elif POL == POL_ESTRIN
  float y, y2, y3, y4, x2, x4;
  x2 = x * x;
  x4 = x2 * x2;
  y2 = a32[9] + x4 * a32[13];
  y = a32[8] + x4 * a32[12];
  y4 = a32[7] + x4 * a32[11];
  y3 = a32[6] + x4 * a32[10];
  y2 = a32[5] + x4 * y2;
  y = a32[4] + x4 * y;
  y4 = a32[3] + x4 * y4;
  y3 = a32[2] + x4 * y3;
  y2 = a32[1] + x4 * y2;
  y = a32[0] + x4 * y;
  y2 = y2 + x2 * y4;
  y = y + x2 * y3;
  return y + x2 * y2;
#endif
}

static inline float
pol14_f32 (const float x)
{
#if POL == POL_HORNER
  float y;
  y = a32[13] + x * a32[14];
  y = a32[12] + x * y;
  y = a32[11] + x * y;
  y = a32[10] + x * y;
  y = a32[9] + x * y;
  y = a32[8] + x * y;
  y = a32[7] + x * y;
  y = a32[6] + x * y;
  y = a32[5] + x * y;
  y = a32[4] + x * y;
  y = a32[3] + x * y;
  y = a32[2] + x * y;
  y = a32[1] + x * y;
  return a32[0] + x * y;
#elif POL == POL_ESTRIN
  float y, y2, y3, y4, x2, x4;
  x2 = x * x;
  x4 = x2 * x2;
  y3 = a32[10] + x4 * a32[14];
  y2 = a32[9] + x4 * a32[13];
  y = a32[8] + x4 * a32[12];
  y4 = a32[7] + x4 * a32[11];
  y3 = a32[6] + x4 * y3;
  y2 = a32[5] + x4 * y2;
  y = a32[4] + x4 * y;
  y4 = a32[3] + x4 * y4;
  y3 = a32[2] + x4 * y3;
  y2 = a32[1] + x4 * y2;
  y = a32[0] + x4 * y;
  y2 = y2 + x2 * y4;
  y = y + x2 * y3;
  return y + x2 * y2;
#endif
}

static inline float
pol15_f32 (const float x)
{
#if POL == POL_HORNER
  float y;
  y = a32[14] + x * a32[15];
  y = a32[13] + x * y;
  y = a32[12] + x * y;
  y = a32[11] + x * y;
  y = a32[10] + x * y;
  y = a32[9] + x * y;
  y = a32[8] + x * y;
  y = a32[7] + x * y;
  y = a32[6] + x * y;
  y = a32[5] + x * y;
  y = a32[4] + x * y;
  y = a32[3] + x * y;
  y = a32[2] + x * y;
  y = a32[1] + x * y;
  return a32[0] + x * y;
#elif POL == POL_ESTRIN
  float y, y2, y3, y4, x2, x4;
  x2 = x * x;
  x4 = x2 * x2;
  y4 = a32[11] + x4 * a32[15];
  y3 = a32[10] + x4 * a32[14];
  y2 = a32[9] + x4 * a32[13];
  y = a32[8] + x4 * a32[12];
  y4 = a32[7] + x4 * y4;
  y3 = a32[6] + x4 * y3;
  y2 = a32[5] + x4 * y2;
  y = a32[4] + x4 * y;
  y4 = a32[3] + x4 * y4;
  y3 = a32[2] + x4 * y3;
  y2 = a32[1] + x4 * y2;
  y = a32[0] + x4 * y;
  y2 = y2 + x2 * y4;
  y = y + x2 * y3;
  return y + x2 * y2;
#endif
}

static inline float
f32_pow (const float x)
{
  return powf (x, M_PIf);
}

static inline float
f32_pow_jbm (const float x)
{
  return jbm_f32_pow (x, M_PIf);
}

static inline float
f32 (unsigned int type, float x)
{
  switch (type)
    {
    case TYPE_ADD:
      return add_f32 (x);
    case TYPE_SUB:
      return sub_f32 (x);
    case TYPE_MUL:
      return mul_f32 (x);
    case TYPE_DIV:
      return div_f32 (x);
    case TYPE_SQRT:
      return sqrtf (x);
    case TYPE_MAX:
      return max_f32 (x);
    case TYPE_MIN:
      return min_f32 (x);
    case TYPE_ROUND:
      return roundf (x);
    case TYPE_FLOOR:
      return floorf (x);
    case TYPE_CEIL:
      return ceilf (x);
    case TYPE_TRUNC:
      return truncf (x);
    case TYPE_ABS:
      return fabsf (x);
    case TYPE_MOD:
      return f32_mod (x);
    case TYPE_EXP2:
      return exp2f (x);
    case TYPE_EXP:
      return expf (x);
    case TYPE_EXP10:
      return exp10f (x);
    case TYPE_EXPM1:
      return expm1f (x);
    case TYPE_LOG2:
      return log2f (x);
    case TYPE_LOG:
      return logf (x);
    case TYPE_LOG10:
      return log10f (x);
    case TYPE_POW:
      return f32_pow (x);
    case TYPE_CBRT:
      return cbrtf (x);
    case TYPE_SIN:
      return sinf (x);
    case TYPE_COS:
      return cosf (x);
    case TYPE_TAN:
      return tanf (x);
    case TYPE_ATAN:
      return atanf (x);
    case TYPE_ASIN:
      return asinf (x);
    case TYPE_ACOS:
      return acosf (x);
    case TYPE_SINH:
      return sinhf (x);
    case TYPE_COSH:
      return coshf (x);
    case TYPE_TANH:
      return tanhf (x);
    case TYPE_ERF:
      return erff (x);
    case TYPE_ERFC:
      return erfcf (x);
    case TYPE_JBM_ABS:
      return jbm_f32_abs (x);
    case TYPE_JBM_MOD:
      return f32_mod_jbm (x);
    case TYPE_JBM_EXP2:
      return jbm_f32_exp2 (x);
    case TYPE_JBM_EXP:
      return jbm_f32_exp (x);
    case TYPE_JBM_EXP10:
      return jbm_f32_exp10 (x);
    case TYPE_JBM_EXPM1:
      return jbm_f32_expm1 (x);
    case TYPE_JBM_LOG2:
      return jbm_f32_log2 (x);
    case TYPE_JBM_LOG:
      return jbm_f32_log (x);
    case TYPE_JBM_LOG10:
      return jbm_f32_log10 (x);
    case TYPE_JBM_POW:
      return f32_pow_jbm (x);
    case TYPE_JBM_CBRT:
      return jbm_f32_cbrt (x);
    case TYPE_JBM_SIN:
      return jbm_f32_sin (x);
    case TYPE_JBM_COS:
      return jbm_f32_cos (x);
    case TYPE_JBM_TAN:
      return jbm_f32_tan (x);
    case TYPE_JBM_ATAN:
      return jbm_f32_atan (x);
    case TYPE_JBM_ASIN:
      return jbm_f32_asin (x);
    case TYPE_JBM_ACOS:
      return jbm_f32_acos (x);
    case TYPE_JBM_SINH:
      return jbm_f32_sinh (x);
    case TYPE_JBM_COSH:
      return jbm_f32_cosh (x);
    case TYPE_JBM_TANH:
      return jbm_f32_tanh (x);
    case TYPE_JBM_ERF:
      return jbm_f32_erf (x);
    case TYPE_JBM_ERFC:
      return jbm_f32_erfc (x);
    case TYPE_JBM_POL1:
      return pol1_f32 (x);
    case TYPE_JBM_POL2:
      return pol2_f32 (x);
    case TYPE_JBM_POL3:
      return pol3_f32 (x);
    case TYPE_JBM_POL4:
      return pol4_f32 (x);
    case TYPE_JBM_POL5:
      return pol5_f32 (x);
    case TYPE_JBM_POL6:
      return pol6_f32 (x);
    case TYPE_JBM_POL7:
      return pol7_f32 (x);
    case TYPE_JBM_POL8:
      return pol8_f32 (x);
    case TYPE_JBM_POL9:
      return pol9_f32 (x);
    case TYPE_JBM_POL10:
      return pol10_f32 (x);
    case TYPE_JBM_POL11:
      return pol11_f32 (x);
    case TYPE_JBM_POL12:
      return pol12_f32 (x);
    case TYPE_JBM_POL13:
      return pol13_f32 (x);
    case TYPE_JBM_POL14:
      return pol14_f32 (x);
    case TYPE_JBM_POL15:
      return pol15_f32 (x);
    }
  return 0.f;
}

static inline void
init_f32 (void *data, void *user_data __attribute__((unused)))
{
  Parallel_f32 *p;
  float *x;
  const double *r;
  double xmin, xmax, tau;
  unsigned long int i, imin, imax;
  p = (Parallel_f32 *) data;
  x = p->x;
  r = p->r;
  imin = p->imin;
  imax = p->imax;
  xmin = p->xmin;
  xmax = p->xmax;
  tau = 10.;
  switch (p->type)
    {
    case TYPE_EXP2:
    case TYPE_EXP:
    case TYPE_EXP10:
    case TYPE_EXPM1:
    case TYPE_ATAN:
    case TYPE_SINH:
    case TYPE_COSH:
    case TYPE_TANH:
    case TYPE_ERF:
    case TYPE_ERFC:
    case TYPE_JBM_EXP2:
    case TYPE_JBM_EXP:
    case TYPE_JBM_EXP10:
    case TYPE_JBM_EXPM1:
    case TYPE_JBM_ATAN:
    case TYPE_JBM_SINH:
    case TYPE_JBM_COSH:
    case TYPE_JBM_TANH:
    case TYPE_JBM_ERF:
    case TYPE_JBM_ERFC:
      BUCLE_INIT (float, normal_f64);
      break;
    case TYPE_LOG2:
    case TYPE_LOG:
    case TYPE_LOG10:
    case TYPE_JBM_LOG2:
    case TYPE_JBM_LOG:
    case TYPE_JBM_LOG10:
      BUCLE_INIT (float, loguniform_f64);
      break;
    case TYPE_ADD:
    case TYPE_SUB:
    case TYPE_MUL:
    case TYPE_DIV:
    case TYPE_SQRT:
    case TYPE_MAX:
    case TYPE_MIN:
    case TYPE_ROUND:
    case TYPE_FLOOR:
    case TYPE_CEIL:
    case TYPE_TRUNC:
    case TYPE_ABS:
    case TYPE_MOD:
    case TYPE_POW:
    case TYPE_CBRT:
    case TYPE_SIN:
    case TYPE_COS:
    case TYPE_TAN:
    case TYPE_ASIN:
    case TYPE_ACOS:
    case TYPE_JBM_ABS:
    case TYPE_JBM_MOD:
    case TYPE_JBM_POW:
    case TYPE_JBM_CBRT:
    case TYPE_JBM_SIN:
    case TYPE_JBM_COS:
    case TYPE_JBM_TAN:
    case TYPE_JBM_ASIN:
    case TYPE_JBM_ACOS:
    case TYPE_JBM_POL1:
    case TYPE_JBM_POL2:
    case TYPE_JBM_POL3:
    case TYPE_JBM_POL4:
    case TYPE_JBM_POL5:
    case TYPE_JBM_POL6:
    case TYPE_JBM_POL7:
    case TYPE_JBM_POL8:
    case TYPE_JBM_POL9:
    case TYPE_JBM_POL10:
    case TYPE_JBM_POL11:
    case TYPE_JBM_POL12:
    case TYPE_JBM_POL13:
    case TYPE_JBM_POL14:
    case TYPE_JBM_POL15:
    default:
      BUCLE_INIT (float, uniform_f64);
    }
}

static inline void
thread_f32 (void *data, void *user_data __attribute__((unused)))
{
  Parallel_f32 *p;
  float *x, *y;
  unsigned long int i, imin, imax;
  p = (Parallel_f32 *) data;
  x = p->x;
  y = p->y;
  imin = p->imin;
  imax = p->imax;
  switch (p->type)
    {
    case TYPE_ADD:
      BUCLE_FUNCTION (add_f32);
      break;
    case TYPE_SUB:
      BUCLE_FUNCTION (sub_f32);
      break;
    case TYPE_MUL:
      BUCLE_FUNCTION (mul_f32);
      break;
    case TYPE_DIV:
      BUCLE_FUNCTION (div_f32);
      break;
    case TYPE_SQRT:
      BUCLE_FUNCTION (sqrtf);
      break;
    case TYPE_MAX:
      BUCLE_FUNCTION (max_f32);
      break;
    case TYPE_MIN:
      BUCLE_FUNCTION (min_f32);
      break;
    case TYPE_ROUND:
      BUCLE_FUNCTION (roundf);
      break;
    case TYPE_FLOOR:
      BUCLE_FUNCTION (floorf);
      break;
    case TYPE_CEIL:
      BUCLE_FUNCTION (ceilf);
      break;
    case TYPE_TRUNC:
      BUCLE_FUNCTION (truncf);
      break;
    case TYPE_ABS:
      BUCLE_FUNCTION (fabsf);
      break;
    case TYPE_MOD:
      BUCLE_FUNCTION (f32_mod);
      break;
    case TYPE_EXP2:
      BUCLE_FUNCTION (exp2f);
      break;
    case TYPE_EXP:
      BUCLE_FUNCTION (expf);
      break;
    case TYPE_EXP10:
      BUCLE_FUNCTION (exp10f);
      break;
    case TYPE_EXPM1:
      BUCLE_FUNCTION (expm1f);
      break;
    case TYPE_LOG2:
      BUCLE_FUNCTION (log2f);
      break;
    case TYPE_LOG:
      BUCLE_FUNCTION (logf);
      break;
    case TYPE_LOG10:
      BUCLE_FUNCTION (log10f);
      break;
    case TYPE_POW:
      BUCLE_FUNCTION (f32_pow);
      break;
    case TYPE_CBRT:
      BUCLE_FUNCTION (cbrtf);
      break;
    case TYPE_SIN:
      BUCLE_FUNCTION (sinf);
      break;
    case TYPE_COS:
      BUCLE_FUNCTION (cosf);
      break;
    case TYPE_TAN:
      BUCLE_FUNCTION (tanf);
      break;
    case TYPE_ATAN:
      BUCLE_FUNCTION (atanf);
      break;
    case TYPE_ASIN:
      BUCLE_FUNCTION (asinf);
      break;
    case TYPE_ACOS:
      BUCLE_FUNCTION (acosf);
      break;
    case TYPE_SINH:
      BUCLE_FUNCTION (sinhf);
      break;
    case TYPE_COSH:
      BUCLE_FUNCTION (coshf);
      break;
    case TYPE_TANH:
      BUCLE_FUNCTION (tanhf);
      break;
    case TYPE_ERF:
      BUCLE_FUNCTION (erff);
      break;
    case TYPE_ERFC:
      BUCLE_FUNCTION (erfcf);
      break;
    case TYPE_JBM_ABS:
      BUCLE_FUNCTION (jbm_f32_abs);
      break;
    case TYPE_JBM_MOD:
      BUCLE_FUNCTION (f32_mod_jbm);
      break;
    case TYPE_JBM_EXP2:
      BUCLE_FUNCTION (jbm_f32_exp2);
      break;
    case TYPE_JBM_EXP:
      BUCLE_FUNCTION (jbm_f32_exp);
      break;
    case TYPE_JBM_EXP10:
      BUCLE_FUNCTION (jbm_f32_exp10);
      break;
    case TYPE_JBM_EXPM1:
      BUCLE_FUNCTION (jbm_f32_expm1);
      break;
    case TYPE_JBM_LOG2:
      BUCLE_FUNCTION (jbm_f32_log2);
      break;
    case TYPE_JBM_LOG:
      BUCLE_FUNCTION (jbm_f32_log);
      break;
    case TYPE_JBM_LOG10:
      BUCLE_FUNCTION (jbm_f32_log10);
      break;
    case TYPE_JBM_POW:
      BUCLE_FUNCTION (f32_pow_jbm);
      break;
    case TYPE_JBM_CBRT:
      BUCLE_FUNCTION (jbm_f32_cbrt);
      break;
    case TYPE_JBM_SIN:
      BUCLE_FUNCTION (jbm_f32_sin);
      break;
    case TYPE_JBM_COS:
      BUCLE_FUNCTION (jbm_f32_cos);
      break;
    case TYPE_JBM_TAN:
      BUCLE_FUNCTION (jbm_f32_tan);
      break;
    case TYPE_JBM_ATAN:
      BUCLE_FUNCTION (jbm_f32_atan);
      break;
    case TYPE_JBM_ASIN:
      BUCLE_FUNCTION (jbm_f32_asin);
      break;
    case TYPE_JBM_ACOS:
      BUCLE_FUNCTION (jbm_f32_acos);
      break;
    case TYPE_JBM_SINH:
      BUCLE_FUNCTION (jbm_f32_sinh);
      break;
    case TYPE_JBM_COSH:
      BUCLE_FUNCTION (jbm_f32_cosh);
      break;
    case TYPE_JBM_TANH:
      BUCLE_FUNCTION (jbm_f32_tanh);
      break;
    case TYPE_JBM_ERF:
      BUCLE_FUNCTION (jbm_f32_erf);
      break;
    case TYPE_JBM_ERFC:
      BUCLE_FUNCTION (jbm_f32_erfc);
      break;
    case TYPE_JBM_POL1:
      BUCLE_FUNCTION (pol1_f32);
      break;
    case TYPE_JBM_POL2:
      BUCLE_FUNCTION (pol2_f32);
      break;
    case TYPE_JBM_POL3:
      BUCLE_FUNCTION (pol3_f32);
      break;
    case TYPE_JBM_POL4:
      BUCLE_FUNCTION (pol4_f32);
      break;
    case TYPE_JBM_POL5:
      BUCLE_FUNCTION (pol5_f32);
      break;
    case TYPE_JBM_POL6:
      BUCLE_FUNCTION (pol6_f32);
      break;
    case TYPE_JBM_POL7:
      BUCLE_FUNCTION (pol7_f32);
      break;
    case TYPE_JBM_POL8:
      BUCLE_FUNCTION (pol8_f32);
      break;
    case TYPE_JBM_POL9:
      BUCLE_FUNCTION (pol9_f32);
      break;
    case TYPE_JBM_POL10:
      BUCLE_FUNCTION (pol10_f32);
      break;
    case TYPE_JBM_POL11:
      BUCLE_FUNCTION (pol11_f32);
      break;
    case TYPE_JBM_POL12:
      BUCLE_FUNCTION (pol12_f32);
      break;
    case TYPE_JBM_POL13:
      BUCLE_FUNCTION (pol13_f32);
      break;
    case TYPE_JBM_POL14:
      BUCLE_FUNCTION (pol14_f32);
      break;
    case TYPE_JBM_POL15:
      BUCLE_FUNCTION (pol15_f32);
      break;
    }
}

// double functions

static inline double
add_f64 (const double x)
{
  return x + M_PI;
}

static inline double
sub_f64 (const double x)
{
  return x - M_PI;
}

static inline double
mul_f64 (const double x)
{
  return x * M_PI;
}

static inline double
div_f64 (const double x)
{
  return x / M_PI;
}

static inline double
max_f64 (const double x)
{
  return fmax (x, M_PI);
}

static inline double
min_f64 (const double x)
{
  return fmin (x, M_PI);
}

static inline double
f64_mod (const double x)
{
  return fmod (x, M_PI);
}

static inline double
f64_mod_jbm (const double x)
{
  return jbm_f64_mod (x, M_PI);
}

static inline double
pol1_f64 (const double x)
{
  return a64[0] + x * a64[1];
}

static inline double
pol2_f64 (const double x)
{
  double y;
  y = a64[1] + x * a64[2];
  return a64[0] + x * y;
}

static inline double
pol3_f64 (const double x)
{
#if POL == POL_HORNER
  double y;
  y = a64[2] + x * a64[3];
  y = a64[1] + x * y;
  return a64[0] + x * y;
#elif POL == POL_ESTRIN
  double y, y2, x2;
  x2 = x * x;
  y2 = a64[1] + x2 * a64[3];
  y = a64[0] + x2 * a64[2];
  return y + x * y2;
#endif
}

static inline double
pol4_f64 (const double x)
{
#if POL == POL_HORNER
  double y;
  y = a64[3] + x * a64[4];
  y = a64[2] + x * y;
  y = a64[1] + x * y;
  return a64[0] + x * y;
#elif POL == POL_ESTRIN
  double y, y2, x2;
  x2 = x * x;
  y = a64[2] + x2 * a64[4];
  y2 = a64[1] + x2 * a64[3];
  y = a64[0] + x2 * y;
  return y + x * y2;
#endif
}

static inline double
pol5_f64 (const double x)
{
#if POL == POL_HORNER
  double y;
  y = a64[4] + x * a64[5];
  y = a64[3] + x * y;
  y = a64[2] + x * y;
  y = a64[1] + x * y;
  return a64[0] + x * y;
#elif POL == POL_ESTRIN
  double y, y2, x2;
  x2 = x * x;
  y2 = a64[3] + x2 * a64[5];
  y = a64[2] + x2 * a64[4];
  y2 = a64[1] + x2 * y2;
  y = a64[0] + x2 * y;
  return y + x * y2;
#endif
}

static inline double
pol6_f64 (const double x)
{
#if POL == POL_HORNER
  double y;
  y = a64[5] + x * a64[6];
  y = a64[4] + x * y;
  y = a64[3] + x * y;
  y = a64[2] + x * y;
  y = a64[1] + x * y;
  return a64[0] + x * y;
#elif POL == POL_ESTRIN
  double y, y2, x2;
  x2 = x * x;
  y = a64[4] + x2 * a64[6];
  y2 = a64[3] + x2 * a64[5];
  y = a64[2] + x2 * y;
  y2 = a64[1] + x2 * y2;
  y = a64[0] + x2 * y;
  return y + x * y2;
#endif
}

static inline double
pol7_f64 (const double x)
{
#if POL == POL_HORNER
  double y;
  y = a64[6] + x * a64[7];
  y = a64[5] + x * y;
  y = a64[4] + x * y;
  y = a64[3] + x * y;
  y = a64[2] + x * y;
  y = a64[1] + x * y;
  return a64[0] + x * y;
#elif POL == POL_ESTRIN
  double y, y2, x2;
  x2 = x * x;
  y2 = a64[5] + x2 * a64[7];
  y = a64[4] + x2 * a64[6];
  y2 = a64[3] + x2 * y2;
  y = a64[2] + x2 * y;
  y2 = a64[1] + x2 * y2;
  y = a64[0] + x2 * y;
  return y + x * y2;
#endif
}

static inline double
pol8_f64 (const double x)
{
#if POL == POL_HORNER
  double y;
  y = a64[7] + x * a64[8];
  y = a64[6] + x * y;
  y = a64[5] + x * y;
  y = a64[4] + x * y;
  y = a64[3] + x * y;
  y = a64[2] + x * y;
  y = a64[1] + x * y;
  return a64[0] + x * y;
#elif POL == POL_ESTRIN
  double y, y2, y3, y4, x2, x4;
  x2 = x * x;
  x4 = x2 * x2;
  y = a64[4] + x4 * a64[8];
  y4 = a64[3] + x4 * a64[7];
  y3 = a64[2] + x4 * a64[6];
  y2 = a64[1] + x4 * a64[5];
  y = a64[0] + x4 * y;
  y2 = y2 + x2 * y4;
  y = y + x2 * y3;
  return y + x2 * y2;
#endif
}

static inline double
pol9_f64 (const double x)
{
#if POL == POL_HORNER
  double y;
  y = a64[8] + x * a64[9];
  y = a64[7] + x * y;
  y = a64[6] + x * y;
  y = a64[5] + x * y;
  y = a64[4] + x * y;
  y = a64[3] + x * y;
  y = a64[2] + x * y;
  y = a64[1] + x * y;
  return a64[0] + x * y;
#elif POL == POL_ESTRIN
  double y, y2, y3, y4, x2, x4;
  x2 = x * x;
  x4 = x2 * x2;
  y2 = a64[5] + x4 * a64[9];
  y = a64[4] + x4 * a64[8];
  y4 = a64[3] + x4 * a64[7];
  y3 = a64[2] + x4 * a64[6];
  y2 = a64[1] + x4 * y2;
  y = a64[0] + x4 * y;
  y2 = y2 + x2 * y4;
  y = y + x2 * y3;
  return y + x2 * y2;
#endif
}

static inline double
pol10_f64 (const double x)
{
#if POL == POL_HORNER
  double y;
  y = a64[9] + x * a64[10];
  y = a64[8] + x * y;
  y = a64[7] + x * y;
  y = a64[6] + x * y;
  y = a64[5] + x * y;
  y = a64[4] + x * y;
  y = a64[3] + x * y;
  y = a64[2] + x * y;
  y = a64[1] + x * y;
  return a64[0] + x * y;
#elif POL == POL_ESTRIN
  double y, y2, y3, y4, x2, x4;
  x2 = x * x;
  x4 = x2 * x2;
  y3 = a64[6] + x4 * a64[10];
  y2 = a64[5] + x4 * a64[9];
  y = a64[4] + x4 * a64[8];
  y4 = a64[3] + x4 * a64[7];
  y3 = a64[2] + x4 * y3;
  y2 = a64[1] + x4 * y2;
  y = a64[0] + x4 * y;
  y2 = y2 + x2 * y4;
  y = y + x2 * y3;
  return y + x2 * y2;
#endif
}

static inline double
pol11_f64 (const double x)
{
#if POL == POL_HORNER
  double y;
  y = a64[10] + x * a64[11];
  y = a64[9] + x * y;
  y = a64[8] + x * y;
  y = a64[7] + x * y;
  y = a64[6] + x * y;
  y = a64[5] + x * y;
  y = a64[4] + x * y;
  y = a64[3] + x * y;
  y = a64[2] + x * y;
  y = a64[1] + x * y;
  return a64[0] + x * y;
#elif POL == POL_ESTRIN
  double y, y2, y3, y4, x2, x4;
  x2 = x * x;
  x4 = x2 * x2;
  y4 = a64[7] + x4 * a64[11];
  y3 = a64[6] + x4 * a64[10];
  y2 = a64[5] + x4 * a64[9];
  y = a64[4] + x4 * a64[8];
  y4 = a64[3] + x4 * y4;
  y3 = a64[2] + x4 * y3;
  y2 = a64[1] + x4 * y2;
  y = a64[0] + x4 * y;
  y2 = y2 + x2 * y4;
  y = y + x2 * y3;
  return y + x2 * y2;
#endif
}

static inline double
pol12_f64 (const double x)
{
#if POL == POL_HORNER
  double y;
  y = a64[11] + x * a64[12];
  y = a64[10] + x * y;
  y = a64[9] + x * y;
  y = a64[8] + x * y;
  y = a64[7] + x * y;
  y = a64[6] + x * y;
  y = a64[5] + x * y;
  y = a64[4] + x * y;
  y = a64[3] + x * y;
  y = a64[2] + x * y;
  y = a64[1] + x * y;
  return a64[0] + x * y;
#elif POL == POL_ESTRIN
  double y, y2, y3, y4, x2, x4;
  x2 = x * x;
  x4 = x2 * x2;
  y = a64[8] + x4 * a64[12];
  y4 = a64[7] + x4 * a64[11];
  y3 = a64[6] + x4 * a64[10];
  y2 = a64[5] + x4 * a64[9];
  y = a64[4] + x4 * y;
  y4 = a64[3] + x4 * y4;
  y3 = a64[2] + x4 * y3;
  y2 = a64[1] + x4 * y2;
  y = a64[0] + x4 * y;
  y2 = y2 + x2 * y4;
  y = y + x2 * y3;
  return y + x2 * y2;
#endif
}

static inline double
pol13_f64 (const double x)
{
#if POL == POL_HORNER
  double y;
  y = a64[12] + x * a64[13];
  y = a64[11] + x * y;
  y = a64[10] + x * y;
  y = a64[9] + x * y;
  y = a64[8] + x * y;
  y = a64[7] + x * y;
  y = a64[6] + x * y;
  y = a64[5] + x * y;
  y = a64[4] + x * y;
  y = a64[3] + x * y;
  y = a64[2] + x * y;
  y = a64[1] + x * y;
  return a64[0] + x * y;
#elif POL == POL_ESTRIN
  double y, y2, y3, y4, x2, x4;
  x2 = x * x;
  x4 = x2 * x2;
  y2 = a64[9] + x4 * a64[13];
  y = a64[8] + x4 * a64[12];
  y4 = a64[7] + x4 * a64[11];
  y3 = a64[6] + x4 * a64[10];
  y2 = a64[5] + x4 * y2;
  y = a64[4] + x4 * y;
  y4 = a64[3] + x4 * y4;
  y3 = a64[2] + x4 * y3;
  y2 = a64[1] + x4 * y2;
  y = a64[0] + x4 * y;
  y2 = y2 + x2 * y4;
  y = y + x2 * y3;
  return y + x2 * y2;
#endif
}

static inline double
pol14_f64 (const double x)
{
#if POL == POL_HORNER
  double y;
  y = a64[13] + x * a64[14];
  y = a64[12] + x * y;
  y = a64[11] + x * y;
  y = a64[10] + x * y;
  y = a64[9] + x * y;
  y = a64[8] + x * y;
  y = a64[7] + x * y;
  y = a64[6] + x * y;
  y = a64[5] + x * y;
  y = a64[4] + x * y;
  y = a64[3] + x * y;
  y = a64[2] + x * y;
  y = a64[1] + x * y;
  return a64[0] + x * y;
#elif POL == POL_ESTRIN
  double y, y2, y3, y4, x2, x4;
  x2 = x * x;
  x4 = x2 * x2;
  y3 = a64[10] + x4 * a64[14];
  y2 = a64[9] + x4 * a64[13];
  y = a64[8] + x4 * a64[12];
  y4 = a64[7] + x4 * a64[11];
  y3 = a64[6] + x4 * y3;
  y2 = a64[5] + x4 * y2;
  y = a64[4] + x4 * y;
  y4 = a64[3] + x4 * y4;
  y3 = a64[2] + x4 * y3;
  y2 = a64[1] + x4 * y2;
  y = a64[0] + x4 * y;
  y2 = y2 + x2 * y4;
  y = y + x2 * y3;
  return y + x2 * y2;
#endif
}

static inline double
pol15_f64 (const double x)
{
#if POL == POL_HORNER
  double y;
  y = a64[14] + x * a64[15];
  y = a64[13] + x * y;
  y = a64[12] + x * y;
  y = a64[11] + x * y;
  y = a64[10] + x * y;
  y = a64[9] + x * y;
  y = a64[8] + x * y;
  y = a64[7] + x * y;
  y = a64[6] + x * y;
  y = a64[5] + x * y;
  y = a64[4] + x * y;
  y = a64[3] + x * y;
  y = a64[2] + x * y;
  y = a64[1] + x * y;
  return a64[0] + x * y;
#elif POL == POL_ESTRIN
  double y, y2, y3, y4, x2, x4;
  x2 = x * x;
  x4 = x2 * x2;
  y4 = a64[11] + x4 * a64[15];
  y3 = a64[10] + x4 * a64[14];
  y2 = a64[9] + x4 * a64[13];
  y = a64[8] + x4 * a64[12];
  y4 = a64[7] + x4 * y4;
  y3 = a64[6] + x4 * y3;
  y2 = a64[5] + x4 * y2;
  y = a64[4] + x4 * y;
  y4 = a64[3] + x4 * y4;
  y3 = a64[2] + x4 * y3;
  y2 = a64[1] + x4 * y2;
  y = a64[0] + x4 * y;
  y2 = y2 + x2 * y4;
  y = y + x2 * y3;
  return y + x2 * y2;
#endif
}

static inline double
f64_pow (const double x)
{
  return powf (x, M_PI);
}

static inline double
f64_pow_jbm (const double x)
{
  return jbm_f64_pow (x, M_PI);
}

static inline double
f64 (unsigned int type, double x)
{
  switch (type)
    {
    case TYPE_ADD:
      return add_f64 (x);
    case TYPE_SUB:
      return sub_f64 (x);
    case TYPE_MUL:
      return mul_f64 (x);
    case TYPE_DIV:
      return div_f64 (x);
    case TYPE_SQRT:
      return sqrt (x);
    case TYPE_MAX:
      return max_f64 (x);
    case TYPE_MIN:
      return min_f64 (x);
    case TYPE_ROUND:
      return round (x);
    case TYPE_FLOOR:
      return floor (x);
    case TYPE_CEIL:
      return ceil (x);
    case TYPE_TRUNC:
      return trunc (x);
    case TYPE_ABS:
      return fabs (x);
    case TYPE_MOD:
      return f64_mod (x);
    case TYPE_EXP2:
      return exp2 (x);
    case TYPE_EXP:
      return exp (x);
    case TYPE_EXP10:
      return exp10 (x);
    case TYPE_EXPM1:
      return expm1 (x);
    case TYPE_LOG2:
      return log2 (x);
    case TYPE_LOG:
      return log (x);
    case TYPE_LOG10:
      return log10 (x);
    case TYPE_POW:
      return f64_pow (x);
    case TYPE_CBRT:
      return cbrt (x);
    case TYPE_SIN:
      return sin (x);
    case TYPE_COS:
      return cos (x);
    case TYPE_TAN:
      return tan (x);
    case TYPE_ATAN:
      return atan (x);
    case TYPE_ASIN:
      return asin (x);
    case TYPE_ACOS:
      return acos (x);
    case TYPE_SINH:
      return sinh (x);
    case TYPE_COSH:
      return cosh (x);
    case TYPE_TANH:
      return tanh (x);
    case TYPE_ERF:
      return erf (x);
    case TYPE_ERFC:
      return erfc (x);
    case TYPE_JBM_ABS:
      return jbm_f64_abs (x);
    case TYPE_JBM_MOD:
      return f64_mod_jbm (x);
    case TYPE_JBM_EXP2:
      return jbm_f64_exp2 (x);
    case TYPE_JBM_EXP:
      return jbm_f64_exp (x);
    case TYPE_JBM_EXP10:
      return jbm_f64_exp10 (x);
    case TYPE_JBM_EXPM1:
      return jbm_f64_expm1 (x);
    case TYPE_JBM_LOG2:
      return jbm_f64_log2 (x);
    case TYPE_JBM_LOG:
      return jbm_f64_log (x);
    case TYPE_JBM_LOG10:
      return jbm_f64_log10 (x);
    case TYPE_JBM_POW:
      return f64_pow_jbm (x);
    case TYPE_JBM_CBRT:
      return jbm_f64_cbrt (x);
    case TYPE_JBM_SIN:
      return jbm_f64_sin (x);
    case TYPE_JBM_COS:
      return jbm_f64_cos (x);
    case TYPE_JBM_TAN:
      return jbm_f64_tan (x);
    case TYPE_JBM_ATAN:
      return jbm_f64_atan (x);
    case TYPE_JBM_ASIN:
      return jbm_f64_asin (x);
    case TYPE_JBM_ACOS:
      return jbm_f64_acos (x);
    case TYPE_JBM_SINH:
      return jbm_f64_sinh (x);
    case TYPE_JBM_COSH:
      return jbm_f64_cosh (x);
    case TYPE_JBM_TANH:
      return jbm_f64_tanh (x);
    case TYPE_JBM_ERF:
      return jbm_f64_erf (x);
    case TYPE_JBM_ERFC:
      return jbm_f64_erfc (x);
    case TYPE_JBM_POL1:
      return pol1_f64 (x);
    case TYPE_JBM_POL2:
      return pol2_f64 (x);
    case TYPE_JBM_POL3:
      return pol3_f64 (x);
    case TYPE_JBM_POL4:
      return pol4_f64 (x);
    case TYPE_JBM_POL5:
      return pol5_f64 (x);
    case TYPE_JBM_POL6:
      return pol6_f64 (x);
    case TYPE_JBM_POL7:
      return pol7_f64 (x);
    case TYPE_JBM_POL8:
      return pol8_f64 (x);
    case TYPE_JBM_POL9:
      return pol9_f64 (x);
    case TYPE_JBM_POL10:
      return pol10_f64 (x);
    case TYPE_JBM_POL11:
      return pol11_f64 (x);
    case TYPE_JBM_POL12:
      return pol12_f64 (x);
    case TYPE_JBM_POL13:
      return pol13_f64 (x);
    case TYPE_JBM_POL14:
      return pol14_f64 (x);
    case TYPE_JBM_POL15:
      return pol15_f64 (x);
    }
  return 0.;
}

static inline void
init_f64 (void *data, void *user_data __attribute__((unused)))
{
  Parallel_f64 *p;
  double *x;
  const double *r;
  double xmin, xmax, tau;
  unsigned long int i, imin, imax;
  p = (Parallel_f64 *) data;
  x = p->x;
  r = p->r;
  imin = p->imin;
  imax = p->imax;
  xmin = p->xmin;
  xmax = p->xmax;
  tau = 10.;
  switch (p->type)
    {
    case TYPE_EXP2:
    case TYPE_EXP:
    case TYPE_EXP10:
    case TYPE_EXPM1:
    case TYPE_ATAN:
    case TYPE_SINH:
    case TYPE_COSH:
    case TYPE_TANH:
    case TYPE_ERF:
    case TYPE_ERFC:
    case TYPE_JBM_EXP2:
    case TYPE_JBM_EXP:
    case TYPE_JBM_EXP10:
    case TYPE_JBM_EXPM1:
    case TYPE_JBM_ATAN:
    case TYPE_JBM_SINH:
    case TYPE_JBM_COSH:
    case TYPE_JBM_TANH:
    case TYPE_JBM_ERF:
    case TYPE_JBM_ERFC:
      BUCLE_INIT (double, normal_f64);
      break;
    case TYPE_LOG2:
    case TYPE_LOG:
    case TYPE_LOG10:
    case TYPE_JBM_LOG2:
    case TYPE_JBM_LOG:
    case TYPE_JBM_LOG10:
      BUCLE_INIT (double, loguniform_f64);
      break;
    case TYPE_ADD:
    case TYPE_SUB:
    case TYPE_MUL:
    case TYPE_DIV:
    case TYPE_SQRT:
    case TYPE_MAX:
    case TYPE_MIN:
    case TYPE_ROUND:
    case TYPE_FLOOR:
    case TYPE_CEIL:
    case TYPE_TRUNC:
    case TYPE_ABS:
    case TYPE_MOD:
    case TYPE_POW:
    case TYPE_CBRT:
    case TYPE_SIN:
    case TYPE_COS:
    case TYPE_TAN:
    case TYPE_ASIN:
    case TYPE_ACOS:
    case TYPE_JBM_ABS:
    case TYPE_JBM_MOD:
    case TYPE_JBM_POW:
    case TYPE_JBM_CBRT:
    case TYPE_JBM_SIN:
    case TYPE_JBM_COS:
    case TYPE_JBM_TAN:
    case TYPE_JBM_ASIN:
    case TYPE_JBM_ACOS:
    case TYPE_JBM_POL1:
    case TYPE_JBM_POL2:
    case TYPE_JBM_POL3:
    case TYPE_JBM_POL4:
    case TYPE_JBM_POL5:
    case TYPE_JBM_POL6:
    case TYPE_JBM_POL7:
    case TYPE_JBM_POL8:
    case TYPE_JBM_POL9:
    case TYPE_JBM_POL10:
    case TYPE_JBM_POL11:
    case TYPE_JBM_POL12:
    case TYPE_JBM_POL13:
    case TYPE_JBM_POL14:
    case TYPE_JBM_POL15:
    default:
      BUCLE_INIT (double, uniform_f64);
    }
}

static inline void
thread_f64 (void *data, void *user_data __attribute__((unused)))
{
  Parallel_f64 *p;
  double *x, *y;
  unsigned long int i, imin, imax;
  p = (Parallel_f64 *) data;
  x = p->x;
  y = p->y;
  imin = p->imin;
  imax = p->imax;
  switch (p->type)
    {
    case TYPE_ADD:
      BUCLE_FUNCTION (add_f64);
      break;
    case TYPE_SUB:
      BUCLE_FUNCTION (sub_f64);
      break;
    case TYPE_MUL:
      BUCLE_FUNCTION (mul_f64);
      break;
    case TYPE_DIV:
      BUCLE_FUNCTION (div_f64);
      break;
    case TYPE_SQRT:
      BUCLE_FUNCTION (sqrt);
      break;
    case TYPE_MAX:
      BUCLE_FUNCTION (max_f64);
      break;
    case TYPE_MIN:
      BUCLE_FUNCTION (min_f64);
      break;
    case TYPE_ROUND:
      BUCLE_FUNCTION (round);
      break;
    case TYPE_FLOOR:
      BUCLE_FUNCTION (floor);
      break;
    case TYPE_CEIL:
      BUCLE_FUNCTION (ceil);
      break;
    case TYPE_TRUNC:
      BUCLE_FUNCTION (trunc);
      break;
    case TYPE_ABS:
      BUCLE_FUNCTION (fabs);
      break;
    case TYPE_MOD:
      BUCLE_FUNCTION (f64_mod);
      break;
    case TYPE_EXP2:
      BUCLE_FUNCTION (exp2);
      break;
    case TYPE_EXP:
      BUCLE_FUNCTION (exp);
      break;
    case TYPE_EXP10:
      BUCLE_FUNCTION (exp10);
      break;
    case TYPE_EXPM1:
      BUCLE_FUNCTION (expm1);
      break;
    case TYPE_LOG2:
      BUCLE_FUNCTION (log2);
      break;
    case TYPE_LOG:
      BUCLE_FUNCTION (log);
      break;
    case TYPE_LOG10:
      BUCLE_FUNCTION (log10);
      break;
    case TYPE_POW:
      BUCLE_FUNCTION (f64_pow);
      break;
    case TYPE_CBRT:
      BUCLE_FUNCTION (cbrt);
      break;
    case TYPE_SIN:
      BUCLE_FUNCTION (sin);
      break;
    case TYPE_COS:
      BUCLE_FUNCTION (cos);
      break;
    case TYPE_TAN:
      BUCLE_FUNCTION (tan);
      break;
    case TYPE_ATAN:
      BUCLE_FUNCTION (atan);
      break;
    case TYPE_ASIN:
      BUCLE_FUNCTION (asin);
      break;
    case TYPE_ACOS:
      BUCLE_FUNCTION (acos);
      break;
    case TYPE_SINH:
      BUCLE_FUNCTION (sinh);
      break;
    case TYPE_COSH:
      BUCLE_FUNCTION (cosh);
      break;
    case TYPE_TANH:
      BUCLE_FUNCTION (tanh);
      break;
    case TYPE_ERF:
      BUCLE_FUNCTION (erf);
      break;
    case TYPE_ERFC:
      BUCLE_FUNCTION (erfc);
      break;
    case TYPE_JBM_ABS:
      BUCLE_FUNCTION (jbm_f64_abs);
      break;
    case TYPE_JBM_MOD:
      BUCLE_FUNCTION (f64_mod_jbm);
      break;
    case TYPE_JBM_EXP2:
      BUCLE_FUNCTION (jbm_f64_exp2);
      break;
    case TYPE_JBM_EXP:
      BUCLE_FUNCTION (jbm_f64_exp);
      break;
    case TYPE_JBM_EXP10:
      BUCLE_FUNCTION (jbm_f64_exp10);
      break;
    case TYPE_JBM_EXPM1:
      BUCLE_FUNCTION (jbm_f64_expm1);
      break;
    case TYPE_JBM_LOG2:
      BUCLE_FUNCTION (jbm_f64_log2);
      break;
    case TYPE_JBM_LOG:
      BUCLE_FUNCTION (jbm_f64_log);
      break;
    case TYPE_JBM_LOG10:
      BUCLE_FUNCTION (jbm_f64_log10);
      break;
    case TYPE_JBM_POW:
      BUCLE_FUNCTION (f64_pow_jbm);
      break;
    case TYPE_JBM_CBRT:
      BUCLE_FUNCTION (jbm_f64_cbrt);
      break;
    case TYPE_JBM_SIN:
      BUCLE_FUNCTION (jbm_f64_sin);
      break;
    case TYPE_JBM_COS:
      BUCLE_FUNCTION (jbm_f64_cos);
      break;
    case TYPE_JBM_TAN:
      BUCLE_FUNCTION (jbm_f64_tan);
      break;
    case TYPE_JBM_ATAN:
      BUCLE_FUNCTION (jbm_f64_atan);
      break;
    case TYPE_JBM_ASIN:
      BUCLE_FUNCTION (jbm_f64_asin);
      break;
    case TYPE_JBM_ACOS:
      BUCLE_FUNCTION (jbm_f64_acos);
      break;
    case TYPE_JBM_SINH:
      BUCLE_FUNCTION (jbm_f64_sinh);
      break;
    case TYPE_JBM_COSH:
      BUCLE_FUNCTION (jbm_f64_cosh);
      break;
    case TYPE_JBM_TANH:
      BUCLE_FUNCTION (jbm_f64_tanh);
      break;
    case TYPE_JBM_ERF:
      BUCLE_FUNCTION (jbm_f64_erf);
      break;
    case TYPE_JBM_ERFC:
      BUCLE_FUNCTION (jbm_f64_erfc);
      break;
    case TYPE_JBM_POL1:
      BUCLE_FUNCTION (pol1_f64);
      break;
    case TYPE_JBM_POL2:
      BUCLE_FUNCTION (pol2_f64);
      break;
    case TYPE_JBM_POL3:
      BUCLE_FUNCTION (pol3_f64);
      break;
    case TYPE_JBM_POL4:
      BUCLE_FUNCTION (pol4_f64);
      break;
    case TYPE_JBM_POL5:
      BUCLE_FUNCTION (pol5_f64);
      break;
    case TYPE_JBM_POL6:
      BUCLE_FUNCTION (pol6_f64);
      break;
    case TYPE_JBM_POL7:
      BUCLE_FUNCTION (pol7_f64);
      break;
    case TYPE_JBM_POL8:
      BUCLE_FUNCTION (pol8_f64);
      break;
    case TYPE_JBM_POL9:
      BUCLE_FUNCTION (pol9_f64);
      break;
    case TYPE_JBM_POL10:
      BUCLE_FUNCTION (pol10_f64);
      break;
    case TYPE_JBM_POL11:
      BUCLE_FUNCTION (pol11_f64);
      break;
    case TYPE_JBM_POL12:
      BUCLE_FUNCTION (pol12_f64);
      break;
    case TYPE_JBM_POL13:
      BUCLE_FUNCTION (pol13_f64);
      break;
    case TYPE_JBM_POL14:
      BUCLE_FUNCTION (pol14_f64);
      break;
    case TYPE_JBM_POL15:
      BUCLE_FUNCTION (pol15_f64);
      break;
    }
}

#ifdef __SSE4_2__

#define BUCLE_4XF32(f) \
  for (i = imin; i < imax; i += 4) \
    { \
      xv = _mm_load_ps (x + i); \
      yv = f (xv); \
      _mm_store_ps (y + i, yv); \
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

static inline __m128
mod_4xf32 (__m128 x)
{
  return jbm_4xf32_mod (x, _mm_set1_ps (M_PIf));
}

static inline __m128
pow_4xf32 (__m128 x)
{
  return jbm_4xf32_pow (x, _mm_set1_ps (M_PIf));
}

static inline void
thread_4xf32 (void *data, void *user_data __attribute__((unused)))
{
  Parallel_f32 *p;
  float *x, *y;
  __m128 xv, yv;
  unsigned long int i, imin, imax;
  p = (Parallel_f32 *) data;
  x = p->x;
  y = p->y;
  imin = p->imin;
  imax = p->imax;
  switch (p->type)
    {
    case TYPE_ADD:
      BUCLE_4XF32 (add_4xf32);
      break;
    case TYPE_SUB:
      BUCLE_4XF32 (sub_4xf32);
      break;
    case TYPE_MUL:
      BUCLE_4XF32 (mul_4xf32);
      break;
    case TYPE_DIV:
      BUCLE_4XF32 (div_4xf32);
      break;
    case TYPE_SQRT:
      BUCLE_4XF32 (sqrt_4xf32);
      break;
    case TYPE_MAX:
      BUCLE_4XF32 (max_4xf32);
      break;
    case TYPE_MIN:
      BUCLE_4XF32 (min_4xf32);
      break;
    case TYPE_JBM_ABS:
      BUCLE_4XF32 (jbm_4xf32_abs);
      break;
    case TYPE_JBM_MOD:
      BUCLE_4XF32 (mod_4xf32);
      break;
    case TYPE_JBM_EXP2:
      BUCLE_4XF32 (jbm_4xf32_exp2);
      break;
    case TYPE_JBM_EXP:
      BUCLE_4XF32 (jbm_4xf32_exp);
      break;
    case TYPE_JBM_EXP10:
      BUCLE_4XF32 (jbm_4xf32_exp10);
      break;
    case TYPE_JBM_EXPM1:
      BUCLE_4XF32 (jbm_4xf32_expm1);
      break;
    case TYPE_JBM_LOG2:
      BUCLE_4XF32 (jbm_4xf32_log2);
      break;
    case TYPE_JBM_LOG:
      BUCLE_4XF32 (jbm_4xf32_log);
      break;
    case TYPE_JBM_LOG10:
      BUCLE_4XF32 (jbm_4xf32_log10);
      break;
    case TYPE_JBM_POW:
      BUCLE_4XF32 (pow_4xf32);
      break;
    case TYPE_JBM_CBRT:
      BUCLE_4XF32 (jbm_4xf32_cbrt);
      break;
    case TYPE_JBM_SIN:
      BUCLE_4XF32 (jbm_4xf32_sin);
      break;
    case TYPE_JBM_COS:
      BUCLE_4XF32 (jbm_4xf32_cos);
      break;
    case TYPE_JBM_TAN:
      BUCLE_4XF32 (jbm_4xf32_tan);
      break;
    case TYPE_JBM_ATAN:
      BUCLE_4XF32 (jbm_4xf32_atan);
      break;
    case TYPE_JBM_ASIN:
      BUCLE_4XF32 (jbm_4xf32_asin);
      break;
    case TYPE_JBM_ACOS:
      BUCLE_4XF32 (jbm_4xf32_acos);
      break;
    case TYPE_JBM_SINH:
      BUCLE_4XF32 (jbm_4xf32_sinh);
      break;
    case TYPE_JBM_COSH:
      BUCLE_4XF32 (jbm_4xf32_cosh);
      break;
    case TYPE_JBM_TANH:
      BUCLE_4XF32 (jbm_4xf32_tanh);
      break;
    case TYPE_JBM_ERF:
      BUCLE_4XF32 (jbm_4xf32_erf);
      break;
    case TYPE_JBM_ERFC:
      BUCLE_4XF32 (jbm_4xf32_erfc);
      break;
    }
}

#define BUCLE_2XF64(f) \
  for (i = imin; i < imax; i += 2) \
    { \
      xv = _mm_load_pd (x + i); \
      yv = f (xv); \
      _mm_store_pd (y + i, yv); \
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

static inline __m128d
mod_2xf64 (__m128d x)
{
  return jbm_2xf64_mod (x, _mm_set1_pd (M_PI));
}

static inline __m128d
pow_2xf64 (__m128d x)
{
  return jbm_2xf64_pow (x, _mm_set1_pd (M_PI));
}

static inline void
thread_2xf64 (void *data, void *user_data __attribute__((unused)))
{
  Parallel_f64 *p;
  double *x, *y;
  __m128d xv, yv;
  unsigned long int i, imin, imax;
  p = (Parallel_f64 *) data;
  x = p->x;
  y = p->y;
  imin = p->imin;
  imax = p->imax;
  switch (p->type)
    {
    case TYPE_ADD:
      BUCLE_2XF64 (add_2xf64);
      break;
    case TYPE_SUB:
      BUCLE_2XF64 (sub_2xf64);
      break;
    case TYPE_MUL:
      BUCLE_2XF64 (mul_2xf64);
      break;
    case TYPE_DIV:
      BUCLE_2XF64 (div_2xf64);
      break;
    case TYPE_SQRT:
      BUCLE_2XF64 (sqrt_2xf64);
      break;
    case TYPE_MAX:
      BUCLE_2XF64 (max_2xf64);
      break;
    case TYPE_MIN:
      BUCLE_2XF64 (min_2xf64);
      break;
    case TYPE_JBM_ABS:
      BUCLE_2XF64 (jbm_2xf64_abs);
      break;
    case TYPE_JBM_MOD:
      BUCLE_2XF64 (mod_2xf64);
      break;
    case TYPE_JBM_EXP2:
      BUCLE_2XF64 (jbm_2xf64_exp2);
      break;
    case TYPE_JBM_EXP:
      BUCLE_2XF64 (jbm_2xf64_exp);
      break;
    case TYPE_JBM_EXP10:
      BUCLE_2XF64 (jbm_2xf64_exp10);
      break;
    case TYPE_JBM_EXPM1:
      BUCLE_2XF64 (jbm_2xf64_expm1);
      break;
    case TYPE_JBM_LOG2:
      BUCLE_2XF64 (jbm_2xf64_log2);
      break;
    case TYPE_JBM_LOG:
      BUCLE_2XF64 (jbm_2xf64_log);
      break;
    case TYPE_JBM_LOG10:
      BUCLE_2XF64 (jbm_2xf64_log10);
      break;
    case TYPE_JBM_POW:
      BUCLE_2XF64 (pow_2xf64);
      break;
    case TYPE_JBM_CBRT:
      BUCLE_2XF64 (jbm_2xf64_cbrt);
      break;
    case TYPE_JBM_SIN:
      BUCLE_2XF64 (jbm_2xf64_sin);
      break;
    case TYPE_JBM_COS:
      BUCLE_2XF64 (jbm_2xf64_cos);
      break;
    case TYPE_JBM_TAN:
      BUCLE_2XF64 (jbm_2xf64_tan);
      break;
    case TYPE_JBM_ATAN:
      BUCLE_2XF64 (jbm_2xf64_atan);
      break;
    case TYPE_JBM_ASIN:
      BUCLE_2XF64 (jbm_2xf64_asin);
      break;
    case TYPE_JBM_ACOS:
      BUCLE_2XF64 (jbm_2xf64_acos);
      break;
    case TYPE_JBM_SINH:
      BUCLE_2XF64 (jbm_2xf64_sinh);
      break;
    case TYPE_JBM_COSH:
      BUCLE_2XF64 (jbm_2xf64_cosh);
      break;
    case TYPE_JBM_TANH:
      BUCLE_2XF64 (jbm_2xf64_tanh);
      break;
    case TYPE_JBM_ERF:
      BUCLE_2XF64 (jbm_2xf64_erf);
      break;
    case TYPE_JBM_ERFC:
      BUCLE_2XF64 (jbm_2xf64_erfc);
      break;
    }
}

#endif

#ifdef __AVX__

#define BUCLE_8XF32(f) \
  for (i = imin; i < imax; i += 8) \
    { \
      xv = _mm256_load_ps (x + i); \
      yv = f (xv); \
      _mm256_store_ps (y + i, yv); \
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

static inline __m256
mod_8xf32 (__m256 x)
{
  return jbm_8xf32_mod (x, _mm256_set1_ps (M_PIf));
}

static inline __m256
pow_8xf32 (__m256 x)
{
  return jbm_8xf32_pow (x, _mm256_set1_ps (M_PIf));
}

static inline void
thread_8xf32 (void *data, void *user_data __attribute__((unused)))
{
  Parallel_f32 *p;
  float *x, *y;
  __m256 xv, yv;
  unsigned long int i, imin, imax;
  p = (Parallel_f32 *) data;
  x = p->x;
  y = p->y;
  imin = p->imin;
  imax = p->imax;
  switch (p->type)
    {
    case TYPE_ADD:
      BUCLE_8XF32 (add_8xf32);
      break;
    case TYPE_SUB:
      BUCLE_8XF32 (sub_8xf32);
      break;
    case TYPE_MUL:
      BUCLE_8XF32 (mul_8xf32);
      break;
    case TYPE_DIV:
      BUCLE_8XF32 (div_8xf32);
      break;
    case TYPE_SQRT:
      BUCLE_8XF32 (sqrt_8xf32);
      break;
    case TYPE_MAX:
      BUCLE_8XF32 (max_8xf32);
      break;
    case TYPE_MIN:
      BUCLE_8XF32 (min_8xf32);
      break;
    case TYPE_JBM_ABS:
      BUCLE_8XF32 (jbm_8xf32_abs);
      break;
    case TYPE_JBM_MOD:
      BUCLE_8XF32 (mod_8xf32);
      break;
    case TYPE_JBM_EXP2:
      BUCLE_8XF32 (jbm_8xf32_exp2);
      break;
    case TYPE_JBM_EXP:
      BUCLE_8XF32 (jbm_8xf32_exp);
      break;
    case TYPE_JBM_EXP10:
      BUCLE_8XF32 (jbm_8xf32_exp10);
      break;
    case TYPE_JBM_EXPM1:
      BUCLE_8XF32 (jbm_8xf32_expm1);
      break;
    case TYPE_JBM_LOG2:
      BUCLE_8XF32 (jbm_8xf32_log2);
      break;
    case TYPE_JBM_LOG:
      BUCLE_8XF32 (jbm_8xf32_log);
      break;
    case TYPE_JBM_LOG10:
      BUCLE_8XF32 (jbm_8xf32_log10);
      break;
    case TYPE_JBM_POW:
      BUCLE_8XF32 (pow_8xf32);
      break;
    case TYPE_JBM_CBRT:
      BUCLE_8XF32 (jbm_8xf32_cbrt);
      break;
    case TYPE_JBM_SIN:
      BUCLE_8XF32 (jbm_8xf32_sin);
      break;
    case TYPE_JBM_COS:
      BUCLE_8XF32 (jbm_8xf32_cos);
      break;
    case TYPE_JBM_TAN:
      BUCLE_8XF32 (jbm_8xf32_tan);
      break;
    case TYPE_JBM_ATAN:
      BUCLE_8XF32 (jbm_8xf32_atan);
      break;
    case TYPE_JBM_ASIN:
      BUCLE_8XF32 (jbm_8xf32_asin);
      break;
    case TYPE_JBM_ACOS:
      BUCLE_8XF32 (jbm_8xf32_acos);
      break;
    case TYPE_JBM_SINH:
      BUCLE_8XF32 (jbm_8xf32_sinh);
      break;
    case TYPE_JBM_COSH:
      BUCLE_8XF32 (jbm_8xf32_cosh);
      break;
    case TYPE_JBM_TANH:
      BUCLE_8XF32 (jbm_8xf32_tanh);
      break;
    case TYPE_JBM_ERF:
      BUCLE_8XF32 (jbm_8xf32_erf);
      break;
    case TYPE_JBM_ERFC:
      BUCLE_8XF32 (jbm_8xf32_erfc);
      break;
    }
}

#define BUCLE_4XF64(f) \
  for (i = imin; i < imax; i += 4) \
    { \
      xv = _mm256_load_pd (x + i); \
      yv = f (xv); \
      _mm256_store_pd (y + i, yv); \
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

static inline __m256d
mod_4xf64 (__m256d x)
{
  return jbm_4xf64_mod (x, _mm256_set1_pd (M_PI));
}

static inline __m256d
pow_4xf64 (__m256d x)
{
  return jbm_4xf64_pow (x, _mm256_set1_pd (M_PI));
}

static inline void
thread_4xf64 (void *data, void *user_data __attribute__((unused)))
{
  Parallel_f64 *p;
  double *x, *y;
  __m256d xv, yv;
  unsigned long int i, imin, imax;
  p = (Parallel_f64 *) data;
  x = p->x;
  y = p->y;
  imin = p->imin;
  imax = p->imax;
  switch (p->type)
    {
    case TYPE_ADD:
      BUCLE_4XF64 (add_4xf64);
      break;
    case TYPE_SUB:
      BUCLE_4XF64 (sub_4xf64);
      break;
    case TYPE_MUL:
      BUCLE_4XF64 (mul_4xf64);
      break;
    case TYPE_DIV:
      BUCLE_4XF64 (div_4xf64);
      break;
    case TYPE_SQRT:
      BUCLE_4XF64 (sqrt_4xf64);
      break;
    case TYPE_MAX:
      BUCLE_4XF64 (max_4xf64);
      break;
    case TYPE_MIN:
      BUCLE_4XF64 (min_4xf64);
      break;
    case TYPE_JBM_ABS:
      BUCLE_4XF64 (jbm_4xf64_abs);
      break;
    case TYPE_JBM_MOD:
      BUCLE_4XF64 (mod_4xf64);
      break;
    case TYPE_JBM_EXP2:
      BUCLE_4XF64 (jbm_4xf64_exp2);
      break;
    case TYPE_JBM_EXP:
      BUCLE_4XF64 (jbm_4xf64_exp);
      break;
    case TYPE_JBM_EXP10:
      BUCLE_4XF64 (jbm_4xf64_exp10);
      break;
    case TYPE_JBM_EXPM1:
      BUCLE_4XF64 (jbm_4xf64_expm1);
      break;
    case TYPE_JBM_LOG2:
      BUCLE_4XF64 (jbm_4xf64_log2);
      break;
    case TYPE_JBM_LOG:
      BUCLE_4XF64 (jbm_4xf64_log);
      break;
    case TYPE_JBM_LOG10:
      BUCLE_4XF64 (jbm_4xf64_log10);
      break;
    case TYPE_JBM_POW:
      BUCLE_4XF64 (pow_4xf64);
      break;
    case TYPE_JBM_CBRT:
      BUCLE_4XF64 (jbm_4xf64_cbrt);
      break;
    case TYPE_JBM_SIN:
      BUCLE_4XF64 (jbm_4xf64_sin);
      break;
    case TYPE_JBM_COS:
      BUCLE_4XF64 (jbm_4xf64_cos);
      break;
    case TYPE_JBM_TAN:
      BUCLE_4XF64 (jbm_4xf64_tan);
      break;
    case TYPE_JBM_ATAN:
      BUCLE_4XF64 (jbm_4xf64_atan);
      break;
    case TYPE_JBM_ASIN:
      BUCLE_4XF64 (jbm_4xf64_asin);
      break;
    case TYPE_JBM_ACOS:
      BUCLE_4XF64 (jbm_4xf64_acos);
      break;
    case TYPE_JBM_SINH:
      BUCLE_4XF64 (jbm_4xf64_sinh);
      break;
    case TYPE_JBM_COSH:
      BUCLE_4XF64 (jbm_4xf64_cosh);
      break;
    case TYPE_JBM_TANH:
      BUCLE_4XF64 (jbm_4xf64_tanh);
      break;
    case TYPE_JBM_ERF:
      BUCLE_4XF64 (jbm_4xf64_erf);
      break;
    case TYPE_JBM_ERFC:
      BUCLE_4XF64 (jbm_4xf64_erfc);
      break;
    }
}

#endif

#ifdef __AVX512F__

#define BUCLE_16XF32(f) \
  for (i = imin; i < imax; i += 16) \
    { \
      xv = _mm512_load_ps (x + i); \
      yv = f (xv); \
      _mm512_store_ps (y + i, yv); \
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

static inline __m512
mod_16xf32 (__m512 x)
{
  return jbm_16xf32_mod (x, _mm512_set1_ps (M_PIf));
}

static inline __m512
pow_16xf32 (__m512 x)
{
  return jbm_16xf32_pow (x, _mm512_set1_ps (M_PIf));
}

static inline void
thread_16xf32 (void *data, void *user_data __attribute__((unused)))
{
  Parallel_f32 *p;
  float *x, *y;
  __m512 xv, yv;
  unsigned long int i, imin, imax;
  p = (Parallel_f32 *) data;
  x = p->x;
  y = p->y;
  imin = p->imin;
  imax = p->imax;
  switch (p->type)
    {
    case TYPE_ADD:
      BUCLE_16XF32 (add_16xf32);
      break;
    case TYPE_SUB:
      BUCLE_16XF32 (sub_16xf32);
      break;
    case TYPE_MUL:
      BUCLE_16XF32 (mul_16xf32);
      break;
    case TYPE_DIV:
      BUCLE_16XF32 (div_16xf32);
      break;
    case TYPE_SQRT:
      BUCLE_16XF32 (sqrt_16xf32);
      break;
    case TYPE_MAX:
      BUCLE_16XF32 (max_16xf32);
      break;
    case TYPE_MIN:
      BUCLE_16XF32 (min_16xf32);
      break;
    case TYPE_JBM_ABS:
      BUCLE_16XF32 (jbm_16xf32_abs);
      break;
    case TYPE_JBM_MOD:
      BUCLE_16XF32 (mod_16xf32);
      break;
    case TYPE_JBM_EXP2:
      BUCLE_16XF32 (jbm_16xf32_exp2);
      break;
    case TYPE_JBM_EXP:
      BUCLE_16XF32 (jbm_16xf32_exp);
      break;
    case TYPE_JBM_EXP10:
      BUCLE_16XF32 (jbm_16xf32_exp10);
      break;
    case TYPE_JBM_EXPM1:
      BUCLE_16XF32 (jbm_16xf32_expm1);
      break;
    case TYPE_JBM_LOG2:
      BUCLE_16XF32 (jbm_16xf32_log2);
      break;
    case TYPE_JBM_LOG:
      BUCLE_16XF32 (jbm_16xf32_log);
      break;
    case TYPE_JBM_LOG10:
      BUCLE_16XF32 (jbm_16xf32_log10);
      break;
    case TYPE_JBM_POW:
      BUCLE_16XF32 (pow_16xf32);
      break;
    case TYPE_JBM_CBRT:
      BUCLE_16XF32 (jbm_16xf32_cbrt);
      break;
    case TYPE_JBM_SIN:
      BUCLE_16XF32 (jbm_16xf32_sin);
      break;
    case TYPE_JBM_COS:
      BUCLE_16XF32 (jbm_16xf32_cos);
      break;
    case TYPE_JBM_TAN:
      BUCLE_16XF32 (jbm_16xf32_tan);
      break;
    case TYPE_JBM_ATAN:
      BUCLE_16XF32 (jbm_16xf32_atan);
      break;
    case TYPE_JBM_ASIN:
      BUCLE_16XF32 (jbm_16xf32_asin);
      break;
    case TYPE_JBM_ACOS:
      BUCLE_16XF32 (jbm_16xf32_acos);
      break;
    case TYPE_JBM_SINH:
      BUCLE_16XF32 (jbm_16xf32_sinh);
      break;
    case TYPE_JBM_COSH:
      BUCLE_16XF32 (jbm_16xf32_cosh);
      break;
    case TYPE_JBM_TANH:
      BUCLE_16XF32 (jbm_16xf32_tanh);
      break;
    case TYPE_JBM_ERF:
      BUCLE_16XF32 (jbm_16xf32_erf);
      break;
    case TYPE_JBM_ERFC:
      BUCLE_16XF32 (jbm_16xf32_erfc);
      break;
    }
}

#define BUCLE_8XF64(f) \
  for (i = imin; i < imax; i += 8) \
    { \
      xv = _mm512_load_pd (x + i); \
      yv = f (xv); \
      _mm512_store_pd (y + i, yv); \
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

static inline __m512d
mod_8xf64 (__m512d x)
{
  return jbm_8xf64_mod (x, _mm512_set1_pd (M_PI));
}

static inline __m512d
pow_8xf64 (__m512d x)
{
  return jbm_8xf64_pow (x, _mm512_set1_pd (M_PI));
}

static inline void
thread_8xf64 (void *data, void *user_data __attribute__((unused)))
{
  Parallel_f64 *p;
  double *x, *y;
  __m512d xv, yv;
  unsigned long int i, imin, imax;
  p = (Parallel_f64 *) data;
  x = p->x;
  y = p->y;
  imin = p->imin;
  imax = p->imax;
  switch (p->type)
    {
    case TYPE_ADD:
      BUCLE_8XF64 (add_8xf64);
      break;
    case TYPE_SUB:
      BUCLE_8XF64 (sub_8xf64);
      break;
    case TYPE_MUL:
      BUCLE_8XF64 (mul_8xf64);
      break;
    case TYPE_DIV:
      BUCLE_8XF64 (div_8xf64);
      break;
    case TYPE_SQRT:
      BUCLE_8XF64 (sqrt_8xf64);
      break;
    case TYPE_MAX:
      BUCLE_8XF64 (max_8xf64);
      break;
    case TYPE_MIN:
      BUCLE_8XF64 (min_8xf64);
      break;
    case TYPE_JBM_ABS:
      BUCLE_8XF64 (jbm_8xf64_abs);
      break;
    case TYPE_JBM_MOD:
      BUCLE_8XF64 (mod_8xf64);
      break;
    case TYPE_JBM_EXP2:
      BUCLE_8XF64 (jbm_8xf64_exp2);
      break;
    case TYPE_JBM_EXP:
      BUCLE_8XF64 (jbm_8xf64_exp);
      break;
    case TYPE_JBM_EXP10:
      BUCLE_8XF64 (jbm_8xf64_exp10);
      break;
    case TYPE_JBM_EXPM1:
      BUCLE_8XF64 (jbm_8xf64_expm1);
      break;
    case TYPE_JBM_LOG2:
      BUCLE_8XF64 (jbm_8xf64_log2);
      break;
    case TYPE_JBM_LOG:
      BUCLE_8XF64 (jbm_8xf64_log);
      break;
    case TYPE_JBM_LOG10:
      BUCLE_8XF64 (jbm_8xf64_log10);
      break;
    case TYPE_JBM_POW:
      BUCLE_8XF64 (pow_8xf64);
      break;
    case TYPE_JBM_CBRT:
      BUCLE_8XF64 (jbm_8xf64_cbrt);
      break;
    case TYPE_JBM_SIN:
      BUCLE_8XF64 (jbm_8xf64_sin);
      break;
    case TYPE_JBM_COS:
      BUCLE_8XF64 (jbm_8xf64_cos);
      break;
    case TYPE_JBM_TAN:
      BUCLE_8XF64 (jbm_8xf64_tan);
      break;
    case TYPE_JBM_ATAN:
      BUCLE_8XF64 (jbm_8xf64_atan);
      break;
    case TYPE_JBM_ASIN:
      BUCLE_8XF64 (jbm_8xf64_asin);
      break;
    case TYPE_JBM_ACOS:
      BUCLE_8XF64 (jbm_8xf64_acos);
      break;
    case TYPE_JBM_SINH:
      BUCLE_8XF64 (jbm_8xf64_sinh);
      break;
    case TYPE_JBM_COSH:
      BUCLE_8XF64 (jbm_8xf64_cosh);
      break;
    case TYPE_JBM_TANH:
      BUCLE_8XF64 (jbm_8xf64_tanh);
      break;
    case TYPE_JBM_ERF:
      BUCLE_8XF64 (jbm_8xf64_erf);
      break;
    case TYPE_JBM_ERFC:
      BUCLE_8XF64 (jbm_8xf64_erfc);
      break;
    }
}

#endif

static inline void
thread_array_f32 (void *data, void *user_data __attribute__((unused)))
{
  Parallel_f32 *p;
  float *x, *y;
  unsigned long int imin, imax, n;
  p = (Parallel_f32 *) data;
  imin = p->imin;
  imax = p->imax;
  x = p->x + imin;
  y = p->y + imin;
  n = imax - imin;
  switch (p->type)
    {
    case TYPE_ADD:
      jbm_array_f32_add1 (y, x, M_PIf, n);
      break;
    case TYPE_SUB:
      jbm_array_f32_sub1 (y, x, M_PIf, n);
      break;
    case TYPE_MUL:
      jbm_array_f32_mul1 (y, x, M_PIf, n);
      break;
    case TYPE_DIV:
      jbm_array_f32_div1 (y, x, M_PIf, n);
      break;
    case TYPE_SQRT:
      jbm_array_f32_sqrt (y, x, n);
      break;
    case TYPE_MAX:
      jbm_array_f32_max1 (y, x, M_PIf, n);
      break;
    case TYPE_MIN:
      jbm_array_f32_min1 (y, x, M_PIf, n);
      break;
    case TYPE_JBM_ABS:
      jbm_array_f32_abs (y, x, n);
      break;
    case TYPE_JBM_MOD:
      jbm_array_f32_mod1 (y, x, M_PIf, n);
      break;
    case TYPE_JBM_EXP2:
      jbm_array_f32_exp2 (y, x, n);
      break;
    case TYPE_JBM_EXP:
      jbm_array_f32_exp (y, x, n);
      break;
    case TYPE_JBM_EXP10:
      jbm_array_f32_exp10 (y, x, n);
      break;
    case TYPE_JBM_EXPM1:
      jbm_array_f32_expm1 (y, x, n);
      break;
    case TYPE_JBM_LOG2:
      jbm_array_f32_log2 (y, x, n);
      break;
    case TYPE_JBM_LOG:
      jbm_array_f32_log (y, x, n);
      break;
    case TYPE_JBM_LOG10:
      jbm_array_f32_log10 (y, x, n);
      break;
    case TYPE_JBM_POW:
      jbm_array_f32_pow1 (y, x, M_PIf, n);
      break;
    case TYPE_JBM_CBRT:
      jbm_array_f32_cbrt (y, x, n);
      break;
    case TYPE_JBM_SIN:
      jbm_array_f32_sin (y, x, n);
      break;
    case TYPE_JBM_COS:
      jbm_array_f32_cos (y, x, n);
      break;
    case TYPE_JBM_TAN:
      jbm_array_f32_tan (y, x, n);
      break;
    case TYPE_JBM_ATAN:
      jbm_array_f32_atan (y, x, n);
      break;
    case TYPE_JBM_ASIN:
      jbm_array_f32_asin (y, x, n);
      break;
    case TYPE_JBM_ACOS:
      jbm_array_f32_acos (y, x, n);
      break;
    case TYPE_JBM_SINH:
      jbm_array_f32_sinh (y, x, n);
      break;
    case TYPE_JBM_COSH:
      jbm_array_f32_cosh (y, x, n);
      break;
    case TYPE_JBM_TANH:
      jbm_array_f32_tanh (y, x, n);
      break;
    case TYPE_JBM_ERF:
      jbm_array_f32_erf (y, x, n);
      break;
    case TYPE_JBM_ERFC:
      jbm_array_f32_erfc (y, x, n);
      break;
    }
}

static inline void
thread_array_f64 (void *data, void *user_data __attribute__((unused)))
{
  Parallel_f64 *p;
  double *x, *y;
  unsigned long int imin, imax, n;
  p = (Parallel_f64 *) data;
  imin = p->imin;
  imax = p->imax;
  x = p->x + imin;
  y = p->y + imin;
  n = imax - imin;
  switch (p->type)
    {
    case TYPE_ADD:
      jbm_array_f64_add1 (y, x, M_PI, n);
      break;
    case TYPE_SUB:
      jbm_array_f64_sub1 (y, x, M_PI, n);
      break;
    case TYPE_MUL:
      jbm_array_f64_mul1 (y, x, M_PI, n);
      break;
    case TYPE_DIV:
      jbm_array_f64_div1 (y, x, M_PI, n);
      break;
    case TYPE_SQRT:
      jbm_array_f64_sqrt (y, x, n);
      break;
    case TYPE_MAX:
      jbm_array_f64_max1 (y, x, M_PI, n);
      break;
    case TYPE_MIN:
      jbm_array_f64_min1 (y, x, M_PI, n);
      break;
    case TYPE_JBM_ABS:
      jbm_array_f64_abs (y, x, n);
      break;
    case TYPE_JBM_MOD:
      jbm_array_f64_mod1 (y, x, M_PI, n);
      break;
    case TYPE_JBM_EXP2:
      jbm_array_f64_exp2 (y, x, n);
      break;
    case TYPE_JBM_EXP:
      jbm_array_f64_exp (y, x, n);
      break;
    case TYPE_JBM_EXP10:
      jbm_array_f64_exp10 (y, x, n);
      break;
    case TYPE_JBM_EXPM1:
      jbm_array_f64_expm1 (y, x, n);
      break;
    case TYPE_JBM_LOG2:
      jbm_array_f64_log2 (y, x, n);
      break;
    case TYPE_JBM_LOG:
      jbm_array_f64_log (y, x, n);
      break;
    case TYPE_JBM_LOG10:
      jbm_array_f64_log10 (y, x, n);
      break;
    case TYPE_JBM_POW:
      jbm_array_f64_pow1 (y, x, M_PIf, n);
      break;
    case TYPE_JBM_CBRT:
      jbm_array_f64_cbrt (y, x, n);
      break;
    case TYPE_JBM_SIN:
      jbm_array_f64_sin (y, x, n);
      break;
    case TYPE_JBM_COS:
      jbm_array_f64_cos (y, x, n);
      break;
    case TYPE_JBM_TAN:
      jbm_array_f64_tan (y, x, n);
      break;
    case TYPE_JBM_ATAN:
      jbm_array_f64_atan (y, x, n);
      break;
    case TYPE_JBM_ASIN:
      jbm_array_f64_asin (y, x, n);
      break;
    case TYPE_JBM_ACOS:
      jbm_array_f64_acos (y, x, n);
      break;
    case TYPE_JBM_SINH:
      jbm_array_f64_sinh (y, x, n);
      break;
    case TYPE_JBM_COSH:
      jbm_array_f64_cosh (y, x, n);
      break;
    case TYPE_JBM_TANH:
      jbm_array_f64_tanh (y, x, n);
      break;
    case TYPE_JBM_ERF:
      jbm_array_f64_erf (y, x, n);
      break;
    case TYPE_JBM_ERFC:
      jbm_array_f64_erfc (y, x, n);
      break;
    }
}

static inline void
efficiency_f32 (const unsigned int type, void (*thread) (void *, void *),
                float *restrict x, float *restrict y, const double *r,
                unsigned long int n, const float xmin, const float xmax,
                const unsigned int nthreads, const char *label)
{
  Parallel_f32 p[nthreads];
  GThreadPool *pool;
  double t, t0;
  unsigned long int i;
  global_error = 0ull;
  if (nthreads < 2)
    {
      p[0].type = type;
      p[0].imin = 0;
      p[0].imax = n;
      p[0].xmin = xmin;
      p[0].xmax = xmax;
      p[0].x = x;
      p[0].y = y;
      p[0].r = r;
      init_f32 (p, NULL);
      t0 = crono ();
      thread (p, NULL);
      t = (crono () - t0) / (double) n;
      x32_max = x[0];
      error_f32 (p, NULL);
    }
  else
    {
      pool = g_thread_pool_new (init_f32, NULL, nthreads, FALSE, NULL);
      for (i = 0; i < (unsigned long int) nthreads; ++i)
        {
          p[i].type = type;
          p[i].imin = i * n / (unsigned long int) nthreads;
          p[i].imax = (i + 1) * n / (unsigned long int) nthreads;
          p[i].xmin = xmin;
          p[i].xmax = xmax;
          p[i].x = x;
          p[i].y = y;
          p[i].r = r;
          g_thread_pool_push (pool, p + i, NULL);
        }
      g_thread_pool_free (pool, FALSE, TRUE);
      t0 = crono ();
      pool = g_thread_pool_new (thread, NULL, nthreads, FALSE, NULL);
      for (i = 0; i < (unsigned long int) nthreads; ++i)
        g_thread_pool_push (pool, p + i, NULL);
      g_thread_pool_free (pool, FALSE, TRUE);
      t = (crono () - t0) / (double) n;
      x32_max = x[0];
      pool = g_thread_pool_new (error_f32, NULL, nthreads, FALSE, NULL);
      for (i = 0; i < (unsigned long int) nthreads; ++i)
        g_thread_pool_push (pool, p + i, NULL);
      g_thread_pool_free (pool, FALSE, TRUE);
    }
  printf ("%s time=%lg s, error=%" PRIu64 " ulp\n", label, t, global_error);
  printf ("worst x=%.8e f(x)=%.8e e(x)=%.8Le\n",
          x32_max, f32 (type, x32_max), f80 (type, (long double) x32_max));
}

static inline void
efficiency_f64 (const unsigned int type, void (*thread) (void *, void *),
                double *restrict x, double *restrict y, const double *r,
                unsigned long int n, const double xmin, const double xmax,
                const unsigned int nthreads, const char *label)
{
  Parallel_f64 p[nthreads];
  GThreadPool *pool;
  double t, t0;
  unsigned long int i;
  global_error = 0ull;
  if (nthreads < 2)
    {
      p[0].type = type;
      p[0].imin = 0;
      p[0].imax = n;
      p[0].xmin = xmin;
      p[0].xmax = xmax;
      p[0].x = x;
      p[0].y = y;
      p[0].r = r;
      init_f64 (p, NULL);
      t0 = crono ();
      thread (p, NULL);
      t = (crono () - t0) / (double) n;
      x64_max = x[0];
      error_f64 (p, NULL);
    }
  else
    {
      pool = g_thread_pool_new (init_f64, NULL, nthreads, FALSE, NULL);
      for (i = 0; i < (unsigned long int) nthreads; ++i)
        {
          p[i].type = type;
          p[i].imin = i * n / (unsigned long int) nthreads;
          p[i].imax = (i + 1) * n / (unsigned long int) nthreads;
          p[i].xmin = xmin;
          p[i].xmax = xmax;
          p[i].x = x;
          p[i].y = y;
          p[i].r = r;
          g_thread_pool_push (pool, p + i, NULL);
        }
      g_thread_pool_free (pool, FALSE, TRUE);
      t0 = crono ();
      pool = g_thread_pool_new (thread, NULL, nthreads, FALSE, NULL);
      for (i = 0; i < (unsigned long int) nthreads; ++i)
        g_thread_pool_push (pool, p + i, NULL);
      g_thread_pool_free (pool, FALSE, TRUE);
      t = (crono () - t0) / (double) n;
      x64_max = x[0];
      pool = g_thread_pool_new (error_f64, NULL, nthreads, FALSE, NULL);
      for (i = 0; i < (unsigned long int) nthreads; ++i)
        g_thread_pool_push (pool, p + i, NULL);
      g_thread_pool_free (pool, FALSE, TRUE);
    }
  printf ("%s time=%lg s, error=%" PRIu64 " ulp\n", label, t, global_error);
  printf ("worst x=%.15le f(x)=%.15le e(x)=%.15Le\n",
          x64_max, f64 (type, x64_max), f80 (type, (long double) x64_max));
}

int
main (int argn, char **argc)
{
  gsl_rng *rng;
  double *r;
  double *x64, *y64;
  float *x32, *y32;
  double t0;
  unsigned long int i, n;
  unsigned int nthreads;

  // check arguments
  if (argn != 3)
    {
      printf ("The syntax is:\n./efficiency n nthreads\n");
      return 1;
    }

  // init variables
  nthreads = (unsigned int) atoi (argc[2]);
  n = 64l * (unsigned long int) nthreads;
  n = ((unsigned long int) atol (argc[1]) / n) * n;
  printf ("calculations number=%lu threads=%u\n", n, nthreads);
  x64 = (double *) JB_MALLOC (n * sizeof (double));
  y64 = (double *) JB_MALLOC (n * sizeof (double));
  x32 = (float *) x64;
  y32 = (float *) y64;
  t0 = crono ();
  r = (double *) malloc (n * sizeof (double));
  rng = gsl_rng_alloc (gsl_rng_taus2);
  gsl_rng_set (rng, SEED);
  for (i = 0; i < n; ++i)
    r[i] = gsl_rng_uniform (rng);
  gsl_rng_free (rng);
  printf ("random numbers generation (taus2 %lu numbers): %lg s\n", n,
          crono () - t0);
  g_mutex_init (&mutex);

  // float functions
  printf ("\nfloat functions\n");
  efficiency_f32 (TYPE_ADD, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "add_f32");
  efficiency_f32 (TYPE_ADD, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "add_f32");
  efficiency_f32 (TYPE_SUB, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "sub_f32");
  efficiency_f32 (TYPE_MUL, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "mul_f32");
  efficiency_f32 (TYPE_DIV, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "div_f32");
  efficiency_f32 (TYPE_SQRT, thread_f32, x32, y32, r, n, 0.f, FLT_MAX,
                  nthreads, "sqrtf");
  efficiency_f32 (TYPE_MAX, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "max_f32");
  efficiency_f32 (TYPE_MIN, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "min_f32");
  efficiency_f32 (TYPE_ROUND, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "roundf");
  efficiency_f32 (TYPE_FLOOR, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "floorf");
  efficiency_f32 (TYPE_CEIL, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "ceilf");
  efficiency_f32 (TYPE_TRUNC, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "truncf");
  efficiency_f32 (TYPE_ABS, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "fabsf");
  efficiency_f32 (TYPE_JBM_ABS, thread_f32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_f32_abs");
  efficiency_f32 (TYPE_MOD, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "f32_mod");
  efficiency_f32 (TYPE_JBM_MOD, thread_f32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_f32_mod");
  efficiency_f32 (TYPE_CBRT, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "cbrtf");
  efficiency_f32 (TYPE_JBM_CBRT, thread_f32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_f32_cbrt");
  efficiency_f32 (TYPE_EXP2, thread_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "exp2f");
  efficiency_f32 (TYPE_JBM_EXP2, thread_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_f32_exp2");
  efficiency_f32 (TYPE_EXP, thread_f32, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "expf");
  efficiency_f32 (TYPE_JBM_EXP, thread_f32, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "jbm_f32_exp");
  efficiency_f32 (TYPE_EXP10, thread_f32, x32, y32, r, n, -FLT_MAX_10_EXP,
                  FLT_MAX_10_EXP, nthreads, "exp10f");
  efficiency_f32 (TYPE_JBM_EXP10, thread_f32, x32, y32, r, n, -FLT_MAX_10_EXP,
                  FLT_MAX_10_EXP, nthreads, "jbm_f32_exp10");
  efficiency_f32 (TYPE_EXPM1, thread_f32, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "expm1f");
  efficiency_f32 (TYPE_JBM_EXPM1, thread_f32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_f32_expm1");
  efficiency_f32 (TYPE_LOG2, thread_f32, x32, y32, r, n, FLT_MIN, FLT_MAX,
                  nthreads, "log2f");
  efficiency_f32 (TYPE_JBM_LOG2, thread_f32, x32, y32, r, n, FLT_MIN, FLT_MAX,
                  nthreads, "jbm_f32_log2");
  efficiency_f32 (TYPE_LOG, thread_f32, x32, y32, r, n, FLT_MIN, FLT_MAX,
                  nthreads, "logf");
  efficiency_f32 (TYPE_JBM_LOG, thread_f32, x32, y32, r, n, FLT_MIN, FLT_MAX,
                  nthreads, "jbm_f32_log");
  efficiency_f32 (TYPE_LOG10, thread_f32, x32, y32, r, n, FLT_MIN, FLT_MAX,
                  nthreads, "log10f");
  efficiency_f32 (TYPE_JBM_LOG10, thread_f32, x32, y32, r, n, FLT_MIN, FLT_MAX,
                  nthreads, "jbm_f32_log10");
  efficiency_f32 (TYPE_POW, thread_f32, x32, y32, r, n, 0.f, 100.f, nthreads,
                  "pow");
  efficiency_f32 (TYPE_JBM_POW, thread_f32, x32, y32, r, n, 0.f, 100.f,
                  nthreads, "jbm_f32_pow");
  efficiency_f32 (TYPE_SIN, thread_f32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "sinf");
  efficiency_f32 (TYPE_JBM_SIN, thread_f32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_f32_sin");
  efficiency_f32 (TYPE_COS, thread_f32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "cosf");
  efficiency_f32 (TYPE_JBM_COS, thread_f32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_f32_cos");
  efficiency_f32 (TYPE_TAN, thread_f32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "tanf");
  efficiency_f32 (TYPE_JBM_TAN, thread_f32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_f32_tan");
  efficiency_f32 (TYPE_ATAN, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "atanf");
  efficiency_f32 (TYPE_JBM_ATAN, thread_f32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_f32_atan");
  efficiency_f32 (TYPE_ASIN, thread_f32, x32, y32, r, n, -1.f, 1.f, nthreads,
                  "asinf");
  efficiency_f32 (TYPE_JBM_ASIN, thread_f32, x32, y32, r, n, -1.f, 1.f,
                  nthreads, "jbm_f32_asin");
  efficiency_f32 (TYPE_ACOS, thread_f32, x32, y32, r, n, -1.f, 1.f, nthreads,
                  "acosf");
  efficiency_f32 (TYPE_JBM_ACOS, thread_f32, x32, y32, r, n, -1.f, 1.f,
                  nthreads, "jbm_f32_acos");
  efficiency_f32 (TYPE_SINH, thread_f32, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "sinhf");
  efficiency_f32 (TYPE_JBM_SINH, thread_f32, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "jbm_f32_sinh");
  efficiency_f32 (TYPE_COSH, thread_f32, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "coshf");
  efficiency_f32 (TYPE_JBM_COSH, thread_f32, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "jbm_f32_cosh");
  efficiency_f32 (TYPE_TANH, thread_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "tanhf");
  efficiency_f32 (TYPE_JBM_TANH, thread_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_f32_tanh");
  efficiency_f32 (TYPE_ERF, thread_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "erff");
  efficiency_f32 (TYPE_JBM_ERF, thread_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_f32_erf");
  efficiency_f32 (TYPE_ERFC, thread_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "erfcf");
  efficiency_f32 (TYPE_JBM_ERFC, thread_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_f32_erfc");
  efficiency_f32 (TYPE_JBM_POL1, thread_f32, x32, y32, r, n, 0.f, 1.f, nthreads,
                  "pol1_f32");
  efficiency_f32 (TYPE_JBM_POL2, thread_f32, x32, y32, r, n, 0.f, 1.f, nthreads,
                  "pol2_f32");
  efficiency_f32 (TYPE_JBM_POL3, thread_f32, x32, y32, r, n, 0.f, 1.f, nthreads,
                  "pol3_f32");
  efficiency_f32 (TYPE_JBM_POL4, thread_f32, x32, y32, r, n, 0.f, 1.f, nthreads,
                  "pol4_f32");
  efficiency_f32 (TYPE_JBM_POL5, thread_f32, x32, y32, r, n, 0.f, 1.f, nthreads,
                  "pol5_f32");
  efficiency_f32 (TYPE_JBM_POL6, thread_f32, x32, y32, r, n, 0.f, 1.f, nthreads,
                  "pol6_f32");
  efficiency_f32 (TYPE_JBM_POL7, thread_f32, x32, y32, r, n, 0.f, 1.f, nthreads,
                  "pol7_f32");
  efficiency_f32 (TYPE_JBM_POL8, thread_f32, x32, y32, r, n, 0.f, 1.f, nthreads,
                  "pol8_f32");
  efficiency_f32 (TYPE_JBM_POL9, thread_f32, x32, y32, r, n, 0.f, 1.f, nthreads,
                  "pol9_f32");
  efficiency_f32 (TYPE_JBM_POL10, thread_f32, x32, y32, r, n, 0.f, 1.f,
                  nthreads, "pol10_f32");
  efficiency_f32 (TYPE_JBM_POL11, thread_f32, x32, y32, r, n, 0.f, 1.f,
                  nthreads, "pol11_f32");
  efficiency_f32 (TYPE_JBM_POL12, thread_f32, x32, y32, r, n, 0.f, 1.f,
                  nthreads, "pol12_f32");
  efficiency_f32 (TYPE_JBM_POL13, thread_f32, x32, y32, r, n, 0.f, 1.f,
                  nthreads, "pol13_f32");
  efficiency_f32 (TYPE_JBM_POL14, thread_f32, x32, y32, r, n, 0.f, 1.f,
                  nthreads, "pol14_f32");
  efficiency_f32 (TYPE_JBM_POL15, thread_f32, x32, y32, r, n, 0.f, 1.f,
                  nthreads, "pol15_f32");

  // double functions
  printf ("\ndouble functions\n");
  efficiency_f64 (TYPE_ADD, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "add_f64");
  efficiency_f64 (TYPE_ADD, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "add_f64");
  efficiency_f64 (TYPE_SUB, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "sub_f64");
  efficiency_f64 (TYPE_MUL, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "mul_f64");
  efficiency_f64 (TYPE_DIV, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "div_f64");
  efficiency_f64 (TYPE_SQRT, thread_f64, x64, y64, r, n, 0., DBL_MAX,
                  nthreads, "sqrt");
  efficiency_f64 (TYPE_MAX, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "max_f64");
  efficiency_f64 (TYPE_MIN, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "min_f64");
  efficiency_f64 (TYPE_ROUND, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "round");
  efficiency_f64 (TYPE_FLOOR, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "floor");
  efficiency_f64 (TYPE_CEIL, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "ceil");
  efficiency_f64 (TYPE_TRUNC, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "trunc");
  efficiency_f64 (TYPE_ABS, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "fabs");
  efficiency_f64 (TYPE_JBM_ABS, thread_f64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_f64_abs");
  efficiency_f64 (TYPE_MOD, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "f64_mod");
  efficiency_f64 (TYPE_JBM_MOD, thread_f64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_f64_mod");
  efficiency_f64 (TYPE_CBRT, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "cbrt");
  efficiency_f64 (TYPE_JBM_CBRT, thread_f64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_f64_cbrt");
  efficiency_f64 (TYPE_EXP2, thread_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "exp2");
  efficiency_f64 (TYPE_JBM_EXP2, thread_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_f64_exp2");
  efficiency_f64 (TYPE_EXP, thread_f64, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                  JBM_DBL_MAX_E_EXP, nthreads, "exp");
  efficiency_f64 (TYPE_JBM_EXP, thread_f64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_f64_exp");
  efficiency_f64 (TYPE_EXP10, thread_f64, x64, y64, r, n, -DBL_MAX_10_EXP,
                  DBL_MAX_10_EXP, nthreads, "exp10");
  efficiency_f64 (TYPE_JBM_EXP10, thread_f64, x64, y64, r, n,
                  -DBL_MAX_10_EXP, DBL_MAX_10_EXP, nthreads, "jbm_f64_exp10");
  efficiency_f64 (TYPE_EXPM1, thread_f64, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                  JBM_DBL_MAX_E_EXP, nthreads, "expm1");
  efficiency_f64 (TYPE_JBM_EXPM1, thread_f64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_f64_expm1");
  efficiency_f64 (TYPE_LOG2, thread_f64, x64, y64, r, n, DBL_MIN, DBL_MAX,
                  nthreads, "log2");
  efficiency_f64 (TYPE_JBM_LOG2, thread_f64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_f64_log2");
  efficiency_f64 (TYPE_LOG, thread_f64, x64, y64, r, n, DBL_MIN, DBL_MAX,
                  nthreads, "log");
  efficiency_f64 (TYPE_JBM_LOG, thread_f64, x64, y64, r, n, DBL_MIN, DBL_MAX,
                  nthreads, "jbm_f64_log");
  efficiency_f64 (TYPE_LOG10, thread_f64, x64, y64, r, n, DBL_MIN, DBL_MAX,
                  nthreads, "log10");
  efficiency_f64 (TYPE_JBM_LOG10, thread_f64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_f64_log10");
  efficiency_f64 (TYPE_POW, thread_f64, x64, y64, r, n, 0., 100., nthreads,
                  "pow");
  efficiency_f64 (TYPE_JBM_POW, thread_f64, x64, y64, r, n, 0., 100.,
                  nthreads, "jbm_f64_pow");
  efficiency_f64 (TYPE_SIN, thread_f64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "sin");
  efficiency_f64 (TYPE_JBM_SIN, thread_f64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_f64_sin");
  efficiency_f64 (TYPE_COS, thread_f64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "cos");
  efficiency_f64 (TYPE_JBM_COS, thread_f64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_f64_cos");
  efficiency_f64 (TYPE_TAN, thread_f64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "tan");
  efficiency_f64 (TYPE_JBM_TAN, thread_f64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_f64_tan");
  efficiency_f64 (TYPE_ATAN, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "atan");
  efficiency_f64 (TYPE_JBM_ATAN, thread_f64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_f64_atan");
  efficiency_f64 (TYPE_ASIN, thread_f64, x64, y64, r, n, -1., 1., nthreads,
                  "asin");
  efficiency_f64 (TYPE_JBM_ASIN, thread_f64, x64, y64, r, n, -1., 1.,
                  nthreads, "jbm_f64_asin");
  efficiency_f64 (TYPE_ACOS, thread_f64, x64, y64, r, n, -1., 1., nthreads,
                  "acos");
  efficiency_f64 (TYPE_JBM_ACOS, thread_f64, x64, y64, r, n, -1., 1.,
                  nthreads, "jbm_f64_acos");
  efficiency_f64 (TYPE_SINH, thread_f64, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                  JBM_DBL_MAX_E_EXP, nthreads, "sinh");
  efficiency_f64 (TYPE_JBM_SINH, thread_f64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_f64_sinh");
  efficiency_f64 (TYPE_COSH, thread_f64, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                  JBM_DBL_MAX_E_EXP, nthreads, "cosh");
  efficiency_f64 (TYPE_JBM_COSH, thread_f64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_f64_cosh");
  efficiency_f64 (TYPE_TANH, thread_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "tanh");
  efficiency_f64 (TYPE_JBM_TANH, thread_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_f64_tanh");
  efficiency_f64 (TYPE_ERF, thread_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "erf");
  efficiency_f64 (TYPE_JBM_ERF, thread_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_f64_erf");
  efficiency_f64 (TYPE_ERFC, thread_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "erfc");
  efficiency_f64 (TYPE_JBM_ERFC, thread_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_f64_erfc");
  efficiency_f64 (TYPE_JBM_POL1, thread_f64, x64, y64, r, n, 0., 1.,
                  nthreads, "pol1_f64");
  efficiency_f64 (TYPE_JBM_POL2, thread_f64, x64, y64, r, n, 0., 1.,
                  nthreads, "pol2_f64");
  efficiency_f64 (TYPE_JBM_POL3, thread_f64, x64, y64, r, n, 0., 1.,
                  nthreads, "pol3_f64");
  efficiency_f64 (TYPE_JBM_POL4, thread_f64, x64, y64, r, n, 0., 1.,
                  nthreads, "pol4_f64");
  efficiency_f64 (TYPE_JBM_POL5, thread_f64, x64, y64, r, n, 0., 1.,
                  nthreads, "pol5_f64");
  efficiency_f64 (TYPE_JBM_POL6, thread_f64, x64, y64, r, n, 0., 1.,
                  nthreads, "pol6_f64");
  efficiency_f64 (TYPE_JBM_POL7, thread_f64, x64, y64, r, n, 0., 1.,
                  nthreads, "pol7_f64");
  efficiency_f64 (TYPE_JBM_POL8, thread_f64, x64, y64, r, n, 0., 1.,
                  nthreads, "pol8_f64");
  efficiency_f64 (TYPE_JBM_POL9, thread_f64, x64, y64, r, n, 0., 1.,
                  nthreads, "pol9_f64");
  efficiency_f64 (TYPE_JBM_POL10, thread_f64, x64, y64, r, n, 0., 1.,
                  nthreads, "pol10_f64");
  efficiency_f64 (TYPE_JBM_POL11, thread_f64, x64, y64, r, n, 0., 1.,
                  nthreads, "pol11_f64");
  efficiency_f64 (TYPE_JBM_POL12, thread_f64, x64, y64, r, n, 0., 1.,
                  nthreads, "pol12_f64");
  efficiency_f64 (TYPE_JBM_POL13, thread_f64, x64, y64, r, n, 0., 1.,
                  nthreads, "pol13_f64");
  efficiency_f64 (TYPE_JBM_POL14, thread_f64, x64, y64, r, n, 0., 1.,
                  nthreads, "pol14_f64");
  efficiency_f64 (TYPE_JBM_POL15, thread_f64, x64, y64, r, n, 0., 1.,
                  nthreads, "pol15_f64");

#ifdef __SSE4_2__

  // 4xf32 functions
  printf ("\n4xf32 functions\n");
  efficiency_f32 (TYPE_ADD, thread_4xf32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "add_4xf32");
  efficiency_f32 (TYPE_SUB, thread_4xf32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "sub_4xf32");
  efficiency_f32 (TYPE_MUL, thread_4xf32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "mul_4xf32");
  efficiency_f32 (TYPE_DIV, thread_4xf32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "div_4xf32");
  efficiency_f32 (TYPE_SQRT, thread_4xf32, x32, y32, r, n, 0.f, FLT_MAX,
                  nthreads, "sqrt_4xf32");
  efficiency_f32 (TYPE_MAX, thread_4xf32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "max_4xf32");
  efficiency_f32 (TYPE_MIN, thread_4xf32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "min_4xf32");
  efficiency_f32 (TYPE_JBM_ABS, thread_4xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_4xf32_abs");
  efficiency_f32 (TYPE_JBM_MOD, thread_4xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_4xf32_mod");
  efficiency_f32 (TYPE_JBM_CBRT, thread_4xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_4xf32_cbrt");
  efficiency_f32 (TYPE_JBM_EXP2, thread_4xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_4xf32_exp2");
  efficiency_f32 (TYPE_JBM_EXP, thread_4xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_4xf32_exp");
  efficiency_f32 (TYPE_JBM_EXP10, thread_4xf32, x32, y32, r, n,
                  -FLT_MAX_10_EXP, FLT_MAX_10_EXP, nthreads, "jbm_4xf32_exp10");
  efficiency_f32 (TYPE_JBM_EXPM1, thread_4xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_4xf32_expm1");
  efficiency_f32 (TYPE_JBM_LOG2, thread_4xf32, x32, y32, r, n, FLT_MIN,
                  FLT_MAX, nthreads, "jbm_4xf32_log2");
  efficiency_f32 (TYPE_JBM_LOG, thread_4xf32, x32, y32, r, n, FLT_MIN,
                  FLT_MAX, nthreads, "jbm_4xf32_log");
  efficiency_f32 (TYPE_JBM_LOG10, thread_4xf32, x32, y32, r, n, FLT_MIN,
                  FLT_MAX, nthreads, "jbm_4xf32_log10");
  efficiency_f32 (TYPE_JBM_POW, thread_4xf32, x32, y32, r, n, 0., 100.,
                  nthreads, "jbm_4xf32_pow");
  efficiency_f32 (TYPE_JBM_SIN, thread_4xf32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_4xf32_sin");
  efficiency_f32 (TYPE_JBM_COS, thread_4xf32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_4xf32_cos");
  efficiency_f32 (TYPE_JBM_TAN, thread_4xf32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_4xf32_tan");
  efficiency_f32 (TYPE_JBM_ATAN, thread_4xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_4xf32_atan");
  efficiency_f32 (TYPE_JBM_ASIN, thread_4xf32, x32, y32, r, n, -1.f, 1.f,
                  nthreads, "jbm_4xf32_asin");
  efficiency_f32 (TYPE_JBM_ACOS, thread_4xf32, x32, y32, r, n, -1.f, 1.f,
                  nthreads, "jbm_4xf32_acos");
  efficiency_f32 (TYPE_JBM_SINH, thread_4xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_4xf32_sinh");
  efficiency_f32 (TYPE_JBM_COSH, thread_4xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_4xf32_cosh");
  efficiency_f32 (TYPE_JBM_TANH, thread_4xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_4xf32_tanh");
  efficiency_f32 (TYPE_JBM_ERF, thread_4xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_4xf32_erf");
  efficiency_f32 (TYPE_JBM_ERFC, thread_4xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_4xf32_erfc");

  // 2xf64 functions
  printf ("\n2xf64 functions\n");
  efficiency_f64 (TYPE_ADD, thread_2xf64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "add_2xf64");
  efficiency_f64 (TYPE_SUB, thread_2xf64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "sub_2xf64");
  efficiency_f64 (TYPE_MUL, thread_2xf64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "mul_2xf64");
  efficiency_f64 (TYPE_DIV, thread_2xf64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "div_2xf64");
  efficiency_f64 (TYPE_SQRT, thread_2xf64, x64, y64, r, n, 0., DBL_MAX,
                  nthreads, "sqrt_2xf64");
  efficiency_f64 (TYPE_MAX, thread_2xf64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "max_2xf64");
  efficiency_f64 (TYPE_MIN, thread_2xf64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "min_2xf64");
  efficiency_f64 (TYPE_JBM_ABS, thread_2xf64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_2xf64_abs");
  efficiency_f64 (TYPE_JBM_MOD, thread_2xf64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_2xf64_mod");
  efficiency_f64 (TYPE_JBM_CBRT, thread_2xf64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_2xf64_cbrt");
  efficiency_f64 (TYPE_JBM_EXP2, thread_2xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_2xf64_exp2");
  efficiency_f64 (TYPE_JBM_EXP, thread_2xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_2xf64_exp");
  efficiency_f64 (TYPE_JBM_EXP10, thread_2xf64, x64, y64, r, n,
                  -DBL_MAX_10_EXP, DBL_MAX_10_EXP, nthreads, "jbm_2xf64_exp10");
  efficiency_f64 (TYPE_JBM_EXPM1, thread_2xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_2xf64_expm1");
  efficiency_f64 (TYPE_JBM_LOG2, thread_2xf64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_2xf64_log2");
  efficiency_f64 (TYPE_JBM_LOG, thread_2xf64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_2xf64_log");
  efficiency_f64 (TYPE_JBM_LOG10, thread_2xf64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_2xf64_log10");
  efficiency_f64 (TYPE_JBM_POW, thread_2xf64, x64, y64, r, n, 0., 100.,
                  nthreads, "jbm_2xf64_pow");
  efficiency_f64 (TYPE_JBM_SIN, thread_2xf64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_2xf64_sin");
  efficiency_f64 (TYPE_JBM_COS, thread_2xf64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_2xf64_cos");
  efficiency_f64 (TYPE_JBM_TAN, thread_2xf64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_2xf64_tan");
  efficiency_f64 (TYPE_JBM_ATAN, thread_2xf64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_2xf64_atan");
  efficiency_f64 (TYPE_JBM_ASIN, thread_2xf64, x64, y64, r, n, -1., 1.,
                  nthreads, "jbm_2xf64_asin");
  efficiency_f64 (TYPE_JBM_ACOS, thread_2xf64, x64, y64, r, n, -1., 1.,
                  nthreads, "jbm_2xf64_acos");
  efficiency_f64 (TYPE_JBM_SINH, thread_2xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_2xf64_sinh");
  efficiency_f64 (TYPE_JBM_COSH, thread_2xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_2xf64_cosh");
  efficiency_f64 (TYPE_JBM_TANH, thread_2xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_2xf64_tanh");
  efficiency_f64 (TYPE_JBM_ERF, thread_2xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_2xf64_erf");
  efficiency_f64 (TYPE_JBM_ERFC, thread_2xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_2xf64_erfc");

#endif

#ifdef __AVX__

  // 8xf32 functions
  printf ("\n8xf32 functions\n");
  efficiency_f32 (TYPE_ADD, thread_8xf32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "add_8xf32");
  efficiency_f32 (TYPE_SUB, thread_8xf32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "sub_8xf32");
  efficiency_f32 (TYPE_MUL, thread_8xf32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "mul_8xf32");
  efficiency_f32 (TYPE_DIV, thread_8xf32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "div_8xf32");
  efficiency_f32 (TYPE_SQRT, thread_8xf32, x32, y32, r, n, 0.f, FLT_MAX,
                  nthreads, "sqrt_8xf32");
  efficiency_f32 (TYPE_MAX, thread_8xf32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "max_8xf32");
  efficiency_f32 (TYPE_MIN, thread_8xf32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "min_8xf32");
  efficiency_f32 (TYPE_JBM_ABS, thread_8xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_8xf32_abs");
  efficiency_f32 (TYPE_JBM_MOD, thread_8xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_8xf32_mod");
  efficiency_f32 (TYPE_JBM_CBRT, thread_8xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_8xf32_cbrt");
  efficiency_f32 (TYPE_JBM_EXP2, thread_8xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_8xf32_exp2");
  efficiency_f32 (TYPE_JBM_EXP, thread_8xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_8xf32_exp");
  efficiency_f32 (TYPE_JBM_EXP10, thread_8xf32, x32, y32, r, n,
                  -FLT_MAX_10_EXP, FLT_MAX_10_EXP, nthreads, "jbm_8xf32_exp10");
  efficiency_f32 (TYPE_JBM_EXPM1, thread_8xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_8xf32_expm1");
  efficiency_f32 (TYPE_JBM_LOG2, thread_8xf32, x32, y32, r, n, FLT_MIN,
                  FLT_MAX, nthreads, "jbm_8xf32_log2");
  efficiency_f32 (TYPE_JBM_LOG, thread_8xf32, x32, y32, r, n, FLT_MIN,
                  FLT_MAX, nthreads, "jbm_8xf32_log");
  efficiency_f32 (TYPE_JBM_LOG10, thread_8xf32, x32, y32, r, n, FLT_MIN,
                  FLT_MAX, nthreads, "jbm_8xf32_log10");
  efficiency_f32 (TYPE_JBM_POW, thread_8xf32, x32, y32, r, n, 0., 100.,
                  nthreads, "jbm_8xf32_pow");
  efficiency_f32 (TYPE_JBM_SIN, thread_8xf32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_8xf32_sin");
  efficiency_f32 (TYPE_JBM_COS, thread_8xf32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_8xf32_cos");
  efficiency_f32 (TYPE_JBM_TAN, thread_8xf32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_8xf32_tan");
  efficiency_f32 (TYPE_JBM_ATAN, thread_8xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_8xf32_atan");
  efficiency_f32 (TYPE_JBM_ASIN, thread_8xf32, x32, y32, r, n, -1.f, 1.f,
                  nthreads, "jbm_8xf32_asin");
  efficiency_f32 (TYPE_JBM_ACOS, thread_8xf32, x32, y32, r, n, -1.f, 1.f,
                  nthreads, "jbm_8xf32_acos");
  efficiency_f32 (TYPE_JBM_SINH, thread_8xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_8xf32_sinh");
  efficiency_f32 (TYPE_JBM_COSH, thread_8xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_8xf32_cosh");
  efficiency_f32 (TYPE_JBM_TANH, thread_8xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_8xf32_tanh");
  efficiency_f32 (TYPE_JBM_ERF, thread_8xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_8xf32_erf");
  efficiency_f32 (TYPE_JBM_ERFC, thread_8xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_8xf32_erfc");

  // 4xf64 functions
  printf ("\n4xf64 functions\n");
  efficiency_f64 (TYPE_ADD, thread_4xf64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "add_4xf64");
  efficiency_f64 (TYPE_SUB, thread_4xf64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "sub_4xf64");
  efficiency_f64 (TYPE_MUL, thread_4xf64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "mul_4xf64");
  efficiency_f64 (TYPE_DIV, thread_4xf64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "div_4xf64");
  efficiency_f64 (TYPE_SQRT, thread_4xf64, x64, y64, r, n, 0., DBL_MAX,
                  nthreads, "sqrt_4xf64");
  efficiency_f64 (TYPE_MAX, thread_4xf64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "max_4xf64");
  efficiency_f64 (TYPE_MIN, thread_4xf64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "min_4xf64");
  efficiency_f64 (TYPE_JBM_ABS, thread_4xf64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_4xf64_abs");
  efficiency_f64 (TYPE_JBM_MOD, thread_4xf64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_4xf64_mod");
  efficiency_f64 (TYPE_JBM_CBRT, thread_4xf64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_4xf64_cbrt");
  efficiency_f64 (TYPE_JBM_EXP2, thread_4xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_4xf64_exp2");
  efficiency_f64 (TYPE_JBM_EXP, thread_4xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_4xf64_exp");
  efficiency_f64 (TYPE_JBM_EXP10, thread_4xf64, x64, y64, r, n,
                  -DBL_MAX_10_EXP, DBL_MAX_10_EXP, nthreads, "jbm_4xf64_exp10");
  efficiency_f64 (TYPE_JBM_EXPM1, thread_4xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_4xf64_expm1");
  efficiency_f64 (TYPE_JBM_LOG2, thread_4xf64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_4xf64_log2");
  efficiency_f64 (TYPE_JBM_LOG, thread_4xf64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_4xf64_log");
  efficiency_f64 (TYPE_JBM_LOG10, thread_4xf64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_4xf64_log10");
  efficiency_f64 (TYPE_JBM_POW, thread_4xf64, x64, y64, r, n, 0., 100.,
                  nthreads, "jbm_4xf64_pow");
  efficiency_f64 (TYPE_JBM_SIN, thread_4xf64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_4xf64_sin");
  efficiency_f64 (TYPE_JBM_COS, thread_4xf64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_4xf64_cos");
  efficiency_f64 (TYPE_JBM_TAN, thread_4xf64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_4xf64_tan");
  efficiency_f64 (TYPE_JBM_ATAN, thread_4xf64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_4xf64_atan");
  efficiency_f64 (TYPE_JBM_ASIN, thread_4xf64, x64, y64, r, n, -1., 1.,
                  nthreads, "jbm_4xf64_asin");
  efficiency_f64 (TYPE_JBM_ACOS, thread_4xf64, x64, y64, r, n, -1., 1.,
                  nthreads, "jbm_4xf64_acos");
  efficiency_f64 (TYPE_JBM_SINH, thread_4xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_4xf64_sinh");
  efficiency_f64 (TYPE_JBM_COSH, thread_4xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_4xf64_cosh");
  efficiency_f64 (TYPE_JBM_TANH, thread_4xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_4xf64_tanh");
  efficiency_f64 (TYPE_JBM_ERF, thread_4xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_4xf64_erf");
  efficiency_f64 (TYPE_JBM_ERFC, thread_4xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_4xf64_erfc");

#endif

#ifdef __AVX512F__

  // 16xf32 functions
  printf ("\n16xf32 functions\n");
  efficiency_f32 (TYPE_ADD, thread_16xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "add_16xf32");
  efficiency_f32 (TYPE_SUB, thread_16xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "sub_16xf32");
  efficiency_f32 (TYPE_MUL, thread_16xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "mul_16xf32");
  efficiency_f32 (TYPE_DIV, thread_16xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "div_16xf32");
  efficiency_f32 (TYPE_SQRT, thread_16xf32, x32, y32, r, n, 0.f, FLT_MAX,
                  nthreads, "sqrt_16xf32");
  efficiency_f32 (TYPE_MAX, thread_16xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "max_16xf32");
  efficiency_f32 (TYPE_MIN, thread_16xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "min_16xf32");
  efficiency_f32 (TYPE_JBM_ABS, thread_16xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_16xf32_abs");
  efficiency_f32 (TYPE_JBM_MOD, thread_16xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_16xf32_mod");
  efficiency_f32 (TYPE_JBM_CBRT, thread_16xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_16xf32_cbrt");
  efficiency_f32 (TYPE_JBM_EXP2, thread_16xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_16xf32_exp2");
  efficiency_f32 (TYPE_JBM_EXP, thread_16xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_16xf32_exp");
  efficiency_f32 (TYPE_JBM_EXP10, thread_16xf32, x32, y32, r, n,
                  -FLT_MAX_10_EXP, FLT_MAX_10_EXP, nthreads,
                  "jbm_16xf32_exp10");
  efficiency_f32 (TYPE_JBM_EXPM1, thread_16xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_16xf32_expm1");
  efficiency_f32 (TYPE_JBM_LOG2, thread_16xf32, x32, y32, r, n, FLT_MIN,
                  FLT_MAX, nthreads, "jbm_16xf32_log2");
  efficiency_f32 (TYPE_JBM_LOG, thread_16xf32, x32, y32, r, n, FLT_MIN, FLT_MAX,
                  nthreads, "jbm_16xf32_log");
  efficiency_f32 (TYPE_JBM_LOG10, thread_16xf32, x32, y32, r, n, FLT_MIN,
                  FLT_MAX, nthreads, "jbm_16xf32_log10");
  efficiency_f32 (TYPE_JBM_POW, thread_16xf32, x32, y32, r, n, 0., 100.,
                  nthreads, "jbm_16xf32_pow");
  efficiency_f32 (TYPE_JBM_SIN, thread_16xf32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_16xf32_sin");
  efficiency_f32 (TYPE_JBM_COS, thread_16xf32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_16xf32_cos");
  efficiency_f32 (TYPE_JBM_TAN, thread_16xf32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_16xf32_tan");
  efficiency_f32 (TYPE_JBM_ATAN, thread_16xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_16xf32_atan");
  efficiency_f32 (TYPE_JBM_ASIN, thread_16xf32, x32, y32, r, n, -1.f, 1.f,
                  nthreads, "jbm_16xf32_asin");
  efficiency_f32 (TYPE_JBM_ACOS, thread_16xf32, x32, y32, r, n, -1.f, 1.f,
                  nthreads, "jbm_16xf32_acos");
  efficiency_f32 (TYPE_JBM_SINH, thread_16xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_16xf32_sinh");
  efficiency_f32 (TYPE_JBM_COSH, thread_16xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_16xf32_cosh");
  efficiency_f32 (TYPE_JBM_TANH, thread_16xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_16xf32_tanh");
  efficiency_f32 (TYPE_JBM_ERF, thread_16xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_16xf32_erf");
  efficiency_f32 (TYPE_JBM_ERFC, thread_16xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_16xf32_erfc");

  // 8xf64 functions
  printf ("\n8xf64 functions\n");
  efficiency_f64 (TYPE_ADD, thread_8xf64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "add_8xf64");
  efficiency_f64 (TYPE_SUB, thread_8xf64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "sub_8xf64");
  efficiency_f64 (TYPE_MUL, thread_8xf64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "mul_8xf64");
  efficiency_f64 (TYPE_DIV, thread_8xf64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "div_8xf64");
  efficiency_f64 (TYPE_SQRT, thread_8xf64, x64, y64, r, n, 0., DBL_MAX,
                  nthreads, "sqrt_8xf64");
  efficiency_f64 (TYPE_MAX, thread_8xf64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "max_8xf64");
  efficiency_f64 (TYPE_MIN, thread_8xf64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "min_8xf64");
  efficiency_f64 (TYPE_JBM_ABS, thread_8xf64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_8xf64_abs");
  efficiency_f64 (TYPE_JBM_MOD, thread_8xf64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_8xf64_abs");
  efficiency_f64 (TYPE_JBM_CBRT, thread_8xf64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_8xf64_cbrt");
  efficiency_f64 (TYPE_JBM_EXP2, thread_8xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_8xf64_exp2");
  efficiency_f64 (TYPE_JBM_EXP, thread_8xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_8xf64_exp");
  efficiency_f64 (TYPE_JBM_EXP10, thread_8xf64, x64, y64, r, n,
                  -DBL_MAX_10_EXP, DBL_MAX_10_EXP, nthreads, "jbm_8xf64_exp10");
  efficiency_f64 (TYPE_JBM_EXPM1, thread_8xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_8xf64_expm1");
  efficiency_f64 (TYPE_JBM_LOG2, thread_8xf64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_8xf64_log2");
  efficiency_f64 (TYPE_JBM_LOG, thread_8xf64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_8xf64_log");
  efficiency_f64 (TYPE_JBM_LOG10, thread_8xf64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_8xf64_log10");
  efficiency_f64 (TYPE_JBM_POW, thread_8xf64, x64, y64, r, n, 0., 100.,
                  nthreads, "jbm_8xf64_pow");
  efficiency_f64 (TYPE_JBM_SIN, thread_8xf64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_8xf64_sin");
  efficiency_f64 (TYPE_JBM_COS, thread_8xf64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_8xf64_cos");
  efficiency_f64 (TYPE_JBM_TAN, thread_8xf64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_8xf64_tan");
  efficiency_f64 (TYPE_JBM_ATAN, thread_8xf64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_8xf64_atan");
  efficiency_f64 (TYPE_JBM_ASIN, thread_8xf64, x64, y64, r, n, -1., 1.,
                  nthreads, "jbm_8xf64_asin");
  efficiency_f64 (TYPE_JBM_ACOS, thread_8xf64, x64, y64, r, n, -1., 1.,
                  nthreads, "jbm_8xf64_acos");
  efficiency_f64 (TYPE_JBM_SINH, thread_8xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_8xf64_sinh");
  efficiency_f64 (TYPE_JBM_COSH, thread_8xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_8xf64_cosh");
  efficiency_f64 (TYPE_JBM_TANH, thread_8xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_8xf64_tanh");
  efficiency_f64 (TYPE_JBM_ERF, thread_8xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_8xf64_erf");
  efficiency_f64 (TYPE_JBM_ERFC, thread_8xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_8xf64_erfc");

#endif

  printf ("\narray_f32 functions\n");
  efficiency_f32 (TYPE_ADD, thread_array_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "add_array_f32");
  efficiency_f32 (TYPE_SUB, thread_array_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "sub_array_f32");
  efficiency_f32 (TYPE_MUL, thread_array_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "mul_array_f32");
  efficiency_f32 (TYPE_DIV, thread_array_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "div_array_f32");
  efficiency_f32 (TYPE_SQRT, thread_array_f32, x32, y32, r, n, 0.f, FLT_MAX,
                  nthreads, "sqrt_array_f32");
  efficiency_f32 (TYPE_MAX, thread_array_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "max_array_f32");
  efficiency_f32 (TYPE_MIN, thread_array_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "min_array_f32");
  efficiency_f32 (TYPE_JBM_ABS, thread_array_f32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_array_f32_abs");
  efficiency_f32 (TYPE_JBM_MOD, thread_array_f32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_array_f32_mod");
  efficiency_f32 (TYPE_JBM_CBRT, thread_array_f32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_array_f32_cbrt");
  efficiency_f32 (TYPE_JBM_EXP2, thread_array_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_array_f32_exp2");
  efficiency_f32 (TYPE_JBM_EXP, thread_array_f32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_array_f32_exp");
  efficiency_f32 (TYPE_JBM_EXP10, thread_array_f32, x32, y32, r, n,
                  -FLT_MAX_10_EXP, FLT_MAX_10_EXP, nthreads,
                  "jbm_array_f32_exp10");
  efficiency_f32 (TYPE_JBM_EXPM1, thread_array_f32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_array_f32_expm1");
  efficiency_f32 (TYPE_JBM_LOG2, thread_array_f32, x32, y32, r, n, FLT_MIN,
                  FLT_MAX, nthreads, "jbm_array_f32_log2");
  efficiency_f32 (TYPE_JBM_LOG, thread_array_f32, x32, y32, r, n, FLT_MIN,
                  FLT_MAX, nthreads, "jbm_array_f32_log");
  efficiency_f32 (TYPE_JBM_LOG10, thread_array_f32, x32, y32, r, n, FLT_MIN,
                  FLT_MAX, nthreads, "jbm_array_f32_log10");
  efficiency_f32 (TYPE_JBM_POW, thread_array_f32, x32, y32, r, n, 0., 100.,
                  nthreads, "jbm_array_f32_pow");
  efficiency_f32 (TYPE_JBM_SIN, thread_array_f32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_array_f32_sin");
  efficiency_f32 (TYPE_JBM_COS, thread_array_f32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_array_f32_cos");
  efficiency_f32 (TYPE_JBM_TAN, thread_array_f32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_array_f32_tan");
  efficiency_f32 (TYPE_JBM_ATAN, thread_array_f32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_array_f32_atan");
  efficiency_f32 (TYPE_JBM_ASIN, thread_array_f32, x32, y32, r, n, -1.f, 1.f,
                  nthreads, "jbm_array_f32_asin");
  efficiency_f32 (TYPE_JBM_ACOS, thread_array_f32, x32, y32, r, n, -1.f, 1.f,
                  nthreads, "jbm_array_f32_acos");
  efficiency_f32 (TYPE_JBM_SINH, thread_array_f32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_array_f32_sinh");
  efficiency_f32 (TYPE_JBM_COSH, thread_array_f32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_array_f32_cosh");
  efficiency_f32 (TYPE_JBM_TANH, thread_array_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_array_f32_tanh");
  efficiency_f32 (TYPE_JBM_ERF, thread_array_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_array_f32_erf");
  efficiency_f32 (TYPE_JBM_ERFC, thread_array_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_array_f32_erfc");

  printf ("\narray_f64 functions\n");
  efficiency_f64 (TYPE_ADD, thread_array_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "add_array_f64");
  efficiency_f64 (TYPE_SUB, thread_array_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "sub_array_f64");
  efficiency_f64 (TYPE_MUL, thread_array_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "mul_array_f64");
  efficiency_f64 (TYPE_DIV, thread_array_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "div_array_f64");
  efficiency_f64 (TYPE_SQRT, thread_array_f64, x64, y64, r, n, 0., DBL_MAX,
                  nthreads, "sqrt_array_f64");
  efficiency_f64 (TYPE_MAX, thread_array_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "max_array_f64");
  efficiency_f64 (TYPE_MIN, thread_array_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "min_array_f64");
  efficiency_f64 (TYPE_JBM_ABS, thread_array_f64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_array_f64_abs");
  efficiency_f64 (TYPE_JBM_MOD, thread_array_f64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_array_f64_mod");
  efficiency_f64 (TYPE_JBM_CBRT, thread_array_f64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_array_f64_cbrt");
  efficiency_f64 (TYPE_JBM_EXP2, thread_array_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_array_f64_exp2");
  efficiency_f64 (TYPE_JBM_EXP, thread_array_f64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_array_f64_exp");
  efficiency_f64 (TYPE_JBM_EXP10, thread_array_f64, x64, y64, r, n,
                  -DBL_MAX_10_EXP, DBL_MAX_10_EXP, nthreads,
                  "jbm_array_f64_exp10");
  efficiency_f64 (TYPE_JBM_EXPM1, thread_array_f64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_array_f64_expm1");
  efficiency_f64 (TYPE_JBM_LOG2, thread_array_f64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_array_f64_log2");
  efficiency_f64 (TYPE_JBM_LOG, thread_array_f64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_array_f64_log");
  efficiency_f64 (TYPE_JBM_LOG10, thread_array_f64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_array_f64_log10");
  efficiency_f64 (TYPE_JBM_POW, thread_array_f64, x64, y64, r, n, 0., 100.,
                  nthreads, "jbm_array_f64_pow");
  efficiency_f64 (TYPE_JBM_SIN, thread_array_f64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_array_f64_sin");
  efficiency_f64 (TYPE_JBM_COS, thread_array_f64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_array_f64_cos");
  efficiency_f64 (TYPE_JBM_TAN, thread_array_f64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_array_f64_tan");
  efficiency_f64 (TYPE_JBM_ATAN, thread_array_f64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_array_f64_atan");
  efficiency_f64 (TYPE_JBM_ASIN, thread_array_f64, x64, y64, r, n, -1., 1.,
                  nthreads, "jbm_array_f64_asin");
  efficiency_f64 (TYPE_JBM_ACOS, thread_array_f64, x64, y64, r, n, -1., 1.,
                  nthreads, "jbm_array_f64_acos");
  efficiency_f64 (TYPE_JBM_SINH, thread_array_f64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_array_f64_sinh");
  efficiency_f64 (TYPE_JBM_COSH, thread_array_f64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_array_f64_cosh");
  efficiency_f64 (TYPE_JBM_TANH, thread_array_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_array_f64_tanh");
  efficiency_f64 (TYPE_JBM_ERF, thread_array_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_array_f64_erf");
  efficiency_f64 (TYPE_JBM_ERFC, thread_array_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_array_f64_erfc");

  // free memory
  g_mutex_clear (&mutex);
  free (r);
  JB_FREE (y64);
  JB_FREE (x64);

  return 0;
}
