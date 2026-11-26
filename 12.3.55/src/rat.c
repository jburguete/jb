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
  TYPE_LASX = 7,
  TYPE_NONE = 8
};

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
  TYPE_LASX = 7,
  TYPE_NONE = 8
};

static const char *
get_suffix (const unsigned int n)
{
  if (n % 100 >= 11 && n % 100 <= 13)
    return "th";
  switch (n % 10)
    {
    case 1:
      return "st";
    case 2:
      return "nd";
    case 3:
      return "rd";
    default:
      return "th";
    }
}

static const char *
get_type (const unsigned int arch, const unsigned int size)
{
  static const char *t32[TYPE_NONE] = {
    "__m128", "__m256", "__m512", "float32x4_t",
    "vfloat32m1_t", "svfloat32_t", "__m128", "__m256"
  };
  static const char *t64[TYPE_NONE] = {
    "__m128d", "__m256d", "__m512d", "float64x2_t",
    "vfloat64m1_t", "svfloat64_t", "__m128d", "__m256d"
  };
  return (size == 32) ? t32[arch] : t64[arch];
}

static const char *
get_prefix (const unsigned int arch, const unsigned int size)
{
  static const char *p32[TYPE_NONE] = {
    "jbm_4xf32_", "jbm_8xf32_", "jbm_16xf32_", "jbm_4xf32_",
    "jbm_nxf32_", "jbm_nxf32_", "jbm_4xf32_", "jbm_8xf32_"
  };
  static const char *p64[TYPE_NONE] = {
    "jbm_2xf64_", "jbm_4xf64_", "jbm_8xf64_", "jbm_2xf64_",
    "jbm_nxf64_", "jbm_nxf64_", "jbm_2xf64_", "jbm_4xf64_"
  };
  return (size == 32) ? p32[arch] : p64[arch];
}

static void
print_lsx_f32 (FILE *f, const char *val)
{
  fprintf (f, "((JBM4xF32){ .x = { %s, %s, %s, %s } }).x", val, val, val, val);
}

static void
print_lsx_f64 (FILE *f, const char *val)
{
  fprintf (f, "((JBM2xF64){ .x = { %s, %s } }).x", val, val);
}

static void
print_lasx_f32 (FILE *f, const char *val)
{
  fprintf (f, "((JBM8xF32){ .x = { %s, %s, %s, %s, %s, %s, %s, %s } }).x",
           val, val, val, val, val, val, val, val);
}

static void
print_lasx_f64 (FILE *f, const char *val)
{
  fprintf (f, "((JBM4xF64){ .x = { %s, %s, %s, %s } }).x", val, val, val, val);
}

static void
print_lsx_set1 (FILE *f, const unsigned int size, const char *val)
{
  if (size == 32)
    print_lsx_f32 (f, val);
  else
    print_lsx_f64 (f, val);
}

static void
print_lasx_set1 (FILE *f, const unsigned int size, const char *val)
{
  if (size == 32)
    print_lasx_f32 (f, val);
  else
    print_lasx_f64 (f, val);
}

void
print_comment_pol (FILE *f, const unsigned int i, const unsigned int arch,
                   const unsigned int size)
{
  const char *t = get_type (arch, size);
  fprintf (f, "/**\n");
  fprintf (f, " * Function to calculate a %u%s order polynomial (%s).\n",
           i, get_suffix (i), t);
  fprintf (f, " *\n");
  fprintf (f, " * \\return %s vector of polynomial values.\n", t);
  fprintf (f, " */\n");
}

