#include <stdio.h>

enum Type
{
  TYPE_SSE = 0,
  TYPE_AVX = 1,
  TYPE_AVX512 = 2,
  TYPE_ARM_NEON = 3,
  TYPE_RISCV = 4,
  TYPE_NONE = 5
};

void
print_comment_pol (FILE *f, const unsigned int i, const unsigned int type)
{
  const char *ch[5] = { "th", "st", "nd", "rd", "th" };
  const char *t[TYPE_NONE] = { "__m128", "__m256", "__m512", "float32x4_t",
    "vfloat32m1_t"
  };
  const char *th;
  if (i > 3)
    th = ch[4];
  else
    th = ch[i];
  fprintf (f, "/**\n");
  fprintf (f, " * Function to calculate a %u%s order polynomial (%s).\n",
           i, th, t[type]);
  fprintf (f, " *\n");
  fprintf (f, " * \\return %s vector of polynomial values.\n", t[type]);
  fprintf (f, " */\n");
}

void
print_pol_1 (FILE *f, const unsigned int type)
{
  print_comment_pol (f, 1, type);
  switch (type)
    {
    case TYPE_SSE:
      fprintf (f, "static inline __m128\n");
      fprintf (f,
               "jbm_polynomial_1_4xdbl (const __m128 x, ///< __m128 vector.\n");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm_fmadd_ps (x, _mm_set1_ps (p[1]), _mm_set1_ps (p[0]));\n");
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256\n");
      fprintf (f,
               "jbm_polynomial_1_8xdbl (const __m256 x, ///< __m256 vector.\n");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm256_fmadd_ps (x, _mm256_set1_ps (p[1]), _mm256_set1_ps (p[0]));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512\n");
      fprintf (f,
               "jbm_polynomial_1_16xdbl (const __m512 x, ///< __m512 vector.\n");
      fprintf (f,
               "                         const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm512_fmadd_ps (x, _mm512_set1_ps (p[1]), _mm512_set1_ps (p[0]));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float32x4_t\n");
      fprintf (f,
               "jbm_polynomial_1_4xdbl (const float32x4_t x, ///< float32x4_t vector.\n");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return vmlaq_dbl (vdupq_n_dbl (p[0]), x, vdupq_n_dbl (p[1]));\n");
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat32m1_t\n");
      fprintf (f,
               "jbm_polynomial_1_nxdbl (const vfloat32m1_t x, ///< vfloat32m1_t vector.\n");
      fprintf (f,
               "                        const float *p, ///< array of coefficients.\n");
      fprintf (f,
               "                        const size_t vl) ///< array size.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return vfmacc_vf_dblm1 (vfmv_v_f_dbl (p[0], vl), p[1], x, vl);\n");
      break;
    }
  fprintf (f, "}\n\n");
}

void
print_pol_i (FILE *f, const unsigned int i, const unsigned int type)
{
  print_comment_pol (f, i, type);
  switch (type)
    {
    case TYPE_SSE:
      fprintf (f, "static inline __m128\n");
      if (i < 10)
        {
          fprintf (f,
                   "jbm_polynomial_%u_4xdbl (const __m128 x, ///< __m128 vector.\n",
                   i);
          fprintf (f,
                   "                        const float *p) ///< array of coefficients.\n");
        }
      else
        {
          fprintf (f,
                   "jbm_polynomial_%u_4xdbl (const __m128 x,        ///< __m128 vector.\n",
                   i);
          fprintf (f,
                   "                         const float *p)        ///< array of coefficients.\n");
        }
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm_fmadd_ps (x, jbm_polynomial_%u_4xdbl (x, p + 1),\n",
               i - 1);
      fprintf (f, "                       _mm_set1_ps (p[0]));\n");
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256\n");
      fprintf (f,
               "jbm_polynomial_%u_8xdbl (const __m256 x, ///< __m256 vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm256_fmadd_ps (x, jbm_polynomial_%u_8xdbl (x, p + 1),\n",
               i - 1);
      fprintf (f, "                          _mm256_set1_ps (p[0]));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512\n");
      fprintf (f,
               "jbm_polynomial_%u_16xdbl (const __m512 x, ///< __m512 vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                         const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm512_fmadd_ps (x, jbm_polynomial_%u_16xdbl (x, p + 1),\n",
               i - 1);
      fprintf (f, "                          _mm512_set1_ps (p[0]));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float32x4_t\n");
      fprintf (f,
               "jbm_polynomial_%u_4xdbl (const float32x4_t x, ///< float32x4_t vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return vmlaq_dbl (vdupq_n_dbl (p[0]), x, jbm_polynomial_%u_4xdbl (x, p + 1));\n",
               i - 1);
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat32m1_t\n");
      fprintf (f,
               "jbm_polynomial_%u_nxdbl (const vfloat32m1_t x, ///< vfloat32m1_t vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p, ///< array of coefficients.\n");
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const size_t vl) ///< array size.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return vfmacc_vv_dblm1 (vfmv_v_f_dblm1 (p[0], vl), x,\n");
      fprintf (f,
               "                          jbm_polynomial_%u_nxdbl (x, p + 1, vl), vl);\n",
               i - 1);
      break;
    }
  fprintf (f, "}\n\n");
}

