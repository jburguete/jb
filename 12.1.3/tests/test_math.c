#include "../src/math.h"

#define MAX_ITERATIONS 1024

typedef struct
{
  JBFLOAT A, B, C, D, E, F, G, H;
} MatrixFloat;

typedef struct
{
  JBDOUBLE A, B, C, D, E, F, G, H;
} MatrixDouble;

#ifdef __ARM_NEON

float32x4_t
set_float32x4_t (const float x3, const float x2, const float x1, const float x0)
{
  return (float32x4_t)
  {
  x0, x1, x2, x3};
}

float64x2_t
set_float64x2_t (const double x1, const double x0)
{
  return (float64x2_t)
  {
  x0, x1};
}

#endif

#ifdef __riscv_vector

vfloat32m1_t
set_float32x4_t (const float x0, const float x1, const float x2, const float x3)
{
  float x[4] = { x0, x1, x2, x3 };
  return __riscv_vle32_v_f32m1 (x, 4);
}

vfloat64m1_t
set_float64x2_t (const double x0, const double x1)
{
  double x[2] = { x0, x1 };
  return __riscv_vle64_v_f64m1 (x, 2);
}

vfloat32m1_t
set_float32x8_t (const float x0, const float x1, const float x2, const float x3,
                 const float x4, const float x5, const float x6, const float x7)
{
  float x[8] = { x0, x1, x2, x3, x4, x5, x6, x7 };
  return __riscv_vle32_v_f32m1 (x, 8);
}

vfloat64m1_t
set_float64x4_t (const double x0, const double x1, const double x2,
                 const double x3)
{
  double x[4] = { x0, x1, x2, x3 };
  return __riscv_vle64_v_f64m1 (x, 4);
}

#endif

const JBFLOAT pf[15] = { (JBFLOAT) 1., (JBFLOAT) 2., (JBFLOAT) 4., (JBFLOAT) 8.,
  (JBFLOAT) 16., (JBFLOAT) 32., (JBFLOAT) 64., (JBFLOAT) 128., (JBFLOAT) 256.,
  (JBFLOAT) 512., (JBFLOAT) 1024., (JBFLOAT) 2048., (JBFLOAT) 4096.,
  (JBFLOAT) 8192., (JBFLOAT) 16384.
};

JBFLOAT mxf[] = {
  (JBFLOAT) 1., (JBFLOAT) 3., (JBFLOAT) 2., (JBFLOAT) 1., (JBFLOAT) 18.,
  (JBFLOAT) 2., (JBFLOAT) 4., (JBFLOAT) 8., (JBFLOAT) 0., (JBFLOAT) 18.,
  (JBFLOAT) 3., (JBFLOAT) - 1., (JBFLOAT) 4., (JBFLOAT) 2., (JBFLOAT) 4.,
  (JBFLOAT) 4., (JBFLOAT) 0., (JBFLOAT) 3., (JBFLOAT) 1., (JBFLOAT) 11.
};
const JBFLOAT myf[] = { 3., (JBFLOAT) 5., (JBFLOAT) - 1., (JBFLOAT) 2. };
JBFLOAT Cf[] = { (JBFLOAT) 1., (JBFLOAT) - 1., (JBFLOAT) - 1. }, Df[] =
  { (JBFLOAT) 2., (JBFLOAT) 2., (JBFLOAT) 2., (JBFLOAT) 1. }, Ef[] =
  { (JBFLOAT) 1., (JBFLOAT) 1., (JBFLOAT) - 1. }, Hf[] =
  { (JBFLOAT) 5., (JBFLOAT) 9., (JBFLOAT) - 7., (JBFLOAT) 6. }, Czf[] =
  { (JBFLOAT) 1., (JBFLOAT) - 1., (JBFLOAT) 0., (JBFLOAT) 1. }, Dzf[] =
  { (JBFLOAT) 2., (JBFLOAT) 2., (JBFLOAT) 0., (JBFLOAT) 2., (JBFLOAT) 1. },
  Ezf[] = { (JBFLOAT) 1., (JBFLOAT) 0., (JBFLOAT) 1., (JBFLOAT) - 1. }, Hzf[] =
  { (JBFLOAT) 5., (JBFLOAT) 7., (JBFLOAT) - 1., (JBFLOAT) - 4., (JBFLOAT) 6. },
  Cpf[] = { (JBFLOAT) 1., (JBFLOAT) - 1., (JBFLOAT) - 1. }, Dpf[] =
  { (JBFLOAT) 2., (JBFLOAT) 2., (JBFLOAT) 2., (JBFLOAT) 1. }, Epf[] =
  { (JBFLOAT) 1., (JBFLOAT) 1., (JBFLOAT) - 1. }, Bpf[] =
  { (JBFLOAT) 1., (JBFLOAT) - 1. }, Fpf[] =
  { (JBFLOAT) - 1., (JBFLOAT) 1. }, Hpf[] =
  { (JBFLOAT) 3., (JBFLOAT) 17., (JBFLOAT) - 6., (JBFLOAT) 3. }, Cpzf[] =
  { (JBFLOAT) 1., (JBFLOAT) - 1., (JBFLOAT) 0., (JBFLOAT) - 1. }, Dpzf[] =
  { (JBFLOAT) 2., (JBFLOAT) 2., (JBFLOAT) 0., (JBFLOAT) 2., (JBFLOAT) 1. },
  Epzf[] =
  { (JBFLOAT) 1., (JBFLOAT) 0., (JBFLOAT) 1., (JBFLOAT) - 1. }, Bpzf[] =
  { (JBFLOAT) 1., (JBFLOAT) - 1., (JBFLOAT) 0. }, Fpzf[] =
  { (JBFLOAT) 0., (JBFLOAT) - 1., (JBFLOAT) 1. }, Hpzf[] =
  { (JBFLOAT) 5., (JBFLOAT) 5., (JBFLOAT) 8., (JBFLOAT) - 7., (JBFLOAT) 6. };
const JBFLOAT rmlfx[] = {
  (JBFLOAT) 0., (JBFLOAT) 0., (JBFLOAT) 0., (JBFLOAT) 0., (JBFLOAT) 0.,
  (JBFLOAT) 0., (JBFLOAT) 1., (JBFLOAT) 1., (JBFLOAT) 1., (JBFLOAT) 1.,
  (JBFLOAT) 1., (JBFLOAT) 1.,
  (JBFLOAT) 2., (JBFLOAT) 2., (JBFLOAT) 2., (JBFLOAT) 2., (JBFLOAT) 2.,
  (JBFLOAT) 2., (JBFLOAT) 3., (JBFLOAT) 3., (JBFLOAT) 3., (JBFLOAT) 3.,
  (JBFLOAT) 3., (JBFLOAT) 3.,
  (JBFLOAT) 4., (JBFLOAT) 4., (JBFLOAT) 4., (JBFLOAT) 4., (JBFLOAT) 4.,
  (JBFLOAT) 4., (JBFLOAT) 5., (JBFLOAT) 5., (JBFLOAT) 5., (JBFLOAT) 5.,
  (JBFLOAT) 5., (JBFLOAT) 5.
};

const JBFLOAT rmlfy[] = {
  (JBFLOAT) 0., (JBFLOAT) 1., (JBFLOAT) 2., (JBFLOAT) 3., (JBFLOAT) 4.,
  (JBFLOAT) 5., (JBFLOAT) 0., (JBFLOAT) 1., (JBFLOAT) 2., (JBFLOAT) 3.,
  (JBFLOAT) 4., (JBFLOAT) 5.,
  (JBFLOAT) 0., (JBFLOAT) 1., (JBFLOAT) 2., (JBFLOAT) 3., (JBFLOAT) 4.,
  (JBFLOAT) 5., (JBFLOAT) 0., (JBFLOAT) 1., (JBFLOAT) 2., (JBFLOAT) 3.,
  (JBFLOAT) 4., (JBFLOAT) 5.,
  (JBFLOAT) 0., (JBFLOAT) 1., (JBFLOAT) 2., (JBFLOAT) 3., (JBFLOAT) 4.,
  (JBFLOAT) 5., (JBFLOAT) 0., (JBFLOAT) 1., (JBFLOAT) 2., (JBFLOAT) 3.,
  (JBFLOAT) 4., (JBFLOAT) 5.
};

const JBFLOAT rmlff1[] = {
  (JBFLOAT) 0., (JBFLOAT) 1., (JBFLOAT) 2., (JBFLOAT) 3., (JBFLOAT) 4.,
  (JBFLOAT) 5., (JBFLOAT) 1., (JBFLOAT) 2., (JBFLOAT) 3., (JBFLOAT) 4.,
  (JBFLOAT) 5., (JBFLOAT) 6.,
  (JBFLOAT) 2., (JBFLOAT) 3., (JBFLOAT) 4., (JBFLOAT) 5., (JBFLOAT) 6.,
  (JBFLOAT) 7., (JBFLOAT) 3., (JBFLOAT) 4., (JBFLOAT) 5., (JBFLOAT) 6.,
  (JBFLOAT) 7., (JBFLOAT) 8.,
  (JBFLOAT) 4., (JBFLOAT) 5., (JBFLOAT) 6., (JBFLOAT) 7., (JBFLOAT) 8.,
  (JBFLOAT) 9., (JBFLOAT) 5., (JBFLOAT) 6., (JBFLOAT) 7., (JBFLOAT) 8.,
  (JBFLOAT) 9., (JBFLOAT) 10.
};

const JBFLOAT rmlff2[] = {
  (JBFLOAT) 10., (JBFLOAT) 12., (JBFLOAT) 14., (JBFLOAT) 16., (JBFLOAT) 18.,
  (JBFLOAT) 20., (JBFLOAT) 9., (JBFLOAT) 11., (JBFLOAT) 13., (JBFLOAT) 15.,
  (JBFLOAT) 17., (JBFLOAT) 19.,
  (JBFLOAT) 8., (JBFLOAT) 10., (JBFLOAT) 12., (JBFLOAT) 14., (JBFLOAT) 16.,
  (JBFLOAT) 18., (JBFLOAT) 7., (JBFLOAT) 9., (JBFLOAT) 11., (JBFLOAT) 13.,
  (JBFLOAT) 15., (JBFLOAT) 17.,
  (JBFLOAT) 6., (JBFLOAT) 8., (JBFLOAT) 10., (JBFLOAT) 12., (JBFLOAT) 14.,
  (JBFLOAT) 16., (JBFLOAT) 5., (JBFLOAT) 7., (JBFLOAT) 9., (JBFLOAT) 11.,
  (JBFLOAT) 13., (JBFLOAT) 15.
};

JBFLOAT rmefx[] = {
  (JBFLOAT) 1., (JBFLOAT) 1., (JBFLOAT) 1., (JBFLOAT) 1., (JBFLOAT) 1.,
  (JBFLOAT) 2., (JBFLOAT) 2., (JBFLOAT) 2., (JBFLOAT) 2., (JBFLOAT) 2.,
  (JBFLOAT) 3., (JBFLOAT) 3., (JBFLOAT) 3., (JBFLOAT) 3., (JBFLOAT) 3.,
  (JBFLOAT) 4., (JBFLOAT) 4., (JBFLOAT) 4., (JBFLOAT) 4., (JBFLOAT) 4.,
  (JBFLOAT) 5., (JBFLOAT) 5., (JBFLOAT) 5., (JBFLOAT) 5., (JBFLOAT) 5.
};

JBFLOAT rmefy[] = {
  (JBFLOAT) 1., (JBFLOAT) 2., (JBFLOAT) 3., (JBFLOAT) 4., (JBFLOAT) 5.,
  (JBFLOAT) 1., (JBFLOAT) 2., (JBFLOAT) 3., (JBFLOAT) 4., (JBFLOAT) 5.,
  (JBFLOAT) 1., (JBFLOAT) 2., (JBFLOAT) 3., (JBFLOAT) 4., (JBFLOAT) 5.,
  (JBFLOAT) 1., (JBFLOAT) 2., (JBFLOAT) 3., (JBFLOAT) 4., (JBFLOAT) 5.,
  (JBFLOAT) 1., (JBFLOAT) 2., (JBFLOAT) 3., (JBFLOAT) 4., (JBFLOAT) 5.
};

JBFLOAT rmeff1[] = {
  (JBFLOAT) 60., (JBFLOAT) 30., (JBFLOAT) 20., (JBFLOAT) 15., (JBFLOAT) 12.,
  (JBFLOAT) 120., (JBFLOAT) 60., (JBFLOAT) 40., (JBFLOAT) 30., (JBFLOAT) 24.,
  (JBFLOAT) 180., (JBFLOAT) 90., (JBFLOAT) 60., (JBFLOAT) 45., (JBFLOAT) 36.,
  (JBFLOAT) 240., (JBFLOAT) 120., (JBFLOAT) 80., (JBFLOAT) 60., (JBFLOAT) 48.,
  (JBFLOAT) 300., (JBFLOAT) 150., (JBFLOAT) 100., (JBFLOAT) 75., (JBFLOAT) 60.
};

const JBDOUBLE pd[15] = { (JBDOUBLE) 1., (JBDOUBLE) 2., (JBDOUBLE) 4.,
  (JBDOUBLE) 8., (JBDOUBLE) 16., (JBDOUBLE) 32., (JBDOUBLE) 64.,
  (JBDOUBLE) 128., (JBDOUBLE) 256., (JBDOUBLE) 512., (JBDOUBLE) 1024.,
  (JBDOUBLE) 2048., (JBDOUBLE) 4096., (JBDOUBLE) 8192., (JBDOUBLE) 16384.
};

JBDOUBLE mxd[] = {
  (JBDOUBLE) 1., (JBDOUBLE) 3., (JBDOUBLE) 2., (JBDOUBLE) 1., (JBDOUBLE) 18.,
  (JBDOUBLE) 2., (JBDOUBLE) 4., (JBDOUBLE) 8., (JBDOUBLE) 0., (JBDOUBLE) 18.,
  (JBDOUBLE) 3., (JBDOUBLE) - 1., (JBDOUBLE) 4., (JBDOUBLE) 2., (JBDOUBLE) 4.,
  (JBDOUBLE) 4., (JBDOUBLE) 0., (JBDOUBLE) 3., (JBDOUBLE) 1., (JBDOUBLE) 11.
};
const JBDOUBLE myd[] = { 3., (JBDOUBLE) 5., (JBDOUBLE) - 1., (JBDOUBLE) 2. };
JBDOUBLE Cd[] = { (JBDOUBLE) 1., (JBDOUBLE) - 1., (JBDOUBLE) - 1. }, Dd[] =
  { (JBDOUBLE) 2., (JBDOUBLE) 2., (JBDOUBLE) 2., (JBDOUBLE) 1. }, Ed[] =
  { (JBDOUBLE) 1., (JBDOUBLE) 1., (JBDOUBLE) - 1. }, Hd[] =
  { (JBDOUBLE) 5., (JBDOUBLE) 9., (JBDOUBLE) - 7., (JBDOUBLE) 6. }, Czd[] =
  { (JBDOUBLE) 1., (JBDOUBLE) - 1., (JBDOUBLE) 0., (JBDOUBLE) 1. }, Dzd[] =
  { (JBDOUBLE) 2., (JBDOUBLE) 2., (JBDOUBLE) 0., (JBDOUBLE) 2., (JBDOUBLE) 1. },
  Ezd[] =
  { (JBDOUBLE) 1., (JBDOUBLE) 0., (JBDOUBLE) 1., (JBDOUBLE) - 1. }, Hzd[] =
  { (JBDOUBLE) 5., (JBDOUBLE) 7., (JBDOUBLE) - 1., (JBDOUBLE) - 4.,
  (JBDOUBLE) 6.
}, Cpd[] = { (JBDOUBLE) 1., (JBDOUBLE) - 1., (JBDOUBLE) - 1. }, Dpd[] =
  { (JBDOUBLE) 2., (JBDOUBLE) 2., (JBDOUBLE) 2., (JBDOUBLE) 1. }, Epd[] =
  { (JBDOUBLE) 1., (JBDOUBLE) 1., (JBDOUBLE) - 1. }, Bpd[] =
  { (JBDOUBLE) 1., (JBDOUBLE) - 1. }, Fpd[] =
  { (JBDOUBLE) - 1., (JBDOUBLE) 1. }, Hpd[] =
  { (JBDOUBLE) 3., (JBDOUBLE) 17., (JBDOUBLE) - 6., (JBDOUBLE) 3. }, Cpzd[] =
  { (JBDOUBLE) 1., (JBDOUBLE) - 1., (JBDOUBLE) 0., (JBDOUBLE) - 1. }, Dpzd[] =
  { (JBDOUBLE) 2., (JBDOUBLE) 2., (JBDOUBLE) 0., (JBDOUBLE) 2., (JBDOUBLE) 1. },
  Epzd[] =
  { (JBDOUBLE) 1., (JBDOUBLE) 0., (JBDOUBLE) 1., (JBDOUBLE) - 1. }, Bpzd[] =
  { (JBDOUBLE) 1., (JBDOUBLE) - 1., (JBDOUBLE) 0. }, Fpzd[] =
  { (JBDOUBLE) 0., (JBDOUBLE) - 1., (JBDOUBLE) 1. }, Hpzd[] =
  { 5., (JBDOUBLE) 5., (JBDOUBLE) 8., (JBDOUBLE) - 7., (JBDOUBLE) 6. };
const JBDOUBLE rmldx[] = {
  (JBDOUBLE) 0., (JBDOUBLE) 0., (JBDOUBLE) 0., (JBDOUBLE) 0., (JBDOUBLE) 0.,
  (JBDOUBLE) 0., (JBDOUBLE) 1., (JBDOUBLE) 1., (JBDOUBLE) 1., (JBDOUBLE) 1.,
  (JBDOUBLE) 1., (JBDOUBLE) 1.,
  (JBDOUBLE) 2., (JBDOUBLE) 2., (JBDOUBLE) 2., (JBDOUBLE) 2., (JBDOUBLE) 2.,
  (JBDOUBLE) 2., (JBDOUBLE) 3., (JBDOUBLE) 3., (JBDOUBLE) 3., (JBDOUBLE) 3.,
  (JBDOUBLE) 3., (JBDOUBLE) 3.,
  (JBDOUBLE) 4., (JBDOUBLE) 4., (JBDOUBLE) 4., (JBDOUBLE) 4., (JBDOUBLE) 4.,
  (JBDOUBLE) 4., (JBDOUBLE) 5., (JBDOUBLE) 5., (JBDOUBLE) 5., (JBDOUBLE) 5.,
  (JBDOUBLE) 5., (JBDOUBLE) 5.
};

const JBDOUBLE rmldy[] = {
  (JBDOUBLE) 0., (JBDOUBLE) 1., (JBDOUBLE) 2., (JBDOUBLE) 3., (JBDOUBLE) 4.,
  (JBDOUBLE) 5., (JBDOUBLE) 0., (JBDOUBLE) 1., (JBDOUBLE) 2., (JBDOUBLE) 3.,
  (JBDOUBLE) 4., (JBDOUBLE) 5.,
  (JBDOUBLE) 0., (JBDOUBLE) 1., (JBDOUBLE) 2., (JBDOUBLE) 3., (JBDOUBLE) 4.,
  (JBDOUBLE) 5., (JBDOUBLE) 0., (JBDOUBLE) 1., (JBDOUBLE) 2., (JBDOUBLE) 3.,
  (JBDOUBLE) 4., (JBDOUBLE) 5.,
  (JBDOUBLE) 0., (JBDOUBLE) 1., (JBDOUBLE) 2., (JBDOUBLE) 3., (JBDOUBLE) 4.,
  (JBDOUBLE) 5., (JBDOUBLE) 0., (JBDOUBLE) 1., (JBDOUBLE) 2., (JBDOUBLE) 3.,
  (JBDOUBLE) 4., (JBDOUBLE) 5.
};

const JBDOUBLE rmldf1[] = {
  (JBDOUBLE) 0., (JBDOUBLE) 1., (JBDOUBLE) 2., (JBDOUBLE) 3., (JBDOUBLE) 4.,
  (JBDOUBLE) 5., (JBDOUBLE) 1., (JBDOUBLE) 2., (JBDOUBLE) 3., (JBDOUBLE) 4.,
  (JBDOUBLE) 5., (JBDOUBLE) 6.,
  (JBDOUBLE) 2., (JBDOUBLE) 3., (JBDOUBLE) 4., (JBDOUBLE) 5., (JBDOUBLE) 6.,
  (JBDOUBLE) 7., (JBDOUBLE) 3., (JBDOUBLE) 4., (JBDOUBLE) 5., (JBDOUBLE) 6.,
  (JBDOUBLE) 7., (JBDOUBLE) 8.,
  (JBDOUBLE) 4., (JBDOUBLE) 5., (JBDOUBLE) 6., (JBDOUBLE) 7., (JBDOUBLE) 8.,
  (JBDOUBLE) 9., (JBDOUBLE) 5., (JBDOUBLE) 6., (JBDOUBLE) 7., (JBDOUBLE) 8.,
  (JBDOUBLE) 9., (JBDOUBLE) 10.
};

const JBDOUBLE rmldf2[] = {
  (JBDOUBLE) 10., (JBDOUBLE) 12., (JBDOUBLE) 14., (JBDOUBLE) 16.,
  (JBDOUBLE) 18., (JBDOUBLE) 20., (JBDOUBLE) 9., (JBDOUBLE) 11.,
  (JBDOUBLE) 13., (JBDOUBLE) 15., (JBDOUBLE) 17., (JBDOUBLE) 19.,
  (JBDOUBLE) 8., (JBDOUBLE) 10., (JBDOUBLE) 12., (JBDOUBLE) 14., (JBDOUBLE) 16.,
  (JBDOUBLE) 18., (JBDOUBLE) 7., (JBDOUBLE) 9., (JBDOUBLE) 11.,
  (JBDOUBLE) 13., (JBDOUBLE) 15., (JBDOUBLE) 17.,
  (JBDOUBLE) 6., (JBDOUBLE) 8., (JBDOUBLE) 10., (JBDOUBLE) 12., (JBDOUBLE) 14.,
  (JBDOUBLE) 16., (JBDOUBLE) 5., (JBDOUBLE) 7., (JBDOUBLE) 9., (JBDOUBLE) 11.,
  (JBDOUBLE) 13., (JBDOUBLE) 15.
};

JBDOUBLE rmedx[] = {
  (JBDOUBLE) 1., (JBDOUBLE) 1., (JBDOUBLE) 1., (JBDOUBLE) 1., (JBDOUBLE) 1.,
  (JBDOUBLE) 2., (JBDOUBLE) 2., (JBDOUBLE) 2., (JBDOUBLE) 2., (JBDOUBLE) 2.,
  (JBDOUBLE) 3., (JBDOUBLE) 3., (JBDOUBLE) 3., (JBDOUBLE) 3., (JBDOUBLE) 3.,
  (JBDOUBLE) 4., (JBDOUBLE) 4., (JBDOUBLE) 4., (JBDOUBLE) 4., (JBDOUBLE) 4.,
  (JBDOUBLE) 5., (JBDOUBLE) 5., (JBDOUBLE) 5., (JBDOUBLE) 5., (JBDOUBLE) 5.
};

JBDOUBLE rmedy[] = {
  (JBDOUBLE) 1., (JBDOUBLE) 2., (JBDOUBLE) 3., (JBDOUBLE) 4., (JBDOUBLE) 5.,
  (JBDOUBLE) 1., (JBDOUBLE) 2., (JBDOUBLE) 3., (JBDOUBLE) 4., (JBDOUBLE) 5.,
  (JBDOUBLE) 1., (JBDOUBLE) 2., (JBDOUBLE) 3., (JBDOUBLE) 4., (JBDOUBLE) 5.,
  (JBDOUBLE) 1., (JBDOUBLE) 2., (JBDOUBLE) 3., (JBDOUBLE) 4., (JBDOUBLE) 5.,
  (JBDOUBLE) 1., (JBDOUBLE) 2., (JBDOUBLE) 3., (JBDOUBLE) 4., (JBDOUBLE) 5.
};

JBDOUBLE rmedf1[] = {
  (JBDOUBLE) 60., (JBDOUBLE) 30., (JBDOUBLE) 20., (JBDOUBLE) 15.,
  (JBDOUBLE) 12., (JBDOUBLE) 120., (JBDOUBLE) 60., (JBDOUBLE) 40.,
  (JBDOUBLE) 30., (JBDOUBLE) 24.,
  (JBDOUBLE) 180., (JBDOUBLE) 90., (JBDOUBLE) 60., (JBDOUBLE) 45.,
  (JBDOUBLE) 36., (JBDOUBLE) 240., (JBDOUBLE) 120., (JBDOUBLE) 80.,
  (JBDOUBLE) 60., (JBDOUBLE) 48.,
  (JBDOUBLE) 300., (JBDOUBLE) 150., (JBDOUBLE) 100., (JBDOUBLE) 75.,
  (JBDOUBLE) 60.
};

const double p_1[12] = { 1., 2., 4., 8., 16., 32., 64., 128., 256.,
  512., 1024., 2048.
};
const JBFLOAT *rmlf1[] = { rmlff1, rmlfx, rmlfy };
const JBFLOAT *rmlf2[] = { rmlff2, rmlfx, rmlfy };
const JBFLOAT *rmef1[] = { rmeff1, rmefx, rmefy };
const JBDOUBLE *rmld1[] = { rmldf1, rmldx, rmldy };
const JBDOUBLE *rmld2[] = { rmldf2, rmldx, rmldy };
const JBDOUBLE *rmed1[] = { rmedf1, rmedx, rmedy };

void
print_float (const JBFLOAT x, const char *label)
{
  char buffer[JB_BUFFER_SIZE];
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, x);
  printf ("%s=%s ", label, buffer);
}

void
print_double (const JBDOUBLE x, const char *label)
{
  char buffer[JB_BUFFER_SIZE];
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWL, x);
  printf ("%s=%s ", label, buffer);
}

JBFLOAT
fn0f (const JBFLOAT x __attribute__((unused)))
{
  return (JBFLOAT) 1.;
}

JBFLOAT
fn1f (const JBFLOAT x)
{
  return x;
}

JBFLOAT
fn2f (const JBFLOAT x)
{
  return x * fn1f (x);
}

JBFLOAT
fn3f (const JBFLOAT x)
{
  return x * fn2f (x);
}

JBFLOAT
fn4f (const JBFLOAT x)
{
  return x * fn3f (x);
}

JBFLOAT
fn5f (const JBFLOAT x)
{
  return x * fn4f (x);
}

JBFLOAT
fn6f (const JBFLOAT x)
{
  return x * fn5f (x);
}

JBFLOAT
fn7f (const JBFLOAT x)
{
  return x * fn6f (x);
}

JBFLOAT
fn8f (const JBFLOAT x)
{
  return x * fn7f (x);
}

JBFLOAT
fn9f (const JBFLOAT x)
{
  return x * fn8f (x);
}

JBFLOAT
fn10f (const JBFLOAT x)
{
  return x * fn9f (x);
}

JBFLOAT
fn11f (const JBFLOAT x)
{
  return x * fn10f (x);
}

JBFLOAT
fn12f (const JBFLOAT x)
{
  return x * fn11f (x);
}

JBFLOAT
fn13f (const JBFLOAT x)
{
  return x * fn12f (x);
}

JBFLOAT
fn14f (const JBFLOAT x)
{
  return x * fn13f (x);
}

JBDOUBLE
fn0d (const JBDOUBLE x __attribute__((unused)))
{
  return (JBFLOAT) 1.;
}

JBDOUBLE
fn1d (const JBDOUBLE x)
{
  return x;
}

JBDOUBLE
fn2d (const JBDOUBLE x)
{
  return x * fn1d (x);
}

JBDOUBLE
fn3d (const JBDOUBLE x)
{
  return x * fn2d (x);
}

JBDOUBLE
fn4d (const JBDOUBLE x)
{
  return x * fn3d (x);
}

JBDOUBLE
fn5d (const JBDOUBLE x)
{
  return x * fn4d (x);
}

JBDOUBLE
fn6d (const JBDOUBLE x)
{
  return x * fn5d (x);
}

JBDOUBLE
fn7d (const JBDOUBLE x)
{
  return x * fn6d (x);
}

JBDOUBLE
fn8d (const JBDOUBLE x)
{
  return x * fn7d (x);
}

JBDOUBLE
fn9d (const JBDOUBLE x)
{
  return x * fn8d (x);
}

JBDOUBLE
fn10d (const JBDOUBLE x)
{
  return x * fn9d (x);
}

JBDOUBLE
fn11d (const JBDOUBLE x)
{
  return x * fn10d (x);
}

JBDOUBLE
fn12d (const JBDOUBLE x)
{
  return x * fn11d (x);
}

JBDOUBLE
fn13d (const JBDOUBLE x)
{
  return x * fn12d (x);
}

JBDOUBLE
fn14d (const JBDOUBLE x)
{
  return x * fn13d (x);
}

#ifdef __SSE4_2__

__m128
fn0_4xf32 (const __m128 x __attribute__((unused)))
{
  return _mm_set1_ps (1.f);
}

__m128
fn1_4xf32 (const __m128 x)
{
  return x;
}

__m128
fn2_4xf32 (const __m128 x)
{
  return _mm_mul_ps (x, fn1_4xf32 (x));
}

__m128
fn3_4xf32 (const __m128 x)
{
  return _mm_mul_ps (x, fn2_4xf32 (x));
}

__m128
fn4_4xf32 (const __m128 x)
{
  return _mm_mul_ps (x, fn3_4xf32 (x));
}

__m128
fn5_4xf32 (const __m128 x)
{
  return _mm_mul_ps (x, fn4_4xf32 (x));
}

__m128
fn6_4xf32 (const __m128 x)
{
  return _mm_mul_ps (x, fn5_4xf32 (x));
}

__m128
fn7_4xf32 (const __m128 x)
{
  return _mm_mul_ps (x, fn6_4xf32 (x));
}

__m128
fn8_4xf32 (const __m128 x)
{
  return _mm_mul_ps (x, fn7_4xf32 (x));
}

