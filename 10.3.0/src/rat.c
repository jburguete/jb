#include <stdio.h>

void
print_comment (FILE *f, const unsigned int i, const unsigned int j)
{
  const char *ch[5] = { "th", "st", "nd", "rd", "th" };
  const char *th1, *th2;
  if (i > 3)
    th1 = ch[4];
  else
    th1 = ch[i];
  if (j > 3)
    th2 = ch[4];
  else
    th2 = ch[j];
  fprintf (f, "/**\n");
  fprintf (f, " * Function to calculate a %u%s+%u%s order rational (__m128).\n",
           i, th1, j, th2);
  fprintf (f, " *\n");
  fprintf (f, " * \\return rational value.\n");
  fprintf (f, " */\n");
}

void
print_1_0 (FILE *f)
{
  print_comment (f, 0, 1);
  fprintf (f, "static inline __m128\n");
  fprintf (f, "jbm_rational_1_0_4xf32 (const __m128 x, ///< __m128 vector.\n");
  fprintf (f, "                        const float *p) ///< array of coefficients.\n");
  fprintf (f, "{\n");
  fprintf (f, "  return _mm_div_ps (_mm_set1_ps (p[0]),\n");
  fprintf (f, "                     _mm_fmadd_ps (x, _mm_set1_ps (p[1]), _mm_set1_ps (1.f)));\n");
  fprintf (f, "}\n\n");
}

void
print_0 (FILE *f, const unsigned int i)
{
  print_comment (f, 0, i);
  fprintf (f, "static inline __m128\n");
  fprintf (f, "jbm_rational_%u_0_4xf32 (const __m128 x, ///< __m128 vector.\n",
           i);
  fprintf (f, "                        const float *p) ///< array of coefficients.\n");
  fprintf (f, "{\n");
  fprintf (f, "  return _mm_div_ps (_mm_set1_ps (p[0]),\n");
  fprintf (f, "                     _mm_fmadd_ps (x, jbm_polynomial_%u_4xf32 (x, p + 1),\n",
           i - 1);
  fprintf (f, "                                   _mm_set1_ps (1.f)));\n");
  fprintf (f, "}\n\n");
}

void
print_i (FILE *f, const unsigned int i, const unsigned int j)
{
  print_comment (f, j, i - j);
  fprintf (f, "static inline __m128\n");
  fprintf (f, "jbm_rational_%u_%u_4xf32 (const __m128 x, ///< __m128 vector.\n",
           i, j);
  fprintf (f, "                        const float *p) ///< array of coefficients.\n");
  fprintf (f, "{\n");
  fprintf (f, "  return _mm_div_ps (jbm_polynomial_%u_4xf32 (x, p),\n", j);
  fprintf (f, "                     _mm_fmadd_ps (x, jbm_polynomial_%u_4xf32 (x, p + %u),\n",
           i - j - 1, j + 1);
  fprintf (f, "                                   _mm_set1_ps (1.f)));\n");
  fprintf (f, "}\n\n");
}

void
print_n (FILE *f, const unsigned int i)
{
  print_comment (f, 1, i - 1);
  fprintf (f, "static inline __m128\n");
  fprintf (f, "jbm_rational_%u_%u_4xf32 (const __m128 x, ///< __m128 vector.\n",
           i, i - 1);
  fprintf (f, "                        const float *p) ///< array of coefficients.\n");
  fprintf (f, "{\n");
  fprintf (f, "  return _mm_div_ps (jbm_polynomial_%u_4xf32 (x, p),\n", i - 1);
  fprintf (f, "                     _mm_fmadd_ps (x, _mm_set1_ps (p[%u]), _mm_set1_ps (1.f)));\n", i);
  fprintf (f, "}\n\n");
}

