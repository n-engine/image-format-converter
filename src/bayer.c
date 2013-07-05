/* 
 * bayer.c
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
 * $Log: bayer.c,v $
 *
 *
 *
 *
 * Note: code shamesly taken from eLynx SDK :
 *
 *  Copyright (C) 2006 by eLynx project
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU Library General Public License for more details.
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
#include "bayer.h"

#include "tga.h"

#define CLEAN_PIXEL(r,g0,g1,b)		\
	/* clip pixel value */	\
	r &= mask, g0 &= mask, g1 &= mask, b &= mask; \
	/* convert to 8 bits */  \
	r >>= (in->bpp - 8), g0 >>= (in->bpp - 8), \
	g1 >>= (in->bpp - 8), b >>= (in->bpp - 8);

typedef struct pixel_rgb888_t {
	uchar r,g,b;
} pixel_rgb888_t;

uint getPixelSize( enum PixelType type )
{
	switch(type)
	{
		case eU8: return 1;
		case eU16: return 2;
		case eINT32: return 4;
		case eFLOAT:
		case eDOUBLE: return 8;
	}

	return 0;
}

static void do_nearest( struct Bayer_t* in, uchar* data )
{
	const uint w = in->width;
	const uint h = in->height;
	const uint hHalf = h / 2;
	const uint wHalf = w / 2;
	const uint w2 = 2*w;
	int mask = (1 << in->bpp) - 1;

	pixel_rgb888_t *prDst, *prDstV;
	const ushort *prSrc, *prSrcV;

	uint x,y;
	ushort r,g0,g1,b;

	prSrcV = (ushort*)in->data_16;
	prDstV = (pixel_rgb888_t*)data;

	printf("nearest: %d\n", in->bayer);

	switch (in->bayer)
	{
    case eBGGR:
    	printf("nearest: bggr\n");
     for ( y=0; y < hHalf; y++, prSrcV += w2, prDstV += w2 )
		{
			prSrc	= prSrcV;
			prDst	= prDstV;
			for ( x=0; x < wHalf; x++, prSrc += 2, prDst += 2 )
			{
				//  B  G0
				//  G1 R
				b  = prSrc[0];  g0 = prSrc[  1];
				g1 = prSrc[w];  r  = prSrc[w+1];

				CLEAN_PIXEL(r,g0,g1,b);

				prDst[  0 ].r = r; prDst[  0 ].g = g1; prDst[  0 ].b = b;
				prDst[  1 ].r = r; prDst[  1 ].g = g0; prDst[  1 ].b = b;
				prDst[w   ].r = r; prDst[w   ].g = g1; prDst[w   ].b = b;
				prDst[w+1 ].r = r; prDst[w+1 ].g = g0; prDst[w+1 ].b = b;
			}
		}
      break;

    case eGRBG:
      for (y=0; y<hHalf; y++, prSrcV+=w2, prDstV+=w2)
      {
        prSrc = prSrcV;
        prDst = prDstV;
        for (x=0; x<wHalf; x++, prSrc+=2, prDst+=2)
        {
          //  G0 R
          //  B  G1
          g0 = prSrc[0];  r  = prSrc[  1];
          b  = prSrc[w];  g1 = prSrc[w+1];

          CLEAN_PIXEL(r,g0,g1,b);

          prDst[  0].r = r; prDst[  0].g = g0; prDst[  0].b = b;
          prDst[  1].r = r; prDst[  1].g = g1; prDst[  1].b = b;
          prDst[w  ].r = r; prDst[w  ].g = g0; prDst[w  ].b = b;
          prDst[w+1].r = r; prDst[w+1].g = g1; prDst[w+1].b = b;
        }
      }
      break;

    case eGBRG:
      for (y=0; y<hHalf; y++, prSrcV+=w2, prDstV+=w2)
      {
        prSrc = prSrcV;
        prDst = prDstV;
        for (x=0; x<wHalf; x++, prSrc+=2, prDst+=2)
        {
          //  G0 B
          //  R  G1
          g0 = prSrc[0];  b  = prSrc[  1];
          r  = prSrc[w];  g1 = prSrc[w+1];

          CLEAN_PIXEL(r,g0,g1,b);

          prDst[  0].r = r; prDst[  0].g = g0; prDst[  0].b = b;
          prDst[  1].r = r; prDst[  1].g = g1; prDst[  1].b = b;
          prDst[w  ].r = r; prDst[w  ].g = g0; prDst[w  ].b = b;
          prDst[w+1].r = r; prDst[w+1].g = g1; prDst[w+1].b = b;
        }
      }
      break;

    case eRGGB:
      for (y=0; y<hHalf; y++, prSrcV+=w2, prDstV+=w2)
      {
        prSrc = prSrcV;
        prDst = prDstV;
        for (x=0; x<wHalf; x++, prSrc+=2, prDst+=2)
        {
          //  R  G0
          //  G1 B
          r  = prSrc[0];  g0 = prSrc[  1];
          g1 = prSrc[w];  b  = prSrc[w+1];

          CLEAN_PIXEL(r,g0,g1,b);

          prDst[  0].r = r; prDst[  0].g = g1; prDst[  0].b = b;
          prDst[  1].r = r; prDst[  1].g = g0; prDst[  1].b = b;
          prDst[w  ].r = r; prDst[w  ].g = g1; prDst[w  ].b = b;
          prDst[w+1].r = r; prDst[w+1].g = g0; prDst[w+1].b = b;
        }
      }
      break;

    default:break;
  }
}

