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

#define JB_PRECISION 3          ///< Definition of the accuracy.
#define JB_DEBUG_FILE 0
  ///< Define if the debug information is displayed in a terminal (0) or in a
  ///< file (1).
#define JB_BUFFER_SIZE 512      ///< Size of string buffers.
#define FRS "%512s"             ///< Format of the string buffer input.

#define JBM_INTEGRAL_GAUSS_N 4  ///< Method of gaussian integral.

#define JBW_GRAPHIC_N_LABELS 6  ///< Number of maximum labels in a JBWGraphic.
#define JBW_GRAPHIC_N_CHARS 12  ///< Number of characters displayed in a
                                ///< graphical label.
#define JBW_GRAPHIC_FONT "courier 10"
  ///< Font displayed in a graphical label.

// These macros decide if the corresponding functions have to be compiled

#define JB_FREE_NULL 1
  ///< Macro deciding if the function jb_free_null() has to be compiled.
#define JB_FUNCTION_NULL 1
  ///< Macro deciding if the function jb_function_null() has to be compiled.
#define JB_REALLOC 1
  ///< Macro deciding if the function jb_realloc() has to be compiled.
#define JB_TRY_REALLOC 1
  ///< Macro deciding if the function jb_try_realloc() has to be compiled.
#define JB_STRDUP 1
  ///< Macro deciding if the function jb_strdup() has to be compiled.
#define JB_SLIST_FREE 1
  ///< Macro deciding if the function jb_slist_free() has to be compiled.
#define JBM_INDEX_SORT_FLASH 1  ///< Macro deciding if the function
                                ///< jb_index_sort_flash() has to be compiled.
#define JB_XML_NODE_GET_FLOAT 1 ///< Macro deciding if the function
                                ///< jb_xml_node_get_float() has to be compiled.
#define JB_XML_NODE_SET_FLOAT 1 ///< Macro deciding if the function
                                ///< jb_xml_node_set_float() has to be compiled.
#define JB_XML_NODE_GET_INT 1   ///< Macro deciding if the function
                                ///< jb_xml_node_get_int() has to be compiled.
#define JB_XML_NODE_SET_INT 1   ///< Macro deciding if the function
                                ///< jb_xml_node_set_int() has to be compiled.
#define JB_XML_NODE_GET_TIME 1  ///< Macro deciding if the function
                                ///< jb_xml_node_get_time() has to be compiled.
#define JB_XML_NODE_SET_TIME 1  ///< Macro deciding if the function
                                ///< jb_xml_node_set_time() has to be compiled.
#define JB_XML_NODE_GET_FLOAT_WITH_DEFAULT 1
  ///< Macro deciding if the function jb_xml_node_get_float_with_default()
  ///< has to be compiled.
#define JB_XML_NODE_SET_FLOAT_WITH_DEFAULT 1
  ///< Macro deciding if the function jb_xml_node_set_float_with_default()
  ///< has to be compiled.
#define JB_XML_NODE_GET_INT_WITH_DEFAULT 1
  ///< Macro deciding if the function jb_xml_node_get_int_with_default()
  ///< has to be compiled.
#define JB_XML_NODE_SET_INT_WITH_DEFAULT 1
  ///< Macro deciding if the function jb_xml_node_set_int_with_default()
  ///< has to be compiled.
#define JB_XML_NODE_GET_TIME_WITH_DEFAULT 1
  ///< Macro deciding if the function jb_xml_node_get_time_with_default()
  ///< has to be compiled.
#define JB_XML_NODE_SET_TIME_WITH_DEFAULT 1
  ///< Macro deciding if the function jb_xml_node_set_time_with_default()
  ///< has to be compiled.
#define JB_XML_NODE_GET_CONTENT_FILE 1
  ///< Macro deciding if the function jb_xml_node_get_content_file() has to
  ///< be compiled.
#define JB_XML_NODE_SET_CONTENT_FILE 1
  ///< Macro deciding if the function jb_xml_node_set_content_file() has to
  ///< be compiled.

// These macros decide if the corresponding functions have to be inline

#define INLINE_JB_CHANGE		1
  ///< Macro deciding if the function JBChange() has to be inlined.
#define INLINE_JB_FLENGTH		1
  ///< Macro deciding if the function jb_flength() has to be inlined.
#define INLINE_JB_MAKE_TIME		0
  ///< Macro deciding if the function jb_make_time() has to be inlined.
#define INLINE_JB_GET_TIME		0
  ///< Macro deciding if the function jb_get_time() has to be inlined.
#define INLINE_JB_GET_TIME_FILE	0
  ///< Macro deciding if the function jb_get_time_file() has to be inlined.
#define INLINE_JB_SET_TIME		0
  ///< Macro deciding if the function jb_set_time() has to be inlined.
#define INLINE_JBM_FCOMPARE							1
  ///< Macro deciding if the function jbm_fcompare() has to be inlined.
#define INLINE_JBM_MAX								1
  ///< Macro deciding if the function jbm_max() has to be inlined.
#define INLINE_JBM_MIN								1
  ///< Macro deciding if the function jbm_min() has to be inlined.
#define INLINE_JBM_MAXL								1
  ///< Macro deciding if the function jbm_maxl() has to be inlined.
#define INLINE_JBM_MINL								1
  ///< Macro deciding if the function jbm_minl() has to be inlined.
#define INLINE_JBM_MAXLL							1
  ///< Macro deciding if the function jbm_maxll() has to be inlined.
#define INLINE_JBM_MINLL							1
  ///< Macro deciding if the function jbm_minll() has to be inlined.
#define INLINE_JBM_MODMIN							1
  ///< Macro deciding if the function jbm_modmin() has to be inlined.
#define INLINE_JBM_MODMINL							1
  ///< Macro deciding if the function jbm_modminl() has to be inlined.
#define INLINE_JBM_MODMINLL							1
  ///< Macro deciding if the function jbm_modminll() has to be inlined.
#define INLINE_JBM_FMODMIN							1
  ///< Macro deciding if the function jbm_fmodmin() has to be inlined.
#define INLINE_JBM_CHANGE							1
  ///< Macro deciding if the function jbm_change() has to be inlined.
#define INLINE_JBM_CHANGEL							1
  ///< Macro deciding if the function jbm_changel() has to be inlined.
#define INLINE_JBM_CHANGELL							1
  ///< Macro deciding if the function jbm_changell() has to be inlined.
#define INLINE_JBM_FCHANGE							1
  ///< Macro deciding if the function jbm_fchange() has to be inlined.
#define INLINE_JBM_FCHANGEL							1
  ///< Macro deciding if the function jbm_fchangel() has to be inlined.
#define INLINE_JBM_SQR								1
  ///< Macro deciding if the function jbm_sqr() has to be inlined.
#define INLINE_JBM_SQRL								1
  ///< Macro deciding if the function jbm_sqrl() has to be inlined.