void
print_comment_rat (FILE *f, const unsigned int i, const unsigned int j,
                   const unsigned int type)
{
  const char *ch[5] = { "th", "st", "nd", "rd", "th" };
  const char *t[TYPE_NONE] = { "__m128", "__m256", "__m512", "float32x4_t",
    "vfloat32m1_t"
  };
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
  fprintf (f, " * Function to calculate a %u%s+%u%s order rational (%s).\n",
           i, th1, j, th2, t[type]);
  fprintf (f, " *\n");
  fprintf (f, " * \\return %s vector of rational values.\n", t[type]);
  fprintf (f, " */\n");
}

void
print_rat_1_0 (FILE *f, const unsigned int type)
{
  print_comment_rat (f, 0, 1, type);
  switch (type)
    {
    case TYPE_SSE:
      fprintf (f, "static inline __m128\n");
      fprintf (f,
               "jbm_rational_1_0_4xdbl (const __m128 x, ///< __m128 vector.\n");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm_div_ps (_mm_set1_ps (p[0]),\n");
      fprintf (f,
               "                     _mm_fmadd_ps (x, _mm_set1_ps (p[1]), _mm_set1_ps (1.f)));\n");
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256\n");
      fprintf (f,
               "jbm_rational_1_0_8xdbl (const __m256 x, ///< __m256 vector.\n");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm256_div_ps (_mm256_set1_ps (p[0]),\n");
      fprintf (f,
               "                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[1]), _mm256_set1_ps (1.f)));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512\n");
      fprintf (f,
               "jbm_rational_1_0_16xdbl (const __m512 x, ///< __m512 vector.\n");
      fprintf (f,
               "                         const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm512_div_ps (_mm512_set1_ps (p[0]),\n");
      fprintf (f,
               "                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[1]), _mm512_set1_ps (1.f)));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float32x4_t\n");
      fprintf (f,
               "jbm_rational_1_0_4xdbl (const float32x4_t x, ///< float32x4_t vector.\n");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return vdivq_dbl (vdupq_n_dbl (p[0]),\n");
      fprintf (f,
               "                    vmlaq_dbl (vdupq_n_dbl (1.f), x, vdupq_n_dbl (p[1])));\n");
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat32m1_t\n");
      fprintf (f,
               "jbm_rational_1_0_nxdbl (const vfloat32m1_t x, ///< vfloat32m1_t vector.\n");
      fprintf (f,
               "                        const float *p, ///< array of coefficients.\n");
      fprintf (f,
               "                        const size_t vl) ///< array size.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return vfdiv_vv_dblm1 (vfmv_v_f_dblm1 (p[0], vl),\n");
      fprintf (f,
               "                         vfmacc_vf_dbl (vfmv_v_f_dblm1 (1.f, vl),\n");
      fprintf (f, "                                        p[1], x, vl));\n");
      break;
    }
  fprintf (f, "}\n\n");
}

void
print_rat_0 (FILE *f, const unsigned int i, const unsigned int type)
{
  print_comment_rat (f, 0, i, type);
  switch (type)
    {
    case TYPE_SSE:
      fprintf (f, "static inline __m128\n");
      fprintf (f,
               "jbm_rational_%u_0_4xdbl (const __m128 x, ///< __m128 vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm_div_ps (_mm_set1_ps (p[0]),\n");
      fprintf (f,
               "                     _mm_fmadd_ps (x, jbm_polynomial_%u_4xdbl (x, p + 1),\n",
               i - 1);
      fprintf (f, "                                   _mm_set1_ps (1.f)));\n");
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256\n");
      fprintf (f,
               "jbm_rational_%u_0_8xdbl (const __m256 x, ///< __m256 vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                         const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm256_div_ps (_mm256_set1_ps (p[0]),\n");
      fprintf (f,
               "                        _mm256_fmadd_ps (x, jbm_polynomial_%u_8xdbl (x, p + 1),\n",
               i - 1);
      fprintf (f,
               "                                         _mm256_set1_ps (1.f)));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512\n");
      fprintf (f,
               "jbm_rational_%u_0_16xdbl (const __m512 x, ///< __m512 vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                         const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm512_div_ps (_mm512_set1_ps (p[0]),\n");
      fprintf (f,
               "                        _mm512_fmadd_ps (x, jbm_polynomial_%u_16xdbl (x, p + 1),\n",
               i - 1);
      fprintf (f,
               "                                         _mm512_set1_ps (1.f)));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float32x4_t\n");
      fprintf (f,
               "jbm_rational_%u_0_4xdbl (const float32x4_t x, ///< float32x4_t vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return vdivq_dbl (vdupq_n_dbl (p[0]),\n");
      fprintf (f, "                    vmlaq_dbl (vdupq_n_dbl (1.f), x,\n");
      fprintf (f,
               "                               jbm_polynomial_%u_4xdbl (x, p + 1)));\n",
               i - 1);
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat32m1_t\n");
      fprintf (f,
               "jbm_rational_%u_0_nxdbl (const vfloat32m1_t x, ///< vfloat32m1_t vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p, ///< array of coefficients.\n");
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const size_t vl) ///< array size.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f, "    vfdiv_vv_dblm1 (vfmv_v_f_dblm1 (p[0], vl),\n");
      fprintf (f,
               "                    vfmacc_vv_dblm1 (vfmv_v_f_dblm1 (1.f, vl), x,\n");
      fprintf (f,
               "                                     jbm_polynomial_%u_nxdbl (x, p + 1, vl),\n",
               i - 1);
      fprintf (f, "                                     vl), vl);\n");
      break;
    }
  fprintf (f, "}\n\n");
}

void
print_rat_i (FILE *f, const unsigned int i, const unsigned int j,
             const unsigned int type)
{
  print_comment_rat (f, j, i - j, type);
  switch (type)
    {
    case TYPE_SSE:
      fprintf (f, "static inline __m128\n");
      fprintf (f,
               "jbm_rational_%u_%u_4xdbl (const __m128 x, ///< __m128 vector.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm_div_ps (jbm_polynomial_%u_4xdbl (x, p),\n", j);
      fprintf (f,
               "                     _mm_fmadd_ps (x, jbm_polynomial_%u_4xdbl (x, p + %u),\n",
               i - j - 1, j + 1);
      fprintf (f, "                                   _mm_set1_ps (1.f)));\n");
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256\n");
      fprintf (f,
               "jbm_rational_%u_%u_8xdbl (const __m256 x, ///< __m256 vector.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm256_div_ps (jbm_polynomial_%u_8xdbl (x, p),\n",
               j);
      fprintf (f,
               "                        _mm256_fmadd_ps (x, jbm_polynomial_%u_8xdbl (x, p + %u),\n",
               i - j - 1, j + 1);
      fprintf (f,
               "                                         _mm256_set1_ps (1.f)));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512\n");
      fprintf (f,
               "jbm_rational_%u_%u_16xdbl (const __m512 x, ///< __m512 vector.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm512_div_ps (jbm_polynomial_%u_16xdbl (x, p),\n",
               j);
      fprintf (f,
               "                        _mm512_fmadd_ps (x, jbm_polynomial_%u_16xdbl (x, p + %u),\n",
               i - j - 1, j + 1);
      fprintf (f,
               "                                         _mm512_set1_ps (1.f)));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float32x4_t\n");
      fprintf (f,
               "jbm_rational_%u_%u_4xdbl (const float32x4_t x, ///< float32x4_t vector.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return vdivq_dbl (jbm_polynomial_%u_4xdbl (x, p),\n", j);
      fprintf (f, "                    vmlaq_dbl (vdupq_n_dbl (1.f), x,\n");
      fprintf (f,
               "                               jbm_polynomial_%u_4xdbl (x, p + %u)));\n",
               i - j - 1, j + 1);
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat32m1_t\n");
      fprintf (f,
               "jbm_rational_%u_%u_nxdbl (const vfloat32m1_t x, ///< vfloat32m1_t vector.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p, ///< array of coefficients.\n");
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const size_t vl) ///< array size.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f, "    vfdiv_vv_dblm1 (jbm_polynomial_%u_nxdbl (x, p, vl),\n",
               j);
      fprintf (f,
               "                    vfmacc_vv_dblm1 (vfmv_v_f_dblm1 (1.f, vl), x,\n");
      fprintf (f,
               "                                     jbm_polynomial_%u_nxdbl (x, p + %u, vl),\n",
               i - j - 1, j + 1);
      if (i - j > 10)
        fprintf (f, " ");
      if (j > 8)
        fprintf (f, " ");
      fprintf (f,
               "                                                             vl), vl);\n");
      break;
    }
  fprintf (f, "}\n\n");
}

