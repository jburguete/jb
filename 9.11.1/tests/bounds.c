#include "config.h"
#include <stdio.h>
#include <math.h>
#include <float.h>
#if HAVE_QUADMATH
#include <quadmath.h>
#endif

#define FF "%.7e"
#define FD "%.16le"
#if __amd64
#define FLD "%.19Le"
#define ARCH "amd64"
#elif __riscv
#define FLD "%.34Le"
#define ARCH "riscv"
#elif __386
#define FLD "%.19Le"
#define ARCH "x86"
#endif
#define FQ "%.34Qe"
#if __linux__
#define OS "Linux"
#elif __FreeBSD__
#define OS "FreeBSD"
#elif __OpenBSD__
#define OS "OpenBSD"
#elif __NetBSD__
#define OS "NetBSD"
#elif __DragonFly__
#define OS "DragonFlyBSD"
#elif __sun__
#define OS "SunOS"
#elif __HAIKU__
#define OS "Haiku"
#elif __gnu_hurd__
#define OS "Hurd"
#elif __APPLE__
#define OS "MacOS"
#elif __WIN64__
#define OS "Windows (64 bits)"
#elif __WIN32__
#define OS "Windows (32 bits)"
#endif

void
print_bits (char *label, void *p, unsigned int n)
{
  char *s;
  unsigned int i;
  printf ("%s=", label);
  s = (char *) p;
  for (i = n; i-- > 0;)
    printf ("%02x", s[i] & 0xff);
  printf ("\n");
}

