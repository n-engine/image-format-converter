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

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

#define KILLARRAY(a)	if ( a ) { delete [] a ; a = 0; }

static uchar* load_xpm( char **src, int &width, int &height )
{
	int num_colors = 0;
	int chars_per_pixel = 0;

	if(sscanf(*src++,"%d %d %d %d",&width,&height,&num_colors,&chars_per_pixel) != 4)
	{
		fprintf( stderr, "load_xpm(): wrong format \"%s\"\n", *src );
		return 0;
	}
	
	struct Color {
		int key;
		uchar color[4];
	};

	Color *colors = new Color[num_colors];

	for(int i = 0; i < num_colors; ++i)
	{
		char *s = *src++;
		int key = 0;
		for(int j = 0; j < chars_per_pixel; ++j)
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
			fprintf(stderr,"load_xpm(): unknown color key '%s'\n",s);
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
			fprintf(stderr,"load_xpm(): unknown color \"%s\"\n",s);
		}
	}

	uchar *data = new uchar[width * height * 4];

	memset(data,0,sizeof(uchar) * width * height * 4);

	for(int y = 0; y < height; ++y)
	{
		char *s = *src++;
		uchar *d = &data[width * y * 4];
		for(int x = 0; x < width; ++x)
		{
			int key = 0;
			for(int j = 0; j < chars_per_pixel; ++j)
			{
				key = key * 128 + *s++;
			}
			Color *c = 0;
			for(int i = 0; i < num_colors; ++i)
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

uchar* load_xpm( const char *name, int &width, int &height )
{
	FILE *file = fopen(name,"rb");

	if ( !file )
	{
		fprintf(stderr,"load_xpm(): can't open \"%s\" file\n",name);
		return 0;
	}

	char buf[1024];
	fread(buf,strlen("/* XPM */"),1,file);

	if(strncmp(buf,"/* XPM */",strlen("/* XPM */")))
	{
		fprintf(stderr,"load_xpm(): wrong header in \"%s\" file\n",name);
		fclose(file);
		return 0;
	}

	int num_lines = 0;
	int length = 0;
	int max_length = 0;

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

	char **src = new char*[num_lines];

	for(int i = 0; i < num_lines; ++i)
	{
		src[i] = new char[max_length];
		memset(src[i],0,sizeof(char) * max_length);
	}

	fseek(file,0,SEEK_SET);

	char **dest = src;
	char *d = *dest++;
	int bracket = 0;

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

	uchar *data = load_xpm( src, width, height );

	for( int i = 0; i < num_lines; ++i )
	{
		KILLARRAY( src[i] );
	}

	KILLARRAY( src );

	fclose( file );

	return data;
}
