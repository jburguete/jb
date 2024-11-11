#include "../src/math.h"
#include <gsl/gsl_rng.h>
#include <glib.h>

#define SEED 7l

// float functions

typedef struct
{
  unsigned long int imin;
  unsigned long int imax;
  float *x;
  float *y;
  float (*f) (float);
} Parallel_f32;

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

static inline void *
thread_f32 (void *data)
{
  Parallel_f32 *p;
  float (*f) (float);
  float *x, *y;
  unsigned long int i, imin, imax;
  p = (Parallel_f32 *) data;
  f = p->f;
  x = p->x;
  y = p->y;
  imin = p->imin;
  imax = p->imax;
  for (i = imin; i < imax; ++i)
    y[i] = f (x[i]);
  g_thread_exit (NULL);
  return NULL;
}

static inline void
efficiency_f32 (float (*f) (float), long double (*g) (long double),
                float *restrict x, float *restrict y, const double *r,
                unsigned long int n, const float xmin, const float xmax,
                const unsigned int nthreads, const char *label)
{
  Parallel_f32 p[nthreads];
  GThread *thread[nthreads];
  long double em, e;
  float dx, t;
  clock_t t0;
  unsigned long int i;
  n = (n / (unsigned long int) nthreads) * (unsigned long int) nthreads;
  for (i = 0, dx = xmax - xmin; i < n; ++i)
    x[i] = xmin + dx * r[i];
  t0 = clock ();
  if (nthreads < 2)
    for (i = 0; i < n; ++i)
      y[i] = f (x[i]);
  else
    {
      for (i = 0; i < (unsigned long int) nthreads; ++i)
        {
          p[i].imin = i * n / (unsigned long int) nthreads;
          p[i].imax = (i + 1) * n / (unsigned long int) nthreads;
          p[i].x = x;
          p[i].y = y;
          p[i].f = f;
          thread[i] = g_thread_new (NULL, &thread_f32, p + i);
          g_thread_join (thread[i]);
        }
    }
  t = (clock () - t0) / (n * (float) CLOCKS_PER_SEC);
  for (i = 0, em = 0.L; i < n; ++i)
    {
      e = fabsl (y[i] - g ((long double) x[i]));
      if (e > em)
        em = e;
    }
  printf ("%s time=%g error=%Lg\n", label, t, em);
}

// double functions

typedef struct
{
  unsigned long int imin;
  unsigned long int imax;
  double *x;
  double *y;
  double (*f) (double);
} Parallel_f64;

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

static inline void *
thread_f64 (void *data)
{
  Parallel_f64 *p;
  double (*f) (double);
  double *x, *y;
  unsigned long int i, imin, imax;
  p = (Parallel_f64 *) data;
  f = p->f;
  x = p->x;
  y = p->y;
  imin = p->imin;
  imax = p->imax;
  for (i = imin; i < imax; ++i)
    y[i] = f (x[i]);
  g_thread_exit (NULL);
  return NULL;
}

static inline void
efficiency_f64 (double (*f) (double), long double (*g) (long double),
                double *restrict x, double *restrict y, const double *r,
                unsigned long int n, const double xmin, const double xmax,
                const unsigned int nthreads, const char *label)
{
  Parallel_f64 p[nthreads];
  GThread *thread[nthreads];
  long double em, e;
  double dx, t;
  clock_t t0;
  unsigned long int i;
  n = (n / (unsigned long int) nthreads) * (unsigned long int) nthreads;
  for (i = 0, dx = xmax - xmin; i < n; ++i)
    x[i] = xmin + dx * r[i];
  t0 = clock ();
  if (nthreads < 2)
    for (i = 0; i < n; ++i)
      y[i] = f (x[i]);
  else
    {
      for (i = 0; i < (unsigned long int) nthreads; ++i)
        {
          p[i].imin = i * n / (unsigned long int) nthreads;
          p[i].imax = (i + 1) * n / (unsigned long int) nthreads;
          p[i].x = x;
          p[i].y = y;
          p[i].f = f;
          thread[i] = g_thread_new (NULL, &thread_f64, p + i);
          g_thread_join (thread[i]);
        }
    }
  t = (clock () - t0) / (n * (float) CLOCKS_PER_SEC);
  for (i = 0, em = 0.L; i < n; ++i)
    {
      e = fabsl (y[i] - g ((long double) x[i]));
      if (e > em)
        em = e;
    }
  printf ("%s time=%lg error=%Lg\n", label, t, em);
}

// long double functions

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

typedef struct
{
  unsigned long int imin;
  unsigned long int imax;
  float *x;
  float *y;
    __m128 (*f) (__m128);
} Parallel_4xf32;

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

static inline void *
thread_4xf32 (void *data)
{
  Parallel_4xf32 *p;
  __m128 (*f) (__m128);
  float *x, *y;
  __m128 xv, yv;
  unsigned long int i, imin, imax;
  p = (Parallel_4xf32 *) data;
  f = p->f;
  x = p->x;
  y = p->y;
  imin = p->imin;
  imax = p->imax;
  for (i = imin; i < imax; i += 4)
    {
      xv = _mm_load_ps (x + i);
      yv = f (xv);
      _mm_store_ps (y + i, yv);
    }
  g_thread_exit (NULL);
  return NULL;
}

static inline void
efficiency_4xf32 (__m128 (*f) (__m128), long double (*g) (long double),
                  float *restrict x, float *restrict y, const double *r,
                  unsigned long int n, const float xmin, const float xmax,
                  const unsigned int nthreads, const char *label)
{
  Parallel_4xf32 p[nthreads];
  GThread *thread[nthreads];
  __m128 xv, yv;
  long double em, e;
  float dx, t;
  clock_t t0;
  unsigned long int i;
  n = (n / (unsigned long int) (4 * nthreads))
    * (unsigned long int) 4 *nthreads;
  for (i = 0, dx = xmax - xmin; i < n; ++i)
    x[i] = xmin + dx * r[i];
  t0 = clock ();
  if (nthreads < 2)
    for (i = 0; i < n; i += 4)
      {
        xv = _mm_load_ps (x + i);
        yv = f (xv);
        _mm_store_ps (y + i, yv);
      }
  else
    {
      for (i = 0; i < (unsigned long int) nthreads; ++i)
        {
          p[i].imin = i * n / (unsigned long int) nthreads;
          p[i].imax = (i + 1) * n / (unsigned long int) nthreads;
          p[i].x = x;
          p[i].y = y;
          p[i].f = f;
          thread[i] = g_thread_new (NULL, &thread_4xf32, p + i);
          g_thread_join (thread[i]);
        }
    }
  t = (clock () - t0) / (n * (float) CLOCKS_PER_SEC);
  for (i = 0, em = 0.L; i < n; ++i)
    {
      e = fabsl (y[i] - g ((long double) x[i]));
      if (e > em)
        em = e;
    }
  printf ("%s time=%g error=%Lg\n", label, t, em);
}

typedef struct
{
  unsigned long int imin;
  unsigned long int imax;
  double *x;
  double *y;
    __m128d (*f) (__m128d);
} Parallel_2xf64;

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

