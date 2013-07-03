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

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

#include "table.h"

#define fast_memcpy		memcpy
#define fast_memset		memset

#define KILLARRAY(a)	if ( a ) { delete [] a ; a = 0; }
#define KILLOBJECT(a)	if ( a ) { delete a ; a = 0; }

#if defined(_DEBUG)
	#define TRACE_DEBUG		printf
#else
	#define TRACE_DEBUG(...)
#endif	// _DEBUG

#define TRACE_ERROR		printf

/** image format for converter (1521 function available) */
typedef enum {
	RGB444		= 0,
	RGBA4441	= 1,
	RGBA4444	= 2,
	RGB555		= 3,
	RGBA5551	= 4,
	RGB565		= 5,
	RGB888		= 6,
	RGBA8888	= 7,
	BGR444		= 8,
	ABGR1444	= 9,
	ABGR4444	= 10,
	BGR555		= 11,
	ABGR1555	= 12,
	BGR565		= 13,
	BGR888		= 14,
	ABGR8888	= 15,
	BGRA4441	= 16,
	BGRA4444	= 17,
	BGRA5551	= 18,
	BGRA8888	= 19,
	RGB332		= 20,
	BGR332		= 21,
	RGBA5542	= 22,
	ABGR2554	= 23,
	RGBA6661	= 24,
	ABGR1666	= 25,
	RGBA6666	= 26,
	ABGR6666	= 27,
	RGB666		= 28,
	BGR666		= 29,
	RGBA5658	= 30,
	ABGR8565	= 31,
	// TODO:
	YV12		= 32,
	I420		= 33,
	NV12		= 34,
	Y41P		= 35,
	Y411		= 36,
	YUY2		= 37,
	UYVY		= 38,

	// last entry
	FMT_LAST,

	// copy
	RGB			= RGB888,
	RGB18		= RGB666,
	YUV422		= UYVY,
	Y422		= UYVY,
	IYU1		= Y411,
	UYNV		= UYVY,
};

/** */
typedef void (*CONV)( void *src, void *dst, const int& width, const int& height );

#pragma pack(push)
#pragma pack(1)

/** function for convertion */
#define PROTO_PIXEL_FNC(name)																	\
	void name ## _to_RGB444		(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_RGBA4441	(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_RGBA4444	(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_RGB555		(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_RGBA5551	(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_RGB565		(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_RGB888		(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_RGBA8888	(void *bsrc,void *bdst,const int& width,const int& height);		\
																								\
	void name ## _to_BGR444		(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_ABGR1444	(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_ABGR4444	(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_BGR555		(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_ABGR1555	(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_BGR565		(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_BGR888		(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_ABGR8888	(void *bsrc,void *bdst,const int& width,const int& height);		\
																								\
	void name ## _to_BGRA4441	(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_BGRA4444	(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_BGRA5551	(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_BGRA8888	(void *bsrc,void *bdst,const int& width,const int& height);		\
																								\
	void name ## _to_RGB332		(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_BGR332		(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_RGBA5542	(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_ABGR2554	(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_RGBA6661	(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_ABGR1666	(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_RGBA6666	(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_ABGR6666	(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_RGB666		(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_BGR666		(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_RGBA5658	(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_ABGR8565	(void *bsrc,void *bdst,const int& width,const int& height);		\
																								\
	void name ## _to_YV12		(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_I420		(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_NV12		(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_Y41P		(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_Y411		(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_YUY2		(void *bsrc,void *bdst,const int& width,const int& height);		\
	void name ## _to_UYVY		(void *bsrc,void *bdst,const int& width,const int& height);		\


/** structure and prototype for RGB image format */
#define PROTO_STRUCT_PIXEL_RGB(name,type,sr,sg,sb) \
	struct PIXEL_ ## name { type r : sr; type g : sg; type b : sb; } ; \
	PROTO_PIXEL_FNC(name)

/** structure and prototype for RGBA image format */
#define PROTO_STRUCT_PIXEL_RGBA(name,type,sr,sg,sb,sa) \
	struct PIXEL_ ## name { type r : sr; type g : sg; type b : sb; type a : sa; }; \
	PROTO_PIXEL_FNC(name)

/** structure and prototype for BGR image format */
#define PROTO_STRUCT_PIXEL_BGR(name,type,sb,sg,sr) \
	struct PIXEL_ ## name { type b : sb; type g : sg; type r : sr; }; \
	PROTO_PIXEL_FNC(name)

