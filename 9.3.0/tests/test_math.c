#include "../src/math.h"

typedef struct
{
  JBFLOAT A, B, C, D, E, F, G, H;
} MatrixFloat;

typedef struct
{
  JBDOUBLE A, B, C, D, E, F, G, H;
} MatrixDouble;

#if JBM_LOW_PRECISION == 1

const JBFLOAT pf[15] = { 1.f, 2.f, 4.f, 8.f, 16.f, 32.f, 64.f, 128.f, 256.f,
  512.f, 1024.f, 2048.f, 4096.f, 8192.f, 16384.f };
const JBFLOAT cf0 = 0.f, cf1 = 1.f, cf2 = 2.f, cf3 = 3.f, cf05 = 0.5f;
JBFLOAT mxf[] = {
  1.f, 3.f, 2.f, 1.f, 18.f,
  2.f, 4.f, 8.f, 0.f, 18.f,
  3.f, -1.f, 4.f, 2.f, 4.f,
  4.f, 0.f, 3.f, 1.f, 11.f
};
const JBFLOAT myf[] = { 3.f, 5.f, -1.f, 2.f };
JBFLOAT Cf[] = { 1.f, -1.f, -1.f }, Df[] = { 2.f, 2.f, 2.f, 1.f },
  Ef[] = { 1.f, 1.f, -1.f }, Hf[] = { 5.f, 9.f, -7.f, 6.f },
  Czf[] = { 1.f, -1.f, 0.f, 1.f }, Dzf[] = { 2.f, 2.f, 0.f, 2.f, 1.f },
  Ezf[] = { 1.f, 0.f, 1.f, -1.f }, Hzf[] = { 5.f, 7.f, -1.f, -4.f, 6.f },
  Cpf[] = { 1.f, -1.f, -1.f }, Dpf[] = { 2.f, 2.f, 2.f, 1.f },
  Epf[] = { 1.f, 1.f, -1.f }, Bpf[] = { 1.f, -1.f }, Fpf[] = { -1.f, 1.f},
  Hpf[] = { 3.f, 17.f, -6.f, 3.f },
  Cpzf[] = { 1.f, -1.f, 0.f, -1.f }, Dpzf[] = { 2.f, 2.f, 0.f, 2.f, 1.f },
  Epzf[] = { 1.f, 0.f, 1.f, -1.f }, Bpzf[] = { 1.f, -1.f, 0.f },
  Fpzf[] = { 0.f, -1.f, 1.f}, Hpzf[] = { 5.f, 5.f, 8.f, -7.f, 6.f };
const JBFLOAT rmlfx[] = {
  0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
  2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 3.f, 3.f, 3.f, 3.f, 3.f, 3.f,
  4.f, 4.f, 4.f, 4.f, 4.f, 4.f, 5.f, 5.f, 5.f, 5.f, 5.f, 5.f };
const JBFLOAT rmlfy[] = {
  0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f,
  0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f,
  0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f };
const JBFLOAT rmlff1[] = {
  0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f,
  2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f,
  4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f };
const JBFLOAT rmlff2[] = {
  10.f, 12.f, 14.f, 16.f, 18.f, 20.f, 9.f, 11.f, 13.f, 15.f, 17.f, 19.f,
  8.f, 10.f, 12.f, 14.f, 16.f, 18.f, 7.f, 9.f, 11.f, 13.f, 15.f, 17.f,
  6.f, 8.f, 10.f, 12.f, 14.f, 16.f, 5.f, 7.f, 9.f, 11.f, 13.f, 15.f };
JBFLOAT rmefx[] = {
  1.f, 1.f, 1.f, 1.f, 1.f, 2.f, 2.f, 2.f, 2.f, 2.f,
  3.f, 3.f, 3.f, 3.f, 3.f, 4.f, 4.f, 4.f, 4.f, 4.f,
  5.f, 5.f, 5.f, 5.f, 5.f };
JBFLOAT rmefy[] = {
  1.f, 2.f, 3.f, 4.f, 5.f, 1.f, 2.f, 3.f, 4.f, 5.f,
  1.f, 2.f, 3.f, 4.f, 5.f, 1.f, 2.f, 3.f, 4.f, 5.f,
  1.f, 2.f, 3.f, 4.f, 5.f };
JBFLOAT rmeff1[] = {
  60.f, 30.f, 20.f, 15.f, 12.f, 120.f, 60.f, 40.f, 30.f, 24.f,
  180.f, 90.f, 60.f, 45.f, 36.f, 240.f, 120.f, 80.f, 60.f, 48.f,
  300.f, 150.f, 100.f, 75.f, 60.f };

#elif JBM_LOW_PRECISION == 2

const JBFLOAT pf[15] = { 1., 2., 4., 8., 16., 32., 64., 128., 256.,
  512., 1024., 2048., 4096., 8192., 16384. };
const JBFLOAT cf0 = 0., cf1 = 1., cf2 = 2., cf3 = 3., cf05 = 0.5;
JBFLOAT mxf[] = {
  1., 3., 2., 1., 18.,
  2., 4., 8., 0., 18.,
  3., -1., 4., 2., 4.,
  4., 0., 3., 1., 11.
};
const JBFLOAT myf[] = { 3., 5., -1., 2. };
JBFLOAT Cf[] = { 1., -1., -1. }, Df[] = { 2., 2., 2., 1. },
  Ef[] = { 1., 1., -1. }, Hf[] = { 5., 9., -7., 6. },
  Czf[] = { 1., -1., 0., -1. }, Dzf[] = { 2., 2., 0., 2., 1. },
  Ezf[] = { 1., 0., 1., -1. }, Hzf[] = { 5., 7., -1., -4., 6. },
  Cpf[] = { 1., -1., -1. }, Dpf[] = { 2., 2., 2., 1. },
  Epf[] = { 1., 1., -1. }, Bpf[] = { 1., -1. }, Fpf[] = { -1., 1.},
  Hpf[] = { 3., 17., -6., 3. },
  Cpzf[] = { 1., -1., 0., -1. }, Dpzf[] = { 2., 2., 0., 2., 1. },
  Epzf[] = { 1., 0., 1., -1. }, Bpzf[] = { 1., -1., 0. },
  Fpzf[] = { 0., -1., 1.}, Hpzf[] = { 5., 5., 8., -7., 6. };
const JBFLOAT rmlfx[] = {
  0., 0., 0., 0., 0., 0., 1., 1., 1., 1., 1., 1.,
  2., 2., 2., 2., 2., 2., 3., 3., 3., 3., 3., 3.,
  4., 4., 4., 4., 4., 4., 5., 5., 5., 5., 5., 5. };
const JBFLOAT rmlfy[] = {
  0., 1., 2., 3., 4., 5., 0., 1., 2., 3., 4., 5.,
  0., 1., 2., 3., 4., 5., 0., 1., 2., 3., 4., 5.,
  0., 1., 2., 3., 4., 5., 0., 1., 2., 3., 4., 5. };
const JBFLOAT rmlff1[] = {
  0., 1., 2., 3., 4., 5., 1., 2., 3., 4., 5., 6.,
  2., 3., 4., 5., 6., 7., 3., 4., 5., 6., 7., 8.,
  4., 5., 6., 7., 8., 9., 5., 6., 7., 8., 9., 10. };
const JBFLOAT rmlff2[] = {
  10., 12., 14., 16., 18., 20., 9., 11., 13., 15., 17., 19.,
  8., 10., 12., 14., 16., 18., 7., 9., 11., 13., 15., 17.,
  6., 8., 10., 12., 14., 16., 5., 7., 9., 11., 13., 15. };
JBFLOAT rmefx[] = {
  1., 1., 1., 1., 1., 2., 2., 2., 2., 2.,
  3., 3., 3., 3., 3., 4., 4., 4., 4., 4.,
  5., 5., 5., 5., 5. };
JBFLOAT rmefy[] = {
  1., 2., 3., 4., 5., 1., 2., 3., 4., 5.,
  1., 2., 3., 4., 5., 1., 2., 3., 4., 5.,
  1., 2., 3., 4., 5. };
JBFLOAT rmeff1[] = {
  60., 30., 20., 15., 12., 120., 60., 40., 30., 24.,
  180., 90., 60., 45., 36., 240., 120., 80., 60., 48.,
  300., 150., 100., 75., 60. };

#elif JBM_LOW_PRECISION == 3

const JBFLOAT pf[15] = { 1.L, 2.L, 4.L, 8.L, 16.L, 32.L, 64.L, 128.L, 256.L,
  512.L, 1024.L, 2048.L, 4096.L, 8192.L, 16384.L };
const JBFLOAT cf0 = 0.L, cf1 = 1.L, cf2 = 2.L, cf3 = 3.L, cf05 = 0.5L;
JBFLOAT mxf[] = {
  1.L, 3.L, 2.L, 1.L, 18.L,
  2.L, 4.L, 8.L, 0.L, 18.L,
  3.L, -1.L, 4.L, 2.L, 4.L,
  4.L, 0.L, 3.L, 1.L, 11.L
};
const JBFLOAT myf[] = { 3.L, 5.L, -1.L, 2.L };
JBFLOAT Cf[] = { 1.L, -1.L, -1.L }, Df[] = { 2.L, 2.L, 2.L, 1.L },
  Ef[] = { 1.L, 1.L, -1.L }, Hf[] = { 5.L, 9.L, -7.L, 6.L },
  Czf[] = { 1.L, -1.L, 0.L, -1.L }, Dzf[] = { 2.L, 2.L, 0.L, 2.L, 1.L },
  Ezf[] = { 1.L, 0.L, 1.L, -1.L }, Hzf[] = { 5.L, 7.L, -1.L, -4.L, 6.L },
  Cpf[] = { 1.L, -1.L, -1.L }, Dpf[] = { 2.L, 2.L, 2.L, 1.L },
  Epf[] = { 1.L, 1.L, -1.L }, Bpf[] = { 1.L, -1.L }, Fpf[] = { -1.L, 1.L},
  Hpf[] = { 3.L, 17.L, -6.L, 3.L },
  Cpzf[] = { 1.L, -1.L, 0.L, -1.L }, Dpzf[] = { 2.L, 2.L, 0.L, 2.L, 1.L },
  Epzf[] = { 1.L, 0.L, 1.L, -1.L }, Bpzf[] = { 1.L, -1.L, 0.L },
  Fpzf[] = { 0.L, -1.L, 1.L}, Hpzf[] = { 5.L, 5.L, 8.L, -7.L, 6.L };
const JBFLOAT rmlfx[] = {
  0.L, 0.L, 0.L, 0.L, 0.L, 0.L, 1.L, 1.L, 1.L, 1.L, 1.L, 1.L,
  2.L, 2.L, 2.L, 2.L, 2.L, 2.L, 3.L, 3.L, 3.L, 3.L, 3.L, 3.L,
  4.L, 4.L, 4.L, 4.L, 4.L, 4.L, 5.L, 5.L, 5.L, 5.L, 5.L, 5.L };