void
print_pol_1 (FILE *f, const unsigned int arch, const unsigned int size)
{
  const char *vt = get_type (arch, size);
  const char *pfx = get_prefix (arch, size);
  const char *st = (size == 32) ? "float" : "double";
  const char *sfx = (size == 32) ? "ps" : "pd";
  const int pad = (arch == TYPE_AVX512 && size == 32) ? 25 : 24;

  print_comment_pol (f, 1, arch, size);
  fprintf (f, "static inline %s\n", vt);

  if (arch == TYPE_SVE)
    {
      fprintf (f, "%spolynomial_1 (svbool_t pg, ///< predicate.\n", pfx);
      fprintf (f, "%*sconst %s x, ///< %s vector.\n", pad, "", vt, vt);
      fprintf (f, "%*sconst %s *p) ///< array of coefficients.\n", pad, "", st);
    }
  else
    {
      fprintf (f, "%spolynomial_1 (const %s x, ///< %s vector.\n", pfx, vt, vt);
      if (arch == TYPE_RISCV)
        {
          fprintf (f, "%*sconst %s *p, ///< array of coefficients.\n", pad, "",
                   st);
          fprintf (f, "%*sconst size_t vl) ///< array size.\n", pad, "");
        }
      else
        fprintf (f, "%*sconst %s *p) ///< array of coefficients.\n", pad, "",
                 st);
    }

  fprintf (f, "{\n");
  switch (arch)
    {
    case TYPE_SSE:
      fprintf (f,
               "  return _mm_fmadd_%s (x, _mm_set1_%s (p[1]), _mm_set1_%s (p[0]));\n",
               sfx, sfx, sfx);
      break;
    case TYPE_AVX:
      fprintf (f,
               "  return _mm256_fmadd_%s (x, _mm256_set1_%s (p[1]), _mm256_set1_%s (p[0]));\n",
               sfx, sfx, sfx);
      break;
    case TYPE_AVX512:
      fprintf (f,
               "  return _mm512_fmadd_%s (x, _mm512_set1_%s (p[1]), _mm512_set1_%s (p[0]));\n",
               sfx, sfx, sfx);
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "  return vmlaq_n_f%u (vdupq_n_f%u (p[0]), x, p[1]);\n",
               size, size);
      break;
    case TYPE_RISCV:
      fprintf (f, "  return\n");
      fprintf (f,
               "    __riscv_vfmacc_vf_f%um1 (__riscv_vfmv_v_f_f%um1 (p[0], vl), p[1], x, vl);\n",
               size, size);
      break;
    case TYPE_SVE:
      fprintf (f, "  return svmla_n_f%u_x (pg, svdup_n_f%u (p[0]), x, p[1]);\n",
               size, size);
      break;
    case TYPE_LSX:
      fprintf (f, "  return __lsx_vfmadd_%c (x, ", (size == 32) ? 's' : 'd');
      print_lsx_set1 (f, size, "p[1]");
      fprintf (f, ",\n                         ");
      print_lsx_set1 (f, size, "p[0]");
      fprintf (f, ");\n");
      break;
    case TYPE_LASX:
      fprintf (f, "  return __lasx_xvfmadd_%c (x, ", (size == 32) ? 's' : 'd');
      print_lasx_set1 (f, size, "p[1]");
      fprintf (f, ",\n                           ");
      print_lasx_set1 (f, size, "p[0]");
      fprintf (f, ");\n");
      break;
    }
  fprintf (f, "}\n\n");
}

