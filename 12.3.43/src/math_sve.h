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
 * \file math_sve.h
 * \brief Header file with useful mathematical functions for ARM SVE.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2026, Javier Burguete Tolosa.
 */
#ifndef JB_MATH_SVE__H
#define JB_MATH_SVE__H 1

#include "math_f32.h"
#include "math_f64.h"

///> macro to set the maximum vector size.
#define JBM_VLMAX(type) (sizeof(type) == 4 ? svcntw() : svcntd())

///> macro to get the all-true predicate for the given type.
#define JBM_PTRUE(type) (sizeof(type) == 4 ? svptrue_b32() : svptrue_b64())

///> macro to build the tail predicate for elements [i, n) of the given type.
#define JBM_PRED(type, i, n) \
  (sizeof(type) == 4 ? svwhilelt_b32((uint64_t)(i), (uint64_t)(n)) \
                     : svwhilelt_b64((uint64_t)(i), (uint64_t)(n)))

///> macro to automatize sets on one array.
#define JBM_ARRAY_SET(xr, xd, n, type, load, store) \
  const size_t vlmax = JBM_VLMAX(type); \
  const svbool_t pg_true = JBM_PTRUE(type); \
  svbool_t pg; \
  size_t i = 0; \
  for (; (n - i) >= (vlmax << 2);) \
    { \
      store (pg_true, xr + i, load (pg_true, xd + i)); \
      i += vlmax; \
      store (pg_true, xr + i, load (pg_true, xd + i)); \
      i += vlmax; \
      store (pg_true, xr + i, load (pg_true, xd + i)); \
      i += vlmax; \
      store (pg_true, xr + i, load (pg_true, xd + i)); \
      i += vlmax; \
    } \
  if ((n - i) >= (vlmax << 1)) \
    { \
      store (pg_true, xr + i, load (pg_true, xd + i)); \
      i += vlmax; \
      store (pg_true, xr + i, load (pg_true, xd + i)); \
      i += vlmax; \
    } \
  if ((n - i) >= vlmax) \
    { \
      store (pg_true, xr + i, load (pg_true, xd + i)); \
      i += vlmax; \
    } \
  if (i < n) \
    { \
      pg = JBM_PRED(type, i, n); \
      store (pg, xr + i, load (pg, xd + i)); \
    }

///> macro to automatize sets on one array and one number.
#define JBM_ARRAY_SET1(xr, xd, n, type, load, store) \
  const size_t vlmax = JBM_VLMAX(type); \
  const svbool_t pg_true = JBM_PTRUE(type); \
  svbool_t pg; \
  size_t i = 0; \
  for (; (n - i) >= (vlmax << 2);) \
    { \
      store (pg_true, xr + i, load (xd)); \
      i += vlmax; \
      store (pg_true, xr + i, load (xd)); \
      i += vlmax; \
      store (pg_true, xr + i, load (xd)); \
      i += vlmax; \
      store (pg_true, xr + i, load (xd)); \
      i += vlmax; \
    } \
  if ((n - i) >= (vlmax << 1)) \
    { \
      store (pg_true, xr + i, load (xd)); \
      i += vlmax; \
      store (pg_true, xr + i, load (xd)); \
      i += vlmax; \
    } \
  if ((n - i) >= vlmax) \
    { \
      store (pg_true, xr + i, load (xd)); \
      i += vlmax; \
    } \
  if (i < n) \
    { \
      pg = JBM_PRED(type, i, n); \
      store (pg, xr + i, load (xd)); \
    }