const JBFLOAT rmlfy[] = {
  0.L, 1.L, 2.L, 3.L, 4.L, 5.L, 0.L, 1.L, 2.L, 3.L, 4.L, 5.L,
  0.L, 1.L, 2.L, 3.L, 4.L, 5.L, 0.L, 1.L, 2.L, 3.L, 4.L, 5.L,
  0.L, 1.L, 2.L, 3.L, 4.L, 5.L, 0.L, 1.L, 2.L, 3.L, 4.L, 5.L };
const JBFLOAT rmlff1[] = {
  0.L, 1.L, 2.L, 3.L, 4.L, 5.L, 1.L, 2.L, 3.L, 4.L, 5.L, 6.L,
  2.L, 3.L, 4.L, 5.L, 6.L, 7.L, 3.L, 4.L, 5.L, 6.L, 7.L, 8.L,
  4.L, 5.L, 6.L, 7.L, 8.L, 9.L, 5.L, 6.L, 7.L, 8.L, 9.L, 10.L };
const JBFLOAT rmlff2[] = {
  10.L, 12.L, 14.L, 16.L, 18.L, 20.L, 9.L, 11.L, 13.L, 15.L, 17.L, 19.L,
  8.L, 10.L, 12.L, 14.L, 16.L, 18.L, 7.L, 9.L, 11.L, 13.L, 15.L, 17.L,
  6.L, 8.L, 10.L, 12.L, 14.L, 16.L, 5.L, 7.L, 9.L, 11.L, 13.L, 15.L };
JBFLOAT rmefx[] = {
  1.L, 1.L, 1.L, 1.L, 1.L, 2.L, 2.L, 2.L, 2.L, 2.L,
  3.L, 3.L, 3.L, 3.L, 3.L, 4.L, 4.L, 4.L, 4.L, 4.L,
  5.L, 5.L, 5.L, 5.L, 5.L };
JBFLOAT rmefy[] = {
  1.L, 2.L, 3.L, 4.L, 5.L, 1.L, 2.L, 3.L, 4.L, 5.L,
  1.L, 2.L, 3.L, 4.L, 5.L, 1.L, 2.L, 3.L, 4.L, 5.L,
  1.L, 2.L, 3.L, 4.L, 5.L };
JBFLOAT rmeff1[] = {
  60.L, 30.L, 20.L, 15.L, 12.L, 120.L, 60.L, 40.L, 30.L, 24.L,
  180.L, 90.L, 60.L, 45.L, 36.L, 240.L, 120.L, 80.L, 60.L, 48.L,
  300.L, 150.L, 100.L, 75.L, 60.L };

#elif JBM_LOW_PRECISION == 4

const JBFLOAT pf[15] = { 1.Q, 2.Q, 4.Q, 8.Q, 16.Q, 32.Q, 64.Q, 128.Q, 256.Q,
  512.Q, 1024.Q, 2048.Q, 4096.Q, 8192.Q, 16384.Q };
const JBFLOAT cf0 = 0.Q, cf1 = 1.Q, cf2 = 2.Q, cf3 = 3.Q, cf05 = 0.5Q;
JBFLOAT mxf[] = {
  1.Q, 3.Q, 2.Q, 1.Q, 18.Q,
  2.Q, 4.Q, 8.Q, 0.Q, 18.Q,
  3.Q, -1.Q, 4.Q, 2.Q, 4.Q,
  4.Q, 0.Q, 3.Q, 1.Q, 11.Q
};
const JBFLOAT myf[] = { 3.Q, 5.Q, -1.Q, 2.Q };
JBFLOAT Cf[] = { 1.Q, -1.Q, -1.Q }, Df[] = { 2.Q, 2.Q, 2.Q, 1.Q },
  Ef[] = { 1.Q, 1.Q, -1.Q }, Hf[] = { 5.Q, 9.Q, -7.Q, 6.Q },
  Czf[] = { 1.Q, -1.Q, 0.Q, -1.Q }, Dzf[] = { 2.Q, 2.Q, 0.Q, 2.Q, 1.Q },
  Ezf[] = { 1.Q, 0.Q, 1.Q, -1.Q }, Hzf[] = { 5.Q, 7.Q, -1.Q, -4.Q, 6.Q },
  Cpf[] = { 1.Q, -1.Q, -1.Q }, Dpf[] = { 2.Q, 2.Q, 2.Q, 1.Q },
  Epf[] = { 1.Q, 1.Q, -1.Q }, Bpf[] = { 1.Q, -1.Q }, Fpf[] = { -1.Q, 1.Q},
  Hpf[] = { 3.Q, 17.Q, -6.Q, 3.Q },
  Cpzf[] = { 1.Q, -1.Q, 0.Q, -1.Q }, Dpzf[] = { 2.Q, 2.Q, 0.Q, 2.Q, 1.Q },
  Epzf[] = { 1.Q, 0.Q, 1.Q, -1.Q }, Bpzf[] = { 1.Q, -1.Q, 0.Q },
  Fpzf[] = { 0.Q, -1.Q, 1.Q}, Hpzf[] = { 5.Q, 5.Q, 8.Q, -7.Q, 6.Q };
const JBFLOAT rmlfx[] = {
  0.Q, 0.Q, 0.Q, 0.Q, 0.Q, 0.Q, 1.Q, 1.Q, 1.Q, 1.Q, 1.Q, 1.Q,
  2.Q, 2.Q, 2.Q, 2.Q, 2.Q, 2.Q, 3.Q, 3.Q, 3.Q, 3.Q, 3.Q, 3.Q,
  4.Q, 4.Q, 4.Q, 4.Q, 4.Q, 4.Q, 5.Q, 5.Q, 5.Q, 5.Q, 5.Q, 5.Q };
const JBFLOAT rmlfy[] = {
  0.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q, 0.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q,
  0.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q, 0.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q,
  0.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q, 0.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q };
const JBFLOAT rmlff1[] = {
  0.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q, 6.Q,
  2.Q, 3.Q, 4.Q, 5.Q, 6.Q, 7.Q, 3.Q, 4.Q, 5.Q, 6.Q, 7.Q, 8.Q,
  4.Q, 5.Q, 6.Q, 7.Q, 8.Q, 9.Q, 5.Q, 6.Q, 7.Q, 8.Q, 9.Q, 10.Q };
const JBFLOAT rmlff2[] = {
  10.Q, 12.Q, 14.Q, 16.Q, 18.Q, 20.Q, 9.Q, 11.Q, 13.Q, 15.Q, 17.Q, 19.Q,
  8.Q, 10.Q, 12.Q, 14.Q, 16.Q, 18.Q, 7.Q, 9.Q, 11.Q, 13.Q, 15.Q, 17.Q,
  6.Q, 8.Q, 10.Q, 12.Q, 14.Q, 16.Q, 5.Q, 7.Q, 9.Q, 11.Q, 13.Q, 15.Q };
JBFLOAT rmefx[] = {
  1.Q, 1.Q, 1.Q, 1.Q, 1.Q, 2.Q, 2.Q, 2.Q, 2.Q, 2.Q,
  3.Q, 3.Q, 3.Q, 3.Q, 3.Q, 4.Q, 4.Q, 4.Q, 4.Q, 4.Q,
  5.Q, 5.Q, 5.Q, 5.Q, 5.Q };
JBFLOAT rmefy[] = {
  1.Q, 2.Q, 3.Q, 4.Q, 5.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q,
  1.Q, 2.Q, 3.Q, 4.Q, 5.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q,
  1.Q, 2.Q, 3.Q, 4.Q, 5.Q };
JBFLOAT rmeff1[] = {
  60.Q, 30.Q, 20.Q, 15.Q, 12.Q, 120.Q, 60.Q, 40.Q, 30.Q, 24.Q,
  180.Q, 90.Q, 60.Q, 45.Q, 36.Q, 240.Q, 120.Q, 80.Q, 60.Q, 48.Q,
  300.Q, 150.Q, 100.Q, 75.Q, 60.Q };

#endif

#if JBM_HIGH_PRECISION == 1

const JBDOUBLE pd[15] = { 1.f, 2.f, 4.f, 8.f, 16.f, 32.f, 64.f, 128.f, 256.f,
  512.f, 1024.f, 2048.f, 4096.f, 8192.f, 16384.f };
const JBDOUBLE cd0 = 0.f, cd1 = 1.f, cd2 = 2.f, cd3 = 3.f, cd05 = 0.5f;
JBDOUBLE mxd[] = {
  1.f, 3.f, 2.f, 1.f, 18.f,
  2.f, 4.f, 8.f, 0.f, 18.f,
  3.f, -1.f, 4.f, 2.f, 4.f,
  4.f, 0.f, 3.f, 1.f, 11.f
};
const JBDOUBLE myd[] = { 3.f, 5.f, -1.f, 2.f };
JBDOUBLE Cd[] = { 1.f, -1.f, -1.f }, Dd[] = { 2.f, 2.f, 2.f, 1.f },
  Ed[] = { 1.f, 1.f, -1.f }, Hd[] = { 5.f, 9.f, -7.f, 6.f },
  Czd[] = { 1.f, -1.f, 0.f, -1.f }, Dzd[] = { 2.f, 2.f, 0.f, 2.f, 1.f },
  Ezd[] = { 1.f, 0.f, 1.f, -1.f }, Hzd[] = { 5.f, 7.f, -1.f, -4.f, 6.f },
  Cpd[] = { 1.f, -1.f, -1.f }, Dpd[] = { 2.f, 2.f, 2.f, 1.f },
  Epd[] = { 1.f, 1.f, -1.f }, Bpd[] = { 1.f, -1.f }, Fpd[] = { -1.f, 1.f},
  Hpd[] = { 3.f, 17.f, -6.f, 3.f },
  Cpzd[] = { 1.f, -1.f, 0.f, -1.f }, Dpzd[] = { 2.f, 2.f, 0.f, 2.f, 1.f },
  Epzd[] = { 1.f, 0.f, 1.f, -1.f }, Bpzd[] = { 1.f, -1.f, 0.f },
  Fpzd[] = { 0.f, -1.f, 1.f}, Hpzd[] = { 5.f, 5.f, 8.f, -7.f, 6.f };
const JBDOUBLE rmldx[] = {
  0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
  2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 3.f, 3.f, 3.f, 3.f, 3.f, 3.f,
  4.f, 4.f, 4.f, 4.f, 4.f, 4.f, 5.f, 5.f, 5.f, 5.f, 5.f, 5.f };
const JBDOUBLE rmldy[] = {
  0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f,
  0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f,
  0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f };
const JBDOUBLE rmldf1[] = {
  0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f,
  2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f,
  4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f };
const JBDOUBLE rmldf2[] = {
  10.f, 12.f, 14.f, 16.f, 18.f, 20.f, 9.f, 11.f, 13.f, 15.f, 17.f, 19.f,
  8.f, 10.f, 12.f, 14.f, 16.f, 18.f, 7.f, 9.f, 11.f, 13.f, 15.f, 17.f,
  6.f, 8.f, 10.f, 12.f, 14.f, 16.f, 5.f, 7.f, 9.f, 11.f, 13.f, 15.f };