void
print_pol_i (FILE *f, const unsigned int i, const unsigned int arch,
             const unsigned int size)
{
  const char *vt = get_type (arch, size);
  const char *pfx = get_prefix (arch, size);
  const char *st = (size == 32) ? "float" : "double";
  const char *sfx = (size == 32) ? "ps" : "pd";
  const int base_pad = (arch == TYPE_AVX512 && size == 32) ? 25 : 24;
  const int pad = base_pad + ((i > 9) ? 1 : 0);

  print_comment_pol (f, i, arch, size);
  fprintf (f, "static inline %s\n", vt);

  if (arch == TYPE_SVE)
    {
      fprintf (f, "%spolynomial_%u (svbool_t pg, ///< predicate.\n", pfx, i);
      fprintf (f, "%*sconst %s x, ///< %s vector.\n", pad, "", vt, vt);
      fprintf (f, "%*sconst %s *p) ///< array of coefficients.\n", pad, "", st);
    }
  else
    {
      fprintf (f, "%spolynomial_%u (const %s x, ///< %s vector.\n", pfx, i,
               vt, vt);
      if (arch == TYPE_RISCV)
        {
          fprintf (f, "%*sconst %s *p, ///< array of coefficients.\n", pad, "",
                   st);
          fprintf (f, "%*sconst size_t vl) ///< array size.\n", pad, "");
        }
      else
        fprintf (f, "%*sconst %s *p) ///< array of coefficients.\n", pad, "",
                 st);
    }

  fprintf (f, "{\n");
  switch (arch)
    {
    case TYPE_SSE:
      fprintf (f, "  return _mm_fmadd_%s (x, %spolynomial_%u (x, p + 1),\n",
               sfx, pfx, i - 1);
      fprintf (f, "                    _mm_set1_%s (p[0]));\n", sfx);
      break;
    case TYPE_AVX:
      fprintf (f, "  return _mm256_fmadd_%s (x, %spolynomial_%u (x, p + 1),\n",
               sfx, pfx, i - 1);
      fprintf (f, "                       _mm256_set1_%s (p[0]));\n", sfx);
      break;
    case TYPE_AVX512:
      fprintf (f, "  return _mm512_fmadd_%s (x, %spolynomial_%u (x, p + 1),\n",
               sfx, pfx, i - 1);
      fprintf (f, "                       _mm512_set1_%s (p[0]));\n", sfx);
      break;
    case TYPE_ARM_NEON:
      fprintf (f,
               "  return vmlaq_f%u (vdupq_n_f%u (p[0]), x, %spolynomial_%u (x, p + 1));\n",
               size, size, pfx, i - 1);
      break;
    case TYPE_RISCV:
      fprintf (f, "  return\n");
      fprintf (f,
               "    __riscv_vfmacc_vv_f%um1 (__riscv_vfmv_v_f_f%um1 (p[0], vl), x,\n",
               size, size);
      fprintf (f,
               "                             %spolynomial_%u (x, p + 1, vl), vl);\n",
               pfx, i - 1);
      break;
    case TYPE_SVE:
      fprintf (f, "  return svmla_f%u_x (pg, svdup_n_f%u (p[0]), x,\n",
               size, size);
      fprintf (f, "                      %spolynomial_%u (pg, x, p + 1));\n",
               pfx, i - 1);
      break;
    case TYPE_LSX:
      fprintf (f, "  return __lsx_vfmadd_%c (x, %spolynomial_%u (x, p + 1),\n",
               (size == 32) ? 's' : 'd', pfx, i - 1);
      fprintf (f, "                         ");
      print_lsx_set1 (f, size, "p[0]");
      fprintf (f, ");\n");
      break;
    case TYPE_LASX:
      fprintf (f,
               "  return __lasx_xvfmadd_%c (x, %spolynomial_%u (x, p + 1),\n",
               (size == 32) ? 's' : 'd', pfx, i - 1);
      fprintf (f, "                           ");
      print_lasx_set1 (f, size, "p[0]");
      fprintf (f, ");\n");
      break;
    }
  fprintf (f, "}\n\n");
}

void
print_comment_rat (FILE *f, const unsigned int i, const unsigned int j,
                   const unsigned int arch, const unsigned int size)
{
  const char *t = get_type (arch, size);
  fprintf (f, "/**\n");
  fprintf (f, " * Function to calculate a %u%s+%u%s order rational (%s).\n",
           i, get_suffix (i), j, get_suffix (j), t);
  fprintf (f, " *\n");
  fprintf (f, " * \\return %s vector of rational values.\n", t);
  fprintf (f, " */\n");
}

static void
print_rat_sig (FILE *f, const unsigned int i, const unsigned int j,
               const unsigned int arch, const unsigned int size)
{
  const char *vt = get_type (arch, size);
  const char *pfx = get_prefix (arch, size);
  const char *st = (size == 32) ? "float" : "double";
  const int base_pad = (arch == TYPE_AVX512 && size == 32) ? 25 : 24;
  const int pad = base_pad + ((i > 9) ? 1 : 0) + ((j > 9) ? 1 : 0);

  fprintf (f, "static inline %s\n", vt);
  if (arch == TYPE_SVE)
    {
      fprintf (f, "%srational_%u_%u (svbool_t pg, ///< predicate.\n", pfx, i,
               j);
      fprintf (f, "%*sconst %s x, ///< %s vector.\n", pad, "", vt, vt);
      fprintf (f, "%*sconst %s *p) ///< array of coefficients.\n", pad, "", st);
    }
  else
    {
      fprintf (f, "%srational_%u_%u (const %s x, ///< %s vector.\n", pfx, i, j,
               vt, vt);
      if (arch == TYPE_RISCV)
        {
          fprintf (f, "%*sconst %s *p, ///< array of coefficients.\n", pad, "",
                   st);
          fprintf (f, "%*sconst size_t vl) ///< array size.\n", pad, "");
        }
      else
        fprintf (f, "%*sconst %s *p) ///< array of coefficients.\n", pad, "",
                 st);
    }
  fprintf (f, "{\n");
}