#define INLINE_JBM_SQRLL							1
  ///< Macro deciding if the function jbm_sqrll() has to be inlined.
#define INLINE_JBM_FSQR								1
  ///< Macro deciding if the function jbm_fsqr() has to be inlined.
#define INLINE_JBM_DBL								1
  ///< Macro deciding if the function jbm_dbl() has to be inlined.
#define INLINE_JBM_DBLL								1
  ///< Macro deciding if the function jbm_dbll() has to be inlined.
#define INLINE_JBM_DBLLL							1
  ///< Macro deciding if the function jbm_dblll() has to be inlined.
#define INLINE_JBM_FDBL								1
  ///< Macro deciding if the function jbm_fdbl() has to be inlined.
#define INLINE_JBM_EXTRAPOLATE						1
  ///< Macro deciding if the function jbm_extrapolate() has to be inlined.
#define INLINE_JBM_INTERPOLATE						1
  ///< Macro deciding if the function jbm_interpolate() has to be inlined.
#define INLINE_JBM_INTEGRAL							1
  ///< Macro deciding if the function jbm_integral() has to be inlined.
#define INLINE_JBM_FARRAY_SEARCH					1
  ///< Macro deciding if the function jbm_farray_search() has to be inlined.
#define INLINE_JBM_FARRAY_SEARCH_EXTENDED			1
  ///< Macro deciding if the function jbm_farray_search_extended() has to be
  ///< inlined.
#define INLINE_JBM_FARRAY_MAX						1
  ///< Macro deciding if the function jbm_farray_max() has to be inlined.
#define INLINE_JBM_FARRAY_MIN						1
  ///< Macro deciding if the function jbm_farray_min() has to be inlined.
#define INLINE_JBM_FARRAY_MAXMIN					1
  ///< Macro deciding if the function jbm_farray_maxmin() has to be inlined.
#define INLINE_JBM_FARRAY_INTERPOLATE				1
  ///< Macro deciding if the function jbm_farray_interpolate() has to be
  ///< inlined.
#define INLINE_JBM_FARRAY_ADD						1
  ///< Macro deciding if the function jbm_farray_add() has to be inlined.
#define INLINE_JBM_FARRAY_INTEGRAL					1
  ///< Macro deciding if the function jbm_farray_integral() has to be
  ///< inlined.
#define INLINE_JBM_FARRAY_MEAN_SQUARE_ERROR			1
  ///< Macro deciding if the function jbm_farray_mean_square_error() has to
  ///< be inlined.
#define INLINE_JBM_FARRAY_ROOT_MEAN_SQUARE_ERROR	1
  ///< Macro deciding if the function jbm_farray_root_mean_square_error() has
  ///< to be inlined.
#define INLINE_JBM_DARRAY_SEARCH					1
  ///< Macro deciding if the function jbm_darray_search() has to be inlined.
#define INLINE_JBM_DARRAY_SEARCH_EXTENDED			1
  ///< Macro deciding if the function jbm_darray_search_extended() has to be
  ///< inlined.
#define INLINE_JBM_DARRAY_MAX						1
  ///< Macro deciding if the function jbm_darray_max() has to be inlined.
#define INLINE_JBM_DARRAY_MIN						1
  ///< Macro deciding if the function jbm_darray_min() has to be inlined.
#define INLINE_JBM_DARRAY_MAXMIN					1
  ///< Macro deciding if the function jbm_darray_maxmin() has to be inlined.
#define INLINE_JBM_DARRAY_FARRAY_INTERPOLATE		1
  ///< Macro deciding if the function jbm_darray_farray_interpolate() has to
  ///< be inlined.
#define INLINE_JBM_DARRAY_INTERPOLATE				1
  ///< Macro deciding if the function jbm_darray_interpolate() has to be
  ///< inlined.
#define INLINE_JBM_DARRAY_ADD						1
  ///< Macro deciding if the function jbm_darray_add() has to be inlined.
#define INLINE_JBM_DARRAY_FARRAY_INTEGRAL			1
  ///< Macro deciding if the function jbm_darray_farray_integral() has to be
  ///< inlined.
#define INLINE_JBM_DARRAY_INTEGRAL					1
  ///< Macro deciding if the function jbm_darray_integral() has to be
  ///< inlined.
#define INLINE_JBM_DARRAY_MEAN_SQUARE_ERROR			1
  ///< Macro deciding if the function jbm_darray_mean_square_error() has to
  ///< be inlined.
#define INLINE_JBM_DARRAY_ROOT_MEAN_SQUARE_ERROR	1
  ///< Macro deciding if the function jbm_darray_root_mean_square_error() has
  ///< to be inlined.
#define INLINE_JBM_V2_LENGTH						1
  ///< Macro deciding if the function jbm_v2_length() has to be inlined.
#define INLINE_JBM_V3_LENGTH						1
  ///< Macro deciding if the function jbm_v3_length() has to be inlined.
#define INLINE_JBM_SOLVE_CUADRATIC_REDUCED			1
  ///< Macro deciding if the function jbm_solve_cuadratic_reduced() has to be
  ///< inlined.
#define INLINE_JBM_SOLVE_CUADRATIC					1
  ///< Macro deciding if the function jbm_solve_cuadratic() has to be
  ///< inlined.
#define INLINE_JBM_SOLVE_CUBIC_REDUCED				1
  ///< Macro deciding if the function jbm_solve_cubic_reduced() has to be
  ///< inlined.
#define INLINE_JBM_SOLVE_CUBIC						1
  ///< Macro deciding if the function jbm_solve_cubic() has to be inlined.
#define INLINE_JBM_INDEX_SORT_INSERTION				1
  ///< Macro deciding if the function jbm_index_sort_insertion() has to be
  ///< inlined.
#define INLINE_JBM_INDEX_SORT_INTERCHANGE			1
  ///< Macro deciding if the function jbm_index_sort_interchange() has to be
  ///< inlined.
#define INLINE_JBM_INDEX_SORT_MERGE					1
  ///< Macro deciding if the function jbm_index_sort_merge() has to be
  ///< inlined.
#define INLINE_JBM_INDEX_SORT						1
  ///< Macro deciding if the function jbm_index_sort() has to be inlined.
#define INLINE_JBM_INDEX_SORT_EXTENDED				1
  ///< Macro deciding if the function jbm_index_sort_extended() has to be
  ///< inlined.
#define INLINE_JBM_MATRIX_SOLVE						1
  ///< Macro deciding if the function jbm_matrix_solve() has to be inlined.
#define INLINE_JBM_MATRIX_SOLVE_TRIDIAGONAL			1
  ///< Macro deciding if the function jbm_matrix_solve_tridiagonal() has to
  ///< be inlined.
#define INLINE_JBM_MATRIX_SOLVE_TRIDIAGONAL_ZERO	1
  ///< Macro deciding if the function jbm_matrix_solve_tridiagonal_zero() has
  ///< to be inlined.