static enum BayerType _bayerLeftOrRight[5] =
  // BM_None    BM_GRBG    BM_GBRG   BM_RGGB   BM_BGGR
  // +-+-+      +-+-+      +-+-+     +-+-+     +-+-+
  // |L|L|      |G|R|      |G|B|     |R|G|     |B|G|
  // |L|L|      |B|G|      |R|G|     |G|B|     |G|R|
  // +-+-+      +-+-+      +-+-+     +-+-+     +-+-+
  { eNONE,      eRGGB,     eBGGR,    eGRBG,    eGBRG };

//static enum BayerType getBayerLeft(enum BayerType bayer)  { return _bayerLeftOrRight[bayer]; }
static enum BayerType getBayerRight(enum BayerType bayer) { return _bayerLeftOrRight[bayer]; }

static enum BayerType _bayerUpOrDown[5] =
  // None     GRBG     GBRG    RGGB    BGGR
  // +-+-+    +-+-+    +-+-+   +-+-+   +-+-+
  // |L|L|    |G|R|    |G|B|   |R|G|   |B|G|
  // |L|L|    |B|G|    |R|G|   |G|B|   |G|R|
  // +-+-+    +-+-+    +-+-+   +-+-+   +-+-+
  { eNONE,    eBGGR,   eRGGB,  eGBRG,  eGRBG };
 
static inline enum BayerType getBayerUp(enum BayerType bayer)    { return _bayerUpOrDown[bayer]; }
static inline enum BayerType getBayerDown(enum BayerType bayer)  { return _bayerUpOrDown[bayer]; }

static ushort* getPixel(uchar* data, uint w, uint iX, uint iY)
{
	// clip pixel location
	//if ((iX >= width) || (iY >= height) || (NULL == data))
	//	return NULL;
	ushort* prPixel = (ushort*) data + iX + iY*w;
	return prPixel;
}

static void do_bilinear( struct Bayer_t* in, uchar* data )
{
	const uint w = in->width;
	const uint h = in->height;
	const uint border = 1;
	const int w1 = (int)(border+w+border);
	enum BayerType Bayer;
	enum BayerType iBayer = in->bayer;

	uint x,y;
	ushort r1,r2,r3,r4, g1,g2,g3,g4, b1,b2,b3,b4;

	ushort *prSrc, *prSrcV;
	pixel_rgb888_t* prDst, *prDstV;

	int mask = (1 << in->bpp) - 1;

	// TODO: create an expanded imagr from source wich replace original source

	// Create a copy of input image expanded with border black pixels on each sides
	//boost::shared_ptr< ImageImpl< PixelL<T> > > spImageL =
	//	ImageGeometryImpl< PixelL<T> >::CreateExpanded(iImage, border);
	// Create output ImageRGB<T> image
	//boost::shared_ptr< ImageImpl< pixel_rgb888_t > >
	//	spImageRGB( new ImageImpl< pixel_rgb888_t >(w,h, pixel_rgb888_t::Black()) );

	prSrcV = getPixel( in->data, in->width, border, border ); // (ushort*)in->data_16;
	prDstV = (pixel_rgb888_t*)data;

	printf("do_bilinear(): w1: %d\n", w1);

	for (y=0; y<h; y++, prSrcV+=w1, prDstV+=w)
	{
		prSrc = prSrcV;
		prDst = prDstV;
		Bayer = iBayer;
		for (x=0; x<w; x++, prSrc++, prDst++)
		{
		  switch (Bayer)
		  {
		    case eBGGR:
		      // R1  G1  R2
		      // G2 [B ] G3
		      // R3  G4  R4
		      r1 = prSrc[-w1-1];  g1 = prSrc[-w1]; r2 = prSrc[-w1+1];
		      g2 = prSrc[   -1];                   g3 = prSrc[   +1];
		      r3 = prSrc[+w1-1];  g4 = prSrc[+w1]; r4 = prSrc[+w1+1];

		      CLEAN_PIXEL(r1,g1,r2,g2);
		      CLEAN_PIXEL(g3,r3,g4,r4);
		      
		      prDst->r  = (r1 + r2 + r3 + r4) / 4;
		      prDst->g = (g1 + g2 + g3 + g4) / 4;
		      prDst->b = prSrc[0];
		      
		      break;
		
		    case eGBRG:
		      // G   R1  G
		      // B1 [G ] B2
		      // G   R2  G
		                     r1 = prSrc[-w1];  
		      b1 = prSrc[-1];                b2 = prSrc[+1];
		                     r2 = prSrc[+w1];

			  CLEAN_PIXEL(r1,b1,b2,r2);
		
		      prDst->r = (r1 + r2) / 2;
		      prDst->g = prSrc[0];
		      prDst->b = (b1 + b2) / 2;
		      break;
		
		    case eGRBG:
		      // G   B1  G
		      // R1 [G ] R2
		      // G   B2  G
		                      b1 = prSrc[-w1];
		      r1 = prSrc[-1];                  r2 = prSrc[+1];
		                      b2 = prSrc[+w1];

			  CLEAN_PIXEL(b1,r1,r2,b2);

		      prDst->r = (r1 + r2) / 2;
		      prDst->g = prSrc[0];
		      prDst->b = (b1 + b2) / 2;
		      break;
		
		    default: // eRGGB:
		      // B1  G1  B2
		      // G2 [R ] G3
		      // B3  G4  B4
		      b1 = prSrc[-w1-1];  g1 = prSrc[-w1];  b2 = prSrc[-w1+1];
		      g2 = prSrc[   -1];                    g3 = prSrc[   +1];
		      b3 = prSrc[+w1-1];  g4 = prSrc[+w1];  b4 = prSrc[+w1+1];

			  CLEAN_PIXEL(b1,g1,b2,g2);
			  CLEAN_PIXEL(g3,b3,g4,b4);

		      prDst->r = prSrc[0];
		      prDst->g = (g1 + g2 + g3 + g4) / 4;
		      prDst->b = (b1 + b2 + b3 + b4) / 4;
		      break;
		  }
		  Bayer = getBayerRight(Bayer);
		}
		iBayer = getBayerDown(iBayer);
	}
}

