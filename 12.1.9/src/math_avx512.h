/* JB - A library with useful mathematical, XML, JSON, GTK and OpenGL functions.
 *
 * Copyright 2005-2026, Javier Burguete Tolosa.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY Javier Burguete Tolosa ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL Javier Burguete Tolosa OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file math_avx512.h
 * \brief Header file with useful mathematical functions for __m512.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2026, Javier Burguete Tolosa.
 */
#ifndef JB_MATH_AVX512__H
#define JB_MATH_AVX512__H 1

#include "math_f32.h"
#include "math_f64.h"

/**
 * union to work with bits in 8 packed float numbers.
 */
typedef union
{
  __m512 x;                     ///< floating point.
  __m512i i;                    ///< bits.
} JBM16xF32;

/**
 * union to work with bits in 2 packed double numbers.
 */
typedef union
{
  __m512d x;                    ///< floating point.
  __m512i i;                    ///< bits.
} JBM8xF64;

// float constants

#define JBM_16XF32_BIAS _mm512_set1_epi32 (JBM_F32_BIAS)
///< bias for floats.
#define JBM_16XF32_BITS_1 _mm512_set1_epi32 (JBM_F32_BITS_1)
///< 1 bits for floats.
#define JBM_16XF32_BITS_EXPONENT _mm512_set1_epi32 (JBM_F32_BITS_EXPONENT)
///< exponent bits for floats.
#define JBM_16XF32_BITS_MANTISSA _mm512_set1_epi32 (JBM_F32_BITS_MANTISSA)
///< mantissa bits for floats.
#define JBM_16XF32_BITS_SIGN _mm512_set1_epi32 (JBM_F32_BITS_SIGN)
///< sign bits for floats.
#define JBM_16XF32_CBRT2 _mm512_set1_ps (JBM_F32_CBRT2)
///< cbrt(2) for floats.
#define JBM_16XF32_CBRT4 _mm512_set1_ps (JBM_F32_CBRT4)
///< cbrt(4) for floats.

// double constants

#define JBM_8xF64_BIAS _mm512_set1_epi64 (JBM_F64_BIAS)
///< bias for doubles.
#define JBM_8xF64_BITS_1 _mm512_set1_epi64 (JBM_F64_BITS_1)
///< 1 bits for doubles.
#define JBM_8xF64_BITS_EXPONENT _mm512_set1_epi64 (JBM_F64_BITS_EXPONENT)
///< exponent bits for doubles.
#define JBM_8xF64_BITS_MANTISSA _mm512_set1_epi64 (JBM_F64_BITS_MANTISSA)
///< mantissa bits for doubles.
#define JBM_8xF64_BITS_SIGN _mm512_set1_epi64 (JBM_F64_BITS_SIGN)
///< sign bits for doubles.
#define JBM_8xF64_CBRT2 _mm512_set1_pd (JBM_F64_CBRT2)
///< cbrt(2) for doubles.
#define JBM_8xF64_CBRT4 _mm512_set1_pd (JBM_F64_CBRT4)
///< cbrt(4) for doubles.

///> macro to automatize operations on one array.
#define JBM_ARRAY_OP(xr, xd, n, type, load512, load256, load128, store512, \
                     store256, store128, op512, op256, op128, op) \
  const unsigned int prefetch = sizeof (type) == 4 ? 256 : 64; \
  unsigned int i, j; \
  if (n > prefetch + 256 / sizeof (type)) \
    for (i = 0, \
         j = (n - prefetch - 256 / sizeof (type)) >> (4 + 8 / sizeof (type)); \
	 j > 0; --j) \
      { \
        _mm_prefetch((const char *) (xd + i + prefetch), _MM_HINT_T0); \
        store512 (xr + i, op512 (load512 (xd + i))); \
        i += 64 / sizeof (type); \
        store512 (xr + i, op512 (load512 (xd + i))); \
        i += 64 / sizeof (type); \
        store512 (xr + i, op512 (load512 (xd + i))); \
        i += 64 / sizeof (type); \
        store512 (xr + i, op512 (load512 (xd + i))); \
        i += 64 / sizeof (type); \
      } \
  for (j = (n - i) >> (4 + 8 / sizeof (type)); j > 0; --j) \
    { \
      store512 (xr + i, op512 (load512 (xd + i))); \
      i += 64 / sizeof (type); \
      store512 (xr + i, op512 (load512 (xd + i))); \
      i += 64 / sizeof (type); \
      store512 (xr + i, op512 (load512 (xd + i))); \
      i += 64 / sizeof (type); \
      store512 (xr + i, op512 (load512 (xd + i))); \
      i += 64 / sizeof (type); \
    } \
  for (j = (n - i) >> (2 + 8 / sizeof (type)); j > 0; \
       --j, i += 64 / sizeof (type)) \
    store512 (xr + i, op512 (load512 (xd + i))); \
  for (j = (n - i) >> (1 + 8 / sizeof (type)); j > 0; \
       --j, i += 32 / sizeof (type)) \
    store256 (xr + i, op256 (load256 (xd + i))); \
  for (j = (n - i) >> (8 / sizeof (type)); j > 0; \
       --j, i += 16 / sizeof (type)) \
    store128 (xr + i, op128 (load128 (xd + i))); \
  for (; i < n; ++i) \
    xr[i] = op (xd[i]);

///> macro to automatize operations on one array and one number.
#define JBM_ARRAY_OP1(xr, x1, x2, n, type512, type256, type128, type, load512, \
                      load256, load128, store512, store256, store128, set512, \
		      set256, set128, op512, op256, op128, op) \
  const type512 x512 = set512 (x2); \
  const type256 x256 = set256 (x2); \
  const type128 x128 = set128 (x2); \
  const unsigned int prefetch = sizeof (type) == 4 ? 256 : 64; \
  unsigned int i, j; \
  if (n > prefetch + 256 / sizeof (type)) \
    for (i = 0, \
         j = (n - prefetch - 256 / sizeof (type)) >> (4 + 8 / sizeof (type)); \
	 j > 0; --j) \
      { \
        _mm_prefetch((const char *) (x1 + i + prefetch), _MM_HINT_T0); \
        store512 (xr + i, op512 (load512 (x1 + i), x512)); \
        i += 64 / sizeof (type); \
        store512 (xr + i, op512 (load512 (x1 + i), x512)); \
        i += 64 / sizeof (type); \
        store512 (xr + i, op512 (load512 (x1 + i), x512)); \
        i += 64 / sizeof (type); \
        store512 (xr + i, op512 (load512 (x1 + i), x512)); \
        i += 64 / sizeof (type); \
    } \
  for (j = (n - i) >> (4 + 8 / sizeof (type)); j > 0; --j) \
    { \
      store512 (xr + i, op512 (load512 (x1 + i), x512)); \
      i += 64 / sizeof (type); \
      store512 (xr + i, op512 (load512 (x1 + i), x512)); \
      i += 64 / sizeof (type); \
      store512 (xr + i, op512 (load512 (x1 + i), x512)); \
      i += 64 / sizeof (type); \
      store512 (xr + i, op512 (load512 (x1 + i), x512)); \
      i += 64 / sizeof (type); \
    } \
  for (j = (n - i) >> (2 + 8 / sizeof (type)); j > 0; \
       --j, i += 64 / sizeof (type)) \
    store512 (xr + i, op512 (load512 (x1 + i), x512)); \
  for (j = (n - i) >> (1 + 8 / sizeof (type)); j > 0; \
       --j, i += 32 / sizeof (type)) \
    store256 (xr + i, op256 (load256 (x1 + i), x256)); \
  for (j = (n - i) >> (8 / sizeof (type)); j > 0; \
       --j, i += 16 / sizeof (type)) \
    store128 (xr + i, op128 (load128 (x1 + i), x128)); \
  for (; i < n; ++i) \
    xr[i] = op (x1[i], x2);

///> macro to automatize operations on two arrays.
#define JBM_ARRAY_OP2(xr, x1, x2, n, type, load512, load256, load128, \
                      store512, store256, store128, op512, op256, op128, op) \
  const unsigned int prefetch = sizeof (type) == 4 ? 128 : 32; \
  unsigned int i, j; \
  if (n > prefetch + 256 / sizeof (type)) \
    for (i = 0, \
         j = (n - prefetch - 256 / sizeof (type)) >> (4 + 8 / sizeof (type)); \
	 j > 0; --j) \
      { \
        _mm_prefetch((const char *) (x1 + i + prefetch), _MM_HINT_T0); \
        _mm_prefetch((const char *) (x2 + i + prefetch), _MM_HINT_T0); \
        store512 (xr + i, op512 (load512 (x1 + i), load512 (x2 + i))); \
        i += 64 / sizeof (type); \
        store512 (xr + i, op512 (load512 (x1 + i), load512 (x2 + i))); \
        i += 64 / sizeof (type); \
        store512 (xr + i, op512 (load512 (x1 + i), load512 (x2 + i))); \
        i += 64 / sizeof (type); \
        store512 (xr + i, op512 (load512 (x1 + i), load512 (x2 + i))); \
        i += 64 / sizeof (type); \
      } \
  for (j = (n - i) >> (4 + 8 / sizeof (type)); j > 0; --j) \
    { \
      store512 (xr + i, op512 (load512 (x1 + i), load512 (x2 + i))); \
      i += 64 / sizeof (type); \
      store512 (xr + i, op512 (load512 (x1 + i), load512 (x2 + i))); \
      i += 64 / sizeof (type); \
      store512 (xr + i, op512 (load512 (x1 + i), load512 (x2 + i))); \
      i += 64 / sizeof (type); \
      store512 (xr + i, op512 (load512 (x1 + i), load512 (x2 + i))); \
      i += 64 / sizeof (type); \
    } \
  for (j = (n - i) >> (2 + 8 / sizeof (type)); j > 0; \
       --j, i += 64 / sizeof (type)) \
    store512 (xr + i, op512 (load512 (x1 + i), load512 (x2 + i))); \
  for (j = (n - i) >> (1 + 8 / sizeof (type)); j > 0; \
       --j, i += 32 / sizeof (type)) \
    store256 (xr + i, op256 (load256 (x1 + i), load256 (x2 + i))); \
  for (j = (n - i) >> (8 / sizeof (type)); j > 0; \
       --j, i += 16 / sizeof (type)) \
    store128 (xr + i, op128 (load128 (x1 + i), load128 (x2 + i))); \
  for (; i < n; ++i) \
    xr[i] = op (x1[i], x2[i]);

///> macro to automatize reduction operations on arrays.
#define JBM_ARRAY_REDUCE_OP(x, n, type512, type256, type128, type, load512, \
                            load256, load128, op512, op256, op128, op, \
                            reduce512, reduce256, reduce128, initial_value) \
  type512 a512, b512, c512, d512; \
  type256 a256; \
  type128 a128; \
  type a = initial_value; \
  const unsigned int prefetch = sizeof (type) == 4 ? 256 : 64; \
  unsigned int i, j; \
  i = 0; \
  if (n > prefetch + 256 / sizeof (type)) \
    { \
      j = (n - prefetch - 256 / sizeof (type)) >> (4 + 8 / sizeof (type)); \
      if (j) \
        { \
          _mm_prefetch ((const char *) (x + prefetch), _MM_HINT_T0); \
          a512 = load512 (x + i); \
          i += 64 / sizeof (type); \
          b512 = load512 (x + i); \
          i += 64 / sizeof (type); \
          c512 = load512 (x + i); \
          i += 64 / sizeof (type); \
          d512 = load512 (x + i); \
          i += 64 / sizeof (type); \
          while (--j) \
            { \
              _mm_prefetch ((const char *) (x + i + prefetch), _MM_HINT_T0); \
              a512 = op512 (a512, load512 (x + i)); \
              i += 64 / sizeof (type); \
              b512 = op512 (b512, load512 (x + i)); \
              i += 64 / sizeof (type); \
              c512 = op512 (c512, load512 (x + i)); \
              i += 64 / sizeof (type); \
              d512 = op512 (d512, load512 (x + i)); \
              i += 64 / sizeof (type); \
            } \
          a512 = op512 (a512, b512); \
          c512 = op512 (c512, d512); \
          a = reduce512 (op512 (a512, c512)); \
        } \
    } \
  j = (n - i) >> (4 + 8 / sizeof (type)); \
  if (j) \
    { \
      a512 = load512 (x + i); \
      i += 64 / sizeof (type); \
      b512 = load512 (x + i); \
      i += 64 / sizeof (type); \
      c512 = load512 (x + i); \
      i += 64 / sizeof (type); \
      d512 = load512 (x + i); \
      i += 64 / sizeof (type); \
      while (--j) \
        { \
          a512 = op512 (a512, load512 (x + i)); \
          i += 64 / sizeof (type); \
          b512 = op512 (b512, load512 (x + i)); \
          i += 64 / sizeof (type); \
          c512 = op512 (c512, load512 (x + i)); \
          i += 64 / sizeof (type); \
          d512 = op512 (d512, load512 (x + i)); \
          i += 64 / sizeof (type); \
        } \
      a512 = op512 (a512, b512); \
      c512 = op512 (c512, d512); \
      a = op (a, reduce512 (op512 (a512, c512))); \
    } \
  j = (n - i) >> (2 + 8 / sizeof (type)); \
  if (j) \
    { \
      a512 = load512 (x + i); \
      i += 64 / sizeof (type); \
      while (--j) \
        { \
          a512 = op512 (a512, load512 (x + i)); \
          i += 64 / sizeof (type); \
        } \
      a = op (a, reduce512 (a512)); \
    } \
  j = (n - i) >> (1 + 8 / sizeof (type)); \
  if (j) \
    { \
      a256 = load256 (x + i); \
      i += 32 / sizeof (type); \
      while (--j) \
        { \
          a256 = op256 (a256, load256 (x + i)); \
          i += 32 / sizeof (type); \
        } \
      a = op (a, reduce256 (a256)); \
    } \
  j = (n - i) >> (8 / sizeof (type)); \
  if (j) \
    { \
      a128 = load128 (x + i); \
      i += 16 / sizeof (type); \
      while (--j) \
        { \
          a128 = op128 (a128, load128 (x + i)); \
          i += 16 / sizeof (type); \
        } \
      a = op (a, reduce128 (a128)); \
    } \
  while (i < n) \
    a = op (a, x[i++]); \
  return a;

///> macro to automatize dot products on arrays.
#define JBM_ARRAY_DOT(x1, x2, n, type512, type256, type128, type, load512, \
                      load256, load128, mul512, mul256, mul128, add512, \
                      add256, add128, ma512, ma256, ma128, reduce512, \
                      reduce256, reduce128) \
  type512 a512, b512, c512, d512; \
  type256 a256; \
  type128 a128; \
  type a = (type) 0.; \
  const unsigned int prefetch = sizeof (type) == 4 ? 128 : 32; \
  unsigned int i, j; \
  i = 0; \
  if (n > prefetch + 256 / sizeof (type)) \
    { \
      j = (n - prefetch - 256 / sizeof (type)) >> (4 + 8 / sizeof (type)); \
      if (j) \
        { \
          _mm_prefetch ((const char *) (x1 + prefetch), _MM_HINT_T0); \
          _mm_prefetch ((const char *) (x2 + prefetch), _MM_HINT_T0); \
          a512 = mul512 (load512 (x1 + i), load512 (x2 + i)); \
          i += 64 / sizeof (type); \
          b512 = mul512 (load512 (x1 + i), load512 (x2 + i)); \
          i += 64 / sizeof (type); \
          d512 = mul512 (load512 (x1 + i), load512 (x2 + i)); \
          i += 64 / sizeof (type); \
          d512 = mul512 (load512 (x1 + i), load512 (x2 + i)); \
          i += 64 / sizeof (type); \
          while (--j) \
            { \
              _mm_prefetch ((const char *) (x1 + i + prefetch), _MM_HINT_T0); \
              _mm_prefetch ((const char *) (x2 + i + prefetch), _MM_HINT_T0); \
              a512 = ma512 (load512 (x1 + i), load512 (x2 + i), a512); \
              i += 64 / sizeof (type); \
              b512 = ma512 (load512 (x1 + i), load512 (x2 + i), b512); \
              i += 64 / sizeof (type); \
              d512 = ma512 (load512 (x1 + i), load512 (x2 + i), c512); \
              i += 64 / sizeof (type); \
              d512 = ma512 (load512 (x1 + i), load512 (x2 + i), d512); \
              i += 64 / sizeof (type); \
            } \
          a512 = add512 (a512, b512); \
          c512 = add512 (c512, d512); \
          a = reduce512 (add512 (a512, c512)); \
        } \
    } \
  j = (n - i) >> (4 + 8 / sizeof (type)); \
  if (j) \
    { \
      a512 = mul512 (load512 (x1 + i), load512 (x2 + i)); \
      i += 64 / sizeof (type); \
      b512 = mul512 (load512 (x1 + i), load512 (x2 + i)); \
      i += 64 / sizeof (type); \
      d512 = mul512 (load512 (x1 + i), load512 (x2 + i)); \
      i += 64 / sizeof (type); \
      d512 = mul512 (load512 (x1 + i), load512 (x2 + i)); \
      i += 64 / sizeof (type); \
      while (--j) \
        { \
          a512 = ma512 (load512 (x1 + i), load512 (x2 + i), a512); \
          i += 64 / sizeof (type); \
          b512 = ma512 (load512 (x1 + i), load512 (x2 + i), b512); \
          i += 64 / sizeof (type); \
          d512 = ma512 (load512 (x1 + i), load512 (x2 + i), c512); \
          i += 64 / sizeof (type); \
          d512 = ma512 (load512 (x1 + i), load512 (x2 + i), d512); \
          i += 64 / sizeof (type); \
        } \
      a512 = add512 (a512, b512); \
      c512 = add512 (c512, d512); \
      a += reduce512 (add512 (a512, c512)); \
    } \
  j = (n - i) >> (2 + 8 / sizeof (type)); \
  if (j) \
    { \
      a512 = mul512 (load512 (x1 + i), load512 (x2 + i)); \
      i += 64 / sizeof (type); \
      while (--j) \
        { \
          a512 = ma512 (load512 (x1 + i), load512 (x2 + i), a512); \
          i += 64 / sizeof (type); \
        } \
      a += reduce512 (a512); \
    } \
  j = (n - i) >> (1 + 8 / sizeof (type)); \
  if (j) \
    { \
      a256 = mul256 (load256 (x1 + i), load256 (x2 + i)); \
      i += 32 / sizeof (type); \
      while (--j) \
        { \
          a256 = ma256 (load256 (x1 + i), load256 (x2 + i), a256); \
          i += 32 / sizeof (type); \
        } \
      a += reduce256 (a256); \
    } \
  j = (n - i) >> (8 / sizeof (type)); \
  if (j) \
    { \
      a128 = mul128 (load128 (x1 + i), load128 (x2 + i)); \
      i += 16 / sizeof (type); \
      while (--j) \
        { \
          a128 = ma128 (load128 (x1 + i), load128 (x2 + i), a128); \
          i += 16 / sizeof (type); \
        } \
      a += reduce128 (a128); \
    } \
  for (; i < n; ++i) \
    a += JBM_MUL (x1[i], x2[i]); \
  return a;

///> macro to automatize maxmin operations on arrays.
#define JBM_ARRAY_MAXMIN(x, n, type512, type256, type128, type, load512, \
                         load256, load128, max512, max256, max128, max, \
                         min512, min256, min128, min, redmax512, redmax256, \
                         redmax128, redmin512, redmin256, redmin128, mx, mn) \
  type512 x512, mxa512, mxb512, mna512, mnb512; \
  type256 x256, mx256, mn256; \
  type128 x128, mx128, mn128; \
  type mx = -INFINITY, mn = INFINITY; \
  const unsigned int prefetch = sizeof (type) == 4 ? 256 : 64; \
  unsigned int i, j; \
  i = 0; \
  if (n > prefetch + 128 / sizeof (type)) \
    { \
      j = (n - prefetch - 128 / sizeof (type)) >> (3 + 8 / sizeof (type)); \
      if (j) \
        { \
          _mm_prefetch ((const char *) (x + prefetch), _MM_HINT_T0); \
          mxa512 = mna512 = load512 (x + i); \
          i += 64 / sizeof (type); \
          mxb512 = mnb512 = load512 (x + i); \
          i += 64 / sizeof (type); \
          while (--j) \
            { \
              _mm_prefetch ((const char *) (x + i + prefetch), _MM_HINT_T0); \
              x512 = load512 (x + i); \
              mxa512 = max512 (mxa512, x512); \
              mna512 = min512 (mna512, x512); \
              i += 64 / sizeof (type); \
              x512 = load512 (x + i); \
              mxb512 = max512 (mxb512, x512); \
              mnb512 = min512 (mnb512, x512); \
              i += 64 / sizeof (type); \
            } \
          mx = redmax512 (max512 (mxa512, mxb512)); \
          mn = redmin512 (min512 (mna512, mnb512)); \
        } \
    } \
  j = (n - i) >> (3 + 8 / sizeof (type)); \
  if (j) \
    { \
      mxa512 = mna512 = load512 (x + i); \
      i += 64 / sizeof (type); \
      mxb512 = mnb512 = load512 (x + i); \
      i += 64 / sizeof (type); \
      while (--j) \
        { \
          x512 = load512 (x + i); \
          mxa512 = max512 (mxa512, x512); \
          mna512 = min512 (mna512, x512); \
          i += 64 / sizeof (type); \
          x512 = load512 (x + i); \
          mxb512 = max512 (mxb512, x512); \
          mnb512 = min512 (mnb512, x512); \
          i += 64 / sizeof (type); \
        } \
      mx = max (mx, redmax512 (max512 (mxa512, mxb512))); \
      mn = min (mn, redmin512 (min512 (mna512, mnb512))); \
    } \
  j = (n - i) >> (2 + 8 / sizeof (type)); \
  if (j) \
    { \
      mxa512 = mna512 = load512 (x + i); \
      i += 64 / sizeof (type); \
      while (--j) \
        { \
          x512 = load512 (x + i); \
          mxa512 = max512 (mxa512, x512); \
          mna512 = min512 (mna512, x512); \
          i += 64 / sizeof (type); \
        } \
      mx = max (mx, redmax512 (mxa512)); \
      mn = min (mn, redmin512 (mna512)); \
    } \
  j = (n - i) >> (1 + 8 / sizeof (type)); \
  if (j) \
    { \
      mx256 = mn256 = load256 (x + i); \
      i += 32 / sizeof (type); \
      while (--j) \
        { \
          x256 = load256 (x + i); \
          mx256 = max256 (mx256, x256); \
          mn256 = min256 (mn256, x256); \
          i += 32 / sizeof (type); \
        } \
      mx = max (mx, redmax256 (mx256)); \
      mn = min (mn, redmin256 (mn256)); \
    } \
  j = (n - i) >> (8 / sizeof (type)); \
  if (j) \
    { \
      mx128 = mn128 = load128 (x + i); \
      i += 32 / sizeof (type); \
      while (--j) \
        { \
          x128 = load128 (x + i); \
          mx128 = max128 (mx128, x128); \
          mn128 = min128 (mn128, x128); \
          i += 32 / sizeof (type); \
        } \
      mx = max (mx, redmax128 (mx128)); \
      mn = min (mn, redmin128 (mn128)); \
    } \
  for (; i < n; ++i) \
    mx = max (mx, x[i]), mn = min (mn, x[i]); \

