/* 
 * converter.h
 *
 * Copyright 2011-2012 ESTEVE Olivier <naskel .[.at.]. gmail.com>
 *
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 *
 * $Log: converter.h,v $
 *
 *
 *
 *
 *
 *
 * 
 * 
 */
#ifndef __IMAGE_CONVERTER_CONVERTER_INCLUDE_H_
#define __IMAGE_CONVERTER_CONVERTER_INCLUDE_H_

#include "define.h"
#include "image.h"

#ifdef __cplusplus
extern "C" {
#endif	/** extern "C" */

/** */
typedef void (*CONV)( void *src, void *dst, const int width, const int height );

/** function for convertion */
#define PROTO_PIXEL_FNC(name)																	\
	void name ## _to_RGB444		(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_RGBA4441	(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_RGBA4444	(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_RGB555		(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_RGBA5551	(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_RGB565		(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_RGB888		(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_RGBA8888	(void *bsrc,void *bdst,const int width,const int height);		\
																								\
	void name ## _to_BGR444		(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_ABGR1444	(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_ABGR4444	(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_BGR555		(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_ABGR1555	(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_BGR565		(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_BGR888		(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_ABGR8888	(void *bsrc,void *bdst,const int width,const int height);		\
																								\
	void name ## _to_BGRA4441	(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_BGRA4444	(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_BGRA5551	(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_BGRA8888	(void *bsrc,void *bdst,const int width,const int height);		\
																								\
	void name ## _to_RGB332		(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_BGR332		(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_RGBA5542	(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_ABGR2554	(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_RGBA6661	(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_ABGR1666	(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_RGBA6666	(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_ABGR6666	(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_RGB666		(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_BGR666		(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_RGBA5658	(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_ABGR8565	(void *bsrc,void *bdst,const int width,const int height);		\
																								\
	void name ## _to_YV12		(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_I420		(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_NV12		(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_Y41P		(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_Y411		(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_YUY2		(void *bsrc,void *bdst,const int width,const int height);		\
	void name ## _to_UYVY		(void *bsrc,void *bdst,const int width,const int height);		\

/** create prototype and structure */
PROTO_PIXEL_FNC( RGB444 );
PROTO_PIXEL_FNC( RGBA4441 );
PROTO_PIXEL_FNC( RGBA4444 );
PROTO_PIXEL_FNC( RGB555 );
PROTO_PIXEL_FNC( RGBA5551 );
PROTO_PIXEL_FNC( RGB565 );
PROTO_PIXEL_FNC( RGB888 );
PROTO_PIXEL_FNC( RGBA8888 );

/** create prototype and structure */
PROTO_PIXEL_FNC( BGR444 );
PROTO_PIXEL_FNC( ABGR1444 );
PROTO_PIXEL_FNC( ABGR4444 );
PROTO_PIXEL_FNC( BGR555 );
PROTO_PIXEL_FNC( ABGR1555 );
PROTO_PIXEL_FNC( BGR565 );
PROTO_PIXEL_FNC( BGR888 );
PROTO_PIXEL_FNC( ABGR8888 );

/** create prototype and structure */
PROTO_PIXEL_FNC( BGRA4441 );
PROTO_PIXEL_FNC( BGRA4444 );
PROTO_PIXEL_FNC( BGRA5551 );
PROTO_PIXEL_FNC( BGRA8888 );

/** create prototype and structure */
PROTO_PIXEL_FNC( RGB332 );
PROTO_PIXEL_FNC( BGR332 );
PROTO_PIXEL_FNC( RGBA5542 );
PROTO_PIXEL_FNC( ABGR2554 );
PROTO_PIXEL_FNC( RGBA6661 );
PROTO_PIXEL_FNC( ABGR1666 );
PROTO_PIXEL_FNC( RGBA6666 );
PROTO_PIXEL_FNC( ABGR6666 );
PROTO_PIXEL_FNC( RGB666 );
PROTO_PIXEL_FNC( BGR666 );
PROTO_PIXEL_FNC( RGBA5658 );
PROTO_PIXEL_FNC( ABGR8565 );

/** TODO */
PROTO_PIXEL_FNC	( YV12 );
PROTO_PIXEL_FNC	( I420 );
PROTO_PIXEL_FNC	( NV12 );
PROTO_PIXEL_FNC	( Y41P );
PROTO_PIXEL_FNC	( Y411 );
PROTO_PIXEL_FNC	( YUY2 );
PROTO_PIXEL_FNC	( UYVY );

#undef PROTO_PIXEL_FNC

/** todo : doc */
//! todo : doc
void rgb24_to_yuv420p( const uchar * rgb, uchar * yuv, const uint rgbIncrement, const uchar flip, const int srcFrameWidth, const int srcFrameHeight );

/** todo : doc */
//! todo : doc
void* rgba2luminance_alpha(uchar *data,const int width,const int height);

/** todo : doc */
//! todo : doc
void* luminance2rgba(uchar *data,const int width,const int height);

/** todo : doc */
//! todo : doc
void* rgba2luminance(uchar *data,const int width,const int height);

/** todo : doc */
//! todo : doc
void* rgba_float2rgb(float *data,const int width,const int height);

/** todo : doc */
//! todo : doc
void* rgb_float2rgb(float *data,const int width,const int height);

/** todo : doc */
//! todo : doc
void* rgba2rgba_float(uchar *data,const int width,const int height);

/** todo : doc */
//! todo : doc
void* rgba2rgb_float(uchar *data,const int width,const int height);

/** todo : doc */
//! todo : doc
void* rgba2luminance_alpha_float(uchar *data,const int width,const int height);

/** todo : doc */
//! todo : doc
void* rgba2luminance_float(uchar *data,const int width,const int height);

/** todo : doc */
//! todo : doc
void* rgba2rgba(uchar *data,const int width,const int height);

/** todo : doc */
//! todo : doc
void rgba2rgb_inline( uchar *data, const int width, const int height );

/** todo : doc */
//! todo : doc
void* rgba2rgb(uchar *data,const int width,const int height);

/** todo : doc */
//! todo : doc
void* rgb2rgba(uchar *data,const int width,const int height);

/** todo : doc */
//! todo : doc
void* rgba_float2rgba(float *data,const int width,const int height);

/** todo : doc */
//! todo : doc
void* rgb565_to_rgb888(ushort *data, const int width, const int height);

/** todo : doc */
//! todo : doc
void rgb24_to_bgr565(uchar *data, uchar* dest, const int width, const int height);

/** todo : doc */
//! todo : doc
void rgb24_to_rgb565(uchar *data, uchar* dest, const int width, const int height);

/** todo : doc */
//! todo : doc
void* rgb24_to_rgb565_2(uchar *data, const int width, const int height);

/** todo : doc */
//! todo : doc
void rgb32_to_bgr565(uchar *data, uchar* dest, const int width, const int height);

/** todo : doc */
//! todo : doc
void* rgb32_to_bgr565_2(uchar *data, const int width, const int height);

/** todo : doc */
//! todo : doc
void* rgb32_to_rgb565(uchar *data, const int width, const int height);

/** todo : doc */
//! todo : doc
void* rgb32_to_rgb4444(uchar *data, const int width, const int height);

/** todo : doc */
//! todo : doc
void* rgb24_to_rgb4444(uchar *data, const int width, const int height);

/** todo : doc */
//! todo : doc
void* rgb32_to_rgb5551(uchar *data, const int width, const int height);

/** todo : doc */
//! todo : doc
void* rgb24_to_rgb5551(uchar *data, const int width, const int height);

/** todo : doc */
//! todo : doc
void*  uyvy_to_yv12(uchar *input, const int width, const int height);

/** todo : doc */
//! todo : doc
void uyvy_to_422p(uchar *input, uchar* dest, const int width, const int height) ;

/** todo : doc */
//! todo : doc
void* uyvy_to_422p_2(uchar *input, const int width, const int height);

/** todo : doc */
//! todo : doc
void yuv422_to_bgr565( uchar *src, uchar* dest, const int width, const int height );

/** todo : doc */
//! todo : doc
void yuv422_to_rgb565( uchar *src, uchar* dest, const int width, const int height );

/** todo : doc */
//! todo : doc
void yuv422_to_rgb_inline( uchar *input, const int width, const int height );

/** todo : doc */
//! todo : doc
void yuv420_to_bgr565( uchar *src, uchar* dest, const int width, const int height );

/** todo : doc */
//! todo : doc
void yuv420_to_rgb565( uchar *src, uchar* dest, const int width, const int height );

/** todo : doc */
//! todo : doc
void yuv420_to_rgb( uchar *src, uchar* dest, const int width, const int height );

/** todo : doc */
//! todo : doc
void yuv420_to_rgb_inline( uchar *input, const int width, const int height );

/** todo : doc */
//! todo : doc
void* yuv420_to_rgb_2(uchar *input, const int width, const int height);

/** todo : doc */
//! todo : doc
void* yuv420_to_yuv422p(uchar *input, const int width, const int height);

/** todo : doc */
//! todo : doc
void yv12_to_422p(uchar *src, uchar* dest, const int width, const int height);

/** todo : doc */
//! todo : doc
void* yv12_to_422p_2( uchar *input, const int width, const int height );

/** todo : doc */
//! todo : doc
void yuv422_to_rgb( uchar *data, uchar* dest, const int width, const int height );

/** todo : doc */
//! todo : doc
void* yuv422_to_rgb_2( uchar *data, const int width, const int height );

/** todo : doc */
//! todo : doc
void yuv422p_to_bgr565( uchar *src, uchar *dest, const int width, const int height );

/** todo : doc */
//! todo : doc
void yuv422p_to_rgb565( uchar *src, uchar *dest, const int width, const int height );

/** todo : doc */
//! todo : doc
void yuv422p_to_rgb( uchar *data, uchar *dest, const int width, const int height );

/** todo : doc */
//! todo : doc
void yuv422p_to_rgb_inline( uchar *data, const int width, const int height );

/** todo : doc */
//! todo : doc
void* yuv422p_to_rgb_2(uchar* data, const int width, const int height);

/** todo : doc */
//! todo : doc
void rgb24_to_yuv444( int* y, int* u, int* v, const int r, const int g, const int b );

/** todo : doc */
//! todo : doc
ushort yuv444_to_bgr565( const int y, const int u, const int v );

/** todo : doc */
//! todo : doc
ushort yuv444_to_rgb565( const int y, const int u, const int v );

/** todo : doc */
//! todo : doc
void yuv444_to_rgb24( int* r, int* g, int* b, const int y, const int u, const int v );

/** todo : doc */
//! todo : doc
int converter( void *bsrc, void *bdst, const int width, const int height, const int from, const int to );

#ifdef __cplusplus
};
#endif	/** extern "C" */

#endif	// __IMAGE_CONVERTER_CONVERTER_INCLUDE_H_

// -----------------------------------------------------------------------------
// table.h - Last Change: $Date: 2012-05-15 23:36:52 $ - End Of File
// -----------------------------------------------------------------------------