#define INLINE_JBM_MATRIX_SOLVE_PENTADIAGONAL		1
  ///< Macro deciding if the function jbm_matrix_solve_pentadiagonal() has to
  ///< be inlined.
#define INLINE_JBM_MATRIX_SOLVE_PENTADIAGONAL_ZERO	1
  ///< Macro deciding if the function jbm_matrix_solve_pentadiagonal_zero()
  ///< has to be inlined.
#define INLINE_JBM_REGRESSION						1
  ///< Macro deciding if the function jbm_regression() has to be inlined.
#define INLINE_JBM_REGRESSION_LINEAR				1
  ///< Macro deciding if the function jbm_regression_linear() has to be inlined.
#define INLINE_JBM_REGRESSION_EXPONENTIAL			1
  ///< Macro deciding if the function jbm_regression_exponential() has to be
  ///< inlined.
#define INLINE_JBM_REGRESSION_MULTILINEAR			1
  ///< Macro deciding if the function jbm_regression_multilinear() has to be
  ///< inlined.
#define INLINE_JBM_REGRESSION_MULTIEXPONENTIAL		1
  ///< Macro deciding if the function jbm_regression_multiexponential() has
  ///< to be inlined.
#define INLINE_JBM_SPLINE_CUBIC						1
  ///< Macro deciding if the function jbm_spline_cubic() has to be inlined.
#define INLINE_JBM_FLUX_LIMITER_SUPERBEE			1
  ///< Macro deciding if the function jbm_flux_limiter_superbee() has to be
  ///< inlined.
#define INLINE_JBM_FLUX_LIMITER_VANLEER				1
  ///< Macro deciding if the function jbm_flux_limiter_VanLeer() has to be
  ///< inlined.
#define INLINE_JBM_FLUX_LIMITER_VANALBADA			1
  ///< Macro deciding if the function jbm_flux_limiter_VanAlbada() has to be
  ///< inlined.
#define INLINE_JBM_FLUX_LIMITER_MINMOD				1
  ///< Macro deciding if the function jbm_flux_limiter_minmod() has to be
  ///< inlined.
#define INLINE_JBM_FLUX_LIMITER_SUPERMIN			1
  ///< Macro deciding if the function jbm_flux_limiter_supermin() has to be
  ///< inlined.
#define INLINE_JBM_FLUX_LIMITER_MINSUPER			1
  ///< Macro deciding if the function jbm_flux_limiter_minsuper() has to be
  ///< inlined.
#define INLINE_JBM_FLUX_LIMITER_NULL				1
  ///< Macro deciding if the function jbm_flux_limiter_null() has to be
  ///< inlined.
#define INLINE_JBM_FLUX_LIMITER_CENTRED				1
  ///< Macro deciding if the function jbm_flux_limiter_centred() has to be
  ///< inlined.
#define INLINE_JBM_FLUX_LIMITER_TOTAL				1
  ///< Macro deciding if the function jbm_flux_limiter_total() has to be
  ///< inlined.
#define INLINE_JBM_FLUX_LIMITER_MONOTONIZED_CENTRAL	1
  ///< Macro deciding if the function jbm_flux_limiter_monotonized_central()
  ///< has to be inlined.
#define INLINE_JBM_FLUX_LIMITER_MEAN				1
  ///< Macro deciding if the function jbm_flux_limiter_mean() has to be
  ///< inlined.
#define INLINE_JBM_FLUX_LIMITER_SELECT				1
  ///< Macro deciding if the function jbm_flux_limiter_select() has to be
  ///< inlined.
#define INLINE_JBM_TRANSVERSAL_SECTION_REGIONS_SORT	1
  ///< Macro deciding if the function
  ///< jbm_transversal_section_regions_sort() has to be inlined.
#define INLINE_JBM_TRANSVERSAL_SECTION_REGIONS		1
  ///< Macro deciding if the function jbm_transversal_section_regions()
  ///< has to be inlined.
#define INLINE_JBM_VARRAY_SEARCH					1
  ///< Macro deciding if the function jbm_varray_search() has to be inlined.
#define INLINE_JBM_VARRAY_SEARCH_EXTENDED			1
  ///< Macro deciding if the function jbm_varray_search_extended() has to be
  ///< inlined.
#define INLINE_JBM_VARRAY_MAX						1
  ///< Macro deciding if the function jbm_varray_max() has to be inlined.
#define INLINE_JBM_VARRAY_MIN						1
  ///< Macro deciding if the function jbm_varray_min() has to be inlined.
#define INLINE_JBM_VARRAY_MAXMIN					1
  ///< Macro deciding if the function jbm_varray_maxmin() has to be inlined.
#define INLINE_JBM_VARRAY_MEAN_SQUARE_ERROR			1
  ///< Macro deciding if the function jbm_varray_mean_square_error() has to
  ///< be inlined.
#define INLINE_JBM_VARRAY_ROOT_MEAN_SQUARE_ERROR	1
  ///< Macro deciding if the function jbm_varray_root_mean_square_error() has
  ///< to be inlined.
#define INLINE_JBM_VARRAY_SOLVE_TRIDIAGONAL			1
  ///< Macro deciding if the function jbm_varray_solve_tridiagonal() has to
  ///< be inlined.
#define INLINE_JBM_VARRAY_SOLVE_TRIDIAGONAL_ZERO	1
  ///< Macro deciding if the function jbm_varray_solve_tridiagonal_zero() has
  ///< to be inlined.
#define INLINE_JBM_VDARRAY_SEARCH					1
  ///< Macro deciding if the function jbm_vdarray_search() has to be inlined.
#define INLINE_JBM_VDARRAY_SEARCH_EXTENDED			1
  ///< Macro deciding if the function jbm_vdarray_search_extended() has to be
  ///< inlined.
#define INLINE_JBM_VDARRAY_MAX						1
  ///< Macro deciding if the function jbm_vdarray_max() has to be inlined.
#define INLINE_JBM_VDARRAY_MIN						1
  ///< Macro deciding if the function jbm_vdarray_min() has to be inlined.
#define INLINE_JBM_VDARRAY_MAXMIN					1
  ///< Macro deciding if the function jbm_vdarray_maxmin() has to be inlined.
#define INLINE_JBM_VDARRAY_MEAN_SQUARE_ERROR		1
  ///< Macro deciding if the function jbm_vdarray_mean_square_error() has to
  ///< be inlined.
#define INLINE_JBM_VDARRAY_ROOT_MEAN_SQUARE_ERROR	1
  ///< Macro deciding if the function jbm_vdarray_root_mean_square_error()
  ///< has to be inlined.
#define INLINE_JBM_VDARRAY_SOLVE_TRIDIAGONAL		1
  ///< Macro deciding if the function jbm_vdarray_solve_tridiagonal() has to
  ///< be inlined.
#define INLINE_JBM_VDARRAY_SOLVE_TRIDIAGONAL_ZERO	1
  ///< Macro deciding if the function jbm_vdarray_solve_tridiagonal_zero()
  ///< has to be inlined.