void
print_comment_d (FILE *f, const unsigned int i, const unsigned int j)
{
  const char *ch[5] = { "th", "st", "nd", "rd", "th" };
  const char *th1, *th2;
  if (i > 3)
    th1 = ch[4];
  else
    th1 = ch[i];
  if (j > 3)
    th2 = ch[4];
  else
    th2 = ch[j];
  fprintf (f, "/**\n");
  fprintf (f, " * Function to calculate a %u%s+%u%s order rational (__m128d).\n",
           i, th1, j, th2);
  fprintf (f, " *\n");
  fprintf (f, " * \\return rational value.\n");
  fprintf (f, " */\n");
}

void
print_1_0_d (FILE *f)
{
  print_comment_d (f, 0, 1);
  fprintf (f, "static inline __m128d\n");
  fprintf (f, "jbm_rational_1_0_2xf64 (const __m128d x, ///< __m128d vector.\n");
  fprintf (f, "                        const double *p) ///< array of coefficients.\n");
  fprintf (f, "{\n");
  fprintf (f, "  return _mm_div_pd (_mm_set1_pd (p[0]),\n");
  fprintf (f, "                     _mm_fmadd_pd (x, _mm_set1_pd (p[1]), _mm_set1_pd (1.)));\n");
  fprintf (f, "}\n\n");
}

void
print_0_d (FILE *f, const unsigned int i)
{
  print_comment_d (f, 0, i);
  fprintf (f, "static inline __m128d\n");
  fprintf (f, "jbm_rational_%u_0_2xf64 (const __m128d x, ///< __m128d vector.\n",
           i);
  fprintf (f, "                        const double *p) ///< array of coefficients.\n");
  fprintf (f, "{\n");
  fprintf (f, "  return _mm_div_pd (_mm_set1_pd (p[0]),\n");
  fprintf (f, "                     _mm_fmadd_pd (x, jbm_polynomial_%u_2xf64 (x, p + 1),\n",
           i - 1);
  fprintf (f, "                                   _mm_set1_pd (1.)));\n");
  fprintf (f, "}\n\n");
}

void
print_i_d (FILE *f, const unsigned int i, const unsigned int j)
{
  print_comment_d (f, j, i - j);
  fprintf (f, "static inline __m128d\n");
  fprintf (f, "jbm_rational_%u_%u_2xf64 (const __m128d x, ///< __m128d vector.\n",
           i, j);
  fprintf (f, "                        const double *p) ///< array of coefficients.\n");
  fprintf (f, "{\n");
  fprintf (f, "  return _mm_div_pd (jbm_polynomial_%u_2xf64 (x, p),\n", j);
  fprintf (f, "                     _mm_fmadd_pd (x, jbm_polynomial_%u_2xf64 (x, p + %u),\n",
           i - j - 1, j + 1);
  fprintf (f, "                                   _mm_set1_pd (1.)));\n");
  fprintf (f, "}\n\n");
}

void
print_n_d (FILE *f, const unsigned int i)
{
  print_comment_d (f, 1, i - 1);
  fprintf (f, "static inline __m128d\n");
  fprintf (f, "jbm_rational_%u_%u_2xf64 (const __m128d x, ///< __m128d vector.\n",
           i, i - 1);
  fprintf (f, "                        const double *p) ///< array of coefficients.\n");
  fprintf (f, "{\n");
  fprintf (f, "  return _mm_div_pd (jbm_polynomial_%u_2xf64 (x, p),\n", i - 1);
  fprintf (f, "                     _mm_fmadd_pd (x, _mm_set1_pd (p[%u]), _mm_set1_pd (1.)));\n", i);
  fprintf (f, "}\n\n");
}

int
main ()
{
  FILE *f;
  unsigned int i, j;
  f = fopen ("r.c", "w");
  print_1_0 (f);
  for (i = 2; i < 30; ++i)
    {
      print_0 (f, i);
      for (j = 1; j < i - 1; ++j)
        print_i (f, i, j);
      print_n (f, i);
    }
  print_1_0_d (f);
  for (i = 2; i < 30; ++i)
    {
      print_0_d (f, i);
      for (j = 1; j < i - 1; ++j)
        print_i_d (f, i, j);
      print_n_d (f, i);
    }
  fclose (f);
  return 0;
}
