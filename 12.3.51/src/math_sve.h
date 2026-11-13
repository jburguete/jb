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

///> macro to automatize reduction operations on arrays.
#define JBM_ARRAY_REDUCE_OP(x, n, type, vtype, load, vop, rop) \
  const size_t vlmax = JBM_VLMAX (type); \
  const svbool_t pg_true = JBM_PTRUE (type); \
  svbool_t pg; \
  vtype a, b, c, d; \
  size_t i = 0; \
  if (n >= (vlmax << 2)) \
    { \
      a = load (pg_true, x); \
      i += vlmax; \
      b = load (pg_true, x + i); \
      i += vlmax; \
      c = load (pg_true, x + i); \
      i += vlmax; \
      d = load (pg_true, x + i); \
      i += vlmax; \
      while ((n - i) >= (vlmax << 2)) \
        { \
          a = vop (pg_true, a, load (pg_true, x + i)); \
          i += vlmax; \
          b = vop (pg_true, b, load (pg_true, x + i)); \
          i += vlmax; \
          c = vop (pg_true, c, load (pg_true, x + i)); \
          i += vlmax; \
          d = vop (pg_true, d, load (pg_true, x + i)); \
          i += vlmax; \
        } \
      if ((n - i) >= (vlmax << 1)) \
        { \
          a = vop (pg_true, a, load (pg_true, x + i)); \
          i += vlmax; \
          b = vop (pg_true, b, load (pg_true, x + i)); \
          i += vlmax; \
        } \
      if ((n - i) >= vlmax) \
        { \
          a = vop (pg_true, a, load (pg_true, x + i)); \
          i += vlmax; \
        } \
      a = vop (pg_true, a, b); \
      c = vop (pg_true, c, d); \
      a = vop (pg_true, a, c); \
      if (i < n) \
        { \
          pg = JBM_PRED (type, i, n); \
          a = vop (pg, a, load (pg, x + i)); \
        } \
      return rop (pg_true, a); \
    } \
  if (n >= (vlmax << 1)) \
    { \
      a = load (pg_true, x); \
      i += vlmax; \
      b = load (pg_true, x + i); \
      i += vlmax; \
      if ((n - i) >= vlmax) \
        { \
          a = vop (pg_true, a, load (pg_true, x + i)); \
          i += vlmax; \
        } \
      a = vop (pg_true, a, b); \
      if (i < n) \
        { \
          pg = JBM_PRED (type, i, n); \
          a = vop (pg, a, load (pg, x + i)); \
        } \
      return rop (pg_true, a); \
    } \
  if (n >= vlmax) \
    { \
      a = load (pg_true, x); \
      i += vlmax; \
      if (i < n) \
        { \
          pg = JBM_PRED (type, i, n); \
          a = vop (pg, a, load (pg, x + i)); \
        } \
      return rop (pg_true, a); \
    } \
  pg = JBM_PRED (type, 0, n); \
  return rop (pg, load (pg, x));