JBFLOAT rmedx[] = {
  1.f, 1.f, 1.f, 1.f, 1.f, 2.f, 2.f, 2.f, 2.f, 2.f,
  3.f, 3.f, 3.f, 3.f, 3.f, 4.f, 4.f, 4.f, 4.f, 4.f,
  5.f, 5.f, 5.f, 5.f, 5.f };
JBFLOAT rmedy[] = {
  1.f, 2.f, 3.f, 4.f, 5.f, 1.f, 2.f, 3.f, 4.f, 5.f,
  1.f, 2.f, 3.f, 4.f, 5.f, 1.f, 2.f, 3.f, 4.f, 5.f,
  1.f, 2.f, 3.f, 4.f, 5.f };
JBFLOAT rmedf1[] = {
  60.f, 30.f, 20.f, 15.f, 12.f, 120.f, 60.f, 40.f, 30.f, 24.f,
  180.f, 90.f, 60.f, 45.f, 36.f, 240.f, 120.f, 80.f, 60.f, 48.f,
  300.f, 150.f, 100.f, 75.f, 60.f };

#elif JBM_HIGH_PRECISION == 2

const JBDOUBLE pd[15] = { 1., 2., 4., 8., 16., 32., 64., 128., 256.,
  512., 1024., 2048., 4096., 8192., 16384. };
const JBDOUBLE cd0 = 0., cd1 = 1., cd2 = 2., cd3 = 3., cd05 = 0.5;
JBDOUBLE mxd[] = {
  1., 3., 2., 1., 18.,
  2., 4., 8., 0., 18.,
  3., -1., 4., 2., 4.,
  4., 0., 3., 1., 11.
};
const JBDOUBLE myd[] = { 3., 5., -1., 2. };
JBDOUBLE Cd[] = { 1., -1., -1. }, Dd[] = { 2., 2., 2., 1. },
  Ed[] = { 1., 1., -1. }, Hd[] = { 5., 9., -7., 6. },
  Czd[] = { 1., -1., 0., -1. }, Dzd[] = { 2., 2., 0., 2., 1. },
  Ezd[] = { 1., 0., 1., -1. }, Hzd[] = { 5., 7., -1., -4., 6. },
  Cpd[] = { 1., -1., -1. }, Dpd[] = { 2., 2., 2., 1. },
  Epd[] = { 1., 1., -1. }, Bpd[] = { 1., -1. }, Fpd[] = { -1., 1.},
  Hpd[] = { 3., 17., -6., 3. },
  Cpzd[] = { 1., -1., 0., -1. }, Dpzd[] = { 2., 2., 0., 2., 1. },
  Epzd[] = { 1., 0., 1., -1. }, Bpzd[] = { 1., -1., 0. },
  Fpzd[] = { 0., -1., 1.}, Hpzd[] = { 5., 5., 8., -7., 6. };
const JBDOUBLE rmldx[] = {
  0., 0., 0., 0., 0., 0., 1., 1., 1., 1., 1., 1.,
  2., 2., 2., 2., 2., 2., 3., 3., 3., 3., 3., 3.,
  4., 4., 4., 4., 4., 4., 5., 5., 5., 5., 5., 5. };
const JBDOUBLE rmldy[] = {
  0., 1., 2., 3., 4., 5., 0., 1., 2., 3., 4., 5.,
  0., 1., 2., 3., 4., 5., 0., 1., 2., 3., 4., 5.,
  0., 1., 2., 3., 4., 5., 0., 1., 2., 3., 4., 5. };
const JBDOUBLE rmldf1[] = {
  0., 1., 2., 3., 4., 5., 1., 2., 3., 4., 5., 6.,
  2., 3., 4., 5., 6., 7., 3., 4., 5., 6., 7., 8.,
  4., 5., 6., 7., 8., 9., 5., 6., 7., 8., 9., 10. };
const JBDOUBLE rmldf2[] = {
  10., 12., 14., 16., 18., 20., 9., 11., 13., 15., 17., 19.,
  8., 10., 12., 14., 16., 18., 7., 9., 11., 13., 15., 17.,
  6., 8., 10., 12., 14., 16., 5., 7., 9., 11., 13., 15. };
JBFLOAT rmedx[] = {
  1., 1., 1., 1., 1., 2., 2., 2., 2., 2.,
  3., 3., 3., 3., 3., 4., 4., 4., 4., 4.,
  5., 5., 5., 5., 5. };
JBFLOAT rmedy[] = {
  1., 2., 3., 4., 5., 1., 2., 3., 4., 5.,
  1., 2., 3., 4., 5., 1., 2., 3., 4., 5.,
  1., 2., 3., 4., 5. };
JBFLOAT rmedf1[] = {
  60., 30., 20., 15., 12., 120., 60., 40., 30., 24.,
  180., 90., 60., 45., 36., 240., 120., 80., 60., 48.,
  300., 150., 100., 75., 60. };

#elif JBM_HIGH_PRECISION == 3

const JBDOUBLE pd[15] = { 1.L, 2.L, 4.L, 8.L, 16.L, 32.L, 64.L, 128.L, 256.L,
  512.L, 1024.L, 2048.L, 4096.L, 8192.L, 16384.L };
const JBDOUBLE cd0 = 0.L, cd1 = 1.L, cd2 = 2.L, cd3 = 3.L, cd05 = 0.5L;
JBDOUBLE mxd[] = {
  1.L, 3.L, 2.L, 1.L, 18.L,
  2.L, 4.L, 8.L, 0.L, 18.L,
  3.L, -1.L, 4.L, 2.L, 4.L,
  4.L, 0.L, 3.L, 1.L, 11.L
};
const JBDOUBLE myd[] = { 3.L, 5.L, -1.L, 2.L };
JBDOUBLE Cd[] = { 1.L, -1.L, -1.L }, Dd[] = { 2.L, 2.L, 2.L, 1.L },
  Ed[] = { 1.L, 1.L, -1.L }, Hd[] = { 5.L, 9.L, -7.L, 6.L },
  Czd[] = { 1.L, -1.L, 0.L, -1.L }, Dzd[] = { 2.L, 2.L, 0.L, 2.L, 1.L },
  Ezd[] = { 1.L, 0.L, 1.L, -1.L }, Hzd[] = { 5.L, 7.L, -1.L, -4.L, 6.L },
  Cpd[] = { 1.L, -1.L, -1.L }, Dpd[] = { 2.L, 2.L, 2.L, 1.L },
  Epd[] = { 1.L, 1.L, -1.L }, Bpd[] = { 1.L, -1.L }, Fpd[] = { -1.L, 1.L},
  Hpd[] = { 3.L, 17.L, -6.L, 3.L },
  Cpzd[] = { 1.L, -1.L, 0.L, -1.L }, Dpzd[] = { 2.L, 2.L, 0.L, 2.L, 1.L },
  Epzd[] = { 1.L, 0.L, 1.L, -1.L }, Bpzd[] = { 1.L, -1.L, 0.L },
  Fpzd[] = { 0.L, -1.L, 1.L}, Hpzd[] = { 5.L, 5.L, 8.L, -7.L, 6.L };
const JBDOUBLE rmldx[] = {
  0.L, 0.L, 0.L, 0.L, 0.L, 0.L, 1.L, 1.L, 1.L, 1.L, 1.L, 1.L,
  2.L, 2.L, 2.L, 2.L, 2.L, 2.L, 3.L, 3.L, 3.L, 3.L, 3.L, 3.L,
  4.L, 4.L, 4.L, 4.L, 4.L, 4.L, 5.L, 5.L, 5.L, 5.L, 5.L, 5.L };
const JBDOUBLE rmldy[] = {
  0.L, 1.L, 2.L, 3.L, 4.L, 5.L, 0.L, 1.L, 2.L, 3.L, 4.L, 5.L,
  0.L, 1.L, 2.L, 3.L, 4.L, 5.L, 0.L, 1.L, 2.L, 3.L, 4.L, 5.L,
  0.L, 1.L, 2.L, 3.L, 4.L, 5.L, 0.L, 1.L, 2.L, 3.L, 4.L, 5.L };
const JBDOUBLE rmldf1[] = {
  0.L, 1.L, 2.L, 3.L, 4.L, 5.L, 1.L, 2.L, 3.L, 4.L, 5.L, 6.L,
  2.L, 3.L, 4.L, 5.L, 6.L, 7.L, 3.L, 4.L, 5.L, 6.L, 7.L, 8.L,
  4.L, 5.L, 6.L, 7.L, 8.L, 9.L, 5.L, 6.L, 7.L, 8.L, 9.L, 10.L };
const JBDOUBLE rmldf2[] = {
  10.L, 12.L, 14.L, 16.L, 18.L, 20.L, 9.L, 11.L, 13.L, 15.L, 17.L, 19.L,
  8.L, 10.L, 12.L, 14.L, 16.L, 18.L, 7.L, 9.L, 11.L, 13.L, 15.L, 17.L,
  6.L, 8.L, 10.L, 12.L, 14.L, 16.L, 5.L, 7.L, 9.L, 11.L, 13.L, 15.L };
JBFLOAT rmedx[] = {
  1.L, 1.L, 1.L, 1.L, 1.L, 2.L, 2.L, 2.L, 2.L, 2.L,
  3.L, 3.L, 3.L, 3.L, 3.L, 4.L, 4.L, 4.L, 4.L, 4.L,
  5.L, 5.L, 5.L, 5.L, 5.L };
JBFLOAT rmedy[] = {
  1.L, 2.L, 3.L, 4.L, 5.L, 1.L, 2.L, 3.L, 4.L, 5.L,
  1.L, 2.L, 3.L, 4.L, 5.L, 1.L, 2.L, 3.L, 4.L, 5.L,
  1.L, 2.L, 3.L, 4.L, 5.L };
JBFLOAT rmedf1[] = {
  60.L, 30.L, 20.L, 15.L, 12.L, 120.L, 60.L, 40.L, 30.L, 24.L,
  180.L, 90.L, 60.L, 45.L, 36.L, 240.L, 120.L, 80.L, 60.L, 48.L,
  300.L, 150.L, 100.L, 75.L, 60.L };

#elif JBM_HIGH_PRECISION == 4

const JBDOUBLE pd[15] = { 1.Q, 2.Q, 4.Q, 8.Q, 16.Q, 32.Q, 64.Q, 128.Q, 256.Q,
  512.Q, 1024.Q, 2048.Q, 4096.Q, 8192.Q, 16384.Q };
