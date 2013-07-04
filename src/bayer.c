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

/*static uchar* load_raw( struct Bayer_t* in )
{
	FILE* fp = fopen();
}*/

struct pixel_rgb888_t {
	uchar r,g,b;
};

static void do_nearest( struct Bayer_t* in, uchar* data )
{
	const uint w = in->width;
	const uint h = in->height;
	const uint hHalf = h / 2;
	const uint wHalf = w / 2;
	const uint w2 = 2*w;

	pixel_rgb888_t *prDst, * prDstV = data;
	const ushort * prSrc, * prSrcV = (ushort)in->data;

	uint x,y;
	ushort r,g0,g1,b;

	#define CLEAN_PIXEL() \
		printf("todo: clean pixel\n");

	switch (in->bayer)
	{
    case eBGGR:
      for (y=0; y<hHalf; y++, prSrcV+=w2, prDstV+=w2)
      {
        prSrc = prSrcV;
        prDst = prDstV;
        for (x=0; x<wHalf; x++, prSrc+=2, prDst+=2)
        {
          //  B  G0
          //  G1 R
          b  = prSrc[0];  g0 = prSrc[  1];
          g1 = prSrc[w];  r  = prSrc[w+1];

          CLEAN_PIXEL();

          prDst[  0].r = r; prDst[  0].g = g1; prDst[  0].b = b;
          prDst[  1].r = r; prDst[  1].g = g0; prDst[  1].b = b;
          prDst[w  ].r = r; prDst[w  ].g = g1; prDst[w  ].b = b;
          prDst[w+1].r = r; prDst[w+1].g = g0; prDst[w+1].b = b;
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

          CLEAN_PIXEL();

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

          CLEAN_PIXEL();

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

          CLEAN_PIXEL();

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

static enum BayerType getBayerLeft(enum BayerType bayer)  { return _bayerLeftOrRight[bayer]; }
static enum BayerType getBayerRight(enum BayerType bayer) { return _bayerLeftOrRight[bayer]; }

static void do_nearest( struct Bayer_t* in, uchar* data )
{
	const uint w = in->width;
	const uint h = in->height;
	const uint border = 1;
	const int w1 = int(border+w+border);

	// Create a copy of input image expanded with border black pixels on each sides
	//boost::shared_ptr< ImageImpl< PixelL<T> > > spImageL =
	//	ImageGeometryImpl< PixelL<T> >::CreateExpanded(iImage, border);
	// Create output ImageRGB<T> image
	//boost::shared_ptr< ImageImpl< pixel_rgb888_t > >
	//	spImageRGB( new ImageImpl< pixel_rgb888_t >(w,h, pixel_rgb888_t::Black()) );

	enum BayerType Bayer;
	enum BayerType iBayer = in->bayer;

	uint x,y;
	ushort r1,r2,r3,r4, g1,g2,g3,g4, b1,b2,b3,b4;

	ushort *prSrc, *prSrcV = (ushort*)in->data; // spImageL->GetPixel(border,border);
	pixel_rgb888_t* prDst, * prDstV = data;

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

uchar* convert_to_rgb888( struct Bayer_t* in )
{
	// todo: add verif : size, width, height 
	// type, etc..

	uchar* data = malloc( in->width * in->height * 3 );

	 switch( in->btype )
	 {
	 	case eNEAREST:
	 		do_nearest(in, data);
	 	break;
	 }
	 
	 return data;
}

// -----------------------------------------------------------------------------
// bayer.c - Last Change: $Date: 2012-05-15 23:36:52 $ - End Of File
// -----------------------------------------------------------------------------
