/* JB - A library with useful mathematical, XML, GTK+ and OpenGL functions.
 *
 * Copyright 2005-2014, Javier Burguete Tolosa.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 	1. Redistributions of source code must retain the above copyright notice,
 * 		this list of conditions and the following disclaimer.
 * 
 * 	2. Redistributions in binary form must reproduce the above copyright notice,
 * 		this list of conditions and the following disclaimer in the
 * 		documentation and/or other materials provided with the distribution.
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
 * \copyright Copyright 2005-2014, Javier Burguete Tolosa.
 */
#ifndef JB_CONFIG__H
#define JB_CONFIG__H 1

/**
 * \def JB_PRECISION
 * \brief Definition of the accuracy.
 */
#define JB_PRECISION 3

/**
 * \def JB_DEBUG_FILE
 * \brief Define if the debug information is displayed in a terminal (0) or in a
 *   file (1).
 */
#define JB_DEBUG_FILE 0

/**
 * \def JB_BUFFER_SIZE
 * \brief Size of string buffers.
 */
#define JB_BUFFER_SIZE	512
/**
 * \def FRS
 * \brief Format of the string buffer input.
 */
#define FRS "%512s"

/**
 * \def JBM_INTEGRAL_GAUSS_N
 * \brief Method of gaussian integral.
 */
#define JBM_INTEGRAL_GAUSS_N 4

/**
 * \def JBW_GRAPHIC_N_LABELS
 * \brief Number of maximum labels in a JBWGraphic.
 */
#define JBW_GRAPHIC_N_LABELS	6
/**
 * \def JBW_GRAPHIC_N_CHARS
 * \brief Number of characters displayed in a graphical label.
 */
#define JBW_GRAPHIC_N_CHARS		12
/**
 * \def JBW_GRAPHIC_FONT
 * \brief Font displayed in a graphical label.
 */
#define JBW_GRAPHIC_FONT		"courier 10"

// These macros decide if the corresponding functions have to be compiled

/**
 * \def JB_FREE_NULL
 * \brief Macro deciding if the function jb_free_null() has to be compiled.
 */
#define JB_FREE_NULL 		1
/**
 * \def JB_FUNCTION_NULL
 * \brief Macro deciding if the function jb_function_null() has to be compiled.
 */
#define JB_FUNCTION_NULL	1
/**
 * \def JB_REALLOC
 * \brief Macro deciding if the function jb_realloc() has to be compiled.
 */
#define JB_REALLOC			1
/**
 * \def JB_TRY_REALLOC
 * \brief Macro deciding if the function jb_try_realloc() has to be compiled.
 */
#define JB_TRY_REALLOC		1
/**
 * \def JB_STRDUP
 * \brief Macro deciding if the function jb_strdup() has to be compiled.
 */
#define JB_STRDUP			1
/**
 * \def JB_SLIST_FREE
 * \brief Macro deciding if the function jb_slist_free() has to be compiled.
 */
#define JB_SLIST_FREE		1
/**
 * \def JBM_INDEX_SORT_FLASH
 * \brief Macro deciding if the function jb_index_sort_flash() has to be
 *   compiled.
 */
#define JBM_INDEX_SORT_FLASH	1
/**
 * \def JB_XML_NODE_GET_FLOAT
 * \brief Macro deciding if the function jb_xml_node_get_float() has to be
 *   compiled.
 */
#define JB_XML_NODE_GET_FLOAT				1
/**
 * \def JB_XML_NODE_SET_FLOAT
 * \brief Macro deciding if the function jb_xml_node_set_float() has to be
 *   compiled.
 */
#define JB_XML_NODE_SET_FLOAT				1
/**
 * \def JB_XML_NODE_GET_INT
 * \brief Macro deciding if the function jb_xml_node_get_int() has to be
 *   compiled.
 */
#define JB_XML_NODE_GET_INT					1
/**
 * \def JB_XML_NODE_SET_INT
 * \brief Macro deciding if the function jb_xml_node_set_int() has to be
 *   compiled.
 */
#define JB_XML_NODE_SET_INT					1
/**
 * \def JB_XML_NODE_GET_TIME
 * \brief Macro deciding if the function jb_xml_node_get_time() has to be
 *   compiled.
 */
#define JB_XML_NODE_GET_TIME				1
/**
 * \def JB_XML_NODE_SET_TIME
 * \brief Macro deciding if the function jb_xml_node_set_time() has to be
 *   compiled.
 */
#define JB_XML_NODE_SET_TIME				1
/**
 * \def JB_XML_NODE_GET_FLOAT_WITH_DEFAULT
 * \brief Macro deciding if the function jb_xml_node_get_float_with_default()
 *   has to be compiled.
 */
#define JB_XML_NODE_GET_FLOAT_WITH_DEFAULT	1
/**
 * \def JB_XML_NODE_SET_FLOAT_WITH_DEFAULT
 * \brief Macro deciding if the function jb_xml_node_set_float_with_default()
 *   has to be compiled.
 */
#define JB_XML_NODE_SET_FLOAT_WITH_DEFAULT	1
/**
 * \def JB_XML_NODE_GET_INT_WITH_DEFAULT
 * \brief Macro deciding if the function jb_xml_node_get_int_with_default() has
 *   to be compiled.
 */
#define JB_XML_NODE_GET_INT_WITH_DEFAULT	1
/**
 * \def JB_XML_NODE_SET_INT_WITH_DEFAULT
 * \brief Macro deciding if the function jb_xml_node_set_int_with_default() has
 *   to be compiled.
 */
#define JB_XML_NODE_SET_INT_WITH_DEFAULT	1
/**
 * \def JB_XML_NODE_GET_TIME_WITH_DEFAULT
 * \brief Macro deciding if the function jb_xml_node_get_time_with_default() has
 *   to be compiled.
 */
#define JB_XML_NODE_GET_TIME_WITH_DEFAULT	1
/**
 * \def JB_XML_NODE_SET_TIME_WITH_DEFAULT
 * \brief Macro deciding if the function jb_xml_node_set_time_with_default()
 *   has to be compiled.
 */
#define JB_XML_NODE_SET_TIME_WITH_DEFAULT	1
/**
 * \def JB_XML_NODE_GET_CONTENT_FILE
 * \brief Macro deciding if the function jb_xml_node_get_content_file() has to
 *   be compiled.
 */
#define JB_XML_NODE_GET_CONTENT_FILE		1
/**
 * \def JB_XML_NODE_SET_CONTENT_FILE
 * \brief Macro deciding if the function jb_xml_node_set_content_file() has to
 *   be compiled.
 */
#define JB_XML_NODE_SET_CONTENT_FILE		1

// These macros decide if the corresponding functions have to be inline 

/**
 * \def INLINE_JB_CHANGE
 * \brief Macro deciding if the function JBChange() has to be inlined.
 */
#define INLINE_JB_CHANGE		1
/**
 * \def INLINE_JB_FLENGTH
 * \brief Macro deciding if the function jb_flength() has to be inlined.
 */
#define INLINE_JB_FLENGTH		1
/**
 * \def INLINE_JB_MAKE_TIME
 * \brief Macro deciding if the function jb_make_time() has to be inlined.
 */
#define INLINE_JB_MAKE_TIME		0
/**
 * \def INLINE_JB_GET_TIME
 * \brief Macro deciding if the function jb_get_time() has to be inlined.
 */
#define INLINE_JB_GET_TIME		0
/**
 * \def INLINE_JB_GET_TIME_FILE
 * \brief Macro deciding if the function jb_get_time_file() has to be inlined.
 */
#define INLINE_JB_GET_TIME_FILE	0
/**
 * \def INLINE_JB_SET_TIME
 * \brief Macro deciding if the function jb_set_time() has to be inlined.
 */
#define INLINE_JB_SET_TIME		0
/**
 * \def INLINE_JBM_FCOMPARE
 * \brief Macro deciding if the function jbm_fcompare() has to be inlined.
 */
#define INLINE_JBM_FCOMPARE							1
/**
 * \def INLINE_JBM_MAX
 * \brief Macro deciding if the function jbm_max() has to be inlined.
 */
#define INLINE_JBM_MAX								1
/**
 * \def INLINE_JBM_MIN
 * \brief Macro deciding if the function jbm_min() has to be inlined.
 */
#define INLINE_JBM_MIN								1
/**
 * \def INLINE_JBM_MAXL
 * \brief Macro deciding if the function jbm_maxl() has to be inlined.
 */
#define INLINE_JBM_MAXL								1
/**
 * \def INLINE_JBM_MINL
 * \brief Macro deciding if the function jbm_minl() has to be inlined.
 */
#define INLINE_JBM_MINL								1
/**
 * \def INLINE_JBM_MAXLL
 * \brief Macro deciding if the function jbm_maxll() has to be inlined.
 */