/** structure and prototype for ABGR image format */
#define PROTO_STRUCT_PIXEL_ABGR(name,type,sa,sb,sg,sr) \
	struct PIXEL_ ## name { type a : sa; type b : sb; type g : sg; type r : sr; }; \
	PROTO_PIXEL_FNC(name)

/** structure and prototype for BGRA image format */
#define PROTO_STRUCT_PIXEL_BGRA(name,type,sa,sb,sg,sr) \
	struct PIXEL_ ## name { type b : sb; type g : sg; type r : sr; type a : sa; }; \
	PROTO_PIXEL_FNC(name)

/** structure and prototype for YUV image format */
#define PROTO_STRUCT_PIXEL_YUV(name,type,sa,sb,sg,sr) \
	struct PIXEL_ ## name { type b : sb; type g : sg; type r : sr; type a : sa; }; \
	PROTO_PIXEL_FNC(name)

/** create prototype and structure */
PROTO_STRUCT_PIXEL_RGB ( RGB444,   ushort, 4,4,4   );	// todo: description
PROTO_STRUCT_PIXEL_RGBA( RGBA4441, ushort, 4,4,4,1 );	// todo: description
PROTO_STRUCT_PIXEL_RGBA( RGBA4444, ushort, 4,4,4,4 );	// todo: description
PROTO_STRUCT_PIXEL_RGB ( RGB555,   ushort, 5,5,5   );	// todo: description
PROTO_STRUCT_PIXEL_RGBA( RGBA5551, ushort, 5,5,5,1 );	// todo: description
PROTO_STRUCT_PIXEL_RGB ( RGB565,   ushort, 5,6,5   );	// todo: description
PROTO_STRUCT_PIXEL_RGB ( RGB888,   uint,   8,8,8   );	// todo: description
PROTO_STRUCT_PIXEL_RGBA( RGBA8888, uint,   8,8,8,8 );	// todo: description

/** create prototype and structure */
PROTO_STRUCT_PIXEL_BGR ( BGR444,   ushort, 4,4,4   );	// todo: description
PROTO_STRUCT_PIXEL_ABGR( ABGR1444, ushort, 1,4,4,4 );	// todo: description
PROTO_STRUCT_PIXEL_ABGR( ABGR4444, ushort, 4,4,4,4 );	// todo: description
PROTO_STRUCT_PIXEL_BGR ( BGR555,   ushort, 5,5,5   );	// todo: description
PROTO_STRUCT_PIXEL_ABGR( ABGR1555, ushort, 1,5,5,5 );	// todo: description
PROTO_STRUCT_PIXEL_BGR ( BGR565,   ushort, 5,6,5   );	// todo: description
PROTO_STRUCT_PIXEL_BGR ( BGR888,   uint,   8,8,8   );	// todo: description
PROTO_STRUCT_PIXEL_ABGR( ABGR8888, uint,   8,8,8,8 );	// todo: description

/** create prototype and structure */
PROTO_STRUCT_PIXEL_BGRA( BGRA4441,	ushort, 1,4,4,4 );	// todo: description
PROTO_STRUCT_PIXEL_BGRA( BGRA4444,	ushort, 4,4,4,4 );	// todo: description
PROTO_STRUCT_PIXEL_BGRA( BGRA5551,	ushort, 1,5,5,5 );	// todo: description
PROTO_STRUCT_PIXEL_BGRA( BGRA8888,	uint,   8,8,8,8 );	// todo: description

/** create prototype and structure */
PROTO_STRUCT_PIXEL_BGR	( RGB332,	uchar,	3,3,2	);	// 8 bit RGB (1 byte, red 3@5, green 3@2, blue 2@0) 
PROTO_STRUCT_PIXEL_BGR	( BGR332,	uchar,	3,3,2	);	// todo: description
PROTO_STRUCT_PIXEL_RGBA	( RGBA5542,	ushort, 5,5,4,2	);	// 16 bit ARGB (2 byte, alpha 2@14, red 5@9, green 5@4, blue 4@0) 
PROTO_STRUCT_PIXEL_ABGR	( ABGR2554,	ushort, 2,5,5,4	);	// todo: description
PROTO_STRUCT_PIXEL_RGBA	( RGBA6661,	uint,	6,6,6,1	);	// 1 bit alpha (3 byte/ alpha 1@18, red 6@12, green 6@6, blue 6@0) 
PROTO_STRUCT_PIXEL_ABGR	( ABGR1666,	uint,	1,6,6,6	);	// todo: description
PROTO_STRUCT_PIXEL_RGBA	( RGBA6666,	uint,	6,6,6,6	);	// todo: description
PROTO_STRUCT_PIXEL_ABGR	( ABGR6666,	uint,	6,6,6,6	);	// todo: description
PROTO_STRUCT_PIXEL_RGB	( RGB666,	uint,	6,6,6	);	// todo: description
PROTO_STRUCT_PIXEL_BGR	( BGR666,	uint,	6,6,6	);	// todo: description
PROTO_STRUCT_PIXEL_RGBA	( RGBA5658,	uint,	5,6,5,8	);	// todo: description
PROTO_STRUCT_PIXEL_ABGR	( ABGR8565,	uint,	8,5,6,5	);	// todo: description