///> macro to automatize maxmin operations on arrays.
#define JBM_ARRAY_MAXMIN(x, n, xmax, xmin, type, vtype, load, vmax, vmin, \
                         rmax, rmin) \
  const size_t vlmax = JBM_VLMAX (type); \
  const svbool_t pg_true = JBM_PTRUE (type); \
  svbool_t pg; \
  vtype xi, ax, an, bx, bn, cx, cn, dx, dn; \
  size_t i = 0; \
  if (n >= (vlmax << 2)) \
    { \
      ax = an = load (pg_true, x); \
      i += vlmax; \
      bx = bn = load (pg_true, x + i); \
      i += vlmax; \
      cx = cn = load (pg_true, x + i); \
      i += vlmax; \
      dx = dn = load (pg_true, x + i); \
      i += vlmax; \
      while ((n - i) >= (vlmax << 2)) \
        { \
          xi = load (pg_true, x + i); \
          ax = vmax (pg_true, ax, xi); \
          an = vmin (pg_true, an, xi); \
          i += vlmax; \
          xi = load (pg_true, x + i); \
          bx = vmax (pg_true, bx, xi); \
          bn = vmin (pg_true, bn, xi); \
          i += vlmax; \
          xi = load (pg_true, x + i); \
          cx = vmax (pg_true, cx, xi); \
          cn = vmin (pg_true, cn, xi); \
          i += vlmax; \
          xi = load (pg_true, x + i); \
          dx = vmax (pg_true, dx, xi); \
          dn = vmin (pg_true, dn, xi); \
          i += vlmax; \
        } \
      if ((n - i) >= (vlmax << 1)) \
        { \
          xi = load (pg_true, x + i); \
          ax = vmax (pg_true, ax, xi); \
          an = vmin (pg_true, an, xi); \
          i += vlmax; \
          xi = load (pg_true, x + i); \
          bx = vmax (pg_true, bx, xi); \
          bn = vmin (pg_true, bn, xi); \
          i += vlmax; \
        } \
      if ((n - i) >= vlmax) \
        { \
          xi = load (pg_true, x + i); \
          ax = vmax (pg_true, ax, xi); \
          an = vmin (pg_true, an, xi); \
          i += vlmax; \
        } \
      ax = vmax (pg_true, ax, bx); \
      an = vmin (pg_true, an, bn); \
      cx = vmax (pg_true, cx, dx); \
      cn = vmin (pg_true, cn, dn); \
      ax = vmax (pg_true, ax, cx); \
      an = vmin (pg_true, an, cn); \
      if (i < n) \
        { \
          pg = JBM_PRED (type, i, n); \
          ax = vmax (pg, ax, load (pg, x + i)); \
          an = vmin (pg, an, load (pg, x + i)); \
        } \
      *xmax = rmax (pg_true, ax); \
      *xmin = rmin (pg_true, an); \
      return; \
    } \
  if (n >= (vlmax << 1)) \
    { \
      ax = an = load (pg_true, x); \
      i += vlmax; \
      bx = bn = load (pg_true, x + i); \
      i += vlmax; \
      if ((n - i) >= vlmax) \
        { \
          xi = load (pg_true, x + i); \
          ax = vmax (pg_true, ax, xi); \
          an = vmin (pg_true, an, xi); \
          i += vlmax; \
        } \
      ax = vmax (pg_true, ax, bx); \
      an = vmin (pg_true, an, bn); \
      if (i < n) \
        { \
          pg = JBM_PRED (type, i, n); \
          ax = vmax (pg, ax, load (pg, x + i)); \
          an = vmin (pg, an, load (pg, x + i)); \
        } \
      *xmax = rmax (pg_true, ax); \
      *xmin = rmin (pg_true, an); \
      return; \
    } \
  if (n >= vlmax) \
    { \
      ax = an = load (pg_true, x); \
      i += vlmax; \
      if (i < n) \
        { \
          pg = JBM_PRED (type, i, n); \
          ax = vmax (pg, ax, load (pg, x + i)); \
          an = vmin (pg, an, load (pg, x + i)); \
        } \
      *xmax = rmax (pg_true, ax); \
      *xmin = rmin (pg_true, an); \
      return; \
    } \
  pg = JBM_PRED (type, 0, n); \
  xi = load (pg, x); \
  *xmax = rmax (pg, xi); \
  *xmin = rmin (pg, xi); \
  return;