void
print_rat_n (FILE *f, const unsigned int i, const unsigned int type)
{
  print_comment_rat (f, 1, i - 1, type);
  switch (type)
    {
    case TYPE_SSE:
      fprintf (f, "static inline __m128\n");
      fprintf (f,
               "jbm_rational_%u_%u_4xdbl (const __m128 x, ///< __m128 vector.\n",
               i, i - 1);
      if (i > 9)
        {
          fprintf (f, " ");
          if (i > 10)
            fprintf (f, " ");
        }
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm_div_ps (jbm_polynomial_%u_4xdbl (x, p),\n",
               i - 1);
      fprintf (f,
               "                     _mm_fmadd_ps (x, _mm_set1_ps (p[%u]), _mm_set1_ps (1.f)));\n",
               i);
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256\n");
      fprintf (f,
               "jbm_rational_%u_%u_8xdbl (const __m256 x, ///< __m256 vector.\n",
               i, i - 1);
      if (i > 9)
        {
          fprintf (f, " ");
          if (i > 10)
            fprintf (f, " ");
        }
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm256_div_ps (jbm_polynomial_%u_8xdbl (x, p),\n",
               i - 1);
      fprintf (f,
               "                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[%u]),\n",
               i);
      fprintf (f,
               "                                         _mm256_set1_ps (1.f)));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512\n");
      fprintf (f,
               "jbm_rational_%u_%u_16xdbl (const __m512 x, ///< __m512 vector.\n",
               i, i - 1);
      if (i > 9)
        {
          fprintf (f, " ");
          if (i > 10)
            fprintf (f, " ");
        }
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm512_div_ps (jbm_polynomial_%u_16xdbl (x, p),\n",
               i - 1);
      fprintf (f,
               "                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[%u]),\n",
               i);
      fprintf (f,
               "                                         _mm512_set1_ps (1.f)));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float32x4_t\n");
      fprintf (f,
               "jbm_rational_%u_%u_4xdbl (const float32x4_t x, ///< float32x4_t vector.\n",
               i, i - 1);
      if (i > 9)
        {
          fprintf (f, " ");
          if (i > 10)
            fprintf (f, " ");
        }
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return vdivq_dbl (jbm_polynomial_%u_4xdbl (x, p),\n",
               i - 1);
      fprintf (f,
               "                    vmlaq_dbl (vdupq_n_dbl (1.f), x, vdupq_n_dbl (p[%u])));\n",
               i);
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat32m1_t\n");
      fprintf (f,
               "jbm_rational_%u_%u_nxdbl (const vfloat32m1_t x, ///< vfloat32m1_t vector.\n",
               i, i - 1);
      if (i > 9)
        {
          fprintf (f, " ");
          if (i > 10)
            fprintf (f, " ");
        }
      fprintf (f,
               "                        const float *p, ///< array of coefficients.\n");
      if (i > 9)
        {
          fprintf (f, " ");
          if (i > 10)
            fprintf (f, " ");
        }
      fprintf (f,
               "                        const size_t vl) ///< array size.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f, "    vfdiv_vv_dblm1 (jbm_polynomial_%u_nxdbl (x, p, vl),\n",
               i - 1);
      fprintf (f,
               "                    vfmacc_vf_dblm1 (vfmv_v_f_dblm1 (1.f, vl), p[%u], x, vl),\n",
               i);
      fprintf (f, "                    vl);\n");
      break;
    }
  fprintf (f, "}\n\n");
}

void
print_comment_pol_d (FILE *f, const unsigned int i, const unsigned int type)
{
  const char *ch[5] = { "th", "st", "nd", "rd", "th" };
  const char *t[TYPE_NONE] = { "__m128d", "__m256d", "__m512d", "float64x2_t",
    "vfloat64m1_t"
  };
  const char *th;
  if (i > 3)
    th = ch[4];
  else
    th = ch[i];
  fprintf (f, "/**\n");
  fprintf (f, " * Function to calculate a %u%s order polynomial (%s).\n",
           i, th, t[type]);
  fprintf (f, " *\n");
  fprintf (f, " * \\return %s vector of polynomial values.\n", t[type]);
  fprintf (f, " */\n");
}

void
print_pol_1_d (FILE *f, const unsigned int type)
{
  print_comment_pol_d (f, 1, type);
  switch (type)
    {
    case TYPE_SSE:
      fprintf (f, "static inline __m128d\n");
      fprintf (f,
               "jbm_polynomial_1_2xdbl (const __m128d x, ///< __m128d vector.\n");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm_fmadd_pd (x, _mm_set1_pd (p[1]), _mm_set1_pd (p[0]));\n");
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256d\n");
      fprintf (f,
               "jbm_polynomial_1_4xdbl (const __m256d x, ///< __m256d vector.\n");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm256_fmadd_pd (x, _mm256_set1_pd (p[1]), _mm256_set1_pd (p[0]));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512d\n");
      fprintf (f,
               "jbm_polynomial_1_8xdbl (const __m512d x, ///< __m512d vector.\n");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm512_fmadd_pd (x, _mm512_set1_pd (p[1]), _mm512_set1_pd (p[0]));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float64x2_t\n");
      fprintf (f,
               "jbm_polynomial_1_2xdbl (const float64x2_t x, ///< float64x2_t vector.\n");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return vmlaq_dbl (vdupq_n_dbl (p[0]), x, vdupq_n_dbl (p[1]));\n");
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat64m1_t\n");
      fprintf (f,
               "jbm_polynomial_1_nxdbl (const vfloat64m1_t x, ///< vfloat64m1_t vector.\n");
      fprintf (f,
               "                        const double *p, ///< array of coefficients.\n");
      fprintf (f,
               "                        const size_t vl) ///< array size.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return vfmacc_vx_dblm1 (vfmv_v_f_dbl (p[0], vl), p[1], x, vl);\n");
      break;
    }
  fprintf (f, "}\n\n");
}

void
print_pol_i_d (FILE *f, const unsigned int i, const unsigned int type)
{
  print_comment_pol_d (f, i, type);
  switch (type)
    {
    case TYPE_SSE:
      fprintf (f, "static inline __m128d\n");
      fprintf (f,
               "jbm_polynomial_%u_2xdbl (const __m128d x, ///< __m128d vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm_fmadd_pd (x, jbm_polynomial_%u_2xdbl (x, p + 1),\n",
               i - 1);
      fprintf (f, "                       _mm_set1_pd (p[0]));\n");
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256d\n");
      fprintf (f,
               "jbm_polynomial_%u_4xdbl (const __m256d x, ///< __m256d vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm256_fmadd_pd (x, jbm_polynomial_%u_4xdbl (x, p + 1),\n",
               i - 1);
      fprintf (f, "                          _mm256_set1_pd (p[0]));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512d\n");
      fprintf (f,
               "jbm_polynomial_%u_8xdbl (const __m512d x, ///< __m512d vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm512_fmadd_pd (x, jbm_polynomial_%u_8xdbl (x, p + 1),\n",
               i - 1);
      fprintf (f, "                          _mm512_set1_pd (p[0]));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float64x2_t\n");
      fprintf (f,
               "jbm_polynomial_%u_2xdbl (const float64x2_t x, ///< float64x2_t vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return vmlaq_dbl (vdupq_n_dbl (p[0]), x, jbm_polynomial_%u_2xdbl (x, p + 1));\n",
               i - 1);
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat64m1_t\n");
      fprintf (f,
               "jbm_polynomial_%u_nxdbl (const vfloat64m1_t x, ///< vfloat64m1_t vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p, ///< array of coefficients.\n");
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const size_t vl) ///< array size.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return vfmacc_vv_dblm1 (vfmv_v_f_dblm1 (p[0], vl), x,\n");
      fprintf (f,
               "                          jbm_polynomial_%u_nxdbl (x, p + 1, vl), vl);\n",
               i - 1);
      break;
    }
  fprintf (f, "}\n\n");
}

