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
 * \file jb_config.h
 * \brief Header file to configure the jb library.
 * \author Javier Burguete Tolosa,
 * \copyright Copyright 2005-2026, Javier Burguete Tolosa.
 */
#ifndef JB_CONFIG__H
#define JB_CONFIG__H 1

#include "config.h"

#define JB_DEBUG_FILE 0
///< define if the debug information is displayed in a terminal (0) or in a
///< file (1).
#define JB_BUFFER_SIZE 512      ///< size of string buffers.
#define FRS "%"JB_BUFFER_SIZE"s"        ///< format of the string buffer input.

#define JBM_INTEGRAL_GAUSS_N 4  ///< method of gaussian integral.

#define JBW_GRAPHIC_N_TICS 6    ///< maximum number of tics in a JBWGraphic.
#define JBW_GRAPHIC_N_CHARS 12
///< maximum number of characters displayed in a graphical label.
#define JBW_GRAPHIC_FONT_SIZE 14
///< font size displayed in graphical labels.

///> threshold for using alloca() instead of malloc().
#ifndef JB_MAX_ALLOCA_SIZE
#if defined(__APPLE__) || defined(__MACH__) \
 || defined(__OpenBSD__)
  /* macOS and OpenBSD: thread stack ~512 KB */
#define JB_MAX_ALLOCA_SIZE 8192u
#elif defined(_WIN32) || defined(_WIN64) \
   || defined(__FreeBSD__) || defined(__NetBSD__) \
   || defined(__DragonFly__) || defined(__HAIKU__)
  /* Windows, FreeBSD, NetBSD, DragonFly, Haiku: 1-2 MB */
#define JB_MAX_ALLOCA_SIZE 16384u
#elif defined(__linux__) || defined(__sun) || defined(__illumos__) \
   || defined(__GNU__) || defined(__gnu_hurd__)
  /* Linux, Solaris, illumos, Hurd: 8 MB */
#define JB_MAX_ALLOCA_SIZE 65536u
#else
  /* Unknown platform: conservative value */
#define JB_MAX_ALLOCA_SIZE 8192u
#endif
#endif

#define JBW_OPEN_GL_OLD 1
///< macro to disable 64 bits floats feature in OpenGL.

#endif