#define INLINE_JBM_FILE_MEAN_SQUARE_ERROR			1
  ///< Macro deciding if the function jbm_file_mean_square_error() has to be
  ///< inlined.
#define INLINE_JBM_FILE_ROOT_MEAN_SQUARE_ERROR		1
  ///< Macro deciding if the function jbm_file_root_mean_square_error() has
  ///< to be inlined.
#define INLINE_JBW_BUTTON_NEW_FROM_STOCK				1
  ///< Macro deciding if the function jbw_button_new_from_stock() has to be
  ///< inlined.
#define INLINE_JBW_ARRAY_RADIO_BUTTONS_SET_ACTIVE		1
  ///< Macro deciding if the function jbw_array_radio_buttons_set_active()
  ///< has to be inlined.
#define INLINE_JBW_ARRAY_RADIO_BUTTONS_GET_ACTIVE		1
  ///< Macro deciding if the function jbw_array_radio_buttons_get_active()
  ///< has to be inlined.
#define INLINE_JBW_INT_ENTRY_SET_VALUE					1
  ///< Macro deciding if the function jbw_int_entry_set_value() has to be
  ///< inlined.
#define INLINE_JBW_INT_ENTRY_SET_VALE_WITH_FORMAT		1
  ///< Macro deciding if the function jbw_int_entry_set_vale_with_format()
  ///< has to be inlined.
#define INLINE_JBW_INT_ENTRY_GET_VALUE					1
  ///< Macro deciding if the function jbw_int_entry_get_value() has to be
  ///< inlined.
#define INLINE_JBW_FLOAT_ENTRY_SET_VALUE				1
  ///< Macro deciding if the function jbw_float_entry_set_value() has to be
  ///< inlined.
#define INLINE_JBW_FLOAT_ENTRY_SET_VALUE_WITH_FORMAT	1
  ///< Macro deciding if the function
  ///< jbw_float_entry_set_value_with_format() has to be inlined.
#define INLINE_JBW_FLOAT_ENTRY_GET_VALUE				1
  ///< Macro deciding if the function jbw_float_entry_get_value() has to be
  ///< inlined.
#define INLINE_JBW_COMBO_BOX_SET_STRINGS				1
  ///< Macro deciding if the function jbw_combo_box_set_strings() has to be
  ///< inlined.
#define INLINE_JBW_COMBO_BOX_NEW_WITH_STRINGS			1
  ///< Macro deciding if the function jbw_combo_box_new_with_strings() has to
  ///< be inlined.
#define INLINE_JBW_MENU_ITEM_NEW						1
  ///< Macro deciding if the function jbw_menu_item_new() has to be inlined.
#define INLINE_JBW_SHOW_MESSAGE							1
  ///< Macro deciding if the function jbw_show_message() has to be inlined.
#define INLINE_JBW_SHOW_ERROR							0
  ///< Macro deciding if the function jbw_show_error() has to be inlined.
#define INLINE_JBW_SHOW_ERROR2							0
  ///< Macro deciding if the function jbw_show_error2() has to be inlined.
#define INLINE_JBW_SHOW_ERROR3							0
  ///< Macro deciding if the function jbw_show_error3() has to be inlined.
#define INLINE_JBW_SHOW_WARNING							1
  ///< Macro deciding if the function jbw_show_warning() has to be inlined.
#define INLINE_JBW_DIALOG_FILE_DESTROY					1
  ///< Macro deciding if the function jbw_dialog_file_destroy() has to be
  ///< inlined.
#define INLINE_JBW_DIALOG_FILE_OK						1
  ///< Macro deciding if the function jbw_dialog_file_ok() has to be inlined.
#define INLINE_JBW_DIALOG_FILE							1
  ///< Macro deciding if the function jbw_dialog_file() has to be inlined.
#define INLINE_JBW_DRAW_RECTANGLEF						1
  ///< Macro deciding if the function jbw_draw_rectanglef() has to be
  ///< inlined.
#define INLINE_JBW_DRAW_RECTANGLED						1
  ///< Macro deciding if the function jbw_draw_rectangled() has to be
  ///< inlined.
#define INLINE_JBW_DRAW_RECTANGLE						1
  ///< Macro deciding if the function jbw_draw_rectangle() has to be inlined.
#define INLINE_JBW_DRAW_CLEAR							1
  ///< Macro deciding if the function jbw_draw_clear() has to be inlined.
#define INLINE_JBW_DRAW_LINESF							1
  ///< Macro deciding if the function jbw_draw_linesf() has to be inlined.
#define INLINE_JBW_DRAW_LINESD							1
  ///< Macro deciding if the function jbw_draw_linesd() has to be inlined.
#define INLINE_JBW_DRAW_SEGMENTSF						1
  ///< Macro deciding if the function jbw_draw_segmentsf() has to be inlined.
#define INLINE_JBW_DRAW_SEGMENTSD						1
  ///< Macro deciding if the function jbw_draw_segmentsd() has to be inlined.
#define INLINE_JBW_DRAW_LINES							1
  ///< Macro deciding if the function jbw_draw_lines() has to be inlined.
#define INLINE_JBW_DRAW_LINESVF							0
  ///< Macro deciding if the function jbw_draw_linesvf() has to be inlined.
#define INLINE_JBW_DRAW_LINESVD							0
  ///< Macro deciding if the function jbw_draw_linesvd() has to be inlined.
#define INLINE_JBW_DRAW_LINESV							0
  ///< Macro deciding if the function jbw_draw_linesv() has to be inlined.
#define INLINE_JBW_DRAW_STRING							0
  ///< Macro deciding if the function jbw_draw_string() has to be inlined.
#define INLINE_JBW_DRAW_LINE							0
  ///< Macro deciding if the function jbw_draw_line() has to be inlined.
#define INLINE_JBW_DRAW_LINEV							0
  ///< Macro deciding if the function jbw_draw_linev() has to be inlined.
#define INLINE_JBW_DRAW_SEGMENT_WITH_LIMITS				0
  ///< Macro deciding if the function jbw_draw_segment_with_limits() has to
  ///< be inlined.
#define INLINE_JBW_DRAW_LINE_WITH_LIMITS				0
  ///< Macro deciding if the function jbw_draw_line_with_limits() has to be
  ///< inlined.
#define INLINE_JBW_DRAW_LINE_WITH_LIMITSV				0
  ///< Macro deciding if the function jbw_draw_line_with_limitsv() has to be
  ///< inlined.
#define INLINE_JBW_DRAW_LINES_WITH_LIMITS				0
  ///< Macro deciding if the function jbw_draw_lines_with_limits() has to be
  ///< inlined.
#define INLINE_JBW_DRAW_LINES_WITH_LIMITSV				0
  ///< Macro deciding if the function jbw_draw_lines_with_limitsv() has to be
  ///< inlined.