// Debug functions

static inline void
print_m512b32 (FILE *file, const char *label, __m512i x)
{
  int y[16] JB_ALIGNED;
  unsigned int i;
  _mm512_store_epi32 (y, x);
  for (i = 0; i < 16; ++i)
    fprintf (file, "%s[%u]=%08x\n", label, i, y[i]);
}

static inline void
print_m512b64 (FILE *file, const char *label, __m512i x)
{
  long long int y[8] JB_ALIGNED;
  unsigned int i;
  _mm512_store_epi64 (y, x);
  for (i = 0; i < 8; ++i)
    fprintf (file, "%s[%u]=%016llx\n", label, i, y[i]);
}

static inline void
print_m512i32 (FILE *file, const char *label, __m512i x)
{
  int y[16] JB_ALIGNED;
  unsigned int i;
  _mm512_store_epi32 (y, x);
  for (i = 0; i < 16; ++i)
    fprintf (file, "%s[%u]=%d\n", label, i, y[i]);
}

static inline void
print_m512i64 (FILE *file, const char *label, __m512i x)
{
  long long int y[8] JB_ALIGNED;
  unsigned int i;
  _mm512_store_epi64 (y, x);
  for (i = 0; i < 8; ++i)
    fprintf (file, "%s[%u]=%llu\n", label, i, y[i]);
}

static inline void
print_m512 (FILE *file, const char *label, __m512 x)
{
  float y[16] JB_ALIGNED;
  unsigned int i;
  _mm512_store_ps (y, x);
  for (i = 0; i < 16; ++i)
    fprintf (file, "%s[%u]=%.8g\n", label, i, y[i]);
}

static inline void
print_m512d (FILE *file, const char *label, __m512d x)
{
  double y[8] JB_ALIGNED;
  unsigned int i;
  _mm512_store_pd (y, x);
  for (i = 0; i < 8; ++i)
    fprintf (file, "%s[%u]=%.17lg\n", label, i, y[i]);
}

/**
 * Function to calculate the additive reduction value of a __m512 vector.
 *
 * \return additive reduction (float).
 */
static inline float
jbm_16xf32_reduce_add (const __m512 x)  ///< __m512 vector.
{
  __m256 h, l;
  h = _mm512_extractf32x8_ps (x, 1);
  l = _mm512_castps512_ps256 (x);
  return jbm_8xf32_reduce_add (_mm256_add_ps (h, l));
}

/**
 * Function to calculate the maximum reduction value of a __m512 vector.
 *
 * \return maximum reduction (float).
 */
static inline float
jbm_16xf32_reduce_max (const __m512 x)  ///< __m512 vector.
{
  __m256 h, l;
  h = _mm512_extractf32x8_ps (x, 1);
  l = _mm512_castps512_ps256 (x);
  return jbm_8xf32_reduce_max (_mm256_max_ps (h, l));
}

/**
 * Function to calculate the minimum reduction value of a __m512 vector.
 *
 * \return minimum reduction (float).
 */
static inline float
jbm_16xf32_reduce_min (const __m512 x)  ///< __m512 vector.
{
  __m256 h, l;
  h = _mm512_extractf32x8_ps (x, 1);
  l = _mm512_castps512_ps256 (x);
  return jbm_8xf32_reduce_min (_mm256_min_ps (h, l));
}

/**
 * Function to calculate the maximum and minimum reduction value of a __m512
 * vector.
 */
static inline void
jbm_16xf32_reduce_maxmin (const __m512 x,       ///< __m512 vector.
                          float *max,   ///< pointer to the maximum value
                          float *min)   ///< pointer to the minimum value
{
  __m256 h, l;
  h = _mm512_extractf32x8_ps (x, 1);
  l = _mm512_castps512_ps256 (x);
  *max = jbm_8xf32_reduce_max (_mm256_max_ps (h, l));
  *min = jbm_8xf32_reduce_min (_mm256_min_ps (h, l));
}

/**
 * Function to calculate the additive inverse value of a __m512 vector.
 *
 * \return opposite value vector (__m512).
 */
static inline __m512
jbm_16xf32_opposite (const __m512 x)    ///< __m512 vector.
{
  JBM16xF32 y;
  y.i = JBM_16XF32_BITS_SIGN;
  return _mm512_xor_ps (x, y.x);
}

/**
 * Function to calculate the multiplicative inverse value of a __m512 vector.
 *
 * \return reciprocal value vector (__m512).
 */
static inline __m512
jbm_16xf32_reciprocal (const __m512 x)  ///< __m512 vector.
{
  return _mm512_rcp14_ps (x);
}

/**
 * Function to calculate the sign of a __m512 vector.
 *
 * \return sign vector (__m512).
 */
static inline __m512
jbm_16xf32_sign (const __m512 x)        ///< __m512 vector.
{
  JBM16xF32 y;
  y.x = x;
  y.i = _mm512_and_epi32 (y.i, JBM_16XF32_BITS_SIGN);
  y.i = _mm512_or_epi32 (y.i, JBM_16XF32_BITS_1);
  return y.x;
}

/**
 * Function to calculate the absolute value of a __m512 vector.
 *
 * \return absolute value vector (__m512).
 */
static inline __m512
jbm_16xf32_abs (const __m512 x) ///< __m512 vector.
{
  JBM16xF32 y;
  y.i = JBM_16XF32_BITS_SIGN;
  return _mm512_andnot_ps (y.x, x);
}

/**
 * Function to copy the sign of a __m512 vector to another __m512 vector.
 *
 * \return __m512 vector with magnitud of 1st vector and sign of 2nd vector.
 */
static inline __m512
jbm_16xf32_copysign (const __m512 x,
///< __m512 vector to preserve magnitude.
                     const __m512 y)    ///< __m512 vector to preserve sign.
{
  JBM16xF32 m;
  m.i = JBM_16XF32_BITS_SIGN;
  return _mm512_or_ps (jbm_16xf32_abs (x), _mm512_and_ps (y, m.x));
}

/**
 * Function to calculate the hypot function (__m512).
 *
 * \return function value vector (__m512).
 */
static inline __m512
jbm_16xf32_hypot (const __m512 x,       ///< 1st __m512 vector.
                  const __m512 y)       ///< 2nd __m512 vector.
{
  return _mm512_sqrt_ps (_mm512_fmadd_ps (x, x, _mm512_mul_ps (y, y)));
}

/**
 * Function to calculate the rest of a division (__m512).
 *
 * \return rest value vector (in [0,|divisor|) interval).
 */
static inline __m512
jbm_16xf32_mod (const __m512 x, ///< dividend (__m512).
                const __m512 d) ///< divisor (__m512).
{
  __m512 r;
  r = _mm512_floor_ps (_mm512_div_ps (x, d));
  return
    _mm512_mask_blend_ps
    (_mm512_cmp_ps_mask (jbm_16xf32_abs (r), _mm512_set1_ps (1.f / FLT_EPSILON),
                         _CMP_GT_OQ),
     _mm512_fnmadd_ps (r, d, x), _mm512_mul_ps (d, _mm512_set1_ps (0.5f)));
}

/**
 * Function to implement the standard frexp function (__m512).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline __m512
jbm_16xf32_frexp (const __m512 x,       ///< __m512 vector.
                  __m512i *e)   ///< pointer to the extracted exponents vector.
{
  const __m512i zi = _mm512_setzero_epi32 ();
  const __m512i bias = JBM_16XF32_BIAS;
  const __m512i exp_mask = JBM_16XF32_BITS_EXPONENT;
  const __m512i sign_mask = JBM_16XF32_BITS_SIGN;
  const __m512i mant_mask = JBM_16XF32_BITS_MANTISSA;
  JBM16xF32 y, z;
  __m512i exp;
  __mmask16 is_z, is_sub, is_nan, is_finite;
  // y=abs(x)
  y.x = jbm_16xf32_abs (x);
  // masks
  is_z = _mm512_cmpeq_epu32_mask (y.i, zi);
  is_nan = _mm512_cmpge_epu32_mask (y.i, exp_mask);
  is_finite = ~(is_z | is_nan);
  // extract exponent
  exp = _mm512_maskz_srli_epi32 (is_finite, y.i, 23);
  // subnormals
  is_sub = _mm512_cmpeq_epu32_mask (exp, zi) & is_finite;
  y.x = _mm512_mask_mul_ps (y.x, is_sub, y.x, _mm512_set1_ps (0x1p23f));
  exp
    = _mm512_mask_mov_epi32
    (exp, is_sub, _mm512_sub_epi32 (_mm512_srli_epi32 (y.i, 23),
                                    _mm512_set1_epi32 (23)));
  // exponent
  *e = _mm512_mask_sub_epi32 (zi, is_finite, exp, bias);
  // build mantissa in [0.5,1)
  z.x = x;
  y.i = _mm512_or_epi32 (_mm512_and_epi32 (z.i, sign_mask),
                         _mm512_or_epi32 (_mm512_set1_epi32 (JBM_F32_BIAS
                                                             << 23),
                                          _mm512_and_epi32 (y.i, mant_mask)));
  return _mm512_mask_mov_ps (x, is_finite, y.x);
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (__m512i).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_exp2n (__m512i e)    ///< exponent vector (__m512i).
{
  __m512 x;
  x = _mm512_mask_blend_ps
    (_mm512_cmpgt_epi32_mask (e, _mm512_set1_epi32 (-127)),
     _mm512_castsi512_ps
     (_mm512_sllv_epi32 (_mm512_set1_epi32 (1),
                         _mm512_add_epi32 (_mm512_set1_epi32 (149), e))),
     _mm512_castsi512_ps
     (_mm512_slli_epi32 (_mm512_add_epi32 (e, _mm512_set1_epi32 (127)), 23)));
  x = _mm512_mask_mov_ps (x, _mm512_cmpgt_epi32_mask (_mm512_set1_epi32 (-150),
                                                      e), _mm512_setzero_ps ());
  return
    _mm512_mask_mov_ps (x, _mm512_cmpgt_epi32_mask (e, _mm512_set1_epi32 (127)),
                        _mm512_set1_ps (INFINITY));
}

/**
 * Function to implement the standard ldexp function (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_ldexp (const __m512 x,       ///< __m512 vector.
                  __m512i e)    ///< exponent vector (__m512i).
{
  return _mm512_mul_ps (x, jbm_16xf32_exp2n (e));
}

/**
 * Function to check small __m512 vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline __mmask16
jbm_16xf32_small (const __m512 x)       ///< __m512d vector.
{
  return _mm512_cmp_ps_mask (jbm_16xf32_abs (x), _mm512_set1_ps (FLT_EPSILON),
                             _CMP_LT_OS);
}

/**
 * Function to calculate the __m512 vector with the components with lower
 * module in the [a, b] interval.
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin __m512 vector.
 */
static inline __m512
jbm_16xf32_modmin (const __m512 a,      ///< 1st __m512d vector.
                   const __m512 b)      ///< 2nd __m512d vector.
{
  const __m512 z = _mm512_setzero_ps ();
  __m512 aa, ab, y;
  ab = _mm512_mul_ps (a, b);
  y = _mm512_mask_mov_ps (z, _mm512_cmp_ps_mask (ab, z, _CMP_GT_OS), a);
  aa = jbm_16xf32_abs (y);
  ab = jbm_16xf32_abs (b);
  return _mm512_mask_mov_ps (y, _mm512_cmp_ps_mask (aa, ab, _CMP_GT_OS), b);
}

/**
 * Function to interchange 2 __m512 vectors.
 */