void
print_rat_1_0 (FILE *f, const unsigned int arch, const unsigned int size)
{
  const char *sfx = (size == 32) ? "ps" : "pd";
  const char *one = (size == 32) ? "1.f" : "1.";
  const char fc = (size == 32) ? 's' : 'd';

  print_comment_rat (f, 0, 1, arch, size);
  print_rat_sig (f, 1, 0, arch, size);
  switch (arch)
    {
    case TYPE_SSE:
      fprintf (f, "  return _mm_div_%s (_mm_set1_%s (p[0]),\n", sfx, sfx);
      fprintf (f, "                     _mm_fmadd_%s (x, _mm_set1_%s (p[1]),\n",
               sfx, sfx);
      fprintf (f, "                                   _mm_set1_%s (%s)));\n",
               sfx, one);
      break;
    case TYPE_AVX:
      fprintf (f, "  return _mm256_div_%s (_mm256_set1_%s (p[0]),\n", sfx, sfx);
      fprintf (f,
               "                        _mm256_fmadd_%s (x, _mm256_set1_%s (p[1]),\n",
               sfx, sfx);
      fprintf (f,
               "                                         _mm256_set1_%s (%s)));\n",
               sfx, one);
      break;
    case TYPE_AVX512:
      fprintf (f, "  return _mm512_div_%s (_mm512_set1_%s (p[0]),\n", sfx, sfx);
      fprintf (f,
               "                        _mm512_fmadd_%s (x, _mm512_set1_%s (p[1]),\n",
               sfx, sfx);
      fprintf (f,
               "                                         _mm512_set1_%s (%s)));\n",
               sfx, one);
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "  return vdivq_f%u (vdupq_n_f%u (p[0]),\n", size, size);
      fprintf (f,
               "                    vmlaq_n_f%u (vdupq_n_f%u (%s), x, p[1]));\n",
               size, size, one);
      break;
    case TYPE_RISCV:
      fprintf (f, "  return\n");
      fprintf (f, "    __riscv_vfdiv_vv_f%um1\n", size);
      fprintf (f, "    (__riscv_vfmv_v_f_f%um1 (p[0], vl),\n", size);
      fprintf (f,
               "     __riscv_vfmacc_vf_f%um1 (__riscv_vfmv_v_f_f%um1 (%s, vl), p[1], x,\n",
               size, size, one);
      fprintf (f, "     vl));\n");
      break;
    case TYPE_SVE:
      fprintf (f, "  return\n");
      fprintf (f, "    svdiv_f%u_x (pg, svdup_n_f%u (p[0]),\n", size, size);
      fprintf (f,
               "                 svmla_n_f%u_x (pg, svdup_n_f%u (%s), x, p[1]));\n",
               size, size, one);
      break;
    case TYPE_LSX:
      fprintf (f, "  return __lsx_vfdiv_%c (", fc);
      print_lsx_set1 (f, size, "p[0]");
      fprintf (f, ",\n                        __lsx_vfmadd_%c (x, ", fc);
      print_lsx_set1 (f, size, "p[1]");
      fprintf (f, ",\n                                        ");
      print_lsx_set1 (f, size, one);
      fprintf (f, "));\n");
      break;
    case TYPE_LASX:
      fprintf (f, "  return __lasx_xvfdiv_%c (", fc);
      print_lasx_set1 (f, size, "p[0]");
      fprintf (f, ",\n                          __lasx_xvfmadd_%c (x, ", fc);
      print_lasx_set1 (f, size, "p[1]");
      fprintf (f, ",\n                                            ");
      print_lasx_set1 (f, size, one);
      fprintf (f, "));\n");
      break;
    }
  fprintf (f, "}\n\n");
}