#define INLINE_JBM_MAXLL							1
/**
 * \def INLINE_JBM_MINLL
 * \brief Macro deciding if the function jbm_minll() has to be inlined.
 */
#define INLINE_JBM_MINLL							1
/**
 * \def INLINE_JBM_MODMIN
 * \brief Macro deciding if the function jbm_modmin() has to be inlined.
 */
#define INLINE_JBM_MODMIN							1
/**
 * \def INLINE_JBM_MODMINL
 * \brief Macro deciding if the function jbm_modminl() has to be inlined.
 */
#define INLINE_JBM_MODMINL							1
/**
 * \def INLINE_JBM_MODMINLL
 * \brief Macro deciding if the function jbm_modminll() has to be inlined.
 */
#define INLINE_JBM_MODMINLL							1
/**
 * \def INLINE_JBM_FMODMIN
 * \brief Macro deciding if the function jbm_fmodmin() has to be inlined.
 */
#define INLINE_JBM_FMODMIN							1
/**
 * \def INLINE_JBM_CHANGE
 * \brief Macro deciding if the function jbm_change() has to be inlined.
 */
#define INLINE_JBM_CHANGE							1
/**
 * \def INLINE_JBM_CHANGEL
 * \brief Macro deciding if the function jbm_changel() has to be inlined.
 */
#define INLINE_JBM_CHANGEL							1
/**
 * \def INLINE_JBM_CHANGELL
 * \brief Macro deciding if the function jbm_changell() has to be inlined.
 */
#define INLINE_JBM_CHANGELL							1
/**
 * \def INLINE_JBM_FCHANGE
 * \brief Macro deciding if the function jbm_fchange() has to be inlined.
 */
#define INLINE_JBM_FCHANGE							1
/**
 * \def INLINE_JBM_FCHANGEL
 * \brief Macro deciding if the function jbm_fchangel() has to be inlined.
 */
#define INLINE_JBM_FCHANGEL							1
/**
 * \def INLINE_JBM_SQR
 * \brief Macro deciding if the function jbm_sqr() has to be inlined.
 */
#define INLINE_JBM_SQR								1
/**
 * \def INLINE_JBM_SQRL
 * \brief Macro deciding if the function jbm_sqrl() has to be inlined.
 */
#define INLINE_JBM_SQRL								1
/**
 * \def INLINE_JBM_SQRLL
 * \brief Macro deciding if the function jbm_sqrll() has to be inlined.
 */
#define INLINE_JBM_SQRLL							1
/**
 * \def INLINE_JBM_FSQR
 * \brief Macro deciding if the function jbm_fsqr() has to be inlined.
 */
#define INLINE_JBM_FSQR								1
/**
 * \def INLINE_JBM_DBL
 * \brief Macro deciding if the function jbm_dbl() has to be inlined.
 */
#define INLINE_JBM_DBL								1
/**
 * \def INLINE_JBM_DBLL
 * \brief Macro deciding if the function jbm_dbll() has to be inlined.
 */
#define INLINE_JBM_DBLL								1
/**
 * \def INLINE_JBM_DBLLL
 * \brief Macro deciding if the function jbm_dblll() has to be inlined.
 */
#define INLINE_JBM_DBLLL							1
/**
 * \def INLINE_JBM_FDBL
 * \brief Macro deciding if the function jbm_fdbl() has to be inlined.
 */
#define INLINE_JBM_FDBL								1
/**
 * \def INLINE_JBM_EXTRAPOLATE
 * \brief Macro deciding if the function jbm_extrapolate() has to be inlined.
 */
#define INLINE_JBM_EXTRAPOLATE						1
/**
 * \def INLINE_JBM_INTERPOLATE
 * \brief Macro deciding if the function jbm_interpolate() has to be inlined.
 */
#define INLINE_JBM_INTERPOLATE						1
/**
 * \def INLINE_JBM_INTEGRAL
 * \brief Macro deciding if the function jbm_integral() has to be inlined.
 */
#define INLINE_JBM_INTEGRAL							1
/**
 * \def INLINE_JBM_FARRAY_SEARCH
 * \brief Macro deciding if the function jbm_farray_search() has to be inlined.
 */
#define INLINE_JBM_FARRAY_SEARCH					1
/**
 * \def INLINE_JBM_FARRAY_SEARCH_EXTENDED
 * \brief Macro deciding if the function jbm_farray_search_extended() has to be
 *   inlined.
 */
#define INLINE_JBM_FARRAY_SEARCH_EXTENDED			1
/**
 * \def INLINE_JBM_FARRAY_MAX
 * \brief Macro deciding if the function jbm_farray_max() has to be inlined.
 */
#define INLINE_JBM_FARRAY_MAX						1
/**
 * \def INLINE_JBM_FARRAY_MIN
 * \brief Macro deciding if the function jbm_farray_min() has to be inlined.
 */
#define INLINE_JBM_FARRAY_MIN						1
/**
 * \def INLINE_JBM_FARRAY_MAXMIN
 * \brief Macro deciding if the function jbm_farray_maxmin() has to be inlined.
 */
#define INLINE_JBM_FARRAY_MAXMIN					1
/**
 * \def INLINE_JBM_FARRAY_INTERPOLATE
 * \brief Macro deciding if the function jbm_farray_interpolate() has to be
 *   inlined.
 */
#define INLINE_JBM_FARRAY_INTERPOLATE				1
/**
 * \def INLINE_JBM_FARRAY_ADD
 * \brief Macro deciding if the function jbm_farray_add() has to be inlined.
 */
#define INLINE_JBM_FARRAY_ADD						1
/**
 * \def INLINE_JBM_FARRAY_INTEGRAL
 * \brief Macro deciding if the function jbm_farray_integral() has to be
 *   inlined.
 */
#define INLINE_JBM_FARRAY_INTEGRAL					1
/**
 * \def INLINE_JBM_FARRAY_MEAN_SQUARE_ERROR
 * \brief Macro deciding if the function jbm_farray_mean_square_error() has to
 *   be inlined.
 */
#define INLINE_JBM_FARRAY_MEAN_SQUARE_ERROR			1
/**
 * \def INLINE_JBM_FARRAY_ROOT_MEAN_SQUARE_ERROR
 * \brief Macro deciding if the function jbm_farray_root_mean_square_error() has
 *   to be inlined.
 */
#define INLINE_JBM_FARRAY_ROOT_MEAN_SQUARE_ERROR	1
/**
 * \def INLINE_JBM_V2_LENGTH
 * \brief Macro deciding if the function jbm_v2_length() has to be inlined.
 */
#define INLINE_JBM_V2_LENGTH						1
/**
 * \def INLINE_JBM_V3_LENGTH
 * \brief Macro deciding if the function jbm_v3_length() has to be inlined.
 */
#define INLINE_JBM_V3_LENGTH						1
/**
 * \def INLINE_JBM_SOLVE_CUADRATIC_REDUCED
 * \brief Macro deciding if the function jbm_solve_cuadratic_reduced() has to be
 *   inlined.
 */
#define INLINE_JBM_SOLVE_CUADRATIC_REDUCED			1
/**
 * \def INLINE_JBM_SOLVE_CUADRATIC
 * \brief Macro deciding if the function jbm_solve_cuadratic() has to be
 *   inlined.
 */
#define INLINE_JBM_SOLVE_CUADRATIC					1
/**
 * \def INLINE_JBM_SOLVE_CUBIC_REDUCED
 * \brief Macro deciding if the function jbm_solve_cubic_reduced() has to be
 *   inlined.
 */
#define INLINE_JBM_SOLVE_CUBIC_REDUCED				1
/**
 * \def INLINE_JBM_SOLVE_CUBIC
 * \brief Macro deciding if the function jbm_solve_cubic() has to be inlined.
 */
#define INLINE_JBM_SOLVE_CUBIC						1
/**
 * \def INLINE_JBM_INDEX_SORT_INSERTION
 * \brief Macro deciding if the function jbm_index_sort_insertion() has to be
 * inlined.
 */
#define INLINE_JBM_INDEX_SORT_INSERTION				1
/**
 * \def INLINE_JBM_INDEX_SORT_INTERCHANGE
 * \brief Macro deciding if the function jbm_index_sort_interchange() has to be
 *   inlined.
 */
#define INLINE_JBM_INDEX_SORT_INTERCHANGE			1
/**
 * \def INLINE_JBM_INDEX_SORT_MERGE
 * \brief Macro deciding if the function jbm_index_sort_merge() has to be
 * inlined.
 */
#define INLINE_JBM_INDEX_SORT_MERGE					1
/**
 * \def INLINE_JBM_INDEX_SORT
 * \brief Macro deciding if the function jbm_index_sort() has to be inlined.
 */