static inline void
jbm_change_16xf32 (__m512 *restrict a,  ///< 1st __m512 vector pointer.
                   __m512 *restrict b)  ///< 2nd __m512 vector pointer.
{
  __m512 c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the double of a __m512 vector.
 *
 * \return __m512 double.
 */
static inline __m512
jbm_16xf32_dbl (const __m512 x) ///< __m512d vector.
{
  return _mm512_add_ps (x, x);
}

/**
 * Function to calculate the square of the components of a __m512 vector.
 *
 * \return __m512 vector square.
 */
static inline __m512
jbm_16xf32_sqr (const __m512 x) ///< __m512 vector.
{
  return _mm512_mul_ps (x, x);
}

/**
 * Function to perform an extrapolation between 2 __m512 vectors of 2D points.
 *
 * \return __m512 vector of y-coordinates of the extrapolated points.
 */
static inline __m512
jbm_16xf32_extrapolate (const __m512 x,
                        ///< __m512 vector of x-coordinates of the extrapolated
                        ///< points.
                        const __m512 x1,
                        ///< __m512 vector of x-coordinates of the 1st points.
                        const __m512 x2,
                        ///< __m512 vector of x-coordinates of the 2nd points.
                        const __m512 y1,
                        ///< __m512 vector of y-coordinates of the 1st points.
                        const __m512 y2)
                     ///< __m512 vector of y-coordinates of the 2nd points.
{
  return _mm512_fmadd_ps (_mm512_sub_ps (x, x1),
                          _mm512_div_ps (_mm512_sub_ps (y2, y1),
                                         _mm512_sub_ps (x2, x1)), y1);
}

/**
 * Function to perform an interpolation between 2 __m512 vectors of 2D points.
 *
 * \return __m512 vector of y-coordinates of the interpolated points.
 */
static inline __m512
jbm_16xf32_interpolate (const __m512 x,
                        ///< __m512 vector of x-coordinates of the interpolated
                        ///< points.
                        const __m512 x1,
                        ///< __m512 vector of x-coordinates of the 1st points.
                        const __m512 x2,
                        ///< __m512 vector of x-coordinates of the 2nd points.
                        const __m512 y1,
                        ///< __m512 vector of y-coordinates of the 1st points.
                        const __m512 y2)
                     ///< __m512 vector of y-coordinates of the 2nd points.
{
  __m512 k;
  k = jbm_16xf32_extrapolate (x, x1, x2, y1, y2);
  k = _mm512_mask_mov_ps (y1, _mm512_cmp_ps_mask (x, x1, _CMP_GT_OS), k);
  return _mm512_mask_mov_ps (y2, _mm512_cmp_ps_mask (x, x2, _CMP_LT_OS), k);
}

/**
 * Function to calculate the length of a __m512 vector of 2D segments.
 *
 * \return __m512 vector of segment lengths.
 */
static inline __m512
jbm_16xf32_v2_length (const __m512 x1,
///< __m512 vector of x-coordinates of the 1st points defining the segment.
                      const __m512 y1,
///< __m512 vector of y-coordinates of the 1st points defining the segment.
                      const __m512 x2,
///< __m512 vector of x-coordinates of the 2nd points defining the segment.
                      const __m512 y2)
///< __m512 vector of y-coordinates of the 2nd points defining the segment.
{
  return jbm_16xf32_hypot (_mm512_sub_ps (x2, x1), _mm512_sub_ps (y2, y1));
}

/**
 * Function to calculate the length of a __m512 vector of 3D segments.
 *
 * \return __m512 vector of segment lengths.
 */
static inline __m512
jbm_16xf32_v3_length (const __m512 x1,
///< __m512 vector of x-coordinates of the 1st points defining the segments.
                      const __m512 y1,
///< __m512 vector of y-coordinates of the 1st points defining the segments.
                      const __m512 z1,
///< __m512 vector of z-coordinates of the 1st points defining the segments.
                      const __m512 x2,
///< __m512 vector of x-coordinates of the 2nd points defining the segments.
                      const __m512 y2,
///< __m512 vector of y-coordinates of the 2nd points defining the segments.
                      const __m512 z2)
///< __m512 vector of z-coordinates of the 2nd points defining the segments.
{
  __m512 dx, dy, dz;
  dx = jbm_16xf32_sqr (_mm512_sub_ps (x2, x1));
  dy = _mm512_sub_ps (y2, y1);
  dy = _mm512_fmadd_ps (dy, dy, dx);
  dz = _mm512_sub_ps (z2, z1);
  return _mm512_sqrt_ps (_mm512_fmadd_ps (dz, dz, dy));
}

/**
 * Function to calculate a 1st order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_1 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, _mm512_set1_ps (p[1]), _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 2nd order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_2 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 3rd order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_3 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 4th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_4 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 5th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_5 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 6th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_6 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 7th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_7 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 8th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_8 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 9th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_9 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 10th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_10 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 11th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_11 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_10 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 12th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_12 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_11 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 13th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_13 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_12 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 14th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_14 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_13 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 15th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_15 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_14 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 16th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_16 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_15 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 17th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_17 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_16 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 18th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_18 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_17 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 19th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_19 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_18 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 20th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_20 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_19 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 21th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_21 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_20 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 22th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_22 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_21 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 23th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_23 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_22 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 24th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_24 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_23 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 25th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_25 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_24 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 26th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_26 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_25 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 27th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_27 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_26 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 28th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_28 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_27 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 29th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_16xf32_polynomial_29 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_16xf32_polynomial_28 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 0th+1st order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_1_0 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[1]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_2_0 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+1st order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_2_1 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[2]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_3_0 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_3_1 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_3_2 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[3]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_4_0 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_4_1 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_4_2 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_4_3 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[4]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_5_0 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_5_1 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_5_2 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_5_3 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_5_4 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[5]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_6_0 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_6_1 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_6_2 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_6_3 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_6_4 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_6_5 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[6]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_7_0 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_7_1 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_7_2 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_7_3 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_7_4 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_7_5 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_7_6 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[7]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_8_0 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_8_1 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_8_2 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_8_3 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_8_4 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_8_5 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_8_6 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_8_7 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[8]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_9_0 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_9_1 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_9_2 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_9_3 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_9_4 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_9_5 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_9_6 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_9_7 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_9_8 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[9]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_10_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_10_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_10_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_10_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_10_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_10_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_10_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_10_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_10_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_10_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[10]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_11_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_10 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_11_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_11_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_11_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_11_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_11_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_11_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_11_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_11_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_11_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_11_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[11]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_12_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_11 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_12_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_10 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_12_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_12_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_12_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_12_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_12_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_12_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_12_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_12_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_12_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_12_11 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_11 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[12]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_13_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_12 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_13_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_11 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_13_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_10 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_13_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_13_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_13_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_13_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_13_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_13_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_13_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_13_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_13_11 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_11 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_13_12 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_12 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[13]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_14_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_13 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_14_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_12 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_14_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_11 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_14_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_10 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_14_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_14_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_14_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_14_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_14_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_14_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_14_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_14_11 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_11 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_14_12 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_12 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_14_13 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_13 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[14]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_15_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_14 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_15_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_13 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_15_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_12 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_15_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_11 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_15_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_10 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_15_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_15_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_15_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_15_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_15_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_15_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_15_11 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_11 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_15_12 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_12 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_15_13 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_13 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_15_14 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_14 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[15]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_16_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_15 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_16_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_14 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_16_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_13 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_16_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_12 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_16_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_11 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_16_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_10 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_16_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_16_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_16_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_16_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_16_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_16_11 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_11 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_16_12 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_12 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_16_13 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_13 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_16_14 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_14 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_16_15 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_15 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[16]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_17_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_16 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_17_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_15 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_17_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_14 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_17_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_13 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_17_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_12 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_17_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_11 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_17_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_10 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_17_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_17_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_17_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_17_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_17_11 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_11 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_17_12 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_12 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_17_13 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_13 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_17_14 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_14 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_17_15 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_15 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_17_16 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_16 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[17]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_18_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_17 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_18_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_16 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_18_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_15 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_18_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_14 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_18_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_13 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_18_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_12 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_18_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_11 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_18_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_10 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_18_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_18_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_18_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_18_11 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_11 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_18_12 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_12 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_18_13 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_13 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_18_14 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_14 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_18_15 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_15 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_18_16 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_16 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_18_17 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_17 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[18]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_18 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_17 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_16 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_15 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_14 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_13 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_12 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_11 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_10 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_11 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_11 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_12 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_12 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_13 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_13 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_14 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_14 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_15 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_15 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_16 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_16 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_17 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_17 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_19_18 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_18 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[19]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_19 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_18 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_17 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_16 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_15 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_14 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_13 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_12 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_11 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_10 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_11 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_11 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_12 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_12 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_13 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_13 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_14 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_14 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_15 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_15 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_16 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_16 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_17 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_17 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_18 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_18 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_20_19 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_19 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[20]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_20 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_19 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_18 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_17 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_16 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_15 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_14 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_13 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_12 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_11 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_10 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_11 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_11 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_12 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_12 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_13 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_13 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_14 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_14 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_15 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_15 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_16 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_16 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_17 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_17 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_18 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_18 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_19 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_19 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 20),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_21_20 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_20 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[21]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+22th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_21 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_20 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_19 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_18 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_17 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_16 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_15 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_14 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_13 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_12 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_11 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_11 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_11 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_10 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_12 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_12 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_13 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_13 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_14 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_14 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_15 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_15 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_16 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_16 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_17 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_17 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_18 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_18 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_19 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_19 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 20),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_20 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_20 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 21),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_22_21 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_21 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[22]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+23th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_22 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+22th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_21 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_20 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_19 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_18 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_17 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_16 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_15 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_14 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_13 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_12 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_11 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_11 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_11 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_12 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_12 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_10 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_13 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_13 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_14 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_14 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_15 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_15 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_16 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_16 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_17 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_17 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_18 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_18 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_19 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_19 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 20),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_20 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_20 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 21),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_21 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_21 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 22),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+22th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_23_22 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_22 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[23]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+24th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_23 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+23th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_22 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+22th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_21 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_20 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_19 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_18 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_17 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_16 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_15 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_14 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_13 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_11 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_11 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_12 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_12 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_12 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_11 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_13 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_13 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_10 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_14 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_14 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_15 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_15 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_16 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_16 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_17 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_17 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_18 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_18 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_19 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_19 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 20),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_20 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_20 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 21),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_21 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_21 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 22),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_22 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_22 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 23),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+23th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_24_23 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_23 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[24]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+25th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_24 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+24th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_23 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+23th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_22 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+22th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_21 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_20 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_19 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_18 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_17 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_16 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_15 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_14 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_11 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_11 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_13 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_12 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_12 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_12 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_13 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_13 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_11 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_14 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_14 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_10 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_15 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_15 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_16 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_16 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_17 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_17 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_18 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_18 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_19 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_19 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 20),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_20 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_20 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 21),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_21 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_21 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 22),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_22 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_22 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 23),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_23 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_23 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 24),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+24th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_25_24 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_24 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[25]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+26th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_25 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+25th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_24 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+24th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_23 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+23th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_22 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+22th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_21 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_20 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_19 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_18 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_17 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_16 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_15 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_11 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_11 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_14 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_12 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_12 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_13 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_13 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_13 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_12 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_14 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_14 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_11 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_15 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_15 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_10 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_16 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_16 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_17 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_17 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_18 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_18 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_19 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_19 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 20),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_20 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_20 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 21),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_21 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_21 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 22),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_22 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_22 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 23),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_23 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_23 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 24),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_24 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_24 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 25),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+25th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_26_25 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_25 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[26]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+27th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_26 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+26th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_25 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+25th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_24 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+24th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_23 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+23th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_22 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+22th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_21 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_20 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_19 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_18 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_17 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_16 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_11 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_11 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_15 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_12 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_12 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_14 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_13 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_13 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_13 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_14 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_14 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_12 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_15 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_15 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_11 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_16 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_16 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_10 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_17 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_17 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_18 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_18 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_19 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_19 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 20),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_20 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_20 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 21),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_21 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_21 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 22),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_22 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_22 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 23),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_23 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_23 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 24),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_24 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_24 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 25),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 25th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_25 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_25 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 26),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+26th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_27_26 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_26 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[27]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+28th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_27 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+27th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_26 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+26th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_25 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+25th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_24 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+24th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_23 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+23th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_22 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+22th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_21 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_20 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_19 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_18 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_17 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_11 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_11 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_16 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_12 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_12 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_15 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_13 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_13 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_14 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_14 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_14 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_13 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_15 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_15 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_12 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_16 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_16 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_11 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_17 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_17 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_10 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_18 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_18 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_19 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_19 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 20),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_20 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_20 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 21),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_21 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_21 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 22),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_22 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_22 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 23),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_23 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_23 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 24),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_24 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_24 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 25),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 25th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_25 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_25 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 26),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 26th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_26 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_26 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 27),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+27th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_28_27 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_27 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[28]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+29th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_0 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_28 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+28th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_1 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_1 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_27 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+27th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_2 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_2 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_26 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+26th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_3 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_3 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_25 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+25th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_4 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_4 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_24 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+24th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_5 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_5 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_23 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+23th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_6 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_6 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_22 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+22th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_7 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_7 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_21 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_8 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_8 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_20 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_9 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_9 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_19 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_10 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_10 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_18 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_11 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_11 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_17 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_12 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_12 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_16 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_13 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_13 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_15 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_14 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_14 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_14 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_15 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_15 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_13 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_16 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_16 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_12 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_17 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_17 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_11 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_18 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_18 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_16xf32_polynomial_10 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_19 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_19 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_9 (x, p + 20),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_20 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_20 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_8 (x, p + 21),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_21 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_21 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_7 (x, p + 22),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_22 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_22 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_6 (x, p + 23),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_23 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_23 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_5 (x, p + 24),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_24 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_24 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_4 (x, p + 25),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 25th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_25 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_25 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_3 (x, p + 26),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 26th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_26 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_26 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_2 (x, p + 27),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 27th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_27 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_27 (x, p),
                        _mm512_fmadd_ps (x, jbm_16xf32_polynomial_1 (x, p + 28),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+28th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_16xf32_rational_29_28 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_16xf32_polynomial_28 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[29]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate the well conditionated function cbrt(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_cbrtwc (const __m512 x)
                   ///< __m512 vector \f$\in\left[\frac12,\;1\right]\f$.
{
  return jbm_16xf32_rational_5_3 (x, K_CBRTWC_F32);
}

/**
 * Function to calculate the function cbrt(x) using the jbm_16xf32_cbrtwc
 * function (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_cbrt (const __m512 x)        ///< __m512 vector.
{
  const __m512 cbrt2 = JBM_16XF32_CBRT2;
  const __m512 cbrt4 = JBM_16XF32_CBRT4;
  const __m256i v3 = _mm256_set1_epi16 (3);
  const __m512i v2 = _mm512_set1_epi16 (2);
  const __m512i v1 = _mm512_set1_epi16 (1);
  __m512 y;
  __m512i e32, r512;
  __m256i e, e3, r;
  y = jbm_16xf32_frexp (jbm_16xf32_abs (x), &e32);
  e = _mm512_cvtepi32_epi16 (e32);
  e3 = _mm256_mulhi_epi16 (e, _mm256_set1_epi16 (0x5556));
  r = _mm256_sub_epi16 (e, _mm256_mullo_epi16 (e3, v3));
  r512 = _mm512_castsi256_si512 (r);
  y = jbm_16xf32_ldexp (jbm_16xf32_cbrtwc (y), _mm512_cvtepi16_epi32 (e3));
  y = _mm512_mask_mul_ps (y, _mm512_test_epi16_mask (r512, v1), y, cbrt2);
  y = _mm512_mask_mul_ps (y, _mm512_test_epi16_mask (r512, v2), y, cbrt4);
  return jbm_16xf32_copysign (y, x);
}

/**
 * Function to calculate the well conditionated function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (__m512).
 *
 * \return function value.
 */
static inline __m512
jbm_16xf32_exp2wc (const __m512 x)
                  ///< __m512 vector \f$\in\left[\frac12,1\right]\f$.
{
  return jbm_16xf32_polynomial_5 (x, K_EXP2WC_F32);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_16xf32 and
 * jbm_16xf32_exp2n functions (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_exp2 (const __m512 x)        ///< __m512 vector.
{
  __m512 y, f;
  y = _mm512_floor_ps (x);
  f = _mm512_sub_ps (x, y);
  y = jbm_16xf32_exp2n (_mm512_cvtps_epi32 (y));
  return _mm512_mul_ps (y, jbm_16xf32_exp2wc (f));
}

/**
 * Function to calculate the function exp(x) using the jbm_16xf32_exp2 function
 * (__m512).
 *
 * \return function value.
 */
static inline __m512
jbm_16xf32_exp (const __m512 x) ///< __m512 vector.
{
  return jbm_16xf32_exp2 (_mm512_mul_ps (x, _mm512_set1_ps (M_LOG2Ef)));
}

/**
 * Function to calculate the function exp10(x) using the jbm_16xf32_exp2
 * function (__m512).
 *
 * \return function value.
 */
static inline __m512
jbm_16xf32_exp10 (const __m512 x)       ///< __m512 vector.
{
  return jbm_16xf32_exp2 (_mm512_mul_ps (x, _mm512_set1_ps (M_LN10f / M_LN2f)));
}

/**
 * Function to calculate the well conditionated function expm1(x) for
 * \f$x\in\left[-\log(2)/2,\log(2)/2\right]\f$ (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_expm1wc (const __m512 x)
///< __m512 vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  const float a1 = K_EXPM1WC_F32[0];
  const float b1 = K_EXPM1WC_F32[1];
  const float b2 = K_EXPM1WC_F32[2];
  const float b4 = K_EXPM1WC_F32[3];
  __m512 x2;
  x2 = jbm_16xf32_sqr (x);
  x2 = _mm512_fmadd_ps (x2, _mm512_set1_ps (b4), _mm512_set1_ps (b2));
  x2 = _mm512_fmadd_ps (x2, x, _mm512_set1_ps (b1));
  x2 = _mm512_fmadd_ps (x2, x, _mm512_set1_ps (1.f));
  return _mm512_mul_ps (x, _mm512_div_ps (_mm512_set1_ps (a1), x2));
}

/**
 * Function to calculate the function expm1(x) using the jbm_16xf32_expm1wc and
 * jbm_16xf32_exp functions (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_expm1 (const __m512 x)       ///< __m512 vector.
{
  return
    _mm512_mask_blend_ps (_mm512_cmp_ps_mask (jbm_16xf32_abs (x),
                                              _mm512_set1_ps (M_LN2f / 2.f),
                                              _CMP_LT_OS),
                          _mm512_sub_ps (jbm_16xf32_exp (x),
                                         _mm512_set1_ps (1.f)),
                          jbm_16xf32_expm1wc (x));
}

/**
 * Function to calculate the well conditionated function log2(x) for x in
 * \f$[\sqrt{0.5}-1,\sqrt{2}-1]\f$ (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_log2wc (const __m512 x)      ///< __m512 vector.
{
  return _mm512_mul_ps (x, jbm_16xf32_rational_5_2 (x, K_LOG2WC_F32));
}

/**
 * Function to calculate the function log2(x) using jbm_16xf32_log2wc and
 * jbm_16xf32_frexp (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_log2 (const __m512 x)        ///< __m512 vector.
{
  const __m512 z = _mm512_setzero_ps ();
  __m512 y;
  __m512i e;
  __mmask16 m;
  y = jbm_16xf32_frexp (x, &e);
  m = _mm512_cmplt_ps_mask (y, _mm512_set1_ps (M_SQRT1_2f));
  y = _mm512_add_ps (y, _mm512_maskz_mov_ps (m, y));
  e = _mm512_sub_epi32 (e, _mm512_maskz_set1_epi32 (m, 1));
  y = _mm512_add_ps (jbm_16xf32_log2wc (_mm512_sub_ps (y,
                                                       _mm512_set1_ps (1.f))),
                     _mm512_cvtepi32_ps (e));
  y = _mm512_mask_mov_ps (y, _mm512_cmpeq_ps_mask (x, z),
                          _mm512_set1_ps (-INFINITY));
  y = _mm512_mask_mov_ps (y, _mm512_cmplt_ps_mask (x, z), _mm512_set1_ps (NAN));
  return
    _mm512_mask_mov_ps (y, _mm512_cmp_ps_mask (x, x, _CMP_ORD_Q) ^ 0xffff, x);
}

/**
 * Function to calculate the function log(x) using jbm_16xf32_log2 (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_log (const __m512 x) ///< __m512 vector.
{
  return _mm512_mul_ps (jbm_16xf32_log2 (x), _mm512_set1_ps (M_LN2f));
}

/**
 * Function to calculate the function log10(x) using jbm_16xf32_log2.
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_log10 (const __m512 x)       ///< __m512 vector.
{
  return _mm512_mul_ps (jbm_16xf32_log2 (x), _mm512_set1_ps (M_LN2f / M_LN10f));
}

/**
 * Function to calculate the function x^e with e an integer number (__m512).
 *
 * \return function value (__m512) (__m512).
 */
static inline __m512
jbm_16xf32_pown (const __m512 x,        ///< __m512 vector.
                 const int e)   ///< exponent (int).
{
  __m512 f, xn;
  unsigned int i;
  f = _mm512_set1_ps (1.f);
  if (e < 0)
    xn = _mm512_div_ps (f, x);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_16xf32_sqr (xn))
    if (i & 1)
      f = _mm512_mul_ps (f, xn);
  return f;
}

/**
 * Function to calculate the function pow using the jbm_16xf32_exp2 and
 * jbm_16xf32_log2 functions (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_pow (const __m512 x, ///< __m512 vector.
                const __m512 e) ///< exponent (__m512 vector).
{
  return jbm_16xf32_exp2 (_mm512_mul_ps (e, jbm_16xf32_log2 (x)));
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] (__m512)
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_sinwc (const __m512 x)
                 ///< __m512 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return
    _mm512_mul_ps (x,
                   jbm_16xf32_polynomial_3 (jbm_16xf32_sqr (x), K_SINWC_F32));
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] (__m512):
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_coswc (const __m512 x)
                 ///< __m512 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return jbm_16xf32_polynomial_3 (jbm_16xf32_sqr (x), K_COSWC_F32);
}

/**
 * Function to calculate the well conditionated function tan(x) for x in
 * [-pi/4,pi/4].
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_tanwc (const __m512 x)
                  ///< __m512 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return _mm512_mul_ps (x, jbm_16xf32_rational_3_1 (jbm_16xf32_sqr (x),
                                                    K_TANWC_F32));
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_16xf32_sinwc approximation (__m512).
 */
static inline void
jbm_16xf32_sincoswc (const __m512 x,
                     ///< __m512 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                     __m512 *s, ///< pointer to the sin function value (__m512).
                     __m512 *c) ///< pointer to the cos function value (__m512).
{
  *s = jbm_16xf32_sinwc (x);
  *c = jbm_16xf32_coswc (x);
}

/**
 * Function to calculate reduction to \f$2\,\pi\f$ in trigonometric functions
 * (__m512).
 *
 * \return reduced vector (__m512).
 */
static inline __m512
jbm_16xf32_trig (const __m512 x,        ///< __m512 vector.
                 __m512i *q)    ///< quadrant (__m512i).
{
  __m512 y;
  y = _mm512_roundscale_ps (_mm512_mul_ps (x, _mm512_set1_ps (1.f / M_PI_2f)),
                            _MM_FROUND_TO_NEAREST_INT);
  *q = _mm512_cvtps_epi32 (y);
  return _mm512_fnmadd_ps (y, _mm512_set1_ps (M_PI_2f), x);
}

/**
 * Function to calculate the function sin(x) from jbm_16xf32_sinwc and
 * jbm_16xf32_coswc approximations (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_sin (const __m512 x) ///< __m512 vector.
{
  __m512 y, s, c;
  __m512i q;
  y = jbm_16xf32_trig (x, &q);
  jbm_16xf32_sincoswc (y, &s, &c);
  y = _mm512_mask_blend_ps (_mm512_test_epi32_mask (q, _mm512_set1_epi32 (1)),
                            s, c);
  return
    _mm512_mask_mov_ps (y, _mm512_test_epi32_mask (q, _mm512_set1_epi32 (2)),
                        jbm_16xf32_opposite (y));
}

/**
 * Function to calculate the function cos(x) from jbm_16xf32_sinwc and
 * jbm_16xf32_coswc approximations (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_cos (const __m512 x) ///< __m512 vector.
{
  const __m512i v1 = _mm512_set1_epi32 (1);
  __m512 y, s, c;
  __m512i q;
  y = jbm_16xf32_trig (x, &q);
  jbm_16xf32_sincoswc (y, &s, &c);
  y = _mm512_mask_blend_ps (_mm512_test_epi32_mask (q, v1), c, s);
  return
    _mm512_mask_mov_ps (y, _mm512_test_epi32_mask (_mm512_add_epi32 (q, v1),
                                                   _mm512_set1_epi32 (2)),
                        jbm_16xf32_opposite (y));
}

/**
 * Function to calculate the functions sin(x) and cos(x) from
 * jbm_16xf32_sinwc and jbm_16xf32_coswc approximations (__m512).
 */
static inline void
jbm_16xf32_sincos (const __m512 x,
                   ///< __m512 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                   __m512 *s,   ///< pointer to the sin function value (__m512).
                   __m512 *c)   ///< pointer to the cos function value (__m512).
{
  const __m512i v1 = _mm512_set1_epi32 (1);
  const __m512i v2 = _mm512_set1_epi32 (2);
  __m512 y, s1, c1, s2, c2;
  __m512i q;
  __mmask16 m;
  y = jbm_16xf32_trig (x, &q);
  jbm_16xf32_sincoswc (y, &s1, &c1);
  m = _mm512_test_epi32_mask (q, v1);
  s2 = _mm512_mask_blend_ps(m, s1, c1);
  c2 = _mm512_mask_blend_ps(m, c1, s1);
  *s = _mm512_mask_mov_ps (s2, _mm512_test_epi32_mask(q, v2),
                           jbm_16xf32_opposite (s2));
  *c = _mm512_mask_mov_ps (c2, _mm512_test_epi32_mask(_mm512_add_epi32(q, v1),
                                                      v2),
                           jbm_16xf32_opposite (c2));
}

/**
 * Function to calculate the function tan(x) from jbm_16xf32_tanwc function
 * (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_tan (const __m512 x) ///< __m512 vector.
{
  __m512 y;
  __m512i q;
  y = jbm_16xf32_tanwc (jbm_16xf32_trig (x, &q));
  return
    _mm512_mask_blend_ps (_mm512_test_epi32_mask (q, _mm512_set1_epi32 (1)), y,
                          _mm512_div_ps (_mm512_set1_ps (-1.f), y));
} 

/**
 * Function to calculate the well conditionated function atan(x) for x in [-1,1]
 * (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_atanwc (const __m512 x)
                   ///< __m512 vector \f$\in\left[-1,1\right]\f$.
{
  return
    _mm512_mul_ps (x,
                   jbm_16xf32_rational_4_2 (jbm_16xf32_sqr (x), K_ATANWC_F32));
}

/**
 * Function to calculate the function atan(x) using the jbm_16xf32_atanwc
 * function (__m512).
 *
 * \return function value (in [-pi/2,pi/2]) (__m512).
 */
static inline __m512
jbm_16xf32_atan (const __m512 x)        ///< __m512 vector.
{
  __m512 f, ax;
  __mmask16 m;
  ax = jbm_16xf32_abs (x);
  m = _mm512_cmp_ps_mask (ax, _mm512_set1_ps (1.f), _CMP_GT_OS);
  ax = _mm512_mask_mov_ps (ax, m, jbm_16xf32_reciprocal (ax));
  f = jbm_16xf32_atanwc (ax);
  f = _mm512_mask_mov_ps (f, m, _mm512_sub_ps (_mm512_set1_ps (M_PI_2f), f));
  return jbm_16xf32_copysign (f, x);
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_16xf32_atan
 * function (__m512).
 *
 * \return function value (in [-pi,pi]) (__m512).
 */
static inline __m512
jbm_16xf32_atan2 (const __m512 y,       ///< __m512 y component.
                  const __m512 x)       ///< __m512 x component.
{
  __m512 f, g;
  f = jbm_16xf32_atan (_mm512_div_ps (y, x));
  g = _mm512_add_ps (f, jbm_16xf32_copysign (_mm512_set1_ps (M_PIf), y));
  return
    _mm512_mask_mov_ps (f, _mm512_cmp_ps_mask (x, _mm512_setzero_ps (),
                                               _CMP_LT_OS), g);
}

/**
 * Function to calculate the function asin(x) using the jbm_16xf32_atan function
 * (__m512).
 *
 * \return function value (in [-pi/2,pi/2]).
 */
static inline __m512
jbm_16xf32_asin (const __m512 x)        ///< __m512 vector.
{
  return
    jbm_16xf32_atan (_mm512_div_ps
                     (x,
                      _mm512_sqrt_ps (_mm512_fnmadd_ps
                                      (x, x, _mm512_set1_ps (1.f)))));
}

/**
 * Function to calculate the function acos(x) using the jbm_16xf32_atan function
 * (__m512).
 *
 * \return function value (in [0,pi]) (__m512).
 */
static inline __m512
jbm_16xf32_acos (const __m512 x)        ///< __m512 vector.
{
  __m512 f;
  f =
    jbm_16xf32_atan (_mm512_div_ps
                     (_mm512_sqrt_ps
                      (_mm512_fnmadd_ps (x, x, _mm512_set1_ps (1.f))), x));
  return _mm512_mask_mov_ps (f, _mm512_cmp_ps_mask (x, _mm512_setzero_ps (),
                                                    _CMP_LT_OS),
                             _mm512_add_ps (f, _mm512_set1_ps (M_PIf)));
}

/**
 * Function to calculate the function sinh(x)
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_sinh (const __m512 x)        ///< __m512 number.
{
  __m512 f;
  f = jbm_16xf32_exp (x);
  return _mm512_mul_ps (_mm512_set1_ps (0.5f),
                        _mm512_sub_ps (f, jbm_16xf32_reciprocal (f)));
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_cosh (const __m512 x)        ///< __m512 number.
{
  __m512 f;
  f = jbm_16xf32_exp (x);
  return _mm512_mul_ps (_mm512_set1_ps (0.5f),
                        _mm512_add_ps (f, jbm_16xf32_reciprocal (f)));
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_tanh (const __m512 x)        ///< __m512 number.
{
  __m512 f, fi;
  f = jbm_16xf32_exp (x);
  fi = jbm_16xf32_reciprocal (f);
  f = _mm512_div_ps (_mm512_sub_ps (f, fi), _mm512_add_ps (f, fi));
  f = _mm512_mask_mov_ps
    (f, _mm512_cmp_ps_mask (x, _mm512_set1_ps (JBM_FLT_MAX_E_EXP), _CMP_GT_OS),
     _mm512_set1_ps (1.f));
  return
    _mm512_mask_mov_ps
    (f, _mm512_cmp_ps_mask (x, _mm512_set1_ps (-JBM_FLT_MAX_E_EXP), _CMP_LT_OS),
     _mm512_set1_ps (-1.f));
}

/**
 * Function to calculate the function asinh(x)
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_asinh (const __m512 x)       ///< __m512 number.
{
  return
    jbm_16xf32_log (_mm512_add_ps
                    (x,
                     _mm512_sqrt_ps (_mm512_fmadd_ps
                                     (x, x, _mm512_set1_ps (1.f)))));
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_acosh (const __m512 x)       ///< __m512 number.
{
  return
    jbm_16xf32_log (_mm512_add_ps
                    (x,
                     _mm512_sqrt_ps (_mm512_fmsub_ps
                                     (x, x, _mm512_set1_ps (1.f)))));
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_atanh (const __m512 x)       ///< __m512 number.
{
  const __m512 u = _mm512_set1_ps (1.f);
  return _mm512_mul_ps (_mm512_set1_ps (0.5f),
                        jbm_16xf32_log (_mm512_div_ps (_mm512_add_ps (u, x),
                                                       _mm512_sub_ps (u, x))));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] (__m512)
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_erfwc (const __m512 x)
                 ///< __m512 vector \f$\in\left[-1,1\right]\f$.
{
  return
    _mm512_mul_ps (x,
                   jbm_16xf32_polynomial_5 (jbm_16xf32_sqr (x), K_ERFWC_F32));
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ (__m512)
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_erfcwc (const __m512 x)
                   ///< __m512 vector \f$\in\left[1,\infty\right]\f$.
{
  __m512 f, x2;
  x2 = jbm_16xf32_sqr (x);
  f = _mm512_mul_ps (jbm_16xf32_rational_7_4 (jbm_16xf32_reciprocal (x),
                                              K_ERFCWC_F32),
                     _mm512_div_ps (x, jbm_16xf32_exp (x2)));
  return
    _mm512_mask_mov_ps (f, _mm512_cmp_ps_mask (x,
                                               _mm512_set1_ps (K_ERFC_MAX_F32),
                                               _CMP_GT_OS),
                        _mm512_setzero_ps ());
}

/**
 * Function to calculate the function erf(x) using jbm_16xf32_erfwc and
 * jbm_16xf32_erfcwc
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_erf (const __m512 x) ///< __m512 vector.
{
  const __m512 u = _mm512_set1_ps (1.f);
  const __m512 ax = jbm_16xf32_abs (x);
  return
    _mm512_mask_blend_ps (_mm512_cmp_ps_mask (ax, u, _CMP_LT_OS),
                          jbm_16xf32_copysign (_mm512_sub_ps (u,
                                                              jbm_16xf32_erfcwc
                                                              (ax)), x),
                          jbm_16xf32_erfwc (x));
}

/**
 * Function to calculate the function erfc(x) using jbm_16xf32_erfwc and
 * jbm_16xf32_erfcwc
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_16xf32_erfc (const __m512 x)        ///< __m512 vector.
{
  const __m512 u2 = _mm512_set1_ps (2.f);
  const __m512 u = _mm512_set1_ps (1.f);
  __m512 ax, cwc, wc;
  ax = jbm_16xf32_abs (x);
  cwc = jbm_16xf32_erfcwc (ax);
  wc = _mm512_sub_ps (u, jbm_16xf32_erfwc (x));
  return
    _mm512_mask_mov_ps
    (_mm512_mask_mov_ps
     (wc, _mm512_cmp_ps_mask (ax, u, _CMP_GT_OS), _mm512_sub_ps (u2, cwc)),
     _mm512_cmp_ps_mask (x, u, _CMP_GT_OS), cwc);
}

/**
 * Function to calculate the solution of a __m512 vector of reduced quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return __m512 vector of solution values.
 */
static inline __m512
jbm_solve_quadratic_reduced_16xf32 (const __m512 a,
///< __m512 vector of 1st order coefficient of the equations.
                                    const __m512 b,
///< __m512 vector of 0th order coefficient of the equations.
                                    const __m512 x1,
///< __m512 vector of left limits of the solution intervals.
                                    const __m512 x2)
///< __m512 vector of right limits of the solution intervals.
{
  __m512 ka, kb, k1, k2;
  k1 = _mm512_set1_ps (-0.5f);
  ka = _mm512_mul_ps (a, k1);
  kb = _mm512_sqrt_ps (_mm512_sub_ps (jbm_16xf32_sqr (ka), b));
  k1 = _mm512_add_ps (ka, kb);
  k2 = _mm512_sub_ps (ka, kb);
  k1 = _mm512_mask_mov_ps (k1, _mm512_cmp_ps_mask (k1, x1, _CMP_LT_OS), k2);
  return _mm512_mask_mov_ps (k1, _mm512_cmp_ps_mask (k1, x2, _CMP_GT_OS), k2);
}

/**
 * Function to calculate the solution of a __m512 vector of quadratic equations
 * in an interval \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^2+b\,x+c=0\f$.
 *
 * \return __m512 vector of solution values.
 */
static inline __m512
jbm_16xf32_solve_quadratic (const __m512 a,
///< __m512 vector of 2nd order coefficient of the equations.
                            const __m512 b,
///< __m512 vector of 1st order coefficient of the equations.
                            const __m512 c,
///< __m512 vector of 0th order coefficient of the equations.
                            const __m512 x1,
///< __m512 vector of left limits of the solution intervals.
                            const __m512 x2)
///< __m512 vector of right limits of the solution intervals.
{
  __m512 k1, k2;
  k1 =
    jbm_solve_quadratic_reduced_16xf32 (_mm512_div_ps (b, a),
                                        _mm512_div_ps (c, a), x1, x2);
  k2 = _mm512_div_ps (jbm_16xf32_opposite (c), b);
  return _mm512_mask_mov_ps (k1, jbm_16xf32_small (a), k2);
}

/**
 * Function to calculate the solution of a __m512 vector of reduced cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^3+a\,x^2+b\,x+c=0\f$.
 *
 * \return __m512 vector of solution values.
 */
static inline __m512
jbm_solve_cubic_reduced_16xf32 (const __m512 a,
                                ///< 2nd order coefficient of the equation.
                                const __m512 b,
                                ///< 1st order coefficient of the equation.
                                const __m512 c,
                                ///< 0th order coefficient of the equation.
                                const __m512 x1,
                                ///< left limit of the solution interval.
                                const __m512 x2)
                               ///< right limit of the solution interval.
{
  __m512 a3, k0, k1, k2, k3, l0, l1, l2, l3, l4, l5, c2p_3, c_2, c_3;
  c2p_3 = _mm512_set1_ps (2.f * M_PIf / 3.f);
  c_2 = _mm512_set1_ps (0.5f);
  c_3 = _mm512_set1_ps (1.f / 3.f);
  a3 = _mm512_mul_ps (a, c_3);
  k0 = _mm512_mul_ps (a3, a3);
  k1 = _mm512_fmsub_ps (b, c_3, k0);
  k0 =
    _mm512_fmsub_ps (_mm512_fmsub_ps (b, a3, c), c_2, _mm512_mul_ps (a3, k0));
  k3 = _mm512_mul_ps (k1, _mm512_mul_ps (k1, k1));
  k2 = _mm512_fmadd_ps (k0, k0, k3);
  l1 = _mm512_sqrt_ps (jbm_16xf32_opposite (k1));
  l0 = _mm512_mul_ps (jbm_16xf32_acos (_mm512_div_ps (k0, k3)), c_3);
  l1 = _mm512_add_ps (l1, l1);
  l2 = _mm512_fmsub_ps (l1, jbm_16xf32_cos (k0), a3);
  l3 = _mm512_fmsub_ps (l1, jbm_16xf32_cos (_mm512_add_ps (l0, c2p_3)), a3);
  l3 = _mm512_mask_mov_ps (l3, _mm512_cmp_ps_mask (l2, x1, _CMP_LT_OS)
                           | _mm512_cmp_ps_mask (l2, x2, _CMP_GT_OS), l2);
  l4 = _mm512_fmsub_ps (l1, jbm_16xf32_cos (_mm512_sub_ps (l0, c2p_3)), a);
  l4 = _mm512_mask_mov_ps (l4, _mm512_cmp_ps_mask (l3, x1, _CMP_LT_OS)
                           | _mm512_cmp_ps_mask (l3, x2, _CMP_GT_OS), l3);
  k1 = _mm512_sqrt_ps (k2);
  l5 = _mm512_add_ps (k0, k1);
  l5 = jbm_16xf32_cbrt (k2);
  k0 = _mm512_sub_ps (k0, k1);
  l5 = _mm512_add_ps (l5, _mm512_sub_ps (jbm_16xf32_cbrt (k0), a3));
  return _mm512_mask_mov_ps (l4, _mm512_cmp_ps_mask (k2, _mm512_setzero_ps (),
                                                     _CMP_LT_OS), l5);
}

/**
 * Function to calculate the solution of a __m512 vector of cubic equations in
 * an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return __m512 vector of solution values.
 */
static inline __m512
jbm_16xf32_solve_cubic (const __m512 a,
///< __m512 vector of 3rd order coefficient of the equations.
                        const __m512 b,
///< __m512 vector of 2nd order coefficient of the equations.
                        const __m512 c,
///< __m512 vector of 1st order coefficient of the equations.
                        const __m512 d,
///< __m512 vector of 0th order coefficient of the equations.
                        const __m512 x1,
///< __m512 vector of left limits of the solution intervals.
                        const __m512 x2)
///< __m512 vector of right limits of the solution intervals.
{
  return
    _mm512_mask_blend_ps (jbm_16xf32_small (a),
                          jbm_solve_cubic_reduced_16xf32 (_mm512_div_ps (b, a),
                                                          _mm512_div_ps (c, a),
                                                          _mm512_div_ps (d, a),
                                                          x1, x2),
                          jbm_16xf32_solve_quadratic (b, c, d, x1, x2));
}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_16xf32_flux_limiter_total (const __m512 d1 __attribute__((unused)),
                               ///< 1st flux limiter function parameter.
                               const __m512 d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm512_setzero_ps ();
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_16xf32_flux_limiter_null (const __m512 d1 __attribute__((unused)),
                              ///< 1st flux limiter function parameter.
                              const __m512 d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm512_set1_ps (1.f);
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_16xf32_flux_limiter_centred (const __m512 d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m512 d2)
                              ///< 2nd flux limiter function parameter.
{
  return _mm512_mask_blend_ps (jbm_16xf32_small (d2),
                               _mm512_div_ps (d1, d2), _mm512_setzero_ps ());

}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_16xf32_flux_limiter_superbee (const __m512 d1,
                                  ///< 1st flux limiter function parameter.
                                  const __m512 d2)
                               ///< 2nd flux limiter function parameter.
{
  __m512 r;
  r = _mm512_div_ps (d1, d2);
  r = _mm512_max_ps (_mm512_min_ps (jbm_16xf32_dbl (r), _mm512_set1_ps (1.f)),
                     _mm512_min_ps (r, _mm512_set1_ps (2.f)));
  return _mm512_mask_mov_ps (_mm512_setzero_ps (),
                             _mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                 _mm512_set1_ps (FLT_EPSILON),
                                                 _CMP_GT_OS), r);
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_16xf32_flux_limiter_minmod (const __m512 d1,
                                ///< 1st flux limiter function parameter.
                                const __m512 d2)
                                ///< 2nd flux limiter function parameter.
{
  __m512 r;
  r = _mm512_min_ps (_mm512_div_ps (d1, d2), _mm512_set1_ps (1.f));
  return _mm512_mask_mov_ps (_mm512_setzero_ps (),
                             _mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                 _mm512_set1_ps (FLT_EPSILON),
                                                 _CMP_GT_OS), r);
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_16xf32_flux_limiter_VanLeer (const __m512 d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m512 d2)
    ///< 2nd flux limiter function parameter.
{
  __m512 r, k;
  r = _mm512_div_ps (d1, d2);
  k = jbm_16xf32_abs (r);
  r =
    _mm512_div_ps (_mm512_add_ps (r, k),
                   _mm512_add_ps (_mm512_set1_ps (1.f), k));
  return _mm512_mask_mov_ps (_mm512_setzero_ps (),
                             _mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                 _mm512_set1_ps (FLT_EPSILON),
                                                 _CMP_GT_OS), r);
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_16xf32_flux_limiter_VanAlbada (const __m512 d1,
                                   ///< 1st flux limiter function parameter.
                                   const __m512 d2)
    ///< 2nd flux limiter function parameter.
{
  __m512 r, k;
  r = _mm512_div_ps (d1, d2);
  k = jbm_16xf32_sqr (r);
  r =
    _mm512_div_ps (_mm512_add_ps (r, k),
                   _mm512_add_ps (_mm512_set1_ps (1.f), k));
  return _mm512_mask_mov_ps (_mm512_setzero_ps (),
                             _mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                 _mm512_set1_ps (FLT_EPSILON),
                                                 _CMP_GT_OS), r);
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_16xf32_flux_limiter_minsuper (const __m512 d1,
                                  ///< 1st flux limiter function parameter.
                                  const __m512 d2)
    ///< 2nd flux limiter function parameter.
{
  __m512 r;
  r = _mm512_min_ps (_mm512_div_ps (d1, d2), _mm512_set1_ps (2.f));
  return _mm512_mask_mov_ps (_mm512_setzero_ps (),
                             _mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                 _mm512_set1_ps (FLT_EPSILON),
                                                 _CMP_GT_OS), r);
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_16xf32_flux_limiter_supermin (const __m512 d1,
                                  ///< 1st flux limiter function parameter.
                                  const __m512 d2)
    ///< 2nd flux limiter function parameter.
{
  __m512 r;
  r = _mm512_div_ps (d1, d2);
  r = _mm512_min_ps (jbm_16xf32_dbl (r), _mm512_set1_ps (1.f));
  return _mm512_mask_mov_ps (_mm512_setzero_ps (),
                             _mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                 _mm512_set1_ps (FLT_EPSILON),
                                                 _CMP_GT_OS), r);
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_16xf32_flux_limiter_monotonized_central (const __m512 d1,
///< 1st flux limiter function parameter.
                                             const __m512 d2)
///< 2nd flux limiter function parameter.
{
  __m512 r, rm;
  r = _mm512_div_ps (d1, d2);
  rm =
    _mm512_mul_ps (_mm512_set1_ps (0.5f),
                   _mm512_add_ps (r, _mm512_set1_ps (1.f)));
  rm =
    _mm512_mask_mov_ps (_mm512_set1_ps (2.f),
                        _mm512_cmp_ps_mask (r, _mm512_set1_ps (3.f),
                                            _CMP_LT_OS), rm);

  rm =
    _mm512_mask_mov_ps (rm, _mm512_cmp_ps_mask (r, _mm512_set1_ps (1.f / 3.f),
                                                _CMP_GT_OS),
                        jbm_16xf32_dbl (r));
  return _mm512_mask_mov_ps (_mm512_setzero_ps (),
                             _mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                 _mm512_set1_ps (FLT_EPSILON),
                                                 _CMP_GT_OS), r);
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_16xf32_flux_limiter_mean (const __m512 d1,
                              ///< 1st flux limiter function parameter.
                              const __m512 d2)
    ///< 2nd flux limiter function parameter.
{
  __m512 r;
  r = _mm512_mul_ps (_mm512_set1_ps (0.5f),
                     _mm512_add_ps (_mm512_set1_ps (1.f),
                                    _mm512_div_ps (d1, d2)));
  return _mm512_mask_mov_ps (_mm512_setzero_ps (),
                             _mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                 _mm512_set1_ps (FLT_EPSILON),
                                                 _CMP_GT_OS), r);
}

/**
 * Function to do a flux limiter function (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_16xf32_flux_limiter (const __m512 d1,
                         ///< 1st flux limiter function parameter.
                         const __m512 d2,
                         ///< 2nd flux limiter function parameter.
                         unsigned int type)
    ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_16xf32_flux_limiter_total (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_16xf32_flux_limiter_null (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_16xf32_flux_limiter_centred (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_16xf32_flux_limiter_superbee (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_16xf32_flux_limiter_minmod (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_16xf32_flux_limiter_VanLeer (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_16xf32_flux_limiter_VanAlbada (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_16xf32_flux_limiter_minsuper (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_16xf32_flux_limiter_supermin (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_16xf32_flux_limiter_monotonized_central (d1, d2);
    }
  return jbm_16xf32_flux_limiter_mean (d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (__m512).
 *
 * \return __m512 vector of integral values.
 */
static inline __m512
jbm_16xf32_integral (__m512 (*f) (__m512),
                     ///< pointer to the function to integrate.
                     const __m512 x1,   ///< left limit of the interval.
                     const __m512 x2)   ///< right limit of the interval.
{
  __m512 k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  __m512 k2, f1, f2;
#endif
  unsigned int i;
  h = _mm512_set1_ps (0.5f);
  dx = _mm512_mul_ps (h, _mm512_sub_ps (x2, x1));
  x = _mm512_mul_ps (h, _mm512_add_ps (x2, x1));
  k = _mm512_set1_ps (JBM_INTEGRAL_GAUSS_A_F32[0]);
  k = _mm512_mul_ps (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = _mm512_set1_ps (JBM_INTEGRAL_GAUSS_B_F32[i]);
      k2 = _mm512_mul_ps (k2, dx);
      f1 = f (_mm512_sub_ps (x, k2));
      f2 = f (_mm512_add_ps (x, k2));
      h = _mm512_set1_ps (JBM_INTEGRAL_GAUSS_A_F32[i]);
      k = _mm512_fmadd_ps (h, _mm512_add_ps (f1, f2), k);
    }
#endif
  return _mm512_mul_ps (k, dx);
}

/**
 * Function to calculate the additive reduction value of a __m512d vector.
 *
 * \return additive reduction (double).
 */
static inline double
jbm_8xf64_reduce_add (const __m512d x)  ///< __m512d vector.
{
  __m256d h, l;
  h = _mm512_extractf64x4_pd (x, 1);
  l = _mm512_castpd512_pd256 (x);
  return jbm_4xf64_reduce_add (_mm256_add_pd (h, l));
}

/**
 * Function to calculate the maximum reduction value of a __m512d vector.
 *
 * \return maximum reduction (double).
 */
static inline double
jbm_8xf64_reduce_max (const __m512d x)  ///< __m512d vector.
{
  __m256d h, l;
  h = _mm512_extractf64x4_pd (x, 1);
  l = _mm512_castpd512_pd256 (x);
  return jbm_4xf64_reduce_max (_mm256_max_pd (h, l));
}

/**
 * Function to calculate the minimum reduction value of a __m512d vector.
 *
 * \return minimum reduction (double).
 */
static inline double
jbm_8xf64_reduce_min (const __m512d x)  ///< __m512d vector.
{
  __m256d h, l;
  h = _mm512_extractf64x4_pd (x, 1);
  l = _mm512_castpd512_pd256 (x);
  return jbm_4xf64_reduce_min (_mm256_min_pd (h, l));
}

/**
 * Function to calculate the maximum and minimum reduction value of a __m512d
 * vector.
 */
static inline void
jbm_8xf64_reduce_maxmin (const __m512d x,       ///< __m512d vector.
                         double *max,   ///< pointer to the maximum value
                         double *min)   ///< pointer to the minimum value
{
  __m256d h, l;
  h = _mm512_extractf64x4_pd (x, 1);
  l = _mm512_castpd512_pd256 (x);
  *max = jbm_4xf64_reduce_max (_mm256_max_pd (h, l));
  *min = jbm_4xf64_reduce_min (_mm256_min_pd (h, l));
}

/**
 * Function to calculate the additive inverse value of a __m512d vector.
 *
 * \return negative value vector (__m512d).
 */
static inline __m512d
jbm_8xf64_opposite (const __m512d x)    ///< __m512d vector.
{
  JBM8xF64 y;
  y.i = JBM_8xF64_BITS_SIGN;
  return _mm512_xor_pd (x, y.x);
}

/**
 * Function to calculate the multiplicative inverse value of a __m512d vector.
 *
 * \return reciprocal value vector (__m512d).
 */
static inline __m512d
jbm_8xf64_reciprocal (const __m512d x)  ///< __m512d vector.
{
  return _mm512_div_pd (_mm512_set1_pd (1.), x);
}

/**
 * Function to calculate the sign of a __m512d vector.
 *
 * \return sign vector (__m512d).
 */
static inline __m512d
jbm_8xf64_sign (const __m512d x)        ///< __m512d vector.
{
  JBM8xF64 y;
  y.x = x;
  y.i = _mm512_and_epi64 (y.i, JBM_8xF64_BITS_SIGN);
  y.i = _mm512_or_epi64 (y.i, JBM_8xF64_BITS_1);
  return y.x;
}

/**
 * Function to calculate the absolute value of a __m512d vector.
 *
 * \return absolute value vector.
 */
static inline __m512d
jbm_8xf64_abs (const __m512d x)
{
  JBM8xF64 y;
  y.i = JBM_8xF64_BITS_SIGN;
  return _mm512_andnot_pd (y.x, x);
}

/**
 * Function to copy the sign of a __m512d vector to another __m512d vector.
 *
 * \return __m512d vector with magnitud of 1st vector and sign of 2nd vector.
 */
static inline __m512d
jbm_8xf64_copysign (const __m512d x,
///< __m512d vector to preserve magnitude.
                    const __m512d y)    ///< __m512d vector to preserve sign.
{
  JBM8xF64 m;
  m.i = JBM_8xF64_BITS_SIGN;
  return _mm512_or_pd (jbm_8xf64_abs (x), _mm512_and_pd (y, m.x));
}

/**
 * Function to calculate the hypot function (__m512d).
 *
 * \return function value vector (__m512d).
 */
static inline __m512d
jbm_8xf64_hypot (const __m512d x,       ///< 1st __m512d vector.
                 const __m512d y)       ///< 2nd __m512d vector.
{
  return _mm512_sqrt_pd (_mm512_fmadd_pd (x, x, _mm512_mul_pd (y, y)));
}

/**
 * Function to calculate the rest of a division (__m512d).
 *
 * \return rest value (in [0,|divisor|) interval) (__m512d).
 */
static inline __m512d
jbm_8xf64_mod (const __m512d x, ///< dividend (__m512d).
               const __m512d d) ///< divisor (__m512d).
{
  __m512d r;
  r = _mm512_floor_pd (_mm512_div_pd (x, d));
  return
    _mm512_mask_blend_pd
    (_mm512_cmp_pd_mask (jbm_8xf64_abs (r), _mm512_set1_pd (1. / DBL_EPSILON),
                         _CMP_GT_OQ),
     _mm512_fnmadd_pd (r, d, x), _mm512_mul_pd (d, _mm512_set1_pd (0.5)));
}

/**
 * Function to implement the standard frexp function (__m512d).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline __m512d
jbm_8xf64_frexp (const __m512d x,       ///< __m512d vector.
                 __m512i *e)    ///< pointer to the extracted exponents vector.
{
  const __m512i zi = _mm512_setzero_si512 ();
  const __m512i bias = JBM_8xF64_BIAS;
  const __m512i exp_mask = JBM_8xF64_BITS_EXPONENT;
  const __m512i sign_mask = JBM_8xF64_BITS_SIGN;
  const __m512i mant_mask = JBM_8xF64_BITS_MANTISSA;
  JBM8xF64 y, z;
  __m512i exp;
  __mmask16 is_z, is_sub, is_nan, is_finite;
  // y=abs(x)
  y.x = jbm_8xf64_abs (x);
  // masks
  is_z = _mm512_cmpeq_epu64_mask (y.i, zi);
  is_nan = _mm512_cmpge_epu64_mask (y.i, exp_mask);
  is_finite = ~(is_z | is_nan);
  // extract exponent
  exp = _mm512_maskz_srli_epi64 (is_finite, y.i, 52);
  // subnormals
  is_sub = _mm512_cmpeq_epu64_mask (exp, zi) & is_finite;
  y.x = _mm512_mask_mul_pd (y.x, is_sub, y.x, _mm512_set1_pd (0x1p52));
  exp
    = _mm512_mask_mov_epi64
    (exp, is_sub, _mm512_sub_epi64 (_mm512_srli_epi64 (y.i, 52),
                                    _mm512_set1_epi64 (52ll)));
  // exponent
  *e = _mm512_mask_sub_epi64 (zi, is_finite, exp, bias);
  // build mantissa in [0.5,1)
  z.x = x;
  y.i = _mm512_or_epi64 (_mm512_and_epi64 (z.i, sign_mask),
                         _mm512_or_epi64 (_mm512_set1_epi64 (JBM_F64_BIAS
                                                             << 52),
                                          _mm512_and_epi64 (y.i, mant_mask)));
  return _mm512_mask_mov_pd (x, is_finite, y.x);
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (__m512i)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_exp2n (__m512i e)     ///< exponent vector (__m512i).
{
  const __m512i v1074 = _mm512_set1_epi64 (1074ll);
  const __m512i v1023 = _mm512_set1_epi64 (1023ll);
  const __m512i vn1023 = _mm512_set1_epi64 (-1023ll);
  const __m512i vn1075 = _mm512_set1_epi64 (-1075ll);
  __m512d x;
  __mmask16 is_norm;
  is_norm = _mm512_cmpgt_epi64_mask (e, vn1023);
  x =
    _mm512_mask_blend_pd
    (is_norm, _mm512_setzero_pd (),
     _mm512_castsi512_pd (_mm512_slli_epi64 (_mm512_add_epi64 (e, v1023), 52)));
  x =
    _mm512_mask_mov_pd
    (x, _mm512_cmpgt_epi64_mask (e, vn1075) & ~is_norm,
     _mm512_castsi512_pd
     (_mm512_sllv_epi64 (_mm512_set1_epi64 (1ll),
                         _mm512_add_epi64 (e, v1074))));
  return
    _mm512_mask_mov_pd (x, _mm512_cmpgt_epi64_mask (e, v1023),
                        _mm512_set1_pd (INFINITY));
}

/**
 * Function to implement the standard ldexp function (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_ldexp (const __m512d x,       ///< __m512d vector.
                 __m512i e)     ///< exponent vector (__m512i).
{
  return _mm512_mul_pd (x, jbm_8xf64_exp2n (e));
}

/**
 * Function to check small __m512d vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline __mmask16
jbm_8xf64_small (const __m512d x)       ///< __m512d vector.
{
  return _mm512_cmp_pd_mask (jbm_8xf64_abs (x), _mm512_set1_pd (DBL_EPSILON),
                             _CMP_LT_OS);
}

/**
 * Function to calculate the __m512d vector with the components with lower
 * module in the [a, b] interval.
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin __m512d vector.
 */
static inline __m512d
jbm_8xf64_modmin (const __m512d a,      ///< 1st __m512d vector.
                  const __m512d b)      ///< 2nd __m512d vector.
{
  __m512d aa, ab, y, z;
  z = _mm512_setzero_pd ();
  ab = _mm512_mul_pd (a, b);
  y = _mm512_mask_mov_pd (a, _mm512_cmp_pd_mask (z, ab, _CMP_GT_OS), z);
  aa = jbm_8xf64_abs (y);
  ab = jbm_8xf64_abs (b);
  return _mm512_mask_mov_pd (y, _mm512_cmp_pd_mask (aa, ab, _CMP_GT_OS), b);
}

/**
 * Function to interchange 2 __m512d numbers.
 */
static inline void
jbm_change_8xf64 (__m512d *restrict a,  ///< 1st __m512d vector pointer.
                  __m512d *restrict b)  ///< 2nd __m512d vector pointer.
{
  __m512d c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the double of a __m512d vector.
 *
 * \return __m512d double.
 */
static inline __m512d
jbm_8xf64_dbl (const __m512d x) ///< __m512d vector.
{
  return _mm512_add_pd (x, x);
}

/**
 * Function to calculate the square of the components of a __m512d vector.
 *
 * \return __m512d vector square.
 */
static inline __m512d
jbm_8xf64_sqr (const __m512d x) ///< __m512d vector.
{
  return _mm512_mul_pd (x, x);
}

/**
 * Function to perform an extrapolation between 2 __m512d vectors of 2D points.
 *
 * \return __m512d vector of y-coordinates of the extrapolated points.
 */
static inline __m512d
jbm_8xf64_extrapolate (const __m512d x,
                       ///< __m512d vector of x-coordinates of the extrapolated
                       ///< points.
                       const __m512d x1,
                       ///< __m512d vector of x-coordinates of the 1st points.
                       const __m512d x2,
                       ///< __m512d vector of x-coordinates of the 2nd points.
                       const __m512d y1,
                       ///< __m512d vector of y-coordinates of the 1st points.
                       const __m512d y2)
    ///< __m512d vector of y-coordinates of the 2nd points.
{
  __m512d d;
  d = _mm512_sub_pd (x, x1);
  return _mm512_fmadd_pd (d, _mm512_div_pd (_mm512_sub_pd (y2, y1),
                                            _mm512_sub_pd (x2, x1)), y1);
}

/**
 * Function to perform an interpolation between 2 __m512d vectors of 2D points.
 *
 * \return __m512d vector of y-coordinates of the interpolated points.
 */
static inline __m512d
jbm_8xf64_interpolate (const __m512d x,
                       ///< __m512d vector of x-coordinates of the interpolated
                       ///< points.
                       const __m512d x1,
                       ///< __m512d vector of x-coordinates of the 1st points.
                       const __m512d x2,
                       ///< __m512d vector of x-coordinates of the 2nd points.
                       const __m512d y1,
                       ///< __m512d vector of y-coordinates of the 1st points.
                       const __m512d y2)
    ///< __m512d vector of y-coordinates of the 2nd points.
{
  __m512d k;
  k = jbm_8xf64_extrapolate (x, x1, x2, y1, y2);
  k = _mm512_mask_mov_pd (y1, _mm512_cmp_pd_mask (x, x1, _CMP_GT_OS), k);
  return _mm512_mask_mov_pd (y2, _mm512_cmp_pd_mask (x, x2, _CMP_LT_OS), k);
}

/**
 * Function to calculate the length of a __m512d vector of 2D segments.
 *
 * \return __m512d vector of segment lengths.
 */
static inline __m512d
jbm_8xf64_v2_length (const __m512d x1,
///< __m512d vector of x-coordinates of the 1st points defining the segment.
                     const __m512d y1,
///< __m512d vector of y-coordinates of the 1st points defining the segment.
                     const __m512d x2,
///< __m512d vector of x-coordinates of the 2nd points defining the segment.
                     const __m512d y2)
///< __m512d vector of y-coordinates of the 2nd points defining the segment.
{
  return jbm_8xf64_hypot (_mm512_sub_pd (x2, x1), _mm512_sub_pd (y2, y1));
}

/**
 * Function to calculate the length of a __m512d vector of 3D segments.
 *
 * \return __m512d vector of segment lengths.
 */
static inline __m512d
jbm_8xf64_v3_length (const __m512d x1,
///< __m512d vector of x-coordinates of the 1st points defining the segments.
                     const __m512d y1,
///< __m512d vector of y-coordinates of the 1st points defining the segments.
                     const __m512d z1,
///< __m512d vector of z-coordinates of the 1st points defining the segments.
                     const __m512d x2,
///< __m512d vector of x-coordinates of the 2nd points defining the segments.
                     const __m512d y2,
///< __m512d vector of y-coordinates of the 2nd points defining the segments.
                     const __m512d z2)
///< __m512d vector of z-coordinates of the 2nd points defining the segments.
{
  __m512d dx, dy, dz;
  dx = jbm_8xf64_sqr (_mm512_sub_pd (x2, x1));
  dy = _mm512_sub_pd (y2, y1);
  dy = _mm512_fmadd_pd (dy, dy, dx);
  dz = _mm512_sub_pd (z2, z1);
  return _mm512_sqrt_pd (_mm512_fmadd_pd (dz, dz, dy));
}

/**
 * Function to calculate a 1st order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_1 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, _mm512_set1_pd (p[1]), _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 2nd order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_2 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 3rd order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_3 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 4th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_4 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 5th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_5 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 6th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_6 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 7th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_7 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 8th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_8 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 9th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_9 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 10th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_10 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 11th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_11 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 12th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_12 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 13th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_13 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_12 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 14th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_14 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_13 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 15th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_15 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_14 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 16th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_16 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_15 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 17th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_17 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_16 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 18th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_18 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_17 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 19th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_19 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_18 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 20th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_20 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_19 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 21th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_21 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_20 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 22th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_22 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_21 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 23th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_23 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_22 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 24th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_24 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_23 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 25th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_25 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_24 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 26th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_26 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_25 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 27th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_27 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_26 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 28th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_28 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_27 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 29th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_8xf64_polynomial_29 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_8xf64_polynomial_28 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 0th+1st order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_1_0 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[1]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_2_0 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+1st order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_2_1 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[2]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_3_0 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_3_1 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_3_2 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[3]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_4_0 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_4_1 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_4_2 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_4_3 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[4]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_5_0 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_5_1 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_5_2 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_5_3 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_5_4 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[5]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_6_0 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_6_1 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_6_2 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_6_3 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_6_4 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_6_5 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[6]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_7_0 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_7_1 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_7_2 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_7_3 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_7_4 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_7_5 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_7_6 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[7]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_8_0 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_8_1 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_8_2 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_8_3 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_8_4 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_8_5 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_8_6 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_8_7 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[8]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_9_0 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_9_1 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_9_2 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_9_3 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_9_4 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_9_5 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_9_6 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_9_7 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_9_8 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[9]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_10_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_10_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_10_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_10_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_10_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_10_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_10_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_10_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_10_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_10_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[10]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_11_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_11_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_11_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_11_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_11_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_11_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_11_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_11_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_11_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_11_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_11_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[11]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_12_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_12_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_12_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_12_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_12_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_12_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_12_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_12_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_12_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_12_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_12_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_12_11 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_11 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[12]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_13_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_12 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_13_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_13_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_13_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_13_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_13_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_13_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_13_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_13_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_13_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_13_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_13_11 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_11 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_13_12 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_12 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[13]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_14_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_13 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_14_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_12 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_14_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_14_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_14_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_14_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_14_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_14_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_14_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_14_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_14_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_14_11 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_11 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_14_12 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_12 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_14_13 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_13 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[14]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_15_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_14 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_15_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_13 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_15_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_12 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_15_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_15_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_15_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_15_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_15_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_15_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_15_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_15_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_15_11 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_11 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_15_12 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_12 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_15_13 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_13 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_15_14 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_14 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[15]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_16_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_15 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_16_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_14 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_16_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_13 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_16_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_12 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_16_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_16_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_16_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_16_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_16_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_16_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_16_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_16_11 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_11 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_16_12 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_12 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_16_13 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_13 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_16_14 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_14 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_16_15 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_15 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[16]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_17_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_16 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_17_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_15 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_17_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_14 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_17_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_13 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_17_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_12 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_17_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_17_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_17_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_17_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_17_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_17_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_17_11 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_11 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_17_12 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_12 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_17_13 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_13 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_17_14 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_14 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_17_15 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_15 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_17_16 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_16 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[17]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_18_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_17 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_18_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_16 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_18_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_15 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_18_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_14 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_18_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_13 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_18_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_12 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_18_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_18_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_18_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_18_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_18_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_18_11 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_11 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_18_12 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_12 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_18_13 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_13 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_18_14 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_14 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_18_15 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_15 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_18_16 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_16 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_18_17 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_17 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[18]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_18 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_17 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_16 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_15 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_14 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_13 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_12 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_11 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_11 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_12 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_12 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_13 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_13 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_14 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_14 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_15 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_15 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_16 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_16 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_17 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_17 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_19_18 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_18 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[19]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_19 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_18 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_17 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_16 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_15 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_14 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_13 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_12 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_11 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_11 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_12 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_12 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_13 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_13 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_14 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_14 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_15 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_15 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_16 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_16 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_17 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_17 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_18 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_18 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_20_19 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_19 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[20]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_20 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_19 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_18 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_17 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_16 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_15 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_14 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_13 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_12 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_11 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_11 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_12 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_12 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_13 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_13 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_14 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_14 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_15 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_15 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_16 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_16 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_17 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_17 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_18 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_18 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_19 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_19 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 20),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_21_20 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_20 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[21]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+22th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_21 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_20 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_19 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_18 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_17 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_16 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_15 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_14 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_13 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_12 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_11 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_11 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_12 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_12 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_13 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_13 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_14 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_14 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_15 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_15 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_16 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_16 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_17 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_17 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_18 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_18 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_19 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_19 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 20),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_20 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_20 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 21),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_22_21 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_21 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[22]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+23th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_22 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+22th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_21 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_20 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_19 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_18 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_17 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_16 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_15 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_14 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_13 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_12 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_11 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_11 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_12 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_12 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_13 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_13 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_14 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_14 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_15 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_15 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_16 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_16 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_17 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_17 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_18 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_18 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_19 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_19 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 20),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_20 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_20 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 21),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_21 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_21 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 22),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+22th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_23_22 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_22 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[23]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+24th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_23 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+23th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_22 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+22th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_21 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_20 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_19 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_18 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_17 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_16 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_15 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_14 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_13 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_11 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_11 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_12 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_12 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_12 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_13 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_13 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_14 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_14 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_15 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_15 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_16 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_16 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_17 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_17 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_18 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_18 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_19 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_19 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 20),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_20 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_20 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 21),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_21 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_21 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 22),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_22 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_22 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 23),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+23th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_24_23 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_23 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[24]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+25th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_24 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+24th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_23 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+23th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_22 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+22th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_21 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_20 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_19 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_18 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_17 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_16 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_15 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_14 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_11 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_11 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_13 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_12 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_12 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_12 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_13 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_13 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_14 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_14 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_15 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_15 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_16 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_16 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_17 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_17 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_18 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_18 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_19 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_19 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 20),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_20 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_20 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 21),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_21 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_21 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 22),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_22 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_22 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 23),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_23 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_23 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 24),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+24th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_25_24 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_24 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[25]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+26th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_25 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+25th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_24 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+24th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_23 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+23th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_22 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+22th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_21 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_20 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_19 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_18 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_17 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_16 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_15 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_11 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_11 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_14 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_12 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_12 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_13 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_13 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_13 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_12 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_14 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_14 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_15 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_15 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_16 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_16 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_17 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_17 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_18 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_18 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_19 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_19 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 20),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_20 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_20 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 21),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_21 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_21 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 22),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_22 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_22 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 23),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_23 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_23 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 24),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_24 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_24 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 25),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+25th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_26_25 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_25 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[26]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+27th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_26 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+26th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_25 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+25th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_24 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+24th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_23 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+23th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_22 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+22th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_21 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_20 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_19 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_18 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_17 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_16 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_11 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_11 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_15 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_12 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_12 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_14 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_13 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_13 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_13 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_14 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_14 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_12 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_15 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_15 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_16 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_16 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_17 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_17 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_18 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_18 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_19 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_19 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 20),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_20 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_20 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 21),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_21 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_21 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 22),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_22 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_22 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 23),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_23 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_23 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 24),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_24 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_24 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 25),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 25th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_25 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_25 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 26),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+26th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_27_26 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_26 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[27]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+28th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_27 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+27th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_26 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+26th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_25 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+25th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_24 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+24th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_23 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+23th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_22 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+22th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_21 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_20 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_19 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_18 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_17 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_11 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_11 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_16 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_12 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_12 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_15 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_13 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_13 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_14 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_14 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_14 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_13 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_15 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_15 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_12 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_16 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_16 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_17 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_17 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_18 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_18 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_19 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_19 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 20),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_20 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_20 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 21),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_21 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_21 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 22),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_22 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_22 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 23),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_23 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_23 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 24),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_24 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_24 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 25),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 25th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_25 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_25 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 26),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 26th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_26 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_26 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 27),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+27th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_28_27 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_27 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[28]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+29th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_0 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_28 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+28th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_1 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_1 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_27 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+27th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_2 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_2 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_26 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+26th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_3 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_3 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_25 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+25th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_4 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_4 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_24 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+24th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_5 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_5 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_23 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+23th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_6 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_6 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_22 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+22th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_7 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_7 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_21 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_8 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_8 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_20 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_9 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_9 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_19 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_10 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_10 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_18 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_11 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_11 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_17 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_12 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_12 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_16 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_13 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_13 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_15 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_14 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_14 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_14 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_15 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_15 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_13 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_16 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_16 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_12 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_17 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_17 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_11 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_18 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_18 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_10 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_19 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_19 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_9 (x, p + 20),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_20 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_20 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_8 (x, p + 21),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_21 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_21 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_7 (x, p + 22),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_22 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_22 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_6 (x, p + 23),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_23 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_23 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_5 (x, p + 24),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_24 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_24 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_4 (x, p + 25),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 25th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_25 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_25 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_3 (x, p + 26),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 26th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_26 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_26 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_2 (x, p + 27),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 27th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_27 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_27 (x, p),
                        _mm512_fmadd_pd (x, jbm_8xf64_polynomial_1 (x, p + 28),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+28th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_8xf64_rational_29_28 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_8xf64_polynomial_28 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[29]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate the well conditionated function cbrt(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_cbrtwc (const __m512d x)
                  ///< __m512d vector \f$\in\left[\frac12,\;1\right]\f$.
{
  return jbm_8xf64_rational_11_6 (x, K_CBRTWC_F64);
}

/**
 * Function to calculate the function cbrt(x) using the jbm_8xf64_cbrtwc
 * function (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_cbrt (const __m512d x)        ///< __m512d vector.
{
  const __m512d cbrt2 = JBM_8xF64_CBRT2;
  const __m512d cbrt4 = JBM_8xF64_CBRT4;
  const __m512i v3 = _mm512_set1_epi32 (3);
  const __m512i v2 = _mm512_set1_epi64 (2);
  const __m512i v1 = _mm512_set1_epi64 (1);
  __m512d y;
  __m512i e, e3, r, n;
  y = jbm_8xf64_frexp (jbm_8xf64_abs (x), &e);
  e3 = _mm512_mul_epu32 (e, _mm512_set1_epi32 (0x55555556));
  e3 = _mm512_srli_epi64 (e3, 32);
  r = _mm512_sub_epi32 (e, _mm512_mullo_epi32 (e3, v3));
  n = _mm512_srai_epi32 (r, 31);
  r = _mm512_add_epi32 (r, _mm512_and_si512 (n, v3));
  e3 = _mm512_sub_epi32 (e3, _mm512_and_si512 (n, _mm512_set1_epi32 (1)));
  y = jbm_8xf64_ldexp (jbm_8xf64_cbrtwc (y), e3);
  y = _mm512_mask_mul_pd (y, _mm512_cmpeq_epi64_mask (r, v1), y, cbrt2);
  y = _mm512_mask_mul_pd (y, _mm512_cmpeq_epi64_mask (r, v2), y, cbrt4);
  return jbm_8xf64_copysign (y, x);
}

/**
 * Function to calculate the well conditionated function expm1(x) for x in
 * [-log(2)/2,log(2)/2] (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_expm1wc (const __m512d x)
///< __m512d vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  return _mm512_mul_pd (x, jbm_8xf64_rational_8_2 (x, K_EXPM1WC_F64));
}

/**
 * Function to calculate the well conditionated function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (__m512d).
 *
 * \return function value.
 */
static inline __m512d
jbm_8xf64_exp2wc (const __m512d x)
    ///< __m512d vector \f$\in[\frac12,1]\f$.
{
  return jbm_8xf64_rational_9_4 (x, K_EXP2WC_F64);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_8xf64 and
 * jbm_8xf64_exp2n functions.
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_exp2 (const __m512d x)        ///< __m512d vector.
{
  __m512d y, f;
  y = _mm512_floor_pd (x);
  f = _mm512_sub_pd (x, y);
  return _mm512_mul_pd (jbm_8xf64_exp2n (_mm512_cvtpd_epi64 (y)),
                        jbm_8xf64_exp2wc (f));
}

/**
 * Function to calculate the function exp(x) using the jbm_8xf64_exp2 function.
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_exp (const __m512d x) ///< __m512d vector.
{
  return jbm_8xf64_exp2 (_mm512_mul_pd (x, _mm512_set1_pd (M_LOG2E)));
}

/**
 * Function to calculate the function exp10(x) using the jbm_8xf64_exp2
 * function (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_exp10 (const __m512d x)       ///< __m512d vector.
{
  return jbm_8xf64_exp2 (_mm512_mul_pd (x, _mm512_set1_pd (M_LN10 / M_LN2)));
}

/**
 * Function to calculate the function expm1(x) using the jbm_8xf64_expm1wc and
 * jbm_8xf64_exp functions (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_expm1 (const __m512d x)       ///< __m512d vector.
{
  return
    _mm512_mask_blend_pd (_mm512_cmp_pd_mask (jbm_8xf64_abs (x),
                                              _mm512_set1_pd (M_LN2 / 2.),
                                              _CMP_LT_OS),
                          _mm512_sub_pd (jbm_8xf64_exp (x),
                                         _mm512_set1_pd (1.)),
                          jbm_8xf64_expm1wc (x));
}

/**
 * Function to calculate the well conditionated function log2(x) for x in
 * \f$[\sqrt{0.5}-1,\sqrt{2}-1]\f$ (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_log2wc (const __m512d x)      ///< __m512d vector.
{
  return _mm512_mul_pd (x, jbm_8xf64_rational_11_5 (x, K_LOG2WC_F64));
}

/**
 * Function to calculate the function log_2(x) using jbm_logwc_8xf64 and
 * jbm_8xf64_frexp
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_log2 (const __m512d x)        ///< __m512d vector.
{
  const __m512d z = _mm512_setzero_pd ();
  __m512d y;
  __m512i e;
  __mmask16 m;
  y = jbm_8xf64_frexp (x, &e);
  m = _mm512_cmplt_pd_mask (y, _mm512_set1_pd (M_SQRT1_2));
  y = _mm512_add_pd (y, _mm512_maskz_mov_pd (m, y));
  e = _mm512_sub_epi64 (e, _mm512_maskz_set1_epi64 (m, 1));
  y = _mm512_add_pd (jbm_8xf64_log2wc (_mm512_sub_pd (y,
                                                      _mm512_set1_pd (1.))),
                     _mm512_cvtepi64_pd (e));
  y = _mm512_mask_mov_pd (y, _mm512_cmpeq_pd_mask (x, z),
                          _mm512_set1_pd (-INFINITY));
  y = _mm512_mask_mov_pd (y, _mm512_cmplt_pd_mask (x, z), _mm512_set1_pd (NAN));
  return
    _mm512_mask_mov_pd (y, _mm512_cmp_pd_mask (x, x, _CMP_ORD_Q) ^ 0xffff, x);
}

/**
 * Function to calculate the function log(x) using jbm_8xf64_log2 (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_log (const __m512d x) ///< __m512d vector.
{
  return _mm512_mul_pd (jbm_8xf64_log2 (x), _mm512_set1_pd (M_LN2));
}

/**
 * Function to calculate the function log10(x) using jbm_8xf64_log2 (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_log10 (const __m512d x)       ///< __m512d vector.
{
  return _mm512_mul_pd (jbm_8xf64_log2 (x), _mm512_set1_pd (M_LN2 / M_LN10));
}

/**
 * Function to calculate the function x^e with e an integer number (__m512d).
 *
 * \return function value (__m512d) (__m512d).
 */
static inline __m512d
jbm_8xf64_pown (const __m512d x,        ///< __m512d vector.
                const int e)    ///< exponent (int).
{
  __m512d f, xn;
  unsigned int i;
  f = _mm512_set1_pd (1.);
  if (e < 0)
    xn = _mm512_div_pd (f, x);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_8xf64_sqr (xn))
    if (i & 1)
      f = _mm512_mul_pd (f, xn);
  return f;
}

/**
 * Function to calculate the function dbl using the jbm_8xf64_exp2 and
 * jbm_8xf64_log2 functions.
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_pow (const __m512d x, ///< __m512d vector.
               const __m512d e) ///< exponent (__m512d).
{
  return jbm_8xf64_exp2 (_mm512_mul_pd (e, jbm_8xf64_log2 (x)));
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] (__m512d)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_sinwc (const __m512d x)
    ///< __m512d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return
    _mm512_mul_pd (x, jbm_8xf64_polynomial_6 (jbm_8xf64_sqr (x), K_SINWC_F64));
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_coswc (const __m512d x)
    ///< __m512d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return jbm_8xf64_polynomial_6 (jbm_8xf64_sqr (x), K_COSWC_F64);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_8xf64_sinwc approximation (__m512d).
 */
static inline void
jbm_8xf64_sincoswc (const __m512d x,
                    ///< __m512d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                    __m512d *s,
                    ///< pointer to the sin function value (__m512d).
                    __m512d *c)
    ///< pointer to the sin function value (__m512d).
{
  *s = jbm_8xf64_sinwc (x);
  *c = jbm_8xf64_coswc (x);
}

/**
 * Function to calculate reduction to \f$2\,\pi\f$ in trigonometric functions
 * (__m512d).
 *
 * \return reduced vector (__m512d).
 */
static inline __m512d
jbm_8xf64_trig (const __m512d x,        ///< __m512d vector.
                __m512i *q)     ///< quadrant (__m512i).
{
  __m512d y;
  y = _mm512_roundscale_pd (_mm512_mul_pd (x, _mm512_set1_pd (1. / M_PI_2)),
                            _MM_FROUND_TO_NEAREST_INT);
  *q = _mm512_cvtpd_epi64 (y);
  return _mm512_fnmadd_pd (y, _mm512_set1_pd (M_PI_2), x);
}

/**
 * Function to calculate the function sin(x) from jbm_8xf64_sinwc and
 * jbm_8xf64_coswc approximations.
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_sin (const __m512d x) ///< __m512d vector.
{
  const __m512d pi2 = _mm512_set1_pd (2. * M_PI);
  __m512d y, s;
  y = jbm_8xf64_mod (x, pi2);
  s = jbm_8xf64_sinwc (_mm512_sub_pd (y, pi2));
  s = _mm512_mask_mov_pd (s,
                          _mm512_cmp_pd_mask (y, _mm512_set1_pd (7. * M_PI_4),
                                              _CMP_LT_OS),
                          jbm_8xf64_opposite
                          (jbm_8xf64_coswc
                           (_mm512_sub_pd (_mm512_set1_pd (3. * M_PI_2), y))));
  s =
    _mm512_mask_mov_pd (s, _mm512_cmp_pd_mask (y, _mm512_set1_pd (5. * M_PI_4),
                                               _CMP_LT_OS),
                        jbm_8xf64_sinwc (_mm512_sub_pd (_mm512_set1_pd (M_PI),
                                                        y)));
  s =
    _mm512_mask_mov_pd (s, _mm512_cmp_pd_mask (y, _mm512_set1_pd (3. * M_PI_4),
                                               _CMP_LT_OS),
                        jbm_8xf64_coswc (_mm512_sub_pd (_mm512_set1_pd (M_PI_2),
                                                        y)));
  return _mm512_mask_mov_pd (s, _mm512_cmp_pd_mask (y, _mm512_set1_pd (M_PI_4),
                                                    _CMP_LT_OS),
                             jbm_8xf64_sinwc (y));
}

/**
 * Function to calculate the function cos(x) from jbm_8xf64_sinwc and
 * jbm_8xf64_coswc approximations (__m512).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_cos (const __m512d x) ///< __m512d vector.
{
  const __m512d pi2 = _mm512_set1_pd (2. * M_PI);
  __m512d y, c;
  y = jbm_8xf64_mod (x, pi2);
  c = _mm512_mask_blend_pd (_mm512_cmp_pd_mask (y, _mm512_set1_pd (7. * M_PI_4),
                                                _CMP_LT_OS),
                            jbm_8xf64_coswc (_mm512_sub_pd (y, pi2)),
                            jbm_8xf64_sinwc
                            (_mm512_sub_pd (y, _mm512_set1_pd (3. * M_PI_2))));
  c = _mm512_mask_mov_pd (c,
                          _mm512_cmp_pd_mask (y, _mm512_set1_pd (5. * M_PI_4),
                                              _CMP_LT_OS),
                          jbm_8xf64_opposite
                          (jbm_8xf64_coswc
                           (_mm512_sub_pd (_mm512_set1_pd (M_PI), y))));
  c = _mm512_mask_mov_pd (c,
                          _mm512_cmp_pd_mask (y, _mm512_set1_pd (3. * M_PI_4),
                                              _CMP_LT_OS),
                          jbm_8xf64_sinwc (_mm512_sub_pd
                                           (_mm512_set1_pd (M_PI_2), y)));
  return _mm512_mask_mov_pd (c, _mm512_cmp_pd_mask (y, _mm512_set1_pd (M_PI_4),
                                                    _CMP_LT_OS),
                             jbm_8xf64_coswc (y));
}

/**
 * Function to calculate the functions sin(x) and cos(x) from jbm_8xf64_sinwc
 * and jbm_8xf64_coswc approximations (__m512d).
 */
static inline void
jbm_8xf64_sincos (const __m512d x,
                  ///< __m512d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  __m512d *s,
                  ///< pointer to the sin function value (__m512d).
                  __m512d *c)
                  ///< pointer to the cos function value (__m512d).
{
  const __m512d pi2 = _mm512_set1_pd (2. * M_PI);
  const __m512d z = _mm512_setzero_pd ();
  __m512d y, s1, c1, s2, c2;
  __mmask16 m;
  y = jbm_8xf64_mod (x, pi2);
  jbm_8xf64_sincoswc (_mm512_sub_pd (y, pi2), &s1, &c1);
  jbm_8xf64_sincoswc (_mm512_sub_pd (y, _mm512_set1_pd (3. * M_PI_2)), &c2,
                      &s2);
  m = _mm512_cmp_pd_mask (y, _mm512_set1_pd (7. * M_PI_4), _CMP_LT_OS);
  s1 = _mm512_mask_mov_pd (s1, m, _mm512_sub_pd (z, s2));
  c1 = _mm512_mask_mov_pd (c1, m, c2);
  jbm_8xf64_sincoswc (_mm512_sub_pd (_mm512_set1_pd (M_PI), y), &s2, &c2);
  m = _mm512_cmp_pd_mask (y, _mm512_set1_pd (5. * M_PI_4), _CMP_LT_OS);
  s1 = _mm512_mask_mov_pd (s1, m, s2);
  c1 = _mm512_mask_mov_pd (c1, m, _mm512_sub_pd (z, c2));
  jbm_8xf64_sincoswc (_mm512_sub_pd (_mm512_set1_pd (M_PI_2), y), &c2, &s2);
  m = _mm512_cmp_pd_mask (y, _mm512_set1_pd (3. * M_PI_4), _CMP_LT_OS);
  s1 = _mm512_mask_mov_pd (s1, m, s2);
  c1 = _mm512_mask_mov_pd (c1, m, c2);
  jbm_8xf64_sincoswc (y, &s2, &c2);
  m = _mm512_cmp_pd_mask (y, _mm512_set1_pd (M_PI_4), _CMP_LT_OS);
  *s = _mm512_mask_mov_pd (s1, m, s2);
  *c = _mm512_mask_mov_pd (c1, m, c2);
}

/**
 * Function to calculate the function tan(x) from jbm_8xf64_sinwc and
 * jbm_8xf64_coswc approximations.
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_tan (const __m512d x) ///< __m512d vector.
{
  __m512d s, c;
  jbm_8xf64_sincos (x, &s, &c);
  return _mm512_div_pd (s, c);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [-1,1] (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_atanwc (const __m512d x)
                  ///< __m512d vector \f$\in\left[0,\frac12\right]\f$.
{
  return
    _mm512_mul_pd (x,
                   jbm_8xf64_rational_11_5 (jbm_8xf64_sqr (x), K_ATANWC_F64));
}

/**
 * Function to calculate the function atan(x) using the jbm_8xf64_atanwc
 * function (__m512d).
 *
 * \return function value (__m512d in [-pi/2,pi/2]).
 */
static inline __m512d
jbm_8xf64_atan (const __m512d x)        ///< double number.
{
  __m512d f, ax;
  __mmask16 m;
  ax = jbm_8xf64_abs (x);
  m = _mm512_cmp_pd_mask (ax, _mm512_set1_pd (1.), _CMP_GT_OS);
  ax = _mm512_mask_mov_pd (ax, m, jbm_8xf64_reciprocal (ax));
  f = jbm_8xf64_atanwc (ax);
  f = _mm512_mask_mov_pd (f, m, _mm512_sub_pd (_mm512_set1_pd (M_PI_2), f));
  return jbm_8xf64_copysign (f, x);

}

/**
 * Function to calculate the function atan2(y,x) using the jbm_8xf64_atan
 * function (__m512d).
 *
 * \return function value (__m512d in [-pi,pi]).
 */
static inline __m512d
jbm_8xf64_atan2 (const __m512d y,       ///< __m512d y component.
                 const __m512d x)       ///< __m512d x component.
{
  const __m512d pi = _mm512_set1_pd (M_PI);
  const __m512d z = _mm512_setzero_pd ();
  __m512d f, g;
  f = jbm_8xf64_atan (_mm512_div_pd (y, x));
  g = _mm512_add_pd (f, jbm_8xf64_copysign (pi, y));
  return _mm512_mask_mov_pd (f, _mm512_cmp_pd_mask (x, z, _CMP_LT_OS), g);
}

/**
 * Function to calculate the function asin(x) using the jbm_8xf64_atan function
 * (__m512d).
 *
 * \return function value (__m512d in [-pi/2,pi/2]).
 */
static inline __m512d
jbm_8xf64_asin (const __m512d x)        ///< __m512d number.
{
  return
    jbm_8xf64_atan (_mm512_div_pd
                    (x,
                     _mm512_sqrt_pd (_mm512_fnmadd_pd
                                     (x, x, _mm512_set1_pd (1.)))));
}

/**
 * Function to calculate the function acos(x) using the jbm_8xf64_atan function
 * (__m512d).
 *
 * \return function value (__m512d in [0,pi]).
 */
static inline __m512d
jbm_8xf64_acos (const __m512d x)        ///< __m512d number.
{
  __m512d f;
  f =
    jbm_8xf64_atan (_mm512_div_pd
                    (_mm512_sqrt_pd
                     (_mm512_fnmadd_pd (x, x, _mm512_set1_pd (1.))), x));
  return _mm512_mask_mov_pd (f, _mm512_cmp_pd_mask (x, _mm512_setzero_pd (),
                                                    _CMP_LT_OS),
                             _mm512_add_pd (f, _mm512_set1_pd (M_PI)));
}

/**
 * Function to calculate the function sinh(x)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_sinh (const __m512d x)        ///< __m512d number.
{
  __m512d f;
  f = jbm_8xf64_exp (x);
  return _mm512_mul_pd (_mm512_set1_pd (0.5),
                        _mm512_sub_pd (f, jbm_8xf64_reciprocal (f)));
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_cosh (const __m512d x)        ///< __m512d number.
{
  __m512d f;
  f = jbm_8xf64_exp (x);
  return _mm512_mul_pd (_mm512_set1_pd (0.5),
                        _mm512_add_pd (f, jbm_8xf64_reciprocal (f)));
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_tanh (const __m512d x)        ///< __m512d number.
{
  __m512d f, fi;
  f = jbm_8xf64_exp (x);
  fi = jbm_8xf64_reciprocal (f);
  f = _mm512_div_pd (_mm512_sub_pd (f, fi), _mm512_add_pd (f, fi));
  f = _mm512_mask_mov_pd
    (f, _mm512_cmp_pd_mask (x, _mm512_set1_pd (JBM_DBL_MAX_E_EXP), _CMP_GT_OS),
     _mm512_set1_pd (1.));
  return _mm512_mask_mov_pd
    (f, _mm512_cmp_pd_mask (x, _mm512_set1_pd (-JBM_DBL_MAX_E_EXP), _CMP_LT_OS),
     _mm512_set1_pd (-1.));
}

/**
 * Function to calculate the function asinh(x)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_asinh (const __m512d x)       ///< __m512d number.
{
  return
    jbm_8xf64_log (_mm512_add_pd
                   (x,
                    _mm512_sqrt_pd (_mm512_fmadd_pd
                                    (x, x, _mm512_set1_pd (1.)))));
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_acosh (const __m512d x)       ///< __m512d number.
{
  return
    jbm_8xf64_log (_mm512_add_pd
                   (x,
                    _mm512_sqrt_pd (_mm512_fmsub_pd
                                    (x, x, _mm512_set1_pd (1.)))));
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_atanh (const __m512d x)       ///< __m512d number.
{
  __m512d u;
  u = _mm512_set1_pd (1.);
  return _mm512_mul_pd (_mm512_set1_pd (0.5),
                        jbm_8xf64_log (_mm512_div_pd (_mm512_add_pd (u, x),
                                                      _mm512_sub_pd (u, x))));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] (__m512d)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_erfwc (const __m512d x)
    ///< __m512d vector \f$\in\left[-1,1\right]\f$.
{
  return
    _mm512_mul_pd (x, jbm_8xf64_rational_9_4 (jbm_8xf64_sqr (x), K_ERFWC_F64));
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ (__m512d)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_erfcwc (const __m512d x)
    ///< __m512d vector \f$\in\left[1,\infty\right]\f$.
{
  __m512d f, x2;
  x2 = jbm_8xf64_sqr (x);
  f = _mm512_mul_pd (jbm_8xf64_rational_16_8 (jbm_8xf64_reciprocal (x),
                                              K_ERFCWC_F64),
                     _mm512_div_pd (x, jbm_8xf64_exp (x2)));
  return
    _mm512_mask_mov_pd (f, _mm512_cmp_pd_mask (x,
                                               _mm512_set1_pd (K_ERFC_MAX_F64),
                                               _CMP_GT_OS),
                        _mm512_setzero_pd ());
}

/**
 * Function to calculate the function erf(x) using jbm_8xf64_erfwc and
 * jbm_8xf64_erfcwc
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_erf (const __m512d x) ///< __m512d vector.
{
  const __m512d u = _mm512_set1_pd (1.);
  __m512d ax;
  ax = jbm_8xf64_abs (x);
  return
    _mm512_mask_blend_pd (_mm512_cmp_pd_mask (ax, u, _CMP_LT_OS),
                          jbm_8xf64_copysign (_mm512_sub_pd (u,
                                                             jbm_8xf64_erfcwc
                                                             (ax)), x),
                          jbm_8xf64_erfwc (x));
}

/**
 * Function to calculate the function erfc(x) using jbm_8xf64_erfwc and
 * jbm_8xf64_erfcwc
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_8xf64_erfc (const __m512d x)        ///< __m512d vector.
{
  const __m512d u2 = _mm512_set1_pd (2.);
  const __m512d u = _mm512_set1_pd (1.);
  __m512d ax, cwc, wc;
  ax = jbm_8xf64_abs (x);
  cwc = jbm_8xf64_erfcwc (ax);
  wc = _mm512_sub_pd (u, jbm_8xf64_erfwc (x));
  return
    _mm512_mask_mov_pd
    (_mm512_mask_mov_pd
     (wc, _mm512_cmp_pd_mask (ax, u, _CMP_GT_OS), _mm512_sub_pd (u2, cwc)),
     _mm512_cmp_pd_mask (x, u, _CMP_GT_OS), cwc);
}

/**
 * Function to calculate the solution of a __m512d vector of reduced quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return __m512d vector of solution values.
 */
static inline __m512d
jbm_solve_quadratic_reduced_8xf64 (__m512d a,
///< __m512d vector of 1st order coefficient of the equations.
                                   __m512d b,
///< __m512d vector of 0th order coefficient of the equations.
                                   const __m512d x1,
///< __m512d vector of left limits of the solution intervals.
                                   const __m512d x2)
///< __m512d vector of right limits of the solution intervals.
{
  __m512d k1, k2;
  k1 = _mm512_set1_pd (-0.5);
  a = _mm512_mul_pd (a, k1);
  b = _mm512_sqrt_pd (_mm512_sub_pd (jbm_8xf64_sqr (a), b));
  k1 = _mm512_add_pd (a, b);
  k2 = _mm512_sub_pd (a, b);
  k1 = _mm512_mask_mov_pd (k1, _mm512_cmp_pd_mask (k1, x1, _CMP_LT_OS), k2);
  return _mm512_mask_mov_pd (k1, _mm512_cmp_pd_mask (k1, x2, _CMP_GT_OS), k2);
}

/**
 * Function to calculate the solution of a __m512d vector of quadratic equations
 * in an interval \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^2+b\,x+c=0\f$.
 *
 * \return __m512d vector of solution values.
 */
static inline __m512d
jbm_8xf64_solve_quadratic (const __m512d a,
///< __m512d vector of 2nd order coefficient of the equations.
                           const __m512d b,
///< __m512d vector of 1st order coefficient of the equations.
                           const __m512d c,
///< __m512d vector of 0th order coefficient of the equations.
                           const __m512d x1,
///< __m512d vector of left limits of the solution intervals.
                           const __m512d x2)
///< __m512d vector of right limits of the solution intervals.
{
  __m512d k1, k2;
  k1 = jbm_solve_quadratic_reduced_8xf64 (_mm512_div_pd (b, a),
                                          _mm512_div_pd (c, a), x1, x2);
  k2 = _mm512_div_pd (jbm_8xf64_opposite (c), b);
  return _mm512_mask_mov_pd (k1, jbm_8xf64_small (a), k2);
}

/**
 * Function to calculate the solution of a __m512d vector of reduced cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^3+a\,x^2+b\,x+c=0\f$.
 *
 * \return __m512d vector of solution values.
 */
static inline __m512d
jbm_solve_cubic_reduced_8xf64 (const __m512d a,
                               ///< 2nd order coefficient of the equation.
                               const __m512d b,
                               ///< 1st order coefficient of the equation.
                               const __m512d c,
                               ///< 0th order coefficient of the equation.
                               const __m512d x1,
                               ///< left limit of the solution interval.
                               const __m512d x2)
    ///< right limit of the solution interval.
{
  __m512d a3, k0, k1, k2, k3, l0, l1, l2, l3, l4, l5, c2p_3, c_2, c_3;
  c2p_3 = _mm512_set1_pd (2. * M_PI / 3.);
  c_2 = _mm512_set1_pd (0.5);
  c_3 = _mm512_set1_pd (1. / 3.);
  a3 = _mm512_mul_pd (a, c_3);
  k0 = _mm512_mul_pd (a3, a3);
  k1 = _mm512_fmsub_pd (b, c_3, k0);
  k0 =
    _mm512_fmsub_pd (_mm512_fmsub_pd (b, a3, c), c_2, _mm512_mul_pd (a3, k0));
  k3 = _mm512_mul_pd (k1, _mm512_mul_pd (k1, k1));
  k2 = _mm512_fmadd_pd (k0, k0, k3);
  l1 = _mm512_sqrt_pd (jbm_8xf64_opposite (k1));
  l0 = _mm512_mul_pd (jbm_8xf64_acos (_mm512_div_pd (k0, k3)), c_3);
  l1 = _mm512_add_pd (l1, l1);
  l2 = _mm512_fmsub_pd (l1, jbm_8xf64_cos (k0), a3);
  l3 = _mm512_fmsub_pd (l1, jbm_8xf64_cos (_mm512_add_pd (l0, c2p_3)), a3);
  l3 = _mm512_mask_mov_pd (l3, _mm512_cmp_pd_mask (l2, x1, _CMP_LT_OS)
                           | _mm512_cmp_pd_mask (l2, x2, _CMP_GT_OS), l2);
  l4 = _mm512_fmsub_pd (l1, jbm_8xf64_cos (_mm512_sub_pd (l0, c2p_3)), a);
  l4 = _mm512_mask_mov_pd (l4, _mm512_cmp_pd_mask (l3, x1, _CMP_LT_OS)
                           | _mm512_cmp_pd_mask (l3, x2, _CMP_GT_OS), l3);
  k1 = _mm512_sqrt_pd (k2);
  l5 = _mm512_add_pd (k0, k1);
  l5 = jbm_8xf64_cbrt (k2);
  k0 = _mm512_sub_pd (k0, k1);
  l5 = _mm512_add_pd (l5, _mm512_sub_pd (jbm_8xf64_cbrt (k0), a3));
  return _mm512_mask_mov_pd (l4, _mm512_cmp_pd_mask (k2, _mm512_setzero_pd (),
                                                     _CMP_LT_OS), l5);

}

/**
 * Function to calculate the solution of a __m512d vector of cubic equations in
 * an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return __m512d vector of solution values.
 */
static inline __m512d
jbm_8xf64_solve_cubic (const __m512d a,
///< __m512d vector of 3rd order coefficient of the equations.
                       const __m512d b,
///< __m512d vector of 2nd order coefficient of the equations.
                       const __m512d c,
///< __m512d vector of 1st order coefficient of the equations.
                       const __m512d d,
///< __m512d vector of 0th order coefficient of the equations.
                       const __m512d x1,
///< __m512d vector of left limits of the solution intervals.
                       const __m512d x2)
///< __m512d vector of right limits of the solution intervals.
{
  return
    _mm512_mask_blend_pd (jbm_8xf64_small (a),
                          jbm_solve_cubic_reduced_8xf64 (_mm512_div_pd (b, a),
                                                         _mm512_div_pd (c, a),
                                                         _mm512_div_pd (d, a),
                                                         x1, x2),
                          jbm_8xf64_solve_quadratic (b, c, d, x1, x2));

}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_8xf64_flux_limiter_total (const __m512d d1 __attribute__((unused)),
                              ///< 1st flux limiter function parameter.
                              const __m512d d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm512_setzero_pd ();
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_8xf64_flux_limiter_null (const __m512d d1 __attribute__((unused)),
                             ///< 1st flux limiter function parameter.
                             const __m512d d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm512_set1_pd (1.);
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_8xf64_flux_limiter_centred (const __m512d d1,
                                ///< 1st flux limiter function parameter.
                                const __m512d d2)
    ///< 2nd flux limiter function parameter.
{
  return _mm512_mask_blend_pd (jbm_8xf64_small (d2),
                               _mm512_div_pd (d1, d2), _mm512_setzero_pd ());

}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_8xf64_flux_limiter_superbee (const __m512d d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m512d d2)
    ///< 2nd flux limiter function parameter.
{
  __m512d r;
  r = _mm512_div_pd (d1, d2);
  r = _mm512_max_pd (_mm512_min_pd (jbm_8xf64_dbl (r), _mm512_set1_pd (1.)),
                     _mm512_min_pd (r, _mm512_set1_pd (2.)));
  return _mm512_mask_mov_pd (_mm512_setzero_pd (),
                             _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                 _mm512_set1_pd (DBL_EPSILON),
                                                 _CMP_GT_OS), r);
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_8xf64_flux_limiter_minmod (const __m512d d1,
                               ///< 1st flux limiter function parameter.
                               const __m512d d2)
    ///< 2nd flux limiter function parameter.
{
  __m512d r;
  r = _mm512_min_pd (_mm512_div_pd (d1, d2), _mm512_set1_pd (1.));
  return _mm512_mask_mov_pd (_mm512_setzero_pd (),
                             _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                 _mm512_set1_pd (DBL_EPSILON),
                                                 _CMP_GT_OS), r);
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_8xf64_flux_limiter_VanLeer (const __m512d d1,
                                ///< 1st flux limiter function parameter.
                                const __m512d d2)
    ///< 2nd flux limiter function parameter.
{
  __m512d r, k;
  r = _mm512_div_pd (d1, d2);
  k = jbm_8xf64_abs (r);
  r = _mm512_div_pd (_mm512_add_pd (r, k),
                     _mm512_add_pd (_mm512_set1_pd (1.), k));
  return _mm512_mask_mov_pd (_mm512_setzero_pd (),
                             _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                 _mm512_set1_pd (DBL_EPSILON),
                                                 _CMP_GT_OS), r);
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_8xf64_flux_limiter_VanAlbada (const __m512d d1,
                                  ///< 1st flux limiter function parameter.
                                  const __m512d d2)
    ///< 2nd flux limiter function parameter.
{
  __m512d r, k;
  r = _mm512_div_pd (d1, d2);
  k = jbm_8xf64_sqr (r);
  r = _mm512_div_pd (_mm512_add_pd (r, k),
                     _mm512_add_pd (_mm512_set1_pd (1.), k));
  return _mm512_mask_mov_pd (_mm512_setzero_pd (),
                             _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                 _mm512_set1_pd (DBL_EPSILON),
                                                 _CMP_GT_OS), r);
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_8xf64_flux_limiter_minsuper (const __m512d d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m512d d2)
    ///< 2nd flux limiter function parameter.
{
  __m512d r;
  r = _mm512_min_pd (_mm512_div_pd (d1, d2), _mm512_set1_pd (2.));
  return _mm512_mask_mov_pd (_mm512_setzero_pd (),
                             _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                 _mm512_set1_pd (DBL_EPSILON),
                                                 _CMP_GT_OS), r);
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_8xf64_flux_limiter_supermin (const __m512d d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m512d d2)
    ///< 2nd flux limiter function parameter.
{
  __m512d r;
  r = _mm512_div_pd (d1, d2);
  r = _mm512_min_pd (jbm_8xf64_dbl (r), _mm512_set1_pd (1.));
  return _mm512_mask_mov_pd (_mm512_setzero_pd (),
                             _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                 _mm512_set1_pd (DBL_EPSILON),
                                                 _CMP_GT_OS), r);
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_8xf64_flux_limiter_monotonized_central (const __m512d d1,
///< 1st flux limiter function parameter.
                                            const __m512d d2)
///< 2nd flux limiter function parameter.
{
  __m512d r, rm;
  r = _mm512_div_pd (d1, d2);
  rm = _mm512_mul_pd (_mm512_set1_pd (0.5),
                      _mm512_add_pd (r, _mm512_set1_pd (1.)));
  rm = _mm512_mask_mov_pd (_mm512_set1_pd (2.),
                           _mm512_cmp_pd_mask (r, _mm512_set1_pd (3.),
                                               _CMP_LT_OS), rm);
  rm = _mm512_mask_mov_pd (rm, _mm512_cmp_pd_mask (r, _mm512_set1_pd (1. / 3.),
                                                   _CMP_GT_OS),
                           jbm_8xf64_dbl (r));
  return _mm512_mask_mov_pd (_mm512_setzero_pd (),
                             _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                 _mm512_set1_pd (DBL_EPSILON),
                                                 _CMP_GT_OS), r);
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_8xf64_flux_limiter_mean (const __m512d d1,
                             ///< 1st flux limiter function parameter.
                             const __m512d d2)
    ///< 2nd flux limiter function parameter.
{
  __m512d r;
  r = _mm512_mul_pd (_mm512_set1_pd (0.5),
                     _mm512_add_pd (_mm512_set1_pd (1.),
                                    _mm512_div_pd (d1, d2)));
  return _mm512_mask_mov_pd (_mm512_setzero_pd (),
                             _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                 _mm512_set1_pd (DBL_EPSILON),
                                                 _CMP_GT_OS), r);
}

/**
 * Function to do a flux limiter function (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_8xf64_flux_limiter (const __m512d d1,
                        ///< 1st flux limiter function parameter.
                        const __m512d d2,
                        ///< 2nd flux limiter function parameter.
                        unsigned int type)
    ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_8xf64_flux_limiter_total (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_8xf64_flux_limiter_null (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_8xf64_flux_limiter_centred (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_8xf64_flux_limiter_superbee (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_8xf64_flux_limiter_minmod (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_8xf64_flux_limiter_VanLeer (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_8xf64_flux_limiter_VanAlbada (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_8xf64_flux_limiter_minsuper (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_8xf64_flux_limiter_supermin (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_8xf64_flux_limiter_monotonized_central (d1, d2);
    }
  return jbm_8xf64_flux_limiter_mean (d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (__m512d).
 *
 * \return __m512d vector of integral values.
 */
static inline __m512d
jbm_8xf64_integral (__m512d (*f) (__m512d),
                    ///< pointer to the function to integrate.
                    const __m512d x1,   ///< left limit of the interval.
                    const __m512d x2)   ///< right limit of the interval.
{
  __m512d k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  __m512d k2, f1, f2;
#endif
  unsigned int i;
  h = _mm512_set1_pd (0.5);
  dx = _mm512_mul_pd (h, _mm512_sub_pd (x2, x1));
  x = _mm512_mul_pd (h, _mm512_add_pd (x2, x1));
  k = _mm512_set1_pd (JBM_INTEGRAL_GAUSS_A_F64[0]);
  k = _mm512_mul_pd (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = _mm512_set1_pd (JBM_INTEGRAL_GAUSS_B_F64[i]);
      k2 = _mm512_mul_pd (k2, dx);
      f1 = f (_mm512_sub_pd (x, k2));
      f2 = f (_mm512_add_pd (x, k2));
      h = _mm512_set1_pd (JBM_INTEGRAL_GAUSS_A_F64[i]);
      k = _mm512_fmadd_pd (h, _mm512_add_pd (f1, f2), k);
    }
#endif
  k = _mm512_mul_pd (k, dx);
  return k;
}

/**
 * Function to calculate the root square of a float array.
 */
static inline void
jbm_array_f32_sqrt (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                _mm512_sqrt_ps, _mm256_sqrt_ps, _mm_sqrt_ps, sqrtf);
}

/**
 * Function to calculate the double of a float array.
 */
static inline void
jbm_array_f32_dbl (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_dbl, jbm_8xf32_dbl, jbm_4xf32_dbl, jbm_f32_dbl);
}

/**
 * Function to calculate the square of a float array.
 */
static inline void
jbm_array_f32_sqr (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_sqr, jbm_8xf32_sqr, jbm_4xf32_sqr, jbm_f32_sqr);
}

/**
 * Function to calculate the square of a float array.
 */
static inline void
jbm_array_f32_opposite (float *restrict xr,     ///< result float array.
                        const float *restrict xd,       ///< data float array.
                        const unsigned int n)   ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_opposite, jbm_8xf32_opposite, jbm_4xf32_opposite,
                jbm_f32_opposite);
}

/**
 * Function to calculate the square of a float array.
 */
static inline void
jbm_array_f32_reciprocal (float *restrict xr,   ///< result float array.
                          const float *restrict xd,     ///< data float array.
                          const unsigned int n) ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_reciprocal, jbm_8xf32_reciprocal,
                jbm_4xf32_reciprocal, jbm_f32_reciprocal);
}