void
print_rat_0 (FILE *f, const unsigned int i, const unsigned int arch,
             const unsigned int size)
{
  const char *pfx = get_prefix (arch, size);
  const char *sfx = (size == 32) ? "ps" : "pd";
  const char *one = (size == 32) ? "1.f" : "1.";
  const char fc = (size == 32) ? 's' : 'd';

  print_comment_rat (f, 0, i, arch, size);
  print_rat_sig (f, i, 0, arch, size);
  switch (arch)
    {
    case TYPE_SSE:
      fprintf (f, "  return _mm_div_%s (_mm_set1_%s (p[0]),\n", sfx, sfx);
      fprintf (f,
               "                     _mm_fmadd_%s (x, %spolynomial_%u (x, p + 1),\n",
               sfx, pfx, i - 1);
      fprintf (f, "                                   _mm_set1_%s (%s)));\n",
               sfx, one);
      break;
    case TYPE_AVX:
      fprintf (f, "  return _mm256_div_%s (_mm256_set1_%s (p[0]),\n", sfx, sfx);
      fprintf (f,
               "                        _mm256_fmadd_%s (x, %spolynomial_%u (x, p + 1),\n",
               sfx, pfx, i - 1);
      fprintf (f,
               "                                         _mm256_set1_%s (%s)));\n",
               sfx, one);
      break;
    case TYPE_AVX512:
      fprintf (f, "  return _mm512_div_%s (_mm512_set1_%s (p[0]),\n", sfx, sfx);
      fprintf (f,
               "                        _mm512_fmadd_%s (x, %spolynomial_%u (x, p + 1),\n",
               sfx, pfx, i - 1);
      fprintf (f,
               "                                         _mm512_set1_%s (%s)));\n",
               sfx, one);
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "  return vdivq_f%u (vdupq_n_f%u (p[0]),\n", size, size);
      fprintf (f, "                    vmlaq_f%u (vdupq_n_f%u (%s), x,\n",
               size, size, one);
      fprintf (f,
               "                               %spolynomial_%u (x, p + 1)));\n",
               pfx, i - 1);
      break;
    case TYPE_RISCV:
      fprintf (f, "  return\n");
      fprintf (f, "    __riscv_vfdiv_vv_f%um1\n", size);
      fprintf (f, "    (__riscv_vfmv_v_f_f%um1 (p[0], vl),\n", size);
      fprintf (f,
               "     __riscv_vfmacc_vv_f%um1 (__riscv_vfmv_v_f_f%um1 (%s, vl), x,\n",
               size, size, one);
      fprintf (f,
               "                              %spolynomial_%u (x, p + 1, vl), vl), vl);\n",
               pfx, i - 1);
      break;
    case TYPE_SVE:
      fprintf (f, "  return\n");
      fprintf (f, "    svdiv_f%u_x (pg, svdup_n_f%u (p[0]),\n", size, size);
      fprintf (f, "                 svmla_f%u_x (pg, svdup_n_f%u (%s), x,\n",
               size, size, one);
      fprintf (f,
               "                              %spolynomial_%u (pg, x, p + 1)));\n",
               pfx, i - 1);
      break;
    case TYPE_LSX:
      fprintf (f, "  return __lsx_vfdiv_%c (", fc);
      print_lsx_set1 (f, size, "p[0]");
      fprintf (f,
               ",\n                        __lsx_vfmadd_%c (x, %spolynomial_%u (x, p + 1),\n",
               fc, pfx, i - 1);
      fprintf (f, "                                        ");
      print_lsx_set1 (f, size, one);
      fprintf (f, "));\n");
      break;
    case TYPE_LASX:
      fprintf (f, "  return __lasx_xvfdiv_%c (", fc);
      print_lasx_set1 (f, size, "p[0]");
      fprintf (f,
               ",\n                          __lasx_xvfmadd_%c (x, %spolynomial_%u (x, p + 1),\n",
               fc, pfx, i - 1);
      fprintf (f, "                                            ");
      print_lasx_set1 (f, size, one);
      fprintf (f, "));\n");
      break;
    }
  fprintf (f, "}\n\n");
}

