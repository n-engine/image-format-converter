/* 
 * xpm.cxx
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
 * $Log: xpm.cxx,v $
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

struct Color {
	int key;
	uchar color[4];
};


static uchar* load_xpm_internal( char **src, int *width, int *height )
{
	int num_colors = 0;
	int chars_per_pixel = 0;
	int i,y,x,j;

	if(sscanf(*src++,"%d %d %d %d",width,height,&num_colors,&chars_per_pixel) != 4)
	{
		fprintf( stderr, "load_xpm_internal(): wrong format \"%s\"\n", *src );
		return 0;
	}

	struct Color *colors = (struct Color*)malloc( sizeof(struct Color) * num_colors );

	for(i = 0; i < num_colors; ++i)
	{
		char *s = *src++;
		int key = 0;
		int j;
		for(j = 0; j < chars_per_pixel; ++j)
		{
			key = key * 128 + *s++;
		}
		colors[i].key = key;
		colors[i].color[0] = 0;
		colors[i].color[1] = 0;
		colors[i].color[2] = 0;
		colors[i].color[3] = 0;

		while(*s == ' ' || *s == '\t')
			s++;

		if(*s++ != 'c')
		{
			fprintf(stderr,"load_xpm_internal(): unknown color key '%s'\n",s);
			continue;
		}

		while(*s == ' ' || *s == '\t')
			s++;
		if(!strcmp(s,"None"))
		{
			// nop
		}
		else if(*s == '#')
		{
			int r,g,b;
			sscanf(s,"#%2x%2x%2x",&r,&g,&b);
			colors[i].color[0] = r;
			colors[i].color[1] = g;
			colors[i].color[2] = b;
			colors[i].color[3] = 255;
		}
		else
		{
			fprintf(stderr,"load_xpm_internal(): unknown color \"%s\"\n",s);
		}
	}

	uchar *data = (uchar*)malloc( sizeof(uchar) * *width * *height * 4 );

	memset(data, 0, sizeof(uchar) * *width * *height * 4);

	for(y = 0; y < *height; ++y)
	{
		char *s = *src++;
		uchar *d = &data[*width * y * 4];
		for(x = 0; x < *width; ++x)
		{
			int key = 0;
			for(j = 0; j < chars_per_pixel; ++j)
			{
				key = key * 128 + *s++;
			}
			struct Color *c = 0;
			for(i = 0; i < num_colors; ++i)
			{
				if(colors[i].key == key)
				{
					c = &colors[i];
					break;
				}
			}
			if(c != 0)
			{
				*d++ = c->color[0];
				*d++ = c->color[1];
				*d++ = c->color[2];
				*d++ = c->color[3];
			}
		}
	}
	
	return data;
}

uchar* load_xpm( const char *name, int *width, int *height )
{
	FILE *file = fopen(name,"rb");
	char **dest;
	char *d;
	int bracket = 0, i;
	char buf[1024];
	int num_lines = 0;
	int length = 0;
	int max_length = 0;
	char **src;
	uchar *data;

	if ( !file )
	{
		fprintf(stderr,"load_xpm(): can't open \"%s\" file\n",name);
		return 0;
	}

	fread(buf,strlen("/* XPM */"),1,file);

	if(strncmp(buf,"/* XPM */",strlen("/* XPM */")))
	{
		fprintf(stderr,"load_xpm(): wrong header in \"%s\" file\n",name);
		fclose(file);
		return 0;
	}

	while ( 1 )
	{
		char c = fgetc(file);
		if(c == EOF)
			break;

		if(c == '"')
		{
			num_lines++;

			if ( max_length < length )
				max_length = length;

			length = 0;
		}
		else
		{
			length++;
		}
	}

	num_lines = num_lines / 2 + 1;
	max_length += 1;

	src = (char**)malloc( sizeof(char*) * num_lines );

	for(i = 0; i < num_lines; ++i)
	{
		src[i] = (char*)malloc( sizeof(char) * max_length );
		memset(src[i],0,sizeof(char) * max_length);
	}

	fseek(file,0,SEEK_SET);
	dest = src;
	d = *dest++;

	while(1)
	{
		char c = fgetc(file);

		if(c == EOF)
			break;

		if(c == '"')
		{
			if(bracket == 0)
			{
				bracket = 1;
			}
			else if(bracket == 1)
			{
				bracket = 0;
				d = *dest++;
			}
		}
		else if(bracket == 1)
		{
			*d++ = c;
		}
	}

	data = load_xpm_internal( src, width, height );

	for( i = 0; i < num_lines; ++i )
	{
		KILLARRAY( src[i] );
	}

	KILLARRAY( src );

	fclose( file );

	return data;
}

// -----------------------------------------------------------------------------
// xpm.cxx - Last Change: $Date: 2012-05-15 23:36:52 $ - End Of File
// -----------------------------------------------------------------------------