/**
 * Function to calculate the abs function of a float array.
 */
static inline void
jbm_array_f32_abs (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_abs, jbm_8xf32_abs, jbm_4xf32_abs, jbm_f32_abs);
}

/**
 * Function to calculate the cbrt function of a float array.
 */
static inline void
jbm_array_f32_cbrt (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_cbrt, jbm_8xf32_cbrt, jbm_4xf32_cbrt, jbm_f32_cbrt);
}

/**
 * Function to calculate the exp2 function a float array.
 */
static inline void
jbm_array_f32_exp2 (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_exp2, jbm_8xf32_exp2, jbm_4xf32_exp2, jbm_f32_exp2);
}

/**
 * Function to calculate the exp function a float array.
 */
static inline void
jbm_array_f32_exp (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_exp, jbm_8xf32_exp, jbm_4xf32_exp, jbm_f32_exp);
}

/**
 * Function to calculate the exp10 function a float array.
 */
static inline void
jbm_array_f32_exp10 (float *restrict xr,        ///< result float array.
                     const float *restrict xd,  ///< data float array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_exp10, jbm_8xf32_exp10, jbm_4xf32_exp10,
                jbm_f32_exp10);
}

/**
 * Function to calculate the expm1 function a float array.
 */
static inline void
jbm_array_f32_expm1 (float *restrict xr,        ///< result float array.
                     const float *restrict xd,  ///< data float array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_expm1, jbm_8xf32_expm1, jbm_4xf32_expm1,
                jbm_f32_expm1);
}

