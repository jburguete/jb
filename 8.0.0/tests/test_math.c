#include "jb_math.h"

typedef struct
{
  JBFLOAT A, B, C, D, E, F, G, H;
} MatrixFloat;

typedef struct
{
  JBDOUBLE A, B, C, D, E, F, G, H;
} MatrixDouble;

#if JBM_LOW_PRECISION == 1

const JBFLOAT pf[12] = { 1.f, 2.f, 4.f, 8.f, 16.f, 32.f, 64.f, 128.f, 256.f,
  512.f, 1024.f, 2048.f };
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

#elif JBM_LOW_PRECISION == 2

const JBFLOAT pf[12] = { 1., 2., 4., 8., 16., 32., 64., 128., 256.,
  512., 1024., 2048. };
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

#elif JBM_LOW_PRECISION == 3

const JBFLOAT pf[12] = { 1.L, 2.L, 4.L, 8.L, 16.L, 32.L, 64.L, 128.L, 256.L,
  512.L, 1024.L, 2048.L };
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

#elif JBM_LOW_PRECISION == 4

const JBFLOAT pf[12] = { 1.Q, 2.Q, 4.Q, 8.Q, 16.Q, 32.Q, 64.Q, 128.Q, 256.Q,
  512.Q, 1024.Q, 2048.Q };
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

#endif

#if JBM_HIGH_PRECISION == 1

const JBDOUBLE pd[12] = { 1.f, 2.f, 4.f, 8.f, 16.f, 32.f, 64.f, 128.f, 256.f,
  512.f, 1024.f, 2048.f };
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

#elif JBM_HIGH_PRECISION == 2

const JBDOUBLE pd[12] = { 1., 2., 4., 8., 16., 32., 64., 128., 256.,
  512., 1024., 2048. };
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

#elif JBM_HIGH_PRECISION == 3

const JBDOUBLE pd[12] = { 1.L, 2.L, 4.L, 8.L, 16.L, 32.L, 64.L, 128.L, 256.L,
  512.L, 1024.L, 2048.L };
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

#elif JBM_HIGH_PRECISION == 4

const JBDOUBLE pd[12] = { 1.Q, 2.Q, 4.Q, 8.Q, 16.Q, 32.Q, 64.Q, 128.Q, 256.Q,
  512.Q, 1024.Q, 2048.Q };
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

#endif

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