int
main ()
{
  char buffer[64];
  unsigned long int *v64;
  unsigned int *v32;
#if HAVE_QUADMATH
  __float128 xq, xq2;
#endif
  long double xld, xld2;
  double xd, xd2;
  float xf, xf2;
  long long int ill;
  unsigned long long int ull;
  long int il;
  unsigned long int ul;
  int i;
  unsigned int u;
  short int is;
  unsigned short int us;

  printf ("ARCHITECTURE=%s\n", ARCH);
  printf ("OS=%s\n", OS);

  printf ("\nSIZES\n");
  printf ("void*: %lu bits\n", (unsigned long int) 8l * sizeof (void *));
  printf ("char: %lu bits\n", (unsigned long int) 8l * sizeof (char));
  printf ("short int: %lu bits\n", (unsigned long int) 8l * sizeof (short int));
  printf ("int: %lu bits\n", (unsigned long int) 8l * sizeof (int));
  printf ("long int: %lu bits\n", (unsigned long int) 8l * sizeof (long int));
  printf ("long long int: %lu bits\n",
          (unsigned long int) 8l * sizeof (long long int));
  printf ("float: %lu bits\n", (unsigned long int) 8l * sizeof (float));
  printf ("double: %lu bits\n", (unsigned long int) 8l * sizeof (double));
  printf ("long double: %lu bits\n",
          (unsigned long int) 8l * sizeof (long double));
  printf ("_Float128: %lu bits\n",
          (unsigned long int) 8l * sizeof (_Float128));

  printf ("\nLIMITS\n");
  printf ("FLT_MIN=" FF "\n", (float) FLT_MIN);
  printf ("FLT_MIN_EXP=" FF "\n", (float) FLT_MIN_EXP);
  printf ("FLT_MIN_10_EXP=" FF "\n", (float) FLT_MIN_10_EXP);
  printf ("FLT_MAX=" FF "\n", (float) FLT_MAX);
  printf ("FLT_MAX_EXP=" FF "\n", (float) FLT_MAX_EXP);
  printf ("FLT_MAX_10_EXP=" FF "\n", (float) FLT_MAX_10_EXP);
  printf ("FLT_EPSILON=" FF "\n", (float) FLT_EPSILON);
  printf ("DBL_MIN=" FD "\n", (double) DBL_MIN);
  printf ("DBL_MIN_EXP=" FD "\n", (double) DBL_MIN_EXP);
  printf ("DBL_MIN_10_EXP=" FD "\n", (double) DBL_MIN_10_EXP);
  printf ("DBL_MAX=" FD "\n", (double) DBL_MAX);
  printf ("DBL_MAX_EXP=" FD "\n", (double) DBL_MAX_EXP);
  printf ("DBL_MAX_10_EXP=" FD "\n", (double) DBL_MAX_10_EXP);
  printf ("DBL_EPSILON=" FD "\n", (double) DBL_EPSILON);
  printf ("LDBL_MIN=" FLD "\n", (long double) LDBL_MIN);
  printf ("LDBL_MIN_EXP=" FLD "\n", (long double) LDBL_MIN_EXP);
  printf ("LDBL_MIN_10_EXP=" FLD "\n", (long double) LDBL_MIN_10_EXP);
  printf ("LDBL_MAX=" FLD "\n", (long double) LDBL_MAX);
  printf ("LDBL_MAX_EXP=" FLD "\n", (long double) LDBL_MAX_EXP);
  printf ("LDBL_MAX_10_EXP=" FLD "\n", (long double) LDBL_MAX_10_EXP);
  printf ("LDBL_EPSILON=" FLD "\n", (long double) LDBL_EPSILON);
#if HAVE_QUADMATH
  quadmath_snprintf (buffer, 64, FQ, (__float128) FLT128_MIN);
  printf ("FLT128_MIN=%s\n", buffer);
  quadmath_snprintf (buffer, 64, FQ, (__float128) FLT128_MIN_EXP);
  printf ("FLT128_MIN_EXP=%s\n", buffer);
  quadmath_snprintf (buffer, 64, FQ, (__float128) FLT128_MIN_10_EXP);
  printf ("FLT128_MIN_10_EXP=%s\n", buffer);
  quadmath_snprintf (buffer, 64, FQ, (__float128) FLT128_MAX);
  printf ("FLT128_MAX=%s\n", buffer);
  quadmath_snprintf (buffer, 64, FQ, (__float128) FLT128_MAX_EXP);
  printf ("FLT128_MAX_EXP=%s\n", buffer);
  quadmath_snprintf (buffer, 64, FQ, (__float128) FLT128_MAX_10_EXP);
  printf ("FLT128_MAX_10_EXP=%s\n", buffer);
  quadmath_snprintf (buffer, 64, FQ, (__float128) FLT128_EPSILON);
  printf ("FLT128_EPSILON=%s\n", buffer);
#endif

  printf ("\nBITS\n");
  us = 0x0000;
  printf ("(unsigned short int) 0x0000 = %hu\n", us);
  us = 0xffff;
  printf ("(unsigned short int) 0xffff = %hu\n", us);
  u = 0x00000000;
  printf ("(unsigned int) 0x00000000 = %u\n", u);
  u = 0xffffffff;
  printf ("(unsigned int) 0xffffffff = %u\n", u);
  ul = 0x0000000000000000l;
  printf ("(unsigned long int) 0x0000000000000000 = %lu\n", ul);
  ul = 0xffffffffffffffffl;
  printf ("(unsigned long int) 0xffffffffffffffff = %lu\n", ul);
  ull = 0x0000000000000000L;
  printf ("(unsigned long long int) 0x0000000000000000 = %llu\n", ull);
  ull = 0xffffffffffffffffL;
  printf ("(unsigned long long int) 0xffffffffffffffff = %llu\n", ull);
  is = 0x0000;
  printf ("(short int) 0x0000 = %hd\n", is);
  is = 0xffff;
  printf ("(short int) 0xffff = %hd\n", is);
  is = 0x8000;
  printf ("(short int) 0x8000 = %hd\n", is);
  is = 0x7fff;
  printf ("(short int) 0x7fff = %hd\n", is);
  i = 0x00000000;
  printf ("(int) 0x00000000 = %d\n", i);
  i = 0xffffffff;
  printf ("(int) 0xffffffff = %d\n", i);
  i = 0x80000000;
  printf ("(int) 0x80000000 = %d\n", i);
  i = 0x7fffffff;
  printf ("(int) 0x7fffffff = %d\n", i);
  il = 0x0000000000000000l;
  printf ("(long int) 0x0000000000000000 = %ld\n", il);
  il = 0xffffffffffffffffl;
  printf ("(long int) 0xffffffffffffffff = %ld\n", il);
  il = 0x8000000000000000l;
  printf ("(long int) 0x8000000000000000 = %ld\n", il);
  il = 0x7fffffffffffffffl;
  printf ("(long int) 0x7fffffffffffffff = %ld\n", il);
  ill = 0x0000000000000000L;
  printf ("(long long int) 0x0000000000000000 = %lld\n", ill);
  ill = 0xffffffffffffffffL;
  printf ("(long long int) 0xffffffffffffffff = %lld\n", ill);
  ill = 0x8000000000000000L;
  printf ("(long long int) 0x8000000000000000 = %lld\n", ill);
  ill = 0x7fffffffffffffffL;
  printf ("(long long int) 0x7fffffffffffffff = %lld\n", ill);
  xf = FLT_MIN;
  print_bits ("FLT_MIN", &xf, 4);
  xf = FLT_MIN_EXP;
  print_bits ("FLT_MIN_EXP", &xf, 4);
  xf = FLT_MIN_10_EXP;
  print_bits ("FLT_MIN_10_EXP", &xf, 4);
  xf = FLT_MAX;
  print_bits ("FLT_MAX", &xf, 4);
  xf = FLT_MAX_EXP;
  print_bits ("FLT_MAX_EXP", &xf, 4);
  xf = FLT_MAX_10_EXP;
  print_bits ("FLT_MAX_10_EXP", &xf, 4);
  xf = FLT_EPSILON;
  print_bits ("FLT_EPSILON", &xf, 4);
  xf = 1.f;
  print_bits ("1", &xf, 4);
  xd = DBL_MIN;
  print_bits ("DBL_MIN", &xd, 8);
  xd = DBL_MIN_EXP;
  print_bits ("DBL_MIN_EXP", &xd, 8);
  xd = DBL_MIN_10_EXP;
  print_bits ("DBL_MIN_10_EXP", &xd, 8);
  xd = DBL_MAX;
  print_bits ("DBL_MAX", &xd, 8);
  xd = DBL_MAX_EXP;
  print_bits ("DBL_MAX_EXP", &xd, 8);
  xd = DBL_MAX_10_EXP;
  print_bits ("DBL_MAX_10_EXP", &xd, 8);
  xd = DBL_EPSILON;
  print_bits ("DBL_EPSILON", &xd, 8);
  xd = 1.;
  print_bits ("1", &xd, 8);
  xld = LDBL_MIN;
  print_bits ("LDBL_MIN", &xld, 16);
  xld = LDBL_MIN_EXP;
  print_bits ("LDBL_MIN_EXP", &xld, 16);
  xld = LDBL_MIN_10_EXP;
  print_bits ("LDBL_MIN_10_EXP", &xld, 16);
  xld = LDBL_MAX;
  print_bits ("LDBL_MAX", &xld, 16);
  xld = LDBL_MAX_EXP;
  print_bits ("LDBL_MAX_EXP", &xld, 16);
  xld = LDBL_MAX_10_EXP;
  print_bits ("LDBL_MAX_10_EXP", &xld, 16);
  xld = LDBL_EPSILON;
  print_bits ("LDBL_EPSILON", &xld, 16);
  xld = 1.L;
  print_bits ("1", &xld, 16);
#if HAVE_QUADMATH
  xq = FLT128_MIN;
  print_bits ("FLT128_MIN", &xq, 16);
  xq = FLT128_MIN_EXP;
  print_bits ("FLT128_MIN_EXP", &xq, 16);
  xq = FLT128_MIN_10_EXP;
  print_bits ("FLT128_MIN_10_EXP", &xq, 16);
  xq = FLT128_MAX;
  print_bits ("FLT128_MAX", &xq, 16);
  xq = FLT128_MAX_EXP;
  print_bits ("FLT128_MAX_EXP", &xq, 16);
  xq = FLT128_MAX_10_EXP;
  print_bits ("FLT128_MAX_10_EXP", &xq, 16);
  xq = FLT128_EPSILON;
  print_bits ("FLT128_EPSILON", &xq, 16);
  xq = 1.F128;
  print_bits ("1", &xq, 16);
#endif

  printf ("\nFROM BITS\n");
  v32 = (unsigned int *) &xf;
  *v32 = 0x7f7fffff;
  printf ("FLT_MAX=" FF "\n", (float) FLT_MAX);
  printf ("JBM_FLT_MAX=" FF "\n", xf);
  printf ("FLT_MIN=" FF "\n", (float) FLT_MIN);
  *v32 = 0x00800000;
  printf ("JBM_FLT_NORM_MIN=" FF "\n", xf);
  *v32 = 0x00000001;
  printf ("JBM_FLT_MIN=" FF "\n", xf);
  *v32 = 0x3f800000;
  v32 = (unsigned int *) &xf2;
  *v32 = 0x3f800001;
  printf ("FLT_EPSILON=" FF "\n", (float) FLT_EPSILON);
  printf ("JBM_FLT_EPSILON=" FF "\n", xf2 - xf);
  v64 = (unsigned long int *) &xd;
  *v64 = 0x7fefffffffffffff;
  printf ("DBL_MAX=" FD "\n", (double) DBL_MAX);
  printf ("JBM_DBL_MAX=" FD "\n", xd);
  *v64 = 0x0010000000000000;
  printf ("DBL_MIN=" FD "\n", (double) DBL_MIN);
  printf ("JBM_DBL_NORM_MIN=" FD "\n", xd);
  *v64 = 0x0000000000000001;
  printf ("JBM_DBL_MIN=" FD "\n", xd);
  *v64 = 0x3ff0000000000000;
  v64 = (unsigned long int *) &xd2;
  *v64 = 0x3ff0000000000001;
  printf ("DBL_EPSILON=" FD "\n", (double) DBL_EPSILON);
  printf ("JBM_DBL_EPSILON=" FD "\n", xd2 - xd);
  v64 = (unsigned long int *) &xld;
#if __x86_64
  v64[0] = 0xffffffffffffffff;
  v64[1] = 0x0000000000007ffe;
  printf ("LDBL_MAX=" FLD "\n", (long double) LDBL_MAX);
  printf ("JBM_LDBL_MAX=" FLD "\n", xld);
  v64[0] = 0x8000000000000000;
  v64[1] = 0x0000000000000000;
  printf ("LDBL_MIN=" FLD "\n", (long double) LDBL_MIN);
  printf ("JBM_LDBL_NORM_MIN=" FLD "\n", xld);
  v64[0] = 0x0000000000000001;
  v64[1] = 0x0000000000000000;
  printf ("JBM_LDBL_MIN=" FLD "\n", xld);
  v64[0] = 0x8000000000000000;
  v64[1] = 0x0000000000003fff;
  v64 = (unsigned long int *) &xld2;
  v64[0] = 0x8000000000000001;
  v64[1] = 0x0000000000003fff;
  printf ("LDBL_EPSILON=" FLD "\n", (long double) LDBL_EPSILON);
  printf ("JBM_LDBL_EPSILON=" FLD "\n", xld2 - xld);
#elif __riscv
  v64[0] = 0xffffffffffffffff;
  v64[1] = 0x7ffeffffffffffff;
  printf ("LDBL_MAX=" FLD "\n", (long double) LDBL_MAX);
  printf ("JBM_LDBL_MAX=" FLD "\n", xld);
  v64[0] = 0x0000000000000000;
  v64[1] = 0x0001000000000000;
  printf ("LDBL_MIN=" FLD "\n", (long double) LDBL_MIN);
  printf ("JBM_LDBL_NORM_MIN=" FLD "\n", xld);
  v64[0] = 0x0000000000000001;
  v64[1] = 0x0000000000000000;
  printf ("JBM_LDBL_MIN=" FLD "\n", xld);
  v64[0] = 0x0000000000000000;
  v64[1] = 0x3fff000000000000;
  v64 = (unsigned long int *) &xld2;
  v64[0] = 0x0000000000000001;
  v64[1] = 0x3fff000000000000;
  printf ("LDBL_EPSILON=" FLD "\n", (long double) LDBL_EPSILON);
  printf ("JBM_LDBL_EPSILON=" FLD "\n", xld2 - xld);
#endif
#if HAVE_QUADMATH
  v64 = (unsigned long int *) &xq;
  v64[0] = 0xffffffffffffffff;
  v64[1] = 0x7ffeffffffffffff;
  quadmath_snprintf (buffer, 64, FQ, (__float128) FLT128_MAX);
  printf ("FLT128_MAX=%s\n", buffer);
  quadmath_snprintf (buffer, 64, FQ, xq);
  printf ("JBM_FLT128_MAX=%s\n", buffer);
  v64[0] = 0x0000000000000000;
  v64[1] = 0x0001000000000000;
  quadmath_snprintf (buffer, 64, FQ, (__float128) FLT128_MIN);
  printf ("FLT128_MIN=%s\n", buffer);
  quadmath_snprintf (buffer, 64, FQ, xq);
  printf ("JBM_FLT128_NORM_MIN=%s\n", buffer);
  v64[0] = 0x0000000000000001;
  v64[1] = 0x0000000000000000;
  quadmath_snprintf (buffer, 64, FQ, xq);
  printf ("JBM_FLT128_MIN=%s\n", buffer);
  v64[0] = 0x0000000000000000;
  v64[1] = 0x3fff000000000000;
  v64 = (unsigned long int *) &xq2;
  v64[0] = 0x0000000000000001;
  v64[1] = 0x3fff000000000000;
  quadmath_snprintf (buffer, 64, FQ, (__float128) FLT128_EPSILON);
  printf ("FLT128_EPSILON=%s\n", buffer);
  quadmath_snprintf (buffer, 64, FQ, xq2 - xq);
  printf ("JBM_FLT128_EPSILON=%s\n", buffer);
#endif

  return 0;
}