const JBDOUBLE cd0 = 0.Q, cd1 = 1.Q, cd2 = 2.Q, cd3 = 3.Q, cd05 = 0.5Q;
JBDOUBLE mxd[] = {
  1.Q, 3.Q, 2.Q, 1.Q, 18.Q,
  2.Q, 4.Q, 8.Q, 0.Q, 18.Q,
  3.Q, -1.Q, 4.Q, 2.Q, 4.Q,
  4.Q, 0.Q, 3.Q, 1.Q, 11.Q
};
const JBDOUBLE myd[] = { 3.Q, 5.Q, -1.Q, 2.Q };
JBDOUBLE Cd[] = { 1.Q, -1.Q, -1.Q }, Dd[] = { 2.Q, 2.Q, 2.Q, 1.Q },
  Ed[] = { 1.Q, 1.Q, -1.Q }, Hd[] = { 5.Q, 9.Q, -7.Q, 6.Q },
  Czd[] = { 1.Q, -1.Q, 0.Q, -1.Q }, Dzd[] = { 2.Q, 2.Q, 0.Q, 2.Q, 1.Q },
  Ezd[] = { 1.Q, 0.Q, 1.Q, -1.Q }, Hzd[] = { 5.Q, 7.Q, -1.Q, -4.Q, 6.Q },
  Cpd[] = { 1.Q, -1.Q, -1.Q }, Dpd[] = { 2.Q, 2.Q, 2.Q, 1.Q },
  Epd[] = { 1.Q, 1.Q, -1.Q }, Bpd[] = { 1.Q, -1.Q }, Fpd[] = { -1.Q, 1.Q},
  Hpd[] = { 3.Q, 17.Q, -6.Q, 3.Q },
  Cpzd[] = { 1.Q, -1.Q, 0.Q, -1.Q }, Dpzd[] = { 2.Q, 2.Q, 0.Q, 2.Q, 1.Q },
  Epzd[] = { 1.Q, 0.Q, 1.Q, -1.Q }, Bpzd[] = { 1.Q, -1.Q, 0.Q },
  Fpzd[] = { 0.Q, -1.Q, 1.Q}, Hpzd[] = { 5.Q, 5.Q, 8.Q, -7.Q, 6.Q };
const JBDOUBLE rmldx[] = {
  0.Q, 0.Q, 0.Q, 0.Q, 0.Q, 0.Q, 1.Q, 1.Q, 1.Q, 1.Q, 1.Q, 1.Q,
  2.Q, 2.Q, 2.Q, 2.Q, 2.Q, 2.Q, 3.Q, 3.Q, 3.Q, 3.Q, 3.Q, 3.Q,
  4.Q, 4.Q, 4.Q, 4.Q, 4.Q, 4.Q, 5.Q, 5.Q, 5.Q, 5.Q, 5.Q, 5.Q };
const JBDOUBLE rmldy[] = {
  0.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q, 0.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q,
  0.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q, 0.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q,
  0.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q, 0.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q };
const JBDOUBLE rmldf1[] = {
  0.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q, 6.Q,
  2.Q, 3.Q, 4.Q, 5.Q, 6.Q, 7.Q, 3.Q, 4.Q, 5.Q, 6.Q, 7.Q, 8.Q,
  4.Q, 5.Q, 6.Q, 7.Q, 8.Q, 9.Q, 5.Q, 6.Q, 7.Q, 8.Q, 9.Q, 10.Q };
const JBDOUBLE rmldf2[] = {
  10.Q, 12.Q, 14.Q, 16.Q, 18.Q, 20.Q, 9.Q, 11.Q, 13.Q, 15.Q, 17.Q, 19.Q,
  8.Q, 10.Q, 12.Q, 14.Q, 16.Q, 18.Q, 7.Q, 9.Q, 11.Q, 13.Q, 15.Q, 17.Q,
  6.Q, 8.Q, 10.Q, 12.Q, 14.Q, 16.Q, 5.Q, 7.Q, 9.Q, 11.Q, 13.Q, 15.Q };
JBFLOAT rmedx[] = {
  1.Q, 1.Q, 1.Q, 1.Q, 1.Q, 2.Q, 2.Q, 2.Q, 2.Q, 2.Q,
  3.Q, 3.Q, 3.Q, 3.Q, 3.Q, 4.Q, 4.Q, 4.Q, 4.Q, 4.Q,
  5.Q, 5.Q, 5.Q, 5.Q, 5.Q };
JBFLOAT rmedy[] = {
  1.Q, 2.Q, 3.Q, 4.Q, 5.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q,
  1.Q, 2.Q, 3.Q, 4.Q, 5.Q, 1.Q, 2.Q, 3.Q, 4.Q, 5.Q,
  1.Q, 2.Q, 3.Q, 4.Q, 5.Q };
JBFLOAT rmedf1[] = {
  60.Q, 30.Q, 20.Q, 15.Q, 12.Q, 120.Q, 60.Q, 40.Q, 30.Q, 24.Q,
  180.Q, 90.Q, 60.Q, 45.Q, 36.Q, 240.Q, 120.Q, 80.Q, 60.Q, 48.Q,
  300.Q, 150.Q, 100.Q, 75.Q, 60.Q };

#endif

const double p_1[12] = { 1., 2., 4., 8., 16., 32., 64., 128., 256.,
  512., 1024., 2048. };
const JBFLOAT *rmlf1[] = { rmlff1, rmlfx, rmlfy };
const JBFLOAT *rmlf2[] = { rmlff2, rmlfx, rmlfy };
const JBFLOAT *rmef1[] = { rmeff1, rmefx, rmefy };
const JBDOUBLE *rmld1[] = { rmldf1, rmldx, rmldy };
const JBDOUBLE *rmld2[] = { rmldf2, rmldx, rmldy };
const JBDOUBLE *rmed1[] = { rmedf1, rmedx, rmedy };

JBFLOAT
fn0f (JBFLOAT x)
{
  return cf1;
}

JBFLOAT
fn1f (JBFLOAT x)
{
  return x;
}

JBFLOAT
fn2f (JBFLOAT x)
{
  return x * fn1f (x);
}

JBFLOAT
fn3f (JBFLOAT x)
{
  return x * fn2f (x);
}

JBFLOAT
fn4f (JBFLOAT x)
{
  return x * fn3f (x);
}

JBFLOAT
fn5f (JBFLOAT x)
{
  return x * fn4f (x);
}

JBFLOAT
fn6f (JBFLOAT x)
{
  return x * fn5f (x);
}

JBFLOAT
fn7f (JBFLOAT x)
{
  return x * fn6f (x);
}

JBFLOAT
fn8f (JBFLOAT x)
{
  return x * fn7f (x);
}

JBFLOAT
fn9f (JBFLOAT x)
{
  return x * fn8f (x);
}

JBFLOAT
fn10f (JBFLOAT x)
{
  return x * fn9f (x);
}

JBFLOAT
fn11f (JBFLOAT x)
{
  return x * fn10f (x);
}

JBFLOAT
fn12f (JBFLOAT x)
{
  return x * fn11f (x);
}

JBFLOAT
fn13f (JBFLOAT x)
{
  return x * fn12f (x);
}

JBFLOAT
fn14f (JBFLOAT x)
{
  return x * fn13f (x);
}

JBDOUBLE
fn0d (JBDOUBLE x)
{
  return cf1;
}

JBDOUBLE
fn1d (JBDOUBLE x)
{
  return x;
}

JBDOUBLE
fn2d (JBDOUBLE x)
{
  return x * fn1d (x);
}

JBDOUBLE
fn3d (JBDOUBLE x)
{
  return x * fn2d (x);
}

JBDOUBLE
fn4d (JBDOUBLE x)
{
  return x * fn3d (x);
}

JBDOUBLE
fn5d (JBDOUBLE x)
{
  return x * fn4d (x);
}

JBDOUBLE
fn6d (JBDOUBLE x)
{
  return x * fn5d (x);
}

JBDOUBLE
fn7d (JBDOUBLE x)
{
  return x * fn6d (x);
}

JBDOUBLE
fn8d (JBDOUBLE x)
{
  return x * fn7d (x);
}

JBDOUBLE
fn9d (JBDOUBLE x)
{
  return x * fn8d (x);
}

JBDOUBLE
fn10d (JBDOUBLE x)
{
  return x * fn9d (x);
}

JBDOUBLE
fn11d (JBDOUBLE x)
{
  return x * fn10d (x);
}

JBDOUBLE
fn12d (JBDOUBLE x)
{
  return x * fn11d (x);
}

JBDOUBLE
fn13d (JBDOUBLE x)
{
  return x * fn12d (x);
}

JBDOUBLE
fn14d (JBDOUBLE x)
{
  return x * fn13d (x);
}

#ifdef __SSE4_2__

__m128d
fn0_128 (__m128d x)
{
  return _mm_set1_pd (1.);
}

__m128d
fn1_128 (__m128d x)
{
  return x;
}

__m128d
fn2_128 (__m128d x)
{
  return x * fn1_128 (x);
}

__m128d
fn3_128 (__m128d x)
{
  return x * fn2_128 (x);
}

__m128d
fn4_128 (__m128d x)
{
  return x * fn3_128 (x);
}

__m128d
fn5_128 (__m128d x)
{
  return x * fn4_128 (x);
}

__m128d
fn6_128 (__m128d x)
{
  return x * fn5_128 (x);
}

__m128d
fn7_128 (__m128d x)
{
  return x * fn6_128 (x);
}

__m128d
fn8_128 (__m128d x)
{
  return x * fn7_128 (x);
}

__m128d
fn9_128 (__m128d x)
{
  return x * fn8_128 (x);
}

__m128d
fn10_128 (__m128d x)
{
  return x * fn9_128 (x);
}

__m128d
fn11_128 (__m128d x)
{
  return x * fn10_128 (x);
}

__m128d
fn12_128 (__m128d x)
{
  return x * fn11_128 (x);
}

__m128d
fn13_128 (__m128d x)
{
  return x * fn12_128 (x);
}

__m128d
fn14_128 (__m128d x)
{
  return x * fn13_128 (x);
}

#endif

#ifdef __AVX__

__m256d
fn0_256 (__m256d x)
{
  return _mm256_set1_pd (1.);
}

__m256d
fn1_256 (__m256d x)
{
  return x;
}

__m256d
fn2_256 (__m256d x)
{
  return x * fn1_256 (x);
}

__m256d
fn3_256 (__m256d x)
{
  return x * fn2_256 (x);
}

__m256d
fn4_256 (__m256d x)
{
  return x * fn3_256 (x);
}

__m256d
fn5_256 (__m256d x)
{
  return x * fn4_256 (x);
}

__m256d
fn6_256 (__m256d x)
{
  return x * fn5_256 (x);
}

__m256d
fn7_256 (__m256d x)
{
  return x * fn6_256 (x);
}

__m256d
fn8_256 (__m256d x)
{
  return x * fn7_256 (x);
}

__m256d
fn9_256 (__m256d x)
{
  return x * fn8_256 (x);
}

__m256d
fn10_256 (__m256d x)
{
  return x * fn9_256 (x);
}

__m256d
fn11_256 (__m256d x)
{
  return x * fn10_256 (x);
}

__m256d
fn12_256 (__m256d x)
{
  return x * fn11_256 (x);
}

__m256d
fn13_256 (__m256d x)
{
  return x * fn12_256 (x);
}

__m256d
fn14_256 (__m256d x)
{
  return x * fn13_256 (x);
}

#endif