#define INLINE_JBW_DRAW_SEGMENT							0
  ///< Macro deciding if the function jbw_draw_segment() has to be inlined.
#define INLINE_JBW_DRAW_RANGE							1
  ///< Macro deciding if the function jbw_draw_range() has to be inlined.
#define INLINE_JBW_DRAW_TICS							1
  ///< Macro deciding if the function jbw_draw_tics() has to be inlined.
#define INLINE_JBW_LOGO_DESTROY							1
  ///< Macro deciding if the function jbw_logo_destroy has to be inlined.
#define INLINE_JBW_LOGO_NEW								1
  ///< Macro deciding if the function jbw_logo_destroy has to be inlined.
#define INLINE_JBW_GRAPHIC_STRING						0
  ///< Macro deciding if the function jbw_graphic_string() has to be inlined.
#define INLINE_JBW_GRAPHIC_SET_GRID						1
  ///< Macro deciding if the function jbw_graphic_set_grid() has to be
  ///< inlined.
#define INLINE_JBW_GRAPHIC_SET_TITLE					0
  ///< Macro deciding if the function jbw_graphic_set_title() has to be
  ///< inlined.
#define INLINE_JBW_GRAPHIC_SET_XLABEL					0
  ///< Macro deciding if the function jbw_graphic_set_xlabel() has to be
  ///< inlined.
#define INLINE_JBW_GRAPHIC_SET_YLABEL					0
  ///< Macro deciding if the function jbw_graphic_set_ylabel() has to be
  ///< inlined.
#define INLINE_JBW_GRAPHIC_SET_YYLABEL					0
  ///< Macro deciding if the function jbw_graphic_set_yylabel() has to be
  ///< inlined.
#define INLINE_JBW_GRAPHIC_SET_ZLABEL					0
  ///< Macro deciding if the function jbw_graphic_set_zlabel() has to be
  ///< inlined.
#define INLINE_JBW_GRAPHIC_SET_ZZLABEL					0
  ///< Macro deciding if the function jbw_graphic_set_zzlabel() has to be
  ///< inlined.
#define INLINE_JBW_GRAPHIC_SET_LOGO						0
  ///< Macro deciding if the function jbw_graphic_set_logo() has to be
  ///< inlined.
#define INLINE_JBW_GRAPHIC_GET_DISPLAY_SIZE				0
  ///< Macro deciding if the function jbw_graphic_get_display_size() has to
  ///< be inlined.
#define INLINE_JBW_GRAPHIC_DRAW_STRING					0
  ///< Macro deciding if the function jbw_graphic_draw_string() has to be
  ///< inlined.
#define INLINE_JBW_GRAPHIC_MAP_RESIZE					1
  ///< Macro deciding if the function jbw_graphic_map_resize() has to be
  ///< inlined.
#define INLINE_JBW_GRAPHIC_DRAW_RESIZE					0
  ///< Macro deciding if the function jbw_graphic_draw_resize() has to be
  ///< inlined.
#define INLINE_JBW_GRAPHIC_LABELS						0
  ///< Macro deciding if the function jbw_graphic_labels() has to be inlined.
#define INLINE_JBW_GRAPHIC_DRAW_LINE					1
  ///< Macro deciding if the function jbw_graphic_draw_line() has to be
  ///< inlined.
#define INLINE_JBW_GRAPHIC_DRAW_LINES					1
  ///< Macro deciding if the function jbw_graphic_draw_lines() has to be
  ///< inlined.
#define INLINE_JBW_GRAPHIC_DRAW_LINESV					0
  ///< Macro deciding if the function jbw_graphic_draw_linesv() has to be
  ///< inlined.
#define INLINE_JBW_GRAPHIC_DRAW_LOGO					0
  ///< Macro deciding if the function jbw_graphic_draw_logo() has to be
  ///< inlined.
#define INLINE_JBW_GRAPHIC_REALIZE						1
  ///< Macro deciding if the function jbw_graphic_realize() has to be
  ///< inlined.
#define INLINE_JBW_GRAPHIC_EXPOSE_EVENT					1
  ///< Macro deciding if the function jbw_graphic_expose_event() has to be
  ///< inlined.
#define INLINE_JBW_GRAPHIC_DESTROY						0
  ///< Macro deciding if the function jbw_graphic_destroy() has to be
  ///< inlined.
#define INLINE_JBW_GRAPHIC_NEW							0
  ///< Macro deciding if the function jbw_graphic_new() has to be inlined.
#define INLINE_JBW_GRAPHIC_INIT							1
  ///< Macro deciding if the function jbw_graphic_new() has to be inlined.
#define INLINE_JBW_ARRAY_EDITOR_SET_ELEMENT				1
  ///< Macro deciding if the function jbw_array_editor_set_element() has to
  ///< be inlined.
#define INLINE_JBW_ARRAY_EDITOR_GET_ELEMENT				1
  ///< Macro deciding if the function jbw_array_editor_get_element() has to
  ///< be inlined.
#define INLINE_JBW_ARRAY_EDITOR_SET_ELEMENT_INT			1
  ///< Macro deciding if the function jbw_array_editor_set_element_int() has
  ///< to be inlined.
#define INLINE_JBW_ARRAY_EDITOR_GET_ELEMENT_INT			1
  ///< Macro deciding if the function jbw_array_editor_get_element_int() has
  ///< to be inlined.
#define INLINE_JBW_ARRAY_EDITOR_SET_ELEMENT_FLOAT		1
  ///< Macro deciding if the function
  ///< jbw_array_editor_set_element_float() has to be inlined.
#define INLINE_JBW_ARRAY_EDITOR_GET_ELEMENT_FLOAT		1
  ///< Macro deciding if the function
  ///< jbw_array_editor_get_element_float() has to be inlined.
#define INLINE_JBW_ARRAY_EDITOR_SET_COLUMN				1
  ///< Macro deciding if the function jbw_array_editor_set_column() has to be
  ///< inlined.
#define INLINE_JBW_ARRAY_EDITOR_GET_COLUMN				1
  ///< Macro deciding if the function jbw_array_editor_get_column() has to be
  ///< inlined.
#define INLINE_JBW_ARRAY_EDITOR_SET_COLUMN_INT			1
  ///< Macro deciding if the function jbw_array_editor_set_column_int() has
  ///< to be inlined.
#define INLINE_JBW_ARRAY_EDITOR_GET_COLUMN_INT			1
  ///< Macro deciding if the function jbw_array_editor_get_column_int() has
  ///< to be inlined.
#define INLINE_JBW_ARRAY_EDITOR_SET_COLUMN_FLOAT		1
  ///< Macro deciding if the function jbw_array_editor_set_column_float() has
  ///< to be inlined.
#define INLINE_JBW_ARRAY_EDITOR_GET_COLUMN_TIME			1
  ///< Macro deciding if the function jbw_array_editor_get_column_float() has
  ///< to be inlined.