#define INLINE_JBM_INDEX_SORT						1
/**
 * \def INLINE_JBM_INDEX_SORT_EXTENDED
 * \brief Macro deciding if the function jbm_index_sort_extended() has to be
 *   inlined.
 */
#define INLINE_JBM_INDEX_SORT_EXTENDED				1
/**
 * \def INLINE_JBM_MATRIX_SOLVE
 * \brief Macro deciding if the function jbm_matrix_solve() has to be inlined.
 */
#define INLINE_JBM_MATRIX_SOLVE						1
/**
 * \def INLINE_JBM_MATRIX_SOLVE_TRIDIAGONAL
 * \brief Macro deciding if the function jbm_matrix_solve_tridiagonal() has to
 *   be inlined.
 */
#define INLINE_JBM_MATRIX_SOLVE_TRIDIAGONAL			1
/**
 * \def INLINE_JBM_MATRIX_SOLVE_TRIDIAGONAL_ZERO
 * \brief Macro deciding if the function jbm_matrix_solve_tridiagonal_zero() has
 *   to be inlined.
 */
#define INLINE_JBM_MATRIX_SOLVE_TRIDIAGONAL_ZERO	1
/**
 * \def INLINE_JBM_MATRIX_SOLVE_PENTADIAGONAL
 * \brief Macro deciding if the function jbm_matrix_solve_pentadiagonal() has to
 *   be inlined.
 */
#define INLINE_JBM_MATRIX_SOLVE_PENTADIAGONAL		1
/**
 * \def INLINE_JBM_MATRIX_SOLVE_PENTADIAGONAL_ZERO
 * \brief Macro deciding if the function jbm_matrix_solve_pentadiagonal_zero()
 *   has to be inlined.
 */
#define INLINE_JBM_MATRIX_SOLVE_PENTADIAGONAL_ZERO	1
/**
 * \def INLINE_JBM_REGRESSION
 * \brief Macro deciding if the function jbm_regression() has to be inlined.
 */
#define INLINE_JBM_REGRESSION						1
/**
 * \def INLINE_JBM_REGRESSION_LINEAR
 * \brief Macro deciding if the function jbm_regression_linear() has to be
 *   inlined.
 */
#define INLINE_JBM_REGRESSION_LINEAR				1
/**
 * \def INLINE_JBM_REGRESSION_EXPONENTIAL
 * \brief Macro deciding if the function jbm_regression_exponential() has to be
 *   inlined.
 */
#define INLINE_JBM_REGRESSION_EXPONENTIAL			1
/**
 * \def INLINE_JBM_REGRESSION_MULTILINEAR
 * \brief Macro deciding if the function jbm_regression_multilinear() has to be
 *   inlined.
 */
#define INLINE_JBM_REGRESSION_MULTILINEAR			1
/**
 * \def INLINE_JBM_REGRESSION_MULTIEXPONENTIAL
 * \brief Macro deciding if the function jbm_regression_multiexponential() has
 *   to be inlined.
 */
#define INLINE_JBM_REGRESSION_MULTIEXPONENTIAL		1
/**
 * \def INLINE_JBM_SPLINE_CUBIC
 * \brief Macro deciding if the function jbm_spline_cubic() has to be inlined.
 */
#define INLINE_JBM_SPLINE_CUBIC						1
/**
 * \def INLINE_JBM_FLUX_LIMITER_SUPERBEE
 * \brief Macro deciding if the function jbm_flux_limiter_superbee() has to be
 *   inlined.
 */
#define INLINE_JBM_FLUX_LIMITER_SUPERBEE			1
/**
 * \def INLINE_JBM_FLUX_LIMITER_VANLEER
 * \brief Macro deciding if the function jbm_flux_limiter_VanLeer() has to be
 *   inlined.
 */
#define INLINE_JBM_FLUX_LIMITER_VANLEER				1
/**
 * \def INLINE_JBM_FLUX_LIMITER_VANALBADA
 * \brief Macro deciding if the function jbm_flux_limiter_VanAlbada() has to be
 *   inlined.
 */
#define INLINE_JBM_FLUX_LIMITER_VANALBADA			1
/**
 * \def INLINE_JBM_FLUX_LIMITER_MINMOD
 * \brief Macro deciding if the function jbm_flux_limiter_minmod() has to be
 *   inlined.
 */
#define INLINE_JBM_FLUX_LIMITER_MINMOD				1
/**
 * \def INLINE_JBM_FLUX_LIMITER_SUPERMIN
 * \brief Macro deciding if the function jbm_flux_limiter_supermin() has to be
 *   inlined.
 */
#define INLINE_JBM_FLUX_LIMITER_SUPERMIN			1
/**
 * \def INLINE_JBM_FLUX_LIMITER_MINSUPER
 * \brief Macro deciding if the function jbm_flux_limiter_minsuper() has to be
 *   inlined.
 */
#define INLINE_JBM_FLUX_LIMITER_MINSUPER			1
/**
 * \def INLINE_JBM_FLUX_LIMITER_NULL
 * \brief Macro deciding if the function jbm_flux_limiter_null() has to be
 *   inlined.
 */
#define INLINE_JBM_FLUX_LIMITER_NULL				1
/**
 * \def INLINE_JBM_FLUX_LIMITER_CENTRED
 * \brief Macro deciding if the function jbm_flux_limiter_centred() has to be
 *   inlined.
 */
#define INLINE_JBM_FLUX_LIMITER_CENTRED				1
/**
 * \def INLINE_JBM_FLUX_LIMITER_TOTAL
 * \brief Macro deciding if the function jbm_flux_limiter_total() has to be
 *   inlined.
 */
#define INLINE_JBM_FLUX_LIMITER_TOTAL				1
/**
 * \def INLINE_JBM_FLUX_LIMITER_MONOTONIZED_CENTRAL
 * \brief Macro deciding if the function jbm_flux_limiter_monotonized_central()
 *   has to be inlined.
 */
#define INLINE_JBM_FLUX_LIMITER_MONOTONIZED_CENTRAL	1
/**
 * \def INLINE_JBM_FLUX_LIMITER_MEAN
 * \brief Macro deciding if the function jbm_flux_limiter_mean() has to be
 *   inlined.
 */
#define INLINE_JBM_FLUX_LIMITER_MEAN				1
/**
 * \def INLINE_JBM_FLUX_LIMITER_SELECT
 * \brief Macro deciding if the function jbm_flux_limiter_select() has to be
 *   inlined.
 */
#define INLINE_JBM_FLUX_LIMITER_SELECT				1
/**
 * \def INLINE_JBM_TRANSVERSAL_SECTION_REGIONS_SORT
 * \brief Macro deciding if the function
 *   jbm_transversal_section_regions_sort() has to be inlined.
 */
#define INLINE_JBM_TRANSVERSAL_SECTION_REGIONS_SORT	1
/**
 * \def INLINE_JBM_TRANSVERSAL_SECTION_REGIONS
 * \brief Macro deciding if the function jbm_transversal_section_regions()
 *   has to be inlined.
 */
#define INLINE_JBM_TRANSVERSAL_SECTION_REGIONS		1
/**
 * \def INLINE_JBM_VARRAY_SEARCH
 * \brief Macro deciding if the function jbm_varray_search() has to be inlined.
 */
#define INLINE_JBM_VARRAY_SEARCH					1
/**
 * \def INLINE_JBM_VARRAY_SEARCH_EXTENDED
 * \brief Macro deciding if the function jbm_varray_search_extended() has to be
 *   inlined.
 */
#define INLINE_JBM_VARRAY_SEARCH_EXTENDED			1
/**
 * \def INLINE_JBM_VARRAY_MAX
 * \brief Macro deciding if the function jbm_varray_max() has to be inlined.
 */
#define INLINE_JBM_VARRAY_MAX						1
/**
 * \def INLINE_JBM_VARRAY_MIN
 * \brief Macro deciding if the function jbm_varray_min() has to be inlined.
 */
#define INLINE_JBM_VARRAY_MIN						1
/**
 * \def INLINE_JBM_VARRAY_MAXMIN
 * \brief Macro deciding if the function jbm_varray_maxmin() has to be inlined.
 */
#define INLINE_JBM_VARRAY_MAXMIN					1
/**
 * \def INLINE_JBM_VARRAY_MEAN_SQUARE_ERROR
 * \brief Macro deciding if the function jbm_varray_mean_square_error() has to
 *   be inlined.
 */
#define INLINE_JBM_VARRAY_MEAN_SQUARE_ERROR			1
/**
 * \def INLINE_JBM_VARRAY_ROOT_MEAN_SQUARE_ERROR
 * \brief Macro deciding if the function jbm_varray_root_mean_square_error() has
 *   to be inlined.
 */
