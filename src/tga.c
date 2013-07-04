/* 
 * tga.c
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
 * $Log: tga.c,v $
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

#include "define.h"
#include "tga.h"

int save_tga( const char *name, const uchar *data, const int width, const int height )
{
	int i, size;
	uchar *buf;
	struct tga_header header;
	FILE *file = fopen(name,"wb");

	if(!file) {
		fprintf( stderr,"save_tga(): error create \"%s\" file\n", name );
		return 0;
	}

	fast_memset( &header,0,sizeof(header) );

	header.image_type	= 2;
	header.width		= width;
	header.height		= height;
	header.pixel_size	= 32;
	header.attributes	= 0x28;

	fwrite( &header, 1, sizeof(header), file );

	// rgba->bgra
	size = width * height * 4;
	buf = (uchar*)malloc(sizeof(uchar)*size);

	for( i = 0; i < size; i += 4) {
		buf[i + 0] = data[i + 2];
		buf[i + 1] = data[i + 1];
		buf[i + 2] = data[i + 0];
		buf[i + 3] = data[i + 3];
	}

	fwrite(buf,sizeof(uchar),size,file);

	free(buf);

	fclose(file);
	
	return 1;
}

// -----------------------------------------------------------------------------
// tga.cxx - Last Change: $Date: 2012-05-15 23:36:52 $ - End Of File
// -----------------------------------------------------------------------------
