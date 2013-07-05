/* 
 * tiff.h
 *
 * Copyright 2011-2013 ESTEVE Olivier <naskel .[.at.]. gmail.com>
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
 * $Log: tiff.h,v $
 *
 *
 *
 *
 *
 *
 * 
 * 
 */
#ifndef __IMAGE_CONVERTER_TIFF_INCLUDE_H_
#define __IMAGE_CONVERTER_TIFF_INCLUDE_H_

#ifdef __cplusplus
extern "C" {
#endif	/** extern "C" */

int save_tiff( const char *name, const uchar *data, const int width, const int height, const int fmt );

#ifdef __cplusplus
};
#endif	/** extern "C" */

#endif	// __IMAGE_CONVERTER_TGA_INCLUDE_H_

// -----------------------------------------------------------------------------
// tga.h - Last Change: $Date: 2012-05-15 23:36:52 $ - End Of File
// -----------------------------------------------------------------------------