///> macro to automatize dot products on arrays.
#define JBM_ARRAY_DOT(x1, x2, n, type, vtype, load, mul, fma, add, rop) \
  const size_t vlmax = JBM_VLMAX (type); \
  const svbool_t pg_true = JBM_PTRUE (type); \
  svbool_t pg; \
  vtype a, b, c, d; \
  size_t i = 0; \
  if (n >= (vlmax << 2)) \
    { \
      a = mul (pg_true, load (pg_true, x1), load (pg_true, x2)); \
      i += vlmax; \
      b = mul (pg_true, load (pg_true, x1 + i), load (pg_true, x2 + i)); \
      i += vlmax; \
      c = mul (pg_true, load (pg_true, x1 + i), load (pg_true, x2 + i)); \
      i += vlmax; \
      d = mul (pg_true, load (pg_true, x1 + i), load (pg_true, x2 + i)); \
      i += vlmax; \
      while ((n - i) >= (vlmax << 2)) \
        { \
          a = fma (pg_true, a, load (pg_true, x1 + i), \
                                   load (pg_true, x2 + i)); \
          i += vlmax; \
          b = fma (pg_true, b, load (pg_true, x1 + i), \
                                   load (pg_true, x2 + i)); \
          i += vlmax; \
          c = fma (pg_true, c, load (pg_true, x1 + i), \
                                   load (pg_true, x2 + i)); \
          i += vlmax; \
          d = fma (pg_true, d, load (pg_true, x1 + i), \
                                   load (pg_true, x2 + i)); \
          i += vlmax; \
        } \
      if ((n - i) >= (vlmax << 1)) \
        { \
          a = fma (pg_true, a, load (pg_true, x1 + i), \
                                   load (pg_true, x2 + i)); \
          i += vlmax; \
          b = fma (pg_true, b, load (pg_true, x1 + i), \
                                   load (pg_true, x2 + i)); \
          i += vlmax; \
        } \
      if ((n - i) >= vlmax) \
        { \
          a = fma (pg_true, a, load (pg_true, x1 + i), \
                                   load (pg_true, x2 + i)); \
          i += vlmax; \
        } \
      a = add (pg_true, a, b); \
      c = add (pg_true, c, d); \
      a = add (pg_true, a, c); \
      if (i < n) \
        { \
          pg = JBM_PRED (type, i, n); \
          a = fma (pg, a, load (pg, x1 + i), load (pg, x2 + i)); \
        } \
      return rop (pg_true, a); \
    } \
  if (n >= (vlmax << 1)) \
    { \
      a = mul (pg_true, load (pg_true, x1), load (pg_true, x2)); \
      i += vlmax; \
      b = mul (pg_true, load (pg_true, x1 + i), load (pg_true, x2 + i)); \
      i += vlmax; \
      if ((n - i) >= vlmax) \
        { \
          a = fma (pg_true, a, load (pg_true, x1 + i), \
                                   load (pg_true, x2 + i)); \
          i += vlmax; \
        } \
      a = add (pg_true, a, b); \
      if (i < n) \
        { \
          pg = JBM_PRED (type, i, n); \
          a = fma (pg, a, load (pg, x1 + i), load (pg, x2 + i)); \
        } \
      return rop (pg_true, a); \
    } \
  if (n >= vlmax) \
    { \
      a = mul (pg_true, load (pg_true, x1), load (pg_true, x2)); \
      i += vlmax; \
      if (i < n) \
        { \
          pg = JBM_PRED (type, i, n); \
          a = fma (pg, a, load (pg, x1 + i), load (pg, x2 + i)); \
        } \
      return rop (pg_true, a); \
    } \
  pg = JBM_PRED (type, 0, n); \
  return rop (pg, mul (pg, load (pg, x1), load (pg, x2)));

static inline void
print_vbit32_t (FILE *file, const char *label, svuint32_t x, const size_t vl)
{
  uint32_t y[svcntw ()] JB_ALIGNED;
  unsigned int i;
  svbool_t pg = svwhilelt_b32 ((uint64_t) 0, (uint64_t) vl);
  svst1_u32 (pg, y, x);
  for (i = 0; i < vl; ++i)
    fprintf (file, "%s[%u]=%08" PRIx32 "\n", label, i, y[i]);
}