#define INLINE_JBW_ARRAY_EDITOR_SET_COLUMN_TIME			1
  ///< Macro deciding if the function jbw_array_editor_set_column_time() has
  ///< to be inlined.
#define INLINE_JBW_ARRAY_EDITOR_GET_COLUMN_FLOAT		1
  ///< Macro deciding if the function jbw_array_editor_get_column_time() has
  ///< to be inlined.
#define INLINE_JBW_ARRAY_EDITOR_SET_COLUMN_SENSITIVE	1
  ///< Macro deciding if the function
  ///< jbw_array_editor_set_column_sensitive() has to be inlined.
#define INLINE_JBW_ARRAY_EDITOR_SHOW_COLUMN				1
  ///< Macro deciding if the function jbw_array_editor_show_column() has to
  ///< be inlined.
#define INLINE_JBW_ARRAY_EDITOR_HIDE_COLUMN				1
  ///< Macro deciding if the function jbw_array_editor_hide_column() has to
  ///< be inlined.
#define INLINE_JBW_ARRAY_EDITOR_INSERT_BUTTON			1
  ///< Macro deciding if the function jbw_array_editor_insert_button() has to
  ///< be inlined.
#define INLINE_JBW_ARRAY_EDITOR_INSERT_ENTRY			1
  ///< Macro deciding if the function jbw_array_editor_insert_entry() has to
  ///< be inlined.
#define INLINE_JBW_ARRAY_EDITOR_INSERT					1
  ///< Macro deciding if the function jbw_array_editor_insert() has to be
  ///< inlined.
#define INLINE_JBW_ARRAY_EDITOR_UP_ROWS					1
  ///< Macro deciding if the function jbw_array_editor_up_rows() has to be
  ///< inlined.
#define INLINE_JBW_ARRAY_EDITOR_INSERT_ROW				1
  ///< Macro deciding if the function jbw_array_editor_insert_row() has to be
  ///< inlined.
#define INLINE_JBW_ARRAY_EDITOR_REMOVE_ENTRY			1
  ///< Macro deciding if the function jbw_array_editor_remove_entry() has to
  ///< be inlined.
#define INLINE_JBW_ARRAY_EDITOR_REMOVE					1
  ///< Macro deciding if the function jbw_array_editor_remove() has to be
  ///< inlined.
#define INLINE_JBW_ARRAY_EDITOR_DOWN_ROWS				1
  ///< Macro deciding if the function jbw_array_editor_down_rows() has to be
  ///< inlined.
#define INLINE_JBW_ARRAY_EDITOR_REMOVE_ROW				1
  ///< Macro deciding if the function jbw_array_editor_remove_row() has to be
  ///< inlined.
#define INLINE_JBW_ARRAY_EDITOR_SET_ROWS				1
  ///< Macro deciding if the function jbw_array_editor_set_rows() has to be
  ///< inlined.
#define INLINE_JBW_ARRAY_EDITOR_SET_TITLE				1
  ///< Macro deciding if the function jbw_array_editor_set_title() has to be
  ///< inlined.
#define INLINE_JBW_ARRAY_EDITOR_DELETE					1
  ///< Macro deciding if the function jbw_array_editor_delete() has to be
  ///< inlined.
#define INLINE_JBW_ARRAY_EDITOR_NEW						1
  ///< Macro deciding if the function jbw_array_editor_new() has to be
  ///< inlined.

  // These macros decide if the corresponding functions have to be debugged

#define DEBUG_JBM_FCOMPARE							0
  ///< Macro deciding if the function jbm_fcompare() has to be debugged.
#define DEBUG_JBM_MAX								0
  ///< Macro deciding if the function jbm_max() has to be debugged.
#define DEBUG_JBM_MIN								0
  ///< Macro deciding if the function jbm_min() has to be debugged.
#define DEBUG_JBM_MAXL								1
  ///< Macro deciding if the function jbm_maxl() has to be debugged.
#define DEBUG_JBM_MINL								1
  ///< Macro deciding if the function jbm_minl() has to be debugged.
#define DEBUG_JBM_MAXLL								1
  ///< Macro deciding if the function jbm_maxll() has to be debugged.
#define DEBUG_JBM_MINLL								1
  ///< Macro deciding if the function jbm_minll() has to be debugged.
#define DEBUG_JBM_FMAX								0
  ///< Macro deciding if the function jbm_fmax() has to be debugged.
#define DEBUG_JBM_FMIN								0
  ///< Macro deciding if the function jbm_fmin() has to be debugged.
#define DEBUG_JBM_MODMIN							1
  ///< Macro deciding if the function jbm_modmin() has to be debugged.
#define DEBUG_JBM_MODMINL							1
  ///< Macro deciding if the function jbm_modminl() has to be debugged.
#define DEBUG_JBM_MODMINLL							1
  ///< Macro deciding if the function jbm_modminll() has to be debugged.
#define DEBUG_JBM_FMODMIN							0
  ///< Macro deciding if the function jbm_fmodmin() has to be debugged.
#define DEBUG_JBM_CHANGE							0
  ///< Macro deciding if the function jbm_change() has to be debugged.
#define DEBUG_JBM_CHANGEL							1
  ///< Macro deciding if the function jbm_changel() has to be debugged.
#define DEBUG_JBM_CHANGELL							1
  ///< Macro deciding if the function jbm_changell() has to be debugged.
#define DEBUG_JBM_FCHANGE							0
  ///< Macro deciding if the function jbm_fchange() has to be debugged.
#define DEBUG_JBM_FCHANGEL							1
  ///< Macro deciding if the function jbm_fchangel() has to be debugged.
#define DEBUG_JBM_SQR								0
  ///< Macro deciding if the function jbm_sqr() has to be debugged.
#define DEBUG_JBM_SQRL								1
  ///< Macro deciding if the function jbm_sqrl() has to be debugged.
#define DEBUG_JBM_SQRLL								1
  ///< Macro deciding if the function jbm_sqrll() has to be debugged.
#define DEBUG_JBM_FSQR								0
  ///< Macro deciding if the function jbm_fsqr() has to be debugged.
#define DEBUG_JBM_DBL								1
  ///< Macro deciding if the function jbm_dbl() has to be debugged.
#define DEBUG_JBM_DBLL								1
  ///< Macro deciding if the function jbm_dbll() has to be debugged.
#define DEBUG_JBM_DBLLL								1
  ///< Macro deciding if the function jbm_dblll() has to be debugged.
#define DEBUG_JBM_FDBL								0
  ///< Macro deciding if the function jbm_fdbl() has to be debugged.
#define DEBUG_JBM_EXTRAPOLATE						0
  ///< Macro deciding if the function jbm_extrapolate() has to be debugged.
#define DEBUG_JBM_INTERPOLATE						0
  ///< Macro deciding if the function jbm_interpolate() has to be
  ///< debugged.
#define DEBUG_JBM_INTEGRAL							0
  ///< Macro deciding if the function jbm_integral() has to be debugged.
