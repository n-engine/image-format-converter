/* 
 * image.c
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
 * $Log: image.c,v $
 *
 *
 *
 *
 *
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> // for memcpy
#include <math.h>

#include "define.h"
#include "image.h"

#include "tga.h"
#include "tiff.h"
#include "xpm.h"

int imageSave( const char* name, uchar* data, int w, int h, int fmt )
{
	int rc;

	if ( strstr(name,"tif") ) {
		printf("save tiff\n");
		rc = save_tiff( name, data, w, h, fmt );
	} else if ( strstr(name,"tga") ) {
		rc = save_tga( name, data, w, h, fmt );
	} else {
		printf("invalid format: %s\n", name);
	}

	return 1;
}

#if 0 // todo
int CreateExpanded(
    uchar* data, 
    uint width,
    uint height, uint bpp,
    uint iBorder)
{
	const uint w = width;
	const uint h = height;
	const uint W = iBorder + w + iBorder;
	const uint H = iBorder + h + iBorder;

	// create the new image
	boost::shared_ptr< ImageImpl<Pixel> > spImage(new ImageImpl<Pixel>(W,H));
	if (!elxUseable(spImage.get())) 
		return boost::shared_ptr< ImageImpl<Pixel> >();

	Pixel bg = Pixel::Black();
	const Pixel * prSrc = iImage.GetPixel();
	Pixel * prDst = spImage->GetPixel();
	const uint32 byteLineSize = iImage.sizeofWidth();

	uint32 i,j;
	// fill top with background
	for (j=0; j<iBorder; j++) 
		for (i=0; i<W; i++) 
			*prDst++ = bg;

	// fill central
	for (j=0; j<h; j++) 
	{
		// fill left with background
		for (i=0; i<iBorder; i++) 
			*prDst++ = bg;

		// fill medium with src image
		::memcpy(prDst, prSrc, byteLineSize);
		prSrc += w;
		prDst += w;

		// fill right with background
		for (i=0; i<iBorder; i++) 
		*prDst++ = bg;
	}

	// fill bottom with background
	for (j=0; j<iBorder; j++) 
		for (i=0; i<W; i++) 
			*prDst++ = bg;

	return 1;
}
#endif	// 0

// -----------------------------------------------------------------------------
// image.c - Last Change: $Date: 2012-05-15 23:36:52 $ - End Of File
// -----------------------------------------------------------------------------
