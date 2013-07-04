/* 
 * fnc.h
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
 * $Log: fnc.h,v $
 *
 *
 *
 *
 *
 *
 * 
 * 
 */
#ifndef __IMAGE_CONVERTER_FNC_INCLUDE_H_
#define __IMAGE_CONVERTER_FNC_INCLUDE_H_

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif	/** extern "C" */

#define ARRAY_SIZE(a)		(sizeof(a) / sizeof((a)[0]))

#define IS_NUM(x) (x>=48 && x<=57)


#define BASE_ENUM	1

#if defined(_DEBUG)
	#define TRACE_DEBUG				printf
#else
	#define TRACE_DEBUG(...)		
#endif

#define RGB_NOT_SET				( !IS_RGBA(id) && !IS_BGRA(id) && !IS_RGB(id) && !IS_BGR(id) && !IS_ABGR(id) )

#define R(x,fmt)				x[fmt[0]]
#define G(x,fmt)				x[fmt[1]]
#define B(x,fmt)				x[fmt[2]]
#define A(x,fmt)				x[fmt[3]]
#define IS_RGBA(x)				(x[4]==FMT_RGBA)
#define IS_ABGR(x)				(x[4]==FMT_ABGR)
#define IS_ARGB(x)				(x[4]==FMT_ARGB)
#define IS_BGRA(x)				(x[4]==FMT_BGRA)
#define IS_RGB(x)				(x[4]==FMT_RGB)
#define IS_BGR(x)				(x[4]==FMT_BGR)
#define GET_FMT(x)				x[4]
#define HAS_ALPHA(x)			(x[5])
#define SET_FMT(x,fmt,alpha)	{x[4]=fmt; x[5]=alpha;}
#define BOTH_ALPHA(a,b)			(HAS_ALPHA(a)&&HAS_ALPHA(b))

// same RGBA
#define SAME_NUM(a,b)			((BOTH_ALPHA(a,b)&&(R(a,af)==R(b,bf)&&G(a,af)==G(b,bf)&&B(a,af)==B(b,bf)&&A(a,af)==A(b,bf))))

// has alpha, and rgb must not be equal
#define ALPHA_NOT_SAME_RGB(a,b)		((BOTH_ALPHA(a,b)&&(R(a,af)!=R(b,bf)&&G(a,af)!=G(b,bf)&&B(a,af)!=B(b,bf))))

// same RGB but not alpha but both must have alpha
#define SAME_NUM_BUT_ALPHA(a,b)	( BOTH_ALPHA(a,b) && \
								(R(a,af)==R(b,bf)&&G(a,af)==G(b,bf)&&B(a,af)==B(b,bf)) )

// same alpha
#define SAME_ALPHA(a,b)			( BOTH_ALPHA(a,b) && (A(a,af)==A(b,bf)) )

// same RGB and dest doesnt have alpha
#define SAME_NUM_NO_DEST_ALPHA(a,b)	( HAS_ALPHA(a) && !HAS_ALPHA(b) && \
								(R(a,af)==R(b,bf)&&G(a,af)==G(b,bf)&&B(a,af)==B(b,bf)) )

// dest have a bigger alpha value
#define DEST_BIGGER_ALPHA(a,b)	(BOTH_ALPHA(a,b) && (A(b,bf) > A(a,af)))

// src have a bigger alpha value
#define SRC_BIGGER_ALPHA(a,b)	(BOTH_ALPHA(a,b) && (A(a,af) > A(b,bf)))

#define EQUAL_ALPHA(x,a,alpha)	(A(x,a)==alpha)

// same Red and Blue
#define SAME_R(a,b)				( R(a,af) == R(b,bf) )
#define SAME_G(a,b)				( G(a,af) == G(b,bf) )
#define SAME_B(a,b)				( B(a,af) == B(b,bf) )
#define SAME_A(a,b)				( A(a,af) == A(b,bf) )

#define SAME_RB(a,b)			( SAME_R(a,b) && SAME_B(a,b) )

#define SAME_RGB(a,b)			( SAME_R(a,b) && SAME_G(a,b) && SAME_G(a,b) )

// same Red and Blue green must not be equal
#define SAME_RB_ONLY(a,b)		( R(a,af)==R(b,bf) && B(a,af)==B(b,bf) && G(a,af)!=G(b,bf) )


enum {
	FMT_RGBA=BASE_ENUM,
	FMT_ABGR,
	FMT_ARGB,
	FMT_BGRA,
	FMT_RGB,
	FMT_BGR
};

typedef void (*fnc_process)( const char* from, const char* to, int* s, int* d, int* af, int* bf );

/** */
void check_id( const char* str, int* id );

/** */
void get_fmt( int* id, int* fmt );

/** */
const char* fmt_str( int* id );

/** */
void debug_fmt( int* id, int* fmt );

/** */
void process( const char* from, const char* to, int* s, int* d, int* af, int* bf );

/** */
void generate_function( const char* from, const char* to );

/** */
void generate_all(void);

/** */
void gen_table( uint a, uint b );

#ifdef __cplusplus
};
#endif	/** extern "C" */

#endif	// __IMAGE_CONVERTER_FNC_INCLUDE_H_

// -----------------------------------------------------------------------------
// fnc.h - Last Change: $Date: 2012-05-15 23:36:52 $ - End Of File
// -----------------------------------------------------------------------------