///> macro to automatize operations on one array.
#define JBM_ARRAY_OP(xr, xd, n, type, load, store, op) \
  const size_t vlmax = JBM_VLMAX(type); \
  const svbool_t pg_true = JBM_PTRUE(type); \
  svbool_t pg; \
  size_t i = 0; \
  for (; (n - i) >= (vlmax << 2);) \
    { \
      store (pg_true, xr + i, op (pg_true, load (pg_true, xd + i))); \
      i += vlmax; \
      store (pg_true, xr + i, op (pg_true, load (pg_true, xd + i))); \
      i += vlmax; \
      store (pg_true, xr + i, op (pg_true, load (pg_true, xd + i))); \
      i += vlmax; \
      store (pg_true, xr + i, op (pg_true, load (pg_true, xd + i))); \
      i += vlmax; \
    } \
  if ((n - i) >= (vlmax << 1)) \
    { \
      store (pg_true, xr + i, op (pg_true, load (pg_true, xd + i))); \
      i += vlmax; \
      store (pg_true, xr + i, op (pg_true, load (pg_true, xd + i))); \
      i += vlmax; \
    } \
  if ((n - i) >= vlmax) \
    { \
      store (pg_true, xr + i, op (pg_true, load (pg_true, xd + i))); \
      i += vlmax; \
    } \
  if (i < n) \
    { \
      pg = JBM_PRED(type, i, n); \
      store (pg, xr + i, op (pg, load (pg, xd + i))); \
    }

///> macro to automatize operations on one array and one number.
#define JBM_ARRAY_OP1(xr, x1, x2, n, type, load, store, op) \
  const size_t vlmax = JBM_VLMAX(type); \
  const svbool_t pg_true = JBM_PTRUE(type); \
  svbool_t pg; \
  size_t i = 0; \
  for (; (n - i) >= (vlmax << 2);) \
    { \
      store (pg_true, xr + i, op (pg_true, load (pg_true, x1 + i), x2)); \
      i += vlmax; \
      store (pg_true, xr + i, op (pg_true, load (pg_true, x1 + i), x2)); \
      i += vlmax; \
      store (pg_true, xr + i, op (pg_true, load (pg_true, x1 + i), x2)); \
      i += vlmax; \
      store (pg_true, xr + i, op (pg_true, load (pg_true, x1 + i), x2)); \
      i += vlmax; \
    } \
  if ((n - i) >= (vlmax << 1)) \
    { \
      store (pg_true, xr + i, op (pg_true, load (pg_true, x1 + i), x2)); \
      i += vlmax; \
      store (pg_true, xr + i, op (pg_true, load (pg_true, x1 + i), x2)); \
      i += vlmax; \
    } \
  if ((n - i) >= vlmax) \
    { \
      store (pg_true, xr + i, op (pg_true, load (pg_true, x1 + i), x2)); \
      i += vlmax; \
    } \
  if (i < n) \
    { \
      pg = JBM_PRED(type, i, n); \
      store (pg, xr + i, op (pg, load (pg, x1 + i), x2)); \
    }

///> macro to automatize operations on two arrays.
#define JBM_ARRAY_OP2(xr, x1, x2, n, type, load, store, op) \
  const size_t vlmax = JBM_VLMAX(type); \
  const svbool_t pg_true = JBM_PTRUE(type); \
  svbool_t pg; \
  size_t i = 0; \
  for (; (n - i) >= (vlmax << 2);) \
    { \
      store (pg_true, xr + i, \
             op (pg_true, load (pg_true, x1 + i), load (pg_true, x2 + i))); \
      i += vlmax; \
      store (pg_true, xr + i, \
             op (pg_true, load (pg_true, x1 + i), load (pg_true, x2 + i))); \
      i += vlmax; \
      store (pg_true, xr + i, \
             op (pg_true, load (pg_true, x1 + i), load (pg_true, x2 + i))); \
      i += vlmax; \
      store (pg_true, xr + i, \
             op (pg_true, load (pg_true, x1 + i), load (pg_true, x2 + i))); \
      i += vlmax; \
    } \
  if ((n - i) >= (vlmax << 1)) \
    { \
      store (pg_true, xr + i, \
             op (pg_true, load (pg_true, x1 + i), load (pg_true, x2 + i))); \
      i += vlmax; \
      store (pg_true, xr + i, \
             op (pg_true, load (pg_true, x1 + i), load (pg_true, x2 + i))); \
      i += vlmax; \
    } \
  if ((n - i) >= vlmax) \
    { \
      store (pg_true, xr + i, \
             op (pg_true, load (pg_true, x1 + i), load (pg_true, x2 + i))); \
      i += vlmax; \
    } \
  if (i < n) \
    { \
      pg = JBM_PRED(type, i, n); \
      store (pg, xr + i, \
             op (pg, load (pg, x1 + i), load (pg, x2 + i))); \
    }