__m128
fn9_4xf32 (const __m128 x)
{
  return _mm_mul_ps (x, fn8_4xf32 (x));
}

__m128
fn10_4xf32 (const __m128 x)
{
  return _mm_mul_ps (x, fn9_4xf32 (x));
}

__m128
fn11_4xf32 (const __m128 x)
{
  return _mm_mul_ps (x, fn10_4xf32 (x));
}

__m128
fn12_4xf32 (const __m128 x)
{
  return _mm_mul_ps (x, fn11_4xf32 (x));
}

__m128
fn13_4xf32 (const __m128 x)
{
  return _mm_mul_ps (x, fn12_4xf32 (x));
}

__m128
fn14_4xf32 (const __m128 x)
{
  return _mm_mul_ps (x, fn13_4xf32 (x));
}

#endif

#ifdef __AVX__

__m256
fn0_8xf32 (const __m256 x __attribute__((unused)))
{
  return _mm256_set1_ps (1.f);
}

__m256
fn1_8xf32 (const __m256 x)
{
  return x;
}

__m256
fn2_8xf32 (const __m256 x)
{
  return _mm256_mul_ps (x, fn1_8xf32 (x));
}

__m256
fn3_8xf32 (const __m256 x)
{
  return _mm256_mul_ps (x, fn2_8xf32 (x));
}

__m256
fn4_8xf32 (const __m256 x)
{
  return _mm256_mul_ps (x, fn3_8xf32 (x));
}

__m256
fn5_8xf32 (const __m256 x)
{
  return _mm256_mul_ps (x, fn4_8xf32 (x));
}

__m256
fn6_8xf32 (const __m256 x)
{
  return _mm256_mul_ps (x, fn5_8xf32 (x));
}

__m256
fn7_8xf32 (const __m256 x)
{
  return _mm256_mul_ps (x, fn6_8xf32 (x));
}

__m256
fn8_8xf32 (const __m256 x)
{
  return _mm256_mul_ps (x, fn7_8xf32 (x));
}

__m256
fn9_8xf32 (const __m256 x)
{
  return _mm256_mul_ps (x, fn8_8xf32 (x));
}

__m256
fn10_8xf32 (const __m256 x)
{
  return _mm256_mul_ps (x, fn9_8xf32 (x));
}

__m256
fn11_8xf32 (const __m256 x)
{
  return _mm256_mul_ps (x, fn10_8xf32 (x));
}

__m256
fn12_8xf32 (const __m256 x)
{
  return _mm256_mul_ps (x, fn11_8xf32 (x));
}

__m256
fn13_8xf32 (const __m256 x)
{
  return _mm256_mul_ps (x, fn12_8xf32 (x));
}

__m256
fn14_8xf32 (const __m256 x)
{
  return _mm256_mul_ps (x, fn13_8xf32 (x));
}

#endif

#ifdef __AVX512F__

__m512
fn0_16xf32 (const __m512 x __attribute__((unused)))
{
  return _mm512_set1_ps (1.f);
}

__m512
fn1_16xf32 (const __m512 x)
{
  return x;
}

__m512
fn2_16xf32 (const __m512 x)
{
  return _mm512_mul_ps (x, fn1_16xf32 (x));
}

__m512
fn3_16xf32 (const __m512 x)
{
  return _mm512_mul_ps (x, fn2_16xf32 (x));
}

__m512
fn4_16xf32 (const __m512 x)
{
  return _mm512_mul_ps (x, fn3_16xf32 (x));
}

__m512
fn5_16xf32 (const __m512 x)
{
  return _mm512_mul_ps (x, fn4_16xf32 (x));
}

__m512
fn6_16xf32 (const __m512 x)
{
  return _mm512_mul_ps (x, fn5_16xf32 (x));
}

__m512
fn7_16xf32 (const __m512 x)
{
  return _mm512_mul_ps (x, fn6_16xf32 (x));
}

__m512
fn8_16xf32 (const __m512 x)
{
  return _mm512_mul_ps (x, fn7_16xf32 (x));
}

__m512
fn9_16xf32 (const __m512 x)
{
  return _mm512_mul_ps (x, fn8_16xf32 (x));
}

__m512
fn10_16xf32 (const __m512 x)
{
  return _mm512_mul_ps (x, fn9_16xf32 (x));
}

__m512
fn11_16xf32 (const __m512 x)
{
  return _mm512_mul_ps (x, fn10_16xf32 (x));
}

__m512
fn12_16xf32 (const __m512 x)
{
  return _mm512_mul_ps (x, fn11_16xf32 (x));
}

__m512
fn13_16xf32 (const __m512 x)
{
  return _mm512_mul_ps (x, fn12_16xf32 (x));
}

__m512
fn14_16xf32 (const __m512 x)
{
  return _mm512_mul_ps (x, fn13_16xf32 (x));
}

#endif

#ifdef __ARM_NEON

float32x4_t
fn0_4xf32 (const float32x4_t x __attribute__((unused)))
{
  return vdupq_n_f32 (1.f);
}

float32x4_t
fn1_4xf32 (const float32x4_t x)
{
  return x;
}

float32x4_t
fn2_4xf32 (const float32x4_t x)
{
  return vmulq_f32 (x, fn1_4xf32 (x));
}

float32x4_t
fn3_4xf32 (const float32x4_t x)
{
  return vmulq_f32 (x, fn2_4xf32 (x));
}

float32x4_t
fn4_4xf32 (const float32x4_t x)
{
  return vmulq_f32 (x, fn3_4xf32 (x));
}

float32x4_t
fn5_4xf32 (const float32x4_t x)
{
  return vmulq_f32 (x, fn4_4xf32 (x));
}

float32x4_t
fn6_4xf32 (const float32x4_t x)
{
  return vmulq_f32 (x, fn5_4xf32 (x));
}

float32x4_t
fn7_4xf32 (const float32x4_t x)
{
  return vmulq_f32 (x, fn6_4xf32 (x));
}

float32x4_t
fn8_4xf32 (const float32x4_t x)
{
  return vmulq_f32 (x, fn7_4xf32 (x));
}

float32x4_t
fn9_4xf32 (const float32x4_t x)
{
  return vmulq_f32 (x, fn8_4xf32 (x));
}

float32x4_t
fn10_4xf32 (const float32x4_t x)
{
  return vmulq_f32 (x, fn9_4xf32 (x));
}

float32x4_t
fn11_4xf32 (const float32x4_t x)
{
  return vmulq_f32 (x, fn10_4xf32 (x));
}

float32x4_t
fn12_4xf32 (const float32x4_t x)
{
  return vmulq_f32 (x, fn11_4xf32 (x));
}

float32x4_t
fn13_4xf32 (const float32x4_t x)
{
  return vmulq_f32 (x, fn12_4xf32 (x));
}

float32x4_t
fn14_4xf32 (const float32x4_t x)
{
  return vmulq_f32 (x, fn13_4xf32 (x));
}

#endif

#ifdef __riscv_vector

vfloat32m1_t
fn0_4xf32 (const vfloat32m1_t x __attribute__((unused)))
{
  return __riscv_vfmv_v_f_f32m1 (1.f, 4);
}

vfloat32m1_t
fn1_4xf32 (const vfloat32m1_t x)
{
  return x;
}

vfloat32m1_t
fn2_4xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn1_4xf32 (x), 4);
}

vfloat32m1_t
fn3_4xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn2_4xf32 (x), 4);
}

vfloat32m1_t
fn4_4xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn3_4xf32 (x), 4);
}

vfloat32m1_t
fn5_4xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn4_4xf32 (x), 4);
}

vfloat32m1_t
fn6_4xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn5_4xf32 (x), 4);
}

vfloat32m1_t
fn7_4xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn6_4xf32 (x), 4);
}

vfloat32m1_t
fn8_4xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn7_4xf32 (x), 4);
}

vfloat32m1_t
fn9_4xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn8_4xf32 (x), 4);
}

vfloat32m1_t
fn10_4xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn9_4xf32 (x), 4);
}

vfloat32m1_t
fn11_4xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn10_4xf32 (x), 4);
}

vfloat32m1_t
fn12_4xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn11_4xf32 (x), 4);
}

vfloat32m1_t
fn13_4xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn12_4xf32 (x), 4);
}

vfloat32m1_t
fn14_4xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn13_4xf32 (x), 4);
}

vfloat32m1_t
fn0_8xf32 (const vfloat32m1_t x __attribute__((unused)))
{
  return __riscv_vfmv_v_f_f32m1 (1.f, 8);
}

vfloat32m1_t
fn1_8xf32 (const vfloat32m1_t x)
{
  return x;
}

vfloat32m1_t
fn2_8xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn1_8xf32 (x), 8);
}

vfloat32m1_t
fn3_8xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn2_8xf32 (x), 8);
}

vfloat32m1_t
fn4_8xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn3_8xf32 (x), 8);
}

vfloat32m1_t
fn5_8xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn4_8xf32 (x), 8);
}

vfloat32m1_t
fn6_8xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn5_8xf32 (x), 8);
}

vfloat32m1_t
fn7_8xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn6_8xf32 (x), 8);
}

vfloat32m1_t
fn8_8xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn7_8xf32 (x), 8);
}

vfloat32m1_t
fn9_8xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn8_8xf32 (x), 8);
}

vfloat32m1_t
fn10_8xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn9_8xf32 (x), 8);
}

vfloat32m1_t
fn11_8xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn10_8xf32 (x), 8);
}

vfloat32m1_t
fn12_8xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn11_8xf32 (x), 8);
}

vfloat32m1_t
fn13_8xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn12_8xf32 (x), 8);
}

vfloat32m1_t
fn14_8xf32 (const vfloat32m1_t x)
{
  return __riscv_vfmul_vv_f32m1 (x, fn13_8xf32 (x), 8);
}

#endif

#ifdef __SSE4_2__

__m128d
fn0_2xf64 (const __m128d x __attribute__((unused)))
{
  return _mm_set1_pd (1.);
}

__m128d
fn1_2xf64 (const __m128d x)
{
  return x;
}

__m128d
fn2_2xf64 (const __m128d x)
{
  return _mm_mul_pd (x, fn1_2xf64 (x));
}

__m128d
fn3_2xf64 (const __m128d x)
{
  return _mm_mul_pd (x, fn2_2xf64 (x));
}

__m128d
fn4_2xf64 (const __m128d x)
{
  return _mm_mul_pd (x, fn3_2xf64 (x));
}

__m128d
fn5_2xf64 (const __m128d x)
{
  return _mm_mul_pd (x, fn4_2xf64 (x));
}

__m128d
fn6_2xf64 (const __m128d x)
{
  return _mm_mul_pd (x, fn5_2xf64 (x));
}

__m128d
fn7_2xf64 (const __m128d x)
{
  return _mm_mul_pd (x, fn6_2xf64 (x));
}

__m128d
fn8_2xf64 (const __m128d x)
{
  return _mm_mul_pd (x, fn7_2xf64 (x));
}

__m128d
fn9_2xf64 (const __m128d x)
{
  return _mm_mul_pd (x, fn8_2xf64 (x));
}

__m128d
fn10_2xf64 (const __m128d x)
{
  return _mm_mul_pd (x, fn9_2xf64 (x));
}

__m128d
fn11_2xf64 (const __m128d x)
{
  return _mm_mul_pd (x, fn10_2xf64 (x));
}

__m128d
fn12_2xf64 (const __m128d x)
{
  return _mm_mul_pd (x, fn11_2xf64 (x));
}

__m128d
fn13_2xf64 (const __m128d x)
{
  return _mm_mul_pd (x, fn12_2xf64 (x));
}

__m128d
fn14_2xf64 (const __m128d x)
{
  return _mm_mul_pd (x, fn13_2xf64 (x));
}

#endif

#ifdef __AVX__

__m256d
fn0_4xf64 (const __m256d x __attribute__((unused)))
{
  return _mm256_set1_pd (1.);
}

__m256d
fn1_4xf64 (const __m256d x)
{
  return x;
}

__m256d
fn2_4xf64 (const __m256d x)
{
  return _mm256_mul_pd (x, fn1_4xf64 (x));
}

__m256d
fn3_4xf64 (const __m256d x)
{
  return _mm256_mul_pd (x, fn2_4xf64 (x));
}

__m256d
fn4_4xf64 (const __m256d x)
{
  return _mm256_mul_pd (x, fn3_4xf64 (x));
}

__m256d
fn5_4xf64 (const __m256d x)
{
  return _mm256_mul_pd (x, fn4_4xf64 (x));
}

__m256d
fn6_4xf64 (const __m256d x)
{
  return _mm256_mul_pd (x, fn5_4xf64 (x));
}

__m256d
fn7_4xf64 (const __m256d x)
{
  return _mm256_mul_pd (x, fn6_4xf64 (x));
}

__m256d
fn8_4xf64 (const __m256d x)
{
  return _mm256_mul_pd (x, fn7_4xf64 (x));
}

__m256d
fn9_4xf64 (const __m256d x)
{
  return _mm256_mul_pd (x, fn8_4xf64 (x));
}

__m256d
fn10_4xf64 (const __m256d x)
{
  return _mm256_mul_pd (x, fn9_4xf64 (x));
}

__m256d
fn11_4xf64 (const __m256d x)
{
  return _mm256_mul_pd (x, fn10_4xf64 (x));
}

__m256d
fn12_4xf64 (const __m256d x)
{
  return _mm256_mul_pd (x, fn11_4xf64 (x));
}

__m256d
fn13_4xf64 (const __m256d x)
{
  return _mm256_mul_pd (x, fn12_4xf64 (x));
}

__m256d
fn14_4xf64 (const __m256d x)
{
  return _mm256_mul_pd (x, fn13_4xf64 (x));
}

#endif

#ifdef __AVX512F__

__m512d
fn0_8xf64 (const __m512d x __attribute__((unused)))
{
  return _mm512_set1_pd (1.);
}

__m512d
fn1_8xf64 (const __m512d x)
{
  return x;
}

__m512d
fn2_8xf64 (const __m512d x)
{
  return _mm512_mul_pd (x, fn1_8xf64 (x));
}

__m512d
fn3_8xf64 (const __m512d x)
{
  return _mm512_mul_pd (x, fn2_8xf64 (x));
}

__m512d
fn4_8xf64 (const __m512d x)
{
  return _mm512_mul_pd (x, fn3_8xf64 (x));
}

__m512d
fn5_8xf64 (const __m512d x)
{
  return _mm512_mul_pd (x, fn4_8xf64 (x));
}

__m512d
fn6_8xf64 (const __m512d x)
{
  return _mm512_mul_pd (x, fn5_8xf64 (x));
}

__m512d
fn7_8xf64 (const __m512d x)
{
  return _mm512_mul_pd (x, fn6_8xf64 (x));
}

__m512d
fn8_8xf64 (const __m512d x)
{
  return _mm512_mul_pd (x, fn7_8xf64 (x));
}

__m512d
fn9_8xf64 (const __m512d x)
{
  return _mm512_mul_pd (x, fn8_8xf64 (x));
}

__m512d
fn10_8xf64 (const __m512d x)
{
  return _mm512_mul_pd (x, fn9_8xf64 (x));
}

__m512d
fn11_8xf64 (const __m512d x)
{
  return _mm512_mul_pd (x, fn10_8xf64 (x));
}

__m512d
fn12_8xf64 (const __m512d x)
{
  return _mm512_mul_pd (x, fn11_8xf64 (x));
}

__m512d
fn13_8xf64 (const __m512d x)
{
  return _mm512_mul_pd (x, fn12_8xf64 (x));
}

__m512d
fn14_8xf64 (const __m512d x)
{
  return _mm512_mul_pd (x, fn13_8xf64 (x));
}

#endif

#ifdef __ARM_NEON

float64x2_t
fn0_2xf64 (const float64x2_t x __attribute__((unused)))
{
  return vdupq_n_f64 (1.);
}

float64x2_t
fn1_2xf64 (const float64x2_t x)
{
  return x;
}

float64x2_t
fn2_2xf64 (const float64x2_t x)
{
  return vmulq_f64 (x, fn1_2xf64 (x));
}

float64x2_t
fn3_2xf64 (const float64x2_t x)
{
  return vmulq_f64 (x, fn2_2xf64 (x));
}

float64x2_t
fn4_2xf64 (const float64x2_t x)
{
  return vmulq_f64 (x, fn3_2xf64 (x));
}

float64x2_t
fn5_2xf64 (const float64x2_t x)
{
  return vmulq_f64 (x, fn4_2xf64 (x));
}

float64x2_t
fn6_2xf64 (const float64x2_t x)
{
  return vmulq_f64 (x, fn5_2xf64 (x));
}

float64x2_t
fn7_2xf64 (const float64x2_t x)
{
  return vmulq_f64 (x, fn6_2xf64 (x));
}

float64x2_t
fn8_2xf64 (const float64x2_t x)
{
  return vmulq_f64 (x, fn7_2xf64 (x));
}

float64x2_t
fn9_2xf64 (const float64x2_t x)
{
  return vmulq_f64 (x, fn8_2xf64 (x));
}

float64x2_t
fn10_2xf64 (const float64x2_t x)
{
  return vmulq_f64 (x, fn9_2xf64 (x));
}

float64x2_t
fn11_2xf64 (const float64x2_t x)
{
  return vmulq_f64 (x, fn10_2xf64 (x));
}

float64x2_t
fn12_2xf64 (const float64x2_t x)
{
  return vmulq_f64 (x, fn11_2xf64 (x));
}

float64x2_t
fn13_2xf64 (const float64x2_t x)
{
  return vmulq_f64 (x, fn12_2xf64 (x));
}

float64x2_t
fn14_2xf64 (const float64x2_t x)
{
  return vmulq_f64 (x, fn13_2xf64 (x));
}

#endif

#ifdef __riscv_vector

vfloat64m1_t
fn0_2xf64 (const vfloat64m1_t x __attribute__((unused)))
{
  return __riscv_vfmv_v_f_f64m1 (1.f, 2);
}

vfloat64m1_t
fn1_2xf64 (const vfloat64m1_t x)
{
  return x;
}

vfloat64m1_t
fn2_2xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn1_2xf64 (x), 2);
}

vfloat64m1_t
fn3_2xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn2_2xf64 (x), 2);
}

vfloat64m1_t
fn4_2xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn3_2xf64 (x), 2);
}

vfloat64m1_t
fn5_2xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn4_2xf64 (x), 2);
}

vfloat64m1_t
fn6_2xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn5_2xf64 (x), 2);
}

vfloat64m1_t
fn7_2xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn6_2xf64 (x), 2);
}

vfloat64m1_t
fn8_2xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn7_2xf64 (x), 2);
}

vfloat64m1_t
fn9_2xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn8_2xf64 (x), 2);
}

vfloat64m1_t
fn10_2xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn9_2xf64 (x), 2);
}

vfloat64m1_t
fn11_2xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn10_2xf64 (x), 2);
}

vfloat64m1_t
fn12_2xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn11_2xf64 (x), 2);
}

vfloat64m1_t
fn13_2xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn12_2xf64 (x), 2);
}

vfloat64m1_t
fn14_2xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn13_2xf64 (x), 2);
}

vfloat64m1_t
fn0_4xf64 (const vfloat64m1_t x __attribute__((unused)))
{
  return __riscv_vfmv_v_f_f64m1 (1.f, 4);
}

vfloat64m1_t
fn1_4xf64 (const vfloat64m1_t x)
{
  return x;
}

vfloat64m1_t
fn2_4xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn1_4xf64 (x), 4);
}

vfloat64m1_t
fn3_4xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn2_4xf64 (x), 4);
}

vfloat64m1_t
fn4_4xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn3_4xf64 (x), 4);
}

vfloat64m1_t
fn5_4xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn4_4xf64 (x), 4);
}

vfloat64m1_t
fn6_4xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn5_4xf64 (x), 4);
}

vfloat64m1_t
fn7_4xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn6_4xf64 (x), 4);
}

vfloat64m1_t
fn8_4xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn7_4xf64 (x), 4);
}

vfloat64m1_t
fn9_4xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn8_4xf64 (x), 4);
}

vfloat64m1_t
fn10_4xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn9_4xf64 (x), 4);
}

vfloat64m1_t
fn11_4xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn10_4xf64 (x), 4);
}

vfloat64m1_t
fn12_4xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn11_4xf64 (x), 4);
}

vfloat64m1_t
fn13_4xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn12_4xf64 (x), 4);
}

vfloat64m1_t
fn14_4xf64 (const vfloat64m1_t x)
{
  return __riscv_vfmul_vv_f64m1 (x, fn13_4xf64 (x), 4);
}

#endif

void
matrix_print (const JBFLOAT *x, const unsigned int nr, const unsigned int nc)
{
  char buffer[JB_BUFFER_SIZE];
  unsigned int i, j;
  for (i = 0; i < nr; ++i)
    for (j = 0; j < nc; ++j)
      {
        SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, x[i * nc + j]);
        printf ("f[%u,%u]=%s\n", i, j, buffer);
      }
}

void
farray_print (const JBMFarray *fa)
{
  char buffer[JB_BUFFER_SIZE];
  unsigned int i;
  for (i = 0; i < fa->n; ++i)
    {
      SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, fa->x[i]);
      printf ("f[%u]=%s\n", i, buffer);
    }
}

void
darray_print (const JBDOUBLE *fa, const unsigned int n)
{
  char buffer[JB_BUFFER_SIZE];
  unsigned int i;
  for (i = 0; i <= n; ++i)
    {
      SNPRINTF (buffer, JB_BUFFER_SIZE, FWL, fa[i]);
      printf ("f[%u]=%s\n", i, buffer);
    }
}

int
check_f32 (const float x, const float f0, const float g0, const float prec)
{
  if (fabsf (f0 / g0 - 1.f) > prec && fabsf (f0 - g0) > prec)
    {
      printf ("f/g-1=%.8g f-g=%.8g p=%.8g\n", f0 / g0 - 1.f, f0 - g0, prec);
      printf ("x=%.8g f=%.8g g=%.8g\n", x, f0, g0);
      return 0;
    }
  return 1;
}

int
check_uni_f32 (float (*f) (const float), float (*g) (const float),
               const float prec, const float xmin, const float xmax,
               const unsigned int n)
{
  float x, xm, dx, f0, g0;
  int i, n1;
  n1 = (int) n - 1;
  xm = 0.5f * (xmin + xmax);
  dx = (xmax - xm) / (float) n1;
  for (i = 0; i < (int) n; ++i)
    {
      if (i == 0)
        x = xmin;
      else if (i == n1)
        x = xmax;
      else
        x = xm + (float) (2 * i - n1) * dx;
      f0 = f (x);
      g0 = g (x);
      if (!check_f32 (x, f0, g0, prec))
        return 0;
    }
  return 1;
}

int
check_logn_f32 (float (*f) (const float), float (*g) (const float),
                const float prec, const float x0)
{
  float x, f0, g0;
  for (x = x0; isfinite (x); x *= 2.f)
    {
      f0 = f (x);
      g0 = g (x);
      if (!isfinite (f0) && !isfinite (g0))
        break;
      if (!check_f32 (x, f0, g0, prec))
        return 0;
    }
  for (x = x0; fabsf (x) > 0.f; x *= 0.5f)
    {
      f0 = f (x);
      g0 = g (x);
      if (!isfinite (f0) && !isfinite (g0))
        break;
      if (!check_f32 (x, f0, g0, prec))
        return 0;
    }
  return 1;
}

int
check_f32_log (float (*f) (const float), float (*g) (const float),
               const float prec)
{
  if (!check_logn_f32 (f, g, prec, 1.f))
    return 0;
  return check_logn_f32 (f, g, prec, -1.f);
}

unsigned int
test_f32 (float (*f) (const float), const float g, const float x)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_f32 (x, f (x), g, n * FLT_EPSILON))
      break;
  return n;
}

unsigned int
test_uni_f32 (float (*f) (const float), float (*g) (const float),
              const float xmin, const float xmax)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_uni_f32 (f, g, n * FLT_EPSILON, xmin, xmax, 1000))
      break;
  return n;
}

unsigned int
test_f32_log (float (*f) (const float), float (*g) (const float))
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_f32_log (f, g, n * FLT_EPSILON))
      break;
  return n;
}

unsigned int
test_logn_f32 (float (*f) (const float), float (*g) (const float),
               const float x0)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_logn_f32 (f, g, n * FLT_EPSILON, x0))
      break;
  return n;
}

int
check_f64 (const double x, const double f0, const double g0, const double prec)
{
  if (fabs (f0 / g0 - 1.) > prec && fabs (f0 - g0) > prec)
    {
      printf ("f/g-1=%.17lg f-g=%.17lg p=%.17lg\n",
              f0 / g0 - 1., f0 - g0, prec);
      printf ("x=%.17lg f=%.17lg g=%.17lg\n", x, f0, g0);
      return 0;
    }
  return 1;
}

int
check_uni_f64 (double (*f) (const double), double (*g) (const double),
               const double prec, const double xmin, const double xmax,
               const unsigned int n)
{
  double x, xm, dx, f0, g0;
  int i, n1;
  n1 = (int) n - 1;
  xm = 0.5 * (xmin + xmax);
  dx = (xmax - xm) / (double) n1;
  for (i = 0; i < (int) n; ++i)
    {
      if (i == 0)
        x = xmin;
      else if (i == n1)
        x = xmax;
      else
        x = xm + (double) (2 * i - n1) * dx;
      f0 = f (x);
      g0 = g (x);
      if (!check_f64 (x, f0, g0, prec))
        return 0;
    }
  return 1;
}

int
check_logn_f64 (double (*f) (const double), double (*g) (const double),
                const double prec, const double x0)
{
  double x, f0, g0;
  for (x = x0; isfinite (x); x *= 2.)
    {
      f0 = f (x);
      g0 = g (x);
      if (!isfinite (f0) && !isfinite (g0))
        break;
      if (!check_f64 (x, f0, g0, prec))
        return 0;
    }
  for (x = x0; fabs (x) > 0.; x *= 0.5)
    {
      f0 = f (x);
      g0 = g (x);
      if (!isfinite (f0) && !isfinite (g0))
        break;
      if (!check_f64 (x, f0, g0, prec))
        return 0;
    }
  return 1;
}

int
check_f64_log (double (*f) (const double), double (*g) (const double),
               const double prec)
{
  if (!check_logn_f64 (f, g, prec, 1.))
    return 0;
  return check_logn_f64 (f, g, prec, -1.);
}

unsigned int
test_f64 (double (*f) (const double), const double g, const double x)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_f64 (x, f (x), g, n * DBL_EPSILON))
      break;
  return n;
}

unsigned int
test_uni_f64 (double (*f) (const double), double (*g) (const double),
              const double xmin, const double xmax)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_uni_f64 (f, g, n * DBL_EPSILON, xmin, xmax, 1000))
      break;
  return n;
}

unsigned int
test_f64_log (double (*f) (const double), double (*g) (const double))
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_f64_log (f, g, n * DBL_EPSILON))
      break;
  return n;
}

unsigned int
test_logn_f64 (double (*f) (const double), double (*g) (const double),
               const double x0)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_logn_f64 (f, g, n * DBL_EPSILON, x0))
      break;
  return n;
}

#ifdef __SSE4_2__

int
check_uni_4xf32 (__m128 (*f) (const __m128), float (*g) (const float),
                 const float prec, const float xmin, const float xmax,
                 const unsigned int n)
{
  float x[4] JB_ALIGNED, f0[4] JB_ALIGNED, g0[4] JB_ALIGNED;
  float xm, dx;
  int i, j, n1;
  n1 = (int) n - 1;
  xm = 0.5f * (xmin + xmax);
  dx = (xmax - xm) / (float) n1;
  for (i = 0; i < (int) n;)
    {
      for (j = 0; j < 4; ++j, ++i)
        {
          if (i == 0)
            x[j] = xmin;
          else if (i == n1)
            x[j] = xmax;
          else
            x[j] = xm + (2 * i - n1) * dx;
          g0[j] = g (x[j]);
        }
      _mm_store_ps (f0, f (_mm_load_ps (x)));
      for (j = 0; j < 4; ++j)
        if (!check_f32 (x[j], f0[j], g0[j], prec))
          return 0;
    }
  return 1;
}

int
check_logn_4xf32 (__m128 (*f) (const __m128), float (*g) (const float),
                  const float prec, const float x0)
{
  float x[4] JB_ALIGNED, f0[4] JB_ALIGNED, g0[4] JB_ALIGNED;
  float xn;
  unsigned int j;
  for (xn = x0; isfinite (xn);)
    {
      for (j = 0; j < 4; ++j, xn *= 2.f)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      _mm_store_ps (f0, f (_mm_load_ps (x)));
      for (j = 0; j < 4; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            goto break1;
          if (!check_f32 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
break1:
  for (xn = x0; fabsf (xn) > 0.f;)
    {
      for (j = 0; j < 4; ++j, xn *= 0.5f)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      _mm_store_ps (f0, f (_mm_load_ps (x)));
      for (j = 0; j < 4; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            return 1;
          if (!check_f32 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
  return 1;
}

int
check_4xf32_log (__m128 (*f) (const __m128), float (*g) (const float),
                 const float prec)
{
  if (!check_logn_4xf32 (f, g, prec, 1.f))
    return 0;
  return check_logn_4xf32 (f, g, prec, -1.f);
}

unsigned int
test_uni_4xf32 (__m128 (*f) (const __m128), float (*g) (const float),
                const float xmin, const float xmax)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_uni_4xf32 (f, g, n * FLT_EPSILON, xmin, xmax, 1000))
      break;
  return n;
}

unsigned int
test_4xf32_log (__m128 (*f) (const __m128), float (*g) (const float))
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_4xf32_log (f, g, n * FLT_EPSILON))
      break;
  return n;
}

unsigned int
test_logn_4xf32 (__m128 (*f) (const __m128), float (*g) (const float),
                 const float x0)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_logn_4xf32 (f, g, n * FLT_EPSILON, x0))
      break;
  return n;
}