#define INLINE_JBM_VARRAY_ROOT_MEAN_SQUARE_ERROR	1
/**
 * \def INLINE_JBM_FILE_MEAN_SQUARE_ERROR
 * \brief Macro deciding if the function jbm_file_mean_square_error() has to be
 *   inlined.
 */
#define INLINE_JBM_FILE_MEAN_SQUARE_ERROR			1
/**
 * \def INLINE_JBM_VARRAY_SOLVE_TRIDIAGONAL
 * \brief Macro deciding if the function jbm_varray_solve_tridiagonal() has to
 *   be inlined.
 */
#define INLINE_JBM_VARRAY_SOLVE_TRIDIAGONAL			1
/**
 * \def INLINE_JBM_VARRAY_SOLVE_TRIDIAGONAL_ZERO
 * \brief Macro deciding if the function jbm_varray_solve_tridiagonal_zero() has
 *   to be inlined.
 */
#define INLINE_JBM_VARRAY_SOLVE_TRIDIAGONAL_ZERO	1
/**
 * \def INLINE_JBM_FILE_ROOT_MEAN_SQUARE_ERROR
 * \brief Macro deciding if the function jbm_file_root_mean_square_error() has
 *   to be inlined.
 */
#define INLINE_JBM_FILE_ROOT_MEAN_SQUARE_ERROR		1
/**
 * \def INLINE_JBW_BUTTON_NEW_FROM_STOCK
 * \brief Macro deciding if the function jbw_button_new_from_stock() has to be
 *   inlined.
 */
#define INLINE_JBW_BUTTON_NEW_FROM_STOCK				1
/**
 * \def INLINE_JBW_ARRAY_RADIO_BUTTONS_SET_ACTIVE
 * \brief Macro deciding if the function jbw_array_radio_buttons_set_active()
 *   has to be inlined.
 */
#define INLINE_JBW_ARRAY_RADIO_BUTTONS_SET_ACTIVE		1
/**
 * \def INLINE_JBW_ARRAY_RADIO_BUTTONS_GET_ACTIVE
 * \brief Macro deciding if the function jbw_array_radio_buttons_get_active()
 *   has to be inlined.
 */
#define INLINE_JBW_ARRAY_RADIO_BUTTONS_GET_ACTIVE		1
/**
 * \def INLINE_JBW_INT_ENTRY_SET_VALUE
 * \brief Macro deciding if the function jbw_int_entry_set_value() has to be
 *   inlined.
 */
#define INLINE_JBW_INT_ENTRY_SET_VALUE					1
/**
 * \def INLINE_JBW_INT_ENTRY_SET_VALE_WITH_FORMAT
 * \brief Macro deciding if the function jbw_int_entry_set_vale_with_format()
 *   has to be inlined.
 */
#define INLINE_JBW_INT_ENTRY_SET_VALE_WITH_FORMAT		1
/**
 * \def INLINE_JBW_INT_ENTRY_GET_VALUE
 * \brief Macro deciding if the function jbw_int_entry_get_value() has to be
 *   inlined.
 */
#define INLINE_JBW_INT_ENTRY_GET_VALUE					1
/**
 * \def INLINE_JBW_FLOAT_ENTRY_SET_VALUE
 * \brief Macro deciding if the function jbw_float_entry_set_value() has to be
 *   inlined.
 */
#define INLINE_JBW_FLOAT_ENTRY_SET_VALUE				1
/**
 * \def INLINE_JBW_FLOAT_ENTRY_SET_VALUE_WITH_FORMAT
 * \brief Macro deciding if the function
 *   jbw_float_entry_set_value_with_format() has to be inlined.
 */
#define INLINE_JBW_FLOAT_ENTRY_SET_VALUE_WITH_FORMAT	1
/**
 * \def INLINE_JBW_FLOAT_ENTRY_GET_VALUE
 * \brief Macro deciding if the function jbw_float_entry_get_value() has to be
 *   inlined.
 */
#define INLINE_JBW_FLOAT_ENTRY_GET_VALUE				1
/**
 * \def INLINE_JBW_COMBO_BOX_SET_STRINGS
 * \brief Macro deciding if the function jbw_combo_box_set_strings() has to be
 *   inlined.
 */
#define INLINE_JBW_COMBO_BOX_SET_STRINGS				1
/**
 * \def INLINE_JBW_COMBO_BOX_NEW_WITH_STRINGS
 * \brief Macro deciding if the function jbw_combo_box_new_with_strings() has to
 *   be inlined.
 */
#define INLINE_JBW_COMBO_BOX_NEW_WITH_STRINGS			1
/**
 * \def INLINE_JBW_MENU_ITEM_NEW
 * \brief Macro deciding if the function jbw_menu_item_new() has to be inlined.
 */
#define INLINE_JBW_MENU_ITEM_NEW						1
/**
 * \def INLINE_JBW_SHOW_MESSAGE
 * \brief Macro deciding if the function jbw_show_message() has to be inlined.
 */
#define INLINE_JBW_SHOW_MESSAGE							1
/**
 * \def INLINE_JBW_SHOW_ERROR
 * \brief Macro deciding if the function jbw_show_error() has to be inlined.
 */
#define INLINE_JBW_SHOW_ERROR							0
/**
 * \def INLINE_JBW_SHOW_ERROR2
 * \brief Macro deciding if the function jbw_show_error2() has to be inlined.
 */
#define INLINE_JBW_SHOW_ERROR2							0
/**
 * \def INLINE_JBW_SHOW_ERROR3
 * \brief Macro deciding if the function jbw_show_error3() has to be inlined.
 */
#define INLINE_JBW_SHOW_ERROR3							0
/**
 * \def INLINE_JBW_SHOW_WARNING
 * \brief Macro deciding if the function jbw_show_warning() has to be inlined.
 */
#define INLINE_JBW_SHOW_WARNING							1
/**
 * \def INLINE_JBW_DIALOG_FILE_DESTROY
 * \brief Macro deciding if the function jbw_dialog_file_destroy() has to be
 *   inlined.
 */
#define INLINE_JBW_DIALOG_FILE_DESTROY					1
/**
 * \def INLINE_JBW_DIALOG_FILE_OK
 * \brief Macro deciding if the function jbw_dialog_file_ok() has to be inlined.
 */
#define INLINE_JBW_DIALOG_FILE_OK						1
/**
 * \def INLINE_JBW_DIALOG_FILE
 * \brief Macro deciding if the function jbw_dialog_file() has to be inlined.
 */
#define INLINE_JBW_DIALOG_FILE							1
/**
 * \def INLINE_JBW_DRAW_RECTANGLEF
 * \brief Macro deciding if the function jbw_draw_rectanglef() has to be
 *   inlined.
 */
#define INLINE_JBW_DRAW_RECTANGLEF						1
/**
 * \def INLINE_JBW_DRAW_RECTANGLED
 * \brief Macro deciding if the function jbw_draw_rectangled() has to be
 *   inlined.
 */
#define INLINE_JBW_DRAW_RECTANGLED						1
/**
 * \def INLINE_JBW_DRAW_RECTANGLE
 * \brief Macro deciding if the function jbw_draw_rectangle() has to be inlined.
 */
#define INLINE_JBW_DRAW_RECTANGLE						1
/**
 * \def INLINE_JBW_DRAW_CLEAR
 * \brief Macro deciding if the function jbw_draw_clear() has to be inlined.
 */
#define INLINE_JBW_DRAW_CLEAR							1
/**
 * \def INLINE_JBW_DRAW_LINESF
 * \brief Macro deciding if the function jbw_draw_linesf() has to be inlined.
 */
#define INLINE_JBW_DRAW_LINESF							1
/**
 * \def INLINE_JBW_DRAW_LINESD
 * \brief Macro deciding if the function jbw_draw_linesd() has to be inlined.
 */
#define INLINE_JBW_DRAW_LINESD							1
/**
 * \def INLINE_JBW_DRAW_SEGMENTSF
 * \brief Macro deciding if the function jbw_draw_segmentsf() has to be inlined.
 */
#define INLINE_JBW_DRAW_SEGMENTSF						1
/**
 * \def INLINE_JBW_DRAW_SEGMENTSD
 * \brief Macro deciding if the function jbw_draw_segmentsd() has to be inlined.
 */
#define INLINE_JBW_DRAW_SEGMENTSD						1
/**
 * \def INLINE_JBW_DRAW_LINES
 * \brief Macro deciding if the function jbw_draw_lines() has to be inlined.
 */
#define INLINE_JBW_DRAW_LINES							1
/**
 * \def INLINE_JBW_DRAW_LINESVF
 * \brief Macro deciding if the function jbw_draw_linesvf() has to be inlined.
 */