static inline void *
thread_2xf64 (void *data)
{
  Parallel_2xf64 *p;
  __m128d (*f) (__m128d);
  double *x, *y;
  __m128d xv, yv;
  unsigned long int i, imin, imax;
  p = (Parallel_2xf64 *) data;
  f = p->f;
  x = p->x;
  y = p->y;
  imin = p->imin;
  imax = p->imax;
  for (i = imin; i < imax; i += 2)
    {
      xv = _mm_load_pd (x + i);
      yv = f (xv);
      _mm_store_pd (y + i, yv);
    }
  g_thread_exit (NULL);
  return NULL;
}

static inline void
efficiency_2xf64 (__m128d (*f) (__m128d), long double (*g) (long double),
                  double *restrict x, double *restrict y, const double *r,
                  unsigned long int n, const double xmin, const double xmax,
                  const unsigned int nthreads, const char *label)
{
  Parallel_2xf64 p[nthreads];
  GThread *thread[nthreads];
  __m128d xv, yv;
  long double em, e;
  double dx, t;
  clock_t t0;
  unsigned long int i;
  n = (n / (unsigned long int) (2 * nthreads))
    * (unsigned long int) 2 *nthreads;
  for (i = 0, dx = xmax - xmin; i < n; ++i)
    x[i] = xmin + dx * r[i];
  t0 = clock ();
  if (nthreads < 2)
    for (i = 0; i < n; i += 2)
      {
        xv = _mm_load_pd (x + i);
        yv = f (xv);
        _mm_store_pd (y + i, yv);
      }
  else
    {
      for (i = 0; i < (unsigned long int) nthreads; ++i)
        {
          p[i].imin = i * n / (unsigned long int) nthreads;
          p[i].imax = (i + 1) * n / (unsigned long int) nthreads;
          p[i].x = x;
          p[i].y = y;
          p[i].f = f;
          thread[i] = g_thread_new (NULL, &thread_2xf64, p + i);
          g_thread_join (thread[i]);
        }
    }
  t = (clock () - t0) / (n * (double) CLOCKS_PER_SEC);
  for (i = 0, em = 0.L; i < n; ++i)
    {
      e = fabsl (y[i] - g ((long double) x[i]));
      if (e > em)
        em = e;
    }
  printf ("%s time=%lg error=%Lg\n", label, t, em);
}

#endif

#ifdef __AVX__

typedef struct
{
  unsigned long int imin;
  unsigned long int imax;
  float *x;
  float *y;
    __m256 (*f) (__m256);
} Parallel_8xf32;

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

static inline void *
thread_8xf32 (void *data)
{
  Parallel_8xf32 *p;
  __m256 (*f) (__m256);
  float *x, *y;
  __m256 xv, yv;
  unsigned long int i, imin, imax;
  p = (Parallel_8xf32 *) data;
  f = p->f;
  x = p->x;
  y = p->y;
  imin = p->imin;
  imax = p->imax;
  for (i = imin; i < imax; i += 8)
    {
      xv = _mm256_load_ps (x + i);
      yv = f (xv);
      _mm256_store_ps (y + i, yv);
    }
  g_thread_exit (NULL);
  return NULL;
}

static inline void
efficiency_8xf32 (__m256 (*f) (__m256), long double (*g) (long double),
                  float *restrict x, float *restrict y, const double *r,
                  unsigned long int n, const float xmin, const float xmax,
                  const unsigned int nthreads, const char *label)
{
  Parallel_8xf32 p[nthreads];
  GThread *thread[nthreads];
  __m256 xv, yv;
  long double em, e;
  float dx, t;
  clock_t t0;
  unsigned long int i;
  n = (n / (unsigned long int) (8 * nthreads))
    * (unsigned long int) 8 *nthreads;
  for (i = 0, dx = xmax - xmin; i < n; ++i)
    x[i] = xmin + dx * r[i];
  t0 = clock ();
  if (nthreads < 2)
    for (i = 0; i < n; i += 8)
      {
        xv = _mm256_load_ps (x + i);
        yv = f (xv);
        _mm256_store_ps (y + i, yv);
      }
  else
    {
      for (i = 0; i < (unsigned long int) nthreads; ++i)
        {
          p[i].imin = i * n / (unsigned long int) nthreads;
          p[i].imax = (i + 1) * n / (unsigned long int) nthreads;
          p[i].x = x;
          p[i].y = y;
          p[i].f = f;
          thread[i] = g_thread_new (NULL, &thread_8xf32, p + i);
          g_thread_join (thread[i]);
        }
    }
  t = (clock () - t0) / (n * (float) CLOCKS_PER_SEC);
  for (i = 0, em = 0.L; i < n; ++i)
    {
      e = fabsl (y[i] - g ((long double) x[i]));
      if (e > em)
        em = e;
    }
  printf ("%s time=%g error=%Lg\n", label, t, em);
}

typedef struct
{
  unsigned long int imin;
  unsigned long int imax;
  double *x;
  double *y;
    __m256d (*f) (__m256d);
} Parallel_4xf64;

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

static inline void *
thread_4xf64 (void *data)
{
  Parallel_4xf64 *p;
  __m256d (*f) (__m256d);
  double *x, *y;
  __m256d xv, yv;
  unsigned long int i, imin, imax;
  p = (Parallel_4xf64 *) data;
  f = p->f;
  x = p->x;
  y = p->y;
  imin = p->imin;
  imax = p->imax;
  for (i = imin; i < imax; i += 4)
    {
      xv = _mm256_load_pd (x + i);
      yv = f (xv);
      _mm256_store_pd (y + i, yv);
    }
  g_thread_exit (NULL);
  return NULL;
}

static inline void
efficiency_4xf64 (__m256d (*f) (__m256d), long double (*g) (long double),
                  double *restrict x, double *restrict y, const double *r,
                  unsigned long int n, const double xmin, const double xmax,
                  const unsigned int nthreads, const char *label)
{
  Parallel_4xf64 p[nthreads];
  GThread *thread[nthreads];
  __m256d xv, yv;
  long double em, e;
  double dx, t;
  clock_t t0;
  unsigned long int i;
  n = (n / (unsigned long int) (4 * nthreads))
    * (unsigned long int) 4 *nthreads;
  for (i = 0, dx = xmax - xmin; i < n; ++i)
    x[i] = xmin + dx * r[i];
  t0 = clock ();
  if (nthreads < 2)
    for (i = 0; i < n; i += 4)
      {
        xv = _mm256_load_pd (x + i);
        yv = f (xv);
        _mm256_store_pd (y + i, yv);
      }
  else
    {
      for (i = 0; i < (unsigned long int) nthreads; ++i)
        {
          p[i].imin = i * n / (unsigned long int) nthreads;
          p[i].imax = (i + 1) * n / (unsigned long int) nthreads;
          p[i].x = x;
          p[i].y = y;
          p[i].f = f;
          thread[i] = g_thread_new (NULL, &thread_4xf64, p + i);
          g_thread_join (thread[i]);
        }
    }
  t = (clock () - t0) / (n * (double) CLOCKS_PER_SEC);
  for (i = 0, em = 0.L; i < n; ++i)
    {
      e = fabsl (y[i] - g ((long double) x[i]));
      if (e > em)
        em = e;
    }
  printf ("%s time=%lg error=%Lg\n", label, t, em);
}

#endif

#ifdef __AVX512F__

typedef struct
{
  unsigned long int imin;
  unsigned long int imax;
  float *x;
  float *y;
    __m512 (*f) (__m512);
} Parallel_16xf32;

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