void
print_comment_rat_d (FILE *f, const unsigned int i, const unsigned int j,
                     const unsigned int type)
{
  const char *ch[5] = { "th", "st", "nd", "rd", "th" };
  const char *t[TYPE_NONE] = { "__m128d", "__m256d", "__m512d", "float64x2_t",
    "vfloat64m1_t"
  };
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
  fprintf (f, " * Function to calculate a %u%s+%u%s order rational (%s).\n",
           i, th1, j, th2, t[type]);
  fprintf (f, " *\n");
  fprintf (f, " * \\return %s vector of rational values.\n", t[type]);
  fprintf (f, " */\n");
}

void
print_rat_1_0_d (FILE *f, const unsigned int type)
{
  print_comment_rat_d (f, 0, 1, type);
  switch (type)
    {
    case TYPE_SSE:
      fprintf (f, "static inline __m128d\n");
      fprintf (f,
               "jbm_rational_1_0_2xdbl (const __m128d x, ///< __m128d vector.\n");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm_div_pd (_mm_set1_pd (p[0]),\n");
      fprintf (f,
               "                     _mm_fmadd_pd (x, _mm_set1_pd (p[1]), _mm_set1_pd (1.)));\n");
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256d\n");
      fprintf (f,
               "jbm_rational_1_0_4xdbl (const __m256d x, ///< __m256d vector.\n");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm256_div_pd (_mm256_set1_pd (p[0]),\n");
      fprintf (f,
               "                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[1]), _mm256_set1_pd (1.)));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512d\n");
      fprintf (f,
               "jbm_rational_1_0_8xdbl (const __m512d x, ///< __m512d vector.\n");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm512_div_pd (_mm512_set1_pd (p[0]),\n");
      fprintf (f,
               "                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[1]), _mm512_set1_pd (1.)));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float64x2_t\n");
      fprintf (f,
               "jbm_rational_1_0_2xdbl (const float64x2_t x, ///< float64x2_t vector.\n");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return vdivq_dbl (vdupq_n_dbl (p[0]),\n");
      fprintf (f,
               "                    vmlaq_dbl (vdupq_n_dbl (1.), x, vdupq_n_dbl (p[1])));\n");
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat64m1_t\n");
      fprintf (f,
               "jbm_rational_1_0_nxdbl (const vfloat64m1_t x, ///< vfloat64m1_t vector.\n");
      fprintf (f,
               "                        const double *p, ///< array of coefficients.\n");
      fprintf (f,
               "                        const size_t vl) ///< array size.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return vfdiv_vv_dblm1 (vfmv_v_f_dblm1 (p[0], vl),\n");
      fprintf (f,
               "                         vfmacc_vf_dbl (vfmv_v_f_dblm1 (1., vl),\n");
      fprintf (f, "                                        p[1], x, vl));\n");
      break;
    }
  fprintf (f, "}\n\n");
}

void
print_rat_0_d (FILE *f, const unsigned int i, const unsigned int type)
{
  print_comment_rat_d (f, 0, i, type);
  switch (type)
    {
    case TYPE_SSE:
      fprintf (f, "static inline __m128d\n");
      fprintf (f,
               "jbm_rational_%u_0_2xdbl (const __m128d x, ///< __m128d vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                         const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm_div_pd (_mm_set1_pd (p[0]),\n");
      fprintf (f,
               "                     _mm_fmadd_pd (x, jbm_polynomial_%u_2xdbl (x, p + 1),\n",
               i - 1);
      fprintf (f, "                                   _mm_set1_pd (1.)));\n");
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256d\n");
      fprintf (f,
               "jbm_rational_%u_0_4xdbl (const __m256d x, ///< __m256d vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                         const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm256_div_pd (_mm256_set1_pd (p[0]),\n");
      fprintf (f,
               "                        _mm256_fmadd_pd (x, jbm_polynomial_%u_4xdbl (x, p + 1),\n",
               i - 1);
      fprintf (f,
               "                                         _mm256_set1_pd (1.)));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512d\n");
      fprintf (f,
               "jbm_rational_%u_0_8xdbl (const __m512d x, ///< __m512d vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                         const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm512_div_pd (_mm512_set1_pd (p[0]),\n");
      fprintf (f,
               "                        _mm512_fmadd_pd (x, jbm_polynomial_%u_8xdbl (x, p + 1),\n",
               i - 1);
      fprintf (f,
               "                                         _mm512_set1_pd (1.)));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float64x2_t\n");
      fprintf (f,
               "jbm_rational_%u_0_2xdbl (const float64x2_t x, ///< float64x2_t vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return vdivq_dbl (vdupq_n_dbl (p[0]),\n");
      fprintf (f, "                    vmlaq_dbl (vdupq_n_dbl (1.), x,\n");
      fprintf (f,
               "                               jbm_polynomial_%u_2xdbl (x, p + 1)));\n",
               i - 1);
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat64m1_t\n");
      fprintf (f,
               "jbm_rational_%u_0_nxdbl (const vfloat64m1_t x, ///< vfloat64m1_t vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p, ///< array of coefficients.\n");
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const size_t vl) ///< array size.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f, "    vfdiv_vv_dblm1 (vfmv_v_f_dblm1 (p[0], vl),\n");
      fprintf (f,
               "                    vfmacc_vv_dblm1 (vfmv_v_f_dblm1 (1., vl), x,\n");
      fprintf (f,
               "                                     jbm_polynomial_%u_nxdbl (x, p + 1, vl),\n",
               i - 1);
      fprintf (f, "                                     vl), vl);\n");
      break;
    }
  fprintf (f, "}\n\n");
}

void
print_rat_i_d (FILE *f, const unsigned int i, const unsigned int j,
               const unsigned int type)
{
  print_comment_rat_d (f, j, i - j, type);
  switch (type)
    {
    case TYPE_SSE:
      fprintf (f, "static inline __m128d\n");
      fprintf (f,
               "jbm_rational_%u_%u_2xdbl (const __m128d x, ///< __m128d vector.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm_div_pd (jbm_polynomial_%u_2xdbl (x, p),\n", j);
      fprintf (f,
               "                     _mm_fmadd_pd (x, jbm_polynomial_%u_2xdbl (x, p + %u),\n",
               i - j - 1, j + 1);
      fprintf (f, "                                   _mm_set1_pd (1.)));\n");
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256d\n");
      fprintf (f,
               "jbm_rational_%u_%u_4xdbl (const __m256d x, ///< __m256d vector.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm256_div_pd (jbm_polynomial_%u_4xdbl (x, p),\n",
               j);
      fprintf (f,
               "                        _mm256_fmadd_pd (x, jbm_polynomial_%u_4xdbl (x, p + %u),\n",
               i - j - 1, j + 1);
      fprintf (f,
               "                                         _mm256_set1_pd (1.)));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512d\n");
      fprintf (f,
               "jbm_rational_%u_%u_8xdbl (const __m512d x, ///< __m512d vector.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm512_div_pd (jbm_polynomial_%u_8xdbl (x, p),\n",
               j);
      fprintf (f,
               "                        _mm512_fmadd_pd (x, jbm_polynomial_%u_8xdbl (x, p + %u),\n",
               i - j - 1, j + 1);
      fprintf (f,
               "                                         _mm512_set1_pd (1.)));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float64x2_t\n");
      fprintf (f,
               "jbm_rational_%u_%u_2xdbl (const float64x2_t x, ///< float64x2_t vector.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return vdivq_dbl (jbm_polynomial_%u_2xdbl (x, p),\n", j);
      fprintf (f, "                    vmlaq_dbl (vdupq_n_dbl (1.), x,\n");
      fprintf (f,
               "                               jbm_polynomial_%u_2xdbl (x, p + %u)));\n",
               i - j - 1, j + 1);
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat64m1_t\n");
      fprintf (f,
               "jbm_rational_%u_%u_nxdbl (const vfloat64m1_t x, ///< vfloat64m1_t vector.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p, ///< array of coefficients.\n");
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const size_t vl) ///< array size.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f, "    vfdiv_vv_dblm1 (jbm_polynomial_%u_nxdbl (x, p, vl),\n",
               j);
      fprintf (f,
               "                    vfmacc_vv_dblm1 (vfmv_v_f_dblm1 (1., vl), x,\n");
      fprintf (f,
               "                                     jbm_polynomial_%u_nxdbl (x, p + %u, vl),\n",
               i - j - 1, j + 1);
      if (i - j > 10)
        fprintf (f, " ");
      if (j > 8)
        fprintf (f, " ");
      fprintf (f,
               "                                                             vl), vl);\n");
      break;
    }
  fprintf (f, "}\n\n");
}

void
print_rat_n_d (FILE *f, const unsigned int i, const unsigned int type)
{
  print_comment_rat_d (f, 1, i - 1, type);
  switch (type)
    {
    case TYPE_SSE:
      fprintf (f, "static inline __m128d\n");
      fprintf (f,
               "jbm_rational_%u_%u_2xdbl (const __m128d x, ///< __m128d vector.\n",
               i, i - 1);
      if (i > 9)
        {
          fprintf (f, " ");
          if (i > 10)
            fprintf (f, " ");
        }
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm_div_pd (jbm_polynomial_%u_2xdbl (x, p),\n",
               i - 1);
      fprintf (f,
               "                     _mm_fmadd_pd (x, _mm_set1_pd (p[%u]), _mm_set1_pd (1.)));\n",
               i);
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256d\n");
      fprintf (f,
               "jbm_rational_%u_%u_4xdbl (const __m256d x, ///< __m256d vector.\n",
               i, i - 1);
      if (i > 9)
        {
          fprintf (f, " ");
          if (i > 10)
            fprintf (f, " ");
        }
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm256_div_pd (jbm_polynomial_%u_4xdbl (x, p),\n",
               i - 1);
      fprintf (f,
               "                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[%u]),\n",
               i);
      fprintf (f,
               "                                         _mm256_set1_pd (1.)));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512d\n");
      fprintf (f,
               "jbm_rational_%u_%u_8xdbl (const __m512d x, ///< __m512d vector.\n",
               i, i - 1);
      if (i > 9)
        {
          fprintf (f, " ");
          if (i > 10)
            fprintf (f, " ");
        }
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm512_div_pd (jbm_polynomial_%u_8xdbl (x, p),\n",
               i - 1);
      fprintf (f,
               "                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[%u]),\n",
               i);
      fprintf (f,
               "                                         _mm512_set1_pd (1.)));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float64x2_t\n");
      fprintf (f,
               "jbm_rational_%u_%u_2xdbl (const float64x2_t x, ///< float64x2_t vector.\n",
               i, i - 1);
      if (i > 9)
        {
          fprintf (f, " ");
          if (i > 10)
            fprintf (f, " ");
        }
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return vdivq_dbl (jbm_polynomial_%u_2xdbl (x, p),\n",
               i - 1);
      fprintf (f,
               "                    vmlaq_dbl (vdupq_n_dbl (1.), x, vdupq_n_dbl (p[%u])));\n",
               i);
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat64m1_t\n");
      fprintf (f,
               "jbm_rational_%u_%u_nxdbl (const vfloat64m1_t x, ///< vfloat64m1_t vector.\n",
               i, i - 1);
      if (i > 9)
        {
          fprintf (f, " ");
          if (i > 10)
            fprintf (f, " ");
        }
      fprintf (f,
               "                        const double *p, ///< array of coefficients.\n");
      if (i > 9)
        {
          fprintf (f, " ");
          if (i > 10)
            fprintf (f, " ");
        }
      fprintf (f,
               "                        const size_t vl) ///< array size.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f, "    vfdiv_vv_dblm1 (jbm_polynomial_%u_nxdbl (x, p, vl),\n",
               i - 1);
      fprintf (f,
               "                    vfmacc_vf_dblm1 (vfmv_v_f_dblm1 (1., vl), p[%u], x, vl),\n",
               i);
      fprintf (f, "                    vl);\n");
      break;
    }
  fprintf (f, "}\n\n");
}

int
main ()
{
  char buffer[64];
  FILE *f;
  unsigned int i, j, k;
  for (k = 0; k < TYPE_NONE; ++k)
    {
      snprintf (buffer, 64, "r%u.c", k);
      f = fopen (buffer, "w");
      print_pol_1 (f, k);
      for (i = 2; i < 30; ++i)
        print_pol_i (f, i, k);
      print_rat_1_0 (f, k);
      for (i = 2; i < 30; ++i)
        {
          print_rat_0 (f, i, k);
          for (j = 1; j < i - 1; ++j)
            print_rat_i (f, i, j, k);
          print_rat_n (f, i, k);
        }
      print_pol_1_d (f, k);
      for (i = 2; i < 30; ++i)
        print_pol_i_d (f, i, k);
      print_rat_1_0_d (f, k);
      for (i = 2; i < 30; ++i)
        {
          print_rat_0_d (f, i, k);
          for (j = 1; j < i - 1; ++j)
            print_rat_i_d (f, i, j, k);
          print_rat_n_d (f, i, k);
        }
      fclose (f);
    }
  return 0;
}