void
print_rat_i (FILE *f, const unsigned int i, const unsigned int j,
             const unsigned int arch, const unsigned int size)
{
  const char *pfx = get_prefix (arch, size);
  const char *sfx = (size == 32) ? "ps" : "pd";
  const char *one = (size == 32) ? "1.f" : "1.";
  const char fc = (size == 32) ? 's' : 'd';

  print_comment_rat (f, j, i - j, arch, size);
  print_rat_sig (f, i, j, arch, size);
  switch (arch)
    {
    case TYPE_SSE:
      fprintf (f, "  return _mm_div_%s (%spolynomial_%u (x, p),\n", sfx, pfx,
               j);
      fprintf (f,
               "                     _mm_fmadd_%s (x, %spolynomial_%u (x, p + %u),\n",
               sfx, pfx, i - j - 1, j + 1);
      fprintf (f, "                                   _mm_set1_%s (%s)));\n",
               sfx, one);
      break;
    case TYPE_AVX:
      fprintf (f, "  return _mm256_div_%s (%spolynomial_%u (x, p),\n", sfx, pfx,
               j);
      fprintf (f,
               "                        _mm256_fmadd_%s (x, %spolynomial_%u (x, p + %u),\n",
               sfx, pfx, i - j - 1, j + 1);
      fprintf (f,
               "                                         _mm256_set1_%s (%s)));\n",
               sfx, one);
      break;
    case TYPE_AVX512:
      fprintf (f, "  return _mm512_div_%s (%spolynomial_%u (x, p),\n", sfx, pfx,
               j);
      fprintf (f,
               "                        _mm512_fmadd_%s (x, %spolynomial_%u (x, p + %u),\n",
               sfx, pfx, i - j - 1, j + 1);
      fprintf (f,
               "                                         _mm512_set1_%s (%s)));\n",
               sfx, one);
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "  return vdivq_f%u (%spolynomial_%u (x, p),\n", size, pfx,
               j);
      fprintf (f, "                    vmlaq_f%u (vdupq_n_f%u (%s), x,\n", size,
               size, one);
      fprintf (f,
               "                               %spolynomial_%u (x, p + %u)));\n",
               pfx, i - j - 1, j + 1);
      break;
    case TYPE_RISCV:
      fprintf (f, "  return\n");
      fprintf (f, "    __riscv_vfdiv_vv_f%um1\n", size);
      fprintf (f, "    (%spolynomial_%u (x, p, vl),\n", pfx, j);
      fprintf (f,
               "     __riscv_vfmacc_vv_f%um1 (__riscv_vfmv_v_f_f%um1 (%s, vl), x,\n",
               size, size, one);
      fprintf (f,
               "                              %spolynomial_%u (x, p + %u, vl), vl), vl);\n",
               pfx, i - j - 1, j + 1);
      break;
    case TYPE_SVE:
      fprintf (f, "  return\n");
      fprintf (f, "    svdiv_f%u_x (pg, %spolynomial_%u (pg, x, p),\n", size,
               pfx, j);
      fprintf (f, "                 svmla_f%u_x (pg, svdup_n_f%u (%s), x,\n",
               size, size, one);
      fprintf (f,
               "                              %spolynomial_%u (pg, x, p + %u)));\n",
               pfx, i - j - 1, j + 1);
      break;
    case TYPE_LSX:
      fprintf (f, "  return __lsx_vfdiv_%c (%spolynomial_%u (x, p),\n", fc, pfx,
               j);
      fprintf (f,
               "                        __lsx_vfmadd_%c (x, %spolynomial_%u (x, p + %u),\n",
               fc, pfx, i - j - 1, j + 1);
      fprintf (f, "                                        ");
      print_lsx_set1 (f, size, one);
      fprintf (f, "));\n");
      break;
    case TYPE_LASX:
      fprintf (f, "  return __lasx_xvfdiv_%c (%spolynomial_%u (x, p),\n", fc,
               pfx, j);
      fprintf (f,
               "                          __lasx_xvfmadd_%c (x, %spolynomial_%u (x, p + %u),\n",
               fc, pfx, i - j - 1, j + 1);
      fprintf (f, "                                            ");
      print_lasx_set1 (f, size, one);
      fprintf (f, "));\n");
      break;
    }
  fprintf (f, "}\n\n");
}

