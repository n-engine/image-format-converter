/* 
 * pixel.h
 *
 * Copyright 2013 ESTEVE Olivier <naskel .[.at.]. gmail.com>
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
 * $Log: pixel.h,v $
 *
 *
 *
 *
 *
 *
 * 
 * 
 */
#ifndef __IMAGE_CONVERTER_PIXEL_INCLUDE_H_
#define __IMAGE_CONVERTER_PIXEL_INCLUDE_H_

#ifdef __cplusplus
extern "C" {
#endif	/** extern "C" */

/** pixel format */
enum {
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

/** structure and prototype for RGB image format */
#define PROTO_STRUCT_PIXEL_RGB(name,type,sr,sg,sb) \
	struct PIXEL_ ## name { type r : sr; type g : sg; type b : sb; } ;

/** structure and prototype for RGBA image format */
#define PROTO_STRUCT_PIXEL_RGBA(name,type,sr,sg,sb,sa) \
	struct PIXEL_ ## name { type r : sr; type g : sg; type b : sb; type a : sa; };

/** structure and prototype for BGR image format */
#define PROTO_STRUCT_PIXEL_BGR(name,type,sb,sg,sr) \
	struct PIXEL_ ## name { type b : sb; type g : sg; type r : sr; };

/** structure and prototype for ABGR image format */
#define PROTO_STRUCT_PIXEL_ABGR(name,type,sa,sb,sg,sr) \
	struct PIXEL_ ## name { type a : sa; type b : sb; type g : sg; type r : sr; };

/** structure and prototype for BGRA image format */
#define PROTO_STRUCT_PIXEL_BGRA(name,type,sa,sb,sg,sr) \
	struct PIXEL_ ## name { type b : sb; type g : sg; type r : sr; type a : sa; }; 

/** structure and prototype for YUV image format */
#define PROTO_STRUCT_PIXEL_YUV(name,type,sa,sb,sg,sr) \
	struct PIXEL_ ## name { type b : sb; type g : sg; type r : sr; type a : sa; };

#pragma pack(push)
#pragma pack(1)

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

#pragma pack(pop)

#ifdef __cplusplus
};
#endif	/** extern "C" */

#endif	// __IMAGE_CONVERTER_PIXEL_INCLUDE_H_

// -----------------------------------------------------------------------------
// pixel.h - Last Change: $Date: 2012-05-15 23:36:52 $ - End Of File
// -----------------------------------------------------------------------------