#define DEBUG_JBM_FARRAY_SEARCH						0
  ///< Macro deciding if the function jbm_farray_search() has to be
  ///< debugged.
  /**
 * \def DEBUG_JBM_FARRAY_SEARCH_EXTENDED
  ///< Macro deciding if the function jbm_farray_search_extended() has to be
  ///< debugged.
 */
#define DEBUG_JBM_FARRAY_SEARCH_EXTENDED			0
#define DEBUG_JBM_FARRAY_MAX						0
  ///< Macro deciding if the function jbm_farray_max() has to be debugged.
#define DEBUG_JBM_FARRAY_MIN						0
  ///< Macro deciding if the function jbm_farray_min() has to be debugged.
#define DEBUG_JBM_FARRAY_MAXMIN						0
  ///< Macro deciding if the function jbm_farray_maxmin() has to be debugged.
#define DEBUG_JBM_FARRAY_INTERPOLATE				0
  ///< Macro deciding if the function jbm_farray_interpolate() has to be
  ///< debugged.
#define DEBUG_JBM_FARRAY_ADD						1
  ///< Macro deciding if the function jbm_farray_add() has to be
  ///< debugged.
#define DEBUG_JBM_FARRAY_INTEGRAL					0
  ///< Macro deciding if the function jbm_farray_integral() has to be
  ///< debugged.
#define DEBUG_JBM_FARRAY_MEAN_SQUARE_ERROR			0
  ///< Macro deciding if the function jbm_farray_mean_square_error() has to
  ///< be debugged.
#define DEBUG_JBM_FARRAY_ROOT_MEAN_SQUARE_ERROR		0
  ///< Macro deciding if the function jbm_farray_root_mean_square_error() has
  ///< to be debugged.
#define DEBUG_JBM_DARRAY_SEARCH						0
  ///< Macro deciding if the function jbm_darray_search() has to be
  ///< debugged.
#define DEBUG_JBM_DARRAY_SEARCH_EXTENDED			0
  ///< Macro deciding if the function jbm_darray_search_extended() has to be
  ///< debugged.
#define DEBUG_JBM_DARRAY_MAX						0
  ///< Macro deciding if the function jbm_darray_max() has to be debugged.
#define DEBUG_JBM_DARRAY_MIN						0
  ///< Macro deciding if the function jbm_darray_min() has to be debugged.
#define DEBUG_JBM_DARRAY_MAXMIN						0
  ///< Macro deciding if the function jbm_darray_maxmin() has to be debugged.
#define DEBUG_JBM_DARRAY_FARRAY_INTERPOLATE			0
  ///< Macro deciding if the function jbm_darray_farray_interpolate() has to
  ///< be debugged.
#define DEBUG_JBM_DARRAY_INTERPOLATE				0
  ///< Macro deciding if the function jbm_darray_interpolate() has to be
  ///< debugged.
#define DEBUG_JBM_DARRAY_ADD						1
  ///< Macro deciding if the function jbm_darray_add() has to be
  ///< debugged.
#define DEBUG_JBM_DARRAY_FARRAY_INTEGRAL			0
  ///< Macro deciding if the function jbm_darray_farray_integral() has to be
  ///< debugged.
#define DEBUG_JBM_DARRAY_INTEGRAL					0
  ///< Macro deciding if the function jbm_darray_integral() has to be
  ///< debugged.
#define DEBUG_JBM_DARRAY_MEAN_SQUARE_ERROR			0
  ///< Macro deciding if the function jbm_darray_mean_square_error() has to
  ///< be debugged.
#define DEBUG_JBM_DARRAY_ROOT_MEAN_SQUARE_ERROR		0
  ///< Macro deciding if the function jbm_darray_root_mean_square_error() has
  ///< to be debugged.
#define DEBUG_JBM_V2_LENGTH							1
  ///< Macro deciding if the function jbm_v2_length() has to be debugged.
#define DEBUG_JBM_V3_LENGTH							1
  ///< Macro deciding if the function jbm_v3_length() has to be debugged.
#define DEBUG_JBM_SOLVE_CUADRATIC_REDUCED			0
  ///< Macro deciding if the function jbm_solve_cuadratic_reduced() has to be
  ///< debugged.
#define DEBUG_JBM_SOLVE_CUADRATIC					0
  ///< Macro deciding if the function jbm_solve_cuadratic() has to be
  ///< debugged.
#define DEBUG_JBM_SOLVE_CUBIC_REDUCED				1
  ///< Macro deciding if the function jbm_solve_cubic_reduced() has to be
  ///< debugged.
#define DEBUG_JBM_SOLVE_CUBIC						1
  ///< Macro deciding if the function jbm_solve_cubic() has to be debugged.
#define DEBUG_JBM_INDEX_SORT_INSERTION				0
  ///< Macro deciding if the function jbm_index_sort_insertion() has to be
  ///< debugged.
#define DEBUG_JBM_INDEX_SORT_INTERCHANGE			0
  ///< Macro deciding if the function jbm_index_sort_interchange() has to be
  ///< debugged.
#define DEBUG_JBM_INDEX_SORT_MERGE					0
  ///< Macro deciding if the function jbm_index_sort_merge() has to be
  ///< debugged.
#define DEBUG_JBM_INDEX_SORT_FLASH					0
  ///< Macro deciding if the function jbm_index_sort_flash() has to be
  ///< debugged.
#define DEBUG_JBM_INDEX_SORT						0
  ///< Macro deciding if the function jbm_index_sort() has to be
  ///< debugged.
#define DEBUG_JBM_INDEX_SORT_EXTENDED				0
  ///< Macro deciding if the function jbm_index_sort_extended() has to
  ///< be debugged.
#define DEBUG_JBM_MATRIX_SOLVE						1
  ///< Macro deciding if the function jbm_matrix_solve() has to be
  ///< debugged.
#define DEBUG_JBM_MATRIX_SOLVE_TRIDIAGONAL			1
  ///< Macro deciding if the function jbm_matrix_solve_tridiagonal() has to
  ///< be debugged.
#define DEBUG_JBM_MATRIX_SOLVE_TRIDIAGONAL_ZERO		1
  ///< Macro deciding if the function jbm_matrix_solve_tridiagonal_zero() has
  ///< to be debugged.
#define DEBUG_JBM_MATRIX_SOLVE_PENTADIAGONAL		1
  ///< Macro deciding if the function jbm_matrix_solve_pentadiagonal() has to
  ///< be debugged.
#define DEBUG_JBM_MATRIX_SOLVE_PENTADIAGONAL_ZERO	1
  ///< Macro deciding if the function jbm_matrix_solve_pentadiagonal_zero()
  ///< has to be debugged.
#define DEBUG_JBM_REGRESSION						1
  ///< Macro deciding if the function jbm_regression() has to be debugged.
#define DEBUG_JBM_REGRESSION_LINEAR					0
  ///< Macro deciding if the function jbm_regression_linear() has to be
  ///< debugged.