static inline void *
thread_16xf32 (void *data)
{
  Parallel_16xf32 *p;
  __m512 (*f) (__m512);
  float *x, *y;
  __m512 xv, yv;
  unsigned long int i, imin, imax;
  p = (Parallel_16xf32 *) data;
  f = p->f;
  x = p->x;
  y = p->y;
  imin = p->imin;
  imax = p->imax;
  for (i = imin; i < imax; i += 16)
    {
      xv = _mm512_load_ps (x + i);
      yv = f (xv);
      _mm512_store_ps (y + i, yv);
    }
  g_thread_exit (NULL);
  return NULL;
}

static inline void
efficiency_16xf32 (__m512 (*f) (__m512), long double (*g) (long double),
                   float *restrict x, float *restrict y, const double *r,
                   unsigned long int n, const float xmin, const float xmax,
                   const unsigned int nthreads, const char *label)
{
  Parallel_16xf32 p[nthreads];
  GThread *thread[nthreads];
  __m512 xv, yv;
  long double em, e;
  float dx, t;
  clock_t t0;
  unsigned long int i;
  n = (n / (unsigned long int) (16 * nthreads))
    * (unsigned long int) 16 *nthreads;
  for (i = 0, dx = xmax - xmin; i < n; ++i)
    x[i] = xmin + dx * r[i];
  t0 = clock ();
  if (nthreads < 2)
    for (i = 0; i < n; i += 16)
      {
        xv = _mm512_load_ps (x + i);
        yv = f (xv);
        _mm512_store_ps (y + i, yv);
      }
  else
    {
      for (i = 0; i < (unsigned long int) nthreads; ++i)
        {
          p[i].imin = i * n / (unsigned long int) nthreads;
          p[i].imax = (i + 1) * n / (unsigned long int) nthreads;
          p[i].x = x;
          p[i].y = y;
          p[i].f = f;
          thread[i] = g_thread_new (NULL, &thread_16xf32, p + i);
          g_thread_join (thread[i]);
        }
    }
  t = (clock () - t0) / (n * (float) CLOCKS_PER_SEC);
  for (i = 0, em = 0.L; i < n; ++i)
    {
      e = fabsl (y[i] - g ((long double) x[i]));
      if (e > em)
        em = e;
    }
  printf ("%s time=%g error=%Lg\n", label, t, em);
}

typedef struct
{
  unsigned long int imin;
  unsigned long int imax;
  double *x;
  double *y;
    __m512d (*f) (__m512d);
} Parallel_8xf64;

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

static inline void *
thread_8xf64 (void *data)
{
  Parallel_8xf64 *p;
  __m512d (*f) (__m512d);
  double *x, *y;
  __m512d xv, yv;
  unsigned long int i, imin, imax;
  p = (Parallel_8xf64 *) data;
  f = p->f;
  x = p->x;
  y = p->y;
  imin = p->imin;
  imax = p->imax;
  for (i = imin; i < imax; i += 8)
    {
      xv = _mm512_load_pd (x + i);
      yv = f (xv);
      _mm512_store_pd (y + i, yv);
    }
  g_thread_exit (NULL);
  return NULL;
}

static inline void
efficiency_8xf64 (__m512d (*f) (__m512d), long double (*g) (long double),
                  double *restrict x, double *restrict y, const double *r,
                  unsigned long int n, const double xmin, const double xmax,
                  const unsigned int nthreads, const char *label)
{
  Parallel_8xf64 p[nthreads];
  GThread *thread[nthreads];
  __m512d xv, yv;
  long double em, e;
  double dx, t;
  clock_t t0;
  unsigned long int i;
  n = (n / (unsigned long int) (8 * nthreads))
    * (unsigned long int) 8 *nthreads;
  for (i = 0, dx = xmax - xmin; i < n; ++i)
    x[i] = xmin + dx * r[i];
  t0 = clock ();
  if (nthreads < 2)
    for (i = 0; i < n; i += 8)
      {
        xv = _mm512_load_pd (x + i);
        yv = f (xv);
        _mm512_store_pd (y + i, yv);
      }
  else
    {
      for (i = 0; i < (unsigned long int) nthreads; ++i)
        {
          p[i].imin = i * n / (unsigned long int) nthreads;
          p[i].imax = (i + 1) * n / (unsigned long int) nthreads;
          p[i].x = x;
          p[i].y = y;
          p[i].f = f;
          thread[i] = g_thread_new (NULL, &thread_8xf64, p + i);
          g_thread_join (thread[i]);
        }
    }
  t = (clock () - t0) / (n * (double) CLOCKS_PER_SEC);
  for (i = 0, em = 0.L; i < n; ++i)
    {
      e = fabsl (y[i] - g ((long double) x[i]));
      if (e > em)
        em = e;
    }
  printf ("%s time=%lg error=%Lg\n", label, t, em);
}

#endif

