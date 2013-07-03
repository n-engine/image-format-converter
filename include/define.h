/* 
 * define.h
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
 * $Log: define.h,v $
 *
 *
 *
 *
 *
 *
 * 
 * 
 */
#ifndef __IMAGE_CONVERTER_DEFINE_INCLUDE_H_
#define __IMAGE_CONVERTER_DEFINE_INCLUDE_H_

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

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

#endif	// __IMAGE_CONVERTER_DEFINE_INCLUDE_H_

// -----------------------------------------------------------------------------
// define.h - Last Change: $Date: 2012-05-15 23:36:52 $ - End Of File
// -----------------------------------------------------------------------------