/**
 * Function to calculate the log2 function a float array.
 */
static inline void
jbm_array_f32_log2 (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_log2, jbm_8xf32_log2, jbm_4xf32_log2, jbm_f32_log2);
}

/**
 * Function to calculate the log function a float array.
 */
static inline void
jbm_array_f32_log (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_log, jbm_8xf32_log, jbm_4xf32_log, jbm_f32_log);
}

/**
 * Function to calculate the log10 function a float array.
 */
static inline void
jbm_array_f32_log10 (float *restrict xr,        ///< result float array.
                     const float *restrict xd,  ///< data float array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_log10, jbm_8xf32_log10, jbm_4xf32_log10,
                jbm_f32_log10);
}

/**
 * Function to calculate the sin function a float array.
 */
static inline void
jbm_array_f32_sin (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_sin, jbm_8xf32_sin, jbm_4xf32_sin, jbm_f32_sin);
}

/**
 * Function to calculate the cos function a float array.
 */
static inline void
jbm_array_f32_cos (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_cos, jbm_8xf32_cos, jbm_4xf32_cos, jbm_f32_cos);
}

/**
 * Function to calculate the tan function a float array.
 */
static inline void
jbm_array_f32_tan (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_tan, jbm_8xf32_tan, jbm_4xf32_tan, jbm_f32_tan);
}

