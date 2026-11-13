#include <stdio.h>

enum Type
{
  TYPE_SSE = 0,
  TYPE_AVX = 1,
  TYPE_AVX512 = 2,
  TYPE_ARM_NEON = 3,
  TYPE_RISCV = 4,
  TYPE_SVE = 5,
  TYPE_LSX = 6,
  TYPE_LSX = 7,
  TYPE_NONE = 8
};

void
print_comment_pol (FILE *f, const unsigned int i, const unsigned int type)
{
  const char *ch[5] = { "th", "st", "nd", "rd", "th" };
  const char *t[TYPE_NONE] = { "__m128", "__m256", "__m512", "float32x4_t",
    "vfloat32m1_t", "svfloat32_t", "__m128", "__m256"
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
               "jbm_4xf32_polynomial_1 (const __m128 x, ///< __m128 vector.\n");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm_fmadd_ps (x, _mm_set1_ps (p[1]), _mm_set1_ps (p[0]));\n");
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256\n");
      fprintf (f,
               "jbm_8xf32_polynomial_1 (const __m256 x, ///< __m256 vector.\n");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm256_fmadd_ps (x, _mm256_set1_ps (p[1]), _mm256_set1_ps (p[0]));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512\n");
      fprintf (f,
               "jbm_16xf32_polynomial_1 (const __m512 x, ///< __m512 vector.\n");
      fprintf (f,
               "                         const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm512_fmadd_ps (x, _mm512_set1_ps (p[1]), _mm512_set1_ps (p[0]));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float32x4_t\n");
      fprintf (f,
               "jbm_4xf32_polynomial_1 (const float32x4_t x, ///< float32x4_t vector.\n");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, vdupq_n_f32 (p[1]));\n");
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat32m1_t\n");
      fprintf (f,
               "jbm_nxf32_polynomial_1 (const vfloat32m1_t x, ///< vfloat32m1_t vector.\n");
      fprintf (f,
               "                        const float *p, ///< array of coefficients.\n");
      fprintf (f,
               "                        const size_t vl) ///< array size.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f,
               "    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), p[1], x, vl);\n");
      break;
    case TYPE_SVE:
      fprintf (f, "static inline svfloat32_t\n");
      fprintf (f, "jbm_nxf32_polynomial_1 (svbool_t pg, ///< predicate.\n");
      fprintf (f,
               "                        const svfloat32_t x, ///< svfloat32_t vector.\n");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return svmla_n_f32_x (pg, svdup_n_f32 (p[0]), x, p[1]);\n");
      break;
    case TYPE_LSX:
      fprintf (f, "static inline __m128\n");
      fprintf (f,
               "jbm_4xf32_polynomial_1 (const __m128 x, ///< __m128 vector.\n");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f,
               "    __lsx_vfmadd_s (x, __lsx_vreplfr2vr_s (p[1]), __lsx_vreplfr2vr_s (p[0]));\n");
      break;
    case TYPE_LASX:
      fprintf (f, "static inline __m256\n");
      fprintf (f,
               "jbm_8xf32_polynomial_1 (const __m256 x, ///< __m256 vector.\n");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f,
               "    __lasx_vfmadd_s (x, __lasx_xvreplfr2vr_s (p[1]),\n");
      fprintf (f, "                     __lasx_xvreplfr2vr_s (p[0]));\n");
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
      fprintf (f,
               "jbm_4xf32_polynomial_%u (const __m128 x, ///< __m128 vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_%u (x, p + 1),\n",
               i - 1);
      fprintf (f, "                    _mm_set1_ps (p[0]));\n");
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256\n");
      fprintf (f,
               "jbm_8xf32_polynomial_%u (const __m256 x, ///< __m256 vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_%u (x, p + 1),\n",
               i - 1);
      fprintf (f, "                       _mm256_set1_ps (p[0]));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512\n");
      fprintf (f,
               "jbm_16xf32_polynomial_%u (const __m512 x, ///< __m512 vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                         const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_%u (x, p + 1),\n",
               i - 1);
      fprintf (f, "                       _mm512_set1_ps (p[0]));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float32x4_t\n");
      fprintf (f,
               "jbm_4xf32_polynomial_%u (const float32x4_t x, ///< float32x4_t vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_%u (x, p + 1));\n",
               i - 1);
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat32m1_t\n");
      fprintf (f,
               "jbm_nxf32_polynomial_%u (const vfloat32m1_t x, ///< vfloat32m1_t vector.\n",
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
      fprintf (f,
               "    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,\n");
      fprintf (f,
               "                             jbm_nxf32_polynomial_%u (x, p + 1, vl), vl);\n",
               i - 1);
      break;
    case TYPE_SVE:
      fprintf (f, "static inline svfloat32_t\n");
      fprintf (f, "jbm_nxf32_polynomial_%u (svbool_t pg, ///< predicate.\n", i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const svfloat32_t x, ///< svfloat32_t vector.\n");
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,\n");
      fprintf (f,
               "                      jbm_nxf32_polynomial_%u (pg, x, p + 1));\n",
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
    "vfloat32m1_t", "svfloat32_t"
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
               "jbm_4xf32_rational_1_0 (const __m128 x, ///< __m128 vector.\n");
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
               "jbm_8xf32_rational_1_0 (const __m256 x, ///< __m256 vector.\n");
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
               "jbm_16xf32_rational_1_0 (const __m512 x, ///< __m512 vector.\n");
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
               "jbm_4xf32_rational_1_0 (const float32x4_t x, ///< float32x4_t vector.\n");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return vdivq_f32 (vdupq_n_f32 (p[0]),\n");
      fprintf (f,
               "                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[1])));\n");
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat32m1_t\n");
      fprintf (f,
               "jbm_nxf32_rational_1_0 (const vfloat32m1_t x, ///< vfloat32m1_t vector.\n");
      fprintf (f,
               "                        const float *p, ///< array of coefficients.\n");
      fprintf (f,
               "                        const size_t vl) ///< array size.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f,
               "    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),\n");
      fprintf (f,
               "                            __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl),\n");
      fprintf (f,
               "                                                     p[1], x, vl));\n");
      break;
    case TYPE_SVE:
      fprintf (f, "static inline svfloat32_t\n");
      fprintf (f, "jbm_nxf32_rational_1_0 (svbool_t pg, ///< predicate.\n");
      fprintf (f,
               "                        const svfloat32_t x, ///< svfloat32_t vector.\n");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f, "    svdiv_f32_x (pg, svdup_n_f32 (p[0]),\n");
      fprintf (f,
               "                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[1]));\n");
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
               "jbm_4xf32_rational_%u_0 (const __m128 x, ///< __m128 vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f, "    _mm_div_ps (_mm_set1_ps (p[0]),\n");
      fprintf (f,
               "                _mm_fmadd_ps (x, jbm_4xf32_polynomial_%u (x, p + 1),\n",
               i - 1);
      fprintf (f, "                              _mm_set1_ps (1.f)));\n");
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256\n");
      fprintf (f,
               "jbm_8xf32_rational_%u_0 (const __m256 x, ///< __m256 vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm256_div_ps (_mm256_set1_ps (p[0]),\n");
      fprintf (f,
               "                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_%u (x, p + 1),\n",
               i - 1);
      fprintf (f,
               "                                         _mm256_set1_ps (1.f)));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512\n");
      fprintf (f,
               "jbm_16xf32_rational_%u_0 (const __m512 x, ///< __m512 vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                         const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f, "    _mm512_div_ps (_mm512_set1_ps (p[0]),\n");
      fprintf (f,
               "                   _mm512_fmadd_ps (x, jbm_16xf32_polynomial_%u (x, p + 1),\n",
               i - 1);
      fprintf (f,
               "                                    _mm512_set1_ps (1.f)));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float32x4_t\n");
      fprintf (f,
               "jbm_4xf32_rational_%u_0 (const float32x4_t x, ///< float32x4_t vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return vdivq_f32 (vdupq_n_f32 (p[0]),\n");
      fprintf (f, "                    vmlaq_f32 (vdupq_n_f32 (1.f), x,\n");
      fprintf (f,
               "                               jbm_4xf32_polynomial_%u (x, p + 1)));\n",
               i - 1);
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat32m1_t\n");
      fprintf (f,
               "jbm_nxf32_rational_%u_0 (const vfloat32m1_t x, ///< vfloat32m1_t vector.\n",
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
      fprintf (f, "    __riscv_vfdiv_vv_f32m1\n");
      fprintf (f, "    (__riscv_vfmv_v_f_f32m1 (p[0], vl),\n");
      fprintf (f,
               "     __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,\n");
      fprintf (f,
               "                              jbm_nxf32_polynomial_%u (x, p + 1, vl), vl), vl);\n",
               i - 1);
      break;
    case TYPE_SVE:
      fprintf (f, "static inline svfloat32_t\n");
      fprintf (f, "jbm_nxf32_rational_%u_0 (svbool_t pg, ///< predicate.\n", i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const svfloat32_t x, ///< svfloat32_t vector.\n");
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f, "    svdiv_f32_x (pg, svdup_n_f32 (p[0]),\n");
      fprintf (f, "                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,\n");
      fprintf (f,
               "                              jbm_nxf32_polynomial_%u (pg, x, p + 1)));\n",
               i - 1);
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
               "jbm_4xf32_rational_%u_%u (const __m128 x, ///< __m128 vector.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm_div_ps (jbm_4xf32_polynomial_%u (x, p),\n", j);
      fprintf (f,
               "                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_%u (x, p + %u),\n",
               i - j - 1, j + 1);
      fprintf (f, "                                   _mm_set1_ps (1.f)));\n");
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256\n");
      fprintf (f,
               "jbm_8xf32_rational_%u_%u (const __m256 x, ///< __m256 vector.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm256_div_ps (jbm_8xf32_polynomial_%u (x, p),\n",
               j);
      fprintf (f,
               "                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_%u (x, p + %u),\n",
               i - j - 1, j + 1);
      fprintf (f,
               "                                         _mm256_set1_ps (1.f)));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512\n");
      fprintf (f,
               "jbm_16xf32_rational_%u_%u (const __m512 x, ///< __m512 vector.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm512_div_ps (jbm_16xf32_polynomial_%u (x, p),\n",
               j);
      fprintf (f,
               "                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_%u (x, p + %u),\n",
               i - j - 1, j + 1);
      fprintf (f,
               "                                         _mm512_set1_ps (1.f)));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float32x4_t\n");
      fprintf (f,
               "jbm_4xf32_rational_%u_%u (const float32x4_t x, ///< float32x4_t vector.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return vdivq_f32 (jbm_4xf32_polynomial_%u (x, p),\n", j);
      fprintf (f, "                    vmlaq_f32 (vdupq_n_f32 (1.f), x,\n");
      fprintf (f,
               "                               jbm_4xf32_polynomial_%u (x, p + %u)));\n",
               i - j - 1, j + 1);
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat32m1_t\n");
      fprintf (f,
               "jbm_nxf32_rational_%u_%u (const vfloat32m1_t x, ///< vfloat32m1_t vector.\n",
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
      fprintf (f, "    __riscv_vfdiv_vv_f32m1\n");
      fprintf (f, "    (jbm_nxf32_polynomial_%u (x, p, vl),\n", j);
      fprintf (f,
               "     __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,\n");
      fprintf (f,
               "                              jbm_nxf32_polynomial_%u (x, p + %u, vl), vl), vl);\n",
               i - j - 1, j + 1);
      break;
    case TYPE_SVE:
      fprintf (f, "static inline svfloat32_t\n");
      fprintf (f,
               "jbm_nxf32_rational_%u_%u (svbool_t pg, ///< predicate.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const svfloat32_t x, ///< svfloat32_t vector.\n");

      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f, "    svdiv_f32_x (pg, jbm_nxf32_polynomial_%u (pg, x, p),\n",
               j);
      fprintf (f,
               "                    svmla_f32_x (pg, svdup_n_f32 (1.f), x,\n");
      fprintf (f,
               "                                 jbm_nxf32_polynomial_%u (pg, x, p + %u)));\n",
               i - j - 1, j + 1);
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
               "jbm_4xf32_rational_%u_%u (const __m128 x, ///< __m128 vector.\n",
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
      fprintf (f, "  return _mm_div_ps (jbm_4xf32_polynomial_%u (x, p),\n",
               i - 1);
      fprintf (f,
               "                     _mm_fmadd_ps (x, _mm_set1_ps (p[%u]), _mm_set1_ps (1.f)));\n",
               i);
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256\n");
      fprintf (f,
               "jbm_8xf32_rational_%u_%u (const __m256 x, ///< __m256 vector.\n",
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
      fprintf (f, "  return _mm256_div_ps (jbm_8xf32_polynomial_%u (x, p),\n",
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
               "jbm_16xf32_rational_%u_%u (const __m512 x, ///< __m512 vector.\n",
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
      fprintf (f, "  return _mm512_div_ps (jbm_16xf32_polynomial_%u (x, p),\n",
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
               "jbm_4xf32_rational_%u_%u (const float32x4_t x, ///< float32x4_t vector.\n",
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
      fprintf (f, "  return vdivq_f32 (jbm_4xf32_polynomial_%u (x, p),\n",
               i - 1);
      fprintf (f,
               "                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[%u])));\n",
               i);
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat32m1_t\n");
      fprintf (f,
               "jbm_nxf32_rational_%u_%u (const vfloat32m1_t x, ///< vfloat32m1_t vector.\n",
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
      fprintf (f, "    __riscv_vfdiv_vv_f32m1\n");
      fprintf (f, "    (jbm_nxf32_polynomial_%u (x, p, vl),\n", i - 1);
      fprintf (f,
               "     __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[%u], x, vl),\n",
               i);
      fprintf (f, "     vl);\n");
      break;
    case TYPE_SVE:
      fprintf (f, "static inline svfloat32_t\n");
      fprintf (f,
               "jbm_nxf32_rational_%u_%u (svbool_t pg, ///< predicate.\n",
               i, i - 1);
      if (i > 9)
        {
          fprintf (f, " ");
          if (i > 10)
            fprintf (f, " ");
        }
      fprintf (f,
               "                        const svfloat32_t x, ///< svfloat32_t vector.\n");
      if (i > 9)
        {
          fprintf (f, " ");
          if (i > 10)
            fprintf (f, " ");
        }
      fprintf (f,
               "                        const float *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f, "    svdiv_f32_x (pg, jbm_nxf32_polynomial_%u (pg, x, p),\n",
               i - 1);
      fprintf (f,
               "                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[%u]));\n",
               i);
      break;
    }
  fprintf (f, "}\n\n");
}

void
print_comment_pol_d (FILE *f, const unsigned int i, const unsigned int type)
{
  const char *ch[5] = { "th", "st", "nd", "rd", "th" };
  const char *t[TYPE_NONE] = { "__m128d", "__m256d", "__m512d", "float64x2_t",
    "vfloat64m1_t", "svfloat64_t" "__m128d", "__m256d"
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
               "jbm_2xf64_polynomial_1 (const __m128d x, ///< __m128d vector.\n");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm_fmadd_pd (x, _mm_set1_pd (p[1]), _mm_set1_pd (p[0]));\n");
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256d\n");
      fprintf (f,
               "jbm_4xf64_polynomial_1 (const __m256d x, ///< __m256d vector.\n");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm256_fmadd_pd (x, _mm256_set1_pd (p[1]), _mm256_set1_pd (p[0]));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512d\n");
      fprintf (f,
               "jbm_8xf64_polynomial_1 (const __m512d x, ///< __m512d vector.\n");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm512_fmadd_pd (x, _mm512_set1_pd (p[1]), _mm512_set1_pd (p[0]));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float64x2_t\n");
      fprintf (f,
               "jbm_2xf64_polynomial_1 (const float64x2_t x, ///< float64x2_t vector.\n");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, vdupq_n_f64 (p[1]));\n");
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat64m1_t\n");
      fprintf (f,
               "jbm_nxf64_polynomial_1 (const vfloat64m1_t x, ///< vfloat64m1_t vector.\n");
      fprintf (f,
               "                        const double *p, ///< array of coefficients.\n");
      fprintf (f,
               "                        const size_t vl) ///< array size.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f,
               "    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), p[1], x, vl);\n");
      break;
    case TYPE_SVE:
      fprintf (f, "static inline svfloat64_t\n");
      fprintf (f, "jbm_nxf64_polynomial_1 (svbool_t pg, ///< predicate.\n");
      fprintf (f,
               "                        const svfloat64_t x, ///< svfloat64_t vector.\n");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return svmla_n_f64_x (pg, svdup_n_f64 (p[0]), x, p[1]);\n");
      break;
    case TYPE_LSX:
      fprintf (f, "static inline __m128d\n");
      fprintf (f,
               "jbm_4xf32_polynomial_1 (const __m128d x, ///< __m128d vector.\n");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f,
               "    __lsx_vfmadd_d (x, __lsx_vreplfr2vr_d (p[1]), __lsx_vreplfr2vr_d (p[0]));\n");
      break;
    case TYPE_LASX:
      fprintf (f, "static inline __m256d\n");
      fprintf (f,
               "jbm_8xf32_polynomial_1 (const __m256d x, ///< __m256d vector.\n");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f,
               "    __lasx_vfmadd_d (x, __lasx_xvreplfr2vr_d (p[1]),\n");
      fprintf (f, "                     __lasx_xvreplfr2vr_d (p[0]));\n");
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
               "jbm_2xf64_polynomial_%u (const __m128d x, ///< __m128d vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_%u (x, p + 1),\n",
               i - 1);
      fprintf (f, "                    _mm_set1_pd (p[0]));\n");
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256d\n");
      fprintf (f,
               "jbm_4xf64_polynomial_%u (const __m256d x, ///< __m256d vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_%u (x, p + 1),\n",
               i - 1);
      fprintf (f, "                       _mm256_set1_pd (p[0]));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512d\n");
      fprintf (f,
               "jbm_8xf64_polynomial_%u (const __m512d x, ///< __m512d vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_%u (x, p + 1),\n",
               i - 1);
      fprintf (f, "                       _mm512_set1_pd (p[0]));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float64x2_t\n");
      fprintf (f,
               "jbm_2xf64_polynomial_%u (const float64x2_t x, ///< float64x2_t vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f,
               "  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_%u (x, p + 1));\n",
               i - 1);
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat64m1_t\n");
      fprintf (f,
               "jbm_nxf64_polynomial_%u (const vfloat64m1_t x, ///< vfloat64m1_t vector.\n",
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
      fprintf (f,
               "    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,\n");
      fprintf (f,
               "                             jbm_nxf64_polynomial_%u (x, p + 1, vl), vl);\n",
               i - 1);
      break;
    case TYPE_SVE:
      fprintf (f, "static inline svfloat64_t\n");
      fprintf (f, "jbm_nxf64_polynomial_%u (svbool_t pg, ///< predicate.\n", i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const svfloat64_t x, ///< svfloat64_t vector.\n");
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,\n");
      fprintf (f,
               "                      jbm_nxf64_polynomial_%u (pg, x, p + 1));\n",
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
    "vfloat64m1_t", "svfloat64_t"
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
               "jbm_2xf64_rational_1_0 (const __m128d x, ///< __m128d vector.\n");
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
               "jbm_4xf64_rational_1_0 (const __m256d x, ///< __m256d vector.\n");
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
               "jbm_8xf64_rational_1_0 (const __m512d x, ///< __m512d vector.\n");
      fprintf (f,
               "                         const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm512_div_pd (_mm512_set1_pd (p[0]),\n");
      fprintf (f,
               "                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[1]), _mm512_set1_pd (1.)));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float64x2_t\n");
      fprintf (f,
               "jbm_2xf64_rational_1_0 (const float64x2_t x, ///< float64x2_t vector.\n");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return vdivq_f64 (vdupq_n_f64 (p[0]),\n");
      fprintf (f,
               "                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[1])));\n");
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat64m1_t\n");
      fprintf (f,
               "jbm_nxf64_rational_1_0 (const vfloat64m1_t x, ///< vfloat64m1_t vector.\n");
      fprintf (f,
               "                        const double *p, ///< array of coefficients.\n");
      fprintf (f,
               "                        const size_t vl) ///< array size.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f,
               "    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),\n");
      fprintf (f,
               "                            __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl),\n");
      fprintf (f,
               "                                                     p[1], x, vl));\n");
      break;
    case TYPE_SVE:
      fprintf (f, "static inline svfloat64_t\n");
      fprintf (f, "jbm_nxf64_rational_1_0 (svbool_t pg, ///< predicate.\n");
      fprintf (f,
               "                        const svfloat64_t x, ///< svfloat64_t vector.\n");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f, "    svdiv_f64_x (pg, svdup_n_f64 (p[0]),\n");
      fprintf (f,
               "                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[1]));\n");
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
               "jbm_2xf64_rational_%u_0 (const __m128d x, ///< __m128d vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f, "    _mm_div_pd (_mm_set1_pd (p[0]),\n");
      fprintf (f,
               "                _mm_fmadd_pd (x, jbm_2xf64_polynomial_%u (x, p + 1),\n",
               i - 1);
      fprintf (f, "                              _mm_set1_pd (1.)));\n");
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256d\n");
      fprintf (f,
               "jbm_4xf64_rational_%u_0 (const __m256d x, ///< __m256d vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm256_div_pd (_mm256_set1_pd (p[0]),\n");
      fprintf (f,
               "                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_%u (x, p + 1),\n",
               i - 1);
      fprintf (f,
               "                                         _mm256_set1_pd (1.)));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512d\n");
      fprintf (f,
               "jbm_8xf64_rational_%u_0 (const __m512d x, ///< __m512d vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                         const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f, "    _mm512_div_pd (_mm512_set1_pd (p[0]),\n");
      fprintf (f,
               "                   _mm512_fmadd_pd (x, jbm_8xf64_polynomial_%u (x, p + 1),\n",
               i - 1);
      fprintf (f,
               "                                    _mm512_set1_pd (1.)));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float64x2_t\n");
      fprintf (f,
               "jbm_2xf64_rational_%u_0 (const float64x2_t x, ///< float64x2_t vector.\n",
               i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return vdivq_f64 (vdupq_n_f64 (p[0]),\n");
      fprintf (f, "                    vmlaq_f64 (vdupq_n_f64 (1.), x,\n");
      fprintf (f,
               "                               jbm_2xf64_polynomial_%u (x, p + 1)));\n",
               i - 1);
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat64m1_t\n");
      fprintf (f,
               "jbm_nxf64_rational_%u_0 (const vfloat64m1_t x, ///< vfloat64m1_t vector.\n",
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
      fprintf (f, "    __riscv_vfdiv_vv_f64m1\n");
      fprintf (f, "    (__riscv_vfmv_v_f_f64m1 (p[0], vl),\n");
      fprintf (f,
               "     __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,\n");
      fprintf (f,
               "                              jbm_nxf64_polynomial_%u (x, p + 1, vl), vl), vl);\n",
               i - 1);
      break;
    case TYPE_SVE:
      fprintf (f, "static inline svfloat64_t\n");
      fprintf (f, "jbm_nxf64_rational_%u_0 (svbool_t pg, ///< predicate.\n", i);
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const svfloat64_t x, ///< svfloat64_t vector.\n");
      if (i > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f, "    svdiv_f64_x (pg, svdup_n_f64 (p[0]),\n");
      fprintf (f, "                 svmla_f64_x (pg, svdup_n_f64 (1.), x,\n");
      fprintf (f,
               "                              jbm_nxf64_polynomial_%u (pg, x, p + 1)));\n",
               i - 1);
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
               "jbm_2xf64_rational_%u_%u (const __m128d x, ///< __m128d vector.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm_div_pd (jbm_2xf64_polynomial_%u (x, p),\n", j);
      fprintf (f,
               "                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_%u (x, p + %u),\n",
               i - j - 1, j + 1);
      fprintf (f, "                                   _mm_set1_pd (1.)));\n");
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256d\n");
      fprintf (f,
               "jbm_4xf64_rational_%u_%u (const __m256d x, ///< __m256d vector.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm256_div_pd (jbm_4xf64_polynomial_%u (x, p),\n",
               j);
      fprintf (f,
               "                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_%u (x, p + %u),\n",
               i - j - 1, j + 1);
      fprintf (f,
               "                                         _mm256_set1_pd (1.)));\n");
      break;
    case TYPE_AVX512:
      fprintf (f, "static inline __m512d\n");
      fprintf (f,
               "jbm_8xf64_rational_%u_%u (const __m512d x, ///< __m512d vector.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return _mm512_div_pd (jbm_8xf64_polynomial_%u (x, p),\n",
               j);
      fprintf (f,
               "                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_%u (x, p + %u),\n",
               i - j - 1, j + 1);
      fprintf (f,
               "                                         _mm512_set1_pd (1.)));\n");
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "static inline float64x2_t\n");
      fprintf (f,
               "jbm_2xf64_rational_%u_%u (const float64x2_t x, ///< float64x2_t vector.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return vdivq_f64 (jbm_2xf64_polynomial_%u (x, p),\n", j);
      fprintf (f, "                    vmlaq_f64 (vdupq_n_f64 (1.), x,\n");
      fprintf (f,
               "                               jbm_2xf64_polynomial_%u (x, p + %u)));\n",
               i - j - 1, j + 1);
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat64m1_t\n");
      fprintf (f,
               "jbm_nxf64_rational_%u_%u (const vfloat64m1_t x, ///< vfloat64m1_t vector.\n",
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
      fprintf (f, "    __riscv_vfdiv_vv_f64m1\n");
      fprintf (f, "    (jbm_nxf64_polynomial_%u (x, p, vl),\n", j);
      fprintf (f,
               "     __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,\n");
      fprintf (f,
               "                              jbm_nxf64_polynomial_%u (x, p + %u, vl), vl), vl);\n",
               i - j - 1, j + 1);
      break;
    case TYPE_SVE:
      fprintf (f, "static inline svfloat64_t\n");
      fprintf (f,
               "jbm_nxf64_rational_%u_%u (svbool_t pg, ///< predicate.\n",
               i, j);
      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const svfloat64_t x, ///< svfloat64_t vector.\n");

      if (i > 9)
        fprintf (f, " ");
      if (j > 9)
        fprintf (f, " ");
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f, "    svdiv_f64_x (pg, jbm_nxf64_polynomial_%u (pg, x, p),\n",
               j);
      fprintf (f,
               "                    svmla_f64_x (pg, svdup_n_f64 (1.), x,\n");
      fprintf (f,
               "                                 jbm_nxf64_polynomial_%u (pg, x, p + %u)));\n",
               i - j - 1, j + 1);
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
               "jbm_2xf64_rational_%u_%u (const __m128d x, ///< __m128d vector.\n",
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
      fprintf (f, "  return _mm_div_pd (jbm_2xf64_polynomial_%u (x, p),\n",
               i - 1);
      fprintf (f,
               "                     _mm_fmadd_pd (x, _mm_set1_pd (p[%u]), _mm_set1_pd (1.)));\n",
               i);
      break;
    case TYPE_AVX:
      fprintf (f, "static inline __m256d\n");
      fprintf (f,
               "jbm_4xf64_rational_%u_%u (const __m256d x, ///< __m256d vector.\n",
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
      fprintf (f, "  return _mm256_div_pd (jbm_4xf64_polynomial_%u (x, p),\n",
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
               "jbm_8xf64_rational_%u_%u (const __m512d x, ///< __m512d vector.\n",
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
      fprintf (f, "  return _mm512_div_pd (jbm_8xf64_polynomial_%u (x, p),\n",
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
               "jbm_2xf64_rational_%u_%u (const float64x2_t x, ///< float64x2_t vector.\n",
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
      fprintf (f, "  return vdivq_f64 (jbm_2xf64_polynomial_%u (x, p),\n",
               i - 1);
      fprintf (f,
               "                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[%u])));\n",
               i);
      break;
    case TYPE_RISCV:
      fprintf (f, "static inline vfloat64m1_t\n");
      fprintf (f,
               "jbm_nxf64_rational_%u_%u (const vfloat64m1_t x, ///< vfloat64m1_t vector.\n",
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
      fprintf (f, "    __riscv_vfdiv_vv_f64m1\n");
      fprintf (f, "    (jbm_nxf64_polynomial_%u (x, p, vl),\n", i - 1);
      fprintf (f,
               "     __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[%u], x, vl),\n",
               i);
      fprintf (f, "     vl);\n");
      break;
    case TYPE_SVE:
      fprintf (f, "static inline svfloat64_t\n");
      fprintf (f,
               "jbm_nxf64_rational_%u_%u (svbool_t pg, ///< predicate.\n",
               i, i - 1);
      if (i > 9)
        {
          fprintf (f, " ");
          if (i > 10)
            fprintf (f, " ");
        }
      fprintf (f,
               "                        const svfloat64_t x, ///< svfloat64_t vector.\n");
      if (i > 9)
        {
          fprintf (f, " ");
          if (i > 10)
            fprintf (f, " ");
        }
      fprintf (f,
               "                        const double *p) ///< array of coefficients.\n");
      fprintf (f, "{\n");
      fprintf (f, "  return\n");
      fprintf (f, "    svdiv_f64_x (pg, jbm_nxf64_polynomial_%u (pg, x, p),\n",
               i - 1);
      fprintf (f,
               "                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[%u]));\n",
               i);
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
      snprintf (buffer, 64, "r%u.h", k);
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