void
matrix_print (JBFLOAT *x, unsigned int nr, unsigned int nc)
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
farray_print (JBMFarray * fa)
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
darray_print (JBDOUBLE * fa, unsigned int n)
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
#ifdef __SSE4_2__
  double *d_1, *d_2;
  unsigned long long int *L_1;
  __m128d d_128, d2_128;
#endif
#ifdef __AVX__
  __m256d d_256, d2_256;
#endif
#ifdef __AVX512F__
  __m512d d_512, d2_512;
#endif
  long long int iL, iL2;
  unsigned long long int uL, uL2;
  long int il, il2;
  unsigned long int ul, ul2;
  int i, is, is2;
  unsigned int n, us, us2;
  for (i = 0; i < 3; ++i )
    cf[i].C = Cf[i], cf[i].E = Ef[i];
  for (i = 0; i < 4; ++i )
    cf[i].D = Df[i], cf[i].H = Hf[i];
  for (i = 0; i < 4; ++i )
    czf[i].C = Czf[i], czf[i].E = Ezf[i];
  for (i = 0; i < 5; ++i )
    czf[i].D = Dzf[i], czf[i].H = Hzf[i];
  for (i = 0; i < 3; ++i )
    cd[i].C = Cd[i], cd[i].E = Ed[i];
  for (i = 0; i < 4; ++i )
    cd[i].D = Dd[i], cd[i].H = Hd[i];
  for (i = 0; i < 4; ++i )
    czd[i].C = Czd[i], czd[i].E = Ezd[i];
  for (i = 0; i < 5; ++i )
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
  printf ("minll(1L,-1L)=%Ld\n", iL);
  iL = jbm_maxll (1L, -1L);
  printf ("maxll(1L,-1L)=%Ld\n", iL);
  iL = jbm_modminll (1L, -1L);
  printf ("modminll(1L,-1L)=%Ld\n", iL);
  iL = jbm_modminll (1L, 2L);
  printf ("modminll(1L,2L)=%Ld\n", iL);
  iL = jbm_modminll (-2L, -1L);
  printf ("modminll(-2L,-1L)=%Ld\n", iL);
  iL = jbm_dblll (1L);
  printf ("dbll((1L)=%Ld\n", iL);
  iL = jbm_sqrll (-1L);
  printf ("sqrll(-1L)=%Ld\n", iL);
  iL = 1L, iL2 = -1L;
  jbm_changell (&iL, &iL2);
  printf ("changell(1L,-1L)=(%Ld,%Ld)\n", iL, iL2);
  uL = jbm_minull (1L, 2L);
  printf ("minull(1L,2L)=%Lu\n", uL);
  uL = jbm_maxull (1L, 2L);
  printf ("maxull(1L,2L)=%Lu\n", uL);
  uL = jbm_dblull (1L);
  printf ("dbLull(1L)=%Lu\n", uL);
  uL = jbm_sqrull (1L);
  printf ("sqrull(1L)=%Lu\n", uL);
  uL = 1L, uL2 = 2L;
  jbm_changeull (&uL, &uL2);
  printf ("changeull(1L,2L)=(%Lu,%Lu)\n", uL, uL2);
  printf ("small(0)=%d\n", jbm_small (cf0));
  printf ("small(1)=%d\n", jbm_small (cf1));
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_fmodmin (cf1, cf2));
  printf ("fmodmin(1,2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_fmodmin (-cf1, -cf2));
  printf ("fmodmin(-1,-2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_fmodmin (cf1, -cf2));
  printf ("fmodmin(1,-2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_fdbl (cf1));
  printf ("fdbl(1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_fsqr (-cf2));
  printf ("fsqr(-2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_extrapolate (cf0, cf1, -cf2, cf3, cf2));
  printf ("extrapolate(0,1,-2,3,2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_interpolate (cf0, -cf2, cf1, cf3, cf2));
  printf ("interpolate(0,-2,1,3,2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_interpolate (cf1, -cf2, cf0, cf3, cf2));
  printf ("interpolate(1,-2,0,3,2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_interpolate (-cf2, cf0, cf1, cf3, cf2));
  printf ("interpolate(-2,0,1,3,2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_v2_length (cf0, cf1, -cf2, cf3));
  printf ("v2_length(0,1,-2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_v3_length (cf0, cf1, -cf2, cf3, cf2, -cf3));
  printf ("v3_length(0,1,-2,3,2,-3)=%s\n", buffer);
  f = cf1, f2 = -cf2;
  jbm_fchange (&f, &f2);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, f);
  SNPRINTF (buffer2, JB_BUFFER_SIZE, FWF, f2);
  printf ("fchange(1,-2)=(%s,%s)\n", buffer, buffer2);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_polynomial_11 (cf05, pf));
  printf ("polynomial_11(0.5,pf)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_polynomial_11 (cf1, pf));
  printf ("polynomial_11(1,pf)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
             jbm_solve_quadratic (cf2, -cf1, -cf1, cf0, cf2));
  printf ("solve_quadratic(2,-1,-1,0,2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
             jbm_solve_quadratic (cf0, -cf2, cf1, cf0, cf2));
  printf ("solve_quadratic(0,-2,1,0,2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
             jbm_solve_cubic (cf05, cf1, cf1, cf05, -cf2, cf0));
  printf ("solve_cubic(0.5,1,1,0.5,-2,0)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
             jbm_solve_cubic (cf0, cf2, -cf1, -cf1, cf0, cf2));
  printf ("solve_cubic(0,2,-1,-1,0,2)=%s\n", buffer);
  
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf1, cf3, JBM_FLUX_LIMITER_TYPE_TOTAL));
  printf ("flux_limiter_total(1,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf1, cf3, JBM_FLUX_LIMITER_TYPE_NULL));
  printf ("flux_limiter_null(1,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf1, cf3, JBM_FLUX_LIMITER_TYPE_CENTRED));
  printf ("flux_limiter_centred(1,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf1, cf0, JBM_FLUX_LIMITER_TYPE_CENTRED));
  printf ("flux_limiter_centred(1,0)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (-cf1, cf1, JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbee(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf1, cf3, JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbee(1,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf2, cf3, JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbee(2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf3, cf2, JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbee(3,2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf3, cf1, JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbee(3,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (-cf1, cf1, JBM_FLUX_LIMITER_TYPE_MINMOD));
  printf ("flux_limiter_minmod(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf2, cf3, JBM_FLUX_LIMITER_TYPE_MINMOD));
  printf ("flux_limiter_minmod(2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf3, cf1, JBM_FLUX_LIMITER_TYPE_MINMOD));
  printf ("flux_limiter_minmod(3,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (-cf1, cf1, JBM_FLUX_LIMITER_TYPE_VAN_LEER));
  printf ("flux_limiter_VanLeer(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf2, cf3, JBM_FLUX_LIMITER_TYPE_VAN_LEER));
  printf ("flux_limiter_VanLeer(2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (-cf1, cf1, JBM_FLUX_LIMITER_TYPE_VAN_ALBADA));
  printf ("flux_limiter_VanAlbada(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf2, cf3, JBM_FLUX_LIMITER_TYPE_VAN_ALBADA));
  printf ("flux_limiter_VanAlbada(2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (-cf1, cf1, JBM_FLUX_LIMITER_TYPE_MINSUPER));
  printf ("flux_limiter_minsuper(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf2, cf3, JBM_FLUX_LIMITER_TYPE_MINSUPER));
  printf ("flux_limiter_minsuper(2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf3, cf1, JBM_FLUX_LIMITER_TYPE_MINSUPER));
  printf ("flux_limiter_minsuper(3,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (-cf1, cf1, JBM_FLUX_LIMITER_TYPE_SUPERMIN));
  printf ("flux_limiter_supermin(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf1, cf3, JBM_FLUX_LIMITER_TYPE_SUPERMIN));
  printf ("flux_limiter_supermin(1,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf3, cf1, JBM_FLUX_LIMITER_TYPE_SUPERMIN));
  printf ("flux_limiter_supermin(3,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (-cf1, cf1,
                              JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL));
  printf ("flux_limiter_monotonized_central(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf05, cf3,
                              JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL));
  printf ("flux_limiter_monotonized_central(0.5,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf2, cf3,
                              JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL));
  printf ("flux_limiter_monotonized_central(2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf3, cf05,
                              JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL));
  printf ("flux_limiter_monotonized_central(3,0.5)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (-cf1, cf1, JBM_FLUX_LIMITER_TYPE_MEAN));
  printf ("flux_limiter_mean(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_flux_limiter (cf2, cf3, JBM_FLUX_LIMITER_TYPE_MEAN));
  printf ("flux_limiter_mean(2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_integral (fn0f, cf0, cf1));
  printf ("integral(1,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_integral (fn1f, cf0, cf1));
  printf ("integral(x,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_integral (fn2f, cf0, cf1));
  printf ("integral(x^2,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_integral (fn3f, cf0, cf1));
  printf ("integral(x^3,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_integral (fn4f, cf0, cf1));
  printf ("integral(x^4,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_integral (fn5f, cf0, cf1));
  printf ("integral(x^5,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_integral (fn6f, cf0, cf1));
  printf ("integral(x^6,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_integral (fn7f, cf0, cf1));
  printf ("integral(x^7,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_integral (fn8f, cf0, cf1));
  printf ("integral(x^8,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_integral (fn9f, cf0, cf1));
  printf ("integral(x^9,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_integral (fn10f, cf0, cf1));
  printf ("integral(x^10,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_integral (fn11f, cf0, cf1));
  printf ("integral(x^11,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_integral (fn12f, cf0, cf1));
  printf ("integral(x^12,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_integral (fn13f, cf0, cf1));
  printf ("integral(x^13,0,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_integral (fn14f, cf0, cf1));
  printf ("integral(x^14,0,1)=%s\n", buffer);
  printf ("smalll(0)=%d\n", jbm_smalll (cd0));
  printf ("smalll(1)=%d\n", jbm_smalll (cd1));
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_fmodminl (cd1, cd2));
  printf ("fmodminl(1,2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_fmodminl (-cd1, -cd2));
  printf ("fmodminl(-1,-2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_fmodminl (cd1, -cd2));
  printf ("fmodminl(1,-2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_fdbll (cd1));
  printf ("fdbll(1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_fsqrl (-cd2));
  printf ("fsqrl(-2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_extrapolatel (cd0, cd1, -cd2, cd3, cd2));
  printf ("extrapolatel(0,1,-2,3,2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_interpolatel (cd0, -cd2, cd1, cd3, cd2));
  printf ("interpolatel(0,-2,1,3,2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_interpolatel (cd1, -cd2, cd0, cd3, cd2));
  printf ("interpolatel(1,-2,0,3,2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_interpolatel (-cd2, cd0, cd1, cd3, cd2));
  printf ("interpolatel(-2,0,1,3,2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_v2_lengthl (cd0, cd1, -cd2, cd3));
  printf ("v2_lengthl(0,1,-2,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_v3_lengthl (cd0, cd1, -cd2, cd3, cd2, -cd3));
  printf ("v3_lengthl(0,1,-2,3,2,-3)=%s\n", buffer);
  d = cd1, d2 = -cd2;
  jbm_fchangel (&d, &d2);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, d);
  SNPRINTFL (buffer2, JB_BUFFER_SIZE, FWL, d2);
  printf ("fchangel(1,-2)=(%s,%s)\n", buffer, buffer2);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_polynomial_11l (cd05, pd));
  printf ("polynomial_11l(0.5,pd)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_polynomial_11l (cd1, pd));
  printf ("polynomial_11l(1,pd)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_solve_quadraticl (cd2, -cd1, -cd1, cd0, cd2));
  printf ("solve_quadraticl(2,-1,-1,0,2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_solve_quadraticl (cd0, -cd2, cd1, cd0, cd2));
  printf ("solve_quadraticl(0,-2,1,0,2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_solve_cubicl (cd05, cd1, cd1, cd05, -cd2, cd0));
  printf ("solve_cubicl(0.5,1,1,0.5,-2,0)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
             jbm_solve_cubicl (cd0, cd2, -cd1, -cd1, cd0, cd2));
  printf ("solve_cubicl(0,2,-1,-1,0,2)=%s\n", buffer);
  
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd1, cd3, JBM_FLUX_LIMITER_TYPE_TOTAL));
  printf ("flux_limiter_totall(1,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd1, cd3, JBM_FLUX_LIMITER_TYPE_NULL));
  printf ("flux_limiter_nulll(1,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd1, cd3, JBM_FLUX_LIMITER_TYPE_CENTRED));
  printf ("flux_limiter_centredl(1,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd1, cd0, JBM_FLUX_LIMITER_TYPE_CENTRED));
  printf ("flux_limiter_centredl(1,0)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (-cd1, cd1, JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbeel(-1,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd1, cd3, JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbeel(1,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd2, cd3, JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbeel(2,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd3, cd2, JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbeel(3,2)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd3, cd1, JBM_FLUX_LIMITER_TYPE_SUPERBEE));
  printf ("flux_limiter_superbeel(3,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (-cd1, cd1, JBM_FLUX_LIMITER_TYPE_MINMOD));
  printf ("flux_limiter_minmodl(-1,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd2, cd3, JBM_FLUX_LIMITER_TYPE_MINMOD));
  printf ("flux_limiter_minmodl(2,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd3, cd1, JBM_FLUX_LIMITER_TYPE_MINMOD));
  printf ("flux_limiter_minmodl(3,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (-cd1, cd1, JBM_FLUX_LIMITER_TYPE_VAN_LEER));
  printf ("flux_limiter_VanLeerl(-1,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd2, cd3, JBM_FLUX_LIMITER_TYPE_VAN_LEER));
  printf ("flux_limiter_VanLeerl(2,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (-cd1, cd1, JBM_FLUX_LIMITER_TYPE_VAN_ALBADA));
  printf ("flux_limiter_VanAlbadal(-1,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd2, cd3, JBM_FLUX_LIMITER_TYPE_VAN_ALBADA));
  printf ("flux_limiter_VanAlbadal(2,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (-cd1, cd1, JBM_FLUX_LIMITER_TYPE_MINSUPER));
  printf ("flux_limiter_minsuperl(-1,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd2, cd3, JBM_FLUX_LIMITER_TYPE_MINSUPER));
  printf ("flux_limiter_minsuperl(2,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd3, cd1, JBM_FLUX_LIMITER_TYPE_MINSUPER));
  printf ("flux_limiter_minsuperl(3,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (-cd1, cd1, JBM_FLUX_LIMITER_TYPE_SUPERMIN));
  printf ("flux_limiter_superminl(-1,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd1, cd3, JBM_FLUX_LIMITER_TYPE_SUPERMIN));
  printf ("flux_limiter_superminl(1,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd3, cd1, JBM_FLUX_LIMITER_TYPE_SUPERMIN));
  printf ("flux_limiter_superminl(3,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (-cd1, cd1,
                              JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL));
  printf ("flux_limiter_monotonized_centrall(-1,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd05, cd3,
                              JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL));
  printf ("flux_limiter_monotonized_centrall(0.5,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd2, cd3,
                              JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL));
  printf ("flux_limiter_monotonized_centrall(2,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd3, cd05,
                              JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL));
  printf ("flux_limiter_monotonized_centrall(3,0.5)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (-cd1, cd1, JBM_FLUX_LIMITER_TYPE_MEAN));
  printf ("flux_limiter_meanl(-1,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL,
            jbm_flux_limiterl (cd2, cd3, JBM_FLUX_LIMITER_TYPE_MEAN));
  printf ("flux_limiter_meanl(2,3)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_integrall (fn0d, cd0, cd1));
  printf ("integrall(1,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_integrall (fn1d, cd0, cd1));
  printf ("integrall(x,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_integrall (fn2d, cd0, cd1));
  printf ("integrall(x^2,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_integrall (fn3d, cd0, cd1));
  printf ("integrall(x^3,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_integrall (fn4d, cd0, cd1));
  printf ("integrall(x^4,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_integrall (fn5d, cd0, cd1));
  printf ("integrall(x^5,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_integrall (fn6d, cd0, cd1));
  printf ("integrall(x^6,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_integrall (fn7d, cd0, cd1));
  printf ("integrall(x^7,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_integrall (fn8d, cd0, cd1));
  printf ("integrall(x^8,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_integrall (fn9d, cd0, cd1));
  printf ("integrall(x^9,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_integrall (fn10d, cd0, cd1));
  printf ("integrall(x^10,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_integrall (fn11d, cd0, cd1));
  printf ("integrall(x^11,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_integrall (fn12d, cd0, cd1));
  printf ("integrall(x^12,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_integrall (fn13d, cd0, cd1));
  printf ("integrall(x^13,0,1)=%s\n", buffer);
  SNPRINTFL (buffer, JB_BUFFER_SIZE, FWL, jbm_integrall (fn14d, cd0, cd1));
  printf ("integrall(x^14,0,1)=%s\n", buffer);
#ifdef __SSE4_2__
  printf ("check SSE 4.2 functions\n");
  d_1 = aligned_alloc (16, 2 * sizeof (double));
  d_2 = aligned_alloc (16, 2 * sizeof (double));
  d_128 = jbm_abs_128 (_mm_set_pd (-1., 1));
  _mm_store_pd (d_1, d_128);
  printf ("abs_128([1,-1])=[%.15le,%.15le]\n", d_1[0], d_1[1]);
  d_128 = jbm_small_128 (_mm_set_pd (1., 0.));
  _mm_store_pd (d_1, d_128);
  L_1 = (unsigned long long int *) d_1;
  printf ("small_128([0,1])=[%16Lx,%16Lx]\n", L_1[0], L_1[1]);
  d_128 = jbm_modmin_128 (_mm_set_pd (-1., 1.), _mm_set_pd (-2., 0.5)); 
  _mm_store_pd (d_1, d_128);
  printf ("modmin_128([1,-1],[0.5,-2])=[%.15le,%.15le]\n", d_1[0], d_1[1]);
  d_128 = jbm_modmin_128 (_mm_set_pd (1.0, 0.), _mm_set_pd (-2., 1.)); 
  _mm_store_pd (d_1, d_128);
  printf ("modmin_128([0,1],[1,-2])=[%.15le,%.15le]\n", d_1[0], d_1[1]);
  d_128 = _mm_set_pd (1., 0.); 
  d2_128 = _mm_set_pd (-2., 1.);
  jbm_change_128 (&d_128, &d2_128); 
  _mm_store_pd (d_1, d_128);
  _mm_store_pd (d_2, d2_128);
  printf ("change_128([0,1],[1,-2])=([%.15le,%.15le],[%.15le,%.15le])\n",
          d_1[0], d_1[1], d_2[0], d_2[1]);
  d2_128 = jbm_dbl_128 (d_128);
  _mm_store_pd (d_1, d2_128);
  printf ("dbl_128([1,-2])=[%.15le,%.15le]\n", d_1[0], d_1[1]);
  d_128 = jbm_sqr_128 (d_128);
  _mm_store_pd (d_1, d_128);
  printf ("sqr_128([1,-2])=[%.15le,%.15le]\n", d_1[0], d_1[1]);
  d_128 = jbm_extrapolate_128 (_mm_set_pd (-1., 1.),
                               _mm_set1_pd (0.),
                               _mm_set1_pd (2.),
                               _mm_set1_pd (1.),
                               _mm_set1_pd (4.));
  _mm_store_pd (d_1, d_128);
  printf ("extrapolate_128([1,-1],[0,0],[2,2],[1,1],[4,4])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_interpolate_128 (_mm_set_pd (-1., 1.),
                               _mm_set1_pd (0.),
                               _mm_set1_pd (2.),
                               _mm_set1_pd (1.),
                               _mm_set1_pd (4.));
  _mm_store_pd (d_1, d_128);
  printf ("interpolate_128([1,-1],[0,0],[2,2],[1,1],[4,4])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_interpolate_128 (_mm_set_pd (3., 1.),
                               _mm_set_pd (0., 0.),
                               _mm_set_pd (2., 2.),
                               _mm_set_pd (1., 1.),
                               _mm_set_pd (4., 4.));
  _mm_store_pd (d_1, d_128);
  printf ("interpolate_128([1,3],[0,0],[2,2],[1,1],[4,4])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_v2_length_128 (_mm_set_pd (2., 1.),
                             _mm_set_pd (-1., 4.),
                             _mm_set_pd (5., -3.),
                             _mm_set_pd (3., 1.));
  _mm_store_pd (d_1, d_128);
  printf ("v2_length_128([1,2],[4,-1],[-3,5],[1,3])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_v3_length_128 (_mm_set_pd (2., 1.),
                             _mm_set_pd (-1., 4.),
                             _mm_set_pd (1., 3.),
                             _mm_set_pd (4., -1.),
                             _mm_set_pd (2., 1.),
                             _mm_set_pd (-5., 9.));
  _mm_store_pd (d_1, d_128);
  printf ("v3_length_128([1,2],[4,-1],[3,1],[-1,4],[1,2],[9,-5])"
          "=[%.15le,%.15le]\n", d_1[0], d_1[1]);
  d_128 = jbm_polynomial_11_128 (_mm_set_pd (1., 0.5), p_1);
  _mm_store_pd (d_1, d_128);
  printf ("polynomial_11_128([0.5,1],[1,2,4,8,16,32,64,128,256,512,1024,2048])"
          "=[%.15le,%.15le]\n", d_1[0], d_1[1]);
  d_128 = jbm_solve_quadratic_128 (_mm_set_pd (0., 2.),
                                   _mm_set_pd (-2., -1.),
                                   _mm_set_pd (1., -1.),
                                   _mm_set_pd (0., 0.),
                                   _mm_set_pd (2., 2.));
  _mm_store_pd (d_1, d_128);
  printf ("solve_quadratic_128([2,0],[-1,-2][-1,1],[0,0],[2,2])"
          "=[%.15le,%.15le]\n", d_1[0], d_1[1]);
  d_128 = jbm_flux_limiter_128 (_mm_setzero_pd (),
                                _mm_set1_pd (1.),
                                JBM_FLUX_LIMITER_TYPE_TOTAL);
  _mm_store_pd (d_1, d_128);
  printf ("flux_limiter_total_128([0,0],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_flux_limiter_128 (_mm_setzero_pd (),
                                _mm_set1_pd (1.),
                                JBM_FLUX_LIMITER_TYPE_NULL);
  _mm_store_pd (d_1, d_128);
  printf ("flux_limiter_null_128([0,0],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_flux_limiter_128 (_mm_set_pd (3., 1.),
                                _mm_set_pd (0., 1.),
                                JBM_FLUX_LIMITER_TYPE_CENTRED);
  _mm_store_pd (d_1, d_128);
  printf ("flux_limiter_centred_128([1,3],[1,0])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_flux_limiter_128 (_mm_set_pd (1., -1.),
                                _mm_set_pd (3., 1.),
                                JBM_FLUX_LIMITER_TYPE_SUPERBEE);
  _mm_store_pd (d_1, d_128);
  printf ("flux_limiter_superbee_128([-1,1],[1,3])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_flux_limiter_128 (_mm_set_pd (3., 2.),
                                _mm_set_pd (2., 3.),
                                JBM_FLUX_LIMITER_TYPE_SUPERBEE);
  _mm_store_pd (d_1, d_128);
  printf ("flux_limiter_superbee_128([2,3],[3,2])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_flux_limiter_128 (_mm_set_pd (1., 3.),
                                _mm_set_pd (1., 1.),
                                JBM_FLUX_LIMITER_TYPE_SUPERBEE);
  _mm_store_pd (d_1, d_128);
  printf ("flux_limiter_superbee_128([3,1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_flux_limiter_128 (_mm_set_pd (2., -1.),
                                _mm_set_pd (3., 1.),
                                JBM_FLUX_LIMITER_TYPE_MINMOD);
  _mm_store_pd (d_1, d_128);
  printf ("flux_limiter_minmod_128([-1,2],[1,3])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_flux_limiter_128 (_mm_set_pd (1., 3.),
                                _mm_set_pd (1., 1.),
                                JBM_FLUX_LIMITER_TYPE_MINMOD);
  _mm_store_pd (d_1, d_128);
  printf ("flux_limiter_minmod_128([3,1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_flux_limiter_128 (_mm_set_pd (2., -1.),
                                _mm_set_pd (3., 1.),
                                JBM_FLUX_LIMITER_TYPE_VAN_LEER);
  _mm_store_pd (d_1, d_128);
  printf ("flux_limiter_VanLeer_128([-1,2],[1,3])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_flux_limiter_128 (_mm_set_pd (2., -1.),
                                _mm_set_pd (3., 1.),
                                JBM_FLUX_LIMITER_TYPE_VAN_ALBADA);
  _mm_store_pd (d_1, d_128);
  printf ("flux_limiter_VanAlbada_128([-1,2],[1,3])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_flux_limiter_128 (_mm_set_pd (2., -1.),
                                _mm_set_pd (3., 1.),
                                JBM_FLUX_LIMITER_TYPE_MINSUPER);
  _mm_store_pd (d_1, d_128);
  printf ("flux_limiter_minsuper_128([-1,2],[1,3])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_flux_limiter_128 (_mm_set_pd (1., 3.),
                                _mm_set_pd (1., 1.),
                                JBM_FLUX_LIMITER_TYPE_MINSUPER);
  _mm_store_pd (d_1, d_128);
  printf ("flux_limiter_minsuper_128([3,1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_flux_limiter_128 (_mm_set_pd (1., -1.),
                                _mm_set_pd (3., 1.),
                                JBM_FLUX_LIMITER_TYPE_SUPERMIN);
  _mm_store_pd (d_1, d_128);
  printf ("flux_limiter_supermin_128([-1,1],[1,3])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_flux_limiter_128 (_mm_set_pd (1., 3.),
                                _mm_set_pd (1., 1.),
                                JBM_FLUX_LIMITER_TYPE_SUPERMIN);
  _mm_store_pd (d_1, d_128);
  printf ("flux_limiter_supermin_128([3,1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_flux_limiter_128 (_mm_set_pd (0.5, -1.),
                                _mm_set_pd (3., 1.),
                                JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL);
  _mm_store_pd (d_1, d_128);
  printf ("flux_limiter_monotonized_central_128([-1,0.5],[1,3])"
          "=[%.15le,%.15le]\n", d_1[0], d_1[1]);
  d_128 = jbm_flux_limiter_128 (_mm_set_pd (3., 2.),
                                _mm_set_pd (0.5, 3.),
                                JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL);
  _mm_store_pd (d_1, d_128);
  printf ("flux_limiter_monotonized_central_128([2,3],[3,0.5])"
          "=[%.15le,%.15le]\n", d_1[0], d_1[1]);
  d_128 = jbm_flux_limiter_128 (_mm_set_pd (2., -1.),
                                _mm_set_pd (3., 1.),
                                JBM_FLUX_LIMITER_TYPE_MEAN);
  _mm_store_pd (d_1, d_128);
  printf ("flux_limiter_mean_128([-1,2],[1,3])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_integral_128 (fn0_128, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_128);
  printf ("integral_128(1,[0,-1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_integral_128 (fn1_128, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_128);
  printf ("integral_128(x,[0,-1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_integral_128 (fn2_128, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_128);
  printf ("integral_128(x^2,[0,-1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_integral_128 (fn3_128, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_128);
  printf ("integral_128(x^3,[0,-1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_integral_128 (fn4_128, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_128);
  printf ("integral_128(x^4,[0,-1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_integral_128 (fn5_128, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_128);
  printf ("integral_128(x^5,[0,-1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_integral_128 (fn6_128, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_128);
  printf ("integral_128(x^6,[0,-1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_integral_128 (fn7_128, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_128);
  printf ("integral_128(x^7,[0,-1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_integral_128 (fn8_128, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_128);
  printf ("integral_128(x^8,[0,-1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_integral_128 (fn9_128, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_128);
  printf ("integral_128(x^9,[0,-1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_integral_128 (fn10_128, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_128);
  printf ("integral_128(x^10,[0,-1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_integral_128 (fn11_128, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_128);
  printf ("integral_128(x^11,[0,-1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_integral_128 (fn12_128, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_128);
  printf ("integral_128(x^12,[0,-1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_integral_128 (fn13_128, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_128);
  printf ("integral_128(x^13,[0,-1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  d_128 = jbm_integral_128 (fn14_128, _mm_set_pd (-1., 0.), _mm_set1_pd (1.));
  _mm_store_pd (d_1, d_128);
  printf ("integral_128(x^14,[0,-1],[1,1])=[%.15le,%.15le]\n",
          d_1[0], d_1[1]);
  aligned_free (d_2);
  aligned_free (d_1);
#endif
#ifdef __AVX__
  printf ("check AVX functions\n");
  d_1 = aligned_alloc (32, 4 * sizeof (double));
  d_2 = aligned_alloc (32, 4 * sizeof (double));
  d_256 = jbm_abs_256 (_mm256_set_pd (2., 0., -1., 1));
  _mm256_store_pd (d_1, d_256);
  printf ("abs_256([1,-1,0,2])=[%.15le,%.15le,%.15le,%.15le]\n",
          d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_small_256 (_mm256_set_pd (-1., 1., -0., 0.));
  _mm256_store_pd (d_1, d_256);
  L_1 = (unsigned long long int *) d_1;
  printf ("small_256([0,-0,1,-1])=[%16Lx,%16Lx,%16Lx,%16Lx]\n",
          L_1[0], L_1[1], L_1[2], L_1[3]);
  d_256 = jbm_modmin_256 (_mm256_set_pd (1., 0., -1., 1.),
                          _mm256_set_pd (-2., 1., -2., 0.5)); 
  _mm256_store_pd (d_1, d_256);
  printf ("modmin_256([1,-1,0,1],[0.5,-2,1,-2])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = _mm256_set_pd (3., -1., 1., 0.); 
  d2_256 = _mm256_set_pd (-4., 7., -2., 1.);
  jbm_change_256 (&d_256, &d2_256); 
  _mm256_store_pd (d_1, d_256);
  _mm256_store_pd (d_2, d2_256);
  printf ("change_256([0,1,-1,3],[1,-2,7,-4])"
          "=([%.15le,%.15le,%.15le,%.15le],[%.15le,%.15le,%.15le,%.15le])\n",
          d_1[0], d_1[1], d_1[2], d_1[3], d_2[0], d_2[1], d_2[2], d_2[3]);
  d2_256 = jbm_dbl_256 (d_256);
  _mm256_store_pd (d_1, d2_256);
  printf ("dbl_256([1,-2,7,-4])=[%.15le,%.15le,%.15le,%.15le]\n",
          d_1[0], d_1[1], d_1[2], d_1[3]);
  d2_256 = jbm_sqr_256 (d_256);
  _mm256_store_pd (d_1, d2_256);
  printf ("sqr_256([1,-2,7,-4])=[%.15le,%.15le,%.15le,%.15le]\n",
          d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_extrapolate_256 (_mm256_set_pd (0., 3., -1., 1.),
                               _mm256_set1_pd (0.),
                               _mm256_set1_pd (2.),
                               _mm256_set1_pd (1.),
                               _mm256_set1_pd (4.));
  _mm256_store_pd (d_1, d_256);
  printf ("extrapolate_256([1,-1,3,0],[0,0,0,0],[2,2,2,2],[1,1,1,1],[4,4,4,4])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_interpolate_256 (_mm256_set_pd (0., 3., -1., 1.),
                               _mm256_set1_pd (0.),
                               _mm256_set1_pd (2.),
                               _mm256_set1_pd (1.),
                               _mm256_set1_pd (4.));
  _mm256_store_pd (d_1, d_256);
  printf ("interpolate_256([1,-1,3,0],[0,0,0,0],[2,2,2,2],[1,1,1,1],[4,4,4,4])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_v2_length_256 (_mm256_set_pd (-1., 3., 2., 1.),
                             _mm256_set_pd (2., 3., -1., 4.),
                             _mm256_set_pd (2., 0., 5., -3.),
                             _mm256_set_pd (6., 7., 3., 1.));
  _mm256_store_pd (d_1, d_256);
  printf ("v2_length_256([1,2,3,-1],[4,-1,3,2],[-3,5,0,2],[1,3,7,6])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_v3_length_256 (_mm256_set_pd (-1., 3., 2., 1.),
                             _mm256_set_pd (2., 3., -1., 4.),
                             _mm256_set_pd (5., 0., 1., 3.),
                             _mm256_set_pd (1., 2., 4., -1.),
                             _mm256_set_pd (5., 5., 3., 0.),
                             _mm256_set_pd (-1., 2., 5., 7.));
  _mm256_store_pd (d_1, d_256);
  printf ("v3_length_256([1,2,3,-1],[4,-1,3,2],[3,1,0,5],[-1,4,1,1],[1,2,1,4],"
          "[9,-5,2,0])=[%.15le,%.15le,%.15le,%.15le]\n",
          d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_polynomial_11_256 (_mm256_set_pd (-1., 0., 1., 0.5), p_1);
  _mm256_store_pd (d_1, d_256);
  printf ("polynomial_11_128([0.5,1,0,-1],"
          "[1,2,4,8,16,32,64,128,256,512,1024,2048])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_solve_quadratic_256 (_mm256_set_pd (1., 1., 0., 2.),
                                   _mm256_set_pd (0., 0., -2., -1.),
                                   _mm256_set_pd (-1., -1., 1., -1.),
                                   _mm256_set_pd (-2., 0., 0., 0.),
                                   _mm256_set_pd (0., 2., 2., 2.));
  _mm256_store_pd (d_1, d_256);
  printf ("solve_quadratic_256([2,0,1,1],[-1,-2,0,0][-1,1,-1,-1],[0,0,0,-2],"
          "[2,2,2,0])=[%.15le,%.15le,%.15le,%.15le]\n",
          d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_flux_limiter_256 (_mm256_setzero_pd (),
                                _mm256_set1_pd (1.),
                                JBM_FLUX_LIMITER_TYPE_TOTAL);
  _mm256_store_pd (d_1, d_256);
  printf ("flux_limiter_total_256([0,0,0,0],[1,1,1,1])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_flux_limiter_256 (_mm256_setzero_pd (),
                                _mm256_set1_pd (1.),
                                JBM_FLUX_LIMITER_TYPE_NULL);
  _mm256_store_pd (d_1, d_256);
  printf ("flux_limiter_null_256([0,0,0,0],[1,1,1,1])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_flux_limiter_256 (_mm256_set_pd (0., 1., 3., 1.),
                                _mm256_set_pd (0., 3., 0., 1.),
                                JBM_FLUX_LIMITER_TYPE_CENTRED);
  _mm256_store_pd (d_1, d_256);
  printf ("flux_limiter_centred_256([1,3,1,0],[1,0,3,0])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_flux_limiter_256 (_mm256_set_pd (3., 2., 1., -1.),
                                _mm256_set_pd (2., 3., 3., 1.),
                                JBM_FLUX_LIMITER_TYPE_SUPERBEE);
  _mm256_store_pd (d_1, d_256);
  printf ("flux_limiter_superbee_256([-1,1,2,3],[1,3,3,2])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_flux_limiter_256 (_mm256_set_pd (1., 0., 1., 0.),
                                _mm256_set_pd (1., 1., 0., 0.),
                                JBM_FLUX_LIMITER_TYPE_SUPERBEE);
  _mm256_store_pd (d_1, d_256);
  printf ("flux_limiter_superbee_256([0,1,0,1],[0,0,1,1])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_flux_limiter_256 (_mm256_set_pd (1., 3., 2., -1.),
                                _mm256_set_pd (1., 1., 3., 1.),
                                JBM_FLUX_LIMITER_TYPE_MINMOD);
  _mm256_store_pd (d_1, d_256);
  printf ("flux_limiter_minmod_256([-1,2,3,1],[1,3,1,1])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_flux_limiter_256 (_mm256_set_pd (1., 0., 2., -1.),
                                _mm256_set_pd (0., 0., 3., 1.),
                                JBM_FLUX_LIMITER_TYPE_VAN_LEER);
  _mm256_store_pd (d_1, d_256);
  printf ("flux_limiter_VanLeer_256([-1,2,0,1],[1,3,0,0])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_flux_limiter_256 (_mm256_set_pd (1., 0., 2., -1.),
                                _mm256_set_pd (0., 0., 3., 1.),
                                JBM_FLUX_LIMITER_TYPE_VAN_ALBADA);
  _mm256_store_pd (d_1, d_256);
  printf ("flux_limiter_VanAlbada_256([-1,2,0,1],[1,3,0,0])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_flux_limiter_256 (_mm256_set_pd (1., 3., 2., -1.),
                                _mm256_set_pd (1., 1., 3., 1.),
                                JBM_FLUX_LIMITER_TYPE_MINSUPER);
  _mm256_store_pd (d_1, d_256);
  printf ("flux_limiter_minsuper_256([-1,2,3,1],[1,3,1,1])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_flux_limiter_256 (_mm256_set_pd (1., 3., 1., -1.),
                                _mm256_set_pd (1., 1., 3., 1.),
                                JBM_FLUX_LIMITER_TYPE_SUPERMIN);
  _mm256_store_pd (d_1, d_256);
  printf ("flux_limiter_supermin_256([-1,1,3,1],[1,3,1,1])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_flux_limiter_256 (_mm256_set_pd (3., 2., 0.5, -1.),
                                _mm256_set_pd (0.5, 3., 3., 1.),
                                JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL);
  _mm256_store_pd (d_1, d_256);
  printf ("flux_limiter_monotonized_central_256([-1,0.5,2,3],[1,3,3,0.5])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_flux_limiter_256 (_mm256_set_pd (1., 0., 2., -1.),
                                _mm256_set_pd (0., 0., 3., 1.),
                                JBM_FLUX_LIMITER_TYPE_MEAN);
  _mm256_store_pd (d_1, d_256);
  printf ("flux_limiter_mean_256([-1,2,0,1],[1,3,0,0])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_integral_256 (fn0_256, _mm256_set_pd (-2., 0., -1., 0.),
                            _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_256);
  printf ("integral_256(1,[0,-1,0,-2],[1,1,2,2])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_integral_256 (fn1_256, _mm256_set_pd (-2., 0., -1., 0.),
                            _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_256);
  printf ("integral_256(x,[0,-1,0,-2],[1,1,2,2])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_integral_256 (fn2_256, _mm256_set_pd (-2., 0., -1., 0.),
                            _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_256);
  printf ("integral_256(x^2,[0,-1,0,-2],[1,1,2,2])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_integral_256 (fn3_256, _mm256_set_pd (-2., 0., -1., 0.),
                            _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_256);
  printf ("integral_256(x^3,[0,-1,0,-2],[1,1,2,2])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_integral_256 (fn4_256, _mm256_set_pd (-2., 0., -1., 0.),
                            _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_256);
  printf ("integral_256(x^4,[0,-1,0,-2],[1,1,2,2])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_integral_256 (fn5_256, _mm256_set_pd (-2., 0., -1., 0.),
                            _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_256);
  printf ("integral_256(x^5,[0,-1,0,-2],[1,1,2,2])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_integral_256 (fn6_256, _mm256_set_pd (-2., 0., -1., 0.),
                            _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_256);
  printf ("integral_256(x^6,[0,-1,0,-2],[1,1,2,2])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_integral_256 (fn7_256, _mm256_set_pd (-2., 0., -1., 0.),
                            _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_256);
  printf ("integral_256(x^7,[0,-1,0,-2],[1,1,2,2])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_integral_256 (fn8_256, _mm256_set_pd (-2., 0., -1., 0.),
                            _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_256);
  printf ("integral_256(x^9,[0,-1,0,-2],[1,1,2,2])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_integral_256 (fn9_256, _mm256_set_pd (-2., 0., -1., 0.),
                            _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_256);
  printf ("integral_256(x^9,[0,-1,0,-2],[1,1,2,2])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_integral_256 (fn10_256, _mm256_set_pd (-2., 0., -1., 0.),
                            _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_256);
  printf ("integral_256(x^10,[0,-1,0,-2],[1,1,2,2])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_integral_256 (fn11_256, _mm256_set_pd (-2., 0., -1., 0.),
                            _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_256);
  printf ("integral_256(x^11,[0,-1,0,-2],[1,1,2,2])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_integral_256 (fn12_256, _mm256_set_pd (-2., 0., -1., 0.),
                            _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_256);
  printf ("integral_256(x^12,[0,-1,0,-2],[1,1,2,2])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_integral_256 (fn13_256, _mm256_set_pd (-2., 0., -1., 0.),
                            _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_256);
  printf ("integral_256(x^13,[0,-1,0,-2],[1,1,2,2])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  d_256 = jbm_integral_256 (fn14_256, _mm256_set_pd (-2., 0., -1., 0.),
                            _mm256_set_pd (2., 2., 1., 1.));
  _mm256_store_pd (d_1, d_256);
  printf ("integral_256(x^14,[0,-1,0,-2],[1,1,2,2])"
          "=[%.15le,%.15le,%.15le,%.15le]\n", d_1[0], d_1[1], d_1[2], d_1[3]);
  aligned_free (d_2);
  aligned_free (d_1);
#endif
  printf ("check farray functions\n");
  printf ("0\n");
  fa = jbm_farray_create (pf, 11);
  printf ("1\n");
  fa2 = jbm_farray_new (11);
  printf ("2\n");
  fa3 = jbm_farray_new (11);
  printf ("3\n");
  for (i = 0; i < 11; ++i)
    fa2->x[i] = pf[11 - i];
  printf ("farray_add([1,2,4,...],[2048,1024,512,...],11)\n");
  jbm_farray_add (fa3, fa, fa2);
  farray_print (fa3);
  printf ("farray_sub([1,2,4,...],[2048,1024,512,...],11)\n");
  jbm_farray_sub (fa3, fa, fa2);
  farray_print (fa3);
  printf ("farray_mul1([1,2,4,...],3,11)\n");
  jbm_farray_mul1 (fa3, fa, cf3);
  farray_print (fa3);
  printf ("farray_div1([1,2,4,...],3,11)\n");
  jbm_farray_div1 (fa3, fa, cf3);
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
          jbm_farray_search (fa, -cf1));
  printf ("farray_search_extended(-1,[1,2,4,...],11)=%d\n",
          jbm_farray_search_extended (fa, -cf1));
  printf ("farray_search_extended(3,[1,2,4,...],11)=%d\n",
          jbm_farray_search_extended (fa, cf3));
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
            jbm_farray_interpolate (fa, fa2, cf3));
  printf ("farray_interpolate(3,[1,2,4,...],[2048,1024,512,...],11)=%s\n",
          buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_interpolate (fa, fa2, cf0));
  printf ("farray_interpolate(0,[1,2,4,...],[2048,1024,512,...],11)=%s\n",
          buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_interpolate (fa, fa2, EXP(cf3 * cf3)));
  printf ("farray_interpolate(exp(9),[1,2,4,...],[2048,1024,512,...],11)=%s\n",
          buffer);
  jbm_farray_dbl (fa2, fa);
  printf ("farray_merge([1,2,4,..],[2,4,8,...],11)\n");
  jbm_farray_destroy (fa3);
  fa3 = jbm_farray_merge (fa, fa2);
  farray_print (fa3);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_integral (fa, fa2, cf0, cf05));
  printf ("farray_integral([1,2,4,...],[2,4,8,...],11,0,0.5)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_integral (fa, fa2, pf[10], pf[11]));
  printf ("farray_integral([1,2,4,...],[2,4,8,...],11,2048,4096)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_integral (fa, fa2, cf2, cf3));
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
          "=(%s,%s)\n",buffer, buffer2);
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