int convert_to_rgb888( struct Bayer_t* in, uchar* out )
{
	if (!in) {
		fprintf( stderr, "Invalid pointer.\n" );
		return -1;
	}

	if ( !out || in->size < 0 || in->width < 0 || in->height < 0 ||
		in->bayer >= eBAYER_LAST )
	{
		fprintf( stderr, "Invalid data filled in pointer.\n" );
		return -1;
	}

	switch( in->method )
	{
		case eNEAREST:
			do_nearest(in, out);
		break;
		case eBILINEAR:
			do_bilinear(in, out);
		break;
		default:
			// todo
			fprintf( stderr,
				"TODO: Do other method for demosaicing - method: %d\n",
				in->method );
		break;
	}

	 return 0;
}

static int load_raw( const char* file, uint size, uchar* dst )
{
	int rc;
	FILE* fp;

	fp = fopen( file, "rb" );

	if(!fp) {
		fprintf(stderr, "Can't load : %s\n", file );
		return -1;
	}

	rc = fread( dst, 1, size, fp );

	fclose(fp);

	// fprintf( stderr, "file loaded: %d - wanted: %d\n", rc, dst->size );

	return 0;
}

/**
 *	loader for RAW Bayer
 */
int bayer_to_image(
	enum BayerType type,
	int bpp,
	int w,
	int h,
	enum MethodName method,
	const char* fileIn,
	const char* fileOut)
{
	int rc;
	uchar* data;
	struct Bayer_t dst;

	int psz		= 2;
	dst.width	= w;
	dst.height	= h;
	dst.bayer	= type;
	dst.bpp		= bpp;
	dst.ptype	= eU16;
	dst.method	= method;
	dst.size	= dst.width * dst.height * psz;

	printf("Bayer type: %d\n", type);

	dst.data	= malloc( dst.size );
	data		= malloc( dst.width * dst.height * 3 );

	memset( dst.data, 0, dst.size );
	memset( data, 0, dst.width * dst.height * 3 );

	rc = load_raw( fileIn, dst.size, dst.data );

	if ( rc < 0 )
		goto _error;

	// demosaicing using method 'method'
	rc = convert_to_rgb888( &dst, data );

	if ( rc < 0 ) {
		fprintf( stderr, "Can't convert to rgb888\n" );
	}

	/** store to image */
	rc = imageSave( fileOut, data, w, h, RGB888 );

	if ( rc != 1 ) {
		fprintf( stderr, "Can't save to tga: %s\n", fileOut );
	}

_error:
	if (dst.data) {
		free( dst.data );
		dst.data = 0;
	}

	if (data) {
		free( data );
		data = 0;
	}

	return 0;
}

// -----------------------------------------------------------------------------
// bayer.c - Last Change: $Date: 2012-05-15 23:36:52 $ - End Of File
// -----------------------------------------------------------------------------