static inline void
print_vbit64_t (FILE *file, const char *label, svuint64_t x, const size_t vl)
{
  uint64_t y[svcntd ()] JB_ALIGNED;
  unsigned int i;
  svbool_t pg = svwhilelt_b64 ((uint64_t) 0, (uint64_t) vl);
  svst1_u64 (pg, y, x);
  for (i = 0; i < vl; ++i)
    fprintf (file, "%s[%u]=%016" PRIx64 "\n", label, i, y[i]);
}

static inline void
print_vuint32_t (FILE *file, const char *label, svuint32_t x, const size_t vl)
{
  uint32_t y[svcntw ()] JB_ALIGNED;
  unsigned int i;
  svbool_t pg = svwhilelt_b32 ((uint64_t) 0, (uint64_t) vl);
  svst1_u32 (pg, y, x);
  for (i = 0; i < vl; ++i)
    fprintf (file, "%s[%u]=%" PRIu32 "\n", label, i, y[i]);
}

static inline void
print_vuint64_t (FILE *file, const char *label, svuint64_t x, const size_t vl)
{
  uint64_t y[svcntd ()] JB_ALIGNED;
  unsigned int i;
  svbool_t pg = svwhilelt_b64 ((uint64_t) 0, (uint64_t) vl);
  svst1_u64 (pg, y, x);
  for (i = 0; i < vl; ++i)
    fprintf (file, "%s[%u]=%" PRIu64 "\n", label, i, y[i]);
}

static inline void
print_vint32_t (FILE *file, const char *label, svint32_t x, const size_t vl)
{
  int32_t y[svcntw ()] JB_ALIGNED;
  unsigned int i;
  svbool_t pg = svwhilelt_b32 ((uint64_t) 0, (uint64_t) vl);
  svst1_s32 (pg, y, x);
  for (i = 0; i < vl; ++i)
    fprintf (file, "%s[%u]=%" PRId32 "\n", label, i, y[i]);
}

static inline void
print_vint64_t (FILE *file, const char *label, svint64_t x, const size_t vl)
{
  int64_t y[svcntd ()] JB_ALIGNED;
  unsigned int i;
  svbool_t pg = svwhilelt_b64 ((uint64_t) 0, (uint64_t) vl);
  svst1_s64 (pg, y, x);
  for (i = 0; i < vl; ++i)
    fprintf (file, "%s[%u]=%" PRId64 "\n", label, i, y[i]);
}

static inline void
print_vfloat32_t (FILE *file, const char *label, svfloat32_t x, const size_t vl)
{
  float y[svcntw ()] JB_ALIGNED;
  unsigned int i;
  svbool_t pg = svwhilelt_b32 ((uint64_t) 0, (uint64_t) vl);
  svst1_f32 (pg, y, x);
  for (i = 0; i < vl; ++i)
    fprintf (file, "%s[%u]=%.8g\n", label, i, y[i]);
}

static inline void
print_vfloat64_t (FILE *file, const char *label, svfloat64_t x, const size_t vl)
{
  double y[svcntd ()] JB_ALIGNED;
  unsigned int i;
  svbool_t pg = svwhilelt_b64 ((uint64_t) 0, (uint64_t) vl);
  svst1_f64 (pg, y, x);
  for (i = 0; i < vl; ++i)
    fprintf (file, "%s[%u]=%.17lg\n", label, i, y[i]);
}

/**
 * Function to calculate the additive inverse value of a svfloat32_t vector.
 */
static inline svfloat32_t
jbm_nxf32_opposite (svbool_t pg,        ///< predicate.
                    const svfloat32_t x)        ///< svfloat32_t vector.
{
  return svneg_f32_x (pg, x);
}

/**
 * Function to calculate the multiplicative inverse value of a svfloat32_t
 * vector.
 */
static inline svfloat32_t
jbm_nxf32_reciprocal (svbool_t pg,      ///< predicate.
                      const svfloat32_t x)      ///< svfloat32_t vector.
{
  return svdiv_f32_x (pg, svdup_n_f32 (1.f), x);
}

/**
 * Function to calculate the absolute value of a svfloat32_t vector.
 */
