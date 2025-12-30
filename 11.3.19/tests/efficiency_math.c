#include "../src/math.h"
#include <gsl/gsl_rng.h>
#include <glib.h>

#define SEED 7l
#define POL_HORNER 1
#define POL_ESTRIN 2
#define POL POL_HORNER

// parallel bucle
#define BUCLE(imin, imax, f) \
  for (i = imin; i < imax; ++i) y[i] = f(x[i])

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
  TYPE_ABS,
  TYPE_EXP2,
  TYPE_EXP,
  TYPE_EXP10,
  TYPE_EXPM1,
  TYPE_CBRT,
  TYPE_LOG2,
  TYPE_LOG,
  TYPE_LOG10,
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
  TYPE_JBM_EXP2,
  TYPE_JBM_EXP,
  TYPE_JBM_EXP10,
  TYPE_JBM_EXPM1,
  TYPE_JBM_CBRT,
  TYPE_JBM_LOG2,
  TYPE_JBM_LOG,
  TYPE_JBM_LOG10,
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
  unsigned int type;
  unsigned long int imin;
  unsigned long int imax;
  float *x;
  float *y;
} Parallel_f32;

typedef struct
{
  unsigned int type;
  unsigned long int imin;
  unsigned long int imax;
  double *x;
  double *y;
} Parallel_f64;

// global coefficients
const float a32[17] = { 1.f, 2.f, 4.f, 8.f, 16.f, 32.f, 64.f, 128.f, 256.f,
  512.f, 1024.f, 2048.f, 4096.f, 8192.f, 16384.f, 32768.f, 65536.f };
const double a64[17] = { 1., 2., 4., 8., 16., 32., 64., 128., 256.,
  512., 1024., 2048., 4096., 8192., 16384., 32768., 65536. };
const long double a80[17] = { 1.L, 2.L, 4.L, 8.L, 16.L, 32.L, 64.L, 128.L,
  256.L, 512.L, 1024.L, 2048.L, 4096.L, 8192.L, 16384.L, 32768.L, 65536.L };