/** TODO */
PROTO_STRUCT_PIXEL_YUV	( YV12,	uint,   8,8,8,8 );
PROTO_STRUCT_PIXEL_YUV	( I420,	uint,   8,8,8,8 );
PROTO_STRUCT_PIXEL_YUV	( NV12,	uint,   8,8,8,8 );
PROTO_STRUCT_PIXEL_YUV	( Y41P,	uint,   8,8,8,8 );
PROTO_STRUCT_PIXEL_YUV	( Y411,	uint,   8,8,8,8 );
PROTO_STRUCT_PIXEL_YUV	( YUY2,	uint,   8,8,8,8 );
PROTO_STRUCT_PIXEL_YUV	( UYVY,	uint,   8,8,8,8 );

#undef PROTO_STRUCT_PIXEL_BGRA
#undef PROTO_STRUCT_PIXEL_ABGR
#undef PROTO_STRUCT_PIXEL_BGR
#undef PROTO_STRUCT_PIXEL_RGBA
#undef PROTO_STRUCT_PIXEL_RGB
#undef PROTO_STRUCT_PIXEL_YUV
#undef PROTO_PIXEL_FNC

#pragma pack(pop)

/** todo : doc */
//! todo : doc
void rgb24_to_yuv420p( const uchar * rgb, uchar * yuv, const uint& rgbIncrement, const uchar& flip, const int& srcFrameWidth, const int& srcFrameHeight );

/** todo : doc */
//! todo : doc
void* rgba2luminance_alpha(uchar *data,const int& width,const int& height);

/** todo : doc */
//! todo : doc
void* luminance2rgba(uchar *data,const int& width,const int& height);

/** todo : doc */
//! todo : doc
void* rgba2luminance(uchar *data,const int& width,const int& height);

/** todo : doc */
//! todo : doc
void* rgba_float2rgb(float *data,const int& width,const int& height);

/** todo : doc */
//! todo : doc
void* rgb_float2rgb(float *data,const int& width,const int& height);

/** todo : doc */
//! todo : doc
void* rgba2rgba_float(uchar *data,const int& width,const int& height);

/** todo : doc */
//! todo : doc
void* rgba2rgb_float(uchar *data,const int& width,const int& height);

/** todo : doc */
//! todo : doc
void* rgba2luminance_alpha_float(uchar *data,const int& width,const int& height);

/** todo : doc */
//! todo : doc
void* rgba2luminance_float(uchar *data,const int& width,const int& height);

/** todo : doc */
//! todo : doc
void* rgba2rgba(uchar *data,const int& width,const int& height);

/** todo : doc */
//! todo : doc
void rgba2rgb_inline( uchar *data, const int& width, const int& height );

/** todo : doc */
//! todo : doc
void* rgba2rgb(uchar *data,const int& width,const int& height);

/** todo : doc */
//! todo : doc
void* rgb2rgba(uchar *data,const int& width,const int& height);

/** todo : doc */
//! todo : doc
void* rgba_float2rgba(float *data,const int& width,const int& height);

/** todo : doc */
//! todo : doc
void* rgb565_to_rgb888(ushort *data, const int& width, const int& height);

/** todo : doc */
//! todo : doc
void rgb24_to_bgr565(uchar *data, uchar* dest, const int& width, const int& height);

/** todo : doc */
//! todo : doc
void rgb24_to_rgb565(uchar *data, uchar* dest, const int& width, const int& height);

/** todo : doc */
//! todo : doc
void* rgb24_to_rgb565(uchar *data, const int& width, const int& height);

/** todo : doc */
//! todo : doc
void rgb32_to_bgr565(uchar *data, uchar* dest, const int& width, const int& height);