int
check_uni_2xf64 (__m128d (*f) (const __m128d), double (*g) (const double),
                 const double prec, const double xmin, const double xmax,
                 const unsigned int n)
{
  double x[2] JB_ALIGNED, f0[2] JB_ALIGNED, g0[2] JB_ALIGNED;
  double xm, dx;
  int i, j, n1;
  n1 = (int) n - 1;
  xm = 0.5 * (xmin + xmax);
  dx = (xmax - xm) / (double) n1;
  for (i = 0; i < (int) n;)
    {
      for (j = 0; j < 2; ++j, ++i)
        {
          if (i == 0)
            x[j] = xmin;
          else if (i == n1)
            x[j] = xmax;
          else
            x[j] = xm + (2 * i - n1) * dx;
          g0[j] = g (x[j]);
        }
      _mm_store_pd (f0, f (_mm_load_pd (x)));
      for (j = 0; j < 2; ++j)
        if (!check_f64 (x[j], f0[j], g0[j], prec))
          return 0;
    }
  return 1;
}

int
check_logn_2xf64 (__m128d (*f) (const __m128d), double (*g) (const double),
                  const double prec, const double x0)
{
  double x[2] JB_ALIGNED, f0[2] JB_ALIGNED, g0[2] JB_ALIGNED;
  double xn;
  unsigned int j;
  for (xn = x0; isfinite (xn);)
    {
      for (j = 0; j < 2; ++j, xn *= 2.)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      _mm_store_pd (f0, f (_mm_load_pd (x)));
      for (j = 0; j < 2; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            goto break1;
          if (!check_f64 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
break1:
  for (xn = x0; fabs (xn) > 0.;)
    {
      for (j = 0; j < 2; ++j, xn *= 0.5)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      _mm_store_pd (f0, f (_mm_load_pd (x)));
      for (j = 0; j < 2; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            return 1;
          if (!check_f64 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
  return 1;
}

int
check_2xf64_log (__m128d (*f) (const __m128d), double (*g) (const double),
                 const double prec)
{
  if (!check_logn_2xf64 (f, g, prec, 1.))
    return 0;
  return check_logn_2xf64 (f, g, prec, -1.);
}

unsigned int
test_uni_2xf64 (__m128d (*f) (const __m128d), double (*g) (const double),
                const double xmin, const double xmax)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_uni_2xf64 (f, g, n * DBL_EPSILON, xmin, xmax, 1000))
      break;
  return n;
}

unsigned int
test_2xf64_log (__m128d (*f) (const __m128d), double (*g) (const double))
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_2xf64_log (f, g, n * DBL_EPSILON))
      break;
  return n;
}

unsigned int
test_logn_2xf64 (__m128d (*f) (const __m128d), double (*g) (const double),
                 const double x0)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_logn_2xf64 (f, g, n * DBL_EPSILON, x0))
      break;
  return n;
}

#endif

#ifdef __AVX__

int
check_uni_8xf32 (__m256 (*f) (const __m256), float (*g) (const float),
                 const float prec, const float xmin, const float xmax,
                 const unsigned int n)
{
  float x[8] JB_ALIGNED, f0[8] JB_ALIGNED, g0[8] JB_ALIGNED;
  float xm, dx;
  int i, j, n1;
  n1 = (int) n - 1;
  xm = 0.5f * (xmin + xmax);
  dx = (xmax - xm) / (float) n1;
  for (i = 0; i < (int) n;)
    {
      for (j = 0; j < 8; ++j, ++i)
        {
          if (i == 0)
            x[j] = xmin;
          else if (i == n1)
            x[j] = xmax;
          else
            x[j] = xm + (2 * i - n1) * dx;
          g0[j] = g (x[j]);
        }
      _mm256_store_ps (f0, f (_mm256_load_ps (x)));
      for (j = 0; j < 8; ++j)
        if (!check_f32 (x[j], f0[j], g0[j], prec))
          return 0;
    }
  return 1;
}

int
check_logn_8xf32 (__m256 (*f) (const __m256), float (*g) (const float),
                  const float prec, const float x0)
{
  float x[8] JB_ALIGNED, f0[8] JB_ALIGNED, g0[8] JB_ALIGNED;
  float xn;
  unsigned int j;
  for (xn = x0; isfinite (xn);)
    {
      for (j = 0; j < 8; ++j, xn *= 2.f)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      _mm256_store_ps (f0, f (_mm256_load_ps (x)));
      for (j = 0; j < 8; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            goto break1;
          if (!check_f32 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
break1:
  for (xn = x0; fabsf (xn) > 0.f;)
    {
      for (j = 0; j < 8; ++j, xn *= 0.5f)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      _mm256_store_ps (f0, f (_mm256_load_ps (x)));
      for (j = 0; j < 8; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            return 1;
          if (!check_f32 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
  return 1;
}

int
check_8xf32_log (__m256 (*f) (const __m256), float (*g) (const float),
                 const float prec)
{
  if (!check_logn_8xf32 (f, g, prec, 1.f))
    return 0;
  return check_logn_8xf32 (f, g, prec, -1.f);
}

unsigned int
test_uni_8xf32 (__m256 (*f) (const __m256), float (*g) (const float),
                const float xmin, const float xmax)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_uni_8xf32 (f, g, n * FLT_EPSILON, xmin, xmax, 1000))
      break;
  return n;
}

unsigned int
test_8xf32_log (__m256 (*f) (const __m256), float (*g) (const float))
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_8xf32_log (f, g, n * FLT_EPSILON))
      break;
  return n;
}

unsigned int
test_logn_8xf32 (__m256 (*f) (const __m256), float (*g) (const float),
                 const float x0)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_logn_8xf32 (f, g, n * FLT_EPSILON, x0))
      break;
  return n;
}

int
check_uni_4xf64 (__m256d (*f) (const __m256d), double (*g) (const double),
                 const double prec, const double xmin, const double xmax,
                 const unsigned int n)
{
  double x[4] JB_ALIGNED, f0[4] JB_ALIGNED, g0[4] JB_ALIGNED;
  double xm, dx;
  int i, j, n1;
  n1 = (int) n - 1;
  xm = 0.5 * (xmin + xmax);
  dx = (xmax - xm) / (double) n1;
  for (i = 0; i < (int) n;)
    {
      for (j = 0; j < 4; ++j, ++i)
        {
          if (i == 0)
            x[j] = xmin;
          else if (i == n1)
            x[j] = xmax;
          else
            x[j] = xm + (2 * i - n1) * dx;
          g0[j] = g (x[j]);
        }
      _mm256_store_pd (f0, f (_mm256_load_pd (x)));
      for (j = 0; j < 4; ++j)
        if (!check_f64 (x[j], f0[j], g0[j], prec))
          return 0;
    }
  return 1;
}

int
check_logn_4xf64 (__m256d (*f) (const __m256d), double (*g) (const double),
                  const double prec, const double x0)
{
  double x[4] JB_ALIGNED, f0[4] JB_ALIGNED, g0[4] JB_ALIGNED;
  double xn;
  unsigned int j;
  for (xn = x0; isfinite (xn);)
    {
      for (j = 0; j < 4; ++j, xn *= 2.)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      _mm256_store_pd (f0, f (_mm256_load_pd (x)));
      for (j = 0; j < 4; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            goto break1;
          if (!check_f64 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
break1:
  for (xn = x0; fabs (xn) > 0.;)
    {
      for (j = 0; j < 4; ++j, xn *= 0.5)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      _mm256_store_pd (f0, f (_mm256_load_pd (x)));
      for (j = 0; j < 4; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            return 1;
          if (!check_f64 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
  return 1;
}

int
check_4xf64_log (__m256d (*f) (const __m256d), double (*g) (const double),
                 const double prec)
{
  if (!check_logn_4xf64 (f, g, prec, 1.))
    return 0;
  return check_logn_4xf64 (f, g, prec, -1.);
}

unsigned int
test_uni_4xf64 (__m256d (*f) (const __m256d), double (*g) (const double),
                const double xmin, const double xmax)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_uni_4xf64 (f, g, n * DBL_EPSILON, xmin, xmax, 1000))
      break;
  return n;
}

unsigned int
test_4xf64_log (__m256d (*f) (const __m256d), double (*g) (const double))
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_4xf64_log (f, g, n * DBL_EPSILON))
      break;
  return n;
}

unsigned int
test_logn_4xf64 (__m256d (*f) (const __m256d), double (*g) (const double),
                 const double x0)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_logn_4xf64 (f, g, n * DBL_EPSILON, x0))
      break;
  return n;
}

#endif

#ifdef __AVX512F__

int
check_uni_16xf32 (__m512 (*f) (const __m512), float (*g) (const float),
                  const float prec, const float xmin, const float xmax,
                  const unsigned int n)
{
  float x[16] JB_ALIGNED, f0[16] JB_ALIGNED, g0[16] JB_ALIGNED;
  float xm, dx;
  int i, j, n1;
  n1 = (int) n - 1;
  xm = 0.5f * (xmin + xmax);
  dx = (xmax - xm) / (float) n1;
  for (i = 0; i < (int) n;)
    {
      for (j = 0; j < 16; ++j, ++i)
        {
          if (i == 0)
            x[j] = xmin;
          else if (i == n1)
            x[j] = xmax;
          else
            x[j] = xm + (2 * i - n1) * dx;
          g0[j] = g (x[j]);
        }
      _mm512_store_ps (f0, f (_mm512_load_ps (x)));
      for (j = 0; j < 16; ++j)
        if (!check_f32 (x[j], f0[j], g0[j], prec))
          return 0;
    }
  return 1;
}

int
check_logn_16xf32 (__m512 (*f) (const __m512), float (*g) (const float),
                   const float prec, const float x0)
{
  float x[16] JB_ALIGNED, f0[16] JB_ALIGNED, g0[16] JB_ALIGNED;
  float xn;
  unsigned int j;
  for (xn = x0; isfinite (xn);)
    {
      for (j = 0; j < 16; ++j, xn *= 2.f)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      _mm512_store_ps (f0, f (_mm512_load_ps (x)));
      for (j = 0; j < 16; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            goto break1;
          if (!check_f32 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
break1:
  for (xn = x0; fabsf (xn) > 0.f;)
    {
      for (j = 0; j < 16; ++j, xn *= 0.5f)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      _mm512_store_ps (f0, f (_mm512_load_ps (x)));
      for (j = 0; j < 16; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            return 1;
          if (!check_f32 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
  return 1;
}

int
check_16xf32_log (__m512 (*f) (const __m512), float (*g) (const float),
                  const float prec)
{
  if (!check_logn_16xf32 (f, g, prec, 1.f))
    return 0;
  return check_logn_16xf32 (f, g, prec, -1.f);
}

unsigned int
test_uni_16xf32 (__m512 (*f) (const __m512), float (*g) (const float),
                 const float xmin, const float xmax)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_uni_16xf32 (f, g, n * FLT_EPSILON, xmin, xmax, 1000))
      break;
  return n;
}

unsigned int
test_16xf32_log (__m512 (*f) (const __m512), float (*g) (const float))
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_16xf32_log (f, g, n * FLT_EPSILON))
      break;
  return n;
}

unsigned int
test_logn_16xf32 (__m512 (*f) (const __m512), float (*g) (const float),
                  const float x0)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_logn_16xf32 (f, g, n * FLT_EPSILON, x0))
      break;
  return n;
}

int
check_uni_8xf64 (__m512d (*f) (const __m512d), double (*g) (const double),
                 const double prec, const double xmin, const double xmax,
                 const unsigned int n)
{
  double x[8] JB_ALIGNED, f0[8] JB_ALIGNED, g0[8] JB_ALIGNED;
  double xm, dx;
  int i, j, n1;
  n1 = (int) n - 1;
  xm = 0.5 * (xmin + xmax);
  dx = (xmax - xm) / (double) n1;
  for (i = 0; i < (int) n;)
    {
      for (j = 0; j < 8; ++j, ++i)
        {
          if (i == 0)
            x[j] = xmin;
          else if (i == n1)
            x[j] = xmax;
          else
            x[j] = xm + (2 * i - n1) * dx;
          g0[j] = g (x[j]);
        }
      _mm512_store_pd (f0, f (_mm512_load_pd (x)));
      for (j = 0; j < 8; ++j)
        if (!check_f64 (x[j], f0[j], g0[j], prec))
          return 0;
    }
  return 1;
}

int
check_logn_8xf64 (__m512d (*f) (const __m512d), double (*g) (const double),
                  const double prec, const double x0)
{
  double x[8] JB_ALIGNED, f0[8] JB_ALIGNED, g0[8] JB_ALIGNED;
  double xn;
  unsigned int j;
  for (xn = x0; isfinite (xn);)
    {
      for (j = 0; j < 8; ++j, xn *= 2.)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      _mm512_store_pd (f0, f (_mm512_load_pd (x)));
      for (j = 0; j < 8; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            goto break1;
          if (!check_f64 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
break1:
  for (xn = x0; fabs (xn) > 0.;)
    {
      for (j = 0; j < 8; ++j, xn *= 0.5)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      _mm512_store_pd (f0, f (_mm512_load_pd (x)));
      for (j = 0; j < 8; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            return 1;
          if (!check_f64 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
  return 1;
}

int
check_8xf64_log (__m512d (*f) (const __m512d), double (*g) (const double),
                 const double prec)
{
  if (!check_logn_8xf64 (f, g, prec, 1.))
    return 0;
  return check_logn_8xf64 (f, g, prec, -1.);
}

unsigned int
test_uni_8xf64 (__m512d (*f) (const __m512d), double (*g) (const double),
                double xmin, const double xmax)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_uni_8xf64 (f, g, n * DBL_EPSILON, xmin, xmax, 1000))
      break;
  return n;
}

unsigned int
test_8xf64_log (__m512d (*f) (const __m512d), double (*g) (const double))
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_8xf64_log (f, g, n * DBL_EPSILON))
      break;
  return n;
}

unsigned int
test_logn_8xf64 (__m512d (*f) (const __m512d), double (*g) (const double),
                 const double x0)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_logn_8xf64 (f, g, n * DBL_EPSILON, x0))
      break;
  return n;
}

#endif

#ifdef __ARM_NEON

int
check_uni_4xf32 (float32x4_t (*f) (const float32x4_t), float (*g) (const float),
                 const float prec, const float xmin, const float xmax,
                 const unsigned int n)
{
  float x[4] JB_ALIGNED, f0[4] JB_ALIGNED, g0[4] JB_ALIGNED;
  float xm, dx;
  int i, j, n1;
  n1 = (int) n - 1;
  xm = 0.5f * (xmin + xmax);
  dx = (xmax - xm) / (float) n1;
  for (i = 0; i < (int) n;)
    {
      for (j = 0; j < 4; ++j, ++i)
        {
          if (i == 0)
            x[j] = xmin;
          else if (i == n1)
            x[j] = xmax;
          else
            x[j] = xm + (2 * i - n1) * dx;
          g0[j] = g (x[j]);
        }
      vst1q_f32 (f0, f (vld1q_f32 (x)));
      for (j = 0; j < 4; ++j)
        if (!check_f32 (x[j], f0[j], g0[j], prec))
          return 0;
    }
  return 1;
}

int
check_logn_4xf32 (float32x4_t (*f) (const float32x4_t),
                  float (*g) (const float), const float prec, const float x0)
{
  float x[4] JB_ALIGNED, f0[4] JB_ALIGNED, g0[4] JB_ALIGNED;
  float xn;
  unsigned int j;
  for (xn = x0; isfinite (xn);)
    {
      for (j = 0; j < 4; ++j, xn *= 2.f)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      vst1q_f32 (f0, f (vld1q_f32 (x)));
      for (j = 0; j < 4; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            goto break1;
          if (!check_f32 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
break1:
  for (xn = x0; fabsf (xn) > 0.f;)
    {
      for (j = 0; j < 4; ++j, xn *= 0.5f)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      vst1q_f32 (f0, f (vld1q_f32 (x)));
      for (j = 0; j < 4; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            return 1;
          if (!check_f32 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
  return 1;
}

int
check_4xf32_log (float32x4_t (*f) (const float32x4_t), float (*g) (const float),
                 const float prec)
{
  if (!check_logn_4xf32 (f, g, prec, 1.f))
    return 0;
  return check_logn_4xf32 (f, g, prec, -1.f);
}

unsigned int
test_uni_4xf32 (float32x4_t (*f) (const float32x4_t), float (*g) (const float),
                const float xmin, const float xmax)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_uni_4xf32 (f, g, n * FLT_EPSILON, xmin, xmax, 1000))
      break;
  return n;
}

unsigned int
test_4xf32_log (float32x4_t (*f) (const float32x4_t), float (*g) (const float))
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_4xf32_log (f, g, n * FLT_EPSILON))
      break;
  return n;
}

unsigned int
test_logn_4xf32 (float32x4_t (*f) (const float32x4_t), float (*g) (const float),
                 const float x0)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_logn_4xf32 (f, g, n * FLT_EPSILON, x0))
      break;
  return n;
}

int
check_uni_2xf64 (float64x2_t (*f) (const float64x2_t),
                 double (*g) (const double), const double prec,
                 const double xmin, const double xmax, const unsigned int n)
{
  double x[2] JB_ALIGNED, f0[2] JB_ALIGNED, g0[2] JB_ALIGNED;
  double xm, dx;
  int i, j, n1;
  n1 = (int) n - 1;
  xm = 0.5 * (xmin + xmax);
  dx = (xmax - xm) / (double) n1;
  for (i = 0; i < (int) n;)
    {
      for (j = 0; j < 2; ++j, ++i)
        {
          if (i == 0)
            x[j] = xmin;
          else if (i == n1)
            x[j] = xmax;
          else
            x[j] = xm + (2 * i - n1) * dx;
          g0[j] = g (x[j]);
        }
      vst1q_f64 (f0, f (vld1q_f64 (x)));
      for (j = 0; j < 2; ++j)
        if (!check_f64 (x[j], f0[j], g0[j], prec))
          return 0;
    }
  return 1;
}

int
check_logn_2xf64 (float64x2_t (*f) (const float64x2_t),
                  double (*g) (const double),
                  const double prec, const double x0)
{
  double x[2] JB_ALIGNED, f0[2] JB_ALIGNED, g0[2] JB_ALIGNED;
  double xn;
  unsigned int j;
  for (xn = x0; isfinite (xn);)
    {
      for (j = 0; j < 2; ++j, xn *= 2.)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      vst1q_f64 (f0, f (vld1q_f64 (x)));
      for (j = 0; j < 2; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            goto break1;
          if (!check_f64 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
break1:
  for (xn = x0; fabs (xn) > 0.;)
    {
      for (j = 0; j < 2; ++j, xn *= 0.5)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      vst1q_f64 (f0, f (vld1q_f64 (x)));
      for (j = 0; j < 2; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            return 1;
          if (!check_f64 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
  return 1;
}

int
check_2xf64_log (float64x2_t (*f) (const float64x2_t),
                 double (*g) (const double), const double prec)
{
  if (!check_logn_2xf64 (f, g, prec, 1.))
    return 0;
  return check_logn_2xf64 (f, g, prec, -1.);
}

unsigned int
test_uni_2xf64 (float64x2_t (*f) (const float64x2_t),
                double (*g) (const double),
                const double xmin, const double xmax)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_uni_2xf64 (f, g, n * DBL_EPSILON, xmin, xmax, 1000))
      break;
  return n;
}

unsigned int
test_2xf64_log (float64x2_t (*f) (const float64x2_t),
                double (*g) (const double))
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_2xf64_log (f, g, n * DBL_EPSILON))
      break;
  return n;
}

unsigned int
test_logn_2xf64 (float64x2_t (*f) (const float64x2_t),
                 double (*g) (const double), const double x0)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_logn_2xf64 (f, g, n * DBL_EPSILON, x0))
      break;
  return n;
}

#endif

#ifdef __riscv_vector

int
check_uni_4xf32 (vfloat32m1_t (*f) (const vfloat32m1_t),
                 float (*g) (const float), const float prec,
                 const float xmin, const float xmax, const unsigned int n)
{
  float x[4] JB_ALIGNED, f0[4] JB_ALIGNED, g0[4] JB_ALIGNED;
  float xm, dx;
  int i, j, n1;
  n1 = (int) n - 1;
  xm = 0.5f * (xmin + xmax);
  dx = (xmax - xm) / (float) n1;
  for (i = 0; i < (int) n;)
    {
      for (j = 0; j < 4; ++j, ++i)
        {
          if (i == 0)
            x[j] = xmin;
          else if (i == n1)
            x[j] = xmax;
          else
            x[j] = xm + (2 * i - n1) * dx;
          g0[j] = g (x[j]);
        }
      __riscv_vse32_v_f32m1 (f0, f (__riscv_vle32_v_f32m1 (x, 4)), 4);
      for (j = 0; j < 4; ++j)
        if (!check_f32 (x[j], f0[j], g0[j], prec))
          return 0;
    }
  return 1;
}

int
check_logn_4xf32 (vfloat32m1_t (*f) (const vfloat32m1_t),
                  float (*g) (const float), const float prec, const float x0)
{
  float x[4] JB_ALIGNED, f0[4] JB_ALIGNED, g0[4] JB_ALIGNED;
  float xn;
  unsigned int j;
  for (xn = x0; isfinite (xn);)
    {
      for (j = 0; j < 4; ++j, xn *= 2.f)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      __riscv_vse32_v_f32m1 (f0, f (__riscv_vle32_v_f32m1 (x, 4)), 4);
      for (j = 0; j < 4; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            goto break1;
          if (!check_f32 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
break1:
  for (xn = x0; fabsf (xn) > 0.f;)
    {
      for (j = 0; j < 4; ++j, xn *= 0.5f)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      __riscv_vse32_v_f32m1 (f0, f (__riscv_vle32_v_f32m1 (x, 4)), 4);
      for (j = 0; j < 4; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            return 1;
          if (!check_f32 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
  return 1;
}

int
check_4xf32_log (vfloat32m1_t (*f) (const vfloat32m1_t),
                 float (*g) (const float), const float prec)
{
  if (!check_logn_4xf32 (f, g, prec, 1.f))
    return 0;
  return check_logn_4xf32 (f, g, prec, -1.f);
}

unsigned int
test_uni_4xf32 (vfloat32m1_t (*f) (const vfloat32m1_t),
                float (*g) (const float), const float xmin, const float xmax)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_uni_4xf32 (f, g, n * FLT_EPSILON, xmin, xmax, 1000))
      break;
  return n;
}

unsigned int
test_4xf32_log (vfloat32m1_t (*f) (const vfloat32m1_t),
                float (*g) (const float))
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_4xf32_log (f, g, n * FLT_EPSILON))
      break;
  return n;
}

unsigned int
test_logn_4xf32 (vfloat32m1_t (*f) (const vfloat32m1_t),
                 float (*g) (const float), const float x0)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_logn_4xf32 (f, g, n * FLT_EPSILON, x0))
      break;
  return n;
}

int
check_uni_2xf64 (vfloat64m1_t (*f) (const vfloat64m1_t),
                 double (*g) (const double), const double prec,
                 const double xmin, const double xmax, const unsigned int n)
{
  double x[2] JB_ALIGNED, f0[2] JB_ALIGNED, g0[2] JB_ALIGNED;
  double xm, dx;
  int i, j, n1;
  n1 = (int) n - 1;
  xm = 0.5 * (xmin + xmax);
  dx = (xmax - xm) / (double) n1;
  for (i = 0; i < (int) n;)
    {
      for (j = 0; j < 2; ++j, ++i)
        {
          if (i == 0)
            x[j] = xmin;
          else if (i == n1)
            x[j] = xmax;
          else
            x[j] = xm + (2 * i - n1) * dx;
          g0[j] = g (x[j]);
        }
      __riscv_vse64_v_f64m1 (f0, f (__riscv_vle64_v_f64m1 (x, 2)), 2);
      for (j = 0; j < 2; ++j)
        if (!check_f64 (x[j], f0[j], g0[j], prec))
          return 0;
    }
  return 1;
}

int
check_logn_2xf64 (vfloat64m1_t (*f) (const vfloat64m1_t),
                  double (*g) (const double),
                  const double prec, const double x0)
{
  double x[2] JB_ALIGNED, f0[2] JB_ALIGNED, g0[2] JB_ALIGNED;
  double xn;
  unsigned int j;
  for (xn = x0; isfinite (xn);)
    {
      for (j = 0; j < 2; ++j, xn *= 2.)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      __riscv_vse64_v_f64m1 (f0, f (__riscv_vle64_v_f64m1 (x, 2)), 2);
      for (j = 0; j < 2; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            goto break1;
          if (!check_f64 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
break1:
  for (xn = x0; fabs (xn) > 0.;)
    {
      for (j = 0; j < 2; ++j, xn *= 0.5)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      __riscv_vse64_v_f64m1 (f0, f (__riscv_vle64_v_f64m1 (x, 2)), 2);
      for (j = 0; j < 2; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            return 1;
          if (!check_f64 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
  return 1;
}

int
check_2xf64_log (vfloat64m1_t (*f) (const vfloat64m1_t),
                 double (*g) (const double), const double prec)
{
  if (!check_logn_2xf64 (f, g, prec, 1.))
    return 0;
  return check_logn_2xf64 (f, g, prec, -1.);
}

unsigned int
test_uni_2xf64 (vfloat64m1_t (*f) (const vfloat64m1_t),
                double (*g) (const double),
                const double xmin, const double xmax)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_uni_2xf64 (f, g, n * DBL_EPSILON, xmin, xmax, 1000))
      break;
  return n;
}

unsigned int
test_2xf64_log (vfloat64m1_t (*f) (const vfloat64m1_t),
                double (*g) (const double))
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_2xf64_log (f, g, n * DBL_EPSILON))
      break;
  return n;
}

unsigned int
test_logn_2xf64 (vfloat64m1_t (*f) (const vfloat64m1_t),
                 double (*g) (const double), const double x0)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_logn_2xf64 (f, g, n * DBL_EPSILON, x0))
      break;
  return n;
}

int
check_uni_8xf32 (vfloat32m1_t (*f) (const vfloat32m1_t),
                 float (*g) (const float), const float prec,
                 const float xmin, const float xmax, const unsigned int n)
{
  float x[8] JB_ALIGNED, f0[8] JB_ALIGNED, g0[8] JB_ALIGNED;
  float xm, dx;
  int i, j, n1;
  n1 = (int) n - 1;
  xm = 0.5f * (xmin + xmax);
  dx = (xmax - xm) / (float) n1;
  for (i = 0; i < (int) n;)
    {
      for (j = 0; j < 8; ++j, ++i)
        {
          if (i == 0)
            x[j] = xmin;
          else if (i == n1)
            x[j] = xmax;
          else
            x[j] = xm + (2 * i - n1) * dx;
          g0[j] = g (x[j]);
        }
      __riscv_vse32_v_f32m1 (f0, f (__riscv_vle32_v_f32m1 (x, 8)), 8);
      for (j = 0; j < 8; ++j)
        if (!check_f32 (x[j], f0[j], g0[j], prec))
          return 0;
    }
  return 1;
}

int
check_logn_8xf32 (vfloat32m1_t (*f) (const vfloat32m1_t),
                  float (*g) (const float), const float prec, const float x0)
{
  float x[8] JB_ALIGNED, f0[8] JB_ALIGNED, g0[8] JB_ALIGNED;
  float xn;
  unsigned int j;
  for (xn = x0; isfinite (xn);)
    {
      for (j = 0; j < 8; ++j, xn *= 2.f)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      __riscv_vse32_v_f32m1 (f0, f (__riscv_vle32_v_f32m1 (x, 8)), 8);
      for (j = 0; j < 8; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            goto break1;
          if (!check_f32 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
break1:
  for (xn = x0; fabsf (xn) > 0.f;)
    {
      for (j = 0; j < 8; ++j, xn *= 0.5f)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      __riscv_vse32_v_f32m1 (f0, f (__riscv_vle32_v_f32m1 (x, 8)), 8);
      for (j = 0; j < 8; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            return 1;
          if (!check_f32 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
  return 1;
}

int
check_8xf32_log (vfloat32m1_t (*f) (const vfloat32m1_t),
                 float (*g) (const float), const float prec)
{
  if (!check_logn_8xf32 (f, g, prec, 1.f))
    return 0;
  return check_logn_8xf32 (f, g, prec, -1.f);
}

unsigned int
test_uni_8xf32 (vfloat32m1_t (*f) (const vfloat32m1_t),
                float (*g) (const float), const float xmin, const float xmax)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_uni_8xf32 (f, g, n * FLT_EPSILON, xmin, xmax, 1000))
      break;
  return n;
}

unsigned int
test_8xf32_log (vfloat32m1_t (*f) (const vfloat32m1_t),
                float (*g) (const float))
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_8xf32_log (f, g, n * FLT_EPSILON))
      break;
  return n;
}

unsigned int
test_logn_8xf32 (vfloat32m1_t (*f) (const vfloat32m1_t),
                 float (*g) (const float), const float x0)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_logn_8xf32 (f, g, n * FLT_EPSILON, x0))
      break;
  return n;
}

int
check_uni_4xf64 (vfloat64m1_t (*f) (const vfloat64m1_t),
                 double (*g) (const double), const double prec,
                 const double xmin, const double xmax, const unsigned int n)
{
  double x[4] JB_ALIGNED, f0[4] JB_ALIGNED, g0[4] JB_ALIGNED;
  double xm, dx;
  int i, j, n1;
  n1 = (int) n - 1;
  xm = 0.5 * (xmin + xmax);
  dx = (xmax - xm) / (double) n1;
  for (i = 0; i < (int) n;)
    {
      for (j = 0; j < 4; ++j, ++i)
        {
          if (i == 0)
            x[j] = xmin;
          else if (i == n1)
            x[j] = xmax;
          else
            x[j] = xm + (2 * i - n1) * dx;
          g0[j] = g (x[j]);
        }
      __riscv_vse64_v_f64m1 (f0, f (__riscv_vle64_v_f64m1 (x, 4)), 4);
      for (j = 0; j < 4; ++j)
        if (!check_f64 (x[j], f0[j], g0[j], prec))
          return 0;
    }
  return 1;
}