/**
 * Function to calculate the asin function a float array.
 */
static inline void
jbm_array_f32_asin (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_asin, jbm_8xf32_asin, jbm_4xf32_asin, jbm_f32_asin);
}

/**
 * Function to calculate the acos function a float array.
 */
static inline void
jbm_array_f32_acos (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_acos, jbm_8xf32_acos, jbm_4xf32_acos, jbm_f32_acos);
}

/**
 * Function to calculate the atan function a float array.
 */
static inline void
jbm_array_f32_atan (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_atan, jbm_8xf32_atan, jbm_4xf32_atan, jbm_f32_atan);
}

/**
 * Function to calculate the sinh function a float array.
 */
static inline void
jbm_array_f32_sinh (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_sinh, jbm_8xf32_sinh, jbm_4xf32_sinh, jbm_f32_sinh);
}

/**
 * Function to calculate the cosh function a float array.
 */
static inline void
jbm_array_f32_cosh (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_cosh, jbm_8xf32_cosh, jbm_4xf32_cosh, jbm_f32_cosh);
}

/**
 * Function to calculate the tanh function a float array.
 */
static inline void
jbm_array_f32_tanh (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_tanh, jbm_8xf32_tanh, jbm_4xf32_tanh, jbm_f32_tanh);
}

/**
 * Function to calculate the asinh function a float array.
 */
