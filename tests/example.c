/* 
 * example.c
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
 * $Log: example.c,v $
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
#include <sys/stat.h>
#include <sys/types.h>

#include "define.h"
#include "converter.h"
#include "xpm.h"
#include "tga.h"

#include "bayer.h"

#define ARRAY_SIZE(a)		(sizeof(a) / sizeof((a)[0]))

// this struct is for example only (this is not really needed)
struct ImageStr {
	const char* name;
	const int id;
} __img_str[] = {
	{ "RGB444", RGB444 },
	{ "RGBA4441", RGBA4441 },
	{ "RGBA4444", RGBA4444 },
	{ "RGB555", RGB555 },
	{ "RGBA5551", RGBA5551 },
	{ "RGB565", RGB565 },
	{ "RGB888", RGB888 },
	{ "RGBA8888", RGBA8888 },
	{ "BGR444", BGR444 },
	{ "ABGR1444", ABGR1444 },
	{ "ABGR4444", ABGR4444 },
	{ "BGR555", BGR555 },
	{ "ABGR1555", ABGR1555 },
	{ "BGR565", BGR565 },
	{ "BGR888", BGR888 },
	{ "ABGR8888", ABGR8888 },
	{ "BGRA4441", BGRA4441 },
	{ "BGRA4444", BGRA4444 },
	{ "BGRA5551", BGRA5551 },
	{ "BGRA8888", BGRA8888 },
	{ "RGB332", RGB332 },
	{ "BGR332", BGR332 },
	{ "RGBA5542", RGBA5542 },
	{ "ABGR2554", ABGR2554 },
	{ "RGBA6661", RGBA6661 },
	{ "ABGR1666", ABGR1666 },
	{ "RGBA6666", RGBA6666 },
	{ "ABGR6666", ABGR6666 },
	{ "RGB666", RGB666 },
	{ "BGR666", BGR666 },
	{ "RGBA5658", RGBA5658 },
	{ "ABGR8565", ABGR8565 },
	{ "YV12", YV12 },
	{ "I420", I420 },
	{ "NV12", NV12 },
	{ "Y41P", Y41P },
	{ "Y411", Y411 },
	{ "YUY2", YUY2 },
	{ "UYVY", UYVY },
	{0,0}
};

static void convert( const uchar* src, const int from, const int w, const int h )
{
	int i;
	char str[256];

	uchar* dst = (uchar*)malloc(sizeof(uchar) * w * h * 4 );
	uchar* data = (uchar*)malloc(sizeof(uchar) * w * h * 4 );

	for(i = 0; i < ARRAY_SIZE(__img_str); ++i)
	{
		const int to = __img_str[i].id;

		if ( !__img_str[i].name )
			break;

		if ( i == from )
			continue;

		sprintf(str, "output/from_%s_to_%s.tga", __img_str[from].name, __img_str[i].name );
		printf("Converting image from %s to %s\n", __img_str[from].name, __img_str[i].name );

		// convert from 'src format' to new format
		converter( (void*)src, dst, w, h, from, to );

		// convert back from new format to RGBA8888 (for saving to tga)
		if ( to != RGBA8888 )
		{
			converter( dst, data, w, h, to, RGBA8888 );

			// save data
			save_tga( str, data, w, h, RGBA8888 );
		}
		else
			save_tga( str, dst, w, h, RGBA8888 );
	}

	free(dst);
	free(data);
}

static uchar* load_lenna()
{
	const uint size = 482376;
	FILE* fp = fopen("samples/lenna_head_404x398.raw", "rb");
	if(!fp) return 0;
	uchar* buffer = (uchar*)malloc(sizeof(uchar) * size );
	fread(&buffer[0],1,1,fp); // header
	fread(buffer,1,size,fp); // data (RGB888)
	fclose(fp);
	return buffer;
}

static void do_convert()
{
	int w,h,i;
	int in_format;
	uchar* org;
	uchar* dst;

	mkdir("output",0777);

	// using the flow sample :
	//org = (uchar*)load_xpm( "samples/flower.xpm", w, h );
	//in_format = RGBA8888;

	// using lena raw :
	org = load_lenna();
	in_format = RGB888;
	w = 404, h = 398;

	if ( !org )
		return EXIT_FAILURE;

	/** handle sufficient space for all format (max == RGBA888) */
	dst = (uchar*)malloc(sizeof(uchar) * w * h * 4 );

	for ( i = 0; i < ARRAY_SIZE(__img_str); ++i )
	{
		if ( !__img_str[i].name )
			break;

		const int id = __img_str[i].id;

		// convert to new format
		converter( org, dst, w, h, in_format, id );

		// convert to all other format
		convert( dst, i, w, h );
	}

	free(org);
	free(dst);
}

void do_bayer() {
	#define DO_TEST_DEBAYER(method) \
		bayer_to_image( eBGGR, 10, 2048, 1028, \
			method, \
			"samples/sample.raw", \
			"output/sample_" # method ".tiff" \
		);
	DO_TEST_DEBAYER(eNEAREST);
	/*DO_TEST_DEBAYER(eBILINEAR);*/
}

#define DO_CONVERT	(1<<0)
#define DO_BAYER	(1<<1)

int main( int argc, char* argv[] )
{
	int run = 0;

	//run |= DO_CONVERT;
	run |= DO_BAYER;

	if ( run & DO_CONVERT ) do_convert();
	if ( run & DO_BAYER ) do_bayer();

	return EXIT_SUCCESS;
}

// -----------------------------------------------------------------------------
// example.c - Last Change: $Date: 2012-05-15 23:36:52 $ - End Of File
// -----------------------------------------------------------------------------