int
main (int argn, char **argc)
{
  gsl_rng *rng;
  double *r, *x64, *y64;
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
  n = (unsigned long int) atol (argc[1]);
  nthreads = (unsigned int) atoi (argc[2]);
  n = (n / (unsigned long int) nthreads) * (unsigned long int) nthreads;
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
  efficiency_f32 (add_f32, add_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX, nthreads,
                  "add_f32");
  efficiency_f32 (sub_f32, sub_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX, nthreads,
                  "sub_f32");
  efficiency_f32 (mul_f32, mul_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX, nthreads,
                  "mul_f32");
  efficiency_f32 (div_f32, div_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX, nthreads,
                  "div_f32");
  efficiency_f32 (sqrtf, sqrtl, x32, y32, r, n, 0.f, FLT_MAX, nthreads,
                  "sqrtf");
  efficiency_f32 (max_f32, max_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX, nthreads,
                  "max_f32");
  efficiency_f32 (min_f32, min_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX, nthreads,
                  "min_f32");
  efficiency_f32 (fabsf, fabsl, x32, y32, r, n, -FLT_MAX, FLT_MAX, nthreads,
                  "fabsf");
  efficiency_f32 (jbm_abs_f32, fabsl, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "jbm_abs_f32");
  efficiency_f32 (exp2f, exp2l, x32, y32, r, n, -FLT_MAX_EXP, FLT_MAX_EXP,
                  nthreads, "exp2f");
  efficiency_f32 (jbm_exp2_f32, exp2l, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_exp2_f32");
  efficiency_f32 (expf, expl, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "expf");
  efficiency_f32 (jbm_exp_f32, expl, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "jbm_exp_f32");
  efficiency_f32 (exp10f, exp10l, x32, y32, r, n, -FLT_MAX_10_EXP,
                  FLT_MAX_10_EXP, nthreads, "exp10f");
  efficiency_f32 (jbm_exp10_f32, exp10l, x32, y32, r, n, -FLT_MAX_10_EXP,
                  FLT_MAX_10_EXP, nthreads, "jbm_exp10_f32");
  efficiency_f32 (expm1f, expm1l, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "expm1f");
  efficiency_f32 (jbm_expm1_f32, expm1l, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "jbm_expm1_f32");
  efficiency_f32 (cbrtf, cbrtl, x32, y32, r, n, -FLT_MAX, FLT_MAX, nthreads,
                  "cbrtf");
  efficiency_f32 (jbm_cbrt_f32, cbrtl, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "jbm_cbrt_f32");
  efficiency_f32 (log2f, log2l, x32, y32, r, n, FLT_MIN, FLT_MAX, nthreads,
                  "log2f");
  efficiency_f32 (jbm_log2_f32, log2l, x32, y32, r, n, FLT_MIN, FLT_MAX,
                  nthreads, "jbm_log2_f32");
  efficiency_f32 (logf, logl, x32, y32, r, n, FLT_MIN, FLT_MAX, nthreads,
                  "logf");
  efficiency_f32 (jbm_log_f32, logl, x32, y32, r, n, FLT_MIN, FLT_MAX, nthreads,
                  "jbm_log_f32");
  efficiency_f32 (log10f, log10l, x32, y32, r, n, FLT_MIN, FLT_MAX, nthreads,
                  "log10f");
  efficiency_f32 (jbm_log10_f32, log10l, x32, y32, r, n, FLT_MIN, FLT_MAX,
                  nthreads, "jbm_log10_f32");
  efficiency_f32 (sinf, sinl, x32, y32, r, n, -4.f * M_PIf, 4.f * M_PIf,
                  nthreads, "sinf");
  efficiency_f32 (jbm_sin_f32, sinl, x32, y32, r, n, -4.f * M_PIf, 4.f * M_PIf,
                  nthreads, "jbm_sin_f32");
  efficiency_f32 (cosf, cosl, x32, y32, r, n, -4.f * M_PIf, 4.f * M_PIf,
                  nthreads, "cosf");
  efficiency_f32 (jbm_cos_f32, cosl, x32, y32, r, n, -4.f * M_PIf, 4.f * M_PIf,
                  nthreads, "jbm_cos_f32");
  efficiency_f32 (tanf, tanl, x32, y32, r, n, -4.f * M_PIf, 4.f * M_PIf,
                  nthreads, "tanf");
  efficiency_f32 (jbm_tan_f32, tanl, x32, y32, r, n, -4.f * M_PIf, 4.f * M_PIf,
                  nthreads, "jbm_tan_f32");
  efficiency_f32 (atanf, atanl, x32, y32, r, n, -FLT_MAX, FLT_MAX, nthreads,
                  "atanf");
  efficiency_f32 (jbm_atan_f32, atanl, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                  nthreads, "jbm_atan_f32");
  efficiency_f32 (asinf, asinl, x32, y32, r, n, -1.f, 1.f, nthreads, "asinf");
  efficiency_f32 (jbm_asin_f32, asinl, x32, y32, r, n, -1.f, 1.f, nthreads,
                  "jbm_asin_f32");
  efficiency_f32 (acosf, acosl, x32, y32, r, n, -1.f, 1.f, nthreads, "acosf");
  efficiency_f32 (jbm_acos_f32, acosl, x32, y32, r, n, -1.f, 1.f, nthreads,
                  "jbm_acos_f32");
  efficiency_f32 (sinhf, sinhl, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "sinhf");
  efficiency_f32 (jbm_sinh_f32, sinhl, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "jbm_sinh_f32");
  efficiency_f32 (coshf, coshl, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "coshf");
  efficiency_f32 (jbm_cosh_f32, coshl, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                  JBM_FLT_MAX_E_EXP, nthreads, "jbm_cosh_f32");
  efficiency_f32 (tanhf, tanhl, x32, y32, r, n, -FLT_MAX_EXP, FLT_MAX_EXP,
                  nthreads, "tanhf");
  efficiency_f32 (jbm_tanh_f32, tanhl, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_tanh_f32");
  efficiency_f32 (erff, erfl, x32, y32, r, n, -FLT_MAX_EXP, FLT_MAX_EXP,
                  nthreads, "erff");
  efficiency_f32 (jbm_erf_f32, erfl, x32, y32, r, n, -FLT_MAX_EXP, FLT_MAX_EXP,
                  nthreads, "jbm_erf_f32");
  efficiency_f32 (erfcf, erfcl, x32, y32, r, n, -FLT_MAX_EXP, FLT_MAX_EXP,
                  nthreads, "erfcf");
  efficiency_f32 (jbm_erfc_f32, erfcl, x32, y32, r, n, -FLT_MAX_EXP,
                  FLT_MAX_EXP, nthreads, "jbm_erfc_f32");

  // double functions
  printf ("double functions\n");
  efficiency_f64 (add_f64, add_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX, nthreads,
                  "add_f64");
  efficiency_f64 (sub_f64, sub_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX, nthreads,
                  "sub_f64");
  efficiency_f64 (mul_f64, mul_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX, nthreads,
                  "mul_f64");
  efficiency_f64 (div_f64, div_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX, nthreads,
                  "div_f64");
  efficiency_f64 (sqrt, sqrtl, x64, y64, r, n, 0., DBL_MAX, nthreads, "sqrtf");
  efficiency_f64 (max_f64, max_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX, nthreads,
                  "max_f64");
  efficiency_f64 (min_f64, min_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX, nthreads,
                  "min_f64");
  efficiency_f64 (fabs, fabsl, x64, y64, r, n, -DBL_MAX, DBL_MAX, nthreads,
                  "fabsf");
  efficiency_f64 (jbm_abs_f64, fabsl, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "jbm_abs_f64");
  efficiency_f64 (exp2, exp2l, x64, y64, r, n, -DBL_MAX_EXP, DBL_MAX_EXP,
                  nthreads, "exp2f");
  efficiency_f64 (jbm_exp2_f64, exp2l, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_exp2_f64");
  efficiency_f64 (exp, expl, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                  JBM_DBL_MAX_E_EXP, nthreads, "expf");
  efficiency_f64 (jbm_exp_f64, expl, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                  JBM_DBL_MAX_E_EXP, nthreads, "jbm_exp_f64");
  efficiency_f64 (exp10, exp10l, x64, y64, r, n, -DBL_MAX_10_EXP,
                  DBL_MAX_10_EXP, nthreads, "exp10f");
  efficiency_f64 (jbm_exp10_f64, exp10l, x64, y64, r, n, -DBL_MAX_10_EXP,
                  DBL_MAX_10_EXP, nthreads, "jbm_exp10_f64");
  efficiency_f64 (expm1, expm1l, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                  JBM_DBL_MAX_E_EXP, nthreads, "expm1f");
  efficiency_f64 (jbm_expm1_f64, expm1l, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                  JBM_DBL_MAX_E_EXP, nthreads, "jbm_expm1_f64");
  efficiency_f64 (cbrt, cbrtl, x64, y64, r, n, -DBL_MAX, DBL_MAX, nthreads,
                  "cbrtf");
  efficiency_f64 (jbm_cbrt_f64, cbrtl, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "jbm_cbrt_f64");
  efficiency_f64 (log2, log2l, x64, y64, r, n, DBL_MIN, DBL_MAX, nthreads,
                  "log2f");
  efficiency_f64 (jbm_log2_f64, log2l, x64, y64, r, n, DBL_MIN, DBL_MAX,
                  nthreads, "jbm_log2_f64");
  efficiency_f64 (log, logl, x64, y64, r, n, DBL_MIN, DBL_MAX, nthreads,
                  "logf");
  efficiency_f64 (jbm_log_f64, logl, x64, y64, r, n, DBL_MIN, DBL_MAX, nthreads,
                  "jbm_log_f64");
  efficiency_f64 (log10, log10l, x64, y64, r, n, DBL_MIN, DBL_MAX, nthreads,
                  "log10f");
  efficiency_f64 (jbm_log10_f64, log10l, x64, y64, r, n, DBL_MIN, DBL_MAX,
                  nthreads, "jbm_log10_f64");
  efficiency_f64 (sin, sinl, x64, y64, r, n, -4. * M_PI, 4. * M_PI,
                  nthreads, "sinf");
  efficiency_f64 (jbm_sin_f64, sinl, x64, y64, r, n, -4. * M_PI, 4. * M_PI,
                  nthreads, "jbm_sin_f64");
  efficiency_f64 (cos, cosl, x64, y64, r, n, -4. * M_PI, 4. * M_PI,
                  nthreads, "cosf");
  efficiency_f64 (jbm_cos_f64, cosl, x64, y64, r, n, -4. * M_PI, 4. * M_PI,
                  nthreads, "jbm_cos_f64");
  efficiency_f64 (tan, tanl, x64, y64, r, n, -4. * M_PI, 4. * M_PI,
                  nthreads, "tanf");
  efficiency_f64 (jbm_tan_f64, tanl, x64, y64, r, n, -4. * M_PI, 4. * M_PI,
                  nthreads, "jbm_tan_f64");
  efficiency_f64 (atan, atanl, x64, y64, r, n, -DBL_MAX, DBL_MAX, nthreads,
                  "atanf");
  efficiency_f64 (jbm_atan_f64, atanl, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                  nthreads, "jbm_atan_f64");
  efficiency_f64 (asin, asinl, x64, y64, r, n, -1., 1., nthreads, "asinf");
  efficiency_f64 (jbm_asin_f64, asinl, x64, y64, r, n, -1., 1., nthreads,
                  "jbm_asin_f64");
  efficiency_f64 (acos, acosl, x64, y64, r, n, -1., 1., nthreads, "acosf");
  efficiency_f64 (jbm_acos_f64, acosl, x64, y64, r, n, -1., 1., nthreads,
                  "jbm_acos_f64");
  efficiency_f64 (sinh, sinhl, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                  JBM_DBL_MAX_E_EXP, nthreads, "sinhf");
  efficiency_f64 (jbm_sinh_f64, sinhl, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                  JBM_DBL_MAX_E_EXP, nthreads, "jbm_sinh_f64");
  efficiency_f64 (cosh, coshl, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                  JBM_DBL_MAX_E_EXP, nthreads, "coshf");
  efficiency_f64 (jbm_cosh_f64, coshl, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                  JBM_DBL_MAX_E_EXP, nthreads, "jbm_cosh_f64");
  efficiency_f64 (tanh, tanhl, x64, y64, r, n, -DBL_MAX_EXP, DBL_MAX_EXP,
                  nthreads, "tanhf");
  efficiency_f64 (jbm_tanh_f64, tanhl, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_tanh_f64");
  efficiency_f64 (erf, erfl, x64, y64, r, n, -DBL_MAX_EXP, DBL_MAX_EXP,
                  nthreads, "erff");
  efficiency_f64 (jbm_erf_f64, erfl, x64, y64, r, n, -DBL_MAX_EXP, DBL_MAX_EXP,
                  nthreads, "jbm_erf_f64");
  efficiency_f64 (erfc, erfcl, x64, y64, r, n, -DBL_MAX_EXP, DBL_MAX_EXP,
                  nthreads, "erfcf");
  efficiency_f64 (jbm_erfc_f64, erfcl, x64, y64, r, n, -DBL_MAX_EXP,
                  DBL_MAX_EXP, nthreads, "jbm_erfc_f64");

#ifdef __SSE4_2__

  // __m128 functions
  printf ("__m128 functions\n");
  efficiency_4xf32 (add_4xf32, add_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                    nthreads, "add_4xf32");
  efficiency_4xf32 (sub_4xf32, sub_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                    nthreads, "sub_4xf32");
  efficiency_4xf32 (mul_4xf32, mul_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                    nthreads, "mul_4xf32");
  efficiency_4xf32 (div_4xf32, div_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                    nthreads, "div_4xf32");
  efficiency_4xf32 (max_4xf32, max_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                    nthreads, "max_4xf32");
  efficiency_4xf32 (min_4xf32, min_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                    nthreads, "min_4xf32");
  efficiency_4xf32 (jbm_abs_4xf32, fabsl, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                    nthreads, "jbm_abs_4xf32");
  efficiency_4xf32 (jbm_exp2_4xf32, exp2l, x32, y32, r, n, -FLT_MAX_EXP,
                    FLT_MAX_EXP, nthreads, "jbm_exp2_4xf32");
  efficiency_4xf32 (jbm_exp_4xf32, expl, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                    JBM_FLT_MAX_E_EXP, nthreads, "jbm_exp_4xf32");
  efficiency_4xf32 (jbm_exp10_4xf32, exp10l, x32, y32, r, n, -FLT_MAX_10_EXP,
                    FLT_MAX_10_EXP, nthreads, "jbm_exp10_4xf32");
  efficiency_4xf32 (jbm_expm1_4xf32, expm1l, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                    JBM_FLT_MAX_E_EXP, nthreads, "jbm_expm1_4xf32");
  efficiency_4xf32 (jbm_cbrt_4xf32, cbrtl, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                    nthreads, "jbm_cbrt_4xf32");
  efficiency_4xf32 (jbm_log2_4xf32, log2l, x32, y32, r, n, FLT_MIN, FLT_MAX,
                    nthreads, "jbm_log2_4xf32");
  efficiency_4xf32 (jbm_log_4xf32, logl, x32, y32, r, n, FLT_MIN, FLT_MAX,
                    nthreads, "jbm_log_4xf32");
  efficiency_4xf32 (jbm_log10_4xf32, log10l, x32, y32, r, n, FLT_MIN, FLT_MAX,
                    nthreads, "jbm_log10_4xf32");
  efficiency_4xf32 (jbm_sin_4xf32, sinl, x32, y32, r, n, -4.f * M_PIf,
                    4.f * M_PIf, nthreads, "jbm_sin_4xf32");
  efficiency_4xf32 (jbm_cos_4xf32, cosl, x32, y32, r, n, -4.f * M_PIf,
                    4.f * M_PIf, nthreads, "jbm_cos_4xf32");
  efficiency_4xf32 (jbm_tan_4xf32, tanl, x32, y32, r, n, -4.f * M_PIf,
                    4.f * M_PIf, nthreads, "jbm_tan_4xf32");
  efficiency_4xf32 (jbm_atan_4xf32, atanl, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                    nthreads, "jbm_atan_4xf32");
  efficiency_4xf32 (jbm_asin_4xf32, asinl, x32, y32, r, n, -1.f, 1.f, nthreads,
                    "jbm_asin_4xf32");
  efficiency_4xf32 (jbm_acos_4xf32, acosl, x32, y32, r, n, -1.f, 1.f, nthreads,
                    "jbm_acos_4xf32");
  efficiency_4xf32 (jbm_sinh_4xf32, sinhl, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                    JBM_FLT_MAX_E_EXP, nthreads, "jbm_sinh_4xf32");
  efficiency_4xf32 (jbm_cosh_4xf32, coshl, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                    JBM_FLT_MAX_E_EXP, nthreads, "jbm_cosh_4xf32");
  efficiency_4xf32 (jbm_tanh_4xf32, tanhl, x32, y32, r, n, -FLT_MAX_EXP,
                    FLT_MAX_EXP, nthreads, "jbm_tanh_4xf32");
  efficiency_4xf32 (jbm_erf_4xf32, erfl, x32, y32, r, n, -FLT_MAX_EXP,
                    FLT_MAX_EXP, nthreads, "jbm_erf_4xf32");
  efficiency_4xf32 (jbm_erfc_4xf32, erfcl, x32, y32, r, n, -FLT_MAX_EXP,
                    FLT_MAX_EXP, nthreads, "jbm_erfc_4xf32");

  printf ("__m128d functions\n");
  efficiency_2xf64 (add_2xf64, add_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "add_2xf64");
  efficiency_2xf64 (sub_2xf64, sub_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "sub_2xf64");
  efficiency_2xf64 (mul_2xf64, mul_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "mul_2xf64");
  efficiency_2xf64 (div_2xf64, div_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "div_2xf64");
  efficiency_2xf64 (max_2xf64, max_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "max_2xf64");
  efficiency_2xf64 (min_2xf64, min_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "min_2xf64");
  efficiency_2xf64 (jbm_abs_2xf64, fabsl, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "jbm_abs_2xf64");
  efficiency_2xf64 (jbm_exp2_2xf64, exp2l, x64, y64, r, n,
                    -DBL_MAX_EXP, DBL_MAX_EXP, nthreads, "jbm_exp2_2xf64");
  efficiency_2xf64 (jbm_exp_2xf64, expl, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                    JBM_DBL_MAX_E_EXP, nthreads, "jbm_exp_2xf64");
  efficiency_2xf64 (jbm_exp10_2xf64, exp10l, x64, y64, r, n, -DBL_MAX_10_EXP,
                    DBL_MAX_10_EXP, nthreads, "jbm_exp10_2xf64");
  efficiency_2xf64 (jbm_expm1_2xf64, expm1l, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                    JBM_DBL_MAX_E_EXP, nthreads, "jbm_expm1_2xf64");
  efficiency_2xf64 (jbm_cbrt_2xf64, cbrtl, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "jbm_cbrt_2xf64");
  efficiency_2xf64 (jbm_log2_2xf64, log2l, x64, y64, r, n, DBL_MIN, DBL_MAX,
                    nthreads, "jbm_log2_2xf64");
  efficiency_2xf64 (jbm_log_2xf64, logl, x64, y64, r, n, DBL_MIN, DBL_MAX,
                    nthreads, "jbm_log_2xf64");
  efficiency_2xf64 (jbm_log10_2xf64, log10l, x64, y64, r, n, DBL_MIN, DBL_MAX,
                    nthreads, "jbm_log10_2xf64");
  efficiency_2xf64 (jbm_sin_2xf64, sinl, x64, y64, r, n, -4. * M_PI, 4. * M_PI,
                    nthreads, "jbm_sin_2xf64");
  efficiency_2xf64 (jbm_cos_2xf64, cosl, x64, y64, r, n, -4. * M_PI, 4. * M_PI,
                    nthreads, "jbm_cos_2xf64");
  efficiency_2xf64 (jbm_tan_2xf64, tanl, x64, y64, r, n, -4. * M_PI, 4. * M_PI,
                    nthreads, "jbm_tan_2xf64");
  efficiency_2xf64 (jbm_atan_2xf64, atanl, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "jbm_atan_2xf64");
  efficiency_2xf64 (jbm_asin_2xf64, asinl, x64, y64, r, n, -1., 1., nthreads,
                    "jbm_asin_2xf64");
  efficiency_2xf64 (jbm_acos_2xf64, acosl, x64, y64, r, n, -1., 1., nthreads,
                    "jbm_acos_2xf64");
  efficiency_2xf64 (jbm_sinh_2xf64, sinhl, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                    JBM_DBL_MAX_E_EXP, nthreads, "jbm_sinh_2xf64");
  efficiency_2xf64 (jbm_cosh_2xf64, coshl, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                    JBM_DBL_MAX_E_EXP, nthreads, "jbm_cosh_2xf64");
  efficiency_2xf64 (jbm_tanh_2xf64, tanhl, x64, y64, r, n,
                    -DBL_MAX_EXP, DBL_MAX_EXP, nthreads, "jbm_tanh_2xf64");
  efficiency_2xf64 (jbm_erf_2xf64, erfl, x64, y64, r, n,
                    -DBL_MAX_EXP, DBL_MAX_EXP, nthreads, "jbm_erf_2xf64");
  efficiency_2xf64 (jbm_erfc_2xf64, erfcl, x64, y64, r, n,
                    -DBL_MAX_EXP, DBL_MAX_EXP, nthreads, "jbm_erfc_2xf64");

#endif

#ifdef __AVX__

  printf ("__m256 functions\n");
  efficiency_8xf32 (add_8xf32, add_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                    nthreads, "add_8xf32");
  efficiency_8xf32 (sub_8xf32, sub_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                    nthreads, "sub_8xf32");
  efficiency_8xf32 (mul_8xf32, mul_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                    nthreads, "mul_8xf32");
  efficiency_8xf32 (div_8xf32, div_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                    nthreads, "div_8xf32");
  efficiency_8xf32 (max_8xf32, max_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                    nthreads, "max_8xf32");
  efficiency_8xf32 (min_8xf32, min_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                    nthreads, "min_8xf32");
  efficiency_8xf32 (jbm_abs_8xf32, fabsl, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                    nthreads, "jbm_abs_8xf32");
  efficiency_8xf32 (jbm_exp2_8xf32, exp2l, x32, y32, r, n, -FLT_MAX_EXP,
                    FLT_MAX_EXP, nthreads, "jbm_exp2_8xf32");
  efficiency_8xf32 (jbm_exp_8xf32, expl, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                    JBM_FLT_MAX_E_EXP, nthreads, "jbm_exp_8xf32");
  efficiency_8xf32 (jbm_exp10_8xf32, exp10l, x32, y32, r, n, -FLT_MAX_10_EXP,
                    FLT_MAX_10_EXP, nthreads, "jbm_exp10_8xf32");
  efficiency_8xf32 (jbm_expm1_8xf32, expm1l, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                    JBM_FLT_MAX_E_EXP, nthreads, "jbm_expm1_8xf32");
  efficiency_8xf32 (jbm_cbrt_8xf32, cbrtl, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                    nthreads, "jbm_cbrt_8xf32");
  efficiency_8xf32 (jbm_log2_8xf32, log2l, x32, y32, r, n, FLT_MIN, FLT_MAX,
                    nthreads, "jbm_log2_8xf32");
  efficiency_8xf32 (jbm_log_8xf32, logl, x32, y32, r, n, FLT_MIN, FLT_MAX,
                    nthreads, "jbm_log_8xf32");
  efficiency_8xf32 (jbm_log10_8xf32, log10l, x32, y32, r, n, FLT_MIN, FLT_MAX,
                    nthreads, "jbm_log10_8xf32");
  efficiency_8xf32 (jbm_sin_8xf32, sinl, x32, y32, r, n, -4.f * M_PIf,
                    4.f * M_PIf, nthreads, "jbm_sin_8xf32");
  efficiency_8xf32 (jbm_cos_8xf32, cosl, x32, y32, r, n, -4.f * M_PIf,
                    4.f * M_PIf, nthreads, "jbm_cos_8xf32");
  efficiency_8xf32 (jbm_tan_8xf32, tanl, x32, y32, r, n, -4.f * M_PIf,
                    4.f * M_PIf, nthreads, "jbm_tan_8xf32");
  efficiency_8xf32 (jbm_atan_8xf32, atanl, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                    nthreads, "jbm_atan_8xf32");
  efficiency_8xf32 (jbm_asin_8xf32, asinl, x32, y32, r, n, -1.f, 1.f, nthreads,
                    "jbm_asin_8xf32");
  efficiency_8xf32 (jbm_acos_8xf32, acosl, x32, y32, r, n, -1.f, 1.f, nthreads,
                    "jbm_acos_8xf32");
  efficiency_8xf32 (jbm_sinh_8xf32, sinhl, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                    JBM_FLT_MAX_E_EXP, nthreads, "jbm_sinh_8xf32");
  efficiency_8xf32 (jbm_cosh_8xf32, coshl, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                    JBM_FLT_MAX_E_EXP, nthreads, "jbm_cosh_8xf32");
  efficiency_8xf32 (jbm_tanh_8xf32, tanhl, x32, y32, r, n, -FLT_MAX_EXP,
                    FLT_MAX_EXP, nthreads, "jbm_tanh_8xf32");
  efficiency_8xf32 (jbm_erf_8xf32, erfl, x32, y32, r, n, -FLT_MAX_EXP,
                    FLT_MAX_EXP, nthreads, "jbm_erf_8xf32");
  efficiency_8xf32 (jbm_erfc_8xf32, erfcl, x32, y32, r, n, -FLT_MAX_EXP,
                    FLT_MAX_EXP, nthreads, "jbm_erfc_8xf32");

  printf ("__m256d functions\n");
  efficiency_4xf64 (add_4xf64, add_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "add_4xf64");
  efficiency_4xf64 (sub_4xf64, sub_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "sub_4xf64");
  efficiency_4xf64 (mul_4xf64, mul_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "mul_4xf64");
  efficiency_4xf64 (div_4xf64, div_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "div_4xf64");
  efficiency_4xf64 (max_4xf64, max_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "max_4xf64");
  efficiency_4xf64 (min_4xf64, min_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "min_4xf64");
  efficiency_4xf64 (jbm_abs_4xf64, fabsl, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "jbm_abs_4xf64");
  efficiency_4xf64 (jbm_exp2_4xf64, exp2l, x64, y64, r, n,
                    -DBL_MAX_EXP, DBL_MAX_EXP, nthreads, "jbm_exp2_4xf64");
  efficiency_4xf64 (jbm_exp_4xf64, expl, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                    JBM_DBL_MAX_E_EXP, nthreads, "jbm_exp_4xf64");
  efficiency_4xf64 (jbm_exp10_4xf64, exp10l, x64, y64, r, n, -DBL_MAX_10_EXP,
                    DBL_MAX_10_EXP, nthreads, "jbm_exp10_4xf64");
  efficiency_4xf64 (jbm_expm1_4xf64, expm1l, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                    JBM_DBL_MAX_E_EXP, nthreads, "jbm_expm1_4xf64");
  efficiency_4xf64 (jbm_cbrt_4xf64, cbrtl, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "jbm_cbrt_4xf64");
  efficiency_4xf64 (jbm_log2_4xf64, log2l, x64, y64, r, n, DBL_MIN, DBL_MAX,
                    nthreads, "jbm_log2_4xf64");
  efficiency_4xf64 (jbm_log_4xf64, logl, x64, y64, r, n, DBL_MIN, DBL_MAX,
                    nthreads, "jbm_log_4xf64");
  efficiency_4xf64 (jbm_log10_4xf64, log10l, x64, y64, r, n, DBL_MIN, DBL_MAX,
                    nthreads, "jbm_log10_4xf64");
  efficiency_4xf64 (jbm_sin_4xf64, sinl, x64, y64, r, n, -4. * M_PI, 4. * M_PI,
                    nthreads, "jbm_sin_4xf64");
  efficiency_4xf64 (jbm_cos_4xf64, cosl, x64, y64, r, n, -4. * M_PI, 4. * M_PI,
                    nthreads, "jbm_cos_4xf64");
  efficiency_4xf64 (jbm_tan_4xf64, tanl, x64, y64, r, n, -4. * M_PI, 4. * M_PI,
                    nthreads, "jbm_tan_4xf64");
  efficiency_4xf64 (jbm_atan_4xf64, atanl, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "jbm_atan_4xf64");
  efficiency_4xf64 (jbm_asin_4xf64, asinl, x64, y64, r, n, -1., 1., nthreads,
                    "jbm_asin_4xf64");
  efficiency_4xf64 (jbm_acos_4xf64, acosl, x64, y64, r, n, -1., 1., nthreads,
                    "jbm_acos_4xf64");
  efficiency_4xf64 (jbm_sinh_4xf64, sinhl, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                    JBM_DBL_MAX_E_EXP, nthreads, "jbm_sinh_4xf64");
  efficiency_4xf64 (jbm_cosh_4xf64, coshl, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                    JBM_DBL_MAX_E_EXP, nthreads, "jbm_cosh_4xf64");
  efficiency_4xf64 (jbm_tanh_4xf64, tanhl, x64, y64, r, n,
                    -DBL_MAX_EXP, DBL_MAX_EXP, nthreads, "jbm_tanh_4xf64");
  efficiency_4xf64 (jbm_erf_4xf64, erfl, x64, y64, r, n,
                    -DBL_MAX_EXP, DBL_MAX_EXP, nthreads, "jbm_erf_4xf64");
  efficiency_4xf64 (jbm_erfc_4xf64, erfcl, x64, y64, r, n,
                    -DBL_MAX_EXP, DBL_MAX_EXP, nthreads, "jbm_erfc_4xf64");

#endif

#ifdef __AVX512F__

  printf ("__m512 functions\n");
  efficiency_16xf32 (add_16xf32, add_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                     nthreads, "add_16xf32");
  efficiency_16xf32 (sub_16xf32, sub_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                     nthreads, "sub_16xf32");
  efficiency_16xf32 (mul_16xf32, mul_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                     nthreads, "mul_16xf32");
  efficiency_16xf32 (div_16xf32, div_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                     nthreads, "div_16xf32");
  efficiency_16xf32 (max_16xf32, max_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                     nthreads, "max_16xf32");
  efficiency_16xf32 (min_16xf32, min_f80, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                     nthreads, "min_16xf32");
  efficiency_16xf32 (jbm_abs_16xf32, fabsl, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                     nthreads, "jbm_abs_16xf32");
  efficiency_16xf32 (jbm_exp2_16xf32, exp2l, x32, y32, r, n, -FLT_MAX_EXP,
                     FLT_MAX_EXP, nthreads, "jbm_exp2_16xf32");
  efficiency_16xf32 (jbm_exp_16xf32, expl, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                     JBM_FLT_MAX_E_EXP, nthreads, "jbm_exp_16xf32");
  efficiency_16xf32 (jbm_exp10_16xf32, exp10l, x32, y32, r, n, -FLT_MAX_10_EXP,
                     FLT_MAX_10_EXP, nthreads, "jbm_exp10_16xf32");
  efficiency_16xf32 (jbm_expm1_16xf32, expm1l, x32, y32, r, n,
                     -JBM_FLT_MAX_E_EXP, JBM_FLT_MAX_E_EXP, nthreads,
                     "jbm_expm1_16xf32");
  efficiency_16xf32 (jbm_cbrt_16xf32, cbrtl, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                     nthreads, "jbm_cbrt_16xf32");
  efficiency_16xf32 (jbm_log2_16xf32, log2l, x32, y32, r, n, FLT_MIN, FLT_MAX,
                     nthreads, "jbm_log2_16xf32");
  efficiency_16xf32 (jbm_log_16xf32, logl, x32, y32, r, n, FLT_MIN, FLT_MAX,
                     nthreads, "jbm_log_16xf32");
  efficiency_16xf32 (jbm_log10_16xf32, log10l, x32, y32, r, n, FLT_MIN, FLT_MAX,
                     nthreads, "jbm_log10_16xf32");
  efficiency_16xf32 (jbm_sin_16xf32, sinl, x32, y32, r, n, -4.f * M_PIf,
                     4.f * M_PIf, nthreads, "jbm_sin_16xf32");
  efficiency_16xf32 (jbm_cos_16xf32, cosl, x32, y32, r, n, -4.f * M_PIf,
                     4.f * M_PIf, nthreads, "jbm_cos_16xf32");
  efficiency_16xf32 (jbm_tan_16xf32, tanl, x32, y32, r, n, -4.f * M_PIf,
                     4.f * M_PIf, nthreads, "jbm_tan_16xf32");
  efficiency_16xf32 (jbm_atan_16xf32, atanl, x32, y32, r, n, -FLT_MAX, FLT_MAX,
                     nthreads, "jbm_atan_16xf32");
  efficiency_16xf32 (jbm_asin_16xf32, asinl, x32, y32, r, n, -1.f, 1.f,
                     nthreads, "jbm_asin_16xf32");
  efficiency_16xf32 (jbm_acos_16xf32, acosl, x32, y32, r, n, -1.f, 1.f,
                     nthreads, "jbm_acos_16xf32");
  efficiency_16xf32 (jbm_sinh_16xf32, sinhl, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                     JBM_FLT_MAX_E_EXP, nthreads, "jbm_sinh_16xf32");
  efficiency_16xf32 (jbm_cosh_16xf32, coshl, x32, y32, r, n, -JBM_FLT_MAX_E_EXP,
                     JBM_FLT_MAX_E_EXP, nthreads, "jbm_cosh_16xf32");
  efficiency_16xf32 (jbm_tanh_16xf32, tanhl, x32, y32, r, n, -FLT_MAX_EXP,
                     FLT_MAX_EXP, nthreads, "jbm_tanh_16xf32");
  efficiency_16xf32 (jbm_erf_16xf32, erfl, x32, y32, r, n, -FLT_MAX_EXP,
                     FLT_MAX_EXP, nthreads, "jbm_erf_16xf32");
  efficiency_16xf32 (jbm_erfc_16xf32, erfcl, x32, y32, r, n, -FLT_MAX_EXP,
                     FLT_MAX_EXP, nthreads, "jbm_erfc_16xf32");

  printf ("__m512d functions\n");
  efficiency_8xf64 (add_8xf64, add_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "add_8xf64");
  efficiency_8xf64 (sub_8xf64, sub_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "sub_8xf64");
  efficiency_8xf64 (mul_8xf64, mul_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "mul_8xf64");
  efficiency_8xf64 (div_8xf64, div_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "div_8xf64");
  efficiency_8xf64 (max_8xf64, max_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "max_8xf64");
  efficiency_8xf64 (min_8xf64, min_f80, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "min_8xf64");
  efficiency_8xf64 (jbm_abs_8xf64, fabsl, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "jbm_abs_8xf64");
  efficiency_8xf64 (jbm_exp2_8xf64, exp2l, x64, y64, r, n,
                    -DBL_MAX_EXP, DBL_MAX_EXP, nthreads, "jbm_exp2_8xf64");
  efficiency_8xf64 (jbm_exp_8xf64, expl, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                    JBM_DBL_MAX_E_EXP, nthreads, "jbm_exp_8xf64");
  efficiency_8xf64 (jbm_exp10_8xf64, exp10l, x64, y64, r, n, -DBL_MAX_10_EXP,
                    DBL_MAX_10_EXP, nthreads, "jbm_exp10_8xf64");
  efficiency_8xf64 (jbm_expm1_8xf64, expm1l, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                    JBM_DBL_MAX_E_EXP, nthreads, "jbm_expm1_8xf64");
  efficiency_8xf64 (jbm_cbrt_8xf64, cbrtl, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "jbm_cbrt_8xf64");
  efficiency_8xf64 (jbm_log2_8xf64, log2l, x64, y64, r, n, DBL_MIN, DBL_MAX,
                    nthreads, "jbm_log2_8xf64");
  efficiency_8xf64 (jbm_log_8xf64, logl, x64, y64, r, n, DBL_MIN, DBL_MAX,
                    nthreads, "jbm_log_8xf64");
  efficiency_8xf64 (jbm_log10_8xf64, log10l, x64, y64, r, n, DBL_MIN, DBL_MAX,
                    nthreads, "jbm_log10_8xf64");
  efficiency_8xf64 (jbm_sin_8xf64, sinl, x64, y64, r, n, -4. * M_PI, 4. * M_PI,
                    nthreads, "jbm_sin_8xf64");
  efficiency_8xf64 (jbm_cos_8xf64, cosl, x64, y64, r, n, -4. * M_PI, 4. * M_PI,
                    nthreads, "jbm_cos_8xf64");
  efficiency_8xf64 (jbm_tan_8xf64, tanl, x64, y64, r, n, -4. * M_PI, 4. * M_PI,
                    nthreads, "jbm_tan_8xf64");
  efficiency_8xf64 (jbm_atan_8xf64, atanl, x64, y64, r, n, -DBL_MAX, DBL_MAX,
                    nthreads, "jbm_atan_8xf64");
  efficiency_8xf64 (jbm_asin_8xf64, asinl, x64, y64, r, n, -1., 1., nthreads,
                    "jbm_asin_8xf64");
  efficiency_8xf64 (jbm_acos_8xf64, acosl, x64, y64, r, n, -1., 1., nthreads,
                    "jbm_acos_8xf64");
  efficiency_8xf64 (jbm_sinh_8xf64, sinhl, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                    JBM_DBL_MAX_E_EXP, nthreads, "jbm_sinh_8xf64");
  efficiency_8xf64 (jbm_cosh_8xf64, coshl, x64, y64, r, n, -JBM_DBL_MAX_E_EXP,
                    JBM_DBL_MAX_E_EXP, nthreads, "jbm_cosh_8xf64");
  efficiency_8xf64 (jbm_tanh_8xf64, tanhl, x64, y64, r, n,
                    -DBL_MAX_EXP, DBL_MAX_EXP, nthreads, "jbm_tanh_8xf64");
  efficiency_8xf64 (jbm_erf_8xf64, erfl, x64, y64, r, n,
                    -DBL_MAX_EXP, DBL_MAX_EXP, nthreads, "jbm_erf_8xf64");
  efficiency_8xf64 (jbm_erfc_8xf64, erfcl, x64, y64, r, n,
                    -DBL_MAX_EXP, DBL_MAX_EXP, nthreads, "jbm_erfc_8xf64");

#endif

  // free memory
  JB_FREE (y64);
  JB_FREE (x64);
  JB_FREE (y32);
  JB_FREE (x32);
  free (r);

  return 0;
}