static inline svfloat32_t
jbm_nxf32_abs (svbool_t pg,     ///< predicate.
               const svfloat32_t x)     ///< svfloat32_t vector.
{
  return svabs_f32_x (pg, x);
}

/**
 * Function to copy the sign of a svfloat32_t vector to another svfloat32_t
 * vector.
 */
static inline svfloat32_t
jbm_nxf32_copysign (svbool_t pg,        ///< predicate.
                    const svfloat32_t x,        ///< vector to preserve magnitude.
                    const svfloat32_t y)        ///< vector to preserve sign.
{
  return svcopysign_f32_x (pg, x, y);
}

/**
 * Function to calculate the hypot function (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_hypot (svbool_t pg,   ///< predicate.
                 const svfloat32_t x,   ///< 1st svfloat32_t vector.
                 const svfloat32_t y)   ///< 2nd svfloat32_t vector.
{
  svfloat32_t t = svmul_f32_x (pg, x, x);
  t = svmla_f32_x (pg, t, y, y);
  return svsqrt_f32_x (pg, t);
}

/**
 * Function to rounding to nearest (svfloat32_t).
 */
static inline svint32_t
jbm_nxf32_round (svbool_t pg,   ///< predicate.
                 const svfloat32_t x)   ///< svfloat32_t vector.
{
  return svcvt_s32_f32_x (pg, svrintn_f32_x (pg, x));
}

/**
 * Function to rounding towards zero (svfloat32_t).
 */
static inline svint32_t
jbm_nxf32_trunc (svbool_t pg,   ///< predicate.
                 const svfloat32_t x)   ///< svfloat32_t vector.
{
  return svcvt_s32_f32_x (pg, svrintz_f32_x (pg, x));
}

/**
 * Function to rounding down (svfloat32_t).
 */
static inline svint32_t
jbm_nxf32_floor (svbool_t pg,   ///< predicate.
                 const svfloat32_t x)   ///< svfloat32_t vector.
{
  return svcvt_s32_f32_x (pg, svrintm_f32_x (pg, x));
}

/**
 * Function to rounding top (svfloat32_t).
 */
static inline svint32_t
jbm_nxf32_ceil (svbool_t pg,    ///< predicate.
                const svfloat32_t x)    ///< svfloat32_t vector.
{
  return svcvt_s32_f32_x (pg, svrintp_f32_x (pg, x));
}