// crono function
static inline double
crono ()
{
  struct timespec t;
  clock_gettime (CLOCK_MONOTONIC, &t);
  return t.tv_sec + 1e-9 * t.tv_nsec;
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

// error functions

static inline long double
error_f32 (unsigned int type, float *x, float *y, unsigned int n)
{
  long double g, em;
  unsigned int i;
  for (i = 0, em = 0.L; i < n; ++i)
    {
      switch (type)
        {
        case TYPE_ADD:
          g = add_f80 ((long double) x[i]);
          break;
        case TYPE_SUB:
          g = sub_f80 ((long double) x[i]);
          break;
        case TYPE_MUL:
          g = mul_f80 ((long double) x[i]);
          break;
        case TYPE_DIV:
          g = div_f80 ((long double) x[i]);
          break;
        case TYPE_SQRT:
          g = sqrtl ((long double) x[i]);
          break;
        case TYPE_MAX:
          g = max_f80 ((long double) x[i]);
          break;
        case TYPE_MIN:
          g = min_f80 ((long double) x[i]);
          break;
        case TYPE_ABS:
          g = fabsl ((long double) x[i]);
          break;
        case TYPE_EXP2:
          g = exp2l ((long double) x[i]);
          break;
        case TYPE_EXP:
          g = expl ((long double) x[i]);
          break;
        case TYPE_EXP10:
          g = exp10l ((long double) x[i]);
          break;
        case TYPE_EXPM1:
          g = expm1l ((long double) x[i]);
          break;
        case TYPE_CBRT:
          g = cbrtl ((long double) x[i]);
          break;
        case TYPE_LOG2:
          g = log2l ((long double) x[i]);
          break;
        case TYPE_LOG:
          g = logl ((long double) x[i]);
          break;
        case TYPE_LOG10:
          g = log10l ((long double) x[i]);
          break;
        case TYPE_SIN:
          g = sinl ((long double) x[i]);
          break;
        case TYPE_COS:
          g = cosl ((long double) x[i]);
          break;
        case TYPE_TAN:
          g = tanl ((long double) x[i]);
          break;
        case TYPE_ATAN:
          g = atanl ((long double) x[i]);
          break;
        case TYPE_ASIN:
          g = asinl ((long double) x[i]);
          break;
        case TYPE_ACOS:
          g = acosl ((long double) x[i]);
          break;
        case TYPE_SINH:
          g = sinhl ((long double) x[i]);
          break;
        case TYPE_COSH:
          g = coshl ((long double) x[i]);
          break;
        case TYPE_TANH:
          g = tanhl ((long double) x[i]);
          break;
        case TYPE_ERF:
          g = erfl ((long double) x[i]);
          break;
        case TYPE_ERFC:
          g = erfcl ((long double) x[i]);
          break;
        case TYPE_JBM_ABS:
          g = fabsl ((long double) x[i]);
          break;
        case TYPE_JBM_EXP2:
          g = exp2l ((long double) x[i]);
          break;
        case TYPE_JBM_EXP:
          g = expl ((long double) x[i]);
          break;
        case TYPE_JBM_EXP10:
          g = exp10l ((long double) x[i]);
          break;
        case TYPE_JBM_EXPM1:
          g = expm1l ((long double) x[i]);
          break;
        case TYPE_JBM_CBRT:
          g = cbrtl ((long double) x[i]);
          break;
        case TYPE_JBM_LOG2:
          g = log2l ((long double) x[i]);
          break;
        case TYPE_JBM_LOG:
          g = logl ((long double) x[i]);
          break;
        case TYPE_JBM_LOG10:
          g = log10l ((long double) x[i]);
          break;
        case TYPE_JBM_SIN:
          g = sinl ((long double) x[i]);
          break;
        case TYPE_JBM_COS:
          g = cosl ((long double) x[i]);
          break;
        case TYPE_JBM_TAN:
          g = tanl ((long double) x[i]);
          break;
        case TYPE_JBM_ATAN:
          g = atanl ((long double) x[i]);
          break;
        case TYPE_JBM_ASIN:
          g = asinl ((long double) x[i]);
          break;
        case TYPE_JBM_ACOS:
          g = acosl ((long double) x[i]);
          break;
        case TYPE_JBM_SINH:
          g = sinhl ((long double) x[i]);
          break;
        case TYPE_JBM_COSH:
          g = coshl ((long double) x[i]);
          break;
        case TYPE_JBM_TANH:
          g = tanhl ((long double) x[i]);
          break;
        case TYPE_JBM_ERF:
          g = erfl ((long double) x[i]);
          break;
        case TYPE_JBM_ERFC:
          g = erfcl ((long double) x[i]);
          break;
        case TYPE_JBM_POL1:
          g = pol1_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL2:
          g = pol2_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL3:
          g = pol3_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL4:
          g = pol4_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL5:
          g = pol5_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL6:
          g = pol6_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL7:
          g = pol7_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL8:
          g = pol8_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL9:
          g = pol9_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL10:
          g = pol10_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL11:
          g = pol11_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL12:
          g = pol12_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL13:
          g = pol13_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL14:
          g = pol14_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL15:
          g = pol15_f80 ((long double) x[i]);
          break;
        }
      em = fmaxl (em, fabsl ((long double) y[i] - g));
    }
  return em;
}

static inline long double
error_f64 (unsigned int type, double *x, double *y, unsigned int n)
{
  long double g, em;
  unsigned int i;
  for (i = 0, em = 0.L; i < n; ++i)
    {
      switch (type)
        {
        case TYPE_ADD:
          g = add_f80 ((long double) x[i]);
          break;
        case TYPE_SUB:
          g = sub_f80 ((long double) x[i]);
          break;
        case TYPE_MUL:
          g = mul_f80 ((long double) x[i]);
          break;
        case TYPE_DIV:
          g = div_f80 ((long double) x[i]);
          break;
        case TYPE_SQRT:
          g = sqrtl ((long double) x[i]);
          break;
        case TYPE_MAX:
          g = max_f80 ((long double) x[i]);
          break;
        case TYPE_MIN:
          g = min_f80 ((long double) x[i]);
          break;
        case TYPE_ABS:
          g = fabsl ((long double) x[i]);
          break;
        case TYPE_EXP2:
          g = exp2l ((long double) x[i]);
          break;
        case TYPE_EXP:
          g = expl ((long double) x[i]);
          break;
        case TYPE_EXP10:
          g = exp10l ((long double) x[i]);
          break;
        case TYPE_EXPM1:
          g = expm1l ((long double) x[i]);
          break;
        case TYPE_CBRT:
          g = cbrtl ((long double) x[i]);
          break;
        case TYPE_LOG2:
          g = log2l ((long double) x[i]);
          break;
        case TYPE_LOG:
          g = logl ((long double) x[i]);
          break;
        case TYPE_LOG10:
          g = log10l ((long double) x[i]);
          break;
        case TYPE_SIN:
          g = sinl ((long double) x[i]);
          break;
        case TYPE_COS:
          g = cosl ((long double) x[i]);
          break;
        case TYPE_TAN:
          g = tanl ((long double) x[i]);
          break;
        case TYPE_ATAN:
          g = atanl ((long double) x[i]);
          break;
        case TYPE_ASIN:
          g = asinl ((long double) x[i]);
          break;
        case TYPE_ACOS:
          g = acosl ((long double) x[i]);
          break;
        case TYPE_SINH:
          g = sinhl ((long double) x[i]);
          break;
        case TYPE_COSH:
          g = coshl ((long double) x[i]);
          break;
        case TYPE_TANH:
          g = tanhl ((long double) x[i]);
          break;
        case TYPE_ERF:
          g = erfl ((long double) x[i]);
          break;
        case TYPE_ERFC:
          g = erfcl ((long double) x[i]);
          break;
        case TYPE_JBM_ABS:
          g = fabsl ((long double) x[i]);
          break;
        case TYPE_JBM_EXP2:
          g = exp2l ((long double) x[i]);
          break;
        case TYPE_JBM_EXP:
          g = expl ((long double) x[i]);
          break;
        case TYPE_JBM_EXP10:
          g = exp10l ((long double) x[i]);
          break;
        case TYPE_JBM_EXPM1:
          g = expm1l ((long double) x[i]);
          break;
        case TYPE_JBM_CBRT:
          g = cbrtl ((long double) x[i]);
          break;
        case TYPE_JBM_LOG2:
          g = log2l ((long double) x[i]);
          break;
        case TYPE_JBM_LOG:
          g = logl ((long double) x[i]);
          break;
        case TYPE_JBM_LOG10:
          g = log10l ((long double) x[i]);
          break;
        case TYPE_JBM_SIN:
          g = sinl ((long double) x[i]);
          break;
        case TYPE_JBM_COS:
          g = cosl ((long double) x[i]);
          break;
        case TYPE_JBM_TAN:
          g = tanl ((long double) x[i]);
          break;
        case TYPE_JBM_ATAN:
          g = atanl ((long double) x[i]);
          break;
        case TYPE_JBM_ASIN:
          g = asinl ((long double) x[i]);
          break;
        case TYPE_JBM_ACOS:
          g = acosl ((long double) x[i]);
          break;
        case TYPE_JBM_SINH:
          g = sinhl ((long double) x[i]);
          break;
        case TYPE_JBM_COSH:
          g = coshl ((long double) x[i]);
          break;
        case TYPE_JBM_TANH:
          g = tanhl ((long double) x[i]);
          break;
        case TYPE_JBM_ERF:
          g = erfl ((long double) x[i]);
          break;
        case TYPE_JBM_ERFC:
          g = erfcl ((long double) x[i]);
          break;
        case TYPE_JBM_POL1:
          g = pol1_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL2:
          g = pol2_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL3:
          g = pol3_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL4:
          g = pol4_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL5:
          g = pol5_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL6:
          g = pol6_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL7:
          g = pol7_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL8:
          g = pol8_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL9:
          g = pol9_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL10:
          g = pol10_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL11:
          g = pol11_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL12:
          g = pol12_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL13:
          g = pol13_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL14:
          g = pol14_f80 ((long double) x[i]);
          break;
        case TYPE_JBM_POL15:
          g = pol15_f80 ((long double) x[i]);
          break;
        }
      em = fmaxl (em, fabsl ((long double) y[i] - g));
    }
  return em;
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

static inline void
thread_f32 (void *data, void *user_data __attribute__((unused)))
{
  Parallel_f32 *p;
  volatile float *x, *y;
  unsigned long int i, imin, imax;
  p = (Parallel_f32 *) data;
  x = p->x;
  y = p->y;
  imin = p->imin;
  imax = p->imax;
  switch (p->type)
    {
    case TYPE_ADD:
      BUCLE (imin, imax, add_f32);
      break;
    case TYPE_SUB:
      BUCLE (imin, imax, sub_f32);
      break;
    case TYPE_MUL:
      BUCLE (imin, imax, mul_f32);
      break;
    case TYPE_DIV:
      BUCLE (imin, imax, div_f32);
      break;
    case TYPE_SQRT:
      BUCLE (imin, imax, sqrtf);
      break;
    case TYPE_MAX:
      BUCLE (imin, imax, max_f32);
      break;
    case TYPE_MIN:
      BUCLE (imin, imax, min_f32);
      break;
    case TYPE_ABS:
      BUCLE (imin, imax, fabsf);
      break;
    case TYPE_EXP2:
      BUCLE (imin, imax, exp2f);
      break;
    case TYPE_EXP:
      BUCLE (imin, imax, expf);
      break;
    case TYPE_EXP10:
      BUCLE (imin, imax, exp10f);
      break;
    case TYPE_EXPM1:
      BUCLE (imin, imax, expm1f);
      break;
    case TYPE_CBRT:
      BUCLE (imin, imax, cbrtf);
      break;
    case TYPE_LOG2:
      BUCLE (imin, imax, log2f);
      break;
    case TYPE_LOG:
      BUCLE (imin, imax, logf);
      break;
    case TYPE_LOG10:
      BUCLE (imin, imax, log10f);
      break;
    case TYPE_SIN:
      BUCLE (imin, imax, sinf);
      break;
    case TYPE_COS:
      BUCLE (imin, imax, cosf);
      break;
    case TYPE_TAN:
      BUCLE (imin, imax, tanf);
      break;
    case TYPE_ATAN:
      BUCLE (imin, imax, atanf);
      break;
    case TYPE_ASIN:
      BUCLE (imin, imax, asinf);
      break;
    case TYPE_ACOS:
      BUCLE (imin, imax, acosf);
      break;
    case TYPE_SINH:
      BUCLE (imin, imax, sinhf);
      break;
    case TYPE_COSH:
      BUCLE (imin, imax, coshf);
      break;
    case TYPE_TANH:
      BUCLE (imin, imax, tanhf);
      break;
    case TYPE_ERF:
      BUCLE (imin, imax, erff);
      break;
    case TYPE_ERFC:
      BUCLE (imin, imax, erfcf);
      break;
    case TYPE_JBM_ABS:
      BUCLE (imin, imax, jbm_abs_f32);
      break;
    case TYPE_JBM_EXP2:
      BUCLE (imin, imax, jbm_exp2_f32);
      break;
    case TYPE_JBM_EXP:
      BUCLE (imin, imax, jbm_exp_f32);
      break;
    case TYPE_JBM_EXP10:
      BUCLE (imin, imax, jbm_exp10_f32);
      break;
    case TYPE_JBM_EXPM1:
      BUCLE (imin, imax, jbm_expm1_f32);
      break;
    case TYPE_JBM_CBRT:
      BUCLE (imin, imax, jbm_cbrt_f32);
      break;
    case TYPE_JBM_LOG2:
      BUCLE (imin, imax, jbm_log2_f32);
      break;
    case TYPE_JBM_LOG:
      BUCLE (imin, imax, jbm_log_f32);
      break;
    case TYPE_JBM_LOG10:
      BUCLE (imin, imax, jbm_log10_f32);
      break;
    case TYPE_JBM_SIN:
      BUCLE (imin, imax, jbm_sin_f32);
      break;
    case TYPE_JBM_COS:
      BUCLE (imin, imax, jbm_cos_f32);
      break;
    case TYPE_JBM_TAN:
      BUCLE (imin, imax, jbm_tan_f32);
      break;
    case TYPE_JBM_ATAN:
      BUCLE (imin, imax, jbm_atan_f32);
      break;
    case TYPE_JBM_ASIN:
      BUCLE (imin, imax, jbm_asin_f32);
      break;
    case TYPE_JBM_ACOS:
      BUCLE (imin, imax, jbm_acos_f32);
      break;
    case TYPE_JBM_SINH:
      BUCLE (imin, imax, jbm_sinh_f32);
      break;
    case TYPE_JBM_COSH:
      BUCLE (imin, imax, jbm_cosh_f32);
      break;
    case TYPE_JBM_TANH:
      BUCLE (imin, imax, jbm_tanh_f32);
      break;
    case TYPE_JBM_ERF:
      BUCLE (imin, imax, jbm_erf_f32);
      break;
    case TYPE_JBM_ERFC:
      BUCLE (imin, imax, jbm_erfc_f32);
      break;
    case TYPE_JBM_POL1:
      BUCLE (imin, imax, pol1_f32);
      break;
    case TYPE_JBM_POL2:
      BUCLE (imin, imax, pol2_f32);
      break;
    case TYPE_JBM_POL3:
      BUCLE (imin, imax, pol3_f32);
      break;
    case TYPE_JBM_POL4:
      BUCLE (imin, imax, pol4_f32);
      break;
    case TYPE_JBM_POL5:
      BUCLE (imin, imax, pol5_f32);
      break;
    case TYPE_JBM_POL6:
      BUCLE (imin, imax, pol6_f32);
      break;
    case TYPE_JBM_POL7:
      BUCLE (imin, imax, pol7_f32);
      break;
    case TYPE_JBM_POL8:
      BUCLE (imin, imax, pol8_f32);
      break;
    case TYPE_JBM_POL9:
      BUCLE (imin, imax, pol9_f32);
      break;
    case TYPE_JBM_POL10:
      BUCLE (imin, imax, pol10_f32);
      break;
    case TYPE_JBM_POL11:
      BUCLE (imin, imax, pol11_f32);
      break;
    case TYPE_JBM_POL12:
      BUCLE (imin, imax, pol12_f32);
      break;
    case TYPE_JBM_POL13:
      BUCLE (imin, imax, pol13_f32);
      break;
    case TYPE_JBM_POL14:
      BUCLE (imin, imax, pol14_f32);
      break;
    case TYPE_JBM_POL15:
      BUCLE (imin, imax, pol15_f32);
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

static inline void
thread_f64 (void *data, void *user_data __attribute__((unused)))
{
  Parallel_f64 *p;
  volatile double *x, *y;
  unsigned long int i, imin, imax;
  p = (Parallel_f64 *) data;
  x = p->x;
  y = p->y;
  imin = p->imin;
  imax = p->imax;
  switch (p->type)
    {
    case TYPE_ADD:
      BUCLE (imin, imax, add_f64);
      break;
    case TYPE_SUB:
      BUCLE (imin, imax, sub_f64);
      break;
    case TYPE_MUL:
      BUCLE (imin, imax, mul_f64);
      break;
    case TYPE_DIV:
      BUCLE (imin, imax, div_f64);
      break;
    case TYPE_SQRT:
      BUCLE (imin, imax, sqrt);
      break;
    case TYPE_MAX:
      BUCLE (imin, imax, max_f64);
      break;
    case TYPE_MIN:
      BUCLE (imin, imax, min_f64);
      break;
    case TYPE_ABS:
      BUCLE (imin, imax, fabs);
      break;
    case TYPE_EXP2:
      BUCLE (imin, imax, exp2);
      break;
    case TYPE_EXP:
      BUCLE (imin, imax, exp);
      break;
    case TYPE_EXP10:
      BUCLE (imin, imax, exp10);
      break;
    case TYPE_EXPM1:
      BUCLE (imin, imax, expm1);
      break;
    case TYPE_CBRT:
      BUCLE (imin, imax, cbrt);
      break;
    case TYPE_LOG2:
      BUCLE (imin, imax, log2);
      break;
    case TYPE_LOG:
      BUCLE (imin, imax, log);
      break;
    case TYPE_LOG10:
      BUCLE (imin, imax, log10);
      break;
    case TYPE_SIN:
      BUCLE (imin, imax, sin);
      break;
    case TYPE_COS:
      BUCLE (imin, imax, cos);
      break;
    case TYPE_TAN:
      BUCLE (imin, imax, tan);
      break;
    case TYPE_ATAN:
      BUCLE (imin, imax, atan);
      break;
    case TYPE_ASIN:
      BUCLE (imin, imax, asin);
      break;
    case TYPE_ACOS:
      BUCLE (imin, imax, acos);
      break;
    case TYPE_SINH:
      BUCLE (imin, imax, sinh);
      break;
    case TYPE_COSH:
      BUCLE (imin, imax, cosh);
      break;
    case TYPE_TANH:
      BUCLE (imin, imax, tanh);
      break;
    case TYPE_ERF:
      BUCLE (imin, imax, erf);
      break;
    case TYPE_ERFC:
      BUCLE (imin, imax, erfc);
      break;
    case TYPE_JBM_ABS:
      BUCLE (imin, imax, jbm_abs_f64);
      break;
    case TYPE_JBM_EXP2:
      BUCLE (imin, imax, jbm_exp2_f64);
      break;
    case TYPE_JBM_EXP:
      BUCLE (imin, imax, jbm_exp_f64);
      break;
    case TYPE_JBM_EXP10:
      BUCLE (imin, imax, jbm_exp10_f64);
      break;
    case TYPE_JBM_EXPM1:
      BUCLE (imin, imax, jbm_expm1_f64);
      break;
    case TYPE_JBM_CBRT:
      BUCLE (imin, imax, jbm_cbrt_f64);
      break;
    case TYPE_JBM_LOG2:
      BUCLE (imin, imax, jbm_log2_f64);
      break;
    case TYPE_JBM_LOG:
      BUCLE (imin, imax, jbm_log_f64);
      break;
    case TYPE_JBM_LOG10:
      BUCLE (imin, imax, jbm_log10_f64);
      break;
    case TYPE_JBM_SIN:
      BUCLE (imin, imax, jbm_sin_f64);
      break;
    case TYPE_JBM_COS:
      BUCLE (imin, imax, jbm_cos_f64);
      break;
    case TYPE_JBM_TAN:
      BUCLE (imin, imax, jbm_tan_f64);
      break;
    case TYPE_JBM_ATAN:
      BUCLE (imin, imax, jbm_atan_f64);
      break;
    case TYPE_JBM_ASIN:
      BUCLE (imin, imax, jbm_asin_f64);
      break;
    case TYPE_JBM_ACOS:
      BUCLE (imin, imax, jbm_acos_f64);
      break;
    case TYPE_JBM_SINH:
      BUCLE (imin, imax, jbm_sinh_f64);
      break;
    case TYPE_JBM_COSH:
      BUCLE (imin, imax, jbm_cosh_f64);
      break;
    case TYPE_JBM_TANH:
      BUCLE (imin, imax, jbm_tanh_f64);
      break;
    case TYPE_JBM_ERF:
      BUCLE (imin, imax, jbm_erf_f64);
      break;
    case TYPE_JBM_ERFC:
      BUCLE (imin, imax, jbm_erfc_f64);
      break;
    case TYPE_JBM_POL1:
      BUCLE (imin, imax, pol1_f64);
      break;
    case TYPE_JBM_POL2:
      BUCLE (imin, imax, pol2_f64);
      break;
    case TYPE_JBM_POL3:
      BUCLE (imin, imax, pol3_f64);
      break;
    case TYPE_JBM_POL4:
      BUCLE (imin, imax, pol4_f64);
      break;
    case TYPE_JBM_POL5:
      BUCLE (imin, imax, pol5_f64);
      break;
    case TYPE_JBM_POL6:
      BUCLE (imin, imax, pol6_f64);
      break;
    case TYPE_JBM_POL7:
      BUCLE (imin, imax, pol7_f64);
      break;
    case TYPE_JBM_POL8:
      BUCLE (imin, imax, pol8_f64);
      break;
    case TYPE_JBM_POL9:
      BUCLE (imin, imax, pol9_f64);
      break;
    case TYPE_JBM_POL10:
      BUCLE (imin, imax, pol10_f64);
      break;
    case TYPE_JBM_POL11:
      BUCLE (imin, imax, pol11_f64);
      break;
    case TYPE_JBM_POL12:
      BUCLE (imin, imax, pol12_f64);
      break;
    case TYPE_JBM_POL13:
      BUCLE (imin, imax, pol13_f64);
      break;
    case TYPE_JBM_POL14:
      BUCLE (imin, imax, pol14_f64);
      break;
    case TYPE_JBM_POL15:
      BUCLE (imin, imax, pol15_f64);
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
      BUCLE_4XF32 (jbm_abs_4xf32);
      break;
    case TYPE_JBM_EXP2:
      BUCLE_4XF32 (jbm_exp2_4xf32);
      break;
    case TYPE_JBM_EXP:
      BUCLE_4XF32 (jbm_exp_4xf32);
      break;
    case TYPE_JBM_EXP10:
      BUCLE_4XF32 (jbm_exp10_4xf32);
      break;
    case TYPE_JBM_EXPM1:
      BUCLE_4XF32 (jbm_expm1_4xf32);
      break;
    case TYPE_JBM_CBRT:
      BUCLE_4XF32 (jbm_cbrt_4xf32);
      break;
    case TYPE_JBM_LOG2:
      BUCLE_4XF32 (jbm_log2_4xf32);
      break;
    case TYPE_JBM_LOG:
      BUCLE_4XF32 (jbm_log_4xf32);
      break;
    case TYPE_JBM_LOG10:
      BUCLE_4XF32 (jbm_log10_4xf32);
      break;
    case TYPE_JBM_SIN:
      BUCLE_4XF32 (jbm_sin_4xf32);
      break;
    case TYPE_JBM_COS:
      BUCLE_4XF32 (jbm_cos_4xf32);
      break;
    case TYPE_JBM_TAN:
      BUCLE_4XF32 (jbm_tan_4xf32);
      break;
    case TYPE_JBM_ATAN:
      BUCLE_4XF32 (jbm_atan_4xf32);
      break;
    case TYPE_JBM_ASIN:
      BUCLE_4XF32 (jbm_asin_4xf32);
      break;
    case TYPE_JBM_ACOS:
      BUCLE_4XF32 (jbm_acos_4xf32);
      break;
    case TYPE_JBM_SINH:
      BUCLE_4XF32 (jbm_sinh_4xf32);
      break;
    case TYPE_JBM_COSH:
      BUCLE_4XF32 (jbm_cosh_4xf32);
      break;
    case TYPE_JBM_TANH:
      BUCLE_4XF32 (jbm_tanh_4xf32);
      break;
    case TYPE_JBM_ERF:
      BUCLE_4XF32 (jbm_erf_4xf32);
      break;
    case TYPE_JBM_ERFC:
      BUCLE_4XF32 (jbm_erfc_4xf32);
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
      BUCLE_2XF64 (jbm_abs_2xf64);
      break;
    case TYPE_JBM_EXP2:
      BUCLE_2XF64 (jbm_exp2_2xf64);
      break;
    case TYPE_JBM_EXP:
      BUCLE_2XF64 (jbm_exp_2xf64);
      break;
    case TYPE_JBM_EXP10:
      BUCLE_2XF64 (jbm_exp10_2xf64);
      break;
    case TYPE_JBM_EXPM1:
      BUCLE_2XF64 (jbm_expm1_2xf64);
      break;
    case TYPE_JBM_CBRT:
      BUCLE_2XF64 (jbm_cbrt_2xf64);
      break;
    case TYPE_JBM_LOG2:
      BUCLE_2XF64 (jbm_log2_2xf64);
      break;
    case TYPE_JBM_LOG:
      BUCLE_2XF64 (jbm_log_2xf64);
      break;
    case TYPE_JBM_LOG10:
      BUCLE_2XF64 (jbm_log10_2xf64);
      break;
    case TYPE_JBM_SIN:
      BUCLE_2XF64 (jbm_sin_2xf64);
      break;
    case TYPE_JBM_COS:
      BUCLE_2XF64 (jbm_cos_2xf64);
      break;
    case TYPE_JBM_TAN:
      BUCLE_2XF64 (jbm_tan_2xf64);
      break;
    case TYPE_JBM_ATAN:
      BUCLE_2XF64 (jbm_atan_2xf64);
      break;
    case TYPE_JBM_ASIN:
      BUCLE_2XF64 (jbm_asin_2xf64);
      break;
    case TYPE_JBM_ACOS:
      BUCLE_2XF64 (jbm_acos_2xf64);
      break;
    case TYPE_JBM_SINH:
      BUCLE_2XF64 (jbm_sinh_2xf64);
      break;
    case TYPE_JBM_COSH:
      BUCLE_2XF64 (jbm_cosh_2xf64);
      break;
    case TYPE_JBM_TANH:
      BUCLE_2XF64 (jbm_tanh_2xf64);
      break;
    case TYPE_JBM_ERF:
      BUCLE_2XF64 (jbm_erf_2xf64);
      break;
    case TYPE_JBM_ERFC:
      BUCLE_2XF64 (jbm_erfc_2xf64);
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
      BUCLE_8XF32 (jbm_abs_8xf32);
      break;
    case TYPE_JBM_EXP2:
      BUCLE_8XF32 (jbm_exp2_8xf32);
      break;
    case TYPE_JBM_EXP:
      BUCLE_8XF32 (jbm_exp_8xf32);
      break;
    case TYPE_JBM_EXP10:
      BUCLE_8XF32 (jbm_exp10_8xf32);
      break;
    case TYPE_JBM_EXPM1:
      BUCLE_8XF32 (jbm_expm1_8xf32);
      break;
    case TYPE_JBM_CBRT:
      BUCLE_8XF32 (jbm_cbrt_8xf32);
      break;
    case TYPE_JBM_LOG2:
      BUCLE_8XF32 (jbm_log2_8xf32);
      break;
    case TYPE_JBM_LOG:
      BUCLE_8XF32 (jbm_log_8xf32);
      break;
    case TYPE_JBM_LOG10:
      BUCLE_8XF32 (jbm_log10_8xf32);
      break;
    case TYPE_JBM_SIN:
      BUCLE_8XF32 (jbm_sin_8xf32);
      break;
    case TYPE_JBM_COS:
      BUCLE_8XF32 (jbm_cos_8xf32);
      break;
    case TYPE_JBM_TAN:
      BUCLE_8XF32 (jbm_tan_8xf32);
      break;
    case TYPE_JBM_ATAN:
      BUCLE_8XF32 (jbm_atan_8xf32);
      break;
    case TYPE_JBM_ASIN:
      BUCLE_8XF32 (jbm_asin_8xf32);
      break;
    case TYPE_JBM_ACOS:
      BUCLE_8XF32 (jbm_acos_8xf32);
      break;
    case TYPE_JBM_SINH:
      BUCLE_8XF32 (jbm_sinh_8xf32);
      break;
    case TYPE_JBM_COSH:
      BUCLE_8XF32 (jbm_cosh_8xf32);
      break;
    case TYPE_JBM_TANH:
      BUCLE_8XF32 (jbm_tanh_8xf32);
      break;
    case TYPE_JBM_ERF:
      BUCLE_8XF32 (jbm_erf_8xf32);
      break;
    case TYPE_JBM_ERFC:
      BUCLE_8XF32 (jbm_erfc_8xf32);
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
      BUCLE_4XF64 (jbm_abs_4xf64);
      break;
    case TYPE_JBM_EXP2:
      BUCLE_4XF64 (jbm_exp2_4xf64);
      break;
    case TYPE_JBM_EXP:
      BUCLE_4XF64 (jbm_exp_4xf64);
      break;
    case TYPE_JBM_EXP10:
      BUCLE_4XF64 (jbm_exp10_4xf64);
      break;
    case TYPE_JBM_EXPM1:
      BUCLE_4XF64 (jbm_expm1_4xf64);
      break;
    case TYPE_JBM_CBRT:
      BUCLE_4XF64 (jbm_cbrt_4xf64);
      break;
    case TYPE_JBM_LOG2:
      BUCLE_4XF64 (jbm_log2_4xf64);
      break;
    case TYPE_JBM_LOG:
      BUCLE_4XF64 (jbm_log_4xf64);
      break;
    case TYPE_JBM_LOG10:
      BUCLE_4XF64 (jbm_log10_4xf64);
      break;
    case TYPE_JBM_SIN:
      BUCLE_4XF64 (jbm_sin_4xf64);
      break;
    case TYPE_JBM_COS:
      BUCLE_4XF64 (jbm_cos_4xf64);
      break;
    case TYPE_JBM_TAN:
      BUCLE_4XF64 (jbm_tan_4xf64);
      break;
    case TYPE_JBM_ATAN:
      BUCLE_4XF64 (jbm_atan_4xf64);
      break;
    case TYPE_JBM_ASIN:
      BUCLE_4XF64 (jbm_asin_4xf64);
      break;
    case TYPE_JBM_ACOS:
      BUCLE_4XF64 (jbm_acos_4xf64);
      break;
    case TYPE_JBM_SINH:
      BUCLE_4XF64 (jbm_sinh_4xf64);
      break;
    case TYPE_JBM_COSH:
      BUCLE_4XF64 (jbm_cosh_4xf64);
      break;
    case TYPE_JBM_TANH:
      BUCLE_4XF64 (jbm_tanh_4xf64);
      break;
    case TYPE_JBM_ERF:
      BUCLE_4XF64 (jbm_erf_4xf64);
      break;
    case TYPE_JBM_ERFC:
      BUCLE_4XF64 (jbm_erfc_4xf64);
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
      BUCLE_16XF32 (jbm_abs_16xf32);
      break;
    case TYPE_JBM_EXP2:
      BUCLE_16XF32 (jbm_exp2_16xf32);
      break;
    case TYPE_JBM_EXP:
      BUCLE_16XF32 (jbm_exp_16xf32);
      break;
    case TYPE_JBM_EXP10:
      BUCLE_16XF32 (jbm_exp10_16xf32);
      break;
    case TYPE_JBM_EXPM1:
      BUCLE_16XF32 (jbm_expm1_16xf32);
      break;
    case TYPE_JBM_CBRT:
      BUCLE_16XF32 (jbm_cbrt_16xf32);
      break;
    case TYPE_JBM_LOG2:
      BUCLE_16XF32 (jbm_log2_16xf32);
      break;
    case TYPE_JBM_LOG:
      BUCLE_16XF32 (jbm_log_16xf32);
      break;
    case TYPE_JBM_LOG10:
      BUCLE_16XF32 (jbm_log10_16xf32);
      break;
    case TYPE_JBM_SIN:
      BUCLE_16XF32 (jbm_sin_16xf32);
      break;
    case TYPE_JBM_COS:
      BUCLE_16XF32 (jbm_cos_16xf32);
      break;
    case TYPE_JBM_TAN:
      BUCLE_16XF32 (jbm_tan_16xf32);
      break;
    case TYPE_JBM_ATAN:
      BUCLE_16XF32 (jbm_atan_16xf32);
      break;
    case TYPE_JBM_ASIN:
      BUCLE_16XF32 (jbm_asin_16xf32);
      break;
    case TYPE_JBM_ACOS:
      BUCLE_16XF32 (jbm_acos_16xf32);
      break;
    case TYPE_JBM_SINH:
      BUCLE_16XF32 (jbm_sinh_16xf32);
      break;
    case TYPE_JBM_COSH:
      BUCLE_16XF32 (jbm_cosh_16xf32);
      break;
    case TYPE_JBM_TANH:
      BUCLE_16XF32 (jbm_tanh_16xf32);
      break;
    case TYPE_JBM_ERF:
      BUCLE_16XF32 (jbm_erf_16xf32);
      break;
    case TYPE_JBM_ERFC:
      BUCLE_16XF32 (jbm_erfc_16xf32);
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
      BUCLE_8XF64 (jbm_abs_8xf64);
      break;
    case TYPE_JBM_EXP2:
      BUCLE_8XF64 (jbm_exp2_8xf64);
      break;
    case TYPE_JBM_EXP:
      BUCLE_8XF64 (jbm_exp_8xf64);
      break;
    case TYPE_JBM_EXP10:
      BUCLE_8XF64 (jbm_exp10_8xf64);
      break;
    case TYPE_JBM_EXPM1:
      BUCLE_8XF64 (jbm_expm1_8xf64);
      break;
    case TYPE_JBM_CBRT:
      BUCLE_8XF64 (jbm_cbrt_8xf64);
      break;
    case TYPE_JBM_LOG2:
      BUCLE_8XF64 (jbm_log2_8xf64);
      break;
    case TYPE_JBM_LOG:
      BUCLE_8XF64 (jbm_log_8xf64);
      break;
    case TYPE_JBM_LOG10:
      BUCLE_8XF64 (jbm_log10_8xf64);
      break;
    case TYPE_JBM_SIN:
      BUCLE_8XF64 (jbm_sin_8xf64);
      break;
    case TYPE_JBM_COS:
      BUCLE_8XF64 (jbm_cos_8xf64);
      break;
    case TYPE_JBM_TAN:
      BUCLE_8XF64 (jbm_tan_8xf64);
      break;
    case TYPE_JBM_ATAN:
      BUCLE_8XF64 (jbm_atan_8xf64);
      break;
    case TYPE_JBM_ASIN:
      BUCLE_8XF64 (jbm_asin_8xf64);
      break;
    case TYPE_JBM_ACOS:
      BUCLE_8XF64 (jbm_acos_8xf64);
      break;
    case TYPE_JBM_SINH:
      BUCLE_8XF64 (jbm_sinh_8xf64);
      break;
    case TYPE_JBM_COSH:
      BUCLE_8XF64 (jbm_cosh_8xf64);
      break;
    case TYPE_JBM_TANH:
      BUCLE_8XF64 (jbm_tanh_8xf64);
      break;
    case TYPE_JBM_ERF:
      BUCLE_8XF64 (jbm_erf_8xf64);
      break;
    case TYPE_JBM_ERFC:
      BUCLE_8XF64 (jbm_erfc_8xf64);
      break;
    }
}

#endif

static inline void
efficiency_f32 (const unsigned int type, void (*thread) (void *, void *),
                float *restrict x, float *restrict y, const double *r,
                unsigned long int n, const float xmin, const float xmax,
                const unsigned int nthreads, const char *label)
{
  Parallel_f32 p[nthreads];
  GThreadPool *pool;
  float dx;
  double t, t0;
  unsigned long int i;
  for (i = 0, dx = xmax - xmin; i < n; ++i)
    x[i] = xmin + dx * r[i];
  t0 = crono ();
  if (nthreads < 2)
    {
      p[0].type = type;
      p[0].imin = 0;
      p[0].imax = n;
      p[0].x = x;
      p[0].y = y;
      thread (p, NULL);
    }
  else
    {
      pool = g_thread_pool_new (thread, NULL, nthreads, FALSE, NULL);
      for (i = 0; i < (unsigned long int) nthreads; ++i)
        {
          p[i].type = type;
          p[i].imin = i * n / (unsigned long int) nthreads;
          p[i].imax = (i + 1) * n / (unsigned long int) nthreads;
          p[i].x = x;
          p[i].y = y;
          g_thread_pool_push (pool, p + i, NULL);
        }
      g_thread_pool_free (pool, FALSE, TRUE);
    }
  t = (crono () - t0) / (double) n;
  printf ("%s time=%lg error=%Lg\n", label, t, error_f32 (type, x, y, n));
}

static inline void
efficiency_f64 (const unsigned int type, void (*thread) (void *, void *),
                double *restrict x, double *restrict y, const double *r,
                unsigned long int n, const double xmin, const double xmax,
                const unsigned int nthreads, const char *label)
{
  Parallel_f64 p[nthreads];
  GThreadPool *pool;
  double dx, t, t0;
  unsigned long int i;
  for (i = 0, dx = xmax - xmin; i < n; ++i)
    x[i] = xmin + dx * r[i];
  t0 = crono ();
  if (nthreads < 2)
    {
      p[0].type = type;
      p[0].imin = 0;
      p[0].imax = n;
      p[0].x = x;
      p[0].y = y;
      thread (p, NULL);
    }
  else
    {
      pool = g_thread_pool_new (thread, NULL, nthreads, FALSE, NULL);
      for (i = 0; i < (unsigned long int) nthreads; ++i)
        {
          p[i].type = type;
          p[i].imin = i * n / (unsigned long int) nthreads;
          p[i].imax = (i + 1) * n / (unsigned long int) nthreads;
          p[i].x = x;
          p[i].y = y;
          g_thread_pool_push (pool, p + i, NULL);
        }
      g_thread_pool_free (pool, FALSE, TRUE);
    }
  t = (crono () - t0) / (double) n;
  printf ("%s time=%lg error=%Lg\n", label, t, error_f64 (type, x, y, n));
}

int
main (int argn, char **argc)
{
  gsl_rng *rng;
  double *r;
  double *x64, *y64;
  float *x32, *y32;
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
  r = (double *) malloc (n * sizeof (double));
  rng = gsl_rng_alloc (gsl_rng_taus2);
  gsl_rng_set (rng, SEED);
  for (i = 0; i < n; ++i)
    r[i] = gsl_rng_uniform (rng);
  gsl_rng_free (rng);
  x32 = (float *) JB_MALLOC (n * sizeof (float));
  y32 = (float *) JB_MALLOC (n * sizeof (float));
  x64 = (double *) JB_MALLOC (n * sizeof (double));
  y64 = (double *) JB_MALLOC (n * sizeof (double));

  // float functions
  printf ("float functions\n");
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
  efficiency_f32 (TYPE_ABS, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "fabsf");
  efficiency_f32 (TYPE_JBM_ABS, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "jbm_abs_f32");
  efficiency_f32 (TYPE_EXP2, thread_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "exp2f");
  efficiency_f32 (TYPE_JBM_EXP2, thread_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_exp2_f32");
  efficiency_f32 (TYPE_EXP, thread_f32, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "expf");
  efficiency_f32 (TYPE_JBM_EXP, thread_f32, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "jbm_exp_f32");
  efficiency_f32 (TYPE_EXP10, thread_f32, x32, y32, r, n, -FLT_MAX_10_EXP,
                  FLT_MAX_10_EXP, nthreads, "exp10f");
  efficiency_f32 (TYPE_JBM_EXP10, thread_f32, x32, y32, r, n, -FLT_MAX_10_EXP,
                  FLT_MAX_10_EXP, nthreads, "jbm_exp10_f32");
  efficiency_f32 (TYPE_EXPM1, thread_f32, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "expm1f");
  efficiency_f32 (TYPE_JBM_EXPM1, thread_f32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_expm1_f32");
  efficiency_f32 (TYPE_CBRT, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "cbrtf");
  efficiency_f32 (TYPE_JBM_CBRT, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "jbm_cbrt_f32");
  efficiency_f32 (TYPE_LOG2, thread_f32, x32, y32, r, n, FLT_MIN, FLT_MAX,
                  nthreads, "log2f");
  efficiency_f32 (TYPE_JBM_LOG2, thread_f32, x32, y32, r, n, FLT_MIN, FLT_MAX,
                  nthreads, "jbm_log2_f32");
  efficiency_f32 (TYPE_LOG, thread_f32, x32, y32, r, n, FLT_MIN, FLT_MAX,
                  nthreads, "logf");
  efficiency_f32 (TYPE_JBM_LOG, thread_f32, x32, y32, r, n, FLT_MIN, FLT_MAX,
                  nthreads, "jbm_log_f32");
  efficiency_f32 (TYPE_LOG10, thread_f32, x32, y32, r, n, FLT_MIN, FLT_MAX,
                  nthreads, "log10f");
  efficiency_f32 (TYPE_JBM_LOG10, thread_f32, x32, y32, r, n, FLT_MIN, FLT_MAX,
                  nthreads, "jbm_log10_f32");
  efficiency_f32 (TYPE_SIN, thread_f32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "sinf");
  efficiency_f32 (TYPE_JBM_SIN, thread_f32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_sin_f32");
  efficiency_f32 (TYPE_COS, thread_f32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "cosf");
  efficiency_f32 (TYPE_JBM_COS, thread_f32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_cos_f32");
  efficiency_f32 (TYPE_TAN, thread_f32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "tanf");
  efficiency_f32 (TYPE_JBM_TAN, thread_f32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_tan_f32");
  efficiency_f32 (TYPE_ATAN, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "atanf");
  efficiency_f32 (TYPE_JBM_ATAN, thread_f32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "jbm_atan_f32");
  efficiency_f32 (TYPE_ASIN, thread_f32, x32, y32, r, n, -1.f, 1.f, nthreads,
                  "asinf");
  efficiency_f32 (TYPE_JBM_ASIN, thread_f32, x32, y32, r, n, -1.f, 1.f,
                  nthreads, "jbm_asin_f32");
  efficiency_f32 (TYPE_ACOS, thread_f32, x32, y32, r, n, -1.f, 1.f, nthreads,
                  "acosf");
  efficiency_f32 (TYPE_JBM_ACOS, thread_f32, x32, y32, r, n, -1.f, 1.f,
                  nthreads, "jbm_acos_f32");
  efficiency_f32 (TYPE_SINH, thread_f32, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "sinhf");
  efficiency_f32 (TYPE_JBM_SINH, thread_f32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_sinh_f32");
  efficiency_f32 (TYPE_COSH, thread_f32, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "coshf");
  efficiency_f32 (TYPE_JBM_COSH, thread_f32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_cosh_f32");
  efficiency_f32 (TYPE_TANH, thread_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "tanhf");
  efficiency_f32 (TYPE_JBM_TANH, thread_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_tanh_f32");
  efficiency_f32 (TYPE_ERF, thread_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "erff");
  efficiency_f32 (TYPE_JBM_ERF, thread_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_erf_f32");
  efficiency_f32 (TYPE_ERFC, thread_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "erfcf");
  efficiency_f32 (TYPE_JBM_ERFC, thread_f32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_erfc_f32");
  efficiency_f32 (TYPE_JBM_POL1, thread_f32, x32, y32, r, n, 0.f, 1.f, nthreads,
		  "jbm_pol1_f32");
  efficiency_f32 (TYPE_JBM_POL2, thread_f32, x32, y32, r, n, 0.f, 1.f, nthreads,
		  "jbm_pol2_f32");
  efficiency_f32 (TYPE_JBM_POL3, thread_f32, x32, y32, r, n, 0.f, 1.f, nthreads,
		  "jbm_pol3_f32");
  efficiency_f32 (TYPE_JBM_POL4, thread_f32, x32, y32, r, n, 0.f, 1.f, nthreads,
		  "jbm_pol4_f32");
  efficiency_f32 (TYPE_JBM_POL5, thread_f32, x32, y32, r, n, 0.f, 1.f, nthreads,
		  "jbm_pol5_f32");
  efficiency_f32 (TYPE_JBM_POL6, thread_f32, x32, y32, r, n, 0.f, 1.f, nthreads,
		  "jbm_pol6_f32");
  efficiency_f32 (TYPE_JBM_POL7, thread_f32, x32, y32, r, n, 0.f, 1.f, nthreads,
		  "jbm_pol7_f32");
  efficiency_f32 (TYPE_JBM_POL8, thread_f32, x32, y32, r, n, 0.f, 1.f, nthreads,
		  "jbm_pol8_f32");
  efficiency_f32 (TYPE_JBM_POL9, thread_f32, x32, y32, r, n, 0.f, 1.f, nthreads,
		  "jbm_pol9_f32");
  efficiency_f32 (TYPE_JBM_POL10, thread_f32, x32, y32, r, n, 0.f, 1.f,
		  nthreads, "jbm_pol10_f32");
  efficiency_f32 (TYPE_JBM_POL11, thread_f32, x32, y32, r, n, 0.f, 1.f,
		  nthreads, "jbm_pol11_f32");
  efficiency_f32 (TYPE_JBM_POL12, thread_f32, x32, y32, r, n, 0.f, 1.f,
		  nthreads, "jbm_pol12_f32");
  efficiency_f32 (TYPE_JBM_POL13, thread_f32, x32, y32, r, n, 0.f, 1.f,
		  nthreads, "jbm_pol13_f32");
  efficiency_f32 (TYPE_JBM_POL14, thread_f32, x32, y32, r, n, 0.f, 1.f,
		  nthreads, "jbm_pol14_f32");
  efficiency_f32 (TYPE_JBM_POL15, thread_f32, x32, y32, r, n, 0.f, 1.f,
		  nthreads, "jbm_pol15_f32");

  // double functions
  printf ("double functions\n");
  efficiency_f64 (TYPE_ADD, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "add_f64");
  efficiency_f64 (TYPE_SUB, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "sub_f64");
  efficiency_f64 (TYPE_MUL, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "mul_f64");
  efficiency_f64 (TYPE_DIV, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "div_f64");
  efficiency_f64 (TYPE_SQRT, thread_f64, x64, y64, r, n, 0., DBL_MAX, nthreads,
                  "sqrt");
  efficiency_f64 (TYPE_MAX, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "max_f64");
  efficiency_f64 (TYPE_MIN, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "min_f64");
  efficiency_f64 (TYPE_ABS, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "fabs");
  efficiency_f64 (TYPE_JBM_ABS, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "jbm_abs_f64");
  efficiency_f64 (TYPE_EXP2, thread_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "exp2");
  efficiency_f64 (TYPE_JBM_EXP2, thread_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_exp2_f64");
  efficiency_f64 (TYPE_EXP, thread_f64, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                  JBM_DBL_MAX_E_EXP, nthreads, "exp");
  efficiency_f64 (TYPE_JBM_EXP, thread_f64, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                  JBM_DBL_MAX_E_EXP, nthreads, "jbm_exp_f64");
  efficiency_f64 (TYPE_EXP10, thread_f64, x64, y64, r, n, -DBL_MAX_10_EXP,
                  DBL_MAX_10_EXP, nthreads, "exp10");
  efficiency_f64 (TYPE_JBM_EXP10, thread_f64, x64, y64, r, n, -DBL_MAX_10_EXP,
                  DBL_MAX_10_EXP, nthreads, "jbm_exp10_f64");
  efficiency_f64 (TYPE_EXPM1, thread_f64, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                  JBM_DBL_MAX_E_EXP, nthreads, "expm1");
  efficiency_f64 (TYPE_JBM_EXPM1, thread_f64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_expm1_f64");
  efficiency_f64 (TYPE_CBRT, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "cbrt");
  efficiency_f64 (TYPE_JBM_CBRT, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "jbm_cbrt_f64");
  efficiency_f64 (TYPE_LOG2, thread_f64, x64, y64, r, n, DBL_MIN, DBL_MAX,
                  nthreads, "log2");
  efficiency_f64 (TYPE_JBM_LOG2, thread_f64, x64, y64, r, n, DBL_MIN, DBL_MAX,
                  nthreads, "jbm_log2_f64");
  efficiency_f64 (TYPE_LOG, thread_f64, x64, y64, r, n, DBL_MIN, DBL_MAX,
                  nthreads, "log");
  efficiency_f64 (TYPE_JBM_LOG, thread_f64, x64, y64, r, n, DBL_MIN, DBL_MAX,
                  nthreads, "jbm_log_f64");
  efficiency_f64 (TYPE_LOG10, thread_f64, x64, y64, r, n, DBL_MIN, DBL_MAX,
                  nthreads, "log10");
  efficiency_f64 (TYPE_JBM_LOG10, thread_f64, x64, y64, r, n, DBL_MIN, DBL_MAX,
                  nthreads, "jbm_log10_f64");
  efficiency_f64 (TYPE_SIN, thread_f64, x64, y64, r, n, -4. * M_PI, 4. * M_PI,
                  nthreads, "sin");
  efficiency_f64 (TYPE_JBM_SIN, thread_f64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_sin_f64");
  efficiency_f64 (TYPE_COS, thread_f64, x64, y64, r, n, -4. * M_PI, 4. * M_PI,
                  nthreads, "cos");
  efficiency_f64 (TYPE_JBM_COS, thread_f64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_cos_f64");
  efficiency_f64 (TYPE_TAN, thread_f64, x64, y64, r, n, -4. * M_PI, 4. * M_PI,
                  nthreads, "tan");
  efficiency_f64 (TYPE_JBM_TAN, thread_f64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_tan_f64");
  efficiency_f64 (TYPE_ATAN, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "atan");
  efficiency_f64 (TYPE_JBM_ATAN, thread_f64, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "jbm_atan_f64");
  efficiency_f64 (TYPE_ASIN, thread_f64, x64, y64, r, n, -1., 1., nthreads,
                  "asin");
  efficiency_f64 (TYPE_JBM_ASIN, thread_f64, x64, y64, r, n, -1., 1.,
                  nthreads, "jbm_asin_f64");
  efficiency_f64 (TYPE_ACOS, thread_f64, x64, y64, r, n, -1., 1., nthreads,
                  "acos");
  efficiency_f64 (TYPE_JBM_ACOS, thread_f64, x64, y64, r, n, -1., 1., nthreads,
                  "jbm_acos_f64");
  efficiency_f64 (TYPE_SINH, thread_f64, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                  JBM_DBL_MAX_E_EXP, nthreads, "sinh");
  efficiency_f64 (TYPE_JBM_SINH, thread_f64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_sinh_f64");
  efficiency_f64 (TYPE_COSH, thread_f64, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                  JBM_DBL_MAX_E_EXP, nthreads, "cosh");
  efficiency_f64 (TYPE_JBM_COSH, thread_f64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_cosh_f64");
  efficiency_f64 (TYPE_TANH, thread_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "tanh");
  efficiency_f64 (TYPE_JBM_TANH, thread_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_tanh_f64");
  efficiency_f64 (TYPE_ERF, thread_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "erf");
  efficiency_f64 (TYPE_JBM_ERF, thread_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_erf_f64");
  efficiency_f64 (TYPE_ERFC, thread_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "erfc");
  efficiency_f64 (TYPE_JBM_ERFC, thread_f64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_erfc_f64");
  efficiency_f64 (TYPE_JBM_POL1, thread_f64, x64, y64, r, n, 0., 1., nthreads,
		  "jbm_pol1_f64");
  efficiency_f64 (TYPE_JBM_POL2, thread_f64, x64, y64, r, n, 0., 1., nthreads,
		  "jbm_pol2_f64");
  efficiency_f64 (TYPE_JBM_POL3, thread_f64, x64, y64, r, n, 0., 1., nthreads,
		  "jbm_pol3_f64");
  efficiency_f64 (TYPE_JBM_POL4, thread_f64, x64, y64, r, n, 0., 1., nthreads,
		  "jbm_pol4_f64");
  efficiency_f64 (TYPE_JBM_POL5, thread_f64, x64, y64, r, n, 0., 1., nthreads,
		  "jbm_pol5_f64");
  efficiency_f64 (TYPE_JBM_POL6, thread_f64, x64, y64, r, n, 0., 1., nthreads,
		  "jbm_pol6_f64");
  efficiency_f64 (TYPE_JBM_POL7, thread_f64, x64, y64, r, n, 0., 1., nthreads,
		  "jbm_pol7_f64");
  efficiency_f64 (TYPE_JBM_POL8, thread_f64, x64, y64, r, n, 0., 1., nthreads,
		  "jbm_pol8_f64");
  efficiency_f64 (TYPE_JBM_POL9, thread_f64, x64, y64, r, n, 0., 1., nthreads,
		  "jbm_pol9_f64");
  efficiency_f64 (TYPE_JBM_POL10, thread_f64, x64, y64, r, n, 0., 1., nthreads,
		  "jbm_pol10_f64");
  efficiency_f64 (TYPE_JBM_POL11, thread_f64, x64, y64, r, n, 0., 1., nthreads,
		  "jbm_pol11_f64");
  efficiency_f64 (TYPE_JBM_POL12, thread_f64, x64, y64, r, n, 0., 1., nthreads,
		  "jbm_pol12_f64");
  efficiency_f64 (TYPE_JBM_POL13, thread_f64, x64, y64, r, n, 0., 1., nthreads,
		  "jbm_pol13_f64");
  efficiency_f64 (TYPE_JBM_POL14, thread_f64, x64, y64, r, n, 0., 1., nthreads,
		  "jbm_pol14_f64");
  efficiency_f64 (TYPE_JBM_POL15, thread_f64, x64, y64, r, n, 0., 1., nthreads,
		  "jbm_pol15_f64");

#ifdef __SSE4_2__

  // __m128 functions
  printf ("__m128 functions\n");
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
                  FLT_MAX, nthreads, "jbm_abs_4xf32");
  efficiency_f32 (TYPE_JBM_EXP2, thread_4xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_exp2_4xf32");
  efficiency_f32 (TYPE_JBM_EXP, thread_4xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_exp_4xf32");
  efficiency_f32 (TYPE_JBM_EXP10, thread_4xf32, x32, y32, r, n,
                  -FLT_MAX_10_EXP, FLT_MAX_10_EXP, nthreads, "jbm_exp10_4xf32");
  efficiency_f32 (TYPE_JBM_EXPM1, thread_4xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_expm1_4xf32");
  efficiency_f32 (TYPE_JBM_CBRT, thread_4xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_cbrt_4xf32");
  efficiency_f32 (TYPE_JBM_LOG2, thread_4xf32, x32, y32, r, n, FLT_MIN,
                  FLT_MAX, nthreads, "jbm_log2_4xf32");
  efficiency_f32 (TYPE_JBM_LOG, thread_4xf32, x32, y32, r, n, FLT_MIN, FLT_MAX,
                  nthreads, "jbm_log_4xf32");
  efficiency_f32 (TYPE_JBM_LOG10, thread_4xf32, x32, y32, r, n, FLT_MIN,
                  FLT_MAX, nthreads, "jbm_log10_4xf32");
  efficiency_f32 (TYPE_JBM_SIN, thread_4xf32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_sin_4xf32");
  efficiency_f32 (TYPE_JBM_COS, thread_4xf32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_cos_4xf32");
  efficiency_f32 (TYPE_JBM_TAN, thread_4xf32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_tan_4xf32");
  efficiency_f32 (TYPE_JBM_ATAN, thread_4xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_atan_4xf32");
  efficiency_f32 (TYPE_JBM_ASIN, thread_4xf32, x32, y32, r, n, -1.f, 1.f,
                  nthreads, "jbm_asin_4xf32");
  efficiency_f32 (TYPE_JBM_ACOS, thread_4xf32, x32, y32, r, n, -1.f, 1.f,
                  nthreads, "jbm_acos_4xf32");
  efficiency_f32 (TYPE_JBM_SINH, thread_4xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_sinh_4xf32");
  efficiency_f32 (TYPE_JBM_COSH, thread_4xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_cosh_4xf32");
  efficiency_f32 (TYPE_JBM_TANH, thread_4xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_tanh_4xf32");
  efficiency_f32 (TYPE_JBM_ERF, thread_4xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_erf_4xf32");
  efficiency_f32 (TYPE_JBM_ERFC, thread_4xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_erfc_4xf32");

  printf ("__m128d functions\n");
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
                  DBL_MAX, nthreads, "jbm_abs_2xf64");
  efficiency_f64 (TYPE_JBM_EXP2, thread_2xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_exp2_2xf64");
  efficiency_f64 (TYPE_JBM_EXP, thread_2xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_exp_2xf64");
  efficiency_f64 (TYPE_JBM_EXP10, thread_2xf64, x64, y64, r, n,
                  -DBL_MAX_10_EXP, DBL_MAX_10_EXP, nthreads, "jbm_exp10_2xf64");
  efficiency_f64 (TYPE_JBM_EXPM1, thread_2xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_expm1_2xf64");
  efficiency_f64 (TYPE_JBM_CBRT, thread_2xf64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_cbrt_2xf64");
  efficiency_f64 (TYPE_JBM_LOG2, thread_2xf64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_log2_2xf64");
  efficiency_f64 (TYPE_JBM_LOG, thread_2xf64, x64, y64, r, n, DBL_MIN, DBL_MAX,
                  nthreads, "jbm_log_2xf64");
  efficiency_f64 (TYPE_JBM_LOG10, thread_2xf64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_log10_2xf64");
  efficiency_f64 (TYPE_JBM_SIN, thread_2xf64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_sin_2xf64");
  efficiency_f64 (TYPE_JBM_COS, thread_2xf64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_cos_2xf64");
  efficiency_f64 (TYPE_JBM_TAN, thread_2xf64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_tan_2xf64");
  efficiency_f64 (TYPE_JBM_ATAN, thread_2xf64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_atan_2xf64");
  efficiency_f64 (TYPE_JBM_ASIN, thread_2xf64, x64, y64, r, n, -1., 1.,
                  nthreads, "jbm_asin_2xf64");
  efficiency_f64 (TYPE_JBM_ACOS, thread_2xf64, x64, y64, r, n, -1., 1.,
                  nthreads, "jbm_acos_2xf64");
  efficiency_f64 (TYPE_JBM_SINH, thread_2xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_sinh_2xf64");
  efficiency_f64 (TYPE_JBM_COSH, thread_2xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_cosh_2xf64");
  efficiency_f64 (TYPE_JBM_TANH, thread_2xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_tanh_2xf64");
  efficiency_f64 (TYPE_JBM_ERF, thread_2xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_erf_2xf64");
  efficiency_f64 (TYPE_JBM_ERFC, thread_2xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_erfc_2xf64");

#endif

#ifdef __AVX__

  // __m256 functions
  printf ("__m256 functions\n");
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
                  FLT_MAX, nthreads, "jbm_abs_8xf32");
  efficiency_f32 (TYPE_JBM_EXP2, thread_8xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_exp2_8xf32");
  efficiency_f32 (TYPE_JBM_EXP, thread_8xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_exp_8xf32");
  efficiency_f32 (TYPE_JBM_EXP10, thread_8xf32, x32, y32, r, n,
                  -FLT_MAX_10_EXP, FLT_MAX_10_EXP, nthreads, "jbm_exp10_8xf32");
  efficiency_f32 (TYPE_JBM_EXPM1, thread_8xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_expm1_8xf32");
  efficiency_f32 (TYPE_JBM_CBRT, thread_8xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_cbrt_8xf32");
  efficiency_f32 (TYPE_JBM_LOG2, thread_8xf32, x32, y32, r, n, FLT_MIN,
                  FLT_MAX, nthreads, "jbm_log2_8xf32");
  efficiency_f32 (TYPE_JBM_LOG, thread_8xf32, x32, y32, r, n, FLT_MIN, FLT_MAX,
                  nthreads, "jbm_log_8xf32");
  efficiency_f32 (TYPE_JBM_LOG10, thread_8xf32, x32, y32, r, n, FLT_MIN,
                  FLT_MAX, nthreads, "jbm_log10_8xf32");
  efficiency_f32 (TYPE_JBM_SIN, thread_8xf32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_sin_8xf32");
  efficiency_f32 (TYPE_JBM_COS, thread_8xf32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_cos_8xf32");
  efficiency_f32 (TYPE_JBM_TAN, thread_8xf32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_tan_8xf32");
  efficiency_f32 (TYPE_JBM_ATAN, thread_8xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_atan_8xf32");
  efficiency_f32 (TYPE_JBM_ASIN, thread_8xf32, x32, y32, r, n, -1.f, 1.f,
                  nthreads, "jbm_asin_8xf32");
  efficiency_f32 (TYPE_JBM_ACOS, thread_8xf32, x32, y32, r, n, -1.f, 1.f,
                  nthreads, "jbm_acos_8xf32");
  efficiency_f32 (TYPE_JBM_SINH, thread_8xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_sinh_8xf32");
  efficiency_f32 (TYPE_JBM_COSH, thread_8xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_cosh_8xf32");
  efficiency_f32 (TYPE_JBM_TANH, thread_8xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_tanh_8xf32");
  efficiency_f32 (TYPE_JBM_ERF, thread_8xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_erf_8xf32");
  efficiency_f32 (TYPE_JBM_ERFC, thread_8xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_erfc_8xf32");

  printf ("__m256d functions\n");
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
                  DBL_MAX, nthreads, "jbm_abs_4xf64");
  efficiency_f64 (TYPE_JBM_EXP2, thread_4xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_exp2_4xf64");
  efficiency_f64 (TYPE_JBM_EXP, thread_4xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_exp_4xf64");
  efficiency_f64 (TYPE_JBM_EXP10, thread_4xf64, x64, y64, r, n,
                  -DBL_MAX_10_EXP, DBL_MAX_10_EXP, nthreads, "jbm_exp10_4xf64");
  efficiency_f64 (TYPE_JBM_EXPM1, thread_4xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_expm1_4xf64");
  efficiency_f64 (TYPE_JBM_CBRT, thread_4xf64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_cbrt_4xf64");
  efficiency_f64 (TYPE_JBM_LOG2, thread_4xf64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_log2_4xf64");
  efficiency_f64 (TYPE_JBM_LOG, thread_4xf64, x64, y64, r, n, DBL_MIN, DBL_MAX,
                  nthreads, "jbm_log_4xf64");
  efficiency_f64 (TYPE_JBM_LOG10, thread_4xf64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_log10_4xf64");
  efficiency_f64 (TYPE_JBM_SIN, thread_4xf64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_sin_4xf64");
  efficiency_f64 (TYPE_JBM_COS, thread_4xf64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_cos_4xf64");
  efficiency_f64 (TYPE_JBM_TAN, thread_4xf64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_tan_4xf64");
  efficiency_f64 (TYPE_JBM_ATAN, thread_4xf64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_atan_4xf64");
  efficiency_f64 (TYPE_JBM_ASIN, thread_4xf64, x64, y64, r, n, -1., 1.,
                  nthreads, "jbm_asin_4xf64");
  efficiency_f64 (TYPE_JBM_ACOS, thread_4xf64, x64, y64, r, n, -1., 1.,
                  nthreads, "jbm_acos_4xf64");
  efficiency_f64 (TYPE_JBM_SINH, thread_4xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_sinh_4xf64");
  efficiency_f64 (TYPE_JBM_COSH, thread_4xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_cosh_4xf64");
  efficiency_f64 (TYPE_JBM_TANH, thread_4xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_tanh_4xf64");
  efficiency_f64 (TYPE_JBM_ERF, thread_4xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_erf_4xf64");
  efficiency_f64 (TYPE_JBM_ERFC, thread_4xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_erfc_4xf64");

#endif

#ifdef __AVX512F__

  // __m512 functions
  printf ("__m512 functions\n");
  efficiency_f32 (TYPE_ADD, thread_16xf32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "add_16xf32");
  efficiency_f32 (TYPE_SUB, thread_16xf32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "sub_16xf32");
  efficiency_f32 (TYPE_MUL, thread_16xf32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "mul_16xf32");
  efficiency_f32 (TYPE_DIV, thread_16xf32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "div_16xf32");
  efficiency_f32 (TYPE_SQRT, thread_16xf32, x32, y32, r, n, 0.f, FLT_MAX,
                  nthreads, "sqrt_16xf32");
  efficiency_f32 (TYPE_MAX, thread_16xf32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "max_16xf32");
  efficiency_f32 (TYPE_MIN, thread_16xf32, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "min_16xf32");
  efficiency_f32 (TYPE_JBM_ABS, thread_16xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_abs_16xf32");
  efficiency_f32 (TYPE_JBM_EXP2, thread_16xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_exp2_16xf32");
  efficiency_f32 (TYPE_JBM_EXP, thread_16xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_exp_16xf32");
  efficiency_f32 (TYPE_JBM_EXP10, thread_16xf32, x32, y32, r, n,
                  -FLT_MAX_10_EXP, FLT_MAX_10_EXP, nthreads,
                  "jbm_exp10_16xf32");
  efficiency_f32 (TYPE_JBM_EXPM1, thread_16xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_expm1_16xf32");
  efficiency_f32 (TYPE_JBM_CBRT, thread_16xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_cbrt_16xf32");
  efficiency_f32 (TYPE_JBM_LOG2, thread_16xf32, x32, y32, r, n, FLT_MIN,
                  FLT_MAX, nthreads, "jbm_log2_16xf32");
  efficiency_f32 (TYPE_JBM_LOG, thread_16xf32, x32, y32, r, n, FLT_MIN,
                  FLT_MAX, nthreads, "jbm_log_16xf32");
  efficiency_f32 (TYPE_JBM_LOG10, thread_16xf32, x32, y32, r, n, FLT_MIN,
                  FLT_MAX, nthreads, "jbm_log10_16xf32");
  efficiency_f32 (TYPE_JBM_SIN, thread_16xf32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_sin_16xf32");
  efficiency_f32 (TYPE_JBM_COS, thread_16xf32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_cos_16xf32");
  efficiency_f32 (TYPE_JBM_TAN, thread_16xf32, x32, y32, r, n, -4.f * M_PIf,
                  4.f * M_PIf, nthreads, "jbm_tan_16xf32");
  efficiency_f32 (TYPE_JBM_ATAN, thread_16xf32, x32, y32, r, n, -FLT_MAX,
                  FLT_MAX, nthreads, "jbm_atan_16xf32");
  efficiency_f32 (TYPE_JBM_ASIN, thread_16xf32, x32, y32, r, n, -1.f, 1.f,
                  nthreads, "jbm_asin_16xf32");
  efficiency_f32 (TYPE_JBM_ACOS, thread_16xf32, x32, y32, r, n, -1.f, 1.f,
                  nthreads, "jbm_acos_16xf32");
  efficiency_f32 (TYPE_JBM_SINH, thread_16xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_sinh_16xf32");
  efficiency_f32 (TYPE_JBM_COSH, thread_16xf32, x32, y32, r, n,
                  -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                  "jbm_cosh_16xf32");
  efficiency_f32 (TYPE_JBM_TANH, thread_16xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_tanh_16xf32");
  efficiency_f32 (TYPE_JBM_ERF, thread_16xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_erf_16xf32");
  efficiency_f32 (TYPE_JBM_ERFC, thread_16xf32, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_erfc_16xf32");

  printf ("__m512d functions\n");
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
                  DBL_MAX, nthreads, "jbm_abs_8xf64");
  efficiency_f64 (TYPE_JBM_EXP2, thread_8xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_exp2_8xf64");
  efficiency_f64 (TYPE_JBM_EXP, thread_8xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_exp_8xf64");
  efficiency_f64 (TYPE_JBM_EXP10, thread_8xf64, x64, y64, r, n,
                  -DBL_MAX_10_EXP, DBL_MAX_10_EXP, nthreads, "jbm_exp10_8xf64");
  efficiency_f64 (TYPE_JBM_EXPM1, thread_8xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_expm1_8xf64");
  efficiency_f64 (TYPE_JBM_CBRT, thread_8xf64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_cbrt_8xf64");
  efficiency_f64 (TYPE_JBM_LOG2, thread_8xf64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_log2_8xf64");
  efficiency_f64 (TYPE_JBM_LOG, thread_8xf64, x64, y64, r, n, DBL_MIN, DBL_MAX,
                  nthreads, "jbm_log_8xf64");
  efficiency_f64 (TYPE_JBM_LOG10, thread_8xf64, x64, y64, r, n, DBL_MIN,
                  DBL_MAX, nthreads, "jbm_log10_8xf64");
  efficiency_f64 (TYPE_JBM_SIN, thread_8xf64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_sin_8xf64");
  efficiency_f64 (TYPE_JBM_COS, thread_8xf64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_cos_8xf64");
  efficiency_f64 (TYPE_JBM_TAN, thread_8xf64, x64, y64, r, n, -4. * M_PI,
                  4. * M_PI, nthreads, "jbm_tan_8xf64");
  efficiency_f64 (TYPE_JBM_ATAN, thread_8xf64, x64, y64, r, n, -DBL_MAX,
                  DBL_MAX, nthreads, "jbm_atan_8xf64");
  efficiency_f64 (TYPE_JBM_ASIN, thread_8xf64, x64, y64, r, n, -1., 1.,
                  nthreads, "jbm_asin_8xf64");
  efficiency_f64 (TYPE_JBM_ACOS, thread_8xf64, x64, y64, r, n, -1., 1.,
                  nthreads, "jbm_acos_8xf64");
  efficiency_f64 (TYPE_JBM_SINH, thread_8xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_sinh_8xf64");
  efficiency_f64 (TYPE_JBM_COSH, thread_8xf64, x64, y64, r, n,
                  -JBM_DBL_MAX_E_EXP, JBM_DBL_MAX_E_EXP, nthreads,
                  "jbm_cosh_8xf64");
  efficiency_f64 (TYPE_JBM_TANH, thread_8xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_tanh_8xf64");
  efficiency_f64 (TYPE_JBM_ERF, thread_8xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_erf_8xf64");
  efficiency_f64 (TYPE_JBM_ERFC, thread_8xf64, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_erfc_8xf64");

#endif

  // free memory
  JB_FREE (y64);
  JB_FREE (x64);
  JB_FREE (y32);
  JB_FREE (x32);
  free (r);

  return 0;
}
