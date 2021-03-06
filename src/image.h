#ifndef IMAGE_H_
#define IMAGE_H_
/*****************************************************************************
 * This file is part of Kvazaar HEVC encoder.
 *
 * Copyright (C) 2013-2015 Tampere University of Technology and others (see
 * COPYING file).
 *
 * Kvazaar is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * Kvazaar is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with Kvazaar.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

/**
 * \ingroup DataStructures
 * \file
 * A reference counted YUV pixel buffer.
 */

#include "global.h" // IWYU pragma: keep

#include "kvazaar.h"
#include "strategies/optimized_sad_func_ptr_t.h"

// ***********************************************
  // Modified for SHVC
#include "scaler/scaler.h"
// ***********************************************


typedef struct {
  kvz_pixel y[LCU_LUMA_SIZE];
  kvz_pixel u[LCU_CHROMA_SIZE];
  kvz_pixel v[LCU_CHROMA_SIZE];
  enum kvz_chroma_format chroma_format;
} lcu_yuv_t;

typedef struct {
  int size;
  int16_t *y;
  int16_t *u;
  int16_t *v;
} hi_prec_buf_t;

typedef struct {
  int size;
  kvz_pixel *y;
  kvz_pixel *u;
  kvz_pixel *v;
} yuv_t;


kvz_picture *kvz_image_alloc_420(const int32_t width, const int32_t height);
kvz_picture *kvz_image_alloc(enum kvz_chroma_format chroma_format, const int32_t width, const int32_t height);

void kvz_image_free(kvz_picture *im);

kvz_picture *kvz_image_copy_ref(kvz_picture *im);

kvz_picture *kvz_image_make_subimage(kvz_picture *const orig_image,
                             const unsigned x_offset,
                             const unsigned y_offset,
                             const unsigned width,
                             const unsigned height);

yuv_t * kvz_yuv_t_alloc(int luma_size, int chroma_size);
void kvz_yuv_t_free(yuv_t * yuv);

hi_prec_buf_t * kvz_hi_prec_buf_t_alloc(int luma_size);
void kvz_hi_prec_buf_t_free(hi_prec_buf_t * yuv);


//Algorithms
unsigned kvz_image_calc_sad(const kvz_picture *pic,
                            const kvz_picture *ref,
                            int pic_x,
                            int pic_y,
                            int ref_x,
                            int ref_y,
                            int block_width,
                            int block_height,
                            optimized_sad_func_ptr_t optimized_sad);


unsigned kvz_image_calc_satd(const kvz_picture *pic,
                             const kvz_picture *ref,
                             int pic_x,
                             int pic_y,
                             int ref_x,
                             int ref_y,
                             int block_width,
                             int block_height);


void kvz_pixels_blit(const kvz_pixel* orig, kvz_pixel *dst,
                         unsigned width, unsigned height,
                         unsigned orig_stride, unsigned dst_stride);

// ***********************************************
// Modified for SHVC
typedef struct {
  kvz_picture *pic_in;
  kvz_picture *pic_out;
  
  opaque_yuv_buffer_t *src_buffer;
  opaque_yuv_buffer_t *ver_tmp_buffer;
  opaque_yuv_buffer_t *trgt_buffer;

  int block_x;
  int block_y;
  int block_width;
  int block_height;

  int use_tiles;

  int refcount;

  const scaling_parameter_t *param;
} kvz_image_scaling_parameter_t;

// Worker will free the parameter struct after execution. pic_in and pic_out are also freed (ref count decreased)
void kvz_image_scaler_worker( void *opaque_param);
void kvz_block_scaler_worker( void *opaque_param );
//void kvz_block_step_scaler_worker(void * opaque_param);
void kvz_opaque_block_step_scaler_worker(void * opaque_param);
//void kvz_tile_step_scaler_worker(void * opaque_param);
kvz_picture* kvz_image_scaling(kvz_picture* const pic_in, const scaling_parameter_t *const param, uint8_t skip_same);
void kvz_copy_image_scaling_parameters(kvz_image_scaling_parameter_t * const dst, const kvz_image_scaling_parameter_t * const src);
void kvz_propagate_image_scaling_parameters(kvz_image_scaling_parameter_t * const dst, const kvz_image_scaling_parameter_t * const src);
// ***********************************************

#endif