/**
 * Function to calculate the rest of a division (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_mod (svbool_t pg,     ///< predicate.
               const svfloat32_t x,     ///< dividend (svfloat32_t).
               const svfloat32_t d)     ///< divisor (svfloat32_t).
{
  svfloat32_t q = svdiv_f32_x (pg, x, d);
  q = svcvt_f32_s32_x (pg, jbm_nxf32_floor (pg, q));
  return svmls_f32_x (pg, x, q, d);
}

/**
 * Function to calculate the rest of a division by a float (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_mod1 (svbool_t pg,    ///< predicate.
                const svfloat32_t x,    ///< dividend (svfloat32_t).
                const float d)  ///< divisor (double).
{
  svfloat32_t vd = svdup_n_f32 (d);
  svfloat32_t q = svdiv_f32_x (pg, x, vd);
  q = svcvt_f32_s32_x (pg, jbm_nxf32_floor (pg, q));
  return svmls_f32_x (pg, x, q, vd);
}

/**
 * Function to implement the standard frexp function (vfloat32m1_t).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline svfloat32_t
jbm_nxf32_frexp (svbool_t pg,   ///< predicate.
                 const svfloat32_t x,   ///< svfloat32_t vector.
                 svint32_t *e)  ///< pointer to the exponents vector.
{
  const svuint32_t ai = svreinterpret_u32_f32 (x);
  const svuint32_t ai_abs = svand_n_u32_x (pg, ai, JBM_F32_BITS_ABS);
  const svbool_t m_special = svorr_b_z (pg,
                                        svcmpge_n_u32 (pg, ai_abs,
                                                       JBM_F32_BITS_EXPONENT),
                                        svcmpeq_n_u32 (pg, ai_abs, 0));
  const svbool_t m_sub
    = svcmpeq_n_u32 (pg, svand_n_u32_x (pg, ai, JBM_F32_BITS_EXPONENT), 0);
  const svuint32_t yi = svreinterpret_u32_f32 (svmul_n_f32_x (pg, x, 0x1p23f));
  const svint32_t en = svsub_n_s32_x (pg,
                                      svreinterpret_s32_u32 (svlsr_n_u32_x
                                                             (pg, yi, 23)),
                                      JBM_F32_BIAS);
  const svint32_t en_sub = svsub_n_s32_x (pg, en, 23);
  *e = svsel_s32 (m_special, svdup_n_s32 (0), svsel_s32 (m_sub, en_sub, en));
  const svuint32_t mant = svorr_n_u32_x (pg,
                                         svorr_n_u32_x (pg,
                                                        svand_n_u32_x (pg, yi,
                                                                       JBM_F32_BITS_SIGN),
                                                        0x3f000000),
                                         svand_n_u32_x (pg, yi,
                                                        JBM_F32_BITS_MANTISSA));
  return svsel_f32 (m_special, x, svreinterpret_f32_u32 (mant));
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (svint32_t).
 *
 * \return function value vector (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_exp2n (svbool_t pg,   ///< predicate.
                 svint32_t e)   ///< exponent vector (svint32_t).
{
  svuint32_t r;
  r = svsel_u32 (svcmplt_n_s32 (pg, e, -126),
                 svlsl_u32_x (pg, svdup_n_u32 (1),
                              svreinterpret_u32_s32 (svadd_n_s32_x (pg, e,
                                                                    149))),
                 svlsl_n_u32_x (pg,
                                svreinterpret_u32_s32 (svadd_n_s32_x (pg, e,
                                                                      127)),
                                23));
  r =
    svsel_u32 (svcmpgt_n_s32 (pg, e, 127), svdup_n_u32 (JBM_F32_BITS_EXPONENT),
               r);
  return svreinterpret_f32_u32 (r);
}

/**
 * Function to implement the standard ldexp function (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_ldexp (svbool_t pg,   ///< predicate.
                 const svfloat32_t x,   ///< svfloat32_t vector.
                 svint32_t e)   ///< exponent vector (svint32_t).
{
  return svmul_f32_x (pg, x, jbm_nxf32_exp2n (pg, e));
}

/**
 * Function to check small svfloat32_t vectors.
 *
 * \return predicate true on small numbers.
 */
static inline svbool_t
jbm_nxf32_small (svbool_t pg,   ///< predicate.
                 const svfloat32_t x)   ///< svfloat32_t vector.
{
  return svcmplt_n_f32 (pg, svabs_f32_x (pg, x), FLT_EPSILON);
}

/**
 * Function to calculate the svfloat32_t vector with the components with lower
 * module in the [a, b] interval.
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin svfloat32_t vector.
 */
static inline svfloat32_t
jbm_nxf32_modmin (svbool_t pg,  ///< predicate.
                  const svfloat32_t a,  ///< 1st svfloat32_t vector.
                  const svfloat32_t b)  ///< 2nd svfloat32_t vector.
{
  const svbool_t z = svcmple_n_f32 (pg, svmul_f32_x (pg, a, b), 0.f);
  const svbool_t m
    = svbic_b_z (pg, svcmplt_f32 (pg, svabs_f32_x (pg, a), svabs_f32_x (pg, b)),
                 z);
  return svsel_f32 (z, svdup_n_f32 (0.f), svsel_f32 (m, a, b));
}

/**
 * Function to interchange 2 svfloat32_t vectors.
 */