///> macro to automatize operations on two arrays and one number.
#define JBM_ARRAY_OP3(xr, x1, x2, x3, n, type, load, store, op) \
  const size_t vlmax = JBM_VLMAX(type); \
  const svbool_t pg_true = JBM_PTRUE(type); \
  svbool_t pg; \
  size_t i = 0; \
  for (; (n - i) >= (vlmax << 2);) \
    { \
      store (pg_true, xr + i, op (pg_true, load (pg_true, x3 + i), \
                                  load (pg_true, x1 + i), x2)); \
      i += vlmax; \
      store (pg_true, xr + i, op (pg_true, load (pg_true, x3 + i), \
                                  load (pg_true, x1 + i), x2)); \
      i += vlmax; \
      store (pg_true, xr + i, op (pg_true, load (pg_true, x3 + i), \
                                  load (pg_true, x1 + i), x2)); \
      i += vlmax; \
      store (pg_true, xr + i, op (pg_true, load (pg_true, x3 + i), \
                                  load (pg_true, x1 + i), x2)); \
      i += vlmax; \
    } \
  if ((n - i) >= (vlmax << 1)) \
    { \
      store (pg_true, xr + i, op (pg_true, load (pg_true, x3 + i), \
                                  load (pg_true, x1 + i), x2)); \
      i += vlmax; \
      store (pg_true, xr + i, op (pg_true, load (pg_true, x3 + i), \
                                  load (pg_true, x1 + i), x2)); \
      i += vlmax; \
    } \
  if ((n - i) >= vlmax) \
    { \
      store (pg_true, xr + i, op (pg_true, load (pg_true, x3 + i), \
                                  load (pg_true, x1 + i), x2)); \
      i += vlmax; \
    } \
  if (i < n) \
    { \
      pg = JBM_PRED(type, i, n); \
      store (pg, xr + i, op (pg, load (pg, x3 + i), load (pg, x1 + i), x2)); \
    }

///> macro to automatize operations on three arrays.
#define JBM_ARRAY_OP4(xr, x1, x2, x3, n, type, load, store, op) \
  const size_t vlmax = JBM_VLMAX(type); \
  const svbool_t pg_true = JBM_PTRUE(type); \
  svbool_t pg; \
  size_t i = 0; \
  for (; (n - i) >= (vlmax << 2);) \
    { \
      store (pg_true, xr + i, \
             op (pg_true, load (pg_true, x1 + i), load (pg_true, x2 + i), \
                 load (pg_true, x3 + i))); \
      i += vlmax; \
      store (pg_true, xr + i, \
             op (pg_true, load (pg_true, x1 + i), load (pg_true, x2 + i), \
                 load (pg_true, x3 + i))); \
      i += vlmax; \
      store (pg_true, xr + i, \
             op (pg_true, load (pg_true, x1 + i), load (pg_true, x2 + i), \
                 load (pg_true, x3 + i))); \
      i += vlmax; \
      store (pg_true, xr + i, \
             op (pg_true, load (pg_true, x1 + i), load (pg_true, x2 + i), \
                 load (pg_true, x3 + i))); \
      i += vlmax; \
    } \
  if ((n - i) >= (vlmax << 1)) \
    { \
      store (pg_true, xr + i, \
             op (pg_true, load (pg_true, x1 + i), load (pg_true, x2 + i), \
                 load (pg_true, x3 + i))); \
      i += vlmax; \
      store (pg_true, xr + i, \
             op (pg_true, load (pg_true, x1 + i), load (pg_true, x2 + i), \
                 load (pg_true, x3 + i))); \
      i += vlmax; \
    } \
  if ((n - i) >= vlmax) \
    { \
      store (pg_true, xr + i, \
             op (pg_true, load (pg_true, x1 + i), load (pg_true, x2 + i), \
                 load (pg_true, x3 + i))); \
      i += vlmax; \
    } \
  if (i < n) \
    { \
      pg = JBM_PRED(type, i, n); \
      store (pg, xr + i, \
             op (pg, load (pg, x1 + i), load (pg, x2 + i), \
                 load (pg, x3 + i))); \
    }

#endif