void
farray_print (JBFLOAT * fa, unsigned int n)
{
  char buffer[JB_BUFFER_SIZE];
  unsigned int i;
  for (i = 0; i <= n; ++i)
    {
      SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, fa[i]);
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
  JBDOUBLE darray[12], darray2[12];
  JBFLOAT farray[12], farray2[12];
  char buffer[JB_BUFFER_SIZE], buffer2[JB_BUFFER_SIZE];
  JBDOUBLE (*flux_limiterl) (JBDOUBLE, JBDOUBLE); 
  JBFLOAT (*flux_limiter) (JBFLOAT, JBFLOAT); 
  JBDOUBLE *darray3;
  JBFLOAT *farray3;
  JBDOUBLE d, d2;
  JBFLOAT f, f2;
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
  flux_limiter = jbm_flux_limiter_select (JBM_FLUX_LIMITER_TYPE_TOTAL);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf1, cf3));
  printf ("flux_limiter_total(1,3)=%s\n", buffer);
  flux_limiter = jbm_flux_limiter_select (JBM_FLUX_LIMITER_TYPE_NULL);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf1, cf3));
  printf ("flux_limiter_null(1,3)=%s\n", buffer);
  flux_limiter = jbm_flux_limiter_select (JBM_FLUX_LIMITER_TYPE_CENTRED);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf1, cf3));
  printf ("flux_limiter_centred(1,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf1, cf0));
  printf ("flux_limiter_centred(1,0)=%s\n", buffer);
  flux_limiter = jbm_flux_limiter_select (JBM_FLUX_LIMITER_TYPE_SUPERBEE);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (-cf1, cf1));
  printf ("flux_limiter_superbee(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf1, cf3));
  printf ("flux_limiter_superbee(1,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf2, cf3));
  printf ("flux_limiter_superbee(2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf3, cf2));
  printf ("flux_limiter_superbee(3,2)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf3, cf1));
  printf ("flux_limiter_superbee(3,1)=%s\n", buffer);
  flux_limiter = jbm_flux_limiter_select (JBM_FLUX_LIMITER_TYPE_MINMOD);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (-cf1, cf1));
  printf ("flux_limiter_minmod(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf2, cf3));
  printf ("flux_limiter_minmod(2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf3, cf1));
  printf ("flux_limiter_minmod(3,1)=%s\n", buffer);
  flux_limiter = jbm_flux_limiter_select (JBM_FLUX_LIMITER_TYPE_VAN_LEER);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (-cf1, cf1));
  printf ("flux_limiter_VanLeer(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf2, cf3));
  printf ("flux_limiter_VanLeer(2,3)=%s\n", buffer);
  flux_limiter = jbm_flux_limiter_select (JBM_FLUX_LIMITER_TYPE_VAN_ALBADA);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (-cf1, cf1));
  printf ("flux_limiter_VanAlbada(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf2, cf3));
  printf ("flux_limiter_VanAlbada(2,3)=%s\n", buffer);
  flux_limiter = jbm_flux_limiter_select (JBM_FLUX_LIMITER_TYPE_MINSUPER);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (-cf1, cf1));
  printf ("flux_limiter_minsuper(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf2, cf3));
  printf ("flux_limiter_minsuper(2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf3, cf1));
  printf ("flux_limiter_minsuper(3,1)=%s\n", buffer);
  flux_limiter = jbm_flux_limiter_select (JBM_FLUX_LIMITER_TYPE_SUPERMIN);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (-cf1, cf1));
  printf ("flux_limiter_supermin(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf1, cf3));
  printf ("flux_limiter_supermin(1,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf3, cf1));
  printf ("flux_limiter_supermin(3,1)=%s\n", buffer);
  flux_limiter
    = jbm_flux_limiter_select (JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (-cf1, cf1));
  printf ("flux_limiter_monotonized_central(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf05, cf3));
  printf ("flux_limiter_monotonized_central(0.5,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf2, cf3));
  printf ("flux_limiter_monotonized_central(2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf3, cf05));
  printf ("flux_limiter_monotonized_central(3,0.5)=%s\n", buffer);
  flux_limiter = jbm_flux_limiter_select (JBM_FLUX_LIMITER_TYPE_MEAN);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (-cf1, cf1));
  printf ("flux_limiter_mean(-1,1)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, flux_limiter (cf2, cf3));
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
  printf ("farray_search_extended(-1,[1,2,4,...],11)=%d\n",
          jbm_farray_search_extended (-cf1, pf, 11));
  printf ("farray_search_extended(2048,[1,2,4,...],10)=%d\n",
          jbm_farray_search_extended (pf[11], pf, 10));
  printf ("farray_search_extended(3,[1,2,4,...],11)=%d\n",
          jbm_farray_search_extended (cf3, pf, 11));
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_farray_max (pf, 11));
  printf ("farray_max([1,2,4,...],11)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, jbm_farray_min (pf, 11));
  printf ("farray_min([1,2,4,...],11)=%s\n", buffer);
  jbm_farray_maxmin (pf, 11, &f, &f2);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, f);
  SNPRINTF (buffer2, JB_BUFFER_SIZE, FWF, f2);
  printf ("farray_maxmin([1,2,4,...],11)=(%s,%s)\n", buffer, buffer2);
  printf ("farray_change\n");
  for (i = 0; i <= 11; ++i)
    farray[i] = pf[i], farray2[i] = pf[11 - i];
  jbm_farray_change (farray, farray2, 11);
  farray_print (farray, 11);
  jbm_farray_change (farray, farray2, 11);
  farray_print (farray, 11);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_interpolate (cf3, farray, farray2, 11));
  printf ("farray_interpolate(3,[1,2,4,...],[2048,1024,512,...],11)=%s\n",
          buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_interpolate (cf0, farray, farray2, 11));
  printf ("farray_interpolate(0,[1,2,4,...],[2048,1024,512,...],11)=%s\n",
          buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_interpolate (EXP(cf3 * cf3), farray, farray2, 11));
  printf ("farray_interpolate(exp(9),[1,2,4,...],[2048,1024,512,...],11)=%s\n",
          buffer);
  for (i = 0; i <= 11; ++i)
    farray2[i] = jbm_fdbl (farray[i]);
  jbm_farray_merge (farray, 11, farray2, 11, &farray3, &n);
  farray_print (farray3, n);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_integral (farray, farray2, 11, cf0, cf05));
  printf ("farray_integral([1,2,4,...],[2,4,8,...],11,0,0.5)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_integral (farray, farray2, 11,
                                 farray2[10], farray2[11]));
  printf ("farray_integral([1,2,4,...],[2,4,8,...],11,2048,4096)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_integral (farray, farray2, 11, cf2, cf3));
  printf ("farray_integral([1,2,4,...],[2,4,8,...],11,2,3)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_root_mean_square_error (farray, farray, 11,
                                               farray2, farray2, 10));
  printf ("farray_root_mean_square_error([1,2,4,...],[1,2,4,...],11,"
          "[2,4,8,...],[2,4,8,...],10)=%s\n", buffer);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF,
            jbm_farray_root_mean_square_error (farray, farray, 11,
                                               farray, farray2, 11));
  printf ("farray_root_mean_square_error([1,2,4,...],[1,2,4,...],11,"
          "[1,2,4,...],[2,4,8,...],11)=%s\n", buffer);
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
  printf ("mxf2=%s mxf2=%s\n", buffer, buffer2);
  printf ("matrix_solve_tridiagonal\n");
  jbm_matrix_solve_tridiagonal (Cf, Df, Ef, Hf, 3);
  farray_print (Hf, 3);
  printf ("matrix_solve_tridiagonal_zero\n");
  jbm_matrix_solve_tridiagonal_zero (Czf, Dzf, Ezf, Hzf, 4);
  farray_print (Hzf, 4);
  printf ("matrix_solve_pentadiagonal\n");
  jbm_matrix_solve_pentadiagonal (Bpf, Cpf, Dpf, Epf, Fpf, Hpf, 3);
  farray_print (Hpf, 3);
  printf ("matrix_solve_pentadiagonal_zero\n");
  jbm_matrix_solve_pentadiagonal_zero (Bpzf, Cpzf, Dpzf, Epzf, Fpzf, Hpzf, 4);
  farray_print (Hpzf, 4);
  jbm_regression_linear (farray, farray2, 11, &f, &f2);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, f);
  SNPRINTF (buffer2, JB_BUFFER_SIZE, FWF, f2);
  printf ("regression_linear([1,2,4,...],[2,4,8,...],11)=(%s,%s)\n",
          buffer, buffer2);
  for (i = 0; i < 12; ++i)
    farray2[i] = farray[11 - i];
  jbm_regression_linear (farray, farray2, 11, &f, &f2);
  SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, f);
  SNPRINTF (buffer2, JB_BUFFER_SIZE, FWF, f2);
  printf ("regression_linear([1,2,4,...],[2048,1024,512,...],11)=(%s,%s)\n",
          buffer, buffer2);
  jbm_varray_solve_tridiagonal (&cf[0].C, &cf[0].D, &cf[0].E, &cf[0].H,
                                sizeof (MatrixFloat), 3);
  for (i = 0; i < 4; ++i)
    {
      SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, cf[i].H);
      printf ("x%d=%s\n", i, buffer);
    }
  jbm_varray_solve_tridiagonal_zero (&czf[0].C, &czf[0].D, &czf[0].E, &czf[0].H,
                                     sizeof (MatrixFloat), 4);
  for (i = 0; i < 5; ++i)
    {
      SNPRINTF (buffer, JB_BUFFER_SIZE, FWF, czf[i].H);
      printf ("x%d=%s\n", i, buffer);
    }
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