#define DEBUG_JBM_REGRESSION_EXPONENTIAL			1
  ///< Macro deciding if the function jbm_regression_exponential() has to be
  ///< debugged.
#define DEBUG_JBM_REGRESSION_MULTILINEAR			0
  ///< Macro deciding if the function jbm_regression_multilinear() has to be
  ///< debugged.
#define DEBUG_JBM_REGRESSION_MULTIEXPONENTIAL		0
  ///< Macro deciding if the function jbm_regression_multiexponential() has
  ///< to be debugged.
#define DEBUG_JBM_SPLINE_CUBIC						1
  ///< Macro deciding if the function jbm_spline_cubic() has to be debugged.
#define DEBUG_JBM_FLUX_LIMITER_SUPERBEE				1
  ///< Macro deciding if the function jbm_flux_limiter_superbee() has to be
  ///< debugged.
#define DEBUG_JBM_FLUX_LIMITER_VANLEER				1
  ///< Macro deciding if the function jbm_flux_limiter_VanLeer() has to be
  ///< debugged.
#define DEBUG_JBM_FLUX_LIMITER_VANALBADA			1
  ///< Macro deciding if the function jbm_flux_limiter_VanAlbada() has to be
  ///< debugged.
#define DEBUG_JBM_FLUX_LIMITER_MINMOD				1
  ///< Macro deciding if the function jbm_flux_limiter_minmod() has to be
  ///< debugged.
#define DEBUG_JBM_FLUX_LIMITER_SUPERMIN				1
  ///< Macro deciding if the function jbm_flux_limiter_supermin() has to be
  ///< debugged.
#define DEBUG_JBM_FLUX_LIMITER_MINSUPER				1
  ///< Macro deciding if the function jbm_flux_limiter_minsuper() has to be
  ///< debugged.
#define DEBUG_JBM_FLUX_LIMITER_NULL					1
  ///< Macro deciding if the function jbm_flux_limiter_null() has to be
  ///< debugged.
#define DEBUG_JBM_FLUX_LIMITER_CENTRED				1
  ///< Macro deciding if the function jbm_flux_limiter_centred() has to be
  ///< debugged.
#define DEBUG_JBM_FLUX_LIMITER_TOTAL				1
  ///< Macro deciding if the function jbm_flux_limiter_total() has to be
  ///< debugged.
#define DEBUG_JBM_FLUX_LIMITER_MONOTONIZED_CENTRAL	1
  ///< Macro deciding if the function jbm_flux_limiter_monotonized_central()
  ///< has to be debugged.
#define DEBUG_JBM_FLUX_LIMITER_MEAN					1
  ///< Macro deciding if the function jbm_flux_limiter_mean() has to be
  ///< debugged.
#define DEBUG_JBM_FLUX_LIMITER_SELECT				1
  ///< Macro deciding if the function jbm_flux_limiter_select() has to be
  ///< debugged.
#define DEBUG_JBM_TRANSVERSAL_SECTION_REGIONS_SORT	0
  ///< Macro deciding if the function jbm_transversal_section_regions_sort()
  ///< has to be debugged.
#define DEBUG_JBM_TRANSVERSAL_SECTION_REGIONS		0
  ///< Macro deciding if the function jbm_transversal_section_regions() has
  ///< to be debugged.
#define DEBUG_JBM_VARRAY_SEARCH						0
  ///< Macro deciding if the function jbm_varray_search() has to be
  ///< debugged.
#define DEBUG_JBM_VARRAY_SEARCH_EXTENDED			0
  ///< Macro deciding if the function jbm_varray_search_extended() has to
  ///< be debugged.
#define DEBUG_JBM_VARRAY_MAX						0
  ///< Macro deciding if the function jbm_varray_max() has to be debugged.
#define DEBUG_JBM_VARRAY_MIN						0
  ///< Macro deciding if the function jbm_varray_min() has to be debugged.
#define DEBUG_JBM_VARRAY_MAXMIN						0
  ///< Macro deciding if the function jbm_varray_maxmin() has to be debugged.
#define DEBUG_JBM_VARRAY_MEAN_SQUARE_ERROR			0
  ///< Macro deciding if the function jbm_varray_mean_square_error() has to
  ///< be debugged.
#define DEBUG_JBM_VARRAY_ROOT_MEAN_SQUARE_ERROR		0
  ///< Macro deciding if the function jbm_varray_root_mean_square_error() has
  ///< to be debugged.
#define DEBUG_JBM_VARRAY_SOLVE_TRIDIAGONAL			1
  ///< Macro deciding if the function jbm_varray_solve_tridiagonal() has to
  ///< be debugged.
#define DEBUG_JBM_VARRAY_SOLVE_TRIDIAGONAL_ZERO		1
  ///< Macro deciding if the function jbm_varray_solve_tridiagonal_zero() has
  ///< to be debugged.
#define DEBUG_JBM_VDARRAY_SEARCH					0
  ///< Macro deciding if the function jbm_vdarray_search() has to be
  ///< debugged.
#define DEBUG_JBM_VDARRAY_SEARCH_EXTENDED			0
  ///< Macro deciding if the function jbm_vdarray_search_extended() has to
  ///< be debugged.
#define DEBUG_JBM_VDARRAY_MAX						0
  ///< Macro deciding if the function jbm_vdarray_max() has to be debugged.
#define DEBUG_JBM_VDARRAY_MIN						0
  ///< Macro deciding if the function jbm_vdarray_min() has to be debugged.
#define DEBUG_JBM_VDARRAY_MAXMIN					0
  ///< Macro deciding if the function jbm_vdarray_maxmin() has to be
  ///< debugged.
#define DEBUG_JBM_VDARRAY_MEAN_SQUARE_ERROR			0
  ///< Macro deciding if the function jbm_vdarray_mean_square_error() has to
  ///< be debugged.
#define DEBUG_JBM_VDARRAY_ROOT_MEAN_SQUARE_ERROR	0
  ///< Macro deciding if the function jbm_vdarray_root_mean_square_error()
  ///< has to be debugged.
#define DEBUG_JBM_VDARRAY_SOLVE_TRIDIAGONAL			1
  ///< Macro deciding if the function jbm_vdarray_solve_tridiagonal() has to
  ///< be debugged.
#define DEBUG_JBM_VDARRAY_SOLVE_TRIDIAGONAL_ZERO	1
  ///< Macro deciding if the function jbm_vdarray_solve_tridiagonal_zero()
  ///< has to be debugged.
#define DEBUG_JBM_FILE_MEAN_SQUARE_ERROR			0
  ///< Macro deciding if the function jbm_file_mean_square_error() has to be
  ///< debugged.
#define DEBUG_JBM_FILE_ROOT_MEAN_SQUARE_ERROR		0
  ///< Macro deciding if the function jbm_file_root_mean_square_error() has
  ///< to be debugged.

#endif