int
check_logn_4xf64 (vfloat64m1_t (*f) (const vfloat64m1_t),
                  double (*g) (const double),
                  const double prec, const double x0)
{
  double x[4] JB_ALIGNED, f0[4] JB_ALIGNED, g0[4] JB_ALIGNED;
  double xn;
  unsigned int j;
  for (xn = x0; isfinite (xn);)
    {
      for (j = 0; j < 4; ++j, xn *= 2.)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      __riscv_vse64_v_f64m1 (f0, f (__riscv_vle64_v_f64m1 (x, 4)), 4);
      for (j = 0; j < 4; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            goto break1;
          if (!check_f64 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
break1:
  for (xn = x0; fabs (xn) > 0.;)
    {
      for (j = 0; j < 4; ++j, xn *= 0.5)
        {
          x[j] = xn;
          g0[j] = g (xn);
        }
      __riscv_vse64_v_f64m1 (f0, f (__riscv_vle64_v_f64m1 (x, 4)), 4);
      for (j = 0; j < 4; ++j)
        {
          if (!isfinite (f0[j]) && !isfinite (g0[j]))
            return 1;
          if (!check_f64 (x[j], f0[j], g0[j], prec))
            return 0;
        }
    }
  return 1;
}

int
check_4xf64_log (vfloat64m1_t (*f) (const vfloat64m1_t),
                 double (*g) (const double), const double prec)
{
  if (!check_logn_4xf64 (f, g, prec, 1.))
    return 0;
  return check_logn_4xf64 (f, g, prec, -1.);
}

unsigned int
test_uni_4xf64 (vfloat64m1_t (*f) (const vfloat64m1_t),
                double (*g) (const double),
                const double xmin, const double xmax)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_uni_4xf64 (f, g, n * DBL_EPSILON, xmin, xmax, 1000))
      break;
  return n;
}

unsigned int
test_4xf64_log (vfloat64m1_t (*f) (const vfloat64m1_t),
                double (*g) (const double))
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_4xf64_log (f, g, n * DBL_EPSILON))
      break;
  return n;
}

unsigned int
test_logn_4xf64 (vfloat64m1_t (*f) (const vfloat64m1_t),
                 double (*g) (const double), const double x0)
{
  unsigned int n;
  for (n = 1; n < MAX_ITERATIONS; n <<= 1)
    if (check_logn_4xf64 (f, g, n * DBL_EPSILON, x0))
      break;
  return n;
}

#endif

int
check_uni (JBFLOAT (*f) (const JBFLOAT), JBFLOAT (*g) (const JBFLOAT),
           const JBFLOAT prec, const JBFLOAT xmin, const JBFLOAT xmax,
           const unsigned int n)
{
  JBFLOAT x, xm, dx, f0, g0;
  int i, n1;
  n1 = (int) n - 1;
  xm = (JBFLOAT) 0.5 *(xmin + xmax);
  dx = (xmax - xm) / (JBFLOAT) n1;
  for (i = 0; i < (int) n; ++i)
    {
      if (i == 0)
        x = xmin;
      else if (i == n1)
        x = xmax;
      else
        x = xm + (JBFLOAT) (2 * i - n1) * dx;
      f0 = f (x);
      g0 = g (x);
      if (FABS (f0 / g0 - (JBFLOAT) 1.) > prec && FABS (f0 - g0) > prec)
        {
          print_float (x, "x");
          print_float (f0, "f");
          print_float (g0, "g");
          return 0;
        }
    }
  return 1;
}

int
check_logn (JBFLOAT (*f) (const JBFLOAT), JBFLOAT (*g) (const JBFLOAT),
            const JBFLOAT prec, const JBFLOAT x0)
{
  JBFLOAT x, f0, g0;
  for (x = x0; isfinite (x); x *= (JBFLOAT) 2.)
    {
      f0 = f (x);
      g0 = g (x);
      if (!isfinite (f0) && !isfinite (g0))
        break;
      if (FABS (f0 / g0 - (JBFLOAT) 1.) > prec && FABS (f0 - g0) > prec)
        {
          print_float (x, "x");
          print_float (f0, "f");
          print_float (g0, "g");
          return 0;
        }
    }
  for (x = x0; FABS (x) > (JBFLOAT) 0.; x *= (JBFLOAT) 0.5)
    {
      f0 = f (x);
      g0 = g (x);
      if (!isfinite (f0) && !isfinite (g0))
        break;
      if (FABS (f0 / g0 - (JBFLOAT) 1.) > prec && FABS (f0 - g0) > prec)
        {
          print_float (x, "x");
          print_float (f0, "f");
          print_float (g0, "g");
          return 0;
        }
    }
  return 1;
}

int
check_log (JBFLOAT (*f) (const JBFLOAT), JBFLOAT (*g) (const JBFLOAT),
           const JBFLOAT prec)
{
  if (!check_logn (f, g, prec, (JBFLOAT) 1.))
    return 0;
  return check_logn (f, g, prec, (JBFLOAT) - 1.);
}

int
check_unil (JBDOUBLE (*f) (const JBDOUBLE), JBDOUBLE (*g) (const JBDOUBLE),
            const JBDOUBLE prec, const JBDOUBLE xmin, const JBDOUBLE xmax,
            const unsigned int n)
{
  JBDOUBLE x, xm, dx, f0, g0;
  int i, n1;
  n1 = (int) n - 1;
  xm = (JBDOUBLE) 0.5 *(xmin + xmax);
  dx = (xmax - xm) / (JBDOUBLE) n1;
  for (i = 0; i < (int) n; ++i)
    {
      if (i == 0)
        x = xmin;
      else if (i == n1)
        x = xmax;
      else
        x = xm + (JBDOUBLE) (2 * i - n1) * dx;
      f0 = f (x);
      g0 = g (x);
      if (FABSL (f0 / g0 - (JBDOUBLE) 1.) > prec && FABSL (f0 - g0) > prec)
        {
          print_double (x, "x");
          print_double (f0, "f");
          print_double (g0, "g");
          return 0;
        }
    }
  return 1;
}

int
check_lognl (JBDOUBLE (*f) (const JBDOUBLE), JBDOUBLE (*g) (const JBDOUBLE),
             const JBDOUBLE prec, const JBDOUBLE x0)
{
  JBDOUBLE x, f0, g0;
  for (x = x0; isfinite (x); x *= (JBDOUBLE) 2.)
    {
      f0 = f (x);
      g0 = g (x);
      if (!isfinite (f0) && !isfinite (g0))
        break;
      if (FABSL (f0 / g0 - (JBDOUBLE) 1.) > prec && FABSL (f0 - g0) > prec)
        {
          print_double (x, "x");
          print_double (f0, "f");
          print_double (g0, "g");
          return 0;
        }
    }
  for (x = x0; FABSL (x) > (JBDOUBLE) 0.; x *= (JBDOUBLE) 0.5)
    {
      f0 = f (x);
      g0 = g (x);
      if (!isfinite (f0) && !isfinite (g0))
        break;
      if (FABSL (f0 / g0 - (JBDOUBLE) 1.) > prec && FABSL (f0 - g0) > prec)
        {
          print_double (x, "x");
          print_double (f0, "f");
          print_double (g0, "g");
          return 0;
        }
    }
  return 1;
}

int
check_logl (JBDOUBLE (*f) (const JBDOUBLE), JBDOUBLE (*g) (const JBDOUBLE),
            const JBDOUBLE prec)
{
  if (!check_lognl (f, g, prec, (JBDOUBLE) 1.))
    return 0;
  return check_lognl (f, g, prec, (JBDOUBLE) - 1.);
}

double
log1 (const double x)
{
  return log (1. + x);
}

float
number_find_f32 (float (*f) (const float), const float y,
                 const float xmin, const float xmax)
{
  float x0, x1, x2, f0, f2;
  unsigned int i;
  x1 = xmin;
  x2 = xmax;
  f0 = f (x1) - y;
  f2 = f (x2) - y;
  if (f0 * f2 > 0.f)
    {
      printf ("Unable to find\n");
      return 0.f;
    }
  if (f0 < 0.f)
    {
      for (i = 0; i < 128; ++i)
        {
          x0 = 0.5f * (x1 + x2);
          f0 = f (x0);
          if (f0 > y)
            x2 = x0;
          else
            x1 = x0;
        }
    }
  else
    {
      for (i = 0; i < 128; ++i)
        {
          x0 = 0.5f * (x1 + x2);
          f0 = f (x0);
          if (f0 < y)
            x2 = x0;
          else
            x1 = x0;
        }
    }
  return x0;
}

float
number_max_f32 (float (*f) (const float))
{
  float x0, x1, x2;
  unsigned int i;
  x2 = x1 = 1.f;
  while (isfinite (x2) && isfinite (f (x2)))
    {
      x1 = x2;
      x2 += x2;
    }
  while (!isfinite (x1) && !isfinite (f (x1)))
    {
      x2 = x1;
      x1 *= 0.5f;
    }
  for (i = 0; i < 128; ++i)
    {
      x0 = 0.5f * (x1 + x2);
      if (isfinite (x0) && isfinite (f (x0)))
        x1 = x0;
      else
        x2 = x0;
    }
  return x1;
}

float
number_min_f32 (float (*f) (const float))
{
  float x0, x1, x2;
  unsigned int i;
  x2 = x1 = 1.f;
  while (x1 > 0.f && isfinite (f (x1)))
    {
      x2 = x1;
      x1 *= 0.5f;
    }
  while (isfinite (x2) && !isfinite (f (x2)))
    {
      x1 = x2;
      x2 += x2;
    }
  for (i = 0; i < 128; ++i)
    {
      x0 = 0.5f * (x1 + x2);
      if (x0 > 0.f && isfinite (x0) && isfinite (f (x0)))
        x2 = x0;
      else
        x1 = x0;
    }
  return x2;
}

double
number_find_f64 (double (*f) (const double), const double y,
                 const double xmin, const double xmax)
{
  double x0, x1, x2, f0, f2;
  unsigned int i;
  x1 = xmin;
  x2 = xmax;
  f0 = f (x1) - y;
  f2 = f (x2) - y;
  if (f0 * f2 > 0.)
    {
      printf ("Unable to find\n");
      return 0.;
    }
  if (f0 < 0.)
    {
      for (i = 0; i < 128; ++i)
        {
          x0 = 0.5 * (x1 + x2);
          f0 = f (x0);
          if (f0 > y)
            x2 = x0;
          else
            x1 = x0;
        }
    }
  else
    {
      for (i = 0; i < 128; ++i)
        {
          x0 = 0.5 * (x1 + x2);
          f0 = f (x0);
          if (f0 < y)
            x2 = x0;
          else
            x1 = x0;
        }
    }
  return x0;
}

double
number_max_f64 (double (*f) (const double))
{
  double x0, x1, x2;
  unsigned int i;
  x2 = x1 = 1.;
  while (isfinite (x2) && isfinite (f (x2)))
    {
      x1 = x2;
      x2 += x2;
    }
  while (!isfinite (x1) && !isfinite (f (x1)))
    {
      x2 = x1;
      x1 *= 0.5;
    }
  for (i = 0; i < 128; ++i)
    {
      x0 = 0.5 * (x1 + x2);
      if (isfinite (x0) && isfinite (f (x0)))
        x1 = x0;
      else
        x2 = x0;
    }
  return x1;
}

double
number_min_f64 (double (*f) (const double))
{
  double x0, x1, x2;
  unsigned int i;
  x2 = x1 = 1.;
  while (x1 > 0. && isfinite (f (x1)))
    {
      x2 = x1;
      x1 *= 0.5;
    }
  while (isfinite (x2) && !isfinite (f (x2)))
    {
      x1 = x2;
      x2 += x2;
    }
  for (i = 0; i < 128; ++i)
    {
      x0 = 0.5 * (x1 + x2);
      if (x0 > 0. && isfinite (x0) && isfinite (f (x0)))
        x2 = x0;
      else
        x1 = x0;
    }
  return x2;
}