/** todo : doc */
//! todo : doc
void* rgb32_to_bgr565(uchar *data, const int& width, const int& height);

/** todo : doc */
//! todo : doc
void* rgb32_to_rgb565(uchar *data, const int& width, const int& height);

/** todo : doc */
//! todo : doc
void* rgb32_to_rgb4444(uchar *data, const int& width, const int& height);

/** todo : doc */
//! todo : doc
void* rgb24_to_rgb4444(uchar *data, const int& width, const int& height);

/** todo : doc */
//! todo : doc
void* rgb32_to_rgb5551(uchar *data, const int& width, const int& height);

/** todo : doc */
//! todo : doc
void* rgb24_to_rgb5551(uchar *data, const int& width, const int& height);

/** todo : doc */
//! todo : doc
void*  uyvy_to_yv12(uchar *input, const int& width, const int& height);

/** todo : doc */
//! todo : doc
void uyvy_to_422p(uchar *input, uchar* dest, const int& width, const int& height) ;

/** todo : doc */
//! todo : doc
void* uyvy_to_422p(uchar *input, const int& width, const int& height);

/** todo : doc */
//! todo : doc
void yuv422_to_bgr565( uchar *src, uchar* dest, const int& width, const int& height );

/** todo : doc */
//! todo : doc
void yuv422_to_rgb565( uchar *src, uchar* dest, const int& width, const int& height );

/** todo : doc */
//! todo : doc
void yuv422_to_rgb_inline( uchar *input, const int& width, const int& height );

/** todo : doc */
//! todo : doc
void yuv420_to_bgr565( uchar *src, uchar* dest, const int& width, const int& height );

/** todo : doc */
//! todo : doc
void yuv420_to_rgb565( uchar *src, uchar* dest, const int& width, const int& height );

/** todo : doc */
//! todo : doc
void yuv420_to_rgb( uchar *src, uchar* dest, const int& width, const int& height );

/** todo : doc */
//! todo : doc
void yuv420_to_rgb_inline( uchar *input, const int& width, const int& height );

/** todo : doc */
//! todo : doc
void* yuv420_to_rgb(uchar *input, const int& width, const int& height);

/** todo : doc */
//! todo : doc
void* yuv420_to_yuv422p(uchar *input, const int& width, const int& height);

/** todo : doc */
//! todo : doc
void yv12_to_422p(uchar *src, uchar* dest, const int& width, const int& height);

/** todo : doc */
//! todo : doc
void* yv12_to_422p( uchar *input, const int& width, const int& height );

/** todo : doc */
//! todo : doc
void yuv422_to_rgb( uchar *data, uchar* dest, const int& width, const int& height );

/** todo : doc */
//! todo : doc
void* yuv422_to_rgb( uchar *data, const int& width, const int& height );

/** todo : doc */
//! todo : doc
void yuv422p_to_bgr565( uchar *src, uchar *dest, const int& width, const int& height );

/** todo : doc */
//! todo : doc
void yuv422p_to_rgb565( uchar *src, uchar *dest, const int& width, const int& height );

/** todo : doc */
//! todo : doc
void yuv422p_to_rgb( uchar *data, uchar *dest, const int& width, const int& height );

/** todo : doc */
//! todo : doc
void yuv422p_to_rgb_inline( uchar *data, const int& width, const int& height );

/** todo : doc */
//! todo : doc
void* yuv422p_to_rgb(uchar* data, const int& width, const int& height);

/** todo : doc */
//! todo : doc
void rgb24_to_yuv444( int &y, int &u, int &v, const int& r, const int& g, const int& b );

/** todo : doc */
//! todo : doc
ushort yuv444_to_bgr565( const int& y, const int& u, const int& v );

/** todo : doc */
//! todo : doc
ushort yuv444_to_rgb565( const int& y, const int& u, const int& v );

/** todo : doc */
//! todo : doc
void yuv444_to_rgb24( int &r, int &g, int &b, const int& y, const int& u, const int& v );

/** todo : doc */
//! todo : doc
int converter( void *bsrc, void *bdst, const int& width, const int& height, const int& from, const int& to );

#endif	// __IMAGE_CONVERTER_CONVERTER_INCLUDE_H_

// -----------------------------------------------------------------------------
// table.h - Last Change: $Date: 2012-05-15 23:36:52 $ - End Of File
// -----------------------------------------------------------------------------