#define INLINE_JBW_DRAW_LINESVF							0
/**
 * \def INLINE_JBW_DRAW_LINESVD
 * \brief Macro deciding if the function jbw_draw_linesvd() has to be inlined.
 */
#define INLINE_JBW_DRAW_LINESVD							0
/**
 * \def INLINE_JBW_DRAW_LINESV
 * \brief Macro deciding if the function jbw_draw_linesv() has to be inlined.
 */
#define INLINE_JBW_DRAW_LINESV							0
/**
 * \def INLINE_JBW_DRAW_STRING
 * \brief Macro deciding if the function jbw_draw_string() has to be inlined.
 */
#define INLINE_JBW_DRAW_STRING							0
/**
 * \def INLINE_JBW_DRAW_LINE
 * \brief Macro deciding if the function jbw_draw_line() has to be inlined.
 */
#define INLINE_JBW_DRAW_LINE							0
/**
 * \def INLINE_JBW_DRAW_LINEV
 * \brief Macro deciding if the function jbw_draw_linev() has to be inlined.
 */
#define INLINE_JBW_DRAW_LINEV							0
/**
 * \def INLINE_JBW_DRAW_SEGMENT_WITH_LIMITS
 * \brief Macro deciding if the function jbw_draw_segment_with_limits() has to
 *   be inlined.
 */
#define INLINE_JBW_DRAW_SEGMENT_WITH_LIMITS				0
/**
 * \def INLINE_JBW_DRAW_LINE_WITH_LIMITS
 * \brief Macro deciding if the function jbw_draw_line_with_limits() has to be
 *   inlined.
 */
#define INLINE_JBW_DRAW_LINE_WITH_LIMITS				0
/**
 * \def INLINE_JBW_DRAW_LINE_WITH_LIMITSV
 * \brief Macro deciding if the function jbw_draw_line_with_limitsv() has to be
 *   inlined.
 */
#define INLINE_JBW_DRAW_LINE_WITH_LIMITSV				0
/**
 * \def INLINE_JBW_DRAW_LINES_WITH_LIMITS
 * \brief Macro deciding if the function jbw_draw_lines_with_limits() has to be
 *   inlined.
 */
#define INLINE_JBW_DRAW_LINES_WITH_LIMITS				0
/**
 * \def INLINE_JBW_DRAW_LINES_WITH_LIMITSV
 * \brief Macro deciding if the function jbw_draw_lines_with_limitsv() has to be
 *   inlined.
 */
#define INLINE_JBW_DRAW_LINES_WITH_LIMITSV				0
/**
 * \def INLINE_JBW_DRAW_SEGMENT
 * \brief Macro deciding if the function jbw_draw_segment() has to be inlined.
 */
#define INLINE_JBW_DRAW_SEGMENT							0
/**
 * \def INLINE_JBW_DRAW_RANGE
 * \brief Macro deciding if the function jbw_draw_range() has to be inlined.
 */
#define INLINE_JBW_DRAW_RANGE							1
/**
 * \def INLINE_JBW_DRAW_TICS
 * \brief Macro deciding if the function jbw_draw_tics() has to be inlined.
 */
#define INLINE_JBW_DRAW_TICS							1
/**
 * \def INLINE_JBW_LOGO_DESTROY
 * \brief Macro deciding if the function jbw_logo_destroy has to be inlined.
 */
#define INLINE_JBW_LOGO_DESTROY							1
/**
 * \def INLINE_JBW_LOGO_NEW
 * \brief Macro deciding if the function jbw_logo_destroy has to be inlined.
 */
#define INLINE_JBW_LOGO_NEW								1
/**
 * \def INLINE_JBW_GRAPHIC_STRING
 * \brief Macro deciding if the function jbw_graphic_string() has to be inlined.
 */
#define INLINE_JBW_GRAPHIC_STRING						0
/**
 * \def INLINE_JBW_GRAPHIC_SET_GRID
 * \brief Macro deciding if the function jbw_graphic_set_grid() has to be
 *   inlined.
 */
#define INLINE_JBW_GRAPHIC_SET_GRID						1
/**
 * \def INLINE_JBW_GRAPHIC_SET_TITLE
 * \brief Macro deciding if the function jbw_graphic_set_title() has to be
 *   inlined.
 */
#define INLINE_JBW_GRAPHIC_SET_TITLE					0
/**
 * \def INLINE_JBW_GRAPHIC_SET_XLABEL
 * \brief Macro deciding if the function jbw_graphic_set_xlabel() has to be
 *   inlined.
 */
#define INLINE_JBW_GRAPHIC_SET_XLABEL					0
/**
 * \def INLINE_JBW_GRAPHIC_SET_YLABEL
 * \brief Macro deciding if the function jbw_graphic_set_ylabel() has to be
 *   inlined.
 */
#define INLINE_JBW_GRAPHIC_SET_YLABEL					0
/**
 * \def INLINE_JBW_GRAPHIC_SET_YYLABEL
 * \brief Macro deciding if the function jbw_graphic_set_yylabel() has to be
 *   inlined.
 */
#define INLINE_JBW_GRAPHIC_SET_YYLABEL					0
/**
 * \def INLINE_JBW_GRAPHIC_SET_ZLABEL
 * \brief Macro deciding if the function jbw_graphic_set_zlabel() has to be
 *   inlined.
 */
#define INLINE_JBW_GRAPHIC_SET_ZLABEL					0
/**
 * \def INLINE_JBW_GRAPHIC_SET_ZZLABEL
 * \brief Macro deciding if the function jbw_graphic_set_zzlabel() has to be
 *   inlined.
 */
#define INLINE_JBW_GRAPHIC_SET_ZZLABEL					0
/**
 * \def INLINE_JBW_GRAPHIC_SET_LOGO
 * \brief Macro deciding if the function jbw_graphic_set_logo() has to be
 *   inlined.
 */
#define INLINE_JBW_GRAPHIC_SET_LOGO						0
/**
 * \def INLINE_JBW_GRAPHIC_GET_DISPLAY_SIZE
 * \brief Macro deciding if the function jbw_graphic_get_display_size() has to
 *   be inlined.
 */
#define INLINE_JBW_GRAPHIC_GET_DISPLAY_SIZE				0
/**
 * \def INLINE_JBW_GRAPHIC_DRAW_STRING
 * \brief Macro deciding if the function jbw_graphic_draw_string() has to be
 *   inlined.
 */
#define INLINE_JBW_GRAPHIC_DRAW_STRING					0
/**
 * \def INLINE_JBW_GRAPHIC_MAP_RESIZE
 * \brief Macro deciding if the function jbw_graphic_map_resize() has to be
 *   inlined.
 */
#define INLINE_JBW_GRAPHIC_MAP_RESIZE					1
/**
 * \def INLINE_JBW_GRAPHIC_DRAW_RESIZE
 * \brief Macro deciding if the function jbw_graphic_draw_resize() has to be
 *   inlined.
 */
#define INLINE_JBW_GRAPHIC_DRAW_RESIZE					0
/**
 * \def INLINE_JBW_GRAPHIC_LABELS
 * \brief Macro deciding if the function jbw_graphic_labels() has to be inlined.
 */
#define INLINE_JBW_GRAPHIC_LABELS						0
/**
 * \def INLINE_JBW_GRAPHIC_DRAW_LINE
 * \brief Macro deciding if the function jbw_graphic_draw_line() has to be
 *   inlined.
 */
#define INLINE_JBW_GRAPHIC_DRAW_LINE					1
/**
 * \def INLINE_JBW_GRAPHIC_DRAW_LINES
 * \brief Macro deciding if the function jbw_graphic_draw_lines() has to be
 *   inlined.
 */
#define INLINE_JBW_GRAPHIC_DRAW_LINES					1
/**
 * \def INLINE_JBW_GRAPHIC_DRAW_LINESV
 * \brief Macro deciding if the function jbw_graphic_draw_linesv() has to be
 *   inlined.
 */
#define INLINE_JBW_GRAPHIC_DRAW_LINESV					0
/**
 * \def INLINE_JBW_GRAPHIC_DRAW_LOGO
 * \brief Macro deciding if the function jbw_graphic_draw_logo() has to be
 *   inlined.
 */
#define INLINE_JBW_GRAPHIC_DRAW_LOGO					0
/**
 * \def INLINE_JBW_GRAPHIC_REALIZE
 * \brief Macro deciding if the function jbw_graphic_realize() has to be
 *   inlined.
 */
#define INLINE_JBW_GRAPHIC_REALIZE						1
/**
 * \def INLINE_JBW_GRAPHIC_EXPOSE_EVENT
 * \brief Macro deciding if the function jbw_graphic_expose_event() has to be
 *   inlined.
 */
