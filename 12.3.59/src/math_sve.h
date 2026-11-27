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
jbm_nxf32_copysign (const svfloat32_t x,
		    ///< vector to preserve magnitude.
                    const svfloat32_t y)        ///< vector to preserve sign.
{
  return
    svreinterpret_f32_u32 (svbsl_u32 (svreinterpret_u32_f32 (y),
                                      svreinterpret_u32_f32 (x),
                                      svdup_n_u32 (JBM_F32_BITS_SIGN)));
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
 * Function to implement the standard frexp function (svfloat32_t).
 *
 * \return normalized fraction value in [1/2,1) (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_frexp (svbool_t pg,   ///< predicate.
                 const svfloat32_t x,   ///< svfloat32_t vector.
                 svint32_t *e)  ///< pointer to the exponents vector.
{
  const svuint32_t ai = svreinterpret_u32_f32 (x);
  const svuint32_t ai_abs = svand_n_u32_x (pg, ai, JBM_F32_BITS_ABS);
  const svbool_t m_special = svcmpge_n_u32 (pg, svsub_n_u32_x (pg, ai_abs, 1u),
                                            JBM_F32_BITS_EXPONENT - 1u);
  const svuint32_t yi = svlsr_n_u32_x (pg, ai_abs, 23);
  const svbool_t m_sub = svcmpeq_n_u32 (pg, yi, 0u);
  // Scale subnormals
  const svuint32_t zi_abs
    = svreinterpret_u32_f32 (svmul_n_f32_x (pg, svreinterpret_f32_u32 (ai_abs),
                                            0x1p23f));
  // Exponent
  *e = svdup_n_s32_m
    (svsel_s32 (m_sub,
                svsub_n_s32_x (m_sub,
                               svreinterpret_s32_u32 (svlsr_n_u32_x (m_sub,
                                                                     zi_abs,
                                                                     23u)),
                               JBM_F32_BIAS + 23u),
                svsub_n_s32_x (pg, svreinterpret_s32_u32 (yi), JBM_F32_BIAS)),
     m_special, 0);
  // Mantissa
  return
    svsel_f32
    (m_special, x,
     svreinterpret_f32_u32
     (svbsl_u32 (ai, svbsl_u32 (svsel_u32 (m_sub, zi_abs, ai_abs),
                                svdup_n_u32 ((uint32_t) JBM_F32_BIAS << 23u),
                                svdup_n_u32 (JBM_F32_BITS_MANTISSA)),
                 svdup_n_u32 (JBM_F32_BITS_SIGN))));
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (svint32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_exp2n (svbool_t pg,   ///< predicate.
                 const svint32_t e)     ///< exponent vector (svint32_t).
{
  return svscale_f32_x (pg, svdup_n_f32 (1.f), e);
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
  return svscale_f32_x (pg, x, e);
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
  const svfloat32_t dx2 = jbm_nxf32_sqr (pg, svsub_f32_x (pg, x2, x1));
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
 * Function to calculate a 21th order polynomial (svfloat32_t).
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
 * Function to calculate a 22th order polynomial (svfloat32_t).
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
 * Function to calculate a 23th order polynomial (svfloat32_t).
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
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
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

/**
 * Function to calculate a 0th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_4_0 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_4_1 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_4_2 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_4_3 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[4]));
}

/**
 * Function to calculate a 0th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_5_0 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_5_1 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_5_2 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_5_3 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_5_4 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[5]));
}

/**
 * Function to calculate a 0th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_6_0 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_6_1 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_6_2 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_6_3 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_6_4 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_6_5 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[6]));
}

/**
 * Function to calculate a 0th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_7_0 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_7_1 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_7_2 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_7_3 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_7_4 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_7_5 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_7_6 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[7]));
}

/**
 * Function to calculate a 0th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_8_0 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_8_1 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_8_2 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_8_3 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_8_4 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_8_5 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_8_6 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_8_7 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[8]));
}

/**
 * Function to calculate a 0th+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_9_0 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_9_1 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_9_2 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_9_3 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_9_4 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_9_5 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_9_6 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_9_7 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_9_8 (svbool_t pg,    ///< predicate.
                        const svfloat32_t x,    ///< svfloat32_t vector.
                        const float *p) ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[9]));
}

/**
 * Function to calculate a 0th+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_10_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_10_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_10_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_10_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_10_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_10_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_10_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_10_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_10_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_10_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[10]));
}

/**
 * Function to calculate a 0th+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_11_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_11_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_11_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_11_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_11_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_11_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_11_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_11_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_11_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_11_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_11_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[11]));
}

/**
 * Function to calculate a 0th+12th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_12_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_11 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_12_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_12_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_12_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_12_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_12_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_12_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_12_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_12_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_12_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_12_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_12_11 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_11 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[12]));
}

/**
 * Function to calculate a 0th+13th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_13_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_12 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+12th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_13_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_11 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_13_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_13_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_13_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_13_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_13_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_13_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_13_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_13_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_13_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_13_11 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_11 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_13_12 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_12 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[13]));
}

/**
 * Function to calculate a 0th+14th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_14_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_13 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+13th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_14_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_12 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+12th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_14_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_11 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_14_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_14_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_14_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_14_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_14_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_14_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_14_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_14_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_14_11 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_11 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_14_12 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_12 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_14_13 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_13 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[14]));
}

/**
 * Function to calculate a 0th+15th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_15_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_14 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+14th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_15_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_13 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+13th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_15_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_12 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+12th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_15_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_11 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_15_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_15_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_15_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_15_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_15_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_15_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_15_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_15_11 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_11 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_15_12 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_12 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_15_13 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_13 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_15_14 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_14 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[15]));
}

/**
 * Function to calculate a 0th+16th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_16_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_15 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+15th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_16_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_14 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+14th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_16_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_13 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+13th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_16_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_12 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+12th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_16_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_11 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_16_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_16_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_16_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_16_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_16_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_16_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_16_11 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_11 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_16_12 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_12 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_16_13 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_13 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_16_14 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_14 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_16_15 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_15 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[16]));
}

/**
 * Function to calculate a 0th+17th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_17_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_16 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+16th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_17_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_15 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+15th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_17_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_14 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+14th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_17_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_13 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+13th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_17_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_12 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+12th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_17_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_11 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_17_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_17_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_17_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_17_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_17_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_17_11 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_11 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_17_12 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_12 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_17_13 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_13 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_17_14 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_14 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_17_15 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_15 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_17_16 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_16 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[17]));
}

/**
 * Function to calculate a 0th+18th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_18_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_17 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+17th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_18_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_16 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+16th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_18_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_15 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+15th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_18_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_14 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+14th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_18_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_13 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+13th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_18_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_12 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+12th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_18_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_11 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_18_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_18_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_18_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_18_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_18_11 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_11 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_18_12 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_12 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_18_13 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_13 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_18_14 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_14 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_18_15 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_15 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_18_16 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_16 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_18_17 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_17 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[18]));
}

/**
 * Function to calculate a 0th+19th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_18 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+18th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_17 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+17th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_16 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+16th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_15 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+15th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_14 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+14th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_13 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+13th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_12 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+12th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_11 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_11 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_11 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_12 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_12 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_13 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_13 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_14 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_14 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_15 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_15 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_16 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_16 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_17 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_17 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_19_18 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_18 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[19]));
}

/**
 * Function to calculate a 0th+20th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_19 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+19th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_18 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+18th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_17 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+17th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_16 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+16th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_15 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+15th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_14 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+14th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_13 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+13th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_12 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+12th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_11 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_11 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_11 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_12 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_12 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_13 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_13 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_14 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_14 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_15 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_15 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_16 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_16 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_17 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_17 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_18 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_18 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_20_19 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_19 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[20]));
}

/**
 * Function to calculate a 0th+21th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_20 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+20th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_19 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+19th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_18 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+18th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_17 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+17th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_16 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+16th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_15 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+15th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_14 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+14th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_13 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+13th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_12 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+12th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_11 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_11 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_11 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_12 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_12 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_13 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_13 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_14 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_14 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_15 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_15 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_16 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_16 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_17 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_17 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_18 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_18 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_19 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_19 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 20)));
}

/**
 * Function to calculate a 20th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_21_20 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_20 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[21]));
}

/**
 * Function to calculate a 0th+22th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_21 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+21th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_20 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+20th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_19 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+19th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_18 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+18th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_17 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+17th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_16 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+16th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_15 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+15th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_14 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+14th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_13 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+13th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_12 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+12th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_11 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_11 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_11 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_12 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_12 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_13 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_13 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_14 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_14 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_15 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_15 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_16 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_16 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_17 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_17 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_18 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_18 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_19 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_19 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 20)));
}

/**
 * Function to calculate a 20th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_20 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_20 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 21)));
}

/**
 * Function to calculate a 21th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_22_21 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_21 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[22]));
}

/**
 * Function to calculate a 0th+23th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_22 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+22th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_21 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+21th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_20 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+20th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_19 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+19th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_18 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+18th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_17 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+17th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_16 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+16th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_15 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+15th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_14 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+14th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_13 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+13th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_12 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+12th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_11 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_11 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_11 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_12 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_12 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_13 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_13 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_14 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_14 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_15 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_15 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_16 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_16 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_17 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_17 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_18 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_18 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_19 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_19 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 20)));
}

/**
 * Function to calculate a 20th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_20 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_20 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 21)));
}

/**
 * Function to calculate a 21th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_21 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_21 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 22)));
}

/**
 * Function to calculate a 22th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_23_22 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_22 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[23]));
}

/**
 * Function to calculate a 0th+24th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_23 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+23th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_22 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+22th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_21 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+21th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_20 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+20th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_19 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+19th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_18 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+18th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_17 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+17th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_16 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+16th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_15 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+15th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_14 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+14th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_13 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+13th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_11 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_11 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_12 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+12th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_12 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_12 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_11 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_13 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_13 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_14 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_14 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_15 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_15 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_16 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_16 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_17 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_17 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_18 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_18 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_19 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_19 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 20)));
}

/**
 * Function to calculate a 20th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_20 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_20 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 21)));
}

/**
 * Function to calculate a 21th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_21 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_21 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 22)));
}

/**
 * Function to calculate a 22th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_22 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_22 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 23)));
}

/**
 * Function to calculate a 23th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_24_23 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_23 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[24]));
}

/**
 * Function to calculate a 0th+25th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_24 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+24th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_23 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+23th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_22 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+22th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_21 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+21th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_20 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+20th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_19 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+19th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_18 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+18th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_17 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+17th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_16 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+16th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_15 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+15th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_14 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+14th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_11 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_11 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_13 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+13th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_12 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_12 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_12 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+12th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_13 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_13 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_11 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_14 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_14 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_15 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_15 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_16 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_16 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_17 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_17 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_18 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_18 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_19 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_19 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 20)));
}

/**
 * Function to calculate a 20th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_20 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_20 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 21)));
}

/**
 * Function to calculate a 21th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_21 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_21 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 22)));
}

/**
 * Function to calculate a 22th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_22 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_22 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 23)));
}

/**
 * Function to calculate a 23th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_23 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_23 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 24)));
}

/**
 * Function to calculate a 24th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_25_24 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_24 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[25]));
}

/**
 * Function to calculate a 0th+26th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_25 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+25th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_24 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+24th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_23 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+23th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_22 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+22th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_21 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+21th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_20 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+20th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_19 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+19th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_18 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+18th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_17 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+17th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_16 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+16th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_15 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+15th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_11 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_11 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_14 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+14th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_12 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_12 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_13 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+13th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_13 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_13 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_12 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+12th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_14 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_14 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_11 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_15 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_15 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_16 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_16 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_17 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_17 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_18 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_18 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_19 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_19 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 20)));
}

/**
 * Function to calculate a 20th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_20 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_20 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 21)));
}

/**
 * Function to calculate a 21th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_21 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_21 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 22)));
}

/**
 * Function to calculate a 22th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_22 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_22 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 23)));
}

/**
 * Function to calculate a 23th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_23 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_23 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 24)));
}

/**
 * Function to calculate a 24th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_24 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_24 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 25)));
}

/**
 * Function to calculate a 25th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_26_25 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_25 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[26]));
}

/**
 * Function to calculate a 0th+27th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_26 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+26th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_25 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+25th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_24 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+24th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_23 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+23th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_22 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+22th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_21 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+21th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_20 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+20th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_19 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+19th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_18 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+18th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_17 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+17th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_16 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+16th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_11 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_11 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_15 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+15th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_12 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_12 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_14 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+14th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_13 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_13 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_13 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+13th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_14 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_14 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_12 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+12th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_15 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_15 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_11 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_16 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_16 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_17 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_17 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_18 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_18 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_19 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_19 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 20)));
}

/**
 * Function to calculate a 20th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_20 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_20 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 21)));
}

/**
 * Function to calculate a 21th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_21 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_21 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 22)));
}

/**
 * Function to calculate a 22th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_22 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_22 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 23)));
}

/**
 * Function to calculate a 23th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_23 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_23 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 24)));
}

/**
 * Function to calculate a 24th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_24 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_24 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 25)));
}

/**
 * Function to calculate a 25th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_25 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_25 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 26)));
}

/**
 * Function to calculate a 26th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_27_26 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_26 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[27]));
}

/**
 * Function to calculate a 0th+28th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_27 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+27th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_26 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+26th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_25 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+25th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_24 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+24th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_23 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+23th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_22 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+22th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_21 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+21th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_20 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+20th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_19 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+19th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_18 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+18th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_17 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+17th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_11 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_11 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_16 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+16th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_12 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_12 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_15 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+15th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_13 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_13 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_14 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+14th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_14 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_14 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_13 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+13th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_15 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_15 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_12 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+12th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_16 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_16 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_11 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_17 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_17 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_18 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_18 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_19 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_19 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 20)));
}

/**
 * Function to calculate a 20th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_20 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_20 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 21)));
}

/**
 * Function to calculate a 21th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_21 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_21 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 22)));
}

/**
 * Function to calculate a 22th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_22 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_22 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 23)));
}

/**
 * Function to calculate a 23th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_23 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_23 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 24)));
}

/**
 * Function to calculate a 24th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_24 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_24 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 25)));
}

/**
 * Function to calculate a 25th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_25 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_25 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 26)));
}

/**
 * Function to calculate a 26th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_26 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_26 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 27)));
}

/**
 * Function to calculate a 27th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_28_27 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_27 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[28]));
}

/**
 * Function to calculate a 0th+29th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_0 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, svdup_n_f32 (p[0]),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_28 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+28th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_1 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_1 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_27 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+27th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_2 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_2 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_26 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+26th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_3 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_3 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_25 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+25th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_4 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_4 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_24 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+24th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_5 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_5 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_23 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+23th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_6 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_6 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_22 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+22th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_7 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_7 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_21 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+21th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_8 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_8 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_20 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+20th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_9 (svbool_t pg,   ///< predicate.
                         const svfloat32_t x,   ///< svfloat32_t vector.
                         const float *p)        ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_9 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_19 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+19th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_10 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_10 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_18 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+18th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_11 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_11 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_17 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+17th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_12 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_12 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_16 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+16th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_13 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_13 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_15 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+15th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_14 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_14 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_14 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+14th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_15 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_15 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_13 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+13th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_16 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_16 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_12 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+12th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_17 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_17 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_11 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+11th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_18 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_18 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_10 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+10th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_19 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_19 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_9 (pg, x, p + 20)));
}

/**
 * Function to calculate a 20th+9th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_20 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_20 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_8 (pg, x, p + 21)));
}

/**
 * Function to calculate a 21th+8th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_21 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_21 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_7 (pg, x, p + 22)));
}

/**
 * Function to calculate a 22th+7th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_22 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_22 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_6 (pg, x, p + 23)));
}

/**
 * Function to calculate a 23th+6th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_23 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_23 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_5 (pg, x, p + 24)));
}

/**
 * Function to calculate a 24th+5th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_24 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_24 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_4 (pg, x, p + 25)));
}

/**
 * Function to calculate a 25th+4th order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_25 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_25 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_3 (pg, x, p + 26)));
}

/**
 * Function to calculate a 26th+3rd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_26 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_26 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_2 (pg, x, p + 27)));
}

/**
 * Function to calculate a 27th+2nd order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_27 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_27 (pg, x, p),
                 svmla_f32_x (pg, svdup_n_f32 (1.f), x,
                              jbm_nxf32_polynomial_1 (pg, x, p + 28)));
}

/**
 * Function to calculate a 28th+1st order rational (svfloat32_t).
 *
 * \return svfloat32_t vector of rational values.
 */
static inline svfloat32_t
jbm_nxf32_rational_29_28 (svbool_t pg,  ///< predicate.
                          const svfloat32_t x,  ///< svfloat32_t vector.
                          const float *p)       ///< array of coefficients.
{
  return
    svdiv_f32_x (pg, jbm_nxf32_polynomial_28 (pg, x, p),
                 svmla_n_f32_x (pg, svdup_n_f32 (1.f), x, p[29]));
}

/**
 * Function to calculate the well-conditioned function cbrt(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_cbrtwc (svbool_t pg,  ///< predicate.
                  const svfloat32_t x)
                  ///< svfloat32_t vector \f$\in\left[\frac12,\;1\right]\f$.
{
  return jbm_nxf32_rational_5_3 (pg, x, K_CBRTWC_F32);
}

/**
 * Function to calculate the function cbrt(x) (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_cbrt (svbool_t pg,    ///< predicate.
                const svfloat32_t x)    ///< svfloat32_t vector.
{
  const svfloat32_t xa = svabs_f32_x (pg, x);
  svfloat32_t f, s, ef;
  svint32_t e, q, r;
  svbool_t m_special;
  f = jbm_nxf32_frexp (pg, xa, &e);
  ef = svcvt_f32_s32_x (pg, e);
  ef = svmul_n_f32_x (pg, ef, 1.f / 3.f);
  q = jbm_nxf32_floor (pg, ef);
  r = svmls_n_s32_x (pg, e, q, 3);
  s = svdup_n_f32 (1.f);
  s = svsel_f32 (svcmpeq_n_s32 (pg, r, 1), svdup_n_f32 (JBM_F32_CBRT2), s);
  s = svsel_f32 (svcmpeq_n_s32 (pg, r, 2), svdup_n_f32 (JBM_F32_CBRT4), s);
  f = svmul_f32_x (pg, jbm_nxf32_cbrtwc (pg, f), s);
  f = jbm_nxf32_ldexp (pg, f, q);
  f = jbm_nxf32_copysign (f, x);
  m_special
    = svorr_b_z (pg, svcmpeq_n_f32 (pg, xa, 0.f),
                 svorr_b_z (pg, svcmpeq_n_f32 (pg, xa, INFINITY),
                            svcmpne_f32 (pg, xa, xa)));
  return svsel_f32 (m_special, x, f);
}

/**
 * Function to calculate the well-conditioned function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (svfloat32_t).
 *
 * \return function value.
 */
static inline svfloat32_t
jbm_nxf32_exp2wc (svbool_t pg,  ///< predicate.
                  const svfloat32_t x)
                  ///< svfloat32_t vector \f$\in[\frac12,1]\f$.
{
  return jbm_nxf32_polynomial_5 (pg, x, K_EXP2WC_F32);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_nxf32 and
 * jbm_nxf32_exp2n functions (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_exp2 (svbool_t pg,    ///< predicate.
                const svfloat32_t x)    ///< svfloat32_t vector.
{
  const svint32_t i = jbm_nxf32_floor (pg, x);
  const svfloat32_t f = svsub_f32_x (pg, x, svcvt_f32_s32_x (pg, i));
  return jbm_nxf32_ldexp (pg, jbm_nxf32_exp2wc (pg, f), i);
}

/**
 * Function to calculate the function exp(x) using the jbm_nxf32_exp2 function
 * (svfloat32_t).
 *
 * \return function value.
 */
static inline svfloat32_t
jbm_nxf32_exp (svbool_t pg,     ///< predicate.
               const svfloat32_t x)     ///< svfloat32_t vector.
{
  return jbm_nxf32_exp2 (pg, svmul_n_f32_x (pg, x, M_LOG2Ef));
}

/**
 * Function to calculate the function exp10(x) using the jbm_nxf32_exp2
 * function (svfloat32_t).
 *
 * \return function value.
 */
static inline svfloat32_t
jbm_nxf32_exp10 (svbool_t pg,   ///< predicate.
                 const svfloat32_t x)   ///< svfloat32_t vector.
{
  return jbm_nxf32_exp2 (pg, svmul_n_f32_x (pg, x, M_LN10f / M_LN2f));
}

/**
 * Function to calculate the well-conditioned function expm1(x) for
 * \f$x\in\left[-\log(2)/2,\log(2)/2\right]\f$ (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_expm1wc (svbool_t pg, ///< predicate.
                   const svfloat32_t x)
///< svfloat32_t vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  const float a1 = K_EXPM1WC_F32[0];
  const float b1 = K_EXPM1WC_F32[1];
  const float b2 = K_EXPM1WC_F32[2];
  const float b4 = K_EXPM1WC_F32[3];
  svfloat32_t x2;
  x2 = jbm_nxf32_sqr (pg, x);
  x2 = svmla_n_f32_x (pg, svdup_n_f32 (b2), x2, b4);
  x2 = svmla_f32_x (pg, svdup_n_f32 (b1), x2, x);
  x2 = svmla_f32_x (pg, svdup_n_f32 (1.f), x2, x);
  return svmul_f32_x (pg, x, svdiv_f32_x (pg, svdup_n_f32 (a1), x2));
}

/**
 * Function to calculate the function expm1(x) using the jbm_nxf32_expm1wc and
 * jbm_nxf32_exp functions (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_expm1 (svbool_t pg,   ///< predicate.
                 const svfloat32_t x)   ///< svfloat32_t vector.
{
  return
    svsel_f32 (svcmplt_n_f32 (pg, jbm_nxf32_abs (pg, x), M_LN2f / 2.f),
               jbm_nxf32_expm1wc (pg, x),
               svsub_n_f32_x (pg, jbm_nxf32_exp (pg, x), 1.f));
}

/**
 * Function to calculate the well-conditioned function log2(x) for x in
 * [0.5,1] (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_log2wc (svbool_t pg,  ///< predicate.
                  const svfloat32_t x)
                  ///< svfloat32_t vector \f$\in[0.5,1]\f$.
{
  return svmul_f32_x (pg, x, jbm_nxf32_rational_5_2 (pg, x, K_LOG2WC_F32));
}

/**
 * Function to calculate the function log_2(x) using jbm_nxf32_log2wc and
 * jbm_nxf32_frexp (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_log2 (svbool_t pg,    ///< predicate.
                const svfloat32_t x)    ///< svfloat32_t vector.
{
  svfloat32_t y;
  svint32_t e, e1;
  svbool_t m;
  y = jbm_nxf32_frexp (pg, x, &e);
  m = svcmplt_n_f32 (pg, y, M_SQRT1_2f);
  y = svsel_f32 (m, svadd_f32_x (pg, y, y), y);
  e1 = svsub_n_s32_x (pg, e, 1);
  e = svsel_s32 (m, e1, e);
  y = svadd_f32_x (pg, jbm_nxf32_log2wc (pg, svsub_n_f32_x (pg, y, 1.f)),
                   svcvt_f32_s32_x (pg, e));
  y = svsel_f32 (svcmpeq_n_f32 (pg, x, 0.f), svdup_n_f32 (-INFINITY), y);
  y = svsel_f32 (svcmpeq_n_f32 (pg, x, INFINITY), svdup_n_f32 (INFINITY), y);
  y = svsel_f32 (svcmplt_n_f32 (pg, x, 0.f), svdup_n_f32 (NAN), y);
  return svsel_f32 (svcmpne_f32 (pg, x, x), x, y);
}

/**
 * Function to calculate the function log(x) using jbm_nxf32_log2
 * (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_log (svbool_t pg,     ///< predicate.
               const svfloat32_t x)     ///< svfloat32_t vector.
{
  return svmul_n_f32_x (pg, jbm_nxf32_log2 (pg, x), M_LN2f);
}

/**
 * Function to calculate the function log10(x) using jbm_nxf32_log2.
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_log10 (svbool_t pg,   ///< predicate.
                 const svfloat32_t x)   ///< svfloat32_t vector.
{
  return svmul_n_f32_x (pg, jbm_nxf32_log2 (pg, x), M_LN2f / M_LN10f);
}

/**
 * Function to calculate the function x^e with e an integer number
 * (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_pown (svbool_t pg,    ///< predicate.
                const svfloat32_t x,    ///< svfloat32_t vector.
                const int e)    ///< exponent (int).
{
  svfloat32_t f, xn;
  unsigned int i;
  f = svdup_n_f32 (1.f);
  if (e < 0)
    xn = jbm_nxf32_reciprocal (pg, x);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_nxf32_sqr (pg, xn))
    if (i & 1)
      f = svmul_f32_x (pg, f, xn);
  return f;
}

/**
 * Function to calculate the function pow using the jbm_nxf32_exp2 and
 * jbm_nxf32_log2 functions (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_pow1 (svbool_t pg,    ///< predicate.
                const svfloat32_t x,    ///< svfloat32_t vector.
                const float e)  ///< exponent (float).
{
  return jbm_nxf32_exp2 (pg, svmul_n_f32_x (pg, jbm_nxf32_log2 (pg, x), e));
}

/**
 * Function to calculate the function pow using the jbm_nxf32_exp2 and
 * jbm_nxf32_log2 functions (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_pow (svbool_t pg,     ///< predicate.
               const svfloat32_t x,     ///< svfloat32_t vector.
               const svfloat32_t e)     ///< exponent (svfloat32_t).
{
  return jbm_nxf32_exp2 (pg, svmul_f32_x (pg, jbm_nxf32_log2 (pg, x), e));
}

/**
 * Function to calculate the well-conditioned function sin(x) for x in
 * [-pi/4,pi/4] (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_sinwc (svbool_t pg,   ///< predicate.
                 const svfloat32_t x)
                 ///< svfloat32_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return svmul_f32_x (pg, x,
                      jbm_nxf32_polynomial_3 (pg, jbm_nxf32_sqr (pg, x),
                                              K_SINWC_F32));
}

/**
 * Function to calculate the well-conditioned function cos(x) for x in
 * [-pi/4,pi/4] (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_coswc (svbool_t pg,   ///< predicate.
                 const svfloat32_t x)
                 ///< svfloat32_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return jbm_nxf32_polynomial_3 (pg, jbm_nxf32_sqr (pg, x), K_COSWC_F32);
}

/**
 * Function to calculate the well-conditioned function tan(x) for x in
 * [-pi/4,pi/4] (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_tanwc (svbool_t pg,   ///< predicate.
                 const svfloat32_t x)
                 ///< svfloat32_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return svmul_f32_x (pg, x,
                      jbm_nxf32_rational_3_1 (pg, jbm_nxf32_sqr (pg, x),
                                              K_TANWC_F32));
}

/**
 * Function to calculate the well-conditioned functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_nxf32_sinwc approximation (svfloat32_t).
 */
static inline void
jbm_nxf32_sincoswc (svbool_t pg,        ///< predicate.
                    const svfloat32_t x,
                    ///< svfloat32_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                    svfloat32_t *s,     ///< pointer to the sin function value.
                    svfloat32_t *c)     ///< pointer to the cos function value.
{
  const svfloat32_t x2 = jbm_nxf32_sqr (pg, x);
  *s = svmul_f32_x (pg, x, jbm_nxf32_polynomial_3 (pg, x2, K_SINWC_F32));
  *c = jbm_nxf32_polynomial_3 (pg, x2, K_COSWC_F32);
}

/**
 * Function to calculate reduction to \f$2\,\pi\f$ in trigonometric functions
 * (svfloat32_t).
 *
 * \return reduced vector (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_trig (svbool_t pg,    ///< predicate.
                const svfloat32_t x,    ///< svfloat32_t vector.
                svint32_t *q)   ///< pointer to the quadrant (svint32_t).
{
  const svfloat32_t t = svmul_n_f32_x (pg, x, M_2_PIf);
  *q = jbm_nxf32_round (pg, t);
  return svmls_n_f32_x (pg, x, svcvt_f32_s32_x (pg, *q), M_PI_2f);
}

/**
 * Function to calculate the function sin(x) from jbm_nxf32_sinwc and
 * jbm_nxf32_coswc approximations (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_sin (svbool_t pg,     ///< predicate.
               const svfloat32_t x)     ///< svfloat32_t vector.
{
  svfloat32_t y, s, c;
  svint32_t q;
  y = jbm_nxf32_trig (pg, x, &q);
  jbm_nxf32_sincoswc (pg, y, &s, &c);
  y = svsel_f32 (svcmpne_n_s32 (pg, svand_n_s32_x (pg, q, 1), 0), c, s);
  return svsel_f32 (svcmpne_n_s32 (pg, svand_n_s32_x (pg, q, 2), 0),
                    jbm_nxf32_opposite (pg, y), y);
}

/**
 * Function to calculate the function cos(x) from jbm_nxf32_sinwc and
 * jbm_nxf32_coswc approximations (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_cos (svbool_t pg,     ///< predicate.
               const svfloat32_t x)     ///< svfloat32_t vector.
{
  svfloat32_t y, s, c;
  svint32_t q;
  y = jbm_nxf32_trig (pg, x, &q);
  jbm_nxf32_sincoswc (pg, y, &s, &c);
  y = svsel_f32 (svcmpne_n_s32 (pg, svand_n_s32_x (pg, q, 1), 0), s, c);
  q = svadd_n_s32_x (pg, q, 1);
  return svsel_f32 (svcmpne_n_s32 (pg, svand_n_s32_x (pg, q, 2), 0),
                    jbm_nxf32_opposite (pg, y), y);
}

/**
 * Function to calculate the functions sin(x) and cos(x) from
 * jbm_nxf32_sinwc and jbm_nxf32_coswc approximations (svfloat32_t).
 */
static inline void
jbm_nxf32_sincos (svbool_t pg,  ///< predicate.
                  const svfloat32_t x,  ///< svfloat32_t vector.
                  svfloat32_t *s,       ///< pointer to the sin function value.
                  svfloat32_t *c)       ///< pointer to the cos function value.
{
  svfloat32_t y, s1, c1, s2, c2;
  svint32_t q;
  svbool_t m;
  y = jbm_nxf32_trig (pg, x, &q);
  jbm_nxf32_sincoswc (pg, y, &s1, &c1);
  m = svcmpne_n_s32 (pg, svand_n_s32_x (pg, q, 1), 0);
  s2 = svsel_f32 (m, c1, s1);
  c2 = svsel_f32 (m, s1, c1);
  m = svcmpne_n_s32 (pg, svand_n_s32_x (pg, q, 2), 0);
  *s = svsel_f32 (m, jbm_nxf32_opposite (pg, s2), s2);
  q = svadd_n_s32_x (pg, q, 1);
  m = svcmpne_n_s32 (pg, svand_n_s32_x (pg, q, 2), 0);
  *c = svsel_f32 (m, jbm_nxf32_opposite (pg, c2), c2);
}

/**
 * Function to calculate the function tan(x) from jbm_nxf32_sincos function
 * (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_tan (svbool_t pg,     ///< predicate.
               const svfloat32_t x)     ///< svfloat32_t vector.
{
  svfloat32_t y, z;
  svint32_t q;
  y = jbm_nxf32_tanwc (pg, jbm_nxf32_trig (pg, x, &q));
  z = svdivr_n_f32_x (pg, y, -1.f);
  return svsel_f32 (svcmpne_n_s32 (pg, svand_n_s32_x (pg, q, 1), 0), z, y);
}

/**
 * Function to calculate the well-conditioned function atan(x) for x in [-1,1]
 * (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_atanwc (svbool_t pg,  ///< predicate.
                  const svfloat32_t x)
                  ///< svfloat32_t vector \f$\in\left[-1,1\right]\f$.
{
  return svmul_f32_x (pg, x,
                      jbm_nxf32_rational_4_2 (pg, jbm_nxf32_sqr (pg, x),
                                              K_ATANWC_F32));
}

/**
 * Function to calculate the function atan(x) using the jbm_nxf32_atanwc
 * function (svfloat32_t).
 *
 * \return function value (in [-pi/2,pi/2]) (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_atan (svbool_t pg,    ///< predicate.
                const svfloat32_t x)    ///< svfloat32_t vector.
{
  svfloat32_t f, ax;
  svbool_t m;
  ax = jbm_nxf32_abs (pg, x);
  m = svcmpgt_n_f32 (pg, ax, 1.f);
  ax = svsel_f32 (m, jbm_nxf32_reciprocal (pg, ax), ax);
  f = jbm_nxf32_atanwc (pg, ax);
  f = svsel_f32 (m, svsub_f32_x (pg, svdup_n_f32 (M_PI_2f), f), f);
  return jbm_nxf32_copysign (f, x);
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_nxf32_atan
 * function (svfloat32_t).
 *
 * \return function value (in [-pi,pi]) (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_atan2 (svbool_t pg,   ///< predicate.
                 const svfloat32_t y,   ///< svfloat32_t y component.
                 const svfloat32_t x)   ///< svfloat32_t x component.
{
  const svfloat32_t f = jbm_nxf32_atan (pg, svdiv_f32_x (pg, y, x));
  return
    svsel_f32 (svcmpne_n_u32 (pg,
                              svand_n_u32_x (pg, svreinterpret_u32_f32 (x),
                                             JBM_F32_BITS_SIGN), 0),
               svadd_f32_x (pg, f,
                            jbm_nxf32_copysign (svdup_n_f32 (M_PIf), y)), f);
}

/**
 * Function to calculate the function asin(x) using the jbm_nxf32_atan function
 * (svfloat32_t).
 *
 * \return function value (svfloat32_t in [-pi/2,pi/2]).
 */
static inline svfloat32_t
jbm_nxf32_asin (svbool_t pg,    ///< predicate.
                const svfloat32_t x)    ///< svfloat32_t vector.
{
  return
    jbm_nxf32_atan
    (pg, svdiv_f32_x (pg, x,
                      svsqrt_f32_x (pg,
                                    svmls_f32_x (pg,
                                                 svdup_n_f32 (1.f), x, x))));
}

/**
 * Function to calculate the function acos(x) using the jbm_nxf32_atan function
 * (svfloat32_t).
 *
 * \return function value (in [0,pi]) (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_acos (svbool_t pg,    ///< predicate.
                const svfloat32_t x)    ///< svfloat32_t vector.
{
  const svfloat32_t k1 = svdup_n_f32 (1.f);
  return
    jbm_nxf32_dbl
    (pg,
     jbm_nxf32_atan (pg,
                     svsqrt_f32_x (pg,
                                   svdiv_f32_x (pg, svsub_f32_x (pg, k1, x),
                                                svadd_f32_x (pg, k1, x)))));
}

/**
 * Function to calculate the function sinh(x).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_sinh (svbool_t pg,    ///< predicate.
                const svfloat32_t x)    ///< svfloat32_t vector.
{
  const svfloat32_t f = jbm_nxf32_expm1 (pg, jbm_nxf32_abs (pg, x));
  return
    jbm_nxf32_copysign
    (svmul_n_f32_x (pg,
                    svadd_f32_x (pg, f,
                                 svdiv_f32_x (pg, f,
                                              svadd_n_f32_x (pg, f, 1.f))),
                    0.5f), x);
}

/**
 * Function to calculate the function cosh(x).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_cosh (svbool_t pg,    ///< predicate.
                const svfloat32_t x)    ///< svfloat32_t vector.
{
  const svfloat32_t f = jbm_nxf32_exp (pg, x);
  return svmul_n_f32_x (pg, svadd_f32_x (pg, f, jbm_nxf32_reciprocal (pg, f)),
                        0.5f);
}

/**
 * Function to calculate the function tanh(x).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_tanh (svbool_t pg,    ///< predicate.
                const svfloat32_t x)    ///< svfloat32_t vector.
{
  const svfloat32_t x2 = jbm_nxf32_dbl (pg, x);
  svfloat32_t f = jbm_nxf32_expm1 (pg, x2);
  f = svdiv_f32_x (pg, f, svadd_n_f32_x (pg, f, 2.f));
  f = svsel_f32 (svcmpgt_n_f32 (pg, x2, JBM_FLT_MAX_E_EXP),
                 svdup_n_f32 (1.f), f);
  return svsel_f32 (svcmplt_n_f32 (pg, x2, -JBM_FLT_MAX_E_EXP),
                    svdup_n_f32 (-1.f), f);
}

/**
 * Function to calculate the function asinh(x).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_asinh (svbool_t pg,   ///< predicate.
                 const svfloat32_t x)   ///< svfloat32_t vector.
{
  return
    jbm_nxf32_log (pg,
                   svadd_f32_x (pg, x,
                                svsqrt_f32_x (pg,
                                              svmla_f32_x (pg,
                                                           svdup_n_f32 (1.f), x,
                                                           x))));
}

/**
 * Function to calculate the function acosh(x).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_acosh (svbool_t pg,   ///< predicate.
                 const svfloat32_t x)   ///< svfloat32_t vector.
{
  return
    jbm_nxf32_log (pg,
                   svadd_f32_x (pg, x,
                                svsqrt_f32_x (pg,
                                              svsub_n_f32_x (pg,
                                                             jbm_nxf32_sqr (pg,
                                                                            x),
                                                             1.f))));
}

/**
 * Function to calculate the function atanh(x).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_atanh (svbool_t pg,   ///< predicate.
                 const svfloat32_t x)   ///< svfloat32_t vector.
{
  const svfloat32_t u = svdup_n_f32 (1.f);
  return
    svmul_n_f32_x (pg, jbm_nxf32_log (pg,
                                      svdiv_f32_x (pg, svadd_f32_x (pg, u, x),
                                                   svsub_f32_x (pg, u, x))),
                   0.5f);
}

/**
 * Function to calculate the well-conditioned function erf(x) for x in
 * [-1,1] (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_erfwc (svbool_t pg,   ///< predicate.
                 const svfloat32_t x)
                 ///< svfloat32_t vector \f$\in\left[-1,1\right]\f$.
{
  return svmul_f32_x (pg, x,
                      jbm_nxf32_polynomial_5 (pg, jbm_nxf32_sqr (pg, x),
                                              K_ERFWC_F32));
}

/**
 * Function to calculate the well-conditioned function erfc(x) for
 * \f$x\in[1,\infty]\f$ (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_erfcwc (svbool_t pg,  ///< predicate.
                  const svfloat32_t x)
                  ///< svfloat32_t vector \f$\in\left[1,\infty\right]\f$.
{
  return
    svsel_f32 (svcmpgt_n_f32 (pg, x, K_ERFC_MAX_F32), svdup_n_f32 (0.f),
               svmul_f32_x (pg,
                            jbm_nxf32_rational_7_4 (pg,
                                                    jbm_nxf32_reciprocal (pg,
                                                                          x),
                                                    K_ERFCWC_F32),
                            svdiv_f32_x (pg, x,
                                         jbm_nxf32_exp (pg,
                                                        jbm_nxf32_sqr (pg,
                                                                       x)))));
}

/**
 * Function to calculate the function erf(x) using jbm_nxf32_erfwc and
 * jbm_nxf32_erfcwc (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_erf (svbool_t pg,     ///< predicate.
               const svfloat32_t x)     ///< svfloat32_t vector.
{
  const svfloat32_t ax = jbm_nxf32_abs (pg, x);
  const svfloat32_t u = svdup_n_f32 (1.f);
  return
    svsel_f32 (svcmplt_f32 (pg, ax, u), jbm_nxf32_erfwc (pg, x),
               svmul_f32_x (pg, svdiv_f32_x (pg, x, ax),
                            svsub_f32_x (pg, u, jbm_nxf32_erfcwc (pg, ax))));
}

/**
 * Function to calculate the function erfc(x) using jbm_nxf32_erfwc and
 * jbm_nxf32_erfcwc (svfloat32_t).
 *
 * \return function value (svfloat32_t).
 */
static inline svfloat32_t
jbm_nxf32_erfc (svbool_t pg,    ///< predicate.
                const svfloat32_t x)    ///< svfloat32_t vector.
{
  const svfloat32_t ax = jbm_nxf32_abs (pg, x);
  const svfloat32_t u = svdup_n_f32 (1.f);
  return
    svsel_f32 (svcmplt_f32 (pg, ax, u),
               svsub_f32_x (pg, u, jbm_nxf32_erfwc (pg, x)),
               svsub_f32_x (pg, u,
                            svmul_f32_x (pg, svdiv_f32_x (pg, x, ax),
                                         svsub_f32_x (pg, u,
                                                      jbm_nxf32_erfcwc (pg,
                                                                        ax)))));
}

/**
 * Function to calculate the solution of a svfloat32_t vector of reduced
 * quadratic equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return svfloat32_t vector of solution values.
 */
static inline svfloat32_t
jbm_nxf32_solve_quadratic_reduced (svbool_t pg, ///< predicate.
                                   svfloat32_t a,
///< svfloat32_t vector of 1st order coefficient of the equations.
                                   svfloat32_t b,
///< svfloat32_t vector of 0-th order coefficient of the equations.
                                   const svfloat32_t x1,
///< svfloat32_t vector of left limits of the solution intervals.
                                   const svfloat32_t x2)
///< svfloat32_t vector of right limits of the solution intervals.
{
  svfloat32_t k1, k2;
  a = svmul_n_f32_x (pg, a, -0.5f);
  b = svsqrt_f32_x (pg, svsub_f32_x (pg, jbm_nxf32_sqr (pg, a), b));
  k1 = svadd_f32_x (pg, a, b);
  k2 = svsub_f32_x (pg, a, b);
  k1 = svsel_f32 (svcmplt_f32 (pg, k1, x1), k2, k1);
  return svsel_f32 (svcmpgt_f32 (pg, k1, x2), k2, k1);
}

/**
 * Function to calculate the solution of a svfloat32_t vector of quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^2+b\,x+c=0\f$.
 *
 * \return svfloat32_t vector of solution values.
 */
static inline svfloat32_t
jbm_nxf32_solve_quadratic (svbool_t pg, ///< predicate.
                           svfloat32_t a,
///< svfloat32_t vector of 2nd order coefficient of the equations.
                           svfloat32_t b,
///< svfloat32_t vector of 1st order coefficient of the equations.
                           svfloat32_t c,
///< svfloat32_t vector of 0-th order coefficient of the equations.
                           const svfloat32_t x1,
///< svfloat32_t vector of left limits of the solution intervals.
                           const svfloat32_t x2)
///< svfloat32_t vector of right limits of the solution intervals.
{
  return
    svsel_f32 (jbm_nxf32_small (pg, a),
               jbm_nxf32_solve_quadratic_reduced (pg, svdiv_f32_x (pg, b, a),
                                                  svdiv_f32_x (pg, c, a),
                                                  x1, x2);
               svdiv_f32_x (pg, jbm_nxf32_opposite (pg, c), b));
}

/**
 * Function to calculate the solution of a svfloat32_t vector of reduced cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^3+a\,x^2+b\,x+c=0\f$.
 *
 * \return svfloat32_t vector of solution values.
 */
static inline svfloat32_t
jbm_nxf32_solve_cubic_reduced (svbool_t pg,     ///< predicate.
                               svfloat32_t a,
///< svfloat32_t vector of 2nd order coefficient of the equations.
                               svfloat32_t b,
///< svfloat32_t vector of 1st order coefficient of the equations.
                               svfloat32_t c,
///< svfloat32_t vector of 0-th order coefficient of the equations.
                               const svfloat32_t x1,
///< svfloat32_t vector of left limits of the solution intervals.
                               const svfloat32_t x2)
///< svfloat32_t vector of right limits of the solution intervals.
{
  svfloat32_t a3, k0, k1, k2, l0, l1, l2, l3, l4, l5;
  a3 = svmul_n_f32_x (pg, a, 1.f / 3.f);
  k0 = jbm_nxf32_sqr (pg, a3);
  k1 = svsub_f32_x (pg, svmul_n_f32_x (pg, b, 1.f / 3.f), k0);
  k0 = svsub_f32_x (pg,
                    svmul_n_f32_x (pg,
                                   svsub_f32_x (pg, svmul_f32_x (pg, b, a3), c),
                                   0.5f), svmul_f32_x (pg, a3, k0));
  k2 = svmla_f32_x (pg, svmul_f32_x (pg, k1, jbm_nxf32_sqr (pg, k1)), k0, k0);
  l1 = svsqrt_f32_x (pg, jbm_nxf32_opposite (pg, k1));
  l0 = svmul_n_f32_x
    (pg,
     jbm_nxf32_acos (pg,
                     svdiv_f32_x (pg, k0,
                                  svmul_f32_x (pg, l1,
                                               jbm_nxf32_sqr (pg, l1)))),
     1.f / 3.f);
  l1 = jbm_nxf32_dbl (pg, l1);
  l2 = svsub_f32_x (pg, svmul_f32_x (pg, l1, jbm_nxf32_cos (pg, l0)), a3);
  l3 =
    svsub_f32_x
    (pg,
     svmul_f32_x (pg, l1,
                  jbm_nxf32_cos (pg, svadd_n_f32_x (pg, l0,
                                                    2.f * M_PIf / 3.f))), a3);
  l3 = svsel_f32 (svorr_b_z (pg, svcmplt_f32 (pg, l2, x1),
                             svcmpgt_f32 (pg, l2, x2)), l2, l3);
  l4 =
    svsub_f32_x
    (pg,
     svmul_f32_x (pg, l1,
                  jbm_nxf32_cos (pg, svsub_n_f32_x (pg, l0,
                                                    2.f * M_PIf / 3.f))), a3);
  l4 = svsel_f32 (svorr_b_z (pg, svcmplt_f32 (pg, l3, x1),
                             svcmpgt_f32 (pg, l3, x2)), l3, l4);
  k1 = svsqrt_f32_x (pg, k2);
  l5 = jbm_nxf32_cbrt (pg, svadd_f32_x (pg, k0, k1));
  l5 = svadd_f32_x (pg, l5,
                    svsub_f32_x (pg,
                                 jbm_nxf32_cbrt (pg, svsub_f32_x (pg, k0, k1)),
                                 a3));
  return svsel_f32 (svcmplt_n_f32 (pg, k2, 0.f), l4, l5);
}

/**
 * Function to calculate the solution of a svfloat32_t vector of cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return svfloat32_t vector of solution values.
 */
static inline svfloat32_t
jbm_nxf32_solve_cubic (svbool_t pg,     ///< predicate.
                       svfloat32_t a,
///< svfloat32_t vector of 3rd order coefficient of the equations.
                       svfloat32_t b,
///< svfloat32_t vector of 2nd order coefficient of the equations.
                       svfloat32_t c,
///< svfloat32_t vector of 1st order coefficient of the equations.
                       svfloat32_t d,
///< svfloat32_t vector of 0-th order coefficient of the equations.
                       const svfloat32_t x1,
///< svfloat32_t vector of left limits of the solution intervals.
                       const svfloat32_t x2)
///< svfloat32_t vector of right limits of the solution intervals.
{
  return
    svsel_f32
    (jbm_nxf32_small (pg, a),
     jbm_nxf32_solve_cubic_reduced (pg, svdiv_f32_x (pg, b, a),
                                    svdiv_f32_x (pg, c, a),
                                    svdiv_f32_x (pg, d, a), x1, x2),
     jbm_nxf32_solve_quadratic (pg, b, c, d, x1, x2));
}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (svfloat32_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat32_t
jbm_nxf32_flux_limiter_total (svbool_t pg,      ///< predicate.
                              const svfloat32_t d1 __attribute__((unused)),
                              ///< 1st flux limiter function parameter.
                              const svfloat32_t d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return svdup_n_f32 (0.f);
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (svfloat32_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat32_t
jbm_nxf32_flux_limiter_null (svbool_t pg,       ///< predicate.
                             const svfloat32_t d1 __attribute__((unused)),
                             ///< 1st flux limiter function parameter.
                             const svfloat32_t d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return svdup_n_f32 (1.f);
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (svfloat32_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat32_t
jbm_nxf32_flux_limiter_centred (svbool_t pg,    ///< predicate.
                                const svfloat32_t d1,
                                ///< 1st flux limiter function parameter.
                                const svfloat32_t d2)
                                ///< 2nd flux limiter function parameter.
{
  return svsel_f32 (jbm_nxf32_small (pg, d2),
                    svdup_n_f32 (0.f), svdiv_f32_x (pg, d1, d2));
}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (svfloat32_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat32_t
jbm_nxf32_flux_limiter_superbee (svbool_t pg,   ///< predicate.
                                 const svfloat32_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const svfloat32_t d2)
                                 ///< 2nd flux limiter function parameter.
{
  svfloat32_t r;
  r = svdiv_f32_x (pg, d1, d2);
  r = svmax_f32_x (pg, svmin_n_f32_x (pg, jbm_nxf32_dbl (pg, r), 1.f),
                   svmin_n_f32_x (pg, r, 2.f));
  return svsel_f32 (svcmpgt_n_f32 (pg, svmul_f32_x (pg, d1, d2), FLT_EPSILON),
                    svdup_n_f32 (0.f), r);
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (svfloat32_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat32_t
jbm_nxf32_flux_limiter_minmod (svbool_t pg,     ///< predicate.
                               const svfloat32_t d1,
                               ///< 1st flux limiter function parameter.
                               const svfloat32_t d2)
                               ///< 2nd flux limiter function parameter.
{
  svfloat32_t r;
  r = svmin_n_f32_x (pg, svdiv_f32_x (pg, d1, d2), 1.f);
  return svsel_f32 (svcmpgt_n_f32 (pg, svmul_f32_x (pg, d1, d2), FLT_EPSILON),
                    svdup_n_f32 (0.f), r);
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (svfloat32_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat32_t
jbm_nxf32_flux_limiter_VanLeer (svbool_t pg,    ///< predicate.
                                const svfloat32_t d1,
                                ///< 1st flux limiter function parameter.
                                const svfloat32_t d2)
                                ///< 2nd flux limiter function parameter.
{
  svfloat32_t r, k;
  r = svdiv_f32_x (pg, d1, d2);
  k = jbm_nxf32_abs (pg, r);
  r = svdiv_f32_x (pg, svadd_f32_x (pg, r, k), svadd_n_f32_x (pg, k, 1.f));
  return svsel_f32 (svcmpgt_n_f32 (pg, svmul_f32_x (pg, d1, d2), FLT_EPSILON),
                    svdup_n_f32 (0.f), r);
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (svfloat32_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat32_t
jbm_nxf32_flux_limiter_VanAlbada (svbool_t pg,  ///< predicate.
                                  const svfloat32_t d1,
                                  ///< 1st flux limiter function parameter.
                                  const svfloat32_t d2)
                                  ///< 2nd flux limiter function parameter.
{
  svfloat32_t r, k;
  r = svdiv_f32_x (pg, d1, d2);
  k = jbm_nxf32_sqr (pg, r);
  r = svdiv_f32_x (pg, svadd_f32_x (pg, r, k), svadd_n_f32_x (pg, k, 1.f));
  return svsel_f32 (svcmpgt_n_f32 (pg, svmul_f32_x (pg, d1, d2), FLT_EPSILON),
                    svdup_n_f32 (0.f), r);
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (svfloat32_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat32_t
jbm_nxf32_flux_limiter_minsuper (svbool_t pg,   ///< predicate.
                                 const svfloat32_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const svfloat32_t d2)
                                 ///< 2nd flux limiter function parameter.
{
  svfloat32_t r;
  r = svmin_f32_x (pg, svdiv_f32_x (pg, d1, d2), svdup_n_f32 (2.f));
  return svsel_f32 (svcmpgt_n_f32 (pg, svmul_f32_x (pg, d1, d2), FLT_EPSILON),
                    svdup_n_f32 (0.f), r);
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (svfloat32_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat32_t
jbm_nxf32_flux_limiter_supermin (svbool_t pg,   ///< predicate.
                                 const svfloat32_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const svfloat32_t d2)
                                 ///< 2nd flux limiter function parameter.
{
  svfloat32_t r;
  r = svdiv_f32_x (pg, d1, d2);
  r = svmin_n_f32_x (pg, jbm_nxf32_dbl (pg, r), 1.f);
  return svsel_f32 (svcmpgt_n_f32 (pg, svmul_f32_x (pg, d1, d2), FLT_EPSILON),
                    svdup_n_f32 (0.f), r);
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (svfloat32_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat32_t
jbm_nxf32_flux_limiter_monotonized_central (svbool_t pg,
///< predicate.
                                            const svfloat32_t d1,
///< 1st flux limiter function parameter.
                                            const svfloat32_t d2)
///< 2nd flux limiter function parameter.
{
  svfloat32_t r, rm;
  r = svdiv_f32_x (pg, d1, d2);
  rm = svmul_n_f32_x (pg, svadd_n_f32_x (pg, r, 1.f), 0.5f);
  rm = svsel_f32 (svcmplt_n_f32 (pg, r, 3.f), svdup_n_f32 (2.f), rm);
  rm = svsel_f32 (svcmpgt_n_f32 (pg, r, 1.f / 3.f), jbm_nxf32_dbl (pg, r), rm);
  return svsel_f32 (svcmpgt_n_f32 (pg, svmul_f32_x (pg, d1, d2), FLT_EPSILON),
                    svdup_n_f32 (0.f), rm);
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (svfloat32_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat32_t
jbm_nxf32_flux_limiter_mean (svbool_t pg,       ///< predicate.
                             const svfloat32_t d1,
                             ///< 1st flux limiter function parameter.
                             const svfloat32_t d2)
                             ///< 2nd flux limiter function parameter.
{
  svfloat32_t r;
  r = svmul_n_f32_x (pg,
                     svadd_n_f32_x (pg, svdiv_f32_x (pg, d1, d2), 1.f), 0.5f);
  return svsel_f32 (svcmpgt_n_f32 (pg, svmul_f32_x (pg, d1, d2), FLT_EPSILON),
                    svdup_n_f32 (0.f), r);
}

/**
 * Function to do a flux limiter function (svfloat32_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat32_t
jbm_nxf32_flux_limiter (svbool_t pg,    ///< predicate.
                        const svfloat32_t d1,
                        ///< 1st flux limiter function parameter.
                        const svfloat32_t d2,
                        ///< 2nd flux limiter function parameter.
                        unsigned int type)
                        ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_nxf32_flux_limiter_total (pg, d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_nxf32_flux_limiter_null (pg, d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_nxf32_flux_limiter_centred (pg, d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_nxf32_flux_limiter_superbee (pg, d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_nxf32_flux_limiter_minmod (pg, d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_nxf32_flux_limiter_VanLeer (pg, d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_nxf32_flux_limiter_VanAlbada (pg, d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_nxf32_flux_limiter_minsuper (pg, d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_nxf32_flux_limiter_supermin (pg, d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_nxf32_flux_limiter_monotonized_central (pg, d1, d2);
    }
  return jbm_nxf32_flux_limiter_mean (pg, d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (svfloat32_t).
 *
 * \return svfloat32_t vector of integral values.
 */
static inline svfloat32_t
jbm_nxf32_integral (svfloat32_t (*f) (svbool_t, const svfloat32_t),
                    ///< pointer to the function to integrate.
                    svbool_t pg,        ///< predicate.
                    const svfloat32_t x1,       ///< left limit of the interval.
                    const svfloat32_t x2)
                    ///< right limit of the interval.
{
  svfloat32_t k, x, dx;
#if JBM_INTEGRAL_GAUSS_N > 1
  svfloat32_t k2, f1, f2;
#endif
  unsigned int i;
  dx = svmul_n_f32_x (pg, svsub_f32_x (pg, x2, x1), 0.5f);
  x = svmul_n_f32_x (pg, svadd_f32_x (pg, x2, x1), 0.5f);
  k = svmul_n_f32_x (pg, f (pg, x), JBM_INTEGRAL_GAUSS_A_F32[0]);
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = svmul_n_f32_x (pg, dx, JBM_INTEGRAL_GAUSS_B_F32[i]);
      f1 = f (pg, svsub_f32_x (pg, x, k2));
      f2 = f (pg, svadd_f32_x (pg, x, k2));
      k = svmla_n_f32_x (pg, k, svadd_f32_x (pg, f1, f2),
                         JBM_INTEGRAL_GAUSS_A_F32[i]);
    }
#endif
  return svmul_f32_x (pg, k, dx);
}

/**
 * Function to calculate the additive inverse value of a svfloat64_t vector.
 */
static inline svfloat64_t
jbm_nxf64_opposite (svbool_t pg,        ///< predicate.
                    const svfloat64_t x)        ///< svfloat64_t vector.
{
  return svneg_f64_x (pg, x);
}

/**
 * Function to calculate the multiplicative inverse value of a svfloat64_t
 * vector.
 */
static inline svfloat64_t
jbm_nxf64_reciprocal (svbool_t pg,      ///< predicate.
                      const svfloat64_t x)      ///< svfloat64_t vector.
{
  return svdiv_f64_x (pg, svdup_n_f64 (1.), x);
}

/**
 * Function to calculate the absolute value of a svfloat64_t vector.
 */
static inline svfloat64_t
jbm_nxf64_abs (svbool_t pg,     ///< predicate.
               const svfloat64_t x)     ///< svfloat64_t vector.
{
  return svabs_f64_x (pg, x);
}

/**
 * Function to copy the sign of a svfloat64_t vector to another svfloat64_t
 * vector.
 */
static inline svfloat64_t
jbm_nxf64_copysign (const svfloat64_t x,
                    ///< vector to preserve magnitude.
                    const svfloat64_t y)        ///< vector to preserve sign.
{
  return
    svreinterpret_f64_u64 (svbsl_u64 (svreinterpret_u64_f64 (y),
                                      svreinterpret_u64_f64 (x),
                                      svdup_n_u64 (JBM_F64_BITS_SIGN)));
}

/**
 * Function to calculate the hypot function (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_hypot (svbool_t pg,   ///< predicate.
                 const svfloat64_t x,   ///< 1st svfloat64_t vector.
                 const svfloat64_t y)   ///< 2nd svfloat64_t vector.
{
  svfloat64_t t = svmul_f64_x (pg, x, x);
  t = svmla_f64_x (pg, t, y, y);
  return svsqrt_f64_x (pg, t);
}

/**
 * Function to rounding to nearest (svfloat64_t).
 */
static inline svint64_t
jbm_nxf64_round (svbool_t pg,   ///< predicate.
                 const svfloat64_t x)   ///< svfloat64_t vector.
{
  return svcvt_s64_f64_x (pg, svrintn_f64_x (pg, x));
}

/**
 * Function to rounding towards zero (svfloat64_t).
 */
static inline svint64_t
jbm_nxf64_trunc (svbool_t pg,   ///< predicate.
                 const svfloat64_t x)   ///< svfloat64_t vector.
{
  return svcvt_s64_f64_x (pg, svrintz_f64_x (pg, x));
}

/**
 * Function to rounding down (svfloat64_t).
 */
static inline svint64_t
jbm_nxf64_floor (svbool_t pg,   ///< predicate.
                 const svfloat64_t x)   ///< svfloat64_t vector.
{
  return svcvt_s64_f64_x (pg, svrintm_f64_x (pg, x));
}

/**
 * Function to rounding top (svfloat64_t).
 */
static inline svint64_t
jbm_nxf64_ceil (svbool_t pg,    ///< predicate.
                const svfloat64_t x)    ///< svfloat64_t vector.
{
  return svcvt_s64_f64_x (pg, svrintp_f64_x (pg, x));
}

/**
 * Function to calculate the rest of a division (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_mod (svbool_t pg,     ///< predicate.
               const svfloat64_t x,     ///< dividend (svfloat64_t).
               const svfloat64_t d)     ///< divisor (svfloat64_t).
{
  svfloat64_t q = svdiv_f64_x (pg, x, d);
  q = svcvt_f64_s64_x (pg, jbm_nxf64_floor (pg, q));
  return svmls_f64_x (pg, x, q, d);
}

/**
 * Function to calculate the rest of a division by a double (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_mod1 (svbool_t pg,    ///< predicate.
                const svfloat64_t x,    ///< dividend (svfloat64_t).
                const double d) ///< divisor (double).
{
  svfloat64_t vd = svdup_n_f64 (d);
  svfloat64_t q = svdiv_f64_x (pg, x, vd);
  q = svcvt_f64_s64_x (pg, jbm_nxf64_floor (pg, q));
  return svmls_f64_x (pg, x, q, vd);
}

/**
 * Function to implement the standard frexp function (svfloat64_t).
 *
 * \return normalized fraction value in [1/2,1) (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_frexp (svbool_t pg,   ///< predicate.
                 const svfloat64_t x,   ///< svfloat64_t vector.
                 svint64_t *e)  ///< pointer to the exponents vector.
{
  const svuint64_t ai = svreinterpret_u64_f64 (x);
  const svuint64_t ai_abs = svand_n_u64_x (pg, ai, JBM_F64_BITS_ABS);
  const svbool_t m_special
    = svcmpge_n_u64 (pg, svsub_n_u64_x (pg, ai_abs, 1ull),
                     JBM_F64_BITS_EXPONENT - 1ull);
  const svuint64_t yi = svlsr_n_u64_x (pg, ai_abs, 52ull);
  const svbool_t m_sub = svcmpeq_n_u64 (pg, yi, 0ull);
  // Scale subnormals
  const svuint64_t zi_abs
    = svreinterpret_u64_f64 (svmul_n_f64_x (pg, svreinterpret_f64_u64 (ai_abs),
                                            0x1p52));
  // Exponent
  *e = svdup_n_s64_m
    (svsel_s64 (m_sub,
                svsub_n_s64_x (m_sub,
                               svreinterpret_s64_u64 (svlsr_n_u64_x (m_sub,
                                                                     zi_abs,
                                                                     52ull)),
                               JBM_F64_BIAS + 52ull),
                svsub_n_s32_x (pg, svreinterpret_s32_u32 (yi), JBM_F32_BIAS)),
     m_special, 0);
  *e = svdup_n_s64_m (en, m_special, 0ll);
  // Mantissa
  return
    svsel_f64
    (m_special, x,
     svreinterpret_f64_u64
     (svbsl_u64 (ai, svbsl_u64 (svsel_u64 (m_sub, zi_abs, ai_abs),
                                svdup_n_u64 ((uint64_t) JBM_F64_BIAS << 52ull),
                                svdup_n_u64 (JBM_F64_BITS_MANTISSA)),
                 svdup_n_u64 (JBM_F64_BITS_SIGN))));
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (svint64_t).
 *
 * \return function value vector (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_exp2n (svbool_t pg,   ///< predicate.
                 svint64_t e)   ///< exponent vector (svint64_t).
{
  svuint64_t r;
  r = svsel_u64 (svcmplt_n_s64 (pg, e, -1022ll),
                 svlsl_u64_x (pg, svdup_n_u64 (1ull),
                              svreinterpret_u64_s64 (svadd_n_s64_x (pg, e,
                                                                    1074ll))),
                 svlsl_n_u64_x (pg,
                                svreinterpret_u64_s64 (svadd_n_s64_x (pg, e,
                                                                      1023ll)),
                                52ull));
  r = svsel_u64 (svcmpgt_n_s64 (pg, e, 1023ll),
                 svdup_n_u64 (JBM_F64_BITS_EXPONENT), r);
  return svreinterpret_f64_u64 (r);
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (svint64_t).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_exp2n (svbool_t pg,   ///< predicate.
                 const svint64_t e)     ///< exponent vector (svint64_t).
{
  return svscale_f64_x (pg, svdup_n_f64 (1.), e);
}

/**
 * Function to implement the standard ldexp function (svfloat64_t).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_ldexp (svbool_t pg,   ///< predicate.
                 const svfloat64_t x,   ///< svfloat64_t vector.
                 svint64_t e)   ///< exponent vector (svint64_t).
{
  return svscale_f64_x (pg, x, e);
}

/**
 * Function to check small svfloat64_t vectors.
 *
 * \return predicate true on small numbers.
 */
static inline svbool_t
jbm_nxf64_small (svbool_t pg,   ///< predicate.
                 const svfloat64_t x)   ///< svfloat64_t vector.
{
  return svcmplt_n_f64 (pg, svabs_f64_x (pg, x), DBL_EPSILON);
}

/**
 * Function to calculate the svfloat64_t vector with the components with lower
 * module in the [a, b] interval.
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin svfloat64_t vector.
 */
static inline svfloat64_t
jbm_nxf64_modmin (svbool_t pg,  ///< predicate.
                  const svfloat64_t a,  ///< 1st svfloat64_t vector.
                  const svfloat64_t b)  ///< 2nd svfloat64_t vector.
{
  const svbool_t z = svcmple_n_f64 (pg, svmul_f64_x (pg, a, b), 0.);
  const svbool_t m = svbic_b_z (pg,
                                svcmplt_f64 (pg, svabs_f64_x (pg, a),
                                             svabs_f64_x (pg, b)),
                                z);
  return svsel_f64 (z, svdup_n_f64 (0.), svsel_f64 (m, a, b));
}

/**
 * Function to interchange 2 svfloat64_t vectors.
 */
static inline void
jbm_nxf64_change (svfloat64_t *restrict a,      ///< 1st vector pointer.
                  svfloat64_t *restrict b)      ///< 2nd vector pointer.
{
  svfloat64_t c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the double of a svfloat64_t vector.
 *
 * \return svfloat64_t double.
 */
static inline svfloat64_t
jbm_nxf64_dbl (svbool_t pg,     ///< predicate.
               const svfloat64_t x)     ///< svfloat64_t vector.
{
  return svadd_f64_x (pg, x, x);
}

/**
 * Function to calculate the square of the components of a svfloat64_t vector.
 *
 * \return svfloat64_t vector square.
 */
static inline svfloat64_t
jbm_nxf64_sqr (svbool_t pg,     ///< predicate.
               const svfloat64_t x)     ///< svfloat64_t vector.
{
  return svmul_f64_x (pg, x, x);
}

/**
 * Function to perform an extrapolation between 2 svfloat64_t vectors of 2D
 * points.
 *
 * \return svfloat64_t vector of y-coordinates of the extrapolated points.
 */
static inline svfloat64_t
jbm_nxf64_extrapolate (svbool_t pg,     ///< predicate.
                       const svfloat64_t x,     ///< x-coord. of points.
                       const svfloat64_t x1,    ///< x-coord. of 1st points.
                       const svfloat64_t x2,    ///< x-coord. of 2nd points.
                       const svfloat64_t y1,    ///< y-coord. of 1st points.
                       const svfloat64_t y2)    ///< y-coord. of 2nd points.
{
  return
    svmla_f64_x (pg, y1, svsub_f64_x (pg, x, x1),
                 svdiv_f64_x (pg, svsub_f64_x (pg, y2, y1),
                              svsub_f64_x (pg, x2, x1)));
}

/**
 * Function to perform an interpolation between 2 svfloat64_t vectors of 2D
 * points.
 *
 * \return svfloat64_t vector of y-coordinates of the interpolated points.
 */
static inline svfloat64_t
jbm_nxf64_interpolate (svbool_t pg,     ///< predicate.
                       const svfloat64_t x,     ///< x-coord. of points.
                       const svfloat64_t x1,    ///< x-coord. of 1st points.
                       const svfloat64_t x2,    ///< x-coord. of 2nd points.
                       const svfloat64_t y1,    ///< y-coord. of 1st points.
                       const svfloat64_t y2)    ///< y-coord. of 2nd points.
{
  svfloat64_t k = jbm_nxf64_extrapolate (pg, x, x1, x2, y1, y2);
  k = svsel_f64 (svcmpgt_f64 (pg, x, x1), y1, k);
  return svsel_f64 (svcmplt_f64 (pg, x, x2), y2, k);
}

/**
 * Function to calculate the length of a svfloat64_t vector of 2D segments.
 *
 * \return svfloat64_t vector of segment lengths.
 */
static inline svfloat64_t
jbm_nxf64_v2_length (svbool_t pg,       ///< predicate.
                     const svfloat64_t x1,      ///< x-coord. of 1st points.
                     const svfloat64_t y1,      ///< y-coord. of 1st points.
                     const svfloat64_t x2,      ///< x-coord. of 2nd points.
                     const svfloat64_t y2)      ///< y-coord. of 2nd points.
{
  return jbm_nxf64_hypot (pg, svsub_f64_x (pg, x2, x1),
                          svsub_f64_x (pg, y2, y1));
}

/**
 * Function to calculate the length of a svfloat64_t vector of 3D segments.
 *
 * \return svfloat64_t vector of segment lengths.
 */
static inline svfloat64_t
jbm_nxf64_v3_length (svbool_t pg,       ///< predicate.
                     const svfloat64_t x1,      ///< x-coord. of 1st points.
                     const svfloat64_t y1,      ///< y-coord. of 1st points.
                     const svfloat64_t z1,      ///< z-coord. of 1st points.
                     const svfloat64_t x2,      ///< x-coord. of 2nd points.
                     const svfloat64_t y2,      ///< y-coord. of 2nd points.
                     const svfloat64_t z2)      ///< z-coord. of 2nd points.
{
  const svfloat64_t dx2 = jbm_nxf64_sqr (pg, svsub_f64_x (pg, x2, x1));
  const svfloat64_t dy = svsub_f64_x (pg, y2, y1);
  const svfloat64_t dz = svsub_f64_x (pg, z2, z1);
  return svsqrt_f64_x (pg,
                       svmla_f64_x (pg, svmla_f64_x (pg, dx2, dy, dy), dz, dz));
}

/**
 * Function to calculate a 1st order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_1 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return svmla_n_f64_x (pg, svdup_n_f64 (p[0]), x, p[1]);
}

/**
 * Function to calculate a 2nd order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_2 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_1 (pg, x, p + 1));
}

/**
 * Function to calculate a 3rd order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_3 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_2 (pg, x, p + 1));
}

/**
 * Function to calculate a 4th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_4 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_3 (pg, x, p + 1));
}

/**
 * Function to calculate a 5th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_5 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_4 (pg, x, p + 1));
}

/**
 * Function to calculate a 6th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_6 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_5 (pg, x, p + 1));
}

/**
 * Function to calculate a 7th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_7 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_6 (pg, x, p + 1));
}

/**
 * Function to calculate a 8th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_8 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_7 (pg, x, p + 1));
}

/**
 * Function to calculate a 9th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_9 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_8 (pg, x, p + 1));
}

/**
 * Function to calculate a 10th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_10 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_9 (pg, x, p + 1));
}

/**
 * Function to calculate a 11th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_11 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_10 (pg, x, p + 1));
}

/**
 * Function to calculate a 12th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_12 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_11 (pg, x, p + 1));
}

/**
 * Function to calculate a 13th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_13 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_12 (pg, x, p + 1));
}

/**
 * Function to calculate a 14th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_14 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_13 (pg, x, p + 1));
}

/**
 * Function to calculate a 15th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_15 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_14 (pg, x, p + 1));
}

/**
 * Function to calculate a 16th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_16 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_15 (pg, x, p + 1));
}

/**
 * Function to calculate a 17th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_17 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_16 (pg, x, p + 1));
}

/**
 * Function to calculate a 18th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_18 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_17 (pg, x, p + 1));
}

/**
 * Function to calculate a 19th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_19 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_18 (pg, x, p + 1));
}

/**
 * Function to calculate a 20th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_20 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_19 (pg, x, p + 1));
}

/**
 * Function to calculate a 21th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_21 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_20 (pg, x, p + 1));
}

/**
 * Function to calculate a 22th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_22 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_21 (pg, x, p + 1));
}

/**
 * Function to calculate a 23th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_23 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_22 (pg, x, p + 1));
}

/**
 * Function to calculate a 24th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_24 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_23 (pg, x, p + 1));
}

/**
 * Function to calculate a 25th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_25 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_24 (pg, x, p + 1));
}

/**
 * Function to calculate a 26th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_26 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_25 (pg, x, p + 1));
}

/**
 * Function to calculate a 27th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_27 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_26 (pg, x, p + 1));
}

/**
 * Function to calculate a 28th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_28 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_27 (pg, x, p + 1));
}

/**
 * Function to calculate a 29th order polynomial (svfloat64_t).
 *
 * \return svfloat64_t vector of polynomial values.
 */
static inline svfloat64_t
jbm_nxf64_polynomial_29 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return svmla_f64_x (pg, svdup_n_f64 (p[0]), x,
                      jbm_nxf64_polynomial_28 (pg, x, p + 1));
}

/**
 * Function to calculate a 0th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_1_0 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[1]));
}

/**
 * Function to calculate a 0th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_2_0 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_2_1 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[2]));
}

/**
 * Function to calculate a 0th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_3_0 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_3_1 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_3_2 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[3]));
}

/**
 * Function to calculate a 0th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_4_0 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_4_1 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_4_2 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_4_3 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[4]));
}

/**
 * Function to calculate a 0th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_5_0 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_5_1 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_5_2 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_5_3 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_5_4 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[5]));
}

/**
 * Function to calculate a 0th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_6_0 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_6_1 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_6_2 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_6_3 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_6_4 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_6_5 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[6]));
}

/**
 * Function to calculate a 0th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_7_0 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_7_1 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_7_2 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_7_3 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_7_4 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_7_5 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_7_6 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[7]));
}

/**
 * Function to calculate a 0th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_8_0 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_8_1 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_8_2 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_8_3 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_8_4 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_8_5 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_8_6 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_8_7 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[8]));
}

/**
 * Function to calculate a 0th+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_9_0 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_9_1 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_9_2 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_9_3 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_9_4 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_9_5 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_9_6 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_9_7 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_9_8 (svbool_t pg,    ///< predicate.
                        const svfloat64_t x,    ///< svfloat64_t vector.
                        const double *p)        ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[9]));
}

/**
 * Function to calculate a 0th+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_10_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_10_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_10_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_10_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_10_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_10_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_10_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_10_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_10_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_10_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[10]));
}

/**
 * Function to calculate a 0th+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_11_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_11_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_11_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_11_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_11_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_11_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_11_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_11_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_11_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_11_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_11_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[11]));
}

/**
 * Function to calculate a 0th+12th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_12_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_11 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_12_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_12_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_12_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_12_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_12_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_12_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_12_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_12_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_12_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_12_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_12_11 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_11 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[12]));
}

/**
 * Function to calculate a 0th+13th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_13_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_12 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+12th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_13_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_11 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_13_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_13_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_13_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_13_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_13_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_13_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_13_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_13_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_13_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_13_11 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_11 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_13_12 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_12 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[13]));
}

/**
 * Function to calculate a 0th+14th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_14_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_13 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+13th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_14_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_12 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+12th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_14_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_11 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_14_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_14_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_14_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_14_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_14_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_14_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_14_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_14_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_14_11 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_11 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_14_12 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_12 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_14_13 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_13 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[14]));
}

/**
 * Function to calculate a 0th+15th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_15_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_14 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+14th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_15_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_13 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+13th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_15_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_12 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+12th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_15_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_11 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_15_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_15_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_15_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_15_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_15_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_15_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_15_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_15_11 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_11 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_15_12 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_12 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_15_13 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_13 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_15_14 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_14 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[15]));
}

/**
 * Function to calculate a 0th+16th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_16_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_15 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+15th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_16_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_14 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+14th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_16_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_13 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+13th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_16_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_12 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+12th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_16_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_11 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_16_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_16_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_16_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_16_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_16_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_16_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_16_11 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_11 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_16_12 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_12 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_16_13 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_13 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_16_14 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_14 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_16_15 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_15 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[16]));
}

/**
 * Function to calculate a 0th+17th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_17_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_16 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+16th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_17_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_15 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+15th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_17_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_14 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+14th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_17_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_13 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+13th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_17_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_12 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+12th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_17_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_11 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_17_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_17_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_17_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_17_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_17_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_17_11 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_11 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_17_12 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_12 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_17_13 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_13 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_17_14 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_14 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_17_15 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_15 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_17_16 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_16 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[17]));
}

/**
 * Function to calculate a 0th+18th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_18_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_17 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+17th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_18_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_16 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+16th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_18_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_15 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+15th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_18_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_14 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+14th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_18_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_13 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+13th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_18_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_12 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+12th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_18_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_11 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_18_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_18_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_18_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_18_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_18_11 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_11 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_18_12 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_12 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_18_13 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_13 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_18_14 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_14 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_18_15 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_15 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_18_16 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_16 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_18_17 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_17 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[18]));
}

/**
 * Function to calculate a 0th+19th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_18 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+18th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_17 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+17th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_16 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+16th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_15 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+15th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_14 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+14th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_13 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+13th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_12 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+12th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_11 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_11 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_11 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_12 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_12 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_13 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_13 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_14 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_14 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_15 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_15 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_16 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_16 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_17 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_17 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_19_18 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_18 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[19]));
}

/**
 * Function to calculate a 0th+20th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_19 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+19th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_18 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+18th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_17 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+17th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_16 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+16th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_15 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+15th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_14 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+14th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_13 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+13th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_12 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+12th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_11 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_11 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_11 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_12 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_12 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_13 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_13 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_14 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_14 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_15 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_15 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_16 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_16 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_17 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_17 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_18 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_18 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_20_19 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_19 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[20]));
}

/**
 * Function to calculate a 0th+21th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_20 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+20th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_19 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+19th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_18 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+18th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_17 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+17th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_16 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+16th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_15 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+15th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_14 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+14th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_13 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+13th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_12 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+12th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_11 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_11 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_11 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_12 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_12 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_13 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_13 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_14 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_14 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_15 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_15 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_16 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_16 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_17 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_17 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_18 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_18 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_19 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_19 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 20)));
}

/**
 * Function to calculate a 20th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_21_20 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_20 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[21]));
}

/**
 * Function to calculate a 0th+22th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_21 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+21th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_20 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+20th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_19 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+19th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_18 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+18th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_17 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+17th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_16 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+16th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_15 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+15th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_14 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+14th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_13 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+13th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_12 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+12th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_11 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_11 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_11 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_12 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_12 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_13 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_13 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_14 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_14 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_15 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_15 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_16 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_16 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_17 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_17 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_18 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_18 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_19 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_19 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 20)));
}

/**
 * Function to calculate a 20th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_20 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_20 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 21)));
}

/**
 * Function to calculate a 21th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_22_21 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_21 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[22]));
}

/**
 * Function to calculate a 0th+23th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_22 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+22th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_21 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+21th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_20 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+20th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_19 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+19th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_18 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+18th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_17 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+17th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_16 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+16th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_15 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+15th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_14 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+14th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_13 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+13th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_12 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+12th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_11 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_11 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_11 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_12 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_12 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_13 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_13 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_14 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_14 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_15 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_15 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_16 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_16 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_17 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_17 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_18 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_18 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_19 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_19 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 20)));
}

/**
 * Function to calculate a 20th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_20 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_20 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 21)));
}

/**
 * Function to calculate a 21th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_21 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_21 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 22)));
}

/**
 * Function to calculate a 22th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_23_22 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_22 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[23]));
}

/**
 * Function to calculate a 0th+24th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_23 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+23th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_22 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+22th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_21 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+21th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_20 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+20th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_19 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+19th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_18 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+18th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_17 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+17th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_16 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+16th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_15 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+15th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_14 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+14th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_13 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+13th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_11 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_11 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_12 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+12th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_12 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_12 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_11 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_13 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_13 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_14 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_14 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_15 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_15 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_16 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_16 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_17 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_17 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_18 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_18 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_19 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_19 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 20)));
}

/**
 * Function to calculate a 20th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_20 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_20 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 21)));
}

/**
 * Function to calculate a 21th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_21 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_21 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 22)));
}

/**
 * Function to calculate a 22th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_22 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_22 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 23)));
}

/**
 * Function to calculate a 23th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_24_23 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_23 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[24]));
}

/**
 * Function to calculate a 0th+25th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_24 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+24th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_23 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+23th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_22 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+22th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_21 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+21th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_20 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+20th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_19 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+19th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_18 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+18th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_17 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+17th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_16 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+16th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_15 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+15th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_14 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+14th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_11 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_11 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_13 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+13th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_12 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_12 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_12 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+12th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_13 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_13 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_11 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_14 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_14 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_15 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_15 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_16 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_16 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_17 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_17 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_18 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_18 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_19 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_19 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 20)));
}

/**
 * Function to calculate a 20th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_20 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_20 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 21)));
}

/**
 * Function to calculate a 21th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_21 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_21 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 22)));
}

/**
 * Function to calculate a 22th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_22 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_22 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 23)));
}

/**
 * Function to calculate a 23th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_23 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_23 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 24)));
}

/**
 * Function to calculate a 24th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_25_24 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_24 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[25]));
}

/**
 * Function to calculate a 0th+26th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_25 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+25th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_24 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+24th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_23 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+23th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_22 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+22th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_21 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+21th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_20 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+20th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_19 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+19th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_18 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+18th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_17 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+17th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_16 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+16th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_15 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+15th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_11 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_11 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_14 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+14th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_12 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_12 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_13 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+13th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_13 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_13 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_12 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+12th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_14 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_14 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_11 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_15 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_15 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_16 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_16 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_17 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_17 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_18 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_18 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_19 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_19 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 20)));
}

/**
 * Function to calculate a 20th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_20 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_20 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 21)));
}

/**
 * Function to calculate a 21th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_21 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_21 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 22)));
}

/**
 * Function to calculate a 22th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_22 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_22 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 23)));
}

/**
 * Function to calculate a 23th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_23 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_23 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 24)));
}

/**
 * Function to calculate a 24th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_24 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_24 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 25)));
}

/**
 * Function to calculate a 25th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_26_25 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_25 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[26]));
}

/**
 * Function to calculate a 0th+27th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_26 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+26th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_25 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+25th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_24 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+24th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_23 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+23th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_22 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+22th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_21 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+21th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_20 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+20th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_19 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+19th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_18 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+18th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_17 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+17th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_16 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+16th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_11 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_11 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_15 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+15th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_12 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_12 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_14 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+14th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_13 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_13 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_13 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+13th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_14 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_14 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_12 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+12th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_15 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_15 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_11 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_16 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_16 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_17 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_17 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_18 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_18 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_19 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_19 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 20)));
}

/**
 * Function to calculate a 20th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_20 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_20 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 21)));
}

/**
 * Function to calculate a 21th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_21 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_21 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 22)));
}

/**
 * Function to calculate a 22th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_22 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_22 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 23)));
}

/**
 * Function to calculate a 23th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_23 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_23 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 24)));
}

/**
 * Function to calculate a 24th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_24 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_24 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 25)));
}

/**
 * Function to calculate a 25th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_25 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_25 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 26)));
}

/**
 * Function to calculate a 26th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_27_26 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_26 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[27]));
}

/**
 * Function to calculate a 0th+28th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_27 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+27th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_26 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+26th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_25 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+25th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_24 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+24th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_23 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+23th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_22 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+22th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_21 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+21th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_20 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+20th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_19 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+19th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_18 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+18th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_17 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+17th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_11 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_11 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_16 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+16th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_12 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_12 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_15 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+15th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_13 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_13 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_14 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+14th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_14 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_14 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_13 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+13th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_15 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_15 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_12 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+12th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_16 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_16 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_11 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_17 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_17 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_18 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_18 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_19 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_19 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 20)));
}

/**
 * Function to calculate a 20th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_20 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_20 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 21)));
}

/**
 * Function to calculate a 21th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_21 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_21 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 22)));
}

/**
 * Function to calculate a 22th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_22 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_22 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 23)));
}

/**
 * Function to calculate a 23th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_23 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_23 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 24)));
}

/**
 * Function to calculate a 24th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_24 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_24 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 25)));
}

/**
 * Function to calculate a 25th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_25 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_25 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 26)));
}

/**
 * Function to calculate a 26th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_26 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_26 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 27)));
}

/**
 * Function to calculate a 27th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_28_27 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_27 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[28]));
}

/**
 * Function to calculate a 0th+29th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_0 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, svdup_n_f64 (p[0]),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_28 (pg, x, p + 1)));
}

/**
 * Function to calculate a 1st+28th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_1 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_1 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_27 (pg, x, p + 2)));
}

/**
 * Function to calculate a 2nd+27th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_2 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_2 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_26 (pg, x, p + 3)));
}

/**
 * Function to calculate a 3rd+26th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_3 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_3 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_25 (pg, x, p + 4)));
}

/**
 * Function to calculate a 4th+25th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_4 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_4 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_24 (pg, x, p + 5)));
}

/**
 * Function to calculate a 5th+24th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_5 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_5 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_23 (pg, x, p + 6)));
}

/**
 * Function to calculate a 6th+23th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_6 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_6 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_22 (pg, x, p + 7)));
}

/**
 * Function to calculate a 7th+22th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_7 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_7 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_21 (pg, x, p + 8)));
}

/**
 * Function to calculate a 8th+21th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_8 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_8 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_20 (pg, x, p + 9)));
}

/**
 * Function to calculate a 9th+20th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_9 (svbool_t pg,   ///< predicate.
                         const svfloat64_t x,   ///< svfloat64_t vector.
                         const double *p)       ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_9 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_19 (pg, x, p + 10)));
}

/**
 * Function to calculate a 10th+19th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_10 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_10 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_18 (pg, x, p + 11)));
}

/**
 * Function to calculate a 11th+18th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_11 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_11 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_17 (pg, x, p + 12)));
}

/**
 * Function to calculate a 12th+17th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_12 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_12 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_16 (pg, x, p + 13)));
}

/**
 * Function to calculate a 13th+16th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_13 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_13 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_15 (pg, x, p + 14)));
}

/**
 * Function to calculate a 14th+15th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_14 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_14 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_14 (pg, x, p + 15)));
}

/**
 * Function to calculate a 15th+14th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_15 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_15 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_13 (pg, x, p + 16)));
}

/**
 * Function to calculate a 16th+13th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_16 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_16 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_12 (pg, x, p + 17)));
}

/**
 * Function to calculate a 17th+12th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_17 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_17 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_11 (pg, x, p + 18)));
}

/**
 * Function to calculate a 18th+11th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_18 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_18 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_10 (pg, x, p + 19)));
}

/**
 * Function to calculate a 19th+10th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_19 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_19 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_9 (pg, x, p + 20)));
}

/**
 * Function to calculate a 20th+9th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_20 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_20 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_8 (pg, x, p + 21)));
}

/**
 * Function to calculate a 21th+8th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_21 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_21 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_7 (pg, x, p + 22)));
}

/**
 * Function to calculate a 22th+7th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_22 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_22 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_6 (pg, x, p + 23)));
}

/**
 * Function to calculate a 23th+6th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_23 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_23 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_5 (pg, x, p + 24)));
}

/**
 * Function to calculate a 24th+5th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_24 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_24 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_4 (pg, x, p + 25)));
}

/**
 * Function to calculate a 25th+4th order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_25 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_25 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_3 (pg, x, p + 26)));
}

/**
 * Function to calculate a 26th+3rd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_26 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_26 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_2 (pg, x, p + 27)));
}

/**
 * Function to calculate a 27th+2nd order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_27 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_27 (pg, x, p),
                 svmla_f64_x (pg, svdup_n_f64 (1.), x,
                              jbm_nxf64_polynomial_1 (pg, x, p + 28)));
}

/**
 * Function to calculate a 28th+1st order rational (svfloat64_t).
 *
 * \return svfloat64_t vector of rational values.
 */
static inline svfloat64_t
jbm_nxf64_rational_29_28 (svbool_t pg,  ///< predicate.
                          const svfloat64_t x,  ///< svfloat64_t vector.
                          const double *p)      ///< array of coefficients.
{
  return
    svdiv_f64_x (pg, jbm_nxf64_polynomial_28 (pg, x, p),
                 svmla_n_f64_x (pg, svdup_n_f64 (1.), x, p[29]));
}

/**
 * Function to calculate the well-conditioned function cbrt(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (svfloat64_t).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_cbrtwc (svbool_t pg,  ///< predicate.
                  const svfloat64_t x)
                  ///< svfloat64_t vector \f$\in[1/2,1]\f$.
{
  return jbm_nxf64_rational_11_6 (pg, x, K_CBRTWC_F64);
}

/**
 * Function to calculate the function cbrt(x) (svfloat64_t).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_cbrt (svbool_t pg,    ///< predicate.
                const svfloat64_t x)    ///< svfloat64_t vector.
{
  const svfloat64_t xa = svabs_f64_x (pg, x);
  svfloat64_t f, s, ef;
  svint64_t e, q, r;
  svbool_t m1, m2, m3;
  f = jbm_nxf64_frexp (pg, xa, &e);
  ef = svcvt_f64_s64_x (pg, e);
  ef = svmul_n_f64_x (pg, ef, 1. / 3.);
  q = jbm_nxf64_floor (pg, ef);
  r = svmls_n_s64_x (pg, e, q, 3);
  s = svdup_n_f64 (1.);
  s = svsel_f64 (svcmpeq_n_s64 (pg, r, 1), svdup_n_f64 (JBM_F64_CBRT2), s);
  s = svsel_f64 (svcmpeq_n_s64 (pg, r, 2), svdup_n_f64 (JBM_F64_CBRT4), s);
  f = svmul_f64_x (pg, jbm_nxf64_cbrtwc (pg, f), s);
  f = jbm_nxf64_ldexp (pg, f, q);
  f = jbm_nxf64_copysign (f, x);
  m1 = svcmpeq_n_f64 (pg, xa, 0.);
  m2 = svcmpeq_n_f64 (pg, xa, INFINITY);
  m3 = svcmpne_f64 (pg, xa, xa);
  return svsel_f64 (svorr_b_z (pg, m1, svorr_b_z (pg, m2, m3)), x, f);
}

/**
 * Function to calculate the well-conditioned function expm1(x) for x in
 * [-log(2)/2,log(2)/2] (svfloat64_t).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_expm1wc (svbool_t pg, ///< predicate.
                   const svfloat64_t x)
                   ///< svfloat64_t vector \f$\in[-\log 2/2,\log 2/2]\f$.
{
  return svmul_f64_x (pg, x, jbm_nxf64_rational_8_2 (pg, x, K_EXPM1WC_F64));
}

/**
 * Function to calculate the well-conditioned function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (svfloat64_t).
 *
 * \return function value.
 */
static inline svfloat64_t
jbm_nxf64_exp2wc (svbool_t pg,  ///< predicate.
                  const svfloat64_t x)
                  ///< svfloat64_t vector \f$\in[1/2,1]\f$.
{
  return jbm_nxf64_rational_9_4 (pg, x, K_EXP2WC_F64);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_nxf64 and
 * jbm_nxf64_exp2n functions.
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_exp2 (svbool_t pg,    ///< predicate.
                const svfloat64_t x)    ///< svfloat64_t vector.
{
  const svint64_t i = jbm_nxf64_floor (pg, x);
  const svfloat64_t f = svsub_f64_x (pg, x, svcvt_f64_s64_x (pg, i));
  return jbm_nxf64_ldexp (pg, jbm_nxf64_exp2wc (pg, f), i);
}

/**
 * Function to calculate the function exp(x) using the jbm_nxf64_exp2 function.
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_exp (svbool_t pg,     ///< predicate.
               const svfloat64_t x)     ///< svfloat64_t vector.
{
  return jbm_nxf64_exp2 (pg, svmul_n_f64_x (pg, x, M_LOG2E));
}

/**
 * Function to calculate the function exp10(x) using the jbm_nxf64_exp2
 * function (svfloat64_t).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_exp10 (svbool_t pg,   ///< predicate.
                 const svfloat64_t x)   ///< svfloat64_t vector.
{
  return jbm_nxf64_exp2 (pg, svmul_n_f64_x (pg, x, M_LN10 / M_LN2));
}

/**
 * Function to calculate the function expm1(x) using the jbm_nxf64_expm1wc and
 * jbm_nxf64_exp functions (svfloat64_t).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_expm1 (svbool_t pg,   ///< predicate.
                 const svfloat64_t x)   ///< svfloat64_t vector.
{
  const svbool_t m_small
    = svcmplt_n_f64 (pg, jbm_nxf64_abs (pg, x), M_LN2 / 2.);
  const svfloat64_t f_large = svsub_n_f64_x (pg, jbm_nxf64_exp (pg, x), 1.);
  return svsel_f64 (m_small, jbm_nxf64_expm1wc (pg, x), f_large);
}

/**
 * Function to calculate the well-conditioned function log2(x) for x in
 * [0.5,1] (svfloat64_t).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_log2wc (svbool_t pg,  ///< predicate.
                  const svfloat64_t x)
                  ///< svfloat64_t vector \f$\in[0.5,1]\f$.
{
  return svmul_f64_x (pg, x, jbm_nxf64_rational_11_5 (pg, x, K_LOG2WC_F64));
}

/**
 * Function to calculate the function log2(x) using jbm_logwc_nxf64 and
 * jbm_nxf64_frexp
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_log2 (svbool_t pg,    ///< predicate.
                const svfloat64_t x)    ///< svfloat64_t vector.
{
  svfloat64_t y, y2;
  svint64_t e, e1;
  svbool_t m;
  y = jbm_nxf64_frexp (pg, x, &e);
  m = svcmplt_n_f64 (pg, y, M_SQRT1_2);
  y2 = svadd_f64_x (pg, y, y);
  y = svsel_f64 (m, y2, y);
  e1 = svsub_n_s64_x (pg, e, 1);
  e = svsel_s64 (m, e1, e);
  y = svadd_f64_x (pg,
                   jbm_nxf64_log2wc (pg, svsub_n_f64_x (pg, y, 1.)),
                   svcvt_f64_s64_x (pg, e));
  y = svsel_f64 (svcmpeq_n_f64 (pg, x, 0.), svdup_n_f64 (-INFINITY), y);
  y = svsel_f64 (svcmpeq_n_f64 (pg, x, INFINITY), svdup_n_f64 (INFINITY), y);
  y = svsel_f64 (svcmplt_n_f64 (pg, x, 0.), svdup_n_f64 (NAN), y);
  return svsel_f64 (svcmpne_f64 (pg, x, x), x, y);
}

/**
 * Function to calculate the function log(x) using jbm_nxf64_log2
 * (svfloat64_t).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_log (svbool_t pg,     ///< predicate.
               const svfloat64_t x)     ///< svfloat64_t vector.
{
  return svmul_n_f64_x (pg, jbm_nxf64_log2 (pg, x), M_LN2);
}

/**
 * Function to calculate the function log10(x) using jbm_nxf64_log2
 * (svfloat64_t).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_log10 (svbool_t pg,   ///< predicate.
                 const svfloat64_t x)   ///< svfloat64_t vector.
{
  return svmul_n_f64_x (pg, jbm_nxf64_log2 (pg, x), M_LN2 / M_LN10);
}

/**
 * Function to calculate the function x^e with e an integer number
 * (svfloat64_t).
 *
 * \return function value (svfloat64_t) (vfloat64m1_t).
 */
static inline svfloat64_t
jbm_nxf64_pown (svbool_t pg,    ///< predicate.
                const svfloat64_t x,    ///< svfloat64_t vector.
                int e)          ///< exponent (int).
{
  svfloat64_t f, xn;
  unsigned int i;
  f = svdup_n_f64 (1.);
  if (e < 0)
    xn = jbm_nxf64_reciprocal (pg, x);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_nxf64_sqr (pg, xn))
    if (i & 1)
      f = svmul_f64_x (pg, f, xn);
  return f;
}

/**
 * Function to calculate the function f64 using the jbm_nxf64_exp2 and
 * jbm_nxf64_log2 functions.
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_pow1 (svbool_t pg,    ///< predicate.
                const svfloat64_t x,    ///< svfloat64_t vector.
                const double e) ///< exponent (double).
{
  return jbm_nxf64_exp2 (pg, svmul_n_f64_x (pg, jbm_nxf64_log2 (pg, x), e));
}

/**
 * Function to calculate the function f64 using the jbm_nxf64_exp2 and
 * jbm_nxf64_log2 functions.
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_pow (svbool_t pg,     ///< predicate.
               const svfloat64_t x,     ///< svfloat64_t vector.
               const svfloat64_t e)     ///< exponent (svfloat64_t).
{
  return jbm_nxf64_exp2 (pg, svmul_f64_x (pg, jbm_nxf64_log2 (pg, x), e));
}

/**
 * Function to calculate the well-conditioned function sin(x) for x in
 * [-pi/4,pi/4] (svfloat64_t)
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_sinwc (svbool_t pg,   ///< predicate.
                 const svfloat64_t x)
                 ///< svfloat64_t vector \f$\in[-\pi/4,\pi/4]\f$.
{
  return svmul_f64_x (pg, x,
                      jbm_nxf64_polynomial_6 (pg, jbm_nxf64_sqr (pg, x),
                                              K_SINWC_F64));
}

/**
 * Function to calculate the well-conditioned function cos(x) for x in
 * [-pi/4,pi/4] (svfloat64_t).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_coswc (svbool_t pg,   ///< predicate.
                 const svfloat64_t x)
                 ///< svfloat64_t vector \f$\in[-\pi/4,\pi/4]\f$.
{
  return jbm_nxf64_polynomial_6 (pg, jbm_nxf64_sqr (pg, x), K_COSWC_F64);
}

/**
 * Function to calculate the well-conditioned function tan(x) for x in
 * [-pi/4,pi/4] (svfloat64_t):
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_tanwc (svbool_t pg,   ///< predicate.
                 const svfloat64_t x)
                 ///< svfloat64_t vector \f$\in[-\pi/4,\pi/4]\f$.
{
  return svmul_f64_x (pg, x,
                      jbm_nxf64_rational_6_3 (pg, jbm_nxf64_sqr (pg, x),
                                              K_TANWC_F64));
}

/**
 * Function to calculate the well-conditioned functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_nxf64_sinwc approximation (svfloat64_t).
 */
static inline void
jbm_nxf64_sincoswc (svbool_t pg,        ///< predicate.
                    const svfloat64_t x,
                    ///< svfloat64_t vector \f$\in[-\pi/4,\pi/4]\f$.
                    svfloat64_t *s,     ///< pointer to sin value.
                    svfloat64_t *c)     ///< pointer to cos value.
{
  const svfloat64_t x2 = jbm_nxf64_sqr (pg, x);
  *s = svmul_f64_x (pg, x, jbm_nxf64_polynomial_6 (pg, x2, K_SINWC_F64));
  *c = jbm_nxf64_polynomial_6 (pg, x2, K_COSWC_F64);
}

/**
 * Function to calculate reduction to \f$2\,\pi\f$ in trigonometric functions
 * (svfloat64_t).
 *
 * \return reduced vector (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_trig (svbool_t pg,    ///< predicate.
                const svfloat64_t x,    ///< svfloat64_t vector.
                svint64_t *q)   ///< pointer to quadrant (svint64_t).
{
  const svfloat64_t t = svmul_n_f64_x (pg, x, M_2_PI);
  *q = jbm_nxf64_round (pg, t);
  return svmls_n_f64_x (pg, x, svcvt_f64_s64_x (pg, *q), M_PI_2);
}

/**
 * Function to calculate the function sin(x) from jbm_nxf64_sinwc and
 * jbm_nxf64_coswc approximations.
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_sin (svbool_t pg,     ///< predicate.
               const svfloat64_t x)     ///< svfloat64_t vector.
{
  svfloat64_t y, s, c;
  svint64_t q;
  svbool_t m;
  y = jbm_nxf64_trig (pg, x, &q);
  jbm_nxf64_sincoswc (pg, y, &s, &c);
  m = svcmpne_n_s64 (pg, svand_n_s64_x (pg, q, 1), 0);
  y = svsel_f64 (m, s, c);
  m = svcmpne_n_s64 (pg, svand_n_s64_x (pg, q, 2), 0);
  return svsel_f64 (m, y, jbm_nxf64_opposite (pg, y));
}

/**
 * Function to calculate the function cos(x) from jbm_nxf64_sinwc and
 * jbm_nxf64_coswc approximations (svfloat64_t).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_cos (svbool_t pg,     ///< predicate.
               const svfloat64_t x)     ///< svfloat64_t vector.
{
  svfloat64_t y, s, c;
  svint64_t q;
  svbool_t m;
  y = jbm_nxf64_trig (pg, x, &q);
  jbm_nxf64_sincoswc (pg, y, &s, &c);
  m = svcmpne_n_s64 (pg, svand_n_s64_x (pg, q, 1), 0);
  y = svsel_f64 (m, c, s);
  q = svadd_n_s64_x (pg, q, 1);
  m = svcmpne_n_s64 (pg, svand_n_s64_x (pg, q, 2), 0);
  return svsel_f64 (m, y, jbm_nxf64_opposite (pg, y));
}

/**
 * Function to calculate the functions sin(x) and cos(x) from
 * jbm_nxf64_sinwc and jbm_nxf64_coswc approximations (svfloat64_t).
 */
static inline void
jbm_nxf64_sincos (svbool_t pg,  ///< predicate.
                  const svfloat64_t x,  ///< svfloat64_t vector.
                  svfloat64_t *s,       ///< pointer to sin value.
                  svfloat64_t *c)       ///< pointer to cos value.
{
  svfloat64_t y, s1, c1, s2, c2;
  svint64_t q;
  svbool_t m;
  y = jbm_nxf64_trig (pg, x, &q);
  jbm_nxf64_sincoswc (pg, y, &s1, &c1);
  m = svcmpne_n_s64 (pg, svand_n_s64_x (pg, q, 1), 0);
  s2 = svsel_f64 (m, s1, c1);
  c2 = svsel_f64 (m, c1, s1);
  m = svcmpne_n_s64 (pg, svand_n_s64_x (pg, q, 2), 0);
  *s = svsel_f64 (m, s2, jbm_nxf64_opposite (pg, s2));
  q = svadd_n_s64_x (pg, q, 1);
  m = svcmpne_n_s64 (pg, svand_n_s64_x (pg, q, 2), 0);
  *c = svsel_f64 (m, c2, jbm_nxf64_opposite (pg, c2));
}

/**
 * Function to calculate the function tan(x) from jbm_nxf64_sincos function
 * (svfloat64_t).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_tan (svbool_t pg,     ///< predicate.
               const svfloat64_t x)     ///< svfloat64_t vector.
{
  svfloat64_t y, z;
  svint64_t q;
  svbool_t m;
  y = jbm_nxf64_tanwc (pg, jbm_nxf64_trig (pg, x, &q));
  z = svdivr_n_f64_x (pg, y, -1.);
  m = svcmpne_n_s64 (pg, svand_n_s64_x (pg, q, 1), 0);
  return svsel_f64 (m, y, z);
}

/**
 * Function to calculate the well-conditioned function atan(x) for x in [-1,1]
 * (svfloat64_t).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_atanwc (svbool_t pg,  ///< predicate.
                  const svfloat64_t x)  ///< svfloat64_t vector \f$\in[-1,1]\f$.
{
  return svmul_f64_x (pg, x,
                      jbm_nxf64_rational_11_5 (pg, jbm_nxf64_sqr (pg, x),
                                               K_ATANWC_F64));
}

/**
 * Function to calculate the function atan(x) using the jbm_nxf64_atanwc
 * function (svfloat64_t).
 *
 * \return function value (svfloat64_t in [-pi/2,pi/2]).
 */
static inline svfloat64_t
jbm_nxf64_atan (svbool_t pg,    ///< predicate.
                const svfloat64_t x)    ///< svfloat64_t vector.
{
  svfloat64_t f, ax;
  svbool_t m;
  ax = jbm_nxf64_abs (pg, x);
  m = svcmpgt_n_f64 (pg, ax, 1.);
  ax = svsel_f64 (m, ax, jbm_nxf64_reciprocal (pg, ax));
  f = jbm_nxf64_atanwc (pg, ax);
  f = svsel_f64 (m, f, svsub_f64_x (pg, svdup_n_f64 (M_PI_2), f));
  return jbm_nxf64_copysign (f, x);
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_nxf64_atan
 * function (svfloat64_t).
 *
 * \return function value (svfloat64_t in [-pi,pi]).
 */
static inline svfloat64_t
jbm_nxf64_atan2 (svbool_t pg,   ///< predicate.
                 const svfloat64_t y,   ///< svfloat64_t y component.
                 const svfloat64_t x)   ///< svfloat64_t x component.
{
  const svfloat64_t f = jbm_nxf64_atan (pg, svdiv_f64_x (pg, y, x));
  return svsel_f64 (m, g, f);
  return
    svsel_f64 (svcmpne_n_u64 (pg,
                              svand_n_u64_x (pg, svreinterpret_u64_f64 (x),
                                             JBM_F64_BITS_SIGN), 0),
               svadd_f64_x (pg, f,
                            jbm_nxf64_copysign (svdup_n_f64 (M_PI), y)), f);
}

/**
 * Function to calculate the function asin(x) using the jbm_nxf64_atan function
 * (svfloat64_t).
 *
 * \return function value (svfloat64_t in [-pi/2,pi/2]).
 */
static inline svfloat64_t
jbm_nxf64_asin (svbool_t pg,    ///< predicate.
                const svfloat64_t x)    ///< svfloat64_t vector.
{
  const svfloat64_t t = svsqrt_f64_x (pg, svsub_n_f64_x (pg, svdup_n_f64 (1.),
                                                         jbm_nxf64_sqr (pg,
                                                                        x)));
  return jbm_nxf64_atan (pg, svdiv_f64_x (pg, x, t));
}

/**
 * Function to calculate the function acos(x) using the jbm_nxf64_atan function
 * (svfloat64_t).
 *
 * \return function value (svfloat64_t in [0,pi]).
 */
static inline svfloat64_t
jbm_nxf64_acos (svbool_t pg,    ///< predicate.
                const svfloat64_t x)    ///< svfloat64_t vector.
{
  const svfloat64_t k1 = svdup_n_f64 (1.);
  const svfloat64_t t = svsqrt_f64_x (pg,
                                      svdiv_f64_x (pg, svsub_f64_x (pg, k1, x),
                                                   svadd_f64_x (pg, k1, x)));
  return jbm_nxf64_dbl (pg, jbm_nxf64_atan (pg, t));
}

/**
 * Function to calculate the function sinh(x).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_sinh (svbool_t pg,    ///< predicate.
                const svfloat64_t x)    ///< svfloat64_t vector.
{
  const svfloat64_t f = jbm_nxf64_expm1 (pg, jbm_nxf64_abs (pg, x));
  return
    jbm_nxf64_copysign
    (svmul_n_f64_x (pg,
                    svadd_f64_x (pg, f,
                                 svdiv_f64_x (pg, f,
                                              svadd_n_f64_x (pg, f, 1.))), 0.5),
     x);
}

/**
 * Function to calculate the function cosh(x).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_cosh (svbool_t pg,    ///< predicate.
                const svfloat64_t x)    ///< svfloat64_t vector.
{
  const svfloat64_t f = jbm_nxf64_exp (pg, x);
  return svmul_n_f64_x (pg,
                        svadd_f64_x (pg, f, jbm_nxf64_reciprocal (pg, f)), 0.5);
}

/**
 * Function to calculate the function tanh(x).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_tanh (svbool_t pg,    ///< predicate.
                const svfloat64_t x)    ///< svfloat64_t vector.
{
  const svfloat64_t x2 = jbm_nxf64_dbl (pg, x);
  svfloat64_t f = jbm_nxf64_expm1 (pg, x2);
  f = svdiv_f64_x (pg, f, svadd_n_f64_x (pg, f, 2.));
  f = svsel_f64 (svcmpgt_n_f64 (pg, x2, JBM_DBL_MAX_E_EXP),
                 f, svdup_n_f64 (1.));
  return svsel_f64 (svcmplt_n_f64 (pg, x2, -JBM_DBL_MAX_E_EXP),
                    f, svdup_n_f64 (-1.));
}

/**
 * Function to calculate the function asinh(x).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_asinh (svbool_t pg,   ///< predicate.
                 const svfloat64_t x)   ///< svfloat64_t vector.
{
  const svfloat64_t t
    = svsqrt_f64_x (pg, svmla_f64_x (pg, svdup_n_f64 (1.), x, x));
  return jbm_nxf64_log (pg, svadd_f64_x (pg, x, t));
}

/**
 * Function to calculate the function acosh(x).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_acosh (svbool_t pg,   ///< predicate.
                 const svfloat64_t x)   ///< svfloat64_t vector.
{
  const svfloat64_t t
    = svsqrt_f64_x (pg, svsub_n_f64_x (pg, jbm_nxf64_sqr (pg, x), 1.));
  return jbm_nxf64_log (pg, svadd_f64_x (pg, x, t));
}

/**
 * Function to calculate the function atanh(x).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_atanh (svbool_t pg,   ///< predicate.
                 const svfloat64_t x)   ///< svfloat64_t vector.
{
  const svfloat64_t u = svdup_n_f64 (1.);
  return
    svmul_n_f64_x
    (pg,
     jbm_nxf64_log (pg,
                    svdiv_f64_x (pg, svadd_f64_x (pg, u, x),
                                 svsub_f64_x (pg, u, x))), 0.5);
}

/**
 * Function to calculate the well-conditioned function erf(x) for x in
 * [-1,1] (svfloat64_t).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_erfwc (svbool_t pg,   ///< predicate.
                 const svfloat64_t x)   ///< svfloat64_t vector \f$\in[-1,1]\f$.
{
  return
    svmul_f64_x (pg, x,
                 jbm_nxf64_rational_9_4 (pg, jbm_nxf64_sqr (pg, x),
                                         K_ERFWC_F64));
}

/**
 * Function to calculate the well-conditioned function erf(x) for x in
 * [-1,1] (svfloat64_t).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_erfcwc (svbool_t pg,  ///< predicate.
                  const svfloat64_t x)
                  ///< svfloat64_t vector \f$\in[1,\infty)\f$.
{
  const svfloat64_t x2 = 
  return
    svsel_f64 (svcmpgt_n_f64 (pg, x, K_ERFC_MAX_F64), svdup_n_f64 (0.),
               svmul_f64_x (pg,
                            jbm_nxf64_rational_16_8 (pg,
                                                     jbm_nxf64_reciprocal (pg,
                                                                           x),
                                                     K_ERFCWC_F64),
                             svdiv_f64_x (pg, x,
                                          jbm_nxf64_exp (pg,
                                                         jbm_nxf64_sqr (pg,
                                                                        x)))));
}

/**
 * Function to calculate the well-conditioned function erfc(x) for
 * \f$x\in[1,\infty]\f$ (svfloat64_t).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_erf (svbool_t pg,     ///< predicate.
               const svfloat64_t x)     ///< svfloat64_t vector.
{
  const svfloat64_t ax = jbm_nxf64_abs (pg, x);
  const svfloat64_t u = svdup_n_f64 (1.);
  const svfloat64_t f = svmul_f64_x (pg,
                                     svdiv_f64_x (pg, x, ax),
                                     svsub_f64_x (pg, u,
                                                  jbm_nxf64_erfcwc (pg, ax)));
  return svsel_f64 (svcmplt_f64 (pg, ax, u), jbm_nxf64_erfwc (pg, x), f);
}

/**
 * Function to calculate the function erf(x) using jbm_nxf64_erfwc and
 * jbm_nxf64_erfcwc (svfloat64_t).
 *
 * \return function value (svfloat64_t).
 */
static inline svfloat64_t
jbm_nxf64_erfc (svbool_t pg,    ///< predicate.
                const svfloat64_t x)    ///< svfloat64_t vector.
{
  const svfloat64_t ax = jbm_nxf64_abs (pg, x);
  const svfloat64_t u = svdup_n_f64 (1.);
  return
    svsel_f64 (svcmplt_f64 (pg, ax, u),
               svsub_f64_x (pg, u, jbm_nxf64_erfwc (pg, x)),
               svsub_f64_x (pg, u,
                            svmul_f64_x (pg, svdiv_f64_x (pg, x, ax),
                                         svsub_f64_x (pg, u,
                                                      jbm_nxf64_erfcwc (pg,
                                                                        ax)))));
}

/**
 * Function to calculate the solution of a svfloat64_t vector of reduced
 * quadratic equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return svfloat64_t vector of solution values.
 */
static inline svfloat64_t
jbm_nxf64_solve_quadratic_reduced (svbool_t pg, ///< predicate.
                                   svfloat64_t a,
///< svfloat64_t vector of 1st order coefficient of the equations.
                                   svfloat64_t b,
///< svfloat64_t vector of 0-th order coefficient of the equations.
                                   const svfloat64_t x1,
///< svfloat64_t vector of left limits of the solution intervals.
                                   const svfloat64_t x2)
///< svfloat64_t vector of right limits of the solution intervals.
{
  svfloat64_t k1, k2;
  a = svmul_n_f64_x (pg, a, -0.5);
  b = svsqrt_f64_x (pg, svsub_f64_x (pg, jbm_nxf64_sqr (pg, a), b));
  k1 = svadd_f64_x (pg, a, b);
  k2 = svsub_f64_x (pg, a, b);
  k1 = svsel_f64 (svcmplt_f64 (pg, k1, x1), k2, k1);
  return svsel_f64 (svcmpgt_f64 (pg, k1, x2), k2, k1);
}

/**
 * Function to calculate the solution of a svfloat64_t vector of quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^2+b\,x+c=0\f$.
 *
 * \return svfloat64_t vector of solution values.
 */
static inline svfloat64_t
jbm_nxf64_solve_quadratic (svbool_t pg, ///< predicate.
                           svfloat64_t a,
///< svfloat64_t vector of 2nd order coefficient of the equations.
                           svfloat64_t b,
///< svfloat64_t vector of 1st order coefficient of the equations.
                           svfloat64_t c,
///< svfloat64_t vector of 0-th order coefficient of the equations.
                           const svfloat64_t x1,
///< svfloat64_t vector of left limits of the solution intervals.
                           const svfloat64_t x2)
///< svfloat64_t vector of right limits of the solution intervals.
{
  return
    svsel_f64 (jbm_nxf64_small (pg, a),
               jbm_nxf64_solve_quadratic_reduced (pg, svdiv_f64_x (pg, b, a),
                                                  svdiv_f64_x (pg, c, a),
                                                  x1, x2);
               svdiv_f64_x (pg, jbm_nxf64_opposite (pg, c), b));
}

/**
 * Function to calculate the solution of a svfloat64_t vector of reduced cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^3+a\,x^2+b\,x+c=0\f$.
 *
 * \return svfloat64_t vector of solution values.
 */
static inline svfloat64_t
jbm_nxf64_solve_cubic_reduced (svbool_t pg,     ///< predicate.
                               svfloat64_t a,
///< svfloat64_t vector of 2nd order coefficient of the equations.
                               svfloat64_t b,
///< svfloat64_t vector of 1st order coefficient of the equations.
                               svfloat64_t c,
///< svfloat64_t vector of 0-th order coefficient of the equations.
                               const svfloat64_t x1,
///< svfloat64_t vector of left limits of the solution intervals.
                               const svfloat64_t x2)
///< svfloat64_t vector of right limits of the solution intervals.
{
  svfloat64_t a3, k0, k1, k2, l0, l1, l2, l3, l4, l5;
  a3 = svmul_n_f64_x (pg, a, 1. / 3.);
  k0 = jbm_nxf64_sqr (pg, a3);
  k1 = svsub_f64_x (pg, svmul_n_f64_x (pg, b, 1. / 3.), k0);
  k0 = svsub_f64_x (pg,
                    svmul_n_f64_x (pg,
                                   svsub_f64_x (pg, svmul_f64_x (pg, b, a3), c),
                                   0.5), svmul_f64_x (pg, a3, k0));
  k2 = svmla_f64_x (pg, svmul_f64_x (pg, k1, jbm_nxf64_sqr (pg, k1)), k0, k0);

  l1 = svsqrt_f64_x (pg, jbm_nxf64_opposite (pg, k1));
  l0 = svmul_n_f64_x
    (pg,
     jbm_nxf64_acos (pg,
                     svdiv_f64_x (pg, k0,
                                  svmul_f64_x (pg, l1,
                                               jbm_nxf64_sqr (pg, l1)))),
     1. / 3.);
  l1 = jbm_nxf64_dbl (pg, l1);
  l2 = svsub_f64_x (pg, svmul_f64_x (pg, l1, jbm_nxf64_cos (pg, l0)), a3);
  l3 =
    svsub_f64_x
    (pg,
     svmul_f64_x (pg, l1,
                  jbm_nxf64_cos (pg, svadd_n_f64_x (pg, l0, 2. * M_PI / 3.))),
     a3);
  l3 = svsel_f64 (svorr_b_z (pg, svcmplt_f64 (pg, l2, x1),
                             svcmpgt_f64 (pg, l2, x2)), l2, l3);
  l4 =
    svsub_f64_x
    (pg,
     svmul_f64_x (pg, l1,
                  jbm_nxf64_cos (pg, svsub_n_f64_x (pg, l0, 2. * M_PI / 3.))),
     a3);
  l4 = svsel_f64 (svorr_b_z (pg, svcmplt_f64 (pg, l3, x1),
                             svcmpgt_f64 (pg, l3, x2)), l3, l4);

  k1 = svsqrt_f64_x (pg, k2);
  l5 = jbm_nxf64_cbrt (pg, svadd_f64_x (pg, k0, k1));
  l5 = svadd_f64_x (pg, l5,
                    svsub_f64_x (pg,
                                 jbm_nxf64_cbrt (pg, svsub_f64_x (pg, k0, k1)),
                                 a3));
  return svsel_f64 (svcmplt_n_f64 (pg, k2, 0.), l4, l5);
}

/**
 * Function to calculate the solution of a svfloat64_t vector of cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return svfloat64_t vector of solution values.
 */
static inline svfloat64_t
jbm_nxf64_solve_cubic (svbool_t pg,     ///< predicate.
                       svfloat64_t a,
///< svfloat64_t vector of 3rd order coefficient of the equations.
                       svfloat64_t b,
///< svfloat64_t vector of 2nd order coefficient of the equations.
                       svfloat64_t c,
///< svfloat64_t vector of 1st order coefficient of the equations.
                       svfloat64_t d,
///< svfloat64_t vector of 0-th order coefficient of the equations.
                       const svfloat64_t x1,
///< svfloat64_t vector of left limits of the solution intervals.
                       const svfloat64_t x2)
///< svfloat64_t vector of right limits of the solution intervals.
{
  return
    svsel_f64
    (jbm_nxf64_small (pg, a),
     jbm_nxf64_solve_cubic_reduced (pg, svdiv_f64_x (pg, b, a),
                                    svdiv_f64_x (pg, c, a),
                                    svdiv_f64_x (pg, d, a), x1, x2),
     jbm_nxf64_solve_quadratic (pg, b, c, d, x1, x2));
}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (svfloat64_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat64_t
jbm_nxf64_flux_limiter_total (svbool_t pg,      ///< predicate.
                              const svfloat64_t d1 __attribute__((unused)),
                              ///< 1st flux limiter function parameter.
                              const svfloat64_t d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return svdup_n_f64 (0.);
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (svfloat64_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat64_t
jbm_nxf64_flux_limiter_null (svbool_t pg,       ///< predicate.
                             const svfloat64_t d1 __attribute__((unused)),
                             ///< 1st flux limiter function parameter.
                             const svfloat64_t d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return svdup_n_f64 (1.);
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (svfloat64_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat64_t
jbm_nxf64_flux_limiter_centred (svbool_t pg,    ///< predicate.
                                const svfloat64_t d1,
                                ///< 1st flux limiter function parameter.
                                const svfloat64_t d2)
                                ///< 2nd flux limiter function parameter.
{
  return svsel_f64 (jbm_nxf64_small (pg, d2),
                    svdup_n_f64 (0.), svdiv_f64_x (pg, d1, d2));
}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (svfloat64_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat64_t
jbm_nxf64_flux_limiter_superbee (svbool_t pg,   ///< predicate.
                                 const svfloat64_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const svfloat64_t d2)
                                 ///< 2nd flux limiter function parameter.
{
  svfloat64_t r;
  r = svdiv_f64_x (pg, d1, d2);
  r = svmax_f64_x (pg, svmin_n_f64_x (pg, jbm_nxf64_dbl (pg, r), 1.),
                   svmin_n_f64_x (pg, r, 2.));
  return svsel_f64 (svcmpgt_n_f64 (pg, svmul_f64_x (pg, d1, d2), DBL_EPSILON),
                    svdup_n_f64 (0.), r);
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (svfloat64_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat64_t
jbm_nxf64_flux_limiter_minmod (svbool_t pg,     ///< predicate.
                               const svfloat64_t d1,
                               ///< 1st flux limiter function parameter.
                               const svfloat64_t d2)
                               ///< 2nd flux limiter function parameter.
{
  svfloat64_t r;
  r = svmin_n_f64_x (pg, svdiv_f64_x (pg, d1, d2), 1.);
  return svsel_f64 (svcmpgt_n_f64 (pg, svmul_f64_x (pg, d1, d2), DBL_EPSILON),
                    svdup_n_f64 (0.), r);
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (svfloat64_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat64_t
jbm_nxf64_flux_limiter_VanLeer (svbool_t pg,    ///< predicate.
                                const svfloat64_t d1,
                                ///< 1st flux limiter function parameter.
                                const svfloat64_t d2)
                                ///< 2nd flux limiter function parameter.
{
  svfloat64_t r, k;
  r = svdiv_f64_x (pg, d1, d2);
  k = jbm_nxf64_abs (pg, r);
  r = svdiv_f64_x (pg, svadd_f64_x (pg, r, k), svadd_n_f64_x (pg, k, 1.));
  return svsel_f64 (svcmpgt_n_f64 (pg, svmul_f64_x (pg, d1, d2), DBL_EPSILON),
                    svdup_n_f64 (0.), r);
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (svfloat64_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat64_t
jbm_nxf64_flux_limiter_VanAlbada (svbool_t pg,  ///< predicate.
                                  const svfloat64_t d1,
                                  ///< 1st flux limiter function parameter.
                                  const svfloat64_t d2)
                                  ///< 2nd flux limiter function parameter.
{
  svfloat64_t r, k;
  r = svdiv_f64_x (pg, d1, d2);
  k = jbm_nxf64_sqr (pg, r);
  r = svdiv_f64_x (pg, svadd_f64_x (pg, r, k), svadd_n_f64_x (pg, k, 1.));
  return svsel_f64 (svcmpgt_n_f64 (pg, svmul_f64_x (pg, d1, d2), DBL_EPSILON),
                    svdup_n_f64 (0.), r);
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (svfloat64_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat64_t
jbm_nxf64_flux_limiter_minsuper (svbool_t pg,   ///< predicate.
                                 const svfloat64_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const svfloat64_t d2)
                                 ///< 2nd flux limiter function parameter.
{
  svfloat64_t r;
  r = svmin_f64_x (pg, svdiv_f64_x (pg, d1, d2), svdup_n_f64 (2.));
  return svsel_f64 (svcmpgt_n_f64 (pg, svmul_f64_x (pg, d1, d2), DBL_EPSILON),
                    svdup_n_f64 (0.), r);
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (svfloat64_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat64_t
jbm_nxf64_flux_limiter_supermin (svbool_t pg,   ///< predicate.
                                 const svfloat64_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const svfloat64_t d2)
                                 ///< 2nd flux limiter function parameter.
{
  svfloat64_t r;
  r = svdiv_f64_x (pg, d1, d2);
  r = svmin_n_f64_x (pg, jbm_nxf64_dbl (pg, r), 1.);
  return svsel_f64 (svcmpgt_n_f64 (pg, svmul_f64_x (pg, d1, d2), DBL_EPSILON),
                    svdup_n_f64 (0.), r);
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (svfloat64_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat64_t
jbm_nxf64_flux_limiter_monotonized_central (svbool_t pg,        ///< predicate.
                                            const svfloat64_t d1,
///< 1st flux limiter function parameter.
                                            const svfloat64_t d2)
///< 2nd flux limiter function parameter.
{
  svfloat64_t r, rm;
  r = svdiv_f64_x (pg, d1, d2);
  rm = svmul_n_f64_x (pg, svadd_n_f64_x (pg, r, 1.), 0.5);
  rm = svsel_f64 (svcmplt_n_f64 (pg, r, 3.), svdup_n_f64 (2.), rm);
  rm = svsel_f64 (svcmpgt_n_f64 (pg, r, 1. / 3.), jbm_nxf64_dbl (pg, r), rm);
  return svsel_f64 (svcmpgt_n_f64 (pg, svmul_f64_x (pg, d1, d2), DBL_EPSILON),
                    svdup_n_f64 (0.), rm);
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (svfloat64_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat64_t
jbm_nxf64_flux_limiter_mean (svbool_t pg,       ///< predicate.
                             const svfloat64_t d1,
                             ///< 1st flux limiter function parameter.
                             const svfloat64_t d2)
                             ///< 2nd flux limiter function parameter.
{
  svfloat64_t r;
  r = svmul_n_f64_x (pg, svadd_n_f64_x (pg, svdiv_f64_x (pg, d1, d2), 1.), 0.5);
  return svsel_f64 (svcmpgt_n_f64 (pg, svmul_f64_x (pg, d1, d2), DBL_EPSILON),
                    svdup_n_f64 (0.), r);
}

/**
 * Function to do a flux limiter function (svfloat64_t).
 *
 * \return flux limiter function value.
 */
static inline svfloat64_t
jbm_nxf64_flux_limiter (svbool_t pg,    ///< predicate.
                        const svfloat64_t d1,
                        ///< 1st flux limiter function parameter.
                        const svfloat64_t d2,
                        ///< 2nd flux limiter function parameter.
                        unsigned int type)
                        ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_nxf64_flux_limiter_total (pg, d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_nxf64_flux_limiter_null (pg, d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_nxf64_flux_limiter_centred (pg, d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_nxf64_flux_limiter_superbee (pg, d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_nxf64_flux_limiter_minmod (pg, d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_nxf64_flux_limiter_VanLeer (pg, d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_nxf64_flux_limiter_VanAlbada (pg, d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_nxf64_flux_limiter_minsuper (pg, d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_nxf64_flux_limiter_supermin (pg, d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_nxf64_flux_limiter_monotonized_central (pg, d1, d2);
    }
  return jbm_nxf64_flux_limiter_mean (pg, d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (svfloat64_t).
 *
 * \return svfloat64_t vector of integral values.
 */
static inline svfloat64_t
jbm_nxf64_integral (svfloat64_t (*f) (svbool_t, const svfloat64_t),
                    ///< pointer to the function to integrate.
                    svbool_t pg,        ///< predicate.
                    const svfloat64_t x1,       ///< left limit of the interval.
                    const svfloat64_t x2)
                    ///< right limit of the interval.
{
  svfloat64_t k, x, dx;
#if JBM_INTEGRAL_GAUSS_N > 1
  svfloat64_t k2, f1, f2;
#endif
  unsigned int i;
  dx = svmul_n_f64_x (pg, svsub_f64_x (pg, x2, x1), 0.5);
  x = svmul_n_f64_x (pg, svadd_f64_x (pg, x2, x1), 0.5);
  k = svmul_n_f64_x (pg, f (pg, x), JBM_INTEGRAL_GAUSS_A_F32[0]);
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = svmul_n_f64_x (pg, dx, JBM_INTEGRAL_GAUSS_B_F32[i]);
      f1 = f (pg, svsub_f64_x (pg, x, k2));
      f2 = f (pg, svadd_f64_x (pg, x, k2));
      k = svmla_n_f64_x (pg, k, svadd_f64_x (pg, f1, f2),
                         JBM_INTEGRAL_GAUSS_A_F32[i]);
    }
#endif
  return svmul_f64_x (pg, k, dx);
}

#endif
