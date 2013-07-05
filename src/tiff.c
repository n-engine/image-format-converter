/* 
 * tiff.c
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
 * $Log: tiff.c,v $
 *
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

// require libtiff

#include "define.h"
#include "pixel.h"
#include "tiff.h"

#include <tiffio.h>


static int write_tiff_raw(const char *fname, const uint *data_tiff,
							   uint nx, uint ny, int bpp, int spp, uint compression)
{
	TIFF *tiffp = NULL;
	size_t size;

	/*
	 * ensure the data is allocated
	 * and the width and height are within the limits
	 * (tiff uses uint32, 2^32 - 1 = 4294967295)
	 * and open the TIFF file and structure
	 */
	if (NULL == data_tiff
		|| 4294967295. < (double) nx || 4294967295. < (double) ny) {
		printf("Invalid size: %d x %d\n", nx, ny );
		return -1;
	}
	size = nx * ny;
	
	/* no warning messages */
	(void) TIFFSetWarningHandler( NULL );
	
	/* open the TIFF file and structure */
	if (NULL == (tiffp = TIFFOpen(fname, "w"))) {
		printf("cant open filename: %s for writing\n", fname );
		return -1;
	}
	
	/* insert tags into the TIFF structure */
	if (1 != TIFFSetField(tiffp, TIFFTAG_IMAGEWIDTH, nx)
		|| 1 != TIFFSetField(tiffp, TIFFTAG_IMAGELENGTH, ny)
		|| 1 != TIFFSetField(tiffp, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT)
		|| 1 != TIFFSetField(tiffp, TIFFTAG_BITSPERSAMPLE, bpp)
		|| 1 != TIFFSetField(tiffp, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG)
		|| 1 != TIFFSetField(tiffp, TIFFTAG_ROWSPERSTRIP, ny)
		|| 1 != TIFFSetField(tiffp, TIFFTAG_SAMPLESPERPIXEL, spp)
		|| 1 != TIFFSetField(tiffp, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB)
		|| 1 != TIFFSetField(tiffp, TIFFTAG_COMPRESSION, compression))
	{
		TIFFClose(tiffp);
		printf("Cant set field\n");
		return -1;
	}

	// tsize_t TIFFWriteEncodedStrip(TIFF *tif, tstrip_t strip, tdata_t buf, tsize_t size)
	// tsize_t TIFFWriteRawStrip    (TIFF *tif, tstrip_t strip, tdata_t buf, tsize_t size)

	/* write the image as one single strip */
	if ((spp*size) != (uint)
		TIFFWriteEncodedStrip(tiffp, (tstrip_t) 0, (tdata_t) data_tiff,
							  (tsize_t) (spp * size)))
	{
		TIFFClose(tiffp);
		printf("Cant encode strip\n");
		return -1;
	}

	/* free the TIFF structure and data, return success */
	TIFFClose( tiffp );

	return 0;
}

int save_tiff( const char *name, const uchar *data, const int width, const int height, const int fmt )
{
	int rc;

	printf( "save_tiff: %s\n", name );

	if ( (fmt != RGBA8888) && (fmt != BGRA8888) && 
		(fmt != RGB888) && (fmt != BGR888) ) {
		fprintf(stderr, "unknown format : %d\n", fmt);
		return 0;
	}

	rc = write_tiff_raw(
		name, (const uint*)data,
		width, height, 8, 3, COMPRESSION_LZW
	);

	if ( rc != 0 )
	{
		printf( "Can't save tiff image: %s\n", name );
	}

	return 1;
}

// -----------------------------------------------------------------------------
// tiff.c - Last Change: $Date: 2012-05-15 23:36:52 $ - End Of File
// -----------------------------------------------------------------------------