#define INLINE_JBW_GRAPHIC_EXPOSE_EVENT					1
/**
 * \def INLINE_JBW_GRAPHIC_DESTROY
 * \brief Macro deciding if the function jbw_graphic_destroy() has to be
 *   inlined.
 */
#define INLINE_JBW_GRAPHIC_DESTROY						0
/**
 * \def INLINE_JBW_GRAPHIC_NEW
 * \brief Macro deciding if the function jbw_graphic_new() has to be inlined.
 */
#define INLINE_JBW_GRAPHIC_NEW							0
/**
 * \def INLINE_JBW_GRAPHIC_INIT
 * \brief Macro deciding if the function jbw_graphic_new() has to be inlined.
 */
#define INLINE_JBW_GRAPHIC_INIT							1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_SET_ELEMENT
 * \brief Macro deciding if the function jbw_array_editor_set_element() has to
 *   be inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_SET_ELEMENT				1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_GET_ELEMENT
 * \brief Macro deciding if the function jbw_array_editor_get_element() has to
 *   be inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_GET_ELEMENT				1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_SET_ELEMENT_INT
 * \brief Macro deciding if the function jbw_array_editor_set_element_int() has
 *   to be inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_SET_ELEMENT_INT			1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_GET_ELEMENT_INT
 * \brief Macro deciding if the function jbw_array_editor_get_element_int() has
 *   to be inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_GET_ELEMENT_INT			1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_SET_ELEMENT_FLOAT
 * \brief Macro deciding if the function
 *   jbw_array_editor_set_element_float() has to be inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_SET_ELEMENT_FLOAT		1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_GET_ELEMENT_FLOAT
 * \brief Macro deciding if the function
 *   jbw_array_editor_get_element_float() has to be inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_GET_ELEMENT_FLOAT		1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_SET_COLUMN
 * \brief Macro deciding if the function jbw_array_editor_set_column() has to be
 *   inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_SET_COLUMN				1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_GET_COLUMN
 * \brief Macro deciding if the function jbw_array_editor_get_column() has to be
 *   inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_GET_COLUMN				1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_SET_COLUMN_INT
 * \brief Macro deciding if the function jbw_array_editor_set_column_int() has
 *   to be inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_SET_COLUMN_INT			1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_GET_COLUMN_INT
 * \brief Macro deciding if the function jbw_array_editor_get_column_int() has
 *   to be inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_GET_COLUMN_INT			1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_SET_COLUMN_FLOAT
 * \brief Macro deciding if the function jbw_array_editor_set_column_float() has
 *   to be inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_SET_COLUMN_FLOAT		1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_GET_COLUMN_FLOAT
 * \brief Macro deciding if the function jbw_array_editor_get_column_float() has
 *   to be inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_GET_COLUMN_FLOAT		1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_SET_COLUMN_SENSITIVE
 * \brief Macro deciding if the function
 *   jbw_array_editor_set_column_sensitive() has to be inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_SET_COLUMN_SENSITIVE	1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_SHOW_COLUMN
 * \brief Macro deciding if the function jbw_array_editor_show_column() has to
 *   be inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_SHOW_COLUMN				1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_HIDE_COLUMN
 * \brief Macro deciding if the function jbw_array_editor_hide_column() has to
 *   be inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_HIDE_COLUMN				1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_INSERT_BUTTON
 * \brief Macro deciding if the function jbw_array_editor_insert_button() has to
 *   be inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_INSERT_BUTTON			1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_INSERT_ENTRY
 * \brief Macro deciding if the function jbw_array_editor_insert_entry() has to
 *   be inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_INSERT_ENTRY			1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_INSERT
 * \brief Macro deciding if the function jbw_array_editor_insert() has to be
 *   inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_INSERT					1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_UP_ROWS
 * \brief Macro deciding if the function jbw_array_editor_up_rows() has to be
 *   inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_UP_ROWS					1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_INSERT_ROW
 * \brief Macro deciding if the function jbw_array_editor_insert_row() has to be
 *   inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_INSERT_ROW				1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_REMOVE_ENTRY
 * \brief Macro deciding if the function jbw_array_editor_remove_entry() has to
 *   be inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_REMOVE_ENTRY			1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_REMOVE
 * \brief Macro deciding if the function jbw_array_editor_remove() has to be
 *   inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_REMOVE					1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_DOWN_ROWS
 * \brief Macro deciding if the function jbw_array_editor_down_rows() has to be
 *   inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_DOWN_ROWS				1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_REMOVE_ROW
 * \brief Macro deciding if the function jbw_array_editor_remove_row() has to be
 *   inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_REMOVE_ROW				1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_SET_ROWS
 * \brief Macro deciding if the function jbw_array_editor_set_rows() has to be
 *   inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_SET_ROWS				1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_SET_TITLE
 * \brief Macro deciding if the function jbw_array_editor_set_title() has to be
 *   inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_SET_TITLE				1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_DELETE
 * \brief Macro deciding if the function jbw_array_editor_delete() has to be
 *   inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_DELETE					1
/**
 * \def INLINE_JBW_ARRAY_EDITOR_NEW
 * \brief Macro deciding if the function jbw_array_editor_new() has to be
 *   inlined.
 */
#define INLINE_JBW_ARRAY_EDITOR_NEW						1

// These macros decide if the corresponding functions have to be debugged

/**
 * \def DEBUG_JBM_FCOMPARE
 * \brief Macro deciding if the function jbm_fcompare() has to be debugged.
 */
#define DEBUG_JBM_FCOMPARE							0
/**
 * \def DEBUG_JBM_MAX
 * \brief Macro deciding if the function jbm_max() has to be debugged.
 */
#define DEBUG_JBM_MAX								0
/**
 * \def DEBUG_JBM_MIN
 * \brief Macro deciding if the function jbm_min() has to be debugged.
 */
#define DEBUG_JBM_MIN								0
/**
 * \def DEBUG_JBM_MAXL
 * \brief Macro deciding if the function jbm_maxl() has to be debugged.
 */
#define DEBUG_JBM_MAXL								1
/**
 * \def DEBUG_JBM_MINL
 * \brief Macro deciding if the function jbm_minl() has to be debugged.
 */
#define DEBUG_JBM_MINL								1
/**
 * \def DEBUG_JBM_MAXLL
 * \brief Macro deciding if the function jbm_maxll() has to be debugged.
 */
#define DEBUG_JBM_MAXLL								1
/**
 * \def DEBUG_JBM_MINLL
 * \brief Macro deciding if the function jbm_minll() has to be debugged.
 */
#define DEBUG_JBM_MINLL								1
/**
 * \def DEBUG_JBM_FMAX
 * \brief Macro deciding if the function jbm_fmax() has to be debugged.
 */
#define DEBUG_JBM_FMAX								0
/**
 * \def DEBUG_JBM_FMIN
 * \brief Macro deciding if the function jbm_fmin() has to be debugged.
 */
#define DEBUG_JBM_FMIN								0
/**
 * \def DEBUG_JBM_MODMIN
 * \brief Macro deciding if the function jbm_modmin() has to be debugged.
 */
#define DEBUG_JBM_MODMIN							1
/**
 * \def DEBUG_JBM_MODMINL
 * \brief Macro deciding if the function jbm_modminl() has to be debugged.
 */
#define DEBUG_JBM_MODMINL							1
/**
 * \def DEBUG_JBM_MODMINLL
 * \brief Macro deciding if the function jbm_modminll() has to be debugged.
 */
#define DEBUG_JBM_MODMINLL							1
/**
 * \def DEBUG_JBM_FMODMIN
 * \brief Macro deciding if the function jbm_fmodmin() has to be debugged.
 */
#define DEBUG_JBM_FMODMIN							0
/**
 * \def DEBUG_JBM_CHANGE
 * \brief Macro deciding if the function jbm_change() has to be debugged.
 */
#define DEBUG_JBM_CHANGE							0
/**
 * \def DEBUG_JBM_CHANGEL
 * \brief Macro deciding if the function jbm_changel() has to be debugged.
 */
#define DEBUG_JBM_CHANGEL							1
/**
 * \def DEBUG_JBM_CHANGELL
 * \brief Macro deciding if the function jbm_changell() has to be debugged.
 */
#define DEBUG_JBM_CHANGELL							1
/**
 * \def DEBUG_JBM_FCHANGE
 * \brief Macro deciding if the function jbm_fchange() has to be debugged.
 */
#define DEBUG_JBM_FCHANGE							0
/**
 * \def DEBUG_JBM_FCHANGEL
 * \brief Macro deciding if the function jbm_fchangel() has to be debugged.
 */
#define DEBUG_JBM_FCHANGEL							1
/**
 * \def DEBUG_JBM_SQR
 * \brief Macro deciding if the function jbm_sqr() has to be debugged.
 */
