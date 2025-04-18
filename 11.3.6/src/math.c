/* JB - A library with useful mathematical, XML, JSON, GTK and OpenGL functions.
 *
 * Copyright 2005-2025, Javier Burguete Tolosa.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the
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
 * \file math.c
 * \brief Source file with useful mathematical functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2025, Javier Burguete Tolosa.
 */
#include "math.h"

/**
 * Function to sort from the highest to the lowest the indexes of an array of
 * JBFLOAT numbers by the flash method.
 */
void
jbm_index_sort_flash (JBFLOAT *restrict x,      ///< array of JBFLOAT numbers.
                      unsigned int *restrict ni,        ///< array of indexes.
                      unsigned int n)   ///< number of array elements.
{
  unsigned int *nj, *nk, *l1, *l2;
  JBFLOAT xi, xmin, xmax;
  int i, j, m, m1;
  unsigned int last;
  last = n - 1;
  if (last <= JBM_INDEX_SORT_FLASH_MIN)
    {
      jbm_index_sort_insertion (x, ni, n);
      return;
    }
  m = last / JBM_INDEX_SORT_FLASH_CLASS + 1;
  m1 = m + 1;
  nj = (unsigned int *) g_malloc ((n + m1) * 2 * sizeof (unsigned int));
  nk = nj + n;
  l1 = nk + n;
  l2 = l1 + m1;
  j = i = last;
  xmax = xmin = x[ni[i]];
  while (--i >= 0)
    {
      xi = x[ni[i]];
      if (xi > xmax)
        xmax = xi, j = i;
      else if (xi < xmin)
        xmin = xi;
    }
  if ((xmax - xmin) < JBM_EPSILON)
    goto sorted;
  jbm_changeu (ni, ni + j);
  i = m;
  l1[i] = 1;
  while (--i >= 0)
    l1[i] = 0;
  for (i = n; --i > 0;)
    {
      j = jbm_max (0, jbm_min (m,
                               FLOOR (m1 * (x[ni[i]] - xmin) / (xmax - xmin))));
      nj[i] = j;
      ++l1[j];
    }
  nj[0] = m;
  for (i = m, l2[i] = l1[i]; --i >= 0;)
    l2[i] = l2[i + 1] + l1[i];
  for (i = n; --i > 0;)
    nk[--l2[nj[i]]] = ni[i];
  for (i = n; --i > 0;)
    ni[i] = nk[i];
  --l2[m];
  i = m;
  do
    {
      j = l1[i];
      nk = ni + l2[i];
      if (j <= JBM_INDEX_SORT_FLASH_MIN)
        jbm_index_sort_insertion (x, nk, j);
      else
        jbm_index_sort_flash (x, nk, j);
    }
  while (--i >= 0);
sorted:
  free (nj);
}

#if JBM_HIGH_PRECISION != JBM_LOW_PRECISION

/**
 * Function to sort from the highest to the lowest the indexes of an array of
 * JBDOUBLE numbers by the flash method.
 */
void
jbm_index_sort_flashl (JBDOUBLE *restrict x,    ///< array of JBDOUBLE numbers.
                       unsigned int *restrict ni,       ///< array of indexes.
                       unsigned int n)
                       ///< the highest element number of the arrays.
{
  unsigned int *nj, *nk, *l1, *l2;
  JBDOUBLE xi, xmin, xmax;
  int i, j, m, m1, n1;
  if (n <= JBM_INDEX_SORT_FLASH_MIN)
    {
      jbm_index_sort_insertionl (x, ni, n);
      return;
    }
  m = n / JBM_INDEX_SORT_FLASH_CLASS + 1;
  m1 = m + 1;
  n1 = n + 1;
  nj = (unsigned int *) g_malloc ((n1 + m1) * 2 * sizeof (unsigned int));
  nk = nj + n1;
  l1 = nk + n1;
  l2 = l1 + m1;
  j = i = n;
  xmax = xmin = x[ni[i]];
  while (--i >= 0)
    {
      xi = x[ni[i]];
      if (xi > xmax)
        xmax = xi, j = i;
      else if (xi < xmin)
        xmin = xi;
    }
  if ((xmax - xmin) < JBM_EPSILONL)
    goto sorted;
  jbm_changeu (ni, ni + j);
  i = m;
  l1[i] = 1;
  while (--i >= 0)
    l1[i] = 0;
  for (i = n1; --i > 0;)
    {
      j = jbm_max (0,
                   jbm_min (m,
                            FLOORL (m1 * (x[ni[i]] - xmin) / (xmax - xmin))));
      nj[i] = j;
      ++l1[j];
    }
  nj[0] = m;
  for (i = m, l2[i] = l1[i]; --i >= 0;)
    l2[i] = l2[i + 1] + l1[i];
  for (i = n1; --i > 0;)
    nk[--l2[nj[i]]] = ni[i];
  for (i = n1; --i > 0;)
    ni[i] = nk[i];
  --l2[m];
  i = m;
  do
    {
      j = l1[i] - 1;
      nk = ni + l2[i];
      if (j < JBM_INDEX_SORT_FLASH_MIN)
        jbm_index_sort_insertionl (x, nk, j);
      else
        jbm_index_sort_flashl (x, nk, j);
    }
  while (--i >= 0);
sorted:
  g_free (nj);
}

#endif