static inline void
jbm_array_f32_asinh (float *restrict xr,        ///< result float array.
                     const float *restrict xd,  ///< data float array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_asinh, jbm_8xf32_asinh, jbm_4xf32_asinh,
                jbm_f32_asinh);
}

/**
 * Function to calculate the acosh function a float array.
 */
static inline void
jbm_array_f32_acosh (float *restrict xr,        ///< result float array.
                     const float *restrict xd,  ///< data float array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_acosh, jbm_8xf32_acosh, jbm_4xf32_acosh,
                jbm_f32_acosh);
}

/**
 * Function to calculate the atanh function a float array.
 */
static inline void
jbm_array_f32_atanh (float *restrict xr,        ///< result float array.
                     const float *restrict xd,  ///< data float array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_atanh, jbm_8xf32_atanh, jbm_4xf32_atanh,
                jbm_f32_atanh);
}

/**
 * Function to calculate the erf function a float array.
 */
static inline void
jbm_array_f32_erf (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_erf, jbm_8xf32_erf, jbm_4xf32_erf, jbm_f32_erf);
}

/**
 * Function to calculate the erfc function a float array.
 */
static inline void
jbm_array_f32_erfc (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps, _mm_storeu_ps,
                jbm_16xf32_erfc, jbm_8xf32_erfc, jbm_4xf32_erfc, jbm_f32_erfc);
}

/**
 * Function to calculate the sum of the elements of a float array.
 *
 * \return the sum value.
 */
static inline float
jbm_array_f32_sum (const float *x,      ///< float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_REDUCE_OP (x, n, __m512, __m256, __m128, float, _mm512_loadu_ps,
                       _mm256_loadu_ps, _mm_loadu_ps, _mm512_add_ps,
                       _mm256_add_ps, _mm_add_ps, JBM_ADD,
                       jbm_16xf32_reduce_add, jbm_8xf32_reduce_add,
                       jbm_4xf32_reduce_add, 0.f);
}

/**
 * Function to find the highest element of a float array.
 *
 * \return the highest value.
 */
static inline float
jbm_array_f32_reduce_max (const float *x,       ///< float array.
                          const unsigned int n) ///< number of array elements.
{
  JBM_ARRAY_REDUCE_OP (x, n, __m512, __m256, __m128, float, _mm512_loadu_ps,
                       _mm256_loadu_ps, _mm_loadu_ps, _mm512_max_ps,
                       _mm256_max_ps, _mm_max_ps, fmaxf, jbm_16xf32_reduce_max,
                       jbm_8xf32_reduce_max, jbm_4xf32_reduce_max, -INFINITY);
}

/**
 * Function to find the lowest element of a float array.
 *
 * \return the lowest value.
 */
static inline float
jbm_array_f32_reduce_min (const float *x,       ///< float array.
                          const unsigned int n) ///< number of array elements.
{
  JBM_ARRAY_REDUCE_OP (x, n, __m512, __m256, __m128, float, _mm512_loadu_ps,
                       _mm256_loadu_ps, _mm_loadu_ps, _mm512_min_ps,
                       _mm256_min_ps, _mm_min_ps, fminf, jbm_16xf32_reduce_min,
                       jbm_8xf32_reduce_min, jbm_4xf32_reduce_min, INFINITY);
}

/**
 * Function to find the highest and the lowest elements of a float array.
 */
static inline void
jbm_array_f32_reduce_maxmin (const float *x,    ///< float array.
                             float *max,        ///< the highest value.
                             float *min,        ///< the lowest value.
                             const unsigned int n)
                             ///< number of array elements.
{
  JBM_ARRAY_MAXMIN (x, n, __m512, __m256, __m128, float, _mm512_loadu_ps,
                    _mm256_loadu_ps, _mm_loadu_ps, _mm512_max_ps, _mm256_max_ps,
                    _mm_max_ps, fmaxf, _mm512_min_ps, _mm256_min_ps, _mm_min_ps,
                    fmin, jbm_16xf32_reduce_max, jbm_8xf32_reduce_max,
                    jbm_4xf32_reduce_max, jbm_16xf32_reduce_min,
                    jbm_8xf32_reduce_min, jbm_4xf32_reduce_min, mx, mn);
  *max = mx, *min = mn;
}

/**
 * Function to add 1 float array + 1 number.
 */
static inline void
jbm_array_f32_add1 (float *restrict xr, ///< result float array.
                    const float *restrict x1,   ///< addend float array.
                    const float x2,     ///< addend float number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m512, __m256, __m128, float, _mm512_loadu_ps,
                 _mm256_loadu_ps, _mm_loadu_ps, _mm512_storeu_ps,
                 _mm256_storeu_ps, _mm_storeu_ps, _mm512_set1_ps,
                 _mm256_set1_ps, _mm_set1_ps, _mm512_add_ps, _mm256_add_ps,
                 _mm_add_ps, JBM_ADD);
}

/**
 * Function to subtract 1 float array + 1 number.
 */
static inline void
jbm_array_f32_sub1 (float *restrict xr, ///< result float array.
                    const float *restrict x1,   ///< minuend float array.
                    const float x2,     ///< subtrahend float number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m512, __m256, __m128, float, _mm512_loadu_ps,
                 _mm256_loadu_ps, _mm_loadu_ps, _mm512_storeu_ps,
                 _mm256_storeu_ps, _mm_storeu_ps, _mm512_set1_ps,
                 _mm256_set1_ps, _mm_set1_ps, _mm512_sub_ps, _mm256_sub_ps,
                 _mm_sub_ps, JBM_SUB);
}

/**
 * Function to multiply a float array by a float number.
 */
static inline void
jbm_array_f32_mul1 (float *restrict xr, ///< result float array.
                    const float *restrict x1,   ///< multiplier float array.
                    const float x2,     ///< multiplicand float number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m512, __m256, __m128, float, _mm512_loadu_ps,
                 _mm256_loadu_ps, _mm_loadu_ps, _mm512_storeu_ps,
                 _mm256_storeu_ps, _mm_storeu_ps, _mm512_set1_ps,
                 _mm256_set1_ps, _mm_set1_ps, _mm512_mul_ps, _mm256_mul_ps,
                 _mm_mul_ps, JBM_MUL);
}

/**
 * Function to divide a float array by a float number.
 */
static inline void
jbm_array_f32_div1 (float *restrict xr, ///< result float array.
                    const float *restrict x1,   ///< dividend float array.
                    const float x2,     ///< divisor float number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m512, __m256, __m128, float, _mm512_loadu_ps,
                 _mm256_loadu_ps, _mm_loadu_ps, _mm512_storeu_ps,
                 _mm256_storeu_ps, _mm_storeu_ps, _mm512_set1_ps,
                 _mm256_set1_ps, _mm_set1_ps, _mm512_div_ps, _mm256_div_ps,
                 _mm_div_ps, JBM_DIV);
}

/**
 * Function to calculate the maximum between 1 float array + 1 number.
 */
static inline void
jbm_array_f32_max1 (float *restrict xr, ///< result float array.
                    const float *restrict x1,   ///< float array.
                    const float x2,     ///< float number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m512, __m256, __m128, float, _mm512_loadu_ps,
                 _mm256_loadu_ps, _mm_loadu_ps, _mm512_storeu_ps,
                 _mm256_storeu_ps, _mm_storeu_ps, _mm512_set1_ps,
                 _mm256_set1_ps, _mm_set1_ps, _mm512_max_ps, _mm256_max_ps,
                 _mm_max_ps, fmaxf);
}

/**
 * Function to calculate the minimum between 1 float array + 1 number.
 */
static inline void
jbm_array_f32_min1 (float *restrict xr, ///< result float array.
                    const float *restrict x1,   ///< float array.
                    const float x2,     ///< float number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m512, __m256, __m128, float, _mm512_loadu_ps,
                 _mm256_loadu_ps, _mm_loadu_ps, _mm512_storeu_ps,
                 _mm256_storeu_ps, _mm_storeu_ps, _mm512_set1_ps,
                 _mm256_set1_ps, _mm_set1_ps, _mm512_min_ps, _mm256_min_ps,
                 _mm_min_ps, fminf);
}

/**
 * Function to calculate the module between 1 float array + 1 number.
 */