#define DEBUG_JBM_SQR								0
/**
 * \def DEBUG_JBM_SQRL
 * \brief Macro deciding if the function jbm_sqrl() has to be debugged.
 */
#define DEBUG_JBM_SQRL								1
/**
 * \def DEBUG_JBM_SQRLL
 * \brief Macro deciding if the function jbm_sqrll() has to be debugged.
 */
#define DEBUG_JBM_SQRLL								1
/**
 * \def DEBUG_JBM_FSQR
 * \brief Macro deciding if the function jbm_fsqr() has to be debugged.
 */
#define DEBUG_JBM_FSQR								0
/**
 * \def DEBUG_JBM_DBL
 * \brief Macro deciding if the function jbm_dbl() has to be debugged.
 */
#define DEBUG_JBM_DBL								1
/**
 * \def DEBUG_JBM_DBLL
 * \brief Macro deciding if the function jbm_dbll() has to be debugged.
 */
#define DEBUG_JBM_DBLL								1
/**
 * \def DEBUG_JBM_DBLLL
 * \brief Macro deciding if the function jbm_dblll() has to be debugged.
 */
#define DEBUG_JBM_DBLLL								1
/**
 * \def DEBUG_JBM_FDBL
 * \brief Macro deciding if the function jbm_fdbl() has to be debugged.
 */
#define DEBUG_JBM_FDBL								0
/**
 * \def DEBUG_JBM_EXTRAPOLATE
 * \brief Macro deciding if the function jbm_extrapolate() has to be debugged.
 */
#define DEBUG_JBM_EXTRAPOLATE						0
/**
 * \def DEBUG_JBM_INTERPOLATE
 * \brief Macro deciding if the function jbm_interpolate() has to be
 *   debugged.
 */
#define DEBUG_JBM_INTERPOLATE						0
/**
 * \def DEBUG_JBM_INTEGRAL
 * \brief Macro deciding if the function jbm_integral() has to be debugged.
 */
#define DEBUG_JBM_INTEGRAL							0
/**
 * \def DEBUG_JBM_FARRAY_SEARCH
 * \brief Macro deciding if the function jbm_farray_search() has to be
 *   debugged.
 */
#define DEBUG_JBM_FARRAY_SEARCH						0
/**
 * \def DEBUG_JBM_FARRAY_SEARCH_EXTENDED
 * \brief Macro deciding if the function jbm_farray_search_extended() has to be
 *   debugged.
 */
#define DEBUG_JBM_FARRAY_SEARCH_EXTENDED			0
/**
 * \def DEBUG_JBM_FARRAY_MAX
 * \brief Macro deciding if the function jbm_farray_max() has to be debugged.
 */
#define DEBUG_JBM_FARRAY_MAX						0
/**
 * \def DEBUG_JBM_FARRAY_MIN
 * \brief Macro deciding if the function jbm_farray_min() has to be debugged.
 */
#define DEBUG_JBM_FARRAY_MIN						0
/**
 * \def DEBUG_JBM_FARRAY_MAXMIN
 * \brief Macro deciding if the function jbm_farray_maxmin() has to be debugged.
 */
#define DEBUG_JBM_FARRAY_MAXMIN						0
/**
 * \def DEBUG_JBM_FARRAY_INTERPOLATE
 * \brief Macro deciding if the function jbm_farray_interpolate() has to be
 *   debugged.
 */
#define DEBUG_JBM_FARRAY_INTERPOLATE				0
/**
 * \def DEBUG_JBM_FARRAY_ADD
 * \brief Macro deciding if the function jbm_farray_add() has to be
 *   debugged.
 */
#define DEBUG_JBM_FARRAY_ADD						1
/**
 * \def DEBUG_JBM_FARRAY_INTEGRAL
 * \brief Macro deciding if the function jbm_farray_integral() has to be
 *   debugged.
 */
#define DEBUG_JBM_FARRAY_INTEGRAL					0
/**
 * \def DEBUG_JBM_FARRAY_MEAN_SQUARE_ERROR
 * \brief Macro deciding if the function jbm_farray_mean_square_error() has to
 *   be debugged.
 */
#define DEBUG_JBM_FARRAY_MEAN_SQUARE_ERROR			0
/**
 * \def DEBUG_JBM_FARRAY_ROOT_MEAN_SQUARE_ERROR
 * \brief Macro deciding if the function jbm_farray_root_mean_square_error() has
 *   to be debugged.
 */
#define DEBUG_JBM_FARRAY_ROOT_MEAN_SQUARE_ERROR		0
/**
 * \def DEBUG_JBM_V2_LENGTH
 * \brief Macro deciding if the function jbm_v2_length() has to be debugged.
 */
#define DEBUG_JBM_V2_LENGTH							1
/**
 * \def DEBUG_JBM_V3_LENGTH
 * \brief Macro deciding if the function jbm_v3_length() has to be debugged.
 */
#define DEBUG_JBM_V3_LENGTH							1
/**
 * \def DEBUG_JBM_SOLVE_CUADRATIC_REDUCED
 * \brief Macro deciding if the function jbm_solve_cuadratic_reduced() has to be
 *   debugged.
 */
#define DEBUG_JBM_SOLVE_CUADRATIC_REDUCED			0
/**
 * \def DEBUG_JBM_SOLVE_CUADRATIC
 * \brief Macro deciding if the function jbm_solve_cuadratic() has to be
 *   debugged.
 */
#define DEBUG_JBM_SOLVE_CUADRATIC					0
/**
 * \def DEBUG_JBM_SOLVE_CUBIC_REDUCED
 * \brief Macro deciding if the function jbm_solve_cubic_reduced() has to be
 *   debugged.
 */
#define DEBUG_JBM_SOLVE_CUBIC_REDUCED				1
/**
 * \def DEBUG_JBM_SOLVE_CUBIC
 * \brief Macro deciding if the function jbm_solve_cubic() has to be debugged.
 */
#define DEBUG_JBM_SOLVE_CUBIC						1
/**
 * \def DEBUG_JBM_INDEX_SORT_INSERTION
 * \brief Macro deciding if the function jbm_index_sort_insertion() has to be
 *   debugged.
 */
#define DEBUG_JBM_INDEX_SORT_INSERTION				0
/**
 * \def DEBUG_JBM_INDEX_SORT_INTERCHANGE
 * \brief Macro deciding if the function jbm_index_sort_interchange() has to be
 *   debugged.
 */
#define DEBUG_JBM_INDEX_SORT_INTERCHANGE			0
/**
 * \def DEBUG_JBM_INDEX_SORT_MERGE
 * \brief Macro deciding if the function jbm_index_sort_merge() has to be
 *   debugged.
 */
#define DEBUG_JBM_INDEX_SORT_MERGE					0
/**
 * \def DEBUG_JBM_INDEX_SORT_FLASH
 * \brief Macro deciding if the function jbm_index_sort_flash() has to be
 *   debugged.
 */
#define DEBUG_JBM_INDEX_SORT_FLASH					0
/**
 * \def DEBUG_JBM_INDEX_SORT
 * \brief Macro deciding if the function jbm_index_sort() has to be
 *   debugged.
 */
#define DEBUG_JBM_INDEX_SORT						0
/**
 * \def DEBUG_JBM_INDEX_SORT_EXTENDED
 * \brief Macro deciding if the function jbm_index_sort_extended() has to
 *   be debugged.
 */
#define DEBUG_JBM_INDEX_SORT_EXTENDED				0
/**
 * \def DEBUG_JBM_MATRIX_SOLVE
 * \brief Macro deciding if the function jbm_matrix_solve() has to be
 *   debugged.
 */
#define DEBUG_JBM_MATRIX_SOLVE						1
/**
 * \def DEBUG_JBM_MATRIX_SOLVE_TRIDIAGONAL
 * \brief Macro deciding if the function jbm_matrix_solve_tridiagonal() has to
 *   be debugged.
 */
#define DEBUG_JBM_MATRIX_SOLVE_TRIDIAGONAL			1
/**
 * \def DEBUG_JBM_MATRIX_SOLVE_TRIDIAGONAL_ZERO
 * \brief Macro deciding if the function jbm_matrix_solve_tridiagonal_zero() has
 *   to be debugged.
 */
#define DEBUG_JBM_MATRIX_SOLVE_TRIDIAGONAL_ZERO		1
/**
 * \def DEBUG_JBM_MATRIX_SOLVE_PENTADIAGONAL
 * \brief Macro deciding if the function jbm_matrix_solve_pentadiagonal() has to
 *   be debugged.
 */