int
main (void)
{
  MatrixDouble cd[4], czd[5];
  MatrixFloat cf[4], czf[5];
  JBDOUBLE darray[15], darray2[15], kd[3];
  JBFLOAT farray[15], farray2[15], kf[3];
  char buffer[JB_BUFFER_SIZE], buffer2[JB_BUFFER_SIZE];
  JBMFarray *fa, *fa2, *fa3;
  JBDOUBLE *darray3;
  JBFLOAT *farray3, *A1f, *A2f, *A3f;
  JBDOUBLE d, d2;
  JBFLOAT f, f2;
  double x, y;
  float xf, yf;
#ifdef __SSE4_2__
  double *d_1, *d_2;
  unsigned long long int *L_1;
  __m128d d_2xf64, d2_2xf64;
#endif
#ifdef __AVX__
  __m256d d_4xf64, d2_4xf64;
#endif
#ifdef __AVX512F__
  __m512d d_8xf64, d2_8xf64;
  __mmask8 m_8;
#endif
#ifdef __ARM_NEON
  double *d_1, *d_2;
  unsigned long long int *L_1;
  float64x2_t d_2xf64, d2_2xf64;
  uint64x2_t m_2xf64, m2_2xf64;
#endif
#ifdef __riscv_vector
  size_t vlmax32, vlmax64;
  double *d_1, *d_2;
  unsigned long long int *L_1;
  vfloat64m1_t d_2xf64, d2_2xf64, d_4xf64, d2_4xf64;
  vuint64m1_t m_2xf64, m2_2xf64, m_4xf64, m2_4xf64;
#endif
  long long int iL, iL2;
  unsigned long long int uL, uL2;
  long int il, il2;
  unsigned long int ul, ul2;
  int i, is, is2;
  unsigned int n, us, us2;

  // constants
  printf ("FLT_MIN=%g FLT_MAX=%g FLT_EPSILON=%g\n",
          FLT_MIN, FLT_MAX, FLT_EPSILON);
  printf ("DBL_MIN=%lg DBL_MAX=%lg DBL_EPSILON=%lg\n",
          DBL_MIN, DBL_MAX, DBL_EPSILON);

  // extreme values
  printf ("max x for exp2=%.7e=%.7e\n",
          number_max_f32 (jbm_f32_exp2), (float) FLT_MAX_EXP);

  printf ("max x for exp=%.7e\n", number_max_f32 (jbm_f32_exp));
  printf ("max x for exp10=%.7e=%.7e\n",
          number_max_f32 (jbm_f32_exp10), (float) FLT_MAX_10_EXP);
  printf ("max x for expm1=%.7e\n", number_max_f32 (jbm_f32_expm1));
  printf ("min x for log2=%.7e\n", number_min_f32 (jbm_f32_log2));
  printf ("min x for log=%.7e\n", number_min_f32 (jbm_f32_log));
  printf ("min x for log10=%.7e\n", number_min_f32 (jbm_f32_log10));
  printf ("max x for sinh=%.7e\n", number_max_f32 (jbm_f32_sinh));
  printf ("max x for cosh=%.7e\n", number_max_f32 (jbm_f32_cosh));
  x = number_find_f64 (erfc, (double) JBM_FLT_MIN, 1., 100.);
  printf ("erfc(x)=JBM_FLT_MIN => x=%.16le\n", x);

  printf ("max x for exp2=%.16le=%.16le\n",
          number_max_f64 (jbm_f64_exp2), (double) DBL_MAX_EXP);
  printf ("max x for exp=%.16le\n", number_max_f64 (jbm_f64_exp));
  printf ("max x for exp10=%.16le=%.16le\n",
          number_max_f64 (jbm_f64_exp10), (double) DBL_MAX_10_EXP);
  printf ("max x for expm1=%.16le\n", number_max_f64 (jbm_f64_expm1));
  printf ("min x for log2=%.16le\n", number_min_f64 (jbm_f64_log2));
  printf ("min x for log=%.16le\n", number_min_f64 (jbm_f64_log));
  printf ("min x for log10=%.16le\n", number_min_f64 (jbm_f64_log10));
  printf ("max x for sinh=%.16le\n", number_max_f64 (jbm_f64_sinh));
  printf ("max x for cosh=%.16le\n", number_max_f64 (jbm_f64_cosh));
  x = number_find_f64 (erfc, (double) JBM_DBL_MIN, 1., 100.);
  printf ("erfc(x)=JBM_DBL_MIN => x=%.16le\n", x);

  // checks

  printf ("checking float functions\n");
  n = test_uni_f32 (jbm_f32_abs, fabsf, -FLT_MAX, FLT_MAX);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check abs: OK(%u)\n", n);
  n = test_uni_f32 (jbm_f32_cbrt, cbrtf, -FLT_MAX, FLT_MAX);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cbrt: OK(%u)\n", n);
  n = test_f32_log (jbm_f32_exp2, exp2f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp2: OK(%u)\n", n);
  n = test_f32_log (jbm_f32_exp, expf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp: OK(%u)\n", n);
  n = test_f32_log (jbm_f32_exp10, exp10f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp10: OK(%u)\n", n);
  n = test_f32_log (jbm_f32_expm1, expm1f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check expm1: OK(%u)\n", n);
  n = test_logn_f32 (jbm_f32_log2, log2f, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log2: OK(%u)\n", n);
  n = test_logn_f32 (jbm_f32_log, logf, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log: OK(%u)\n", n);
  n = test_logn_f32 (jbm_f32_log10, log10f, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log10: OK(%u)\n", n);
  n = test_uni_f32 (jbm_f32_sin, sinf, -2.f * M_PIf, 2.f * M_PIf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check sin: OK(%u)\n", n);
  n = test_uni_f32 (jbm_f32_cos, cosf, -2.f * M_PIf, 2.f * M_PIf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cos: OK(%u)\n", n);
  n = test_uni_f32 (jbm_f32_tan, tanf, -2.f * M_PIf, 2.f * M_PIf);
  if (n == MAX_ITERATIONS)
    printf ("check tan: No\n");
  n = test_f32_log (jbm_f32_atan, atanf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check atan: OK(%u)\n", n);
  n = test_uni_f32 (jbm_f32_asin, asinf, -1.f, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check asin: OK(%u)\n", n);
  n = test_uni_f32 (jbm_f32_acos, acosf, -1.f, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check acos: OK(%u)\n", n);
  n = test_f32_log (jbm_f32_sinh, sinhf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check sinh: OK(%u)\n", n);
  n = test_f32_log (jbm_f32_cosh, coshf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cosh: OK(%u)\n", n);
  n = test_f32_log (jbm_f32_tanh, tanhf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check tanh: OK(%u)\n", n);
  n = test_uni_f32 (jbm_f32_erf, erff, -FLT_MAX_EXP, FLT_MAX_EXP);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check erf: OK(%u)\n", n);
  n = test_uni_f32 (jbm_f32_erfc, erfcf, -FLT_MAX_EXP, FLT_MAX_EXP);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check erfc: OK(%u)\n", n);

  printf ("checking double functions\n");
  n = test_uni_f64 (jbm_f64_abs, fabs, -0.5f * DBL_MAX, 0.5f * DBL_MAX);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check abs: OK(%u)\n", n);
  n = test_uni_f64 (jbm_f64_cbrt, cbrt, -0.5f * DBL_MAX, 0.5f * DBL_MAX);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cbrt: OK(%u)\n", n);
  n = test_f64_log (jbm_f64_exp2, exp2);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp2: OK(%u)\n", n);
  n = test_f64_log (jbm_f64_exp, exp);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp: OK(%u)\n", n);
  n = test_f64_log (jbm_f64_exp10, exp10);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp10: OK(%u)\n", n);
  n = test_f64_log (jbm_f64_expm1, expm1);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check expm1: OK(%u)\n", n);
  n = test_logn_f64 (jbm_f64_log2, log2, 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log2: OK(%u)\n", n);
  n = test_logn_f64 (jbm_f64_log, log, 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log: OK(%u)\n", n);
  n = test_logn_f64 (jbm_f64_log10, log10, 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log10: OK(%u)\n", n);
  n = test_uni_f64 (jbm_f64_sin, sin, -2. * M_PI, 2. * M_PI);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check sin: OK(%u)\n", n);
  n = test_uni_f64 (jbm_f64_cos, cos, -2. * M_PI, 2. * M_PI);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cos: OK(%u)\n", n);
  n = test_uni_f64 (jbm_f64_tan, tan, -2. * M_PI, 2. * M_PI);
  if (n == MAX_ITERATIONS)
    printf ("check tan: No\n");
  n = test_f64_log (jbm_f64_atan, atan);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check atan: OK(%u)\n", n);
  n = test_uni_f64 (jbm_f64_asin, asin, -1., 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check asin: OK(%u)\n", n);
  n = test_uni_f64 (jbm_f64_acos, acos, -1., 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check acos: OK(%u)\n", n);
  n = test_f64_log (jbm_f64_sinh, sinh);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check sinh: OK(%u)\n", n);
  n = test_f64_log (jbm_f64_cosh, cosh);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cosh: OK(%u)\n", n);
  n = test_f64_log (jbm_f64_tanh, tanh);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check tanh: OK(%u)\n", n);
  n = test_uni_f64 (jbm_f64_erf, erf, -DBL_MAX_EXP, DBL_MAX_EXP);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check erf: OK(%u)\n", n);
  n = test_uni_f64 (jbm_f64_erfc, erfc, -DBL_MAX_EXP, DBL_MAX_EXP);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check erfc: OK(%u)\n", n);

#ifdef __riscv_vector
  printf ("check RISCV vector functions\n");
  vlmax32 = __riscv_vsetvlmax_e32m1 ();
  vlmax64 = __riscv_vsetvlmax_e64m1 ();
  printf ("maximum 32 bits vector size=%lu\n", vlmax32);
  printf ("maximum 64 bits vector size=%lu\n", vlmax64);
#endif
#if defined (__SSE4_2__) || defined (__ARM_NEON) || defined (__riscv_vector)

#ifdef __SSE4_2__
  printf ("checking __m128 functions\n");
#endif
#ifdef __ARM_NEON
  printf ("checking float32x4_t functions\n");
#endif
#ifdef __riscv_vector
  printf ("checking vfloat32m1_t functions (128 bits)\n");
#endif

  n = test_uni_4xf32 (jbm_4xf32_abs, fabsf, -FLT_MAX, FLT_MAX);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check abs: OK(%u)\n", n);
  n = test_uni_4xf32 (jbm_4xf32_cbrt, cbrtf, -FLT_MAX, FLT_MAX);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cbrt: OK(%u)\n", n);
  n = test_4xf32_log (jbm_4xf32_exp2, exp2f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp2: OK(%u)\n", n);
  n = test_4xf32_log (jbm_4xf32_exp, expf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp: OK(%u)\n", n);
  n = test_4xf32_log (jbm_4xf32_exp10, exp10f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp10: OK(%u)\n", n);
  n = test_4xf32_log (jbm_4xf32_expm1, expm1f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check expm1: OK(%u)\n", n);
  n = test_logn_4xf32 (jbm_4xf32_log2, log2f, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log2: OK(%u)\n", n);
  n = test_logn_4xf32 (jbm_4xf32_log, logf, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log: OK(%u)\n", n);
  n = test_logn_4xf32 (jbm_4xf32_log10, log10f, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log10: OK(%u)\n", n);
  n = test_uni_4xf32 (jbm_4xf32_sin, sinf, -2.f * M_PIf, 2.f * M_PIf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check sin: OK(%u)\n", n);
  n = test_uni_4xf32 (jbm_4xf32_cos, cosf, -2.f * M_PIf, 2.f * M_PIf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cos: OK(%u)\n", n);
  n = test_uni_4xf32 (jbm_4xf32_tan, tanf, -2.f * M_PIf, 2.f * M_PIf);
  if (n == MAX_ITERATIONS)
    printf ("check tan: No\n");
  n = test_4xf32_log (jbm_4xf32_atan, atanf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check atan: OK(%u)\n", n);
  n = test_uni_4xf32 (jbm_4xf32_asin, asinf, -1.f, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check asin: OK(%u)\n", n);
  n = test_uni_4xf32 (jbm_4xf32_acos, acosf, -1.f, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check acos: OK(%u)\n", n);
  n = test_4xf32_log (jbm_4xf32_sinh, sinhf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check sinh: OK(%u)\n", n);
  n = test_4xf32_log (jbm_4xf32_cosh, coshf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cosh: OK(%u)\n", n);
  n = test_4xf32_log (jbm_4xf32_tanh, tanhf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check tanh: OK(%u)\n", n);
  n = test_uni_4xf32 (jbm_4xf32_erf, erff, -FLT_MAX_EXP, FLT_MAX_EXP);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check erf: OK(%u)\n", n);
  n = test_uni_4xf32 (jbm_4xf32_erfc, erfcf, -FLT_MAX_EXP, FLT_MAX_EXP);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check erfc: OK(%u)\n", n);

#ifdef __SSE4_2__
  printf ("checking __m128d functions\n");
#endif
#ifdef __ARM_NEON
  printf ("checking float64x2_t functions\n");
#endif
#ifdef __riscv_vector
  printf ("checking vfloat64m1_t functions (128 bits)\n");
#endif

  n = test_uni_2xf64 (jbm_2xf64_abs, fabs, -0.5f * DBL_MAX, 0.5f * DBL_MAX);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check abs: OK(%u)\n", n);
  n = test_uni_2xf64 (jbm_2xf64_cbrt, cbrt, -0.5f * DBL_MAX, 0.5f * DBL_MAX);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cbrt: OK(%u)\n", n);
  n = test_2xf64_log (jbm_2xf64_exp2, exp2);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp2: OK(%u)\n", n);
  n = test_2xf64_log (jbm_2xf64_exp, exp);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp: OK(%u)\n", n);
  n = test_2xf64_log (jbm_2xf64_exp10, exp10);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp10: OK(%u)\n", n);
  n = test_2xf64_log (jbm_2xf64_expm1, expm1);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check expm1: OK(%u)\n", n);
  n = test_logn_2xf64 (jbm_2xf64_log2, log2, 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log2: OK(%u)\n", n);
  n = test_logn_2xf64 (jbm_2xf64_log, log, 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log: OK(%u)\n", n);
  n = test_logn_2xf64 (jbm_2xf64_log10, log10, 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log10: OK(%u)\n", n);
  n = test_uni_2xf64 (jbm_2xf64_sin, sin, -2. * M_PI, 2. * M_PI);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check sin: OK(%u)\n", n);
  n = test_uni_2xf64 (jbm_2xf64_cos, cos, -2. * M_PI, 2. * M_PI);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cos: OK(%u)\n", n);
  n = test_uni_2xf64 (jbm_2xf64_tan, tan, -2. * M_PI, 2. * M_PI);
  if (n == MAX_ITERATIONS)
    printf ("check tan: No\n");
  n = test_2xf64_log (jbm_2xf64_atan, atan);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check atan: OK(%u)\n", n);
  n = test_uni_2xf64 (jbm_2xf64_asin, asin, -1., 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check asin: OK(%u)\n", n);
  n = test_uni_2xf64 (jbm_2xf64_acos, acos, -1., 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check acos: OK(%u)\n", n);
  n = test_2xf64_log (jbm_2xf64_sinh, sinh);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check sinh: OK(%u)\n", n);
  n = test_2xf64_log (jbm_2xf64_cosh, cosh);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cosh: OK(%u)\n", n);
  n = test_2xf64_log (jbm_2xf64_tanh, tanh);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check tanh: OK(%u)\n", n);
  n = test_uni_2xf64 (jbm_2xf64_erf, erf, -DBL_MAX_EXP, DBL_MAX_EXP);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check erf: OK(%u)\n", n);
  n = test_uni_2xf64 (jbm_2xf64_erfc, erfc, -DBL_MAX_EXP, DBL_MAX_EXP);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check erfc: OK(%u)\n", n);

#endif

#if defined (__AVX__) || defined (__riscv_vector)

#ifdef __AVX__
  printf ("checking __m256 functions\n");
#endif
#ifdef __riscv_vector
  printf ("checking vfloat32m1_t functions (256 bits)\n");
#endif

  n = test_uni_8xf32 (jbm_8xf32_abs, fabsf, -FLT_MAX, FLT_MAX);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check abs: OK(%u)\n", n);
  n = test_uni_8xf32 (jbm_8xf32_cbrt, cbrtf, -FLT_MAX, FLT_MAX);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cbrt: OK(%u)\n", n);
  n = test_8xf32_log (jbm_8xf32_exp2, exp2f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp2: OK(%u)\n", n);
  n = test_8xf32_log (jbm_8xf32_exp, expf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp: OK(%u)\n", n);
  n = test_8xf32_log (jbm_8xf32_exp10, exp10f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp10: OK(%u)\n", n);
  n = test_8xf32_log (jbm_8xf32_expm1, expm1f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check expm1: OK(%u)\n", n);
  n = test_logn_8xf32 (jbm_8xf32_log2, log2f, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log2: OK(%u)\n", n);
  n = test_logn_8xf32 (jbm_8xf32_log, logf, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log: OK(%u)\n", n);
  n = test_logn_8xf32 (jbm_8xf32_log10, log10f, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log10: OK(%u)\n", n);
  n = test_uni_8xf32 (jbm_8xf32_sin, sinf, -2.f * M_PIf, 2.f * M_PIf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check sin: OK(%u)\n", n);
  n = test_uni_8xf32 (jbm_8xf32_cos, cosf, -2.f * M_PIf, 2.f * M_PIf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cos: OK(%u)\n", n);
  n = test_uni_8xf32 (jbm_8xf32_tan, tanf, -2.f * M_PIf, 2.f * M_PIf);
  if (n == MAX_ITERATIONS)
    printf ("check tan: No\n");
  n = test_8xf32_log (jbm_8xf32_atan, atanf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check atan: OK(%u)\n", n);
  n = test_uni_8xf32 (jbm_8xf32_asin, asinf, -1.f, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check asin: OK(%u)\n", n);
  n = test_uni_8xf32 (jbm_8xf32_acos, acosf, -1.f, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check acos: OK(%u)\n", n);
  n = test_8xf32_log (jbm_8xf32_sinh, sinhf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check sinh: OK(%u)\n", n);
  n = test_8xf32_log (jbm_8xf32_cosh, coshf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cosh: OK(%u)\n", n);
  n = test_8xf32_log (jbm_8xf32_tanh, tanhf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check tanh: OK(%u)\n", n);
  n = test_uni_8xf32 (jbm_8xf32_erf, erff, -FLT_MAX_EXP, FLT_MAX_EXP);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check erf: OK(%u)\n", n);
  n = test_uni_8xf32 (jbm_8xf32_erfc, erfcf, -FLT_MAX_EXP, FLT_MAX_EXP);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check erfc: OK(%u)\n", n);

#ifdef __AVX__
  printf ("checking __m256d functions\n");
#endif
#ifdef __riscv_vector
  printf ("checking vfloat64m1_t functions (256 bits)\n");
#endif

  n = test_uni_4xf64 (jbm_4xf64_abs, fabs, -0.5f * DBL_MAX, 0.5f * DBL_MAX);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check abs: OK(%u)\n", n);
  n = test_uni_4xf64 (jbm_4xf64_cbrt, cbrt, -0.5f * DBL_MAX, 0.5f * DBL_MAX);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cbrt: OK(%u)\n", n);
  n = test_4xf64_log (jbm_4xf64_exp2, exp2);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp2: OK(%u)\n", n);
  n = test_4xf64_log (jbm_4xf64_exp, exp);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp: OK(%u)\n", n);
  n = test_4xf64_log (jbm_4xf64_exp10, exp10);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp10: OK(%u)\n", n);
  n = test_4xf64_log (jbm_4xf64_expm1, expm1);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check expm1: OK(%u)\n", n);
  n = test_logn_4xf64 (jbm_4xf64_log2, log2, 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log2: OK(%u)\n", n);
  n = test_logn_4xf64 (jbm_4xf64_log, log, 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log: OK(%u)\n", n);
  n = test_logn_4xf64 (jbm_4xf64_log10, log10, 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log10: OK(%u)\n", n);
  n = test_uni_4xf64 (jbm_4xf64_sin, sin, -2. * M_PI, 2. * M_PI);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check sin: OK(%u)\n", n);
  n = test_uni_4xf64 (jbm_4xf64_cos, cos, -2. * M_PI, 2. * M_PI);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cos: OK(%u)\n", n);
  n = test_uni_4xf64 (jbm_4xf64_tan, tan, -2. * M_PI, 2. * M_PI);
  if (n == MAX_ITERATIONS)
    printf ("check tan: No\n");
  n = test_4xf64_log (jbm_4xf64_atan, atan);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check atan: OK(%u)\n", n);
  n = test_uni_4xf64 (jbm_4xf64_asin, asin, -1., 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check asin: OK(%u)\n", n);
  n = test_uni_4xf64 (jbm_4xf64_acos, acos, -1., 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check acos: OK(%u)\n", n);
  n = test_4xf64_log (jbm_4xf64_sinh, sinh);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check sinh: OK(%u)\n", n);
  n = test_4xf64_log (jbm_4xf64_cosh, cosh);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cosh: OK(%u)\n", n);
  n = test_4xf64_log (jbm_4xf64_tanh, tanh);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check tanh: OK(%u)\n", n);
  n = test_uni_4xf64 (jbm_4xf64_erf, erf, -DBL_MAX_EXP, DBL_MAX_EXP);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check erf: OK(%u)\n", n);
  n = test_uni_4xf64 (jbm_4xf64_erfc, erfc, -DBL_MAX_EXP, DBL_MAX_EXP);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check erfc: OK(%u)\n", n);

#endif

#if __AVX512F__

  printf ("checking __m512 functions\n");
  n = test_uni_16xf32 (jbm_16xf32_abs, fabsf, -FLT_MAX, FLT_MAX);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check abs: OK(%u)\n", n);
  n = test_uni_16xf32 (jbm_16xf32_cbrt, cbrtf, -FLT_MAX, FLT_MAX);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cbrt: OK(%u)\n", n);
  n = test_16xf32_log (jbm_16xf32_exp2, exp2f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp2: OK(%u)\n", n);
  n = test_16xf32_log (jbm_16xf32_exp, expf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp: OK(%u)\n", n);
  n = test_16xf32_log (jbm_16xf32_exp10, exp10f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp10: OK(%u)\n", n);
  n = test_16xf32_log (jbm_16xf32_expm1, expm1f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check expm1: OK(%u)\n", n);
  n = test_logn_16xf32 (jbm_16xf32_log2, log2f, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log2: OK(%u)\n", n);
  n = test_logn_16xf32 (jbm_16xf32_log, logf, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log: OK(%u)\n", n);
  n = test_logn_16xf32 (jbm_16xf32_log10, log10f, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log10: OK(%u)\n", n);
  n = test_uni_16xf32 (jbm_16xf32_sin, sinf, -2.f * M_PIf, 2.f * M_PIf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check sin: OK(%u)\n", n);
  n = test_uni_16xf32 (jbm_16xf32_cos, cosf, -2.f * M_PIf, 2.f * M_PIf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cos: OK(%u)\n", n);
  n = test_uni_16xf32 (jbm_16xf32_tan, tanf, -2.f * M_PIf, 2.f * M_PIf);
  if (n == MAX_ITERATIONS)
    printf ("check tan: No\n");
  n = test_16xf32_log (jbm_16xf32_atan, atanf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check atan: OK(%u)\n", n);
  n = test_uni_16xf32 (jbm_16xf32_asin, asinf, -1.f, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check asin: OK(%u)\n", n);
  n = test_uni_16xf32 (jbm_16xf32_acos, acosf, -1.f, 1.f);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check acos: OK(%u)\n", n);
  n = test_16xf32_log (jbm_16xf32_sinh, sinhf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check sinh: OK(%u)\n", n);
  n = test_16xf32_log (jbm_16xf32_cosh, coshf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cosh: OK(%u)\n", n);
  n = test_16xf32_log (jbm_16xf32_tanh, tanhf);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check tanh: OK(%u)\n", n);
  n = test_uni_16xf32 (jbm_16xf32_erf, erff, -FLT_MAX_EXP, FLT_MAX_EXP);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check erf: OK(%u)\n", n);
  n = test_uni_16xf32 (jbm_16xf32_erfc, erfcf, -FLT_MAX_EXP, FLT_MAX_EXP);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check erfc: OK(%u)\n", n);

  printf ("checking __m512d functions\n");
  n = test_uni_8xf64 (jbm_8xf64_abs, fabs, -0.5f * DBL_MAX, 0.5f * DBL_MAX);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check abs: OK(%u)\n", n);
  n = test_uni_8xf64 (jbm_8xf64_cbrt, cbrt, -0.5f * DBL_MAX, 0.5f * DBL_MAX);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cbrt: OK(%u)\n", n);
  n = test_8xf64_log (jbm_8xf64_exp2, exp2);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp2: OK(%u)\n", n);
  n = test_8xf64_log (jbm_8xf64_exp, exp);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp: OK(%u)\n", n);
  n = test_8xf64_log (jbm_8xf64_exp10, exp10);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check exp10: OK(%u)\n", n);
  n = test_8xf64_log (jbm_8xf64_expm1, expm1);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check expm1: OK(%u)\n", n);
  n = test_logn_8xf64 (jbm_8xf64_log2, log2, 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log2: OK(%u)\n", n);
  n = test_logn_8xf64 (jbm_8xf64_log, log, 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log: OK(%u)\n", n);
  n = test_logn_8xf64 (jbm_8xf64_log10, log10, 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check log10: OK(%u)\n", n);
  n = test_uni_8xf64 (jbm_8xf64_sin, sin, -2. * M_PI, 2. * M_PI);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check sin: OK(%u)\n", n);
  n = test_uni_8xf64 (jbm_8xf64_cos, cos, -2. * M_PI, 2. * M_PI);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cos: OK(%u)\n", n);
  n = test_uni_8xf64 (jbm_8xf64_tan, tan, -2. * M_PI, 2. * M_PI);
  if (n == MAX_ITERATIONS)
    printf ("check tan: No\n");
  n = test_8xf64_log (jbm_8xf64_atan, atan);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check atan: OK(%u)\n", n);
  n = test_uni_8xf64 (jbm_8xf64_asin, asin, -1., 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check asin: OK(%u)\n", n);
  n = test_uni_8xf64 (jbm_8xf64_acos, acos, -1., 1.);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check acos: OK(%u)\n", n);
  n = test_8xf64_log (jbm_8xf64_sinh, sinh);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check sinh: OK(%u)\n", n);
  n = test_8xf64_log (jbm_8xf64_cosh, cosh);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check cosh: OK(%u)\n", n);
  n = test_8xf64_log (jbm_8xf64_tanh, tanh);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check tanh: OK(%u)\n", n);
  n = test_uni_8xf64 (jbm_8xf64_erf, erf, -DBL_MAX_EXP, DBL_MAX_EXP);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check erf: OK(%u)\n", n);
  n = test_uni_8xf64 (jbm_8xf64_erfc, erfc, -DBL_MAX_EXP, DBL_MAX_EXP);
  if (n == MAX_ITERATIONS)
    return 1;
  printf ("check erfc: OK(%u)\n", n);

#endif

  // tests
  xf = jbm_f32_mod (2.f, -2.f);
  printf ("mod(2,-2)=%g\n", xf);
  xf = jbm_f32_mod (-2.f, 2.f);
  printf ("mod(-2,2)=%g\n", xf);
  xf = jbm_f32_mod (87.f, 4.f);
  printf ("mod(87,4)=%g\n", xf);
  xf = jbm_f32_mod (-87.f, 4.f);
  printf ("mod(-87,4)=%g\n", xf);
  xf = jbm_f32_frexp (2.f, &i);
  yf = frexpf (2.f, &is);
  printf ("frexp(2)=%.8g*2^(%d)=%.8g*2^(%d)\n", xf, i, yf, is);
  printf ("ldexp(%.8g,%d)=%.8g=%.8g\n",
          xf, i, jbm_f32_ldexp (xf, i), ldexpf (yf, is));
  xf = jbm_f32_frexp (2.5f, &i);
  yf = frexpf (2.5f, &is);
  printf ("frexp(2.5)=%.8g*2^(%d)=%.8g*2^(%d)\n", xf, i, yf, is);
  printf ("ldexp(%.8g,%d)=%.8g=%.8g\n",
          xf, i, jbm_f32_ldexp (xf, i), ldexpf (yf, is));
  xf = jbm_f32_frexp (2501.f, &i);
  yf = frexpf (2501.f, &is);
  printf ("frexp(2501)=%.8g*2^(%d)=%.8g*2^(%d)\n", xf, i, yf, is);
  printf ("ldexp(%.8g,%d)=%.8g=%.8g\n",
          xf, i, jbm_f32_ldexp (xf, i), ldexpf (yf, is));
  xf = jbm_f32_frexp (1e-16f, &i);
  yf = frexpf (1e-16f, &is);
  printf ("frexp(1e-16)=%.8g*2^(%d)=%.8g*2^(%d)\n", xf, i, yf, is);
  printf ("ldexp(%.8g,%d)=%.8g=%.8g\n",
          xf, i, jbm_f32_ldexp (xf, i), ldexpf (yf, is));
  xf = jbm_f32_frexp (1e-40f, &i);
  yf = frexpf (1e-40f, &is);
  printf ("frexp(1e-40)=%.8g*2^(%d)=%.8g*2^(%d)\n", xf, i, yf, is);
  printf ("ldexp(%.8g,%d)=%.8g=%.8g\n",
          xf, i, jbm_f32_ldexp (xf, i), ldexpf (yf, is));
  xf = jbm_f32_frexp (1e-45f, &i);
  yf = frexpf (1e-45f, &is);
  printf ("frexp(1e-45)=%.8g*2^(%d)=%.8g*2^(%d)\n", xf, i, yf, is);
  printf ("ldexp(%.8g,%d)=%.8g=%.8g\n",
          xf, i, jbm_f32_ldexp (xf, i), ldexpf (yf, is));
  xf = jbm_f32_frexp (1e-44f, &i);
  yf = frexpf (1e-44f, &is);
  printf ("frexp(1e-44)=%.8g*2^(%d)=%.8g*2^(%d)\n", xf, i, yf, is);
  printf ("ldexp(%.8g,%d)=%.8g=%.8g\n",
          xf, i, jbm_f32_ldexp (xf, i), ldexpf (yf, is));
  xf = jbm_f32_frexp (0.f, &i);
  yf = frexpf (0.f, &is);
  printf ("frexp(0)=%.8g*2^(%d)=%.8g*2^(%d)\n", xf, i, yf, is);
  printf ("ldexp(%.8g,%d)=%.8g=%.8g\n",
          xf, i, jbm_f32_ldexp (xf, i), ldexpf (yf, is));
  xf = jbm_f32_frexp (-2.f, &i);
  printf ("frexp(-2)=%.8g*2^(%d)\n", xf, i);
  printf ("ldexp(%.8g,%d)=%.8g\n", xf, i, jbm_f32_ldexp (xf, i));
  xf = jbm_f32_frexp (-2.5f, &i);
  printf ("frexp(-2.5)=%.8g*2^(%d)\n", xf, i);
  printf ("ldexp(%.8g,%d)=%.8g\n", xf, i, jbm_f32_ldexp (xf, i));
  xf = jbm_f32_frexp (-2501.f, &i);
  printf ("frexp(-2501)=%.8g*2^(%d)\n", xf, i);
  printf ("ldexp(%.8g,%d)=%.8g\n", xf, i, jbm_f32_ldexp (xf, i));
  xf = jbm_f32_frexp (-1e-16f, &i);
  printf ("frexp(-1e-16)=%.8g*2^(%d)\n", xf, i);
  printf ("ldexp(%.8g,%d)=%.8g\n", xf, i, jbm_f32_ldexp (xf, i));
  xf = jbm_f32_frexp (-1e-40f, &i);
  printf ("frexp(-1e-40)=%.8g*2^(%d)\n", xf, i);
  printf ("ldexp(%.8g,%d)=%.8g\n", xf, i, jbm_f32_ldexp (xf, i));
  xf = jbm_f32_frexp (0.f, &i);
  printf ("frexp(-0)=%.8g*2^(%d)\n", xf, i);
  printf ("ldexp(%.8g,%d)=%.8g\n", xf, i, jbm_f32_ldexp (xf, i));
  printf ("exp2n(128)=%.8g\n", jbm_f32_exp2n (128));
  printf ("exp2n(-160)=%.8g\n", jbm_f32_exp2n (-160));
  printf ("exp2n(2)=%.8g\n", jbm_f32_exp2n (2));
  printf ("exp2n(-140)=%.8g\n", jbm_f32_exp2n (-140));
  printf ("exp2(-160)=%.8g\n", jbm_f32_exp2 (-150.f));
  printf ("exp2(-130)=%.8g\n", jbm_f32_exp2 (-130.f));
  printf ("exp2(-53)=%.8g\n", jbm_f32_exp2 (-53.f));
  printf ("exp2(0)=%.8g\n", jbm_f32_exp2 (0.f));
  printf ("exp2(53)=%.8g\n", jbm_f32_exp2 (53.f));
  printf ("exp2(127)=%.8g\n", jbm_f32_exp2 (127.f));
  printf ("exp2(128)=%.8g\n", jbm_f32_exp2 (128.f));
  printf ("exp(-2)=%.8g\n", jbm_f32_exp (-2.f));
  printf ("exp(0)=%.8g\n", jbm_f32_exp (0.f));
  printf ("exp(2)=%.8g\n", jbm_f32_exp (2.f));
  printf ("exp10(-40)=%.8g\n", jbm_f32_exp10 (-40.f));
  printf ("exp10(-2)=%.8g\n", jbm_f32_exp10 (-2.f));
  printf ("exp10(0)=%.8g\n", jbm_f32_exp10 (0.f));
  printf ("exp10(2)=%.8g\n", jbm_f32_exp10 (2.f));
  printf ("expm1(-2)=%.8g\n", jbm_f32_expm1 (-2.f));
  printf ("expm1(-0.1)=%.8g\n", jbm_f32_expm1 (-0.1f));
  printf ("expm1(0)=%.8g\n", jbm_f32_expm1 (0.f));
  printf ("expm1(0.01)=%.8g\n", jbm_f32_expm1 (0.01f));
  printf ("expm1(2)=%.8g\n", jbm_f32_expm1 (2.f));
  printf ("log2(10)=%.8g=%.8g\n", jbm_f32_log2 (10.f), M_LN10f / M_LN2f);
  printf ("log2(e)=%.8g=%.8g\n", jbm_f32_log2 (M_Ef), M_LOG2Ef);
  printf ("log2(1)=%.8g=0\n", jbm_f32_log2 (1.f));
  printf ("log2(1/e)=%.8g=%.8g\n", jbm_f32_log2 (1.f / M_Ef), -M_LOG2Ef);
  printf ("log2(1/10)=%.8g=%.8g\n", jbm_f32_log2 (0.1f), -M_LN10f / M_LN2f);
  printf ("log2(1e-40)=%.8g=%.8g\n", jbm_f32_log2 (1e-40f), log2f (1e-40f));
  printf ("log2(0)=%.8g\n", jbm_f32_log2 (0.f));
  printf ("log2(-1)=%.8g\n", jbm_f32_log2 (-1.f));
  printf ("log(e)=%.8g\n", jbm_f32_log (M_Ef));
  printf ("log(1)=%.8g\n", jbm_f32_log (1.f));
  printf ("log(1/e)=%.8g\n", jbm_f32_log (1.f / M_Ef));
  printf ("log10(10)=%.8g\n", jbm_f32_log10 (10.f));
  printf ("log10(1)=%.8g\n", jbm_f32_log10 (1.f));
  printf ("log10(1/10)=%.8g\n", jbm_f32_log10 (0.1f));
  printf ("log10(1e-40)=%.8g\n", jbm_f32_log10 (1e-40f));
  printf ("pown(10,31)=%.8g\n", jbm_f32_pown (10.f, 31));
  printf ("pown(10,0)=%.8g\n", jbm_f32_pown (10.f, 0));
  printf ("pown(10,-31)=%.8g\n", jbm_f32_pown (10.f, -31));
  printf ("pown(10,-40)=%.8g\n", jbm_f32_pown (10.f, -51));
  printf ("pown(10,-50)=%.8g\n", jbm_f32_pown (10.f, -50));
  printf ("pow(10,40.5)=%.8g\n", jbm_f32_pow (10.f, 40.5f));
  printf ("pow(10,31.5)=%.8g\n", jbm_f32_pow (10.f, 31.5f));
  printf ("pow(10,31)=%.8g\n", jbm_f32_pow (10.f, 31.f));
  printf ("pow(10,0)=%.8g\n", jbm_f32_pow (10.f, 0.f));
  printf ("pow(10,-31)=%.8g\n", jbm_f32_pow (10.f, -31.f));
  printf ("pow(10,-31.5)=%.8g\n", jbm_f32_pow (10.f, -31.5f));
  printf ("pow(10,-40)=%.8g\n", jbm_f32_pow (10.f, -40.f));
  printf ("pow(10,-40.5)=%.8g\n", jbm_f32_pow (10.f, -40.5f));
  printf ("pow(10,-50)=%.8g\n", jbm_f32_pow (10.f, -50.f));
  xf = 0.f;
  printf ("sinwc(0)=%.8le=%.8le\n", sin (xf), jbm_f32_sinwc (xf));
  printf ("coswc(0)=%.8le=%.8le\n", cos (xf), jbm_f32_coswc (xf));
  xf = M_PIf / 6.f;
  printf ("sinwc(pi/6)=%.8le=%.8le\n", sin (xf), jbm_f32_sinwc (xf));
  printf ("coswc(pi/6)=%.8le=%.8le\n", cos (xf), jbm_f32_coswc (xf));
  xf = -M_PIf / 6.f;
  printf ("sinwc(-pi/6)=%.8le=%.8le\n", sin (xf), jbm_f32_sinwc (xf));
  printf ("coswc(-pi/6)=%.8le=%.8le\n", cos (xf), jbm_f32_coswc (xf));
  for (i = 0; i < 13; ++i)
    {
      xf = i * M_PIf / 6.f;
      printf ("sin(%upi/6)=%.8g=%.8g\n", i, sinf (xf), jbm_f32_sin (xf));
      printf ("cos(%upi/6)=%.8g=%.8g\n", i, cosf (xf), jbm_f32_cos (xf));
      printf ("tan(%upi/6)=%.8g=%.8g\n", i, tanf (xf), jbm_f32_tan (xf));
    }
  xf = INFINITY;
  printf ("sin(infinity)=%.8g=%.8g\n", sinf (xf), jbm_f32_sin (xf));
  printf ("cos(infinity)=%.8g=%.8g\n", cosf (xf), jbm_f32_cos (xf));
  printf ("tan(infinity)=%.8g=%.8g\n", tanf (xf), jbm_f32_tan (xf));
  printf ("atan(infinity)=%.8g=%.8g\n", jbm_f32_atan (INFINITY), M_PI_2f);
  printf ("atan(sqrt(3))=%.8g=%.8g\n", jbm_f32_atan (sqrt (3.f)), M_PIf / 3.f);
  printf ("atan(1)=%.8g=%.8g\n", jbm_f32_atan (1.f), M_PI_4f);
  printf ("atan(sqrt(1/3))=%.8g=%.8g\n",
          jbm_f32_atan (1.f / sqrt (3.f)), M_PIf / 6.f);
  printf ("atan(0)=%.8g=0\n", jbm_f32_atan (0.f));
  printf ("atan(-0)=%.8g=-0\n", jbm_f32_atan (-0.f));
  printf ("atan(-sqrt(1/3))=%.8g=%.8g\n",
          jbm_f32_atan (-1.f / sqrt (3.f)), -M_PIf / 6.f);
  printf ("atan(-1)=%.8g=%.8g\n", jbm_f32_atan (-1.f), -M_PI_4f);
  printf ("atan(-sqrt(3))=%.8g=%.8g\n",
          jbm_f32_atan (-sqrt (3.f)), -M_PIf / 3.f);
  printf ("atan(-infinity)=%.8g=%.8g\n", jbm_f32_atan (-INFINITY), -M_PI_2f);
  printf ("atan2(1,1)=%.8g=%.8g\n", jbm_f32_atan2 (1.f, 1.f), M_PI_4f);
  printf ("atan2(1,-1)=%.8g=%.8g\n", jbm_f32_atan2 (1.f, -1.f), 3.f * M_PI_4f);
  printf ("atan2(-1,1)=%.8g=%.8g\n", jbm_f32_atan2 (-1.f, 1.f), -M_PI_4f);
  printf ("atan2(-1,-1)=%.8g=%.8g\n",
          jbm_f32_atan2 (-1.f, -1.f), -3.f * M_PI_4f);
  printf ("asin(1)=%.8g=%.8g\n", jbm_f32_asin (1.f), M_PI_2f);
  printf ("asin(1/2)=%.8g=%.8g\n", jbm_f32_asin (0.5f), M_PIf / 6.f);
  printf ("asin(0)=%.8g=0\n", jbm_f32_asin (0.f));
  printf ("asin(-1/2)=%.8g=%.8g\n", jbm_f32_asin (-0.5f), -M_PIf / 6.f);
  printf ("asin(-1)=%.8g=%.8g\n", jbm_f32_asin (-1.f), -M_PI_2f);
  printf ("acos(1)=%.8g=0\n", jbm_f32_acos (1.f));
  printf ("acos(1/2)=%.8g=%.8g\n", jbm_f32_acos (0.5f), M_PIf / 3.f);
  printf ("acos(0)=%.8g=%.8g\n", jbm_f32_acos (0.f), M_PI_2f);
  printf ("acos(-1/2)=%.8g=%.8g\n", jbm_f32_acos (-0.5f), 2.f * M_PIf / 3.);
  printf ("acos(-1)=%.8g=%.8g\n", jbm_f32_acos (-1.f), M_PIf);
  printf ("sinh(-1)=%.8g\n", jbm_f32_sinh (-1.f));
  printf ("sinh(0)=%.8g\n", jbm_f32_sinh (0.f));
  printf ("sinh(1)=%.8g\n", jbm_f32_sinh (1.f));
  printf ("cosh(-1)=%.8g\n", jbm_f32_cosh (-1.f));
  printf ("cosh(0)=%.8g\n", jbm_f32_cosh (0.f));
  printf ("cosh(1)=%.8g\n", jbm_f32_cosh (1.f));
  printf ("tanh(-inf)=%.8g\n", jbm_f32_tanh (-INFINITY));
  printf ("tanh(-1)=%.8g\n", jbm_f32_tanh (-1.f));
  printf ("tanh(0)=%.8g\n", jbm_f32_tanh (0.f));
  printf ("tanh(1)=%.8g\n", jbm_f32_tanh (1.f));
  printf ("tanh(inf)=%.8g\n", jbm_f32_tanh (INFINITY));
  printf ("erf(10)=%.8g=%.8g\n", jbm_f32_erf (10.f), erff (10.f));
  printf ("erf(3/2)=%.8g=%.8g\n", jbm_f32_erf (1.5f), erff (1.5f));
  printf ("erf(1/2)=%.8g=%.8g\n", jbm_f32_erf (0.5f), erff (0.5f));
  printf ("erf(0)=%.8g=%.8g\n", jbm_f32_erf (0.f), erff (0.f));
  printf ("erf(-1/2)=%.8g=%.8g\n", jbm_f32_erf (-0.5f), erff (-0.5f));
  printf ("erf(-3/2)=%.8g=%.8g\n", jbm_f32_erf (-1.5f), erff (-1.5f));
  printf ("erf(-10)=%.8g=%.8g\n", jbm_f32_erf (-10.f), erff (-10.f));
  printf ("erfc(10)=%.8g=%.8g\n", jbm_f32_erfc (10.f), erfcf (10.f));
  printf ("erfc(3/2)=%.8g=%.8g\n", jbm_f32_erfc (1.5f), erfcf (1.5f));
  printf ("erfc(1/2)=%.8g=%.8g\n", jbm_f32_erfc (0.5f), erfcf (0.5f));
  printf ("erfc(0)=%.8g=%.8g\n", jbm_f32_erfc (0.f), erfcf (0.f));
  printf ("erfc(-1/2)=%.8g=%.8g\n", jbm_f32_erfc (-0.5f), erfcf (-0.5f));
  printf ("erfc(-3/2)=%.8g=%.8g\n", jbm_f32_erfc (-1.5f), erfcf (-1.5f));
  printf ("erfc(-10)=%.8g=%.8g\n", jbm_f32_erfc (-10.f), erfcf (-10.f));

  printf ("Checking 64 bits functions\n");
  x = jbm_f64_mod (2., -2.);
  printf ("mod(2,-2)=%lg\n", x);
  x = jbm_f64_mod (-2., 2.);
  printf ("mod(-2,2)=%lg\n", x);
  x = jbm_f64_mod (87., 4.);
  printf ("mod(87,4)=%lg\n", x);
  x = jbm_f64_mod (-87., 4.);
  printf ("mod(-87,4)=%lg\n", x);
  x = jbm_f64_frexp (2., &i);
  y = frexp (2., &is);
  printf ("frexp(2)=%.17lg*2^(%d)=%.17lg*2^(%d)\n", x, i, y, is);
  printf ("ldexp(%.17lg,%d)=%.17lg=%.17lg\n",
          x, i, jbm_f64_ldexp (x, i), ldexp (y, is));
  x = jbm_f64_frexp (2.5, &i);
  y = frexp (2.5, &is);
  printf ("frexp(2.5)=%.17lg*2^(%d)=%.17lg*2^(%d)\n", x, i, y, is);
  printf ("ldexp(%.17lg,%d)=%.17lg=%.17lg\n",
          x, i, jbm_f64_ldexp (x, i), ldexp (y, is));
  x = jbm_f64_frexp (2501., &i);
  y = frexp (2501., &is);
  printf ("frexp(2501)=%.17lg*2^(%d)=%.17lg*2^(%d)\n", x, i, y, is);
  printf ("ldexp(%.17lg,%d)=%.17lg=%.17lg\n",
          x, i, jbm_f64_ldexp (x, i), ldexp (y, is));
  x = jbm_f64_frexp (1e-16, &i);
  y = frexp (1e-16, &is);
  printf ("frexp(1e-16)=%.17lg*2^(%d)=%.17lg*2^(%d)\n", x, i, y, is);
  printf ("ldexp(%.17lg,%d)=%.17lg=%.17lg\n",
          x, i, jbm_f64_ldexp (x, i), ldexp (y, is));
  x = jbm_f64_frexp (1e-320, &i);
  y = frexp (1e-320, &is);
  printf ("frexp(1e-320)=%.17lg*2^(%d)=%.17lg*2^(%d)\n", x, i, y, is);
  printf ("ldexp(%.17lg,%d)=%.17lg=%.17lg\n",
          x, i, jbm_f64_ldexp (x, i), ldexp (y, is));
  x = jbm_f64_frexp (0., &i);
  y = frexp (0., &is);
  printf ("frexp(0)=%.17lg*2^(%d)=%.17lg*2^(%d)\n", x, i, y, is);
  printf ("ldexp(%.17lg,%d)=%.17lg=%.17lg\n",
          x, i, jbm_f64_ldexp (x, i), ldexp (y, is));
  x = jbm_f64_frexp (-2., &i);
  printf ("frexp(-2.)=%lg*2^(%d)\n", x, i);
  printf ("ldexp(%lg,%d)=%lg\n", x, i, jbm_f64_ldexp (x, i));
  x = jbm_f64_frexp (-2.5, &i);
  printf ("frexp(-2.5)=%lg*2^(%d)\n", x, i);
  printf ("ldexp(%lg,%d)=%lg\n", x, i, jbm_f64_ldexp (x, i));
  x = jbm_f64_frexp (-2501., &i);
  printf ("frexp(-2501)=%lg*2^(%d)\n", x, i);
  printf ("ldexp(%lg,%d)=%lg\n", x, i, jbm_f64_ldexp (x, i));
  x = jbm_f64_frexp (-1e-16, &i);
  printf ("frexp(-1e-16)=%lg*2^(%d)\n", x, i);
  printf ("ldexp(%lg,%d)=%lg\n", x, i, jbm_f64_ldexp (x, i));
  x = jbm_f64_frexp (-1e-320, &i);
  printf ("frexp(-1e-320)=%lg*2^(%d)\n", x, i);
  printf ("ldexp(%lg,%d)=%lg\n", x, i, jbm_f64_ldexp (x, i));
  x = jbm_f64_frexp (-0., &i);
  printf ("frexp(-0)=%lg*2^(%d)\n", x, i);
  printf ("ldexp(%lg,%d)=%lg\n", x, i, jbm_f64_ldexp (x, i));
  printf ("exp2n(1025)=%lg\n", jbm_f64_exp2n (1025));
  printf ("exp2n(-1075)=%lg\n", jbm_f64_exp2n (-1075));
  printf ("exp2n(2)=%lg\n", jbm_f64_exp2n (2));
  printf ("exp2n(-1024)=%lg\n", jbm_f64_exp2n (-1024));
  printf ("exp2(-1100)=%.17lg\n", jbm_f64_exp2 (-1100.));
  printf ("exp2(-1063)=%.17lg\n", jbm_f64_exp2 (-1063.));
  printf ("exp2(-53)=%.17lg\n", jbm_f64_exp2 (-53.));
  printf ("exp2(0)=%.17lg\n", jbm_f64_exp2 (0.));
  printf ("exp2(53)=%.17lg\n", jbm_f64_exp2 (53.));
  printf ("exp2(1023)=%.17lg\n", jbm_f64_exp2 (1023.));
  printf ("exp2(1024)=%.17lg\n", jbm_f64_exp2 (1024.));
  printf ("exp(-2)=%.17lg\n", jbm_f64_exp (-2.));
  printf ("exp(0)=%.17lg\n", jbm_f64_exp (0.));
  printf ("exp(2)=%.17lg\n", jbm_f64_exp (2.));
  printf ("exp10(-320)=%.17lg\n", jbm_f64_exp10 (-320.));
  printf ("exp10(-2)=%.17lg\n", jbm_f64_exp10 (-2.));
  printf ("exp10(0)=%.17lg\n", jbm_f64_exp10 (0.));
  printf ("exp10(2)=%.17lg\n", jbm_f64_exp10 (2.));
  printf ("expm1(-2)=%.17lg\n", jbm_f64_expm1 (-2.));
  printf ("expm1(-0.1)=%.17lg\n", jbm_f64_expm1 (-0.1));
  printf ("expm1(0)=%.17lg\n", jbm_f64_expm1 (0.));
  printf ("expm1(0.01)=%.17lg\n", jbm_f64_expm1 (0.01));
  printf ("expm1(2)=%.17lg\n", jbm_f64_expm1 (2.));
  printf ("log2(e)=%.17lg=%.17lg\n", jbm_f64_log2 (M_E), M_LOG2E);
  printf ("log2(1)=%.17lg\n", jbm_f64_log2 (1.));
  printf ("log2(1/e)=%.17lg=%.17lg\n", jbm_f64_log2 (1. / M_E), -M_LOG2E);
  printf ("log2(1/10)=%.17lg=%.17lg\n", jbm_f64_log2 (0.1), -M_LN10 / M_LN2);
  printf ("log2(1e-320)=%.17lg\n", jbm_f64_log2 (1e-320));
  printf ("log2(0)=%.17lg\n", jbm_f64_log2 (0.));
  printf ("log2(-1)=%.17lg\n", jbm_f64_log2 (-1.));
  printf ("log(1)=%.17lg\n", jbm_f64_log (1.));
  printf ("log(1/e)=%.17lg\n", jbm_f64_log (1. / M_E));
  printf ("log10(1)=%.17lg\n", jbm_f64_log10 (1.));
  printf ("log10(1/10)=%.17lg\n", jbm_f64_log10 (0.1));
  printf ("log10(1e-320)=%.17lg\n", jbm_f64_log10 (1e-320));
  printf ("pown(10,31)=%.17lg\n", jbm_f64_pown (10., 31));
  printf ("pown(10,0)=%.17lg\n", jbm_f64_pown (10., 0));
  printf ("pown(10,-31)=%.17lg\n", jbm_f64_pown (10., -31));
  printf ("pown(10,-321)=%.17lg\n", jbm_f64_pown (10., -321));
  printf ("pown(10,-400)=%.17lg\n", jbm_f64_pown (10., -400));
  printf ("pow(10,321.5)=%.17lg\n", jbm_f64_pow (10., 321.5));
  printf ("pow(10,31.5)=%.17lg\n", jbm_f64_pow (10., 31.5));
  printf ("pow(10,31)=%.17lg\n", jbm_f64_pow (10., 31.));
  printf ("pow(10,0)=%.17lg\n", jbm_f64_pow (10., 0.));
  printf ("pow(10,-31)=%.17lg\n", jbm_f64_pow (10., -31.));
  printf ("pow(10,-31.5)=%.17lg\n", jbm_f64_pow (10., -31.5));
  printf ("pow(10,-321)=%.17lg\n", jbm_f64_pow (10., -321.));
  printf ("pow(10,-321.5)=%.17lg\n", jbm_f64_pow (10., -321.5));
  printf ("pow(10,-400.5)=%.17lg\n", jbm_f64_pow (10., -400.5));
  x = 0.;
  printf ("sinwc(0)=%.17lg=%.17lg\n", sin (x), jbm_f64_sinwc (x));
  printf ("coswc(0)=%.17lg=%.17lg\n", cos (x), jbm_f64_coswc (x));
  x = M_PI / 6.;
  printf ("sinwc(pi/6)=%.17lg=%.17lg\n", sin (x), jbm_f64_sinwc (x));
  printf ("coswc(pi/6)=%.17lg=%.17lg\n", cos (x), jbm_f64_coswc (x));
  x = -M_PI / 6.;
  printf ("sinwc(-pi/6)=%.17lg=%.17lg\n", sin (x), jbm_f64_sinwc (x));
  printf ("coswc(-pi/6)=%.17lg=%.17lg\n", cos (x), jbm_f64_coswc (x));
  for (i = 0; i < 13; ++i)
    {
      x = i * M_PI / 6.;
      printf ("sin(%upi/6)=%.17lg=%.17lg\n", i, sin (x), jbm_f64_sin (x));
      printf ("cos(%upi/6)=%.17lg=%.17lg\n", i, cos (x), jbm_f64_cos (x));
      printf ("tan(%upi/6)=%.17lg=%.17lg\n", i, tan (x), jbm_f64_tan (x));
    }
  x = INFINITY;
  printf ("sin(infinity)=%.17lg=%.17lg\n", sin (x), jbm_f64_sin (x));
  printf ("cos(infinity)=%.17lg=%.17lg\n", cos (x), jbm_f64_cos (x));
  printf ("tan(infinity)=%.17lg=%.17lg\n", tan (x), jbm_f64_tan (x));
  printf ("atan(infinity)=%.17lg=%.17lg\n", jbm_f64_atan (INFINITY), M_PI_2);
  printf ("atan(sqrt(3))=%.17lg=%.17lg\n", jbm_f64_atan (sqrt (3.)), M_PI / 3.);
  printf ("atan(1)=%.17lg=%.17lg\n", jbm_f64_atan (1.), M_PI_4);
  printf ("atan(sqrt(1/3))=%.17lg=%.17lg\n",
          jbm_f64_atan (1. / sqrt (3.)), M_PI / 6.);
  printf ("atan(0)=%.17lg=0\n", jbm_f64_atan (0.));
  printf ("atan(-0)=%.17lg=-0\n", jbm_f64_atan (-0.));
  printf ("atan(-sqrt(1/3))=%.17lg=%.17lg\n",
          jbm_f64_atan (-1. / sqrt (3.)), -M_PI / 6.);
  printf ("atan(-1)=%.17lg=%.17lg\n", jbm_f64_atan (-1.), -M_PI_4);
  printf ("atan(-sqrt(3))=%.17lg=%.17lg\n",
          jbm_f64_atan (-sqrt (3.)), -M_PI / 3.);
  printf ("atan(-infinity)=%.17lg=%.17lg\n", jbm_f64_atan (-INFINITY), -M_PI_2);
  printf ("atan2(1,1)=%.17lg=%.17lg\n", jbm_f64_atan2 (1., 1.), M_PI_4);
  printf ("atan2(1,-1)=%.17lg=%.17lg\n", jbm_f64_atan2 (1., -1.), 3. * M_PI_4);
  printf ("atan2(-1,1)=%.17lg=%.17lg\n", jbm_f64_atan2 (-1., 1.), -M_PI_4);
  printf ("atan2(-1,-1)=%.17lg=%.17lg\n",
          jbm_f64_atan2 (-1., -1.), -3. * M_PI_4);
  printf ("asin(1)=%.17lg=%.17lg\n", jbm_f64_asin (1.), M_PI_2);
  printf ("asin(1/2)=%.17lg=%.17lg\n", jbm_f64_asin (0.5), M_PI / 6.);
  printf ("asin(0)=%.17lg=0\n", jbm_f64_asin (0.));
  printf ("asin(-1/2)=%.17lg=%.17lg\n", jbm_f64_asin (-0.5), -M_PI / 6.);
  printf ("asin(-1)=%.17lg=%.17lg\n", jbm_f64_asin (-1.), -M_PI_2);
  printf ("acos(1)=%.17lg=0\n", jbm_f64_acos (1.));
  printf ("acos(1/2)=%.17lg=%.17lg\n", jbm_f64_acos (0.5), M_PI / 3.);
  printf ("acos(0)=%.17lg=%.17lg\n", jbm_f64_acos (0.), M_PI_2);
  printf ("acos(-1/2)=%.17lg=%.17lg\n", jbm_f64_acos (-0.5), 2. * M_PI / 3.);
  printf ("acos(-1)=%.17lg=%.17lg\n", jbm_f64_acos (-1.), M_PI);
  printf ("sinh(-1)=%.17lg\n", jbm_f64_sinh (-1.));
  printf ("sinh(0)=%.17lg\n", jbm_f64_sinh (0.));
  printf ("sinh(1)=%.17lg\n", jbm_f64_sinh (1.));
  printf ("cosh(-1)=%.17lg\n", jbm_f64_cosh (-1.));
  printf ("cosh(0)=%.17lg\n", jbm_f64_cosh (0.));
  printf ("cosh(1)=%.17lg\n", jbm_f64_cosh (1.));
  printf ("tanh(-inf)=%.17lg\n", jbm_f64_tanh (-INFINITY));
  printf ("tanh(-1)=%.17lg\n", jbm_f64_tanh (-1.));
  printf ("tanh(0)=%.17lg\n", jbm_f64_tanh (0.));
  printf ("tanh(1)=%.17lg\n", jbm_f64_tanh (1.));
  printf ("tanh(inf)=%.17lg\n", jbm_f64_tanh (INFINITY));
  printf ("erf(10)=%.17lg=%.17lg\n", jbm_f64_erf (10.), erf (10.));
  printf ("erf(3/2)=%.17lg=%.17lg\n", jbm_f64_erf (1.5), erf (1.5));
  printf ("erf(1/2)=%.17lg=%.17lg\n", jbm_f64_erf (0.5), erf (0.5));
  printf ("erf(0)=%.17lg=%.17lg\n", jbm_f64_erf (0.), erf (0.));
  printf ("erf(-1/2)=%.17lg=%.17lg\n", jbm_f64_erf (-0.5), erf (-0.5));
  printf ("erf(-3/2)=%.17lg=%.17lg\n", jbm_f64_erf (-1.5), erf (-1.5));
  printf ("erf(-10)=%.17lg=%.17lg\n", jbm_f64_erf (-10.), erf (-10.));
  printf ("erfc(10)=%.17lg=%.17lg\n", jbm_f64_erfc (10.), erfc (10.));
  printf ("erfc(3/2)=%.17lg=%.17lg\n", jbm_f64_erfc (1.5), erfc (1.5));
  printf ("erfc(1/2)=%.17lg=%.17lg\n", jbm_f64_erfc (0.5), erfc (0.5));
  printf ("erfc(0)=%.17lg=%.17lg\n", jbm_f64_erfc (0.), erfc (0.));
  printf ("erfc(-1/2)=%.17lg=%.17lg\n", jbm_f64_erfc (-0.5), erfc (-0.5));
  printf ("erfc(-3/2)=%.17lg=%.17lg\n", jbm_f64_erfc (-1.5), erfc (-1.5));
  printf ("erfc(-10)=%.17lg=%.17lg\n", jbm_f64_erfc (-10.), erfc (-10.));

  for (i = 0; i < 3; ++i)
    cf[i].C = Cf[i], cf[i].E = Ef[i];
  for (i = 0; i < 4; ++i)
    cf[i].D = Df[i], cf[i].H = Hf[i];
  for (i = 0; i < 4; ++i)
    czf[i].C = Czf[i], czf[i].E = Ezf[i];
  for (i = 0; i < 5; ++i)
    czf[i].D = Dzf[i], czf[i].H = Hzf[i];
  for (i = 0; i < 3; ++i)
    cd[i].C = Cd[i], cd[i].E = Ed[i];
  for (i = 0; i < 4; ++i)
    cd[i].D = Dd[i], cd[i].H = Hd[i];
  for (i = 0; i < 4; ++i)
    czd[i].C = Czd[i], czd[i].E = Ezd[i];
  for (i = 0; i < 5; ++i)
    czd[i].D = Dzd[i], czd[i].H = Hzd[i];
  is = jbm_min (1, -1);
  printf ("min(1,-1)=%d\n", is);
  is = jbm_max (1, -1);
  printf ("max(1,-1)=%d\n", is);
  is = jbm_modmin (1, -1);
  printf ("modmin(1,-1)=%d\n", is);
  is = jbm_modmin (1, 2);
  printf ("modmin(1,2)=%d\n", is);
  is = jbm_modmin (-2, -1);
  printf ("modmin(-2,-1)=%d\n", is);
  is = jbm_dbl (1);
  printf ("dbl(1)=%d\n", is);
  is = jbm_sqr (-1);
  printf ("sqr(-1)=%d\n", is);
  is = 1, is2 = -1;
  jbm_change (&is, &is2);
  printf ("change(1,-1)=(%d,%d)\n", is, is2);
  us = jbm_minu (1, 2);
  printf ("minu(1,2)=%u\n", us);
  us = jbm_maxu (1, 2);
  printf ("maxu(1,2)=%u\n", us);
  us = jbm_dblu (1);
  printf ("dblu(1)=%u\n", us);
  us = jbm_sqru (1);
  printf ("sqru(1)=%u\n", us);
  us = 1, us2 = 2;
  jbm_changeu (&us, &us2);
  printf ("changeu(1,2)=(%u,%u)\n", us, us2);
  il = jbm_minl (1l, -1l);
  printf ("minl(1l,-1l)=%ld\n", il);
  il = jbm_maxl (1l, -1l);
  printf ("maxl(1l,-1l)=%ld\n", il);
  il = jbm_modminl (1l, -1l);
  printf ("modminl(1l,-1l)=%ld\n", il);
  il = jbm_modminl (1l, 2l);
  printf ("modminl(1l,2l)=%ld\n", il);
  il = jbm_modminl (-2l, -1l);
  printf ("modminl(-2l,-1l)=%ld\n", il);
  il = jbm_dbll (1l);
  printf ("dbll(1l)=%ld\n", il);
  il = jbm_sqrl (-1l);
  printf ("sqrl(-1l)=%ld\n", il);
  il = 1l, il2 = -1l;
  jbm_changel (&il, &il2);
  printf ("changel(1l,-1l)=(%ld,%ld)\n", il, il2);
  ul = jbm_minul (1l, 2l);
  printf ("minul(1l,2l)=%lu\n", ul);
  ul = jbm_maxul (1l, 2l);
  printf ("maxul(1l,2l)=%lu\n", ul);
  ul = jbm_dblul (1l);
  printf ("dblul(1l)=%lu\n", ul);
  ul = jbm_sqrul (1l);
  printf ("sqrul(1l)=%lu\n", ul);
  ul = 1l, ul2 = 2l;
  jbm_changeul (&ul, &ul2);
  printf ("changeul(1l,2l)=(%lu,%lu)\n", ul, ul2);
  iL = jbm_minll (1L, -1L);
  printf ("minll(1L,-1L)=%lld\n", iL);
  iL = jbm_maxll (1L, -1L);
  printf ("maxll(1L,-1L)=%lld\n", iL);
  iL = jbm_modminll (1L, -1L);
  printf ("modminll(1L,-1L)=%lld\n", iL);
  iL = jbm_modminll (1L, 2L);
  printf ("modminll(1L,2L)=%lld\n", iL);
  iL = jbm_modminll (-2L, -1L);
  printf ("modminll(-2L,-1L)=%lld\n", iL);
  iL = jbm_dblll (1L);
  printf ("dbll((1L)=%lld\n", iL);
  iL = jbm_sqrll (-1L);
  printf ("sqrll(-1L)=%lld\n", iL);
  iL = 1L, iL2 = -1L;
  jbm_changell (&iL, &iL2);
  printf ("changell(1L,-1L)=(%lld,%lld)\n", iL, iL2);
  uL = jbm_minull (1L, 2L);
  printf ("minull(1L,2L)=%llu\n", uL);
  uL = jbm_maxull (1L, 2L);
  printf ("maxull(1L,2L)=%llu\n", uL);
  uL = jbm_dblull (1L);
  printf ("dbLull(1L)=%llu\n", uL);
  uL = jbm_sqrull (1L);
  printf ("sqrull(1L)=%llu\n", uL);
  uL = 1L, uL2 = 2L;
  jbm_changeull (&uL, &uL2);
  printf ("changeull(1L,2L)=(%llu,%llu)\n", uL, uL2);
  printf ("small(0)=%d\n", jbm_small ((JBFLOAT) 0.));
  printf ("small(1)=%d\n", jbm_small ((JBFLOAT) 1.));
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_fmodmin ((JBFLOAT) 1., (JBFLOAT) 2.));
  printf ("fmodmin(1,2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_fmodmin ((JBFLOAT) - 1., (JBFLOAT) - 2.));
  printf ("fmodmin(-1,-2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_fmodmin ((JBFLOAT) 1., (JBFLOAT) - 2.));
  printf ("fmodmin(1,-2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_fdbl ((JBFLOAT) 1.));
  printf ("fdbl(1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_fsqr ((JBFLOAT) - 2.));
  printf ("fsqr(-2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_extrapolate ((JBFLOAT) 0., (JBFLOAT) 1., (JBFLOAT) - 2.,
                             (JBFLOAT) 3., (JBFLOAT) 2.));
  printf ("extrapolate(0,1,-2,3,2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_interpolate ((JBFLOAT) 0., (JBFLOAT) - 2., (JBFLOAT) 1.,
                             (JBFLOAT) 3., (JBFLOAT) 2.));
  printf ("interpolate(0,-2,1,3,2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_interpolate ((JBFLOAT) 1., (JBFLOAT) - 2., (JBFLOAT) 0.,
                             (JBFLOAT) 3., (JBFLOAT) 2.));
  printf ("interpolate(1,-2,0,3,2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_interpolate ((JBFLOAT) - 2., (JBFLOAT) 0., (JBFLOAT) 1.,
                             (JBFLOAT) 3., (JBFLOAT) 2.));
  printf ("interpolate(-2,0,1,3,2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_v2_length ((JBFLOAT) 0., (JBFLOAT) 1., (JBFLOAT) - 2.,
                           (JBFLOAT) 3.));
  printf ("v2_length(0,1,-2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_v3_length ((JBFLOAT) 0., (JBFLOAT) 1., (JBFLOAT) - 2.,
                           (JBFLOAT) 3., (JBFLOAT) 2., (JBFLOAT) - 3.));
  printf ("v3_length(0,1,-2,3,2,-3)=%s\n", buffer);
  f = (JBFLOAT) 1., f2 = (JBFLOAT) - 2.;
  jbm_fchange (&f, &f2);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, f);
  SNPRINTF (buffer2, JB_BUFFER_SIZE, FWF, f2);
  printf ("fchange(1,-2)=(%s,%s)\n", buffer, buffer2);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_polynomial_11 ((JBFLOAT) 0.5, pf));
  printf ("polynomial_11(0.5,pf)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_polynomial_11 ((JBFLOAT) 1., pf));
  printf ("polynomial_11(1,pf)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_solve_quadratic ((JBFLOAT) 2., (JBFLOAT) - 1., (JBFLOAT) - 1.,
                                 (JBFLOAT) 0., (JBFLOAT) 2.));
  printf ("solve_quadratic(2,-1,-1,0,2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_solve_quadratic ((JBFLOAT) 0., (JBFLOAT) - 2., (JBFLOAT) 1.,
                                 (JBFLOAT) 0., (JBFLOAT) 2.));
  printf ("solve_quadratic(0,-2,1,0,2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_solve_cubic ((JBFLOAT) 0.5, (JBFLOAT) 1., (JBFLOAT) 1.,
                             (JBFLOAT) 0.5, (JBFLOAT) - 2., (JBFLOAT) 0.));
  printf ("solve_cubic(0.5,1,1,0.5,-2,0)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_solve_cubic ((JBFLOAT) 0., (JBFLOAT) 2., (JBFLOAT) - 1.,
                             (JBFLOAT) - 1., (JBFLOAT) 0., (JBFLOAT) 2.));
  printf ("solve_cubic(0,2,-1,-1,0,2)=%s\n", buffer);

  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 1., (JBFLOAT) 3.,
                              JBM_FLUX_LIMITER_TYPE_TOTAL));
  printf ("flux_limiter_total(1,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 1., (JBFLOAT) 3.,
                              JBM_FLUX_LIMITER_TYPE_NULL));
  printf ("flux_limiter_null(1,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 1., (JBFLOAT) 3.,
                              JBM_FLUX_LIMITER_TYPE_CENTRED));
  printf ("flux_limiter_centred(1,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 1., (JBFLOAT) 0.,
                              JBM_FLUX_LIMITER_TYPE_CENTRED));
  printf ("flux_limiter_centred(1,0)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) - 1., (JBFLOAT) 1.,
                              JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbee(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 1., (JBFLOAT) 3.,
                              JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbee(1,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 2., (JBFLOAT) 3.,
                              JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbee(2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 3., (JBFLOAT) 2.,
                              JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbee(3,2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 3., (JBFLOAT) 1.,
                              JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbee(3,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) - 1., (JBFLOAT) 1.,
                              JBM_FLUX_LIMITER_TYPE_MINMOD));
  printf ("flux_limiter_minmod(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 2., (JBFLOAT) 3.,
                              JBM_FLUX_LIMITER_TYPE_MINMOD));
  printf ("flux_limiter_minmod(2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 3., (JBFLOAT) 1.,
                              JBM_FLUX_LIMITER_TYPE_MINMOD));
  printf ("flux_limiter_minmod(3,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) - 1., (JBFLOAT) 1.,
                              JBM_FLUX_LIMITER_TYPE_VAN_LEER));
  printf ("flux_limiter_VanLeer(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 2., (JBFLOAT) 3.,
                              JBM_FLUX_LIMITER_TYPE_VAN_LEER));
  printf ("flux_limiter_VanLeer(2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) - 1., (JBFLOAT) 1.,
                              JBM_FLUX_LIMITER_TYPE_VAN_ALBADA));
  printf ("flux_limiter_VanAlbada(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 2., (JBFLOAT) 3.,
                              JBM_FLUX_LIMITER_TYPE_VAN_ALBADA));
  printf ("flux_limiter_VanAlbada(2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) - 1., (JBFLOAT) 1.,
                              JBM_FLUX_LIMITER_TYPE_MINSUPER));
  printf ("flux_limiter_minsuper(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 2., (JBFLOAT) 3.,
                              JBM_FLUX_LIMITER_TYPE_MINSUPER));
  printf ("flux_limiter_minsuper(2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 3., (JBFLOAT) 1.,
                              JBM_FLUX_LIMITER_TYPE_MINSUPER));
  printf ("flux_limiter_minsuper(3,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) - 1., (JBFLOAT) 1.,
                              JBM_FLUX_LIMITER_TYPE_SUPERMIN));
  printf ("flux_limiter_supermin(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 1., (JBFLOAT) 3.,
                              JBM_FLUX_LIMITER_TYPE_SUPERMIN));
  printf ("flux_limiter_supermin(1,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 3., (JBFLOAT) 1.,
                              JBM_FLUX_LIMITER_TYPE_SUPERMIN));
  printf ("flux_limiter_supermin(3,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) - 1., (JBFLOAT) 1.,
                              JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL));
  printf ("flux_limiter_monotonized_central(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 0.5, (JBFLOAT) 3.,
                              JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL));
  printf ("flux_limiter_monotonized_central(0.5,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 2., (JBFLOAT) 3.,
                              JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL));
  printf ("flux_limiter_monotonized_central(2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 3., (JBFLOAT) 0.5,
                              JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL));
  printf ("flux_limiter_monotonized_central(3,0.5)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) - 1., (JBFLOAT) 1.,
                              JBM_FLUX_LIMITER_TYPE_MEAN));
  printf ("flux_limiter_mean(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter ((JBFLOAT) 2., (JBFLOAT) 3.,
                              JBM_FLUX_LIMITER_TYPE_MEAN));
  printf ("flux_limiter_mean(2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_integral (fn0f, (JBFLOAT) 0., (JBFLOAT) 1.));
  printf ("integral(1,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_integral (fn1f, (JBFLOAT) 0., (JBFLOAT) 1.));
  printf ("integral(x,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_integral (fn2f, (JBFLOAT) 0., (JBFLOAT) 1.));
  printf ("integral(x^2,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_integral (fn3f, (JBFLOAT) 0., (JBFLOAT) 1.));
  printf ("integral(x^3,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_integral (fn4f, (JBFLOAT) 0., (JBFLOAT) 1.));
  printf ("integral(x^4,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_integral (fn5f, (JBFLOAT) 0., (JBFLOAT) 1.));
  printf ("integral(x^5,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_integral (fn6f, (JBFLOAT) 0., (JBFLOAT) 1.));
  printf ("integral(x^6,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_integral (fn7f, (JBFLOAT) 0., (JBFLOAT) 1.));
  printf ("integral(x^7,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_integral (fn8f, (JBFLOAT) 0., (JBFLOAT) 1.));
  printf ("integral(x^8,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_integral (fn9f, (JBFLOAT) 0., (JBFLOAT) 1.));
  printf ("integral(x^9,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_integral (fn10f, (JBFLOAT) 0., (JBFLOAT) 1.));
  printf ("integral(x^10,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_integral (fn11f, (JBFLOAT) 0., (JBFLOAT) 1.));
  printf ("integral(x^11,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_integral (fn12f, (JBFLOAT) 0., (JBFLOAT) 1.));
  printf ("integral(x^12,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_integral (fn13f, (JBFLOAT) 0., (JBFLOAT) 1.));
  printf ("integral(x^13,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_integral (fn14f, (JBFLOAT) 0., (JBFLOAT) 1.));
  printf ("integral(x^14,0,1)=%s\n", buffer);
  printf ("smalll(0)=%d\n", jbm_smalll ((JBDOUBLE) 0.));
  printf ("smalll(1)=%d\n", jbm_smalll ((JBDOUBLE) 1.));
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_fmodminl ((JBDOUBLE) 1., (JBDOUBLE) 2.));
  printf ("fmodminl(1,2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_fmodminl ((JBDOUBLE) - 1., (JBDOUBLE) - 2.));
  printf ("fmodminl(-1,-2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_fmodminl ((JBDOUBLE) 1., (JBDOUBLE) - 2.));
  printf ("fmodminl(1,-2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_fdbll ((JBDOUBLE) 1.));
  printf ("fdbll(1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_fsqrl ((JBDOUBLE) - 2.));
  printf ("fsqrl(-2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_extrapolatel ((JBDOUBLE) 0., (JBDOUBLE) 1., (JBDOUBLE) - 2.,
                               (JBDOUBLE) 3., (JBDOUBLE) 2.));
  printf ("extrapolatel(0,1,-2,3,2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_interpolatel ((JBDOUBLE) 0., (JBDOUBLE) - 2., (JBDOUBLE) 1.,
                               (JBDOUBLE) 3., (JBDOUBLE) 2.));
  printf ("interpolatel(0,-2,1,3,2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_interpolatel ((JBDOUBLE) 1., (JBDOUBLE) - 2., (JBDOUBLE) 0.,
                               (JBDOUBLE) 3., (JBDOUBLE) 2.));
  printf ("interpolatel(1,-2,0,3,2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_interpolatel ((JBDOUBLE) - 2., (JBDOUBLE) 0., (JBDOUBLE) 1.,
                               (JBDOUBLE) 3., (JBDOUBLE) 2.));
  printf ("interpolatel(-2,0,1,3,2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_v2_lengthl ((JBDOUBLE) 0., (JBDOUBLE) 1., (JBDOUBLE) - 2.,
                             (JBDOUBLE) 3.));
  printf ("v2_lengthl(0,1,-2,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_v3_lengthl ((JBDOUBLE) 0., (JBDOUBLE) 1., (JBDOUBLE) - 2.,
                             (JBDOUBLE) 3., (JBDOUBLE) 2., (JBDOUBLE) - 3.));
  printf ("v3_lengthl(0,1,-2,3,2,-3)=%s\n", buffer);
  d = (JBDOUBLE) 1., d2 = (JBDOUBLE) - 2.;
  jbm_fchangel (&d, &d2);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, d);
  SNPRINTFL (buffer2, JB_BUFFER_SIZE, FWL, d2);
  printf ("fchangel(1,-2)=(%s,%s)\n", buffer, buffer2);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_polynomial_11l ((JBDOUBLE) 0.5, pd));
  printf ("polynomial_11l(0.5,pd)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_polynomial_11l ((JBDOUBLE) 1., pd));
  printf ("polynomial_11l(1,pd)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_solve_quadraticl ((JBDOUBLE) 2., (JBDOUBLE) - 1.,
                                   (JBDOUBLE) - 1., (JBDOUBLE) 0.,
                                   (JBDOUBLE) 2.));
  printf ("solve_quadraticl(2,-1,-1,0,2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_solve_quadraticl ((JBDOUBLE) 0., (JBDOUBLE) - 2.,
                                   (JBDOUBLE) 1., (JBDOUBLE) 0.,
                                   (JBDOUBLE) 2.));
  printf ("solve_quadraticl(0,-2,1,0,2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_solve_cubicl ((JBDOUBLE) 0.5, (JBDOUBLE) 1., (JBDOUBLE) 1.,
                               (JBDOUBLE) 0.5, (JBDOUBLE) - 2., (JBDOUBLE) 0.));
  printf ("solve_cubicl(0.5,1,1,0.5,-2,0)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_solve_cubicl ((JBDOUBLE) 0., (JBDOUBLE) 2., (JBDOUBLE) - 1.,
                               (JBDOUBLE) - 1., (JBDOUBLE) 0., (JBDOUBLE) 2.));
  printf ("solve_cubicl(0,2,-1,-1,0,2)=%s\n", buffer);

  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 1., (JBDOUBLE) 3.,
                                JBM_FLUX_LIMITER_TYPE_TOTAL));
  printf ("flux_limiter_totall(1,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 1., (JBDOUBLE) 3.,
                                JBM_FLUX_LIMITER_TYPE_NULL));
  printf ("flux_limiter_nulll(1,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 1., (JBDOUBLE) 3.,
                                JBM_FLUX_LIMITER_TYPE_CENTRED));
  printf ("flux_limiter_centredl(1,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 1., (JBDOUBLE) 0.,
                                JBM_FLUX_LIMITER_TYPE_CENTRED));
  printf ("flux_limiter_centredl(1,0)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) - 1., (JBDOUBLE) 1.,
                                JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbeel(-1,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 1., (JBDOUBLE) 3.,
                                JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbeel(1,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 2., (JBDOUBLE) 3.,
                                JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbeel(2,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 3., (JBDOUBLE) 2.,
                                JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbeel(3,2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 3., (JBDOUBLE) 1.,
                                JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbeel(3,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) - 1., (JBDOUBLE) 1.,
                                JBM_FLUX_LIMITER_TYPE_MINMOD));
  printf ("flux_limiter_minmodl(-1,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 2., (JBDOUBLE) 3.,
                                JBM_FLUX_LIMITER_TYPE_MINMOD));
  printf ("flux_limiter_minmodl(2,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 3., (JBDOUBLE) 1.,
                                JBM_FLUX_LIMITER_TYPE_MINMOD));
  printf ("flux_limiter_minmodl(3,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) - 1., (JBDOUBLE) 1.,
                                JBM_FLUX_LIMITER_TYPE_VAN_LEER));
  printf ("flux_limiter_VanLeerl(-1,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 2., (JBDOUBLE) 3.,
                                JBM_FLUX_LIMITER_TYPE_VAN_LEER));
  printf ("flux_limiter_VanLeerl(2,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) - 1., (JBDOUBLE) 1.,
                                JBM_FLUX_LIMITER_TYPE_VAN_ALBADA));
  printf ("flux_limiter_VanAlbadal(-1,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 2., (JBDOUBLE) 3.,
                                JBM_FLUX_LIMITER_TYPE_VAN_ALBADA));
  printf ("flux_limiter_VanAlbadal(2,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) - 1., (JBDOUBLE) 1.,
                                JBM_FLUX_LIMITER_TYPE_MINSUPER));
  printf ("flux_limiter_minsuperl(-1,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 2., (JBDOUBLE) 3.,
                                JBM_FLUX_LIMITER_TYPE_MINSUPER));
  printf ("flux_limiter_minsuperl(2,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 3., (JBDOUBLE) 1.,
                                JBM_FLUX_LIMITER_TYPE_MINSUPER));
  printf ("flux_limiter_minsuperl(3,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) - 1., (JBDOUBLE) 1.,
                                JBM_FLUX_LIMITER_TYPE_SUPERMIN));
  printf ("flux_limiter_superminl(-1,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 1., (JBDOUBLE) 3.,
                                JBM_FLUX_LIMITER_TYPE_SUPERMIN));
  printf ("flux_limiter_superminl(1,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 3., (JBDOUBLE) 1.,
                                JBM_FLUX_LIMITER_TYPE_SUPERMIN));
  printf ("flux_limiter_superminl(3,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) - 1., (JBDOUBLE) 1.,
                                JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL));
  printf ("flux_limiter_monotonized_centrall(-1,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 0.5, (JBDOUBLE) 3.,
                                JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL));
  printf ("flux_limiter_monotonized_centrall(0.5,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 2., (JBDOUBLE) 3.,
                                JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL));
  printf ("flux_limiter_monotonized_centrall(2,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 3., (JBDOUBLE) 0.5,
                                JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL));
  printf ("flux_limiter_monotonized_centrall(3,0.5)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) - 1., (JBDOUBLE) 1.,
                                JBM_FLUX_LIMITER_TYPE_MEAN));
  printf ("flux_limiter_meanl(-1,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_flux_limiterl ((JBDOUBLE) 2., (JBDOUBLE) 3.,
                                JBM_FLUX_LIMITER_TYPE_MEAN));
  printf ("flux_limiter_meanl(2,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_integrall (fn0d, (JBDOUBLE) 0., (JBDOUBLE) 1.));
  printf ("integrall(1,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_integrall (fn1d, (JBDOUBLE) 0., (JBDOUBLE) 1.));
  printf ("integrall(x,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_integrall (fn2d, (JBDOUBLE) 0., (JBDOUBLE) 1.));
  printf ("integrall(x^2,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_integrall (fn3d, (JBDOUBLE) 0., (JBDOUBLE) 1.));
  printf ("integrall(x^3,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_integrall (fn4d, (JBDOUBLE) 0., (JBDOUBLE) 1.));
  printf ("integrall(x^4,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_integrall (fn5d, (JBDOUBLE) 0., (JBDOUBLE) 1.));
  printf ("integrall(x^5,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_integrall (fn6d, (JBDOUBLE) 0., (JBDOUBLE) 1.));
  printf ("integrall(x^6,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_integrall (fn7d, (JBDOUBLE) 0., (JBDOUBLE) 1.));
  printf ("integrall(x^7,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_integrall (fn8d, (JBDOUBLE) 0., (JBDOUBLE) 1.));
  printf ("integrall(x^8,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_integrall (fn9d, (JBDOUBLE) 0., (JBDOUBLE) 1.));
  printf ("integrall(x^9,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_integrall (fn10d, (JBDOUBLE) 0., (JBDOUBLE) 1.));
  printf ("integrall(x^10,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_integrall (fn11d, (JBDOUBLE) 0., (JBDOUBLE) 1.));
  printf ("integrall(x^11,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_integrall (fn12d, (JBDOUBLE) 0., (JBDOUBLE) 1.));
  printf ("integrall(x^12,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_integrall (fn13d, (JBDOUBLE) 0., (JBDOUBLE) 1.));
  printf ("integrall(x^13,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_integrall (fn14d, (JBDOUBLE) 0., (JBDOUBLE) 1.));
  printf ("integrall(x^14,0,1)=%s\n", buffer);

#ifdef __SSE4_2__
  printf ("check SSE 4.2 functions\n");
  d_1 = aligned_alloc (16, 2 * sizeof (double));
  L_1 = (unsigned long long int *) d_1;
  d_2 = aligned_alloc (16, 2 * sizeof (double));
  d_2xf64 = jbm_2xf64_abs (_mm_set_pd (-1., 1));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_abs([1,-1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 = jbm_small_2xf64 (_mm_set_pd (1., 0.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("small_2xf64([0,1])=[%16llx,%16llx]\n", L_1[0], L_1[1]);
  d_2xf64 = jbm_modmin_2xf64 (_mm_set_pd (-1., 1.), _mm_set_pd (-2., 0.5));
  _mm_store_pd (d_1, d_2xf64);
  printf ("modmin_2xf64([1,-1],[0.5,-2])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 = jbm_modmin_2xf64 (_mm_set_pd (1.0, 0.), _mm_set_pd (-2., 1.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("modmin_2xf64([0,1],[1,-2])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 = _mm_set_pd (1., 0.);
  d2_2xf64 = _mm_set_pd (-2., 1.);
  jbm_change_2xf64 (&d_2xf64, &d2_2xf64);
  _mm_store_pd (d_1, d_2xf64);
  _mm_store_pd (d_2, d2_2xf64);
  printf ("change_2xf64([0,1],[1,-2])=([%.17lg,%.17lg],[%.17lg,%.17lg])\n",
          d_1[0], d_1[1], d_2[0], d_2[1]);
  d2_2xf64 = jbm_2xf64_dbl (d_2xf64);
  _mm_store_pd (d_1, d2_2xf64);
  printf ("2xf64_dbl([1,-2])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_sqr (d_2xf64);
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_sqr([1,-2])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_extrapolate (_mm_set_pd (-1., 1.),
                                   _mm_set1_pd (0.),
                                   _mm_set1_pd (2.),
                                   _mm_set1_pd (1.), _mm_set1_pd (4.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_extrapolate([1,-1],[0,0],[2,2],[1,1],[4,4])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_interpolate (_mm_set_pd (-1., 1.),
                                   _mm_set1_pd (0.),
                                   _mm_set1_pd (2.),
                                   _mm_set1_pd (1.), _mm_set1_pd (4.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_interpolate([1,-1],[0,0],[2,2],[1,1],[4,4])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_interpolate (_mm_set_pd (3., 1.),
                                   _mm_set_pd (0., 0.),
                                   _mm_set_pd (2., 2.),
                                   _mm_set_pd (1., 1.), _mm_set_pd (4., 4.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_interpolate([1,3],[0,0],[2,2],[1,1],[4,4])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_v2_length (_mm_set_pd (2., 1.),
                                 _mm_set_pd (-1., 4.),
                                 _mm_set_pd (5., -3.), _mm_set_pd (3., 1.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_v2_length([1,2],[4,-1],[-3,5],[1,3])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_v3_length (_mm_set_pd (2., 1.),
                                 _mm_set_pd (-1., 4.),
                                 _mm_set_pd (1., 3.),
                                 _mm_set_pd (4., -1.),
                                 _mm_set_pd (2., 1.), _mm_set_pd (-5., 9.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_v3_length([1,2],[4,-1],[3,1],[-1,4],[1,2],[9,-5])"
          "=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_polynomial_11 (_mm_set_pd (1., 0.5), p_1);
  _mm_store_pd (d_1, d_2xf64);
  printf
    ("2xf64_polynomial_11([0.5,1],[1,2,4,8,16,32,64,128,256,512,1024,2048])"
     "=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_solve_quadratic (_mm_set_pd (0., 2.), _mm_set_pd (-2., -1.),
                               _mm_set_pd (1., -1.), _mm_set_pd (0., 0.),
                               _mm_set_pd (2., 2.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_solve_quadratic([2,0],[-1,-2][-1,1],[0,0],[2,2])"
          "=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (_mm_setzero_pd (),
                                    _mm_set1_pd (1.),
                                    JBM_FLUX_LIMITER_TYPE_TOTAL);
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_total([0,0],[1,1])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (_mm_setzero_pd (),
                                    _mm_set1_pd (1.),
                                    JBM_FLUX_LIMITER_TYPE_NULL);
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_null([0,0],[1,1])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (_mm_set_pd (3., 1.),
                                    _mm_set_pd (0., 1.),
                                    JBM_FLUX_LIMITER_TYPE_CENTRED);
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_centred([1,3],[1,0])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (_mm_set_pd (1., -1.),
                                    _mm_set_pd (3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_SUPERBEE);
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_superbee([-1,1],[1,3])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (_mm_set_pd (3., 2.),
                                    _mm_set_pd (2., 3.),
                                    JBM_FLUX_LIMITER_TYPE_SUPERBEE);
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_superbee([2,3],[3,2])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (_mm_set_pd (1., 3.),
                                    _mm_set_pd (1., 1.),
                                    JBM_FLUX_LIMITER_TYPE_SUPERBEE);
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_superbee([3,1],[1,1])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (_mm_set_pd (2., -1.),
                                    _mm_set_pd (3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_MINMOD);
  _mm_store_pd (d_1, d_2xf64);
  printf ("flux_limiter_min2xf64_mod([-1,2],[1,3])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (_mm_set_pd (1., 3.),
                                    _mm_set_pd (1., 1.),
                                    JBM_FLUX_LIMITER_TYPE_MINMOD);
  _mm_store_pd (d_1, d_2xf64);
  printf ("flux_limiter_min2xf64_mod([3,1],[1,1])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (_mm_set_pd (2., -1.),
                                    _mm_set_pd (3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_VAN_LEER);
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_VanLeer([-1,2],[1,3])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (_mm_set_pd (2., -1.),
                                    _mm_set_pd (3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_VAN_ALBADA);
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_VanAlbada([-1,2],[1,3])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (_mm_set_pd (2., -1.),
                                    _mm_set_pd (3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_MINSUPER);
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_minsuper([-1,2],[1,3])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (_mm_set_pd (1., 3.),
                                    _mm_set_pd (1., 1.),
                                    JBM_FLUX_LIMITER_TYPE_MINSUPER);
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_minsuper([3,1],[1,1])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (_mm_set_pd (1., -1.),
                                    _mm_set_pd (3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_SUPERMIN);
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_supermin([-1,1],[1,3])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (_mm_set_pd (1., 3.),
                                    _mm_set_pd (1., 1.),
                                    JBM_FLUX_LIMITER_TYPE_SUPERMIN);
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_supermin([3,1],[1,1])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (_mm_set_pd (0.5, -1.),
                                    _mm_set_pd (3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL);
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_monotonized_central([-1,0.5],[1,3])"
          "=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (_mm_set_pd (3., 2.),
                                    _mm_set_pd (0.5, 3.),
                                    JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL);
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_monotonized_central([2,3],[3,0.5])"
          "=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (_mm_set_pd (2., -1.),
                                    _mm_set_pd (3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_MEAN);
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_mean([-1,2],[1,3])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn0_2xf64, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_integral(1,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn1_2xf64, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_integral(x,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn2_2xf64, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_integral(x^2,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn3_2xf64, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_integral(x^3,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn4_2xf64, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_integral(x^4,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn5_2xf64, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_integral(x^5,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn6_2xf64, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_integral(x^6,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn7_2xf64, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_integral(x^7,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn8_2xf64, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_integral(x^8,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn9_2xf64, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_integral(x^9,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn10_2xf64, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_integral(x^10,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0],
          d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn11_2xf64, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_integral(x^11,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0],
          d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn12_2xf64, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_integral(x^12,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0],
          d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn13_2xf64, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_integral(x^13,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0],
          d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn14_2xf64, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_2xf64);
  printf ("2xf64_integral(x^14,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0],
          d_1[1]);
  aligned_free (d_2);
  aligned_free (d_1);
#endif
#ifdef __AVX__
  printf ("check AVX functions\n");
  d_1 = aligned_alloc (32, 4 * sizeof (double));
  L_1 = (unsigned long long int *) d_1;
  d_2 = aligned_alloc (32, 4 * sizeof (double));
  d_4xf64 = jbm_4xf64_abs (_mm256_set_pd (2., 0., -1., 1));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_abs([1,-1,0,2])=[%.17lg,%.17lg,%.17lg,%.17lg]\n",
          d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_small_4xf64 (_mm256_set_pd (-1., 1., -0., 0.));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("small_4xf64([0,-0,1,-1])=[%16llx,%16llx,%16llx,%16llx]\n",
          L_1[0], L_1[1], L_1[2], L_1[3]);
  d_4xf64 = jbm_modmin_4xf64 (_mm256_set_pd (1., 0., -1., 1.),
                              _mm256_set_pd (-2., 1., -2., 0.5));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("modmin_4xf64([1,-1,0,1],[0.5,-2,1,-2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = _mm256_set_pd (3., -1., 1., 0.);
  d2_4xf64 = _mm256_set_pd (-4., 7., -2., 1.);
  jbm_change_4xf64 (&d_4xf64, &d2_4xf64);
  _mm256_store_pd (d_1, d_4xf64);
  _mm256_store_pd (d_2, d2_4xf64);
  printf ("change_4xf64([0,1,-1,3],[1,-2,7,-4])"
          "=([%.17lg,%.17lg,%.17lg,%.17lg],[%.17lg,%.17lg,%.17lg,%.17lg])\n",
          d_1[0], d_1[1], d_1[2], d_1[3], d_2[0], d_2[1], d_2[2], d_2[3]);
  d2_4xf64 = jbm_4xf64_dbl (d_4xf64);
  _mm256_store_pd (d_1, d2_4xf64);
  printf ("4xf64_dbl([1,-2,7,-4])=[%.17lg,%.17lg,%.17lg,%.17lg]\n",
          d_1[0], d_1[1], d_1[2], d_1[3]);
  d2_4xf64 = jbm_4xf64_sqr (d_4xf64);
  _mm256_store_pd (d_1, d2_4xf64);
  printf ("4xf64_sqr([1,-2,7,-4])=[%.17lg,%.17lg,%.17lg,%.17lg]\n",
          d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_extrapolate (_mm256_set_pd (0., 3., -1., 1.),
                                   _mm256_set1_pd (0.),
                                   _mm256_set1_pd (2.),
                                   _mm256_set1_pd (1.), _mm256_set1_pd (4.));
  _mm256_store_pd (d_1, d_4xf64);
  printf
    ("4xf64_extrapolate([1,-1,3,0],[0,0,0,0],[2,2,2,2],[1,1,1,1],[4,4,4,4])"
     "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 =
    jbm_4xf64_interpolate (_mm256_set_pd (0., 3., -1., 1.), _mm256_set1_pd (0.),
                           _mm256_set1_pd (2.), _mm256_set1_pd (1.),
                           _mm256_set1_pd (4.));
  _mm256_store_pd (d_1, d_4xf64);
  printf
    ("4xf64_interpolate([1,-1,3,0],[0,0,0,0],[2,2,2,2],[1,1,1,1],[4,4,4,4])"
     "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 =
    jbm_4xf64_v2_length (_mm256_set_pd (-1., 3., 2., 1.),
                         _mm256_set_pd (2., 3., -1., 4.), _mm256_set_pd (2., 0.,
                                                                         5.,
                                                                         -3.),
                         _mm256_set_pd (6., 7., 3., 1.));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_v2_length([1,2,3,-1],[4,-1,3,2],[-3,5,0,2],[1,3,7,6])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_v3_length (_mm256_set_pd (-1., 3., 2., 1.),
                                 _mm256_set_pd (2., 3., -1., 4.),
                                 _mm256_set_pd (5., 0., 1., 3.),
                                 _mm256_set_pd (1., 2., 4., -1.),
                                 _mm256_set_pd (5., 5., 3., 0.),
                                 _mm256_set_pd (-1., 2., 5., 7.));
  _mm256_store_pd (d_1, d_4xf64);
  printf
    ("4xf64_v3_length([1,2,3,-1],[4,-1,3,2],[3,1,0,5],[-1,4,1,1],[1,2,1,4],"
     "[9,-5,2,0])=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2],
     d_1[3]);
  d_4xf64 = jbm_4xf64_polynomial_11 (_mm256_set_pd (-1., 0., 1., 0.5), p_1);
  _mm256_store_pd (d_1, d_4xf64);
  printf ("polynomial_11_2xdbl([0.5,1,0,-1],"
          "[1,2,4,8,16,32,64,128,256,512,1024,2048])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_solve_quadratic (_mm256_set_pd (1., 1., 0., 2.),
                                       _mm256_set_pd (0., 0., -2., -1.),
                                       _mm256_set_pd (-1., -1., 1., -1.),
                                       _mm256_set_pd (-2., 0., 0., 0.),
                                       _mm256_set_pd (0., 2., 2., 2.));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_solve_quadratic([2,0,1,1],[-1,-2,0,0][-1,1,-1,-1],[0,0,0,-2],"
          "[2,2,2,0])=[%.17lg,%.17lg,%.17lg,%.17lg]\n",
          d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_flux_limiter (_mm256_setzero_pd (),
                                    _mm256_set1_pd (1.),
                                    JBM_FLUX_LIMITER_TYPE_TOTAL);
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_flux_limiter_total([0,0,0,0],[1,1,1,1])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_flux_limiter (_mm256_setzero_pd (),
                                    _mm256_set1_pd (1.),
                                    JBM_FLUX_LIMITER_TYPE_NULL);
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_flux_limiter_null([0,0,0,0],[1,1,1,1])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_flux_limiter (_mm256_set_pd (0., 1., 3., 1.),
                                    _mm256_set_pd (0., 3., 0., 1.),
                                    JBM_FLUX_LIMITER_TYPE_CENTRED);
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_flux_limiter_centred([1,3,1,0],[1,0,3,0])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_flux_limiter (_mm256_set_pd (3., 2., 1., -1.),
                                    _mm256_set_pd (2., 3., 3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_SUPERBEE);
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_flux_limiter_superbee([-1,1,2,3],[1,3,3,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_flux_limiter (_mm256_set_pd (1., 0., 1., 0.),
                                    _mm256_set_pd (1., 1., 0., 0.),
                                    JBM_FLUX_LIMITER_TYPE_SUPERBEE);
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_flux_limiter_superbee([0,1,0,1],[0,0,1,1])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_flux_limiter (_mm256_set_pd (1., 3., 2., -1.),
                                    _mm256_set_pd (1., 1., 3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_MINMOD);
  _mm256_store_pd (d_1, d_4xf64);
  printf ("flux_limiter_min4xf64_mod([-1,2,3,1],[1,3,1,1])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_flux_limiter (_mm256_set_pd (1., 0., 2., -1.),
                                    _mm256_set_pd (0., 0., 3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_VAN_LEER);
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_flux_limiter_VanLeer([-1,2,0,1],[1,3,0,0])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_flux_limiter (_mm256_set_pd (1., 0., 2., -1.),
                                    _mm256_set_pd (0., 0., 3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_VAN_ALBADA);
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_flux_limiter_VanAlbada([-1,2,0,1],[1,3,0,0])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_flux_limiter (_mm256_set_pd (1., 3., 2., -1.),
                                    _mm256_set_pd (1., 1., 3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_MINSUPER);
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_flux_limiter_minsuper([-1,2,3,1],[1,3,1,1])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_flux_limiter (_mm256_set_pd (1., 3., 1., -1.),
                                    _mm256_set_pd (1., 1., 3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_SUPERMIN);
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_flux_limiter_supermin([-1,1,3,1],[1,3,1,1])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_flux_limiter (_mm256_set_pd (3., 2., 0.5, -1.),
                                    _mm256_set_pd (0.5, 3., 3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL);
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_flux_limiter_monotonized_central([-1,0.5,2,3],[1,3,3,0.5])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_flux_limiter (_mm256_set_pd (1., 0., 2., -1.),
                                    _mm256_set_pd (0., 0., 3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_MEAN);
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_flux_limiter_mean([-1,2,0,1],[1,3,0,0])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_integral (fn0_4xf64, _mm256_set_pd (-2., 0., -1., 0.),
                                _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_integral(1,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_integral (fn1_4xf64, _mm256_set_pd (-2., 0., -1., 0.),
                                _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_integral(x,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_integral (fn2_4xf64, _mm256_set_pd (-2., 0., -1., 0.),
                                _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_integral(x^2,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_integral (fn3_4xf64, _mm256_set_pd (-2., 0., -1., 0.),
                                _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_integral(x^3,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_integral (fn4_4xf64, _mm256_set_pd (-2., 0., -1., 0.),
                                _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_integral(x^4,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_integral (fn5_4xf64, _mm256_set_pd (-2., 0., -1., 0.),
                                _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_integral(x^5,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_integral (fn6_4xf64, _mm256_set_pd (-2., 0., -1., 0.),
                                _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_integral(x^6,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_integral (fn7_4xf64, _mm256_set_pd (-2., 0., -1., 0.),
                                _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_integral(x^7,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_integral (fn8_4xf64, _mm256_set_pd (-2., 0., -1., 0.),
                                _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_integral(x^9,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_integral (fn9_4xf64, _mm256_set_pd (-2., 0., -1., 0.),
                                _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_integral(x^9,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_integral (fn10_4xf64, _mm256_set_pd (-2., 0., -1., 0.),
                                _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_integral(x^10,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_integral (fn11_4xf64, _mm256_set_pd (-2., 0., -1., 0.),
                                _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_integral(x^11,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_integral (fn12_4xf64, _mm256_set_pd (-2., 0., -1., 0.),
                                _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_integral(x^12,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_integral (fn13_4xf64, _mm256_set_pd (-2., 0., -1., 0.),
                                _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_integral(x^13,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_4xf64 = jbm_4xf64_integral (fn14_4xf64, _mm256_set_pd (-2., 0., -1., 0.),
                                _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_4xf64);
  printf ("4xf64_integral(x^14,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  aligned_free (d_2);
  aligned_free (d_1);
#endif
#ifdef __AVX512F__
  printf ("check AVX512 functions\n");
  d_1 = aligned_alloc (64, 8 * sizeof (double));
  d_2 = aligned_alloc (64, 8 * sizeof (double));
  d_8xf64 = jbm_8xf64_abs (_mm512_set_pd (4., -3., 3., -2., 2., 0., -1., 1));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_abs([1,-1,0,2,-2,3,-3,4])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg]\n",
          d_1[0], d_1[1], d_1[2], d_1[3], d_1[4], d_1[5], d_1[6], d_1[7]);
  m_8 = jbm_small_8xf64 (_mm512_set_pd (-3., 3., -2., 2., -1., 1., -0., 0.));
  printf ("small_8xf64([0,-0,1,-1,2,-2,3,-3])=%08b\n", (unsigned int) m_8);
  d_8xf64 = jbm_modmin_8xf64 (_mm512_set_pd (-2., 0., 0., 3., 1., 0., -1., 1.),
                              _mm512_set_pd (-1., 2., 3., 1., -2., 1., -2.,
                                             0.5));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("modmin_8xf64([1,-1,0,1,3,0,0,-2],[0.5,-2,1,-2,1,3,2,-1])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg]\n",
          d_1[0], d_1[1], d_1[2], d_1[3], d_1[4], d_1[5], d_1[6], d_1[7]);
  d_8xf64 = _mm512_set_pd (0., 2., -1, 0., 3., -1., 1., 0.);
  d2_8xf64 = _mm512_set_pd (3., 0., 2., -1, -4., 7., -2., 1.);
  jbm_change_8xf64 (&d_8xf64, &d2_8xf64);
  _mm512_store_pd (d_1, d_8xf64);
  _mm512_store_pd (d_2, d2_8xf64);
  printf ("change_8xf64([0,1,-1,3,0,-1,2,0],[1,-2,7,-4,-1,2,0,3])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg]"
          ",[%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg]\n",
          d_1[0], d_1[1], d_1[2], d_1[3], d_1[4], d_1[5], d_1[6], d_1[7],
          d_2[0], d_2[1], d_2[2], d_2[3], d_2[4], d_2[5], d_2[6], d_2[7]);
  d2_8xf64 = jbm_8xf64_dbl (d_8xf64);
  _mm512_store_pd (d_1, d2_8xf64);
  printf ("8xf64_dbl([1,-2,7,-4,-1,2,0,3])="
          "[%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg]\n",
          d_1[0], d_1[1], d_1[2], d_1[3], d_1[4], d_1[5], d_1[6], d_1[7]);
  d2_8xf64 = jbm_8xf64_sqr (d_8xf64);
  _mm512_store_pd (d_1, d2_8xf64);
  printf ("8xf64_sqr([1,-2,7,-4,-1,2,0,3])="
          "[%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg]\n",
          d_1[0], d_1[1], d_1[2], d_1[3], d_1[4], d_1[5], d_1[6], d_1[7]);
  d_8xf64
    = jbm_8xf64_extrapolate (_mm512_set_pd (2., -2., 4., -3., 0., 3., -1., 1.),
                             _mm512_set1_pd (0.),
                             _mm512_set1_pd (2.),
                             _mm512_set1_pd (1.), _mm512_set1_pd (4.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_extrapolate([1,-1,3,0,-3,4,-2,2],[0,0,0,0,0,0,0,0],"
          "[2,2,2,2,2,2,2,2],[1,1,1,1,1,1,1,1],[4,4,4,4,4,4,4,4])"
          "[%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg]\n",
          d_1[0], d_1[1], d_1[2], d_1[3], d_1[4], d_1[5], d_1[6], d_1[7]);
  d_8xf64
    = jbm_8xf64_interpolate (_mm512_set_pd (2., -2., 4., -3., 0., 3., -1., 1.),
                             _mm512_set1_pd (0.),
                             _mm512_set1_pd (2.),
                             _mm512_set1_pd (1.), _mm512_set1_pd (4.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_interpolate([1,-1,3,0,-3,4,-2,2],[0,0,0,0,0,0,0,0],"
          "[2,2,2,2,2,2,2,2],[1,1,1,1,1,1,1,1],[4,4,4,4,4,4,4,4])"
          "[%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg]\n",
          d_1[0], d_1[1], d_1[2], d_1[3], d_1[4], d_1[5], d_1[6], d_1[7]);
  d_8xf64 =
    jbm_8xf64_v2_length (_mm512_set_pd (2., 3., -1., 4., -1., 3., 2., 1.),
                         _mm512_set_pd (-1., 3., 2., 1., 2., 3., -1., 4.),
                         _mm512_set_pd (6., 7., 3., 1., 2., 0., 5., -3.),
                         _mm512_set_pd (2., 0., 5., -3., 6., 7., 3., 1.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_v2_length([1,2,3,-1,4,-1,3,2],[4,-1,3,2,1,2,3,-1],"
          "[-3,5,0,2,1,3,7,6],[1,3,7,6,-3,5,0,2])"
          "[%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg]\n",
          d_1[0], d_1[1], d_1[2], d_1[3], d_1[4], d_1[5], d_1[6], d_1[7]);
  d_8xf64 =
    jbm_8xf64_v3_length (_mm512_set_pd (2., 3., -1., 4., -1., 3., 2., 1.),
                         _mm512_set_pd (-1., 3., 2., 1., 2., 3., -1., 4.),
                         _mm512_set_pd (5., 0., 1., 3., 5., 0., 1., 3.),
                         _mm512_set_pd (5., 5., 3., 0., 1., 2., 4., -1.),
                         _mm512_set_pd (1., 2., 4., -1., 5., 5., 3., 0.),
                         _mm512_set_pd (-1., 2., 5., 7., -1., 2., 5., 7.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_v3_length([1,2,3,-1,4,-1,3,2],[4,-1,3,2,1,2,3,-1],"
          "[5,0,1,3,5,1,0,3],[-1,4,2,1,0,3,5,5],[0,3,5,5,-1,4,2,1],"
          "[7,5,2,-1,7,5,2,-1])="
          "[%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg]\n",
          d_1[0], d_1[1], d_1[2], d_1[3], d_1[4], d_1[5], d_1[6], d_1[7]);
  d_8xf64
    =
    jbm_8xf64_polynomial_11 (_mm512_set_pd
                             (-0.25, 0.25, 0., -0.5, -1., 0., 1., 0.5), p_1);
  _mm512_store_pd (d_1, d_8xf64);
  printf ("polynomial_11_4xdbl([0.5,1,0,-1,-0.5,0,0.25,-0.25],"
          "[1,2,4,8,16,32,64,128,512,512,1024,2048])="
          "[%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg,%.17lg]\n",
          d_1[0], d_1[1], d_1[2], d_1[3], d_1[4], d_1[5], d_1[6], d_1[7]);
/*
  d_8xf64 = jbm_8xf64_solve_quadratic (_mm512_set_pd (1., 1., 0., 2.),
                                   _mm512_set_pd (0., 0., -2., -1.),
                                   _mm512_set_pd (-1., -1., 1., -1.),
                                   _mm512_set_pd (-2., 0., 0., 0.),
                                   _mm512_set_pd (0., 2., 2., 2.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_solve_quadratic([2,0,1,1],[-1,-2,0,0][-1,1,-1,-1],[0,0,0,-2],"
          "[2,2,2,0])=[%.17lg,%.17lg,%.17lg,%.17lg]\n",
          d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_flux_limiter (_mm512_setzero_pd (),
                                _mm512_set1_pd (1.),
                                JBM_FLUX_LIMITER_TYPE_TOTAL);
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_flux_limiter_total([0,0,0,0],[1,1,1,1])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_flux_limiter (_mm512_setzero_pd (),
                                _mm512_set1_pd (1.),
                                JBM_FLUX_LIMITER_TYPE_NULL);
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_flux_limiter_null([0,0,0,0],[1,1,1,1])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_flux_limiter (_mm512_set_pd (0., 1., 3., 1.),
                                _mm512_set_pd (0., 3., 0., 1.),
                                JBM_FLUX_LIMITER_TYPE_CENTRED);
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_flux_limiter_centred([1,3,1,0],[1,0,3,0])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_flux_limiter (_mm512_set_pd (3., 2., 1., -1.),
                                _mm512_set_pd (2., 3., 3., 1.),
                                JBM_FLUX_LIMITER_TYPE_SUPERBEE);
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_flux_limiter_superbee([-1,1,2,3],[1,3,3,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_flux_limiter (_mm512_set_pd (1., 0., 1., 0.),
                                _mm512_set_pd (1., 1., 0., 0.),
                                JBM_FLUX_LIMITER_TYPE_SUPERBEE);
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_flux_limiter_superbee([0,1,0,1],[0,0,1,1])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_flux_limiter (_mm512_set_pd (1., 3., 2., -1.),
                                _mm512_set_pd (1., 1., 3., 1.),
                                JBM_FLUX_LIMITER_TYPE_MINMOD);
  _mm512_store_pd (d_1, d_8xf64);
  printf ("flux_limiter_min8xf64_mod([-1,2,3,1],[1,3,1,1])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_flux_limiter (_mm512_set_pd (1., 0., 2., -1.),
                                _mm512_set_pd (0., 0., 3., 1.),
                                JBM_FLUX_LIMITER_TYPE_VAN_LEER);
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_flux_limiter_VanLeer([-1,2,0,1],[1,3,0,0])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_flux_limiter (_mm512_set_pd (1., 0., 2., -1.),
                                _mm512_set_pd (0., 0., 3., 1.),
                                JBM_FLUX_LIMITER_TYPE_VAN_ALBADA);
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_flux_limiter_VanAlbada([-1,2,0,1],[1,3,0,0])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_flux_limiter (_mm512_set_pd (1., 3., 2., -1.),
                                _mm512_set_pd (1., 1., 3., 1.),
                                JBM_FLUX_LIMITER_TYPE_MINSUPER);
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_flux_limiter_minsuper([-1,2,3,1],[1,3,1,1])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_flux_limiter (_mm512_set_pd (1., 3., 1., -1.),
                                _mm512_set_pd (1., 1., 3., 1.),
                                JBM_FLUX_LIMITER_TYPE_SUPERMIN);
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_flux_limiter_supermin([-1,1,3,1],[1,3,1,1])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_flux_limiter (_mm512_set_pd (3., 2., 0.5, -1.),
                                _mm512_set_pd (0.5, 3., 3., 1.),
                                JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL);
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_flux_limiter_monotonized_central([-1,0.5,2,3],[1,3,3,0.5])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_flux_limiter (_mm512_set_pd (1., 0., 2., -1.),
                                _mm512_set_pd (0., 0., 3., 1.),
                                JBM_FLUX_LIMITER_TYPE_MEAN);
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_flux_limiter_mean([-1,2,0,1],[1,3,0,0])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_integral (fn0_8xf64, _mm512_set_pd (-2., 0., -1., 0.),
                            _mm512_set_pd (2., 2., 1., 1.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_integral(1,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_integral (fn1_8xf64, _mm512_set_pd (-2., 0., -1., 0.),
                            _mm512_set_pd (2., 2., 1., 1.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_integral(x,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_integral (fn2_8xf64, _mm512_set_pd (-2., 0., -1., 0.),
                            _mm512_set_pd (2., 2., 1., 1.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_integral(x^2,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_integral (fn3_8xf64, _mm512_set_pd (-2., 0., -1., 0.),
                            _mm512_set_pd (2., 2., 1., 1.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_integral(x^3,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_integral (fn4_8xf64, _mm512_set_pd (-2., 0., -1., 0.),
                            _mm512_set_pd (2., 2., 1., 1.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_integral(x^4,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_integral (fn5_8xf64, _mm512_set_pd (-2., 0., -1., 0.),
                            _mm512_set_pd (2., 2., 1., 1.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_integral(x^5,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_integral (fn6_8xf64, _mm512_set_pd (-2., 0., -1., 0.),
                            _mm512_set_pd (2., 2., 1., 1.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_integral(x^6,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_integral (fn7_8xf64, _mm512_set_pd (-2., 0., -1., 0.),
                            _mm512_set_pd (2., 2., 1., 1.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_integral(x^7,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_integral (fn8_8xf64, _mm512_set_pd (-2., 0., -1., 0.),
                            _mm512_set_pd (2., 2., 1., 1.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_integral(x^9,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_integral (fn9_8xf64, _mm512_set_pd (-2., 0., -1., 0.),
                            _mm512_set_pd (2., 2., 1., 1.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_integral(x^9,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_integral (fn10_8xf64, _mm512_set_pd (-2., 0., -1., 0.),
                            _mm512_set_pd (2., 2., 1., 1.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_integral(x^10,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_integral (fn11_8xf64, _mm512_set_pd (-2., 0., -1., 0.),
                            _mm512_set_pd (2., 2., 1., 1.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_integral(x^11,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_integral (fn12_8xf64, _mm512_set_pd (-2., 0., -1., 0.),
                            _mm512_set_pd (2., 2., 1., 1.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_integral(x^12,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_integral (fn13_8xf64, _mm512_set_pd (-2., 0., -1., 0.),
                            _mm512_set_pd (2., 2., 1., 1.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_integral(x^13,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_8xf64 = jbm_8xf64_integral (fn14_8xf64, _mm512_set_pd (-2., 0., -1., 0.),
                            _mm512_set_pd (2., 2., 1., 1.));
  _mm512_store_pd (d_1, d_8xf64);
  printf ("8xf64_integral(x^14,[0,-1,0,-2],[1,1,2,2])"
          "=[%.17lg,%.17lg,%.17lg,%.17lg]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
*/
  aligned_free (d_2);
  aligned_free (d_1);
#endif
#ifdef __ARM_NEON
  printf ("check NEON functions\n");
  d_1 = aligned_alloc (16, 2 * sizeof (double));
  L_1 = (unsigned long long int *) d_1;
  d_2 = aligned_alloc (16, 2 * sizeof (double));
  d_2xf64 = jbm_2xf64_abs (set_float64x2_t (-1., 1));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_abs([1,-1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  m_2xf64 = jbm_small_2xf64 (set_float64x2_t (1., 0.));
  vst1q_u64 (L_1, m_2xf64);
  printf ("small_2xf64([0,1])=[%16llx,%16llx]\n", L_1[0], L_1[1]);
  d_2xf64
    = jbm_modmin_2xf64 (set_float64x2_t (-1., 1.), set_float64x2_t (-2., 0.5));
  vst1q_dbl (d_1, d_2xf64);
  printf ("modmin_2xf64([1,-1],[0.5,-2])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64
    = jbm_modmin_2xf64 (set_float64x2_t (1.0, 0.), set_float64x2_t (-2., 1.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("modmin_2xf64([0,1],[1,-2])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 = set_float64x2_t (1., 0.);
  d2_2xf64 = set_float64x2_t (-2., 1.);
  jbm_change_2xf64 (&d_2xf64, &d2_2xf64);
  vst1q_dbl (d_1, d_2xf64);
  vst1q_dbl (d_2, d2_2xf64);
  printf ("change_2xf64([0,1],[1,-2])=([%.17lg,%.17lg],[%.17lg,%.17lg])\n",
          d_1[0], d_1[1], d_2[0], d_2[1]);
  d2_2xf64 = jbm_2xf64_dbl (d_2xf64);
  vst1q_dbl (d_1, d2_2xf64);
  printf ("2xf64_dbl([1,-2])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_sqr (d_2xf64);
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_sqr([1,-2])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_extrapolate (set_float64x2_t (-1., 1.),
                                   vdupq_n_dbl (0.), vdupq_n_dbl (2.),
                                   vdupq_n_dbl (1.), vdupq_n_dbl (4.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_extrapolate([1,-1],[0,0],[2,2],[1,1],[4,4])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_interpolate (set_float64x2_t (-1., 1.),
                                   vdupq_n_dbl (0.), vdupq_n_dbl (2.),
                                   vdupq_n_dbl (1.), vdupq_n_dbl (4.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_interpolate([1,-1],[0,0],[2,2],[1,1],[4,4])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_interpolate (set_float64x2_t (3., 1.),
                                   set_float64x2_t (0., 0.),
                                   set_float64x2_t (2., 2.),
                                   set_float64x2_t (1., 1.),
                                   set_float64x2_t (4., 4.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_interpolate([1,3],[0,0],[2,2],[1,1],[4,4])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_v2_length (set_float64x2_t (2., 1.),
                                 set_float64x2_t (-1., 4.),
                                 set_float64x2_t (5., -3.),
                                 set_float64x2_t (3., 1.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_v2_length([1,2],[4,-1],[-3,5],[1,3])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_v3_length (set_float64x2_t (2., 1.),
                                 set_float64x2_t (-1., 4.),
                                 set_float64x2_t (1., 3.),
                                 set_float64x2_t (4., -1.),
                                 set_float64x2_t (2., 1.),
                                 set_float64x2_t (-5., 9.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_v3_length([1,2],[4,-1],[3,1],[-1,4],[1,2],[9,-5])"
          "=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_polynomial_11 (set_float64x2_t (1., 0.5), p_1);
  vst1q_dbl (d_1, d_2xf64);
  printf
    ("2xf64_polynomial_11([0.5,1],[1,2,4,8,16,32,64,128,256,512,1024,2048])"
     "=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_solve_quadratic (set_float64x2_t (0., 2.),
                               set_float64x2_t (-2., -1.),
                               set_float64x2_t (1., -1.),
                               set_float64x2_t (0., 0.),
                               set_float64x2_t (2., 2.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_solve_quadratic([2,0],[-1,-2][-1,1],[0,0],[2,2])"
          "=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (vdupq_n_dbl (0.),
                                    vdupq_n_dbl (1.),
                                    JBM_FLUX_LIMITER_TYPE_TOTAL);
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_total([0,0],[1,1])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (vdupq_n_dbl (0.),
                                    vdupq_n_dbl (1.),
                                    JBM_FLUX_LIMITER_TYPE_NULL);
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_null([0,0],[1,1])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (set_float64x2_t (3., 1.),
                                    set_float64x2_t (0., 1.),
                                    JBM_FLUX_LIMITER_TYPE_CENTRED);
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_centred([1,3],[1,0])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (set_float64x2_t (1., -1.),
                                    set_float64x2_t (3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_SUPERBEE);
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_superbee([-1,1],[1,3])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (set_float64x2_t (3., 2.),
                                    set_float64x2_t (2., 3.),
                                    JBM_FLUX_LIMITER_TYPE_SUPERBEE);
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_superbee([2,3],[3,2])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (set_float64x2_t (1., 3.),
                                    set_float64x2_t (1., 1.),
                                    JBM_FLUX_LIMITER_TYPE_SUPERBEE);
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_superbee([3,1],[1,1])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (set_float64x2_t (2., -1.),
                                    set_float64x2_t (3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_MINMOD);
  vst1q_dbl (d_1, d_2xf64);
  printf ("flux_limiter_min2xf64_mod([-1,2],[1,3])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (set_float64x2_t (1., 3.),
                                    set_float64x2_t (1., 1.),
                                    JBM_FLUX_LIMITER_TYPE_MINMOD);
  vst1q_dbl (d_1, d_2xf64);
  printf ("flux_limiter_min2xf64_mod([3,1],[1,1])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (set_float64x2_t (2., -1.),
                                    set_float64x2_t (3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_VAN_LEER);
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_VanLeer([-1,2],[1,3])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (set_float64x2_t (2., -1.),
                                    set_float64x2_t (3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_VAN_ALBADA);
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_VanAlbada([-1,2],[1,3])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (set_float64x2_t (2., -1.),
                                    set_float64x2_t (3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_MINSUPER);
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_minsuper([-1,2],[1,3])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (set_float64x2_t (1., 3.),
                                    set_float64x2_t (1., 1.),
                                    JBM_FLUX_LIMITER_TYPE_MINSUPER);
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_minsuper([3,1],[1,1])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (set_float64x2_t (1., -1.),
                                    set_float64x2_t (3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_SUPERMIN);
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_supermin([-1,1],[1,3])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (set_float64x2_t (1., 3.),
                                    set_float64x2_t (1., 1.),
                                    JBM_FLUX_LIMITER_TYPE_SUPERMIN);
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_supermin([3,1],[1,1])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (set_float64x2_t (0.5, -1.),
                                    set_float64x2_t (3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL);
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_monotonized_central([-1,0.5],[1,3])"
          "=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (set_float64x2_t (3., 2.),
                                    set_float64x2_t (0.5, 3.),
                                    JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL);
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_monotonized_central([2,3],[3,0.5])"
          "=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 = jbm_2xf64_flux_limiter (set_float64x2_t (2., -1.),
                                    set_float64x2_t (3., 1.),
                                    JBM_FLUX_LIMITER_TYPE_MEAN);
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_flux_limiter_mean([-1,2],[1,3])=[%.17lg,%.17lg]\n",
          d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn0_2xf64, set_float64x2_t (-1., 0.), vdupq_n_dbl (1.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_integral(1,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn1_2xf64, set_float64x2_t (-1., 0.), vdupq_n_dbl (1.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_integral(x,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn2_2xf64, set_float64x2_t (-1., 0.), vdupq_n_dbl (1.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_integral(x^2,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn3_2xf64, set_float64x2_t (-1., 0.), vdupq_n_dbl (1.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_integral(x^3,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn4_2xf64, set_float64x2_t (-1., 0.), vdupq_n_dbl (1.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_integral(x^4,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn5_2xf64, set_float64x2_t (-1., 0.), vdupq_n_dbl (1.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_integral(x^5,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn6_2xf64, set_float64x2_t (-1., 0.), vdupq_n_dbl (1.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_integral(x^6,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn7_2xf64, set_float64x2_t (-1., 0.), vdupq_n_dbl (1.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_integral(x^7,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn8_2xf64, set_float64x2_t (-1., 0.), vdupq_n_dbl (1.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_integral(x^8,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn9_2xf64, set_float64x2_t (-1., 0.), vdupq_n_dbl (1.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_integral(x^9,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0], d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn10_2xf64, set_float64x2_t (-1., 0.),
                        vdupq_n_dbl (1.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_integral(x^10,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0],
          d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn11_2xf64, set_float64x2_t (-1., 0.),
                        vdupq_n_dbl (1.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_integral(x^11,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0],
          d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn12_2xf64, set_float64x2_t (-1., 0.),
                        vdupq_n_dbl (1.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_integral(x^12,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0],
          d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn13_2xf64, set_float64x2_t (-1., 0.),
                        vdupq_n_dbl (1.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_integral(x^13,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0],
          d_1[1]);
  d_2xf64 =
    jbm_2xf64_integral (fn14_2xf64, set_float64x2_t (-1., 0.),
                        vdupq_n_dbl (1.));
  vst1q_dbl (d_1, d_2xf64);
  printf ("2xf64_integral(x^14,[0,-1],[1,1])=[%.17lg,%.17lg]\n", d_1[0],
          d_1[1]);
  aligned_free (d_2);
  aligned_free (d_1);
#endif

  printf ("check farray functions\n");
  fa = jbm_farray_create (pf, 11);
  printf ("fa=%zu fa->x=%zu\n", (size_t) fa, (size_t) fa->x);
  fa2 = jbm_farray_new (11);
  fa3 = jbm_farray_new (11);
  for (i = 0; i < 11; ++i)
    fa2->x[i] = pf[11 - i];
  printf ("farray_add([1,2,4,...],[2048,1024,512,...],11)\n");
  jbm_farray_add (fa3, fa, fa2);
  farray_print (fa3);
  printf ("farray_sub([1,2,4,...],[2048,1024,512,...],11)\n");
  jbm_farray_sub (fa3, fa, fa2);
  farray_print (fa3);
  printf ("farray_mul1([1,2,4,...],3,11)\n");
  jbm_farray_mul1 (fa3, fa, (JBFLOAT) 3.);
  farray_print (fa3);
  printf ("farray_div1([1,2,4,...],3,11)\n");
  jbm_farray_div1 (fa3, fa, (JBFLOAT) 3.);
  farray_print (fa3);
  printf ("farray_mul([1,2,4,...],[2048,1024,512,...],11)\n");
  jbm_farray_mul (fa3, fa, fa2);
  farray_print (fa3);
  printf ("farray_div([1,2,4,...],[2048,1024,512,...],11)\n");
  jbm_farray_div (fa3, fa, fa2);
  farray_print (fa3);
  printf ("farray_dbl([1,2,4,...],11)\n");
  jbm_farray_dbl (fa3, fa);
  farray_print (fa3);
  printf ("farray_sqr([1,2,4,...],11)\n");
  jbm_farray_sqr (fa3, fa);
  farray_print (fa3);
  printf ("farray_search(2048,[1,2,4,...],11)=%d\n",
          jbm_farray_search (fa, pf[11]));
  printf ("farray_search_extended(2048,[1,2,4,...],11)=%d\n",
          jbm_farray_search_extended (fa, pf[11]));
  jbm_farray_destroy (fa);
  fa = jbm_farray_create (pf, 11);
  printf ("farray_search(-1,[1,2,4,...],11)=%d\n",
          jbm_farray_search (fa, (JBFLOAT) - 1.));
  printf ("farray_search_extended(-1,[1,2,4,...],11)=%d\n",
          jbm_farray_search_extended (fa, (JBFLOAT) - 1.));
  printf ("farray_search_extended(3,[1,2,4,...],11)=%d\n",
          jbm_farray_search_extended (fa, (JBFLOAT) 3.));
  printf ("farray_search_extended(2048,[1,2,4,...],11)=%d\n",
          jbm_farray_search_extended (fa, pf[11]));
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_farray_max (fa));
  printf ("farray_max([1,2,4,...],11)=%s\n", buffer);
  jbm_farray_destroy (fa);
  fa = jbm_farray_create (pf, 10);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_farray_max (fa));
  printf ("farray_max([1,2,4,...],10)=%s\n", buffer);
  jbm_farray_destroy (fa);
  fa = jbm_farray_create (pf, 9);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_farray_max (fa));
  printf ("farray_max([1,2,4,...],9)=%s\n", buffer);
  jbm_farray_destroy (fa);
  fa = jbm_farray_create (pf, 3);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_farray_max (fa));
  printf ("farray_max([1,2,4,...],3)=%s\n", buffer);
  jbm_farray_destroy (fa);
  fa = jbm_farray_create (pf, 2);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_farray_max (fa));
  printf ("farray_max([1,2,4,...],2)=%s\n", buffer);
  jbm_farray_destroy (fa);
  fa = jbm_farray_create (pf, 1);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_farray_max (fa));
  printf ("farray_max([1,2,4,...],1)=%s\n", buffer);
  jbm_farray_destroy (fa);
  fa = jbm_farray_create (pf, 11);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_farray_min (fa));
  printf ("farray_min([1,2,4,...],11)=%s\n", buffer);
  jbm_farray_maxmin (fa, &f, &f2);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, f);
  SNPRINTF (buffer2, JB_BUFFER_SIZE, FWF, f2);
  printf ("farray_maxmin([1,2,4,...],11)=(%s,%s)\n", buffer, buffer2);
  printf ("farray_change\n");
  jbm_farray_change (fa, fa2);
  farray_print (fa);
  jbm_farray_change (fa, fa2);
  farray_print (fa);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_interpolate (fa, fa2, (JBFLOAT) 3.));
  printf ("farray_interpolate(3,[1,2,4,...],[2048,1024,512,...],11)=%s\n",
          buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_interpolate (fa, fa2, (JBFLOAT) 0.));
  printf ("farray_interpolate(0,[1,2,4,...],[2048,1024,512,...],11)=%s\n",
          buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_interpolate (fa, fa2,
                                    EXP ((JBFLOAT) 3. * (JBFLOAT) 3.)));
  printf ("farray_interpolate(exp(9),[1,2,4,...],[2048,1024,512,...],11)=%s\n",
          buffer);
  jbm_farray_dbl (fa2, fa);
  printf ("farray_merge([1,2,4,..],[2,4,8,...],11)\n");
  jbm_farray_destroy (fa3);
  fa3 = jbm_farray_merge (fa, fa2);
  farray_print (fa3);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_integral (fa, fa2, (JBFLOAT) 0., (JBFLOAT) 0.5));
  printf ("farray_integral([1,2,4,...],[2,4,8,...],11,0,0.5)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_integral (fa, fa2, pf[10], pf[11]));
  printf ("farray_integral([1,2,4,...],[2,4,8,...],11,2048,4096)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_integral (fa, fa2, (JBFLOAT) 2., (JBFLOAT) 3.));
  printf ("farray_integral([1,2,4,...],[2,4,8,...],11,2,3)=%s\n", buffer);
  jbm_farray_init (fa, 10);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_root_mean_square_error (fa, fa, fa2, fa2));
  printf ("farray_root_mean_square_error([1,2,4,...],[1,2,4,...],10,"
          "[2,4,8,...],[2,4,8,...],11)=%s\n", buffer);
  jbm_farray_init (fa, 11);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_root_mean_square_error (fa, fa, fa, fa2));
  printf ("farray_root_mean_square_error([1,2,4,...],[1,2,4,...],11,"
          "[1,2,4,...],[2,4,8,...],11)=%s\n", buffer);
  printf ("matrix_solve\n");
  jbm_matrix_solve (mxf, 4);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, mxf[4]);
  SNPRINTF (buffer2, JB_BUFFER_SIZE, FWF, myf[0]);
  printf ("mxf0=%s mxf0=%s\n", buffer, buffer2);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, mxf[9]);
  SNPRINTF (buffer2, JB_BUFFER_SIZE, FWF, myf[1]);
  printf ("mxf1=%s mxf1=%s\n", buffer, buffer2);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, mxf[14]);
  SNPRINTF (buffer2, JB_BUFFER_SIZE, FWF, myf[2]);
  printf ("mxf2=%s mxf2=%s\n", buffer, buffer2);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, mxf[19]);
  SNPRINTF (buffer2, JB_BUFFER_SIZE, FWF, myf[3]);
  printf ("mxf3=%s mxf3=%s\n", buffer, buffer2);
  printf ("matrix_solve_tridiagonal\n");
  jbm_matrix_solve_tridiagonal (Cf, Df, Ef, Hf, 4);
  jbm_farray_set (fa3, Hf, 4);
  farray_print (fa3);
  printf ("matrix_solve_tridiagonal_zero\n");
  jbm_matrix_solve_tridiagonal_zero (Czf, Dzf, Ezf, Hzf, 5);
  jbm_farray_set (fa3, Hzf, 5);
  farray_print (fa3);
  printf ("matrix_solve_pentadiagonal\n");
  jbm_matrix_solve_pentadiagonal (Bpf, Cpf, Dpf, Epf, Fpf, Hpf, 4);
  jbm_farray_set (fa3, Hpf, 4);
  farray_print (fa3);
  printf ("matrix_solve_pentadiagonal_zero\n");
  jbm_matrix_solve_pentadiagonal_zero (Bpzf, Cpzf, Dpzf, Epzf, Fpzf, Hpzf, 5);
  jbm_farray_set (fa3, Hpzf, 5);
  farray_print (fa3);
  jbm_regression_linear (fa, fa2, &f, &f2);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, f);
  SNPRINTF (buffer2, JB_BUFFER_SIZE, FWF, f2);
  printf ("regression_linear([1,2,4,...],[2,4,8,...],11)=(%s,%s)\n",
          buffer, buffer2);
  for (i = 0; i < 11; ++i)
    fa2->x[i] = pf[11 - i];
  jbm_regression_linear (fa, fa2, &f, &f2);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, f);
  SNPRINTF (buffer2, JB_BUFFER_SIZE, FWF, f2);
  printf ("regression_linear([1,2,4,...],[2048,1024,512,...],11)=(%s,%s)\n",
          buffer, buffer2);
  jbm_regression_exponential (fa, fa2, &f, &f2);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, f);
  SNPRINTF (buffer2, JB_BUFFER_SIZE, FWF, f2);
  printf ("regression_exponential([1,2,4,...],[2048,1024,512,...],11)"
          "=(%s,%s)\n", buffer, buffer2);
  jbm_farray_set (fa, pf, 11);
  jbm_farray_dbl (fa2, fa);
  jbm_regression_exponential (fa, fa2, &f, &f2);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, f);
  SNPRINTF (buffer2, JB_BUFFER_SIZE, FWF, f2);
  printf ("regression_exponential([1,2,4,...],[2,4,8,...],11)=(%s,%s)\n",
          buffer, buffer2);
  jbm_farray_set (fa, pf, 11);
  jbm_farray_dbl (fa2, fa);
  jbm_farray_destroy (fa3);
  jbm_regression_polynomial (fa, fa2, &fa3, 2);
  printf ("regression_polynomial([1,2,4,...],[2,4,8,...],11,f,2)\n");
  farray_print (fa3);
  for (i = 0; i < 11; ++i)
    fa2->x[i] = pf[11 - i];
  jbm_farray_destroy (fa3);
  jbm_regression_polynomial (fa, fa2, &fa3, 3);
  printf ("regression_polynomial([1,2,4,...],[2048,1024,512,...],11,f,3)\n");
  farray_print (fa3);
  jbm_farray_destroy (fa3);
  jbm_farray_destroy (fa2);
  jbm_farray_destroy (fa);
/*
  printf ("regression_multilinear\n");
  jbm_regression_multilinear (rmlf1, 36, kf, 2);
  farray_print (kf, 3);
  jbm_regression_multilinear (rmlf2, 36, kf, 2);
  farray_print (kf, 3);
  printf ("regression_multiexponential\n");
  jbm_regression_multiexponential (rmef1, 25, kf, 2);
  farray_print (kf, 3);
  printf ("spline_cubic\n");
  jbm_spline_cubic (farray, farray2, 12, &A1f, &A2f, &A3f);
  farray_print (A1f, 11);
  farray_print (A2f, 11);
  farray_print (A3f, 11);
  free (A1f);
  printf ("varray_solve_tridiagonal\n");
  jbm_varray_solve_tridiagonal (&cf[0].C, &cf[0].D, &cf[0].E, &cf[0].H,
                                sizeof (MatrixFloat), 3);
  for (i = 0; i < 4; ++i)
    {
      SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, cf[i].H);
      printf ("x%d=%s\n", i, buffer);
    }
  printf ("varray_solve_tridiagonal_zero\n");
  jbm_varray_solve_tridiagonal_zero (&czf[0].C, &czf[0].D, &czf[0].E, &czf[0].H,
                                     sizeof (MatrixFloat), 4);
  for (i = 0; i < 5; ++i)
    {
      SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, czf[i].H);
      printf ("x%d=%s\n", i, buffer);
    }
*/
  return 0;
}

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

int
main (void)
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

int
main (void)
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

int
main (void)
{
  printf ("MSE = " FWF "\n",
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

int
main (void)
{
  printf ("MSE = " FWF "\n",
          jbm_varray_mean_square_error
          (&(va->x), &(va->y), sizeof (P2), na,
           &(vr->x), &(vr->y), sizeof (P3), nr));
  return 0;
}

#endif

#ifdef FILE_MEAN_SQUARE_ERROR

int
main (void)
{
  printf
    ("MSE = " FWF "\n",
     jbm_file_mean_square_error ("msea", 1, 2, 2, "mser", 1, 2, 3));
  return 0;
}

#endif

#endif