void
print_rat_n (FILE *f, const unsigned int i, const unsigned int arch,
             const unsigned int size)
{
  const char *pfx = get_prefix (arch, size);
  const char *sfx = (size == 32) ? "ps" : "pd";
  const char *one = (size == 32) ? "1.f" : "1.";
  const char fc = (size == 32) ? 's' : 'd';
  char coef[16];

  snprintf (coef, sizeof (coef), "p[%u]", i);
  print_comment_rat (f, i - 1, 1, arch, size);
  print_rat_sig (f, i, i - 1, arch, size);
  switch (arch)
    {
    case TYPE_SSE:
      fprintf (f, "  return _mm_div_%s (%spolynomial_%u (x, p),\n", sfx, pfx,
               i - 1);
      fprintf (f,
               "                     _mm_fmadd_%s (x, _mm_set1_%s (p[%u]), _mm_set1_%s (%s)));\n",
               sfx, sfx, i, sfx, one);
      break;
    case TYPE_AVX:
      fprintf (f, "  return _mm256_div_%s (%spolynomial_%u (x, p),\n", sfx, pfx,
               i - 1);
      fprintf (f,
               "                        _mm256_fmadd_%s (x, _mm256_set1_%s (p[%u]),\n",
               sfx, sfx, i);
      fprintf (f,
               "                                         _mm256_set1_%s (%s)));\n",
               sfx, one);
      break;
    case TYPE_AVX512:
      fprintf (f, "  return _mm512_div_%s (%spolynomial_%u (x, p),\n", sfx, pfx,
               i - 1);
      fprintf (f,
               "                        _mm512_fmadd_%s (x, _mm512_set1_%s (p[%u]),\n",
               sfx, sfx, i);
      fprintf (f,
               "                                         _mm512_set1_%s (%s)));\n",
               sfx, one);
      break;
    case TYPE_ARM_NEON:
      fprintf (f, "  return vdivq_f%u (%spolynomial_%u (x, p),\n", size, pfx,
               i - 1);
      fprintf (f,
               "                    vmlaq_n_f%u (vdupq_n_f%u (%s), x, p[%u]));\n",
               size, size, one, i);
      break;
    case TYPE_RISCV:
      fprintf (f, "  return\n");
      fprintf (f, "    __riscv_vfdiv_vv_f%um1\n", size);
      fprintf (f, "    (%spolynomial_%u (x, p, vl),\n", pfx, i - 1);
      fprintf (f,
               "     __riscv_vfmacc_vf_f%um1 (__riscv_vfmv_v_f_f%um1 (%s, vl), p[%u], x, vl),\n",
               size, size, one, i);
      fprintf (f, "     vl);\n");
      break;
    case TYPE_SVE:
      fprintf (f, "  return\n");
      fprintf (f, "    svdiv_f%u_x (pg, %spolynomial_%u (pg, x, p),\n", size,
               pfx, i - 1);
      fprintf (f,
               "                 svmla_n_f%u_x (pg, svdup_n_f%u (%s), x, p[%u]));\n",
               size, size, one, i);
      break;
    case TYPE_LSX:
      fprintf (f, "  return __lsx_vfdiv_%c (%spolynomial_%u (x, p),\n", fc, pfx,
               i - 1);
      fprintf (f, "                        __lsx_vfmadd_%c (x, ", fc);
      print_lsx_set1 (f, size, coef);
      fprintf (f, ",\n                                        ");
      print_lsx_set1 (f, size, one);
      fprintf (f, "));\n");
      break;
    case TYPE_LASX:
      fprintf (f, "  return __lasx_xvfdiv_%c (%spolynomial_%u (x, p),\n", fc,
               pfx, i - 1);
      fprintf (f, "                          __lasx_xvfmadd_%c (x, ", fc);
      print_lasx_set1 (f, size, coef);
      fprintf (f, ",\n                                            ");
      print_lasx_set1 (f, size, one);
      fprintf (f, "));\n");
      break;
    }
  fprintf (f, "}\n\n");
}

int
main (void)
{
  const unsigned int sizes[2] = { 32, 64 };
  char buffer[64];
  FILE *f;
  unsigned int i, j, k, l, s;
  for (k = 0; k < TYPE_NONE; ++k)
    {
      snprintf (buffer, sizeof (buffer), "r%u.h", k);
      f = fopen (buffer, "w");
      for (l = 0; l < 2; ++l)
        {
          s = sizes[l];
          print_pol_1 (f, k, s);
          for (i = 2; i < 30; ++i)
            print_pol_i (f, i, k, s);
          print_rat_1_0 (f, k, s);
          for (i = 2; i < 30; ++i)
            {
              print_rat_0 (f, i, k, s);
              for (j = 1; j < i - 1; ++j)
                print_rat_i (f, i, j, k, s);
              print_rat_n (f, i, k, s);
            }
        }
      fclose (f);
    }
  return 0;
}
