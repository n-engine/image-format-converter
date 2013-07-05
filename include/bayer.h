/* 
 * bayer.h
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
 * $Log: bayer.h,v $
 *
 *
 *
 *
 *
 *
 * 
 * 
 */
#ifndef __IMAGE_CONVERTER_BAYER_INCLUDE_H_
#define __IMAGE_CONVERTER_BAYER_INCLUDE_H_

#ifdef __cplusplus
extern "C" {
#endif	/** extern "C" */

enum PixelType
{
	eU8,
	eU16,
	eINT32,
	eFLOAT,
	eDOUBLE,
};

enum BayerType
{
	eNONE,
	eGRBG,
	eGBRG,
	eRGGB,
	eBGGR,
	
	eBAYER_LAST,
};

enum MethodName
{
	eADAMS,
	eAFFINE,
	eAHD,
	eAWD,
	eBALANCE,
	eBICUBIC,
	eBILINEAR,
	eBIN2X2,
	eNEAREST,
};

struct Bayer_t
{
	uint width;
	uint height;
	uint bpp;
	uint size;
	enum BayerType bayer;
	enum MethodName method;
	enum PixelType ptype;
	union {
		uchar *data;
		uchar *data_8;
		ushort *data_16;
		float* dataf;
		double* data_double;
	};
};

uint getPixelSize( enum PixelType type );

int convert_to_rgb888( struct Bayer_t* in, uchar* dst );

int bayer_to_image(
	enum BayerType type,
	int bpp,
	int w,
	int h,
	enum MethodName method,
	const char* fileIn,
	const char* fileOut);

#ifdef __cplusplus
};
#endif	/** extern "C" */

#endif	// __IMAGE_CONVERTER_BAYER_INCLUDE_H_

// -----------------------------------------------------------------------------
// bayer.h - Last Change: $Date: 2012-05-15 23:36:52 $ - End Of File
// -----------------------------------------------------------------------------