#define DEBUG_JBM_MATRIX_SOLVE_PENTADIAGONAL		1
/**
 * \def DEBUG_JBM_MATRIX_SOLVE_PENTADIAGONAL_ZERO
 * \brief Macro deciding if the function jbm_matrix_solve_pentadiagonal_zero()
 *   has to be debugged.
 */
#define DEBUG_JBM_MATRIX_SOLVE_PENTADIAGONAL_ZERO	1
/**
 * \def DEBUG_JBM_REGRESSION
 * \brief Macro deciding if the function jbm_regression() has to be debugged.
 */
#define DEBUG_JBM_REGRESSION						1
/**
 * \def DEBUG_JBM_REGRESSION_LINEAR
 * \brief Macro deciding if the function jbm_regression_linear() has to be
 *   debugged.
 */
#define DEBUG_JBM_REGRESSION_LINEAR					0
/**
 * \def DEBUG_JBM_REGRESSION_EXPONENTIAL
 * \brief Macro deciding if the function jbm_regression_exponential() has to be
 *   debugged.
 */
#define DEBUG_JBM_REGRESSION_EXPONENTIAL			1
/**
 * \def DEBUG_JBM_REGRESSION_MULTILINEAR
 * \brief Macro deciding if the function jbm_regression_multilinear() has to be
 *   debugged.
 */
#define DEBUG_JBM_REGRESSION_MULTILINEAR			0
/**
 * \def DEBUG_JBM_REGRESSION_MULTIEXPONENTIAL
 * \brief Macro deciding if the function jbm_regression_multiexponential() has
 *   to be debugged.
 */
#define DEBUG_JBM_REGRESSION_MULTIEXPONENTIAL		0
/**
 * \def DEBUG_JBM_SPLINE_CUBIC
 * \brief Macro deciding if the function jbm_spline_cubic() has to be debugged.
 */
#define DEBUG_JBM_SPLINE_CUBIC						1
/**
 * \def DEBUG_JBM_FLUX_LIMITER_SUPERBEE
 * \brief Macro deciding if the function jbm_flux_limiter_superbee() has to be
 *   debugged.
 */
#define DEBUG_JBM_FLUX_LIMITER_SUPERBEE				1
/**
 * \def DEBUG_JBM_FLUX_LIMITER_VANLEER
 * \brief Macro deciding if the function jbm_flux_limiter_VanLeer() has to be
 *   debugged.
 */
#define DEBUG_JBM_FLUX_LIMITER_VANLEER				1
/**
 * \def DEBUG_JBM_FLUX_LIMITER_VANALBADA
 * \brief Macro deciding if the function jbm_flux_limiter_VanAlbada() has to be
 *   debugged.
 */
#define DEBUG_JBM_FLUX_LIMITER_VANALBADA			1
/**
 * \def DEBUG_JBM_FLUX_LIMITER_MINMOD
 * \brief Macro deciding if the function jbm_flux_limiter_minmod() has to be
 *   debugged.
 */
#define DEBUG_JBM_FLUX_LIMITER_MINMOD				1
/**
 * \def DEBUG_JBM_FLUX_LIMITER_SUPERMIN
 * \brief Macro deciding if the function jbm_flux_limiter_supermin() has to be
 *   debugged.
 */
#define DEBUG_JBM_FLUX_LIMITER_SUPERMIN				1
/**
 * \def DEBUG_JBM_FLUX_LIMITER_MINSUPER
 * \brief Macro deciding if the function jbm_flux_limiter_minsuper() has to be
 *   debugged.
 */
#define DEBUG_JBM_FLUX_LIMITER_MINSUPER				1
/**
 * \def DEBUG_JBM_FLUX_LIMITER_NULL
 * \brief Macro deciding if the function jbm_flux_limiter_null() has to be
 *   debugged.
 */
#define DEBUG_JBM_FLUX_LIMITER_NULL					1
/**
 * \def DEBUG_JBM_FLUX_LIMITER_CENTRED
 * \brief Macro deciding if the function jbm_flux_limiter_centred() has to be
 *   debugged.
 */
#define DEBUG_JBM_FLUX_LIMITER_CENTRED				1
/**
 * \def DEBUG_JBM_FLUX_LIMITER_TOTAL
 * \brief Macro deciding if the function jbm_flux_limiter_total() has to be
 *   debugged.
 */
#define DEBUG_JBM_FLUX_LIMITER_TOTAL				1
/**
 * \def DEBUG_JBM_FLUX_LIMITER_MONOTONIZED_CENTRAL
 * \brief Macro deciding if the function jbm_flux_limiter_monotonized_central()
 *   has to be debugged.
 */
#define DEBUG_JBM_FLUX_LIMITER_MONOTONIZED_CENTRAL	1
/**
 * \def DEBUG_JBM_FLUX_LIMITER_MEAN
 * \brief Macro deciding if the function jbm_flux_limiter_mean() has to be
 *   debugged.
 */
#define DEBUG_JBM_FLUX_LIMITER_MEAN					1
/**
 * \def DEBUG_JBM_FLUX_LIMITER_SELECT
 * \brief Macro deciding if the function jbm_flux_limiter_select() has to be
 *   debugged.
 */
#define DEBUG_JBM_FLUX_LIMITER_SELECT				1
/**
 * \def DEBUG_JBM_TRANSVERSAL_SECTION_REGIONS_SORT
 * \brief Macro deciding if the function jbm_transversal_section_regions_sort()
 *   has to be debugged.
 */
#define DEBUG_JBM_TRANSVERSAL_SECTION_REGIONS_SORT	0
/**
 * \def DEBUG_JBM_TRANSVERSAL_SECTION_REGIONS
 * \brief Macro deciding if the function jbm_transversal_section_regions() has
 *   to be debugged.
 */
#define DEBUG_JBM_TRANSVERSAL_SECTION_REGIONS		0
/**
 * \def DEBUG_JBM_VARRAY_SEARCH
 * \brief Macro deciding if the function jbm_varray_search() has to be
 *   debugged.
 */
#define DEBUG_JBM_VARRAY_SEARCH						0
/**
 * \def DEBUG_JBM_VARRAY_SEARCH_EXTENDED
 * \brief Macro deciding if the function jbm_varray_search_extended() has to
 *   be debugged.
 */
#define DEBUG_JBM_VARRAY_SEARCH_EXTENDED			0
/**
 * \def DEBUG_JBM_VARRAY_MAX
 * \brief Macro deciding if the function jbm_varray_max() has to be debugged.
 */
#define DEBUG_JBM_VARRAY_MAX						0
/**
 * \def DEBUG_JBM_VARRAY_MIN
 * \brief Macro deciding if the function jbm_varray_min() has to be debugged.
 */
#define DEBUG_JBM_VARRAY_MIN						0
/**
 * \def DEBUG_JBM_VARRAY_MAXMIN
 * \brief Macro deciding if the function jbm_varray_maxmin() has to be debugged.
 */
#define DEBUG_JBM_VARRAY_MAXMIN						0
/**
 * \def DEBUG_JBM_VARRAY_MEAN_SQUARE_ERROR
 * \brief Macro deciding if the function jbm_varray_mean_square_error() has to
 *   be debugged.
 */
#define DEBUG_JBM_VARRAY_MEAN_SQUARE_ERROR			0
/**
 * \def DEBUG_JBM_VARRAY_ROOT_MEAN_SQUARE_ERROR
 * \brief Macro deciding if the function jbm_varray_root_mean_square_error() has
 *   to be debugged.
 */
#define DEBUG_JBM_VARRAY_ROOT_MEAN_SQUARE_ERROR		0
/**
 * \def DEBUG_JBM_VARRAY_SOLVE_TRIDIAGONAL
 * \brief Macro deciding if the function jbm_varray_solve_tridiagonal() has to
 *   be debugged.
 */
#define DEBUG_JBM_VARRAY_SOLVE_TRIDIAGONAL			1
/**
 * \def DEBUG_JBM_VARRAY_SOLVE_TRIDIAGONAL_ZERO
 * \brief Macro deciding if the function jbm_varray_solve_tridiagonal_zero() has
 *   to be debugged.
 */
#define DEBUG_JBM_VARRAY_SOLVE_TRIDIAGONAL_ZERO		1
/**
 * \def DEBUG_JBM_FILE_MEAN_SQUARE_ERROR
 * \brief Macro deciding if the function jbm_file_mean_square_error() has to be
 *   debugged.
 */
#define DEBUG_JBM_FILE_MEAN_SQUARE_ERROR			0
/**
 * \def DEBUG_JBM_FILE_ROOT_MEAN_SQUARE_ERROR
 * \brief Macro deciding if the function jbm_file_root_mean_square_error() has
 *   to be debugged.
 */
#define DEBUG_JBM_FILE_ROOT_MEAN_SQUARE_ERROR		0

#endif