static inline void
jbm_array_f32_mod1 (float *restrict xr, ///< result float array.
                    const float *restrict x1,   ///< float array.
                    const float x2,     ///< float number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m512, __m256, __m128, float, _mm512_loadu_ps,
                 _mm256_loadu_ps, _mm_loadu_ps, _mm512_storeu_ps,
                 _mm256_storeu_ps, _mm_storeu_ps, _mm512_set1_ps,
                 _mm256_set1_ps, _mm_set1_ps, jbm_16xf32_mod, jbm_8xf32_mod,
                 jbm_4xf32_mod, jbm_f32_mod);
}

/**
 * Function to calculate the pow function between 1 float array + 1 number.
 */
static inline void
jbm_array_f32_pow1 (float *restrict xr, ///< result float array.
                    const float *restrict x1,   ///< float array.
                    const float x2,     ///< float number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m512, __m256, __m128, float, _mm512_loadu_ps,
                 _mm256_loadu_ps, _mm_loadu_ps, _mm512_storeu_ps,
                 _mm256_storeu_ps, _mm_storeu_ps, _mm512_set1_ps,
                 _mm256_set1_ps, _mm_set1_ps, jbm_16xf32_pow, jbm_8xf32_pow,
                 jbm_4xf32_pow, jbm_f32_pow);
}

/**
 * Function to add 2 float arrays.
 */
static inline void
jbm_array_f32_add (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< 1st addend float array.
                   const float *restrict x2,    ///< 2nd addend float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                 _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps,
                 _mm_storeu_ps, _mm512_add_ps, _mm256_add_ps, _mm_add_ps,
                 JBM_ADD);
}

/**
 * Function to subtract 2 float arrays.
 */
static inline void
jbm_array_f32_sub (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< minuend float array.
                   const float *restrict x2,    ///< subtrahend float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                 _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps,
                 _mm_storeu_ps, _mm512_sub_ps, _mm256_sub_ps, _mm_sub_ps,
                 JBM_SUB);
}

/**
 * Function to multiply 2 float arrays.
 */
static inline void
jbm_array_f32_mul (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< multiplier float array.
                   const float *restrict x2,    ///< multiplicand float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                 _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps,
                 _mm_storeu_ps, _mm512_mul_ps, _mm256_mul_ps, _mm_mul_ps,
                 JBM_MUL);
}

/**
 * Function to divide 2 float arrays.
 */
static inline void
jbm_array_f32_div (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< dividend float array.
                   const float *restrict x2,    ///< divisor float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                 _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps,
                 _mm_storeu_ps, _mm512_div_ps, _mm256_div_ps, _mm_div_ps,
                 JBM_DIV);
}

/**
 * Function to calculate the maximum in 2 float arrays.
 */
static inline void
jbm_array_f32_max (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< 1st float array.
                   const float *restrict x2,    ///< 2nd float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                 _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps,
                 _mm_storeu_ps, _mm512_max_ps, _mm256_max_ps, _mm_max_ps, fmax);
}

/**
 * Function to calculate the minimum in 2 float arrays.
 */
static inline void
jbm_array_f32_min (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< 1st float array.
                   const float *restrict x2,    ///< 2nd float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                 _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps,
                 _mm_storeu_ps, _mm512_min_ps, _mm256_min_ps, _mm_min_ps, fmin);
}

/**
 * Function to calculate the module in 2 float arrays.
 */
static inline void
jbm_array_f32_mod (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< 1st float array.
                   const float *restrict x2,    ///< 2nd float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                 _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps,
                 _mm_storeu_ps, jbm_16xf32_mod, jbm_8xf32_mod, jbm_4xf32_mod,
                 jbm_f32_mod);
}

/**
 * Function to do the pow function in 2 float arrays.
 */
static inline void
jbm_array_f32_pow (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< 1st float array.
                   const float *restrict x2,    ///< 2nd float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, _mm512_loadu_ps, _mm256_loadu_ps,
                 _mm_loadu_ps, _mm512_storeu_ps, _mm256_storeu_ps,
                 _mm_storeu_ps, jbm_16xf32_pow, jbm_8xf32_pow, jbm_4xf32_pow,
                 jbm_f32_pow);
}

/**
 * Function to do the dot product of 2 float arrays.
 *
 * \return dot product (float).
 */
static inline float
jbm_array_f32_dot (const float *restrict x1,    ///< multiplier float array.
                   const float *restrict x2,    ///< multiplicand float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_DOT (x1, x2, n, __m512, __m256, __m128, float, _mm512_loadu_ps,
                 _mm256_loadu_ps, _mm_loadu_ps, _mm512_mul_ps, _mm256_mul_ps,
                 _mm_mul_ps, _mm512_add_ps, _mm256_add_ps, _mm_add_ps,
                 _mm512_fmadd_ps, _mm256_fmadd_ps, _mm_fmadd_ps,
                 jbm_16xf32_reduce_add, jbm_8xf32_reduce_add,
                 jbm_4xf32_reduce_add);
}

/**
 * Function to calculate the root square of a double array.
 */
static inline void
jbm_array_f64_sqrt (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                _mm512_sqrt_pd, _mm256_sqrt_pd, _mm_sqrt_pd, sqrt);
}

/**
 * Function to calculate the double of a double array.
 */
static inline void
jbm_array_f64_dbl (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_dbl, jbm_4xf64_dbl, jbm_2xf64_dbl, jbm_f64_dbl);
}

/**
 * Function to calculate the square of a double array.
 */
static inline void
jbm_array_f64_sqr (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_sqr, jbm_4xf64_sqr, jbm_2xf64_sqr, jbm_f64_sqr);
}

/**
 * Function to calculate the opposite of a double array.
 */
static inline void
jbm_array_f64_opposite (double *restrict xr,    ///< result double array.
                        const double *restrict xd,      ///< data double array.
                        const unsigned int n)   ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_opposite, jbm_4xf64_opposite, jbm_2xf64_opposite,
                jbm_f64_opposite);
}

/**
 * Function to calculate the reciprocal of a double array.
 */
static inline void
jbm_array_f64_reciprocal (double *restrict xr,  ///< result double array.
                          const double *restrict xd,    ///< data double array.
                          const unsigned int n) ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_reciprocal, jbm_4xf64_reciprocal,
                jbm_2xf64_reciprocal, jbm_f64_reciprocal);
}

/**
 * Function to calculate the abs function of a double array.
 */
static inline void
jbm_array_f64_abs (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_abs, jbm_4xf64_abs, jbm_2xf64_abs, jbm_f64_abs);
}

/**
 * Function to calculate the cbrt function of a double array.
 */
static inline void
jbm_array_f64_cbrt (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_cbrt, jbm_4xf64_cbrt, jbm_2xf64_cbrt, jbm_f64_cbrt);
}

/**
 * Function to calculate the exp2 function a double array.
 */
static inline void
jbm_array_f64_exp2 (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_exp2, jbm_4xf64_exp2, jbm_2xf64_exp2, jbm_f64_exp2);
}

/**
 * Function to calculate the exp function a double array.
 */
static inline void
jbm_array_f64_exp (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_exp, jbm_4xf64_exp, jbm_2xf64_exp, jbm_f64_exp);
}

/**
 * Function to calculate the exp10 function a double array.
 */
static inline void
jbm_array_f64_exp10 (double *restrict xr,       ///< result double array.
                     const double *restrict xd, ///< data double array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_exp10, jbm_4xf64_exp10, jbm_2xf64_exp10,
                jbm_f64_exp10);
}

/**
 * Function to calculate the expm1 function a double array.
 */
static inline void
jbm_array_f64_expm1 (double *restrict xr,       ///< result double array.
                     const double *restrict xd, ///< data double array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_expm1, jbm_4xf64_expm1, jbm_2xf64_expm1,
                jbm_f64_expm1);
}

/**
 * Function to calculate the log2 function a double array.
 */
static inline void
jbm_array_f64_log2 (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_log2, jbm_4xf64_log2, jbm_2xf64_log2, jbm_f64_log2);
}

/**
 * Function to calculate the log function a double array.
 */
static inline void
jbm_array_f64_log (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_log, jbm_4xf64_log, jbm_2xf64_log, jbm_f64_log);
}

/**
 * Function to calculate the log10 function a double array.
 */
static inline void
jbm_array_f64_log10 (double *restrict xr,       ///< result double array.
                     const double *restrict xd, ///< data double array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_log10, jbm_4xf64_log10, jbm_2xf64_log10,
                jbm_f64_log10);
}

/**
 * Function to calculate the sin function a double array.
 */
static inline void
jbm_array_f64_sin (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_sin, jbm_4xf64_sin, jbm_2xf64_sin, jbm_f64_sin);
}

/**
 * Function to calculate the cos function a double array.
 */
static inline void
jbm_array_f64_cos (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_cos, jbm_4xf64_cos, jbm_2xf64_cos, jbm_f64_cos);
}

/**
 * Function to calculate the tan function a double array.
 */
static inline void
jbm_array_f64_tan (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_tan, jbm_4xf64_tan, jbm_2xf64_tan, jbm_f64_tan);
}

/**
 * Function to calculate the asin function a double array.
 */
static inline void
jbm_array_f64_asin (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_asin, jbm_4xf64_asin, jbm_2xf64_asin, jbm_f64_asin);
}

/**
 * Function to calculate the acos function a double array.
 */
static inline void
jbm_array_f64_acos (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_acos, jbm_4xf64_acos, jbm_2xf64_acos, jbm_f64_acos);
}

/**
 * Function to calculate the atan function a double array.
 */
static inline void
jbm_array_f64_atan (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_atan, jbm_4xf64_atan, jbm_2xf64_atan, jbm_f64_atan);
}

/**
 * Function to calculate the sinh function a double array.
 */
static inline void
jbm_array_f64_sinh (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_sinh, jbm_4xf64_sinh, jbm_2xf64_sinh, jbm_f64_sinh);
}

/**
 * Function to calculate the cosh function a double array.
 */
static inline void
jbm_array_f64_cosh (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_cosh, jbm_4xf64_cosh, jbm_2xf64_cosh, jbm_f64_cosh);
}

/**
 * Function to calculate the tanh function a double array.
 */
static inline void
jbm_array_f64_tanh (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_tanh, jbm_4xf64_tanh, jbm_2xf64_tanh, jbm_f64_tanh);
}

/**
 * Function to calculate the asinh function a double array.
 */
static inline void
jbm_array_f64_asinh (double *restrict xr,       ///< result double array.
                     const double *restrict xd, ///< data double array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_asinh, jbm_4xf64_asinh, jbm_2xf64_asinh,
                jbm_f64_asinh);
}

/**
 * Function to calculate the acosh function a double array.
 */
static inline void
jbm_array_f64_acosh (double *restrict xr,       ///< result double array.
                     const double *restrict xd, ///< data double array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_acosh, jbm_4xf64_acosh, jbm_2xf64_acosh,
                jbm_f64_acosh);
}

/**
 * Function to calculate the atanh function a double array.
 */
static inline void
jbm_array_f64_atanh (double *restrict xr,       ///< result double array.
                     const double *restrict xd, ///< data double array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_atanh, jbm_4xf64_atanh, jbm_2xf64_atanh,
                jbm_f64_atanh);
}

/**
 * Function to calculate the erf function a double array.
 */
static inline void
jbm_array_f64_erf (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_erf, jbm_4xf64_erf, jbm_2xf64_erf, jbm_f64_erf);
}

/**
 * Function to calculate the erfc function a double array.
 */
static inline void
jbm_array_f64_erfc (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                jbm_8xf64_erfc, jbm_4xf64_erfc, jbm_2xf64_erfc, jbm_f64_erfc);
}

/**
 * Function to calculate the sum of the elements of a double array.
 *
 * \return the sum value.
 */
static inline double
jbm_array_f64_sum (const double *x,     ///< double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_REDUCE_OP (x, n, __m512d, __m256d, __m128d, double, _mm512_loadu_pd,
                       _mm256_loadu_pd, _mm_loadu_pd, _mm512_add_pd,
                       _mm256_add_pd, _mm_add_pd, JBM_ADD,
                       jbm_8xf64_reduce_add, jbm_4xf64_reduce_add,
                       jbm_2xf64_reduce_add, 0.);
}

/**
 * Function to find the highest element of a double array.
 *
 * \return the highest value.
 */
static inline double
jbm_array_f64_reduce_max (const double *x,      ///< double array.
                          const unsigned int n) ///< number of array elements.
{
  JBM_ARRAY_REDUCE_OP (x, n, __m512d, __m256d, __m128d, double, _mm512_loadu_pd,
                       _mm256_loadu_pd, _mm_loadu_pd, _mm512_max_pd,
                       _mm256_max_pd, _mm_max_pd, fmaxf, jbm_8xf64_reduce_max,
                       jbm_4xf64_reduce_max, jbm_2xf64_reduce_max, -INFINITY);
}

/**
 * Function to find the lowest element of a double array.
 *
 * \return the lowest value.
 */
static inline double
jbm_array_f64_reduce_min (const double *x,      ///< double array.
                          const unsigned int n) ///< number of array elements.
{
  JBM_ARRAY_REDUCE_OP (x, n, __m512d, __m256d, __m128d, double, _mm512_loadu_pd,
                       _mm256_loadu_pd, _mm_loadu_pd, _mm512_min_pd,
                       _mm256_min_pd, _mm_min_pd, fminf, jbm_8xf64_reduce_min,
                       jbm_4xf64_reduce_min, jbm_2xf64_reduce_min, INFINITY);
}

/**
 * Function to find the highest and the lowest elements of a double array.
 */
static inline void
jbm_array_f64_reduce_maxmin (const double *x,   ///< double array.
                             double *max,       ///< the highest value.
                             double *min,       ///< the lowest value.
                             const unsigned int n)
                             ///< number of array elements.
{
  JBM_ARRAY_MAXMIN (x, n, __m512d, __m256d, __m128d, double, _mm512_loadu_pd,
                    _mm256_loadu_pd, _mm_loadu_pd, _mm512_max_pd, _mm256_max_pd,
                    _mm_max_pd, fmaxf, _mm512_min_pd, _mm256_min_pd, _mm_min_pd,
                    fmin, jbm_8xf64_reduce_max, jbm_4xf64_reduce_max,
                    jbm_2xf64_reduce_max, jbm_8xf64_reduce_min,
                    jbm_4xf64_reduce_min, jbm_2xf64_reduce_min, mx, mn);
  *max = mx, *min = mn;
}

/**
 * Function to add 1 double array + 1 number.
 */
static inline void
jbm_array_f64_add1 (double *restrict xr,        ///< result double array.
                    const double *restrict x1,  ///< addend double array.
                    const double x2,    ///< addend double number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m512d, __m256d, __m128d, double,
                 _mm512_loadu_pd, _mm256_loadu_pd, _mm_loadu_pd,
                 _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                 _mm512_set1_pd, _mm256_set1_pd, _mm_set1_pd, _mm512_add_pd,
                 _mm256_add_pd, _mm_add_pd, JBM_ADD);
}

/**
 * Function to subtract 1 double array - 1 double number.
 */
static inline void
jbm_array_f64_sub1 (double *restrict xr,        ///< result double array.
                    const double *restrict x1,  ///< minuend double array.
                    const double x2,    ///< subtrahend double number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m512d, __m256d, __m128d, double,
                 _mm512_loadu_pd, _mm256_loadu_pd, _mm_loadu_pd,
                 _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                 _mm512_set1_pd, _mm256_set1_pd, _mm_set1_pd, _mm512_sub_pd,
                 _mm256_sub_pd, _mm_sub_pd, JBM_SUB);
}

/**
 * Function to multiply a double array by a double number.
 */
static inline void
jbm_array_f64_mul1 (double *restrict xr,        ///< result double array.
                    const double *restrict x1,  ///< multiplier double array.
                    const double x2,    ///< multiplicand double number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m512d, __m256d, __m128d, double,
                 _mm512_loadu_pd, _mm256_loadu_pd, _mm_loadu_pd,
                 _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                 _mm512_set1_pd, _mm256_set1_pd, _mm_set1_pd, _mm512_mul_pd,
                 _mm256_mul_pd, _mm_mul_pd, JBM_MUL);
}

/**
 * Function to divide a double array by a double number.
 */
static inline void
jbm_array_f64_div1 (double *restrict xr,        ///< result double array.
                    const double *restrict x1,  ///< dividend double array.
                    const double x2,    ///< divisor double number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m512d, __m256d, __m128d, double,
                 _mm512_loadu_pd, _mm256_loadu_pd, _mm_loadu_pd,
                 _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                 _mm512_set1_pd, _mm256_set1_pd, _mm_set1_pd, _mm512_div_pd,
                 _mm256_div_pd, _mm_div_pd, JBM_DIV);
}

/**
 * Function to calculate the maximum between 1 double array + 1 number.
 */
static inline void
jbm_array_f64_max1 (double *restrict xr,        ///< result double array.
                    const double *restrict x1,  ///< double array.
                    const double x2,    ///< double number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m512d, __m256d, __m128d, double,
                 _mm512_loadu_pd, _mm256_loadu_pd, _mm_loadu_pd,
                 _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                 _mm512_set1_pd, _mm256_set1_pd, _mm_set1_pd, _mm512_max_pd,
                 _mm256_max_pd, _mm_max_pd, fmax);
}

/**
 * Function to calculate the minimum between 1 double array + 1 number.
 */
static inline void
jbm_array_f64_min1 (double *restrict xr,        ///< result double array.
                    const double *restrict x1,  ///< double array.
                    const double x2,    ///< double number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m512d, __m256d, __m128d, double,
                 _mm512_loadu_pd, _mm256_loadu_pd, _mm_loadu_pd,
                 _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                 _mm512_set1_pd, _mm256_set1_pd, _mm_set1_pd, _mm512_min_pd,
                 _mm256_min_pd, _mm_min_pd, fmin);
}

/**
 * Function to calculate the module between 1 double array + 1 number.
 */
static inline void
jbm_array_f64_mod1 (double *restrict xr,        ///< result double array.
                    const double *restrict x1,  ///< double array.
                    const double x2,    ///< double number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m512d, __m256d, __m128d, double,
                 _mm512_loadu_pd, _mm256_loadu_pd, _mm_loadu_pd,
                 _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                 _mm512_set1_pd, _mm256_set1_pd, _mm_set1_pd, jbm_8xf64_mod,
                 jbm_4xf64_mod, jbm_2xf64_mod, jbm_f64_mod);
}

/**
 * Function to calculate the pow function between 1 double array + 1 number.
 */
static inline void
jbm_array_f64_pow1 (double *restrict xr,        ///< result double array.
                    const double *restrict x1,  ///< double array.
                    const double x2,    ///< double number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m512d, __m256d, __m128d, double,
                 _mm512_loadu_pd, _mm256_loadu_pd, _mm_loadu_pd,
                 _mm512_storeu_pd, _mm256_storeu_pd, _mm_storeu_pd,
                 _mm512_set1_pd, _mm256_set1_pd, _mm_set1_pd, jbm_8xf64_pow,
                 jbm_4xf64_pow, jbm_2xf64_pow, jbm_f64_pow);
}

/**
 * Function to add 2 double arrays.
 */
static inline void
jbm_array_f64_add (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< 1st addend double array.
                   const double *restrict x2,   ///< 2nd addend double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                 _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd,
                 _mm_storeu_pd, _mm512_add_pd, _mm256_add_pd, _mm_add_pd,
                 JBM_ADD);
}

/**
 * Function to subtract 2 double arrays.
 */
static inline void
jbm_array_f64_sub (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< minuend double array.
                   const double *restrict x2,   ///< subtrahend double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                 _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd,
                 _mm_storeu_pd, _mm512_sub_pd, _mm256_sub_pd, _mm_sub_pd,
                 JBM_SUB);
}

/**
 * Function to multiply 2 double arrays.
 */
static inline void
jbm_array_f64_mul (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< multiplier double array.
                   const double *restrict x2,   ///< multiplicand double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                 _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd,
                 _mm_storeu_pd, _mm512_mul_pd, _mm256_mul_pd, _mm_mul_pd,
                 JBM_MUL);
}

/**
 * Function to divide 2 double arrays.
 */
static inline void
jbm_array_f64_div (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< dividend double array.
                   const double *restrict x2,   ///< divisor double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                 _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd,
                 _mm_storeu_pd, _mm512_div_pd, _mm256_div_pd, _mm_div_pd,
                 JBM_DIV);
}

/**
 * Function to calculate the maximum in 2 double arrays.
 */
static inline void
jbm_array_f64_max (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< 1st double array.
                   const double *restrict x2,   ///< 2nd double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                 _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd,
                 _mm_storeu_pd, _mm512_max_pd, _mm256_max_pd, _mm_max_pd, fmax);
}

/**
 * Function to calculate the minimum in 2 double arrays.
 */
static inline void
jbm_array_f64_min (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< 1st double array.
                   const double *restrict x2,   ///< 2nd double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                 _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd,
                 _mm_storeu_pd, _mm512_min_pd, _mm256_min_pd, _mm_min_pd, fmin);
}

/**
 * Function to calculate the module in 2 double arrays.
 */
static inline void
jbm_array_f64_mod (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< 1st double array.
                   const double *restrict x2,   ///< 2nd double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                 _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd,
                 _mm_storeu_pd, jbm_8xf64_mod, jbm_4xf64_mod, jbm_2xf64_mod,
                 jbm_f64_mod);
}

/**
 * Function to do the pow function in 2 double arrays.
 */
static inline void
jbm_array_f64_pow (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< 1st double array.
                   const double *restrict x2,   ///< 2nd double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, _mm512_loadu_pd, _mm256_loadu_pd,
                 _mm_loadu_pd, _mm512_storeu_pd, _mm256_storeu_pd,
                 _mm_storeu_pd, jbm_8xf64_pow, jbm_4xf64_pow, jbm_2xf64_pow,
                 jbm_f64_pow);
}

/**
 * Function to do the dot product of 2 double arrays.
 *
 * \return dot product (double).
 */
static inline double
jbm_array_f64_dot (const double *restrict x1,   ///< multiplier double array.
                   const double *restrict x2,   ///< multiplicand double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_DOT (x1, x2, n, __m512d, __m256d, __m128d, double, _mm512_loadu_pd,
                 _mm256_loadu_pd, _mm_loadu_pd, _mm512_mul_pd, _mm256_mul_pd,
                 _mm_mul_pd, _mm512_add_pd, _mm256_add_pd, _mm_add_pd,
                 _mm512_fmadd_pd, _mm256_fmadd_pd, _mm_fmadd_pd,
                 jbm_8xf64_reduce_add, jbm_4xf64_reduce_add,
                 jbm_2xf64_reduce_add);
}

#endif