static inline void
jbm_nxf32_change (svfloat32_t *restrict a,      ///< 1st vector pointer.
                  svfloat32_t *restrict b)      ///< 2nd vector pointer.
{
  svfloat32_t c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the double of a svfloat32_t vector.
 *
 * \return svfloat32_t double.
 */
static inline svfloat32_t
jbm_nxf32_dbl (svbool_t pg,     ///< predicate.
               const svfloat32_t x)     ///< svfloat32_t vector.
{
  return svadd_f32_x (pg, x, x);
}

/**
 * Function to calculate the square of the components of a svfloat32_t vector.
 *
 * \return svfloat32_t vector square.
 */
static inline svfloat32_t
jbm_nxf32_sqr (svbool_t pg,     ///< predicate.
               const svfloat32_t x)     ///< svfloat32_t vector.
{
  return svmul_f32_x (pg, x, x);
}

/**
 * Function to perform an extrapolation between 2 svfloat32_t vectors of 2D
 * points.
 *
 * \return svfloat32_t vector of y-coordinates of the extrapolated points.
 */
static inline svfloat32_t
jbm_nxf32_extrapolate (svbool_t pg,     ///< predicate.
                       const svfloat32_t x,     ///< x-coord. of points.
                       const svfloat32_t x1,    ///< x-coord. of 1st points.
                       const svfloat32_t x2,    ///< x-coord. of 2nd points.
                       const svfloat32_t y1,    ///< y-coord. of 1st points.
                       const svfloat32_t y2)    ///< y-coord. of 2nd points.
{
  return
    svmla_f32_x (pg, y1, svsub_f32_x (pg, x, x1),
                 svdiv_f32_x (pg, svsub_f32_x (pg, y2, y1),
                              svsub_f32_x (pg, x2, x1)));
}

/**
 * Function to perform an interpolation between 2 svfloat32_t vectors of 2D
 * points.
 *
 * \return svfloat32_t vector of y-coordinates of the interpolated points.
 */
static inline svfloat32_t
jbm_nxf32_interpolate (svbool_t pg,     ///< predicate.
                       const svfloat32_t x,     ///< x-coord. of points.
                       const svfloat32_t x1,    ///< x-coord. of 1st points.
                       const svfloat32_t x2,    ///< x-coord. of 2nd points.
                       const svfloat32_t y1,    ///< y-coord. of 1st points.
                       const svfloat32_t y2)    ///< y-coord. of 2nd points.
{
  svfloat32_t k = jbm_nxf32_extrapolate (pg, x, x1, x2, y1, y2);
  k = svsel_f32 (svcmpgt_f32 (pg, x, x1), y1, k);
  return svsel_f32 (svcmplt_f32 (pg, x, x2), y2, k);
}

/**
 * Function to calculate the length of a svfloat32_t vector of 2D segments.
 *
 * \return svfloat32_t vector of segment lengths.
 */
static inline svfloat32_t
jbm_nxf32_v2_length (svbool_t pg,       ///< predicate.
                     const svfloat32_t x1,      ///< x-coord. of 1st points.
                     const svfloat32_t y1,      ///< y-coord. of 1st points.
                     const svfloat32_t x2,      ///< x-coord. of 2nd points.
                     const svfloat32_t y2)      ///< y-coord. of 2nd points.
{
  return jbm_nxf32_hypot (pg, svsub_f32_x (pg, x2, x1),
                          svsub_f32_x (pg, y2, y1));
}

/**
 * Function to calculate the length of a svfloat32_t vector of 3D segments.
 *
 * \return svfloat32_t vector of segment lengths.
 */
static inline svfloat32_t
jbm_nxf32_v3_length (svbool_t pg,       ///< predicate.
                     const svfloat32_t x1,      ///< x-coord. of 1st points.
                     const svfloat32_t y1,      ///< y-coord. of 1st points.
                     const svfloat32_t z1,      ///< z-coord. of 1st points.
                     const svfloat32_t x2,      ///< x-coord. of 2nd points.
                     const svfloat32_t y2,      ///< y-coord. of 2nd points.
                     const svfloat32_t z2)      ///< z-coord. of 2nd points.
{
  const svfloat32_t dx2 = jbm_nxf32_sqr (svsub_f32_x (pg, x2, x1));
  const svfloat32_t dy = svsub_f32_x (pg, y2, y1);
  const svfloat32_t dz = svsub_f32_x (pg, z2, z1);
  return
    svsqrt_f32_x (pg, svmla_f32_x (pg, svmla_f32_x (pg, dx2, dy, dy), dz, dz));
}

/**
 * Function to calculate a 1st order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_1 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return svmla_n_f32_x (pg, svdup_n_f32 (p[0]), x, p[1]);
}

/**
 * Function to calculate a 2nd order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_2 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_1 (pg, x, p + 1));
}

/**
 * Function to calculate a 3rd order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_3 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_2 (pg, x, p + 1));
}

/**
 * Function to calculate a 4th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_4 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_3 (pg, x, p + 1));
}

/**
 * Function to calculate a 5th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_5 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_4 (pg, x, p + 1));
}

/**
 * Function to calculate a 6th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_6 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_5 (pg, x, p + 1));
}

/**
 * Function to calculate a 7th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_7 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_6 (pg, x, p + 1));
}

/**
 * Function to calculate a 8th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_8 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_7 (pg, x, p + 1));
}

/**
 * Function to calculate a 9th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_9 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_8 (pg, x, p + 1));
}

/**
 * Function to calculate a 10th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_10 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_9 (pg, x, p + 1));
}

/**
 * Function to calculate a 11th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_11 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_10 (pg, x, p + 1));
}

/**
 * Function to calculate a 12th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_12 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_11 (pg, x, p + 1));
}

/**
 * Function to calculate a 13th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_13 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_12 (pg, x, p + 1));
}

/**
 * Function to calculate a 14th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_14 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_13 (pg, x, p + 1));
}

/**
 * Function to calculate a 15th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_15 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_14 (pg, x, p + 1));
}

/**
 * Function to calculate a 16th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_16 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_15 (pg, x, p + 1));
}

/**
 * Function to calculate a 17th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_17 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_16 (pg, x, p + 1));
}

/**
 * Function to calculate a 18th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_18 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_17 (pg, x, p + 1));
}

/**
 * Function to calculate a 19th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_19 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_18 (pg, x, p + 1));
}

/**
 * Function to calculate a 20th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_20 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_19 (pg, x, p + 1));
}

/**
 * Function to calculate a 21st order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_21 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_20 (pg, x, p + 1));
}

/**
 * Function to calculate a 22nd order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_22 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_21 (pg, x, p + 1));
}

/**
 * Function to calculate a 23rd order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_23 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_22 (pg, x, p + 1));
}

/**
 * Function to calculate a 24th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_24 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_23 (pg, x, p + 1));
}

/**
 * Function to calculate a 25th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_25 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_24 (pg, x, p + 1));
}

/**
 * Function to calculate a 26th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_26 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_25 (pg, x, p + 1));
}

/**
 * Function to calculate a 27th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_27 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_26 (pg, x, p + 1));
}

/**
 * Function to calculate a 28th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_28 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_27 (pg, x, p + 1));
}

/**
 * Function to calculate a 29th order polynomial (svfloat32_t).
 *
 * \return svfloat32_t vector of polynomial values.
 */
static inline svfloat32_t
jbm_nxf32_polynomial_29 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return svmla_f32_x (pg, svdup_n_f32 (p[0]), x,
                      jbm_nxf32_polynomial_28 (pg, x, p + 1));
}

/**
 * Function to calculate a 0th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_1_0 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[1]));
}

/**
 * Function to calculate a 0th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_2_0 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_2_1 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                      svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[2]));
}

/**
 * Function to calculate a 0th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_3_0 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_3_1 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_3_2 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[3]));
}

#endif
