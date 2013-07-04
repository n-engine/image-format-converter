/* 
 * fnc.c
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
 * $Log: fnc.c,v $
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
#include "fnc.h"

static const char* all_formats[] = {
	"RGB444",
	"RGBA4441",
	"RGBA4444",
	"RGB555",
	"RGBA5551",
	"RGB565",
	"RGB888",
	"RGBA8888",
	"BGR444",
	"ABGR1444",
	"ABGR4444",
	"BGR555",
	"ABGR1555",
	"BGR565",
	"BGR888",
	"ABGR8888",
	"BGRA4441",
	"BGRA4444",
	"BGRA5551",
	"BGRA8888",
	"RGB332",
	"BGR332",
	"RGBA5542",
	"ABGR2554",
	"RGBA6661",
	"ABGR1666",
	"RGBA6666",
	"ABGR6666",
	"RGB666",
	"BGR666",
	"RGBA5658",
	"ABGR8565",
};

#if 0
static const char* opcodes[] = {
	/*  0 */ "PIX_OP_RGBA",
	/*  1 */ "PIX_TAB_ALPHA_SRC",
	/*  2 */ "PIX_OP_RGBA",
	/*  3 */ "PIX_OP_RGB",
	/*  4 */ "PIX_TAB_ALPHA_SRC",
	/*  5 */ "PIX_TAB_ALPHA_CHK",
	/*  6 */ "PIX_TAB_ALPHA",
	/*  7 */ "PIX_TAB",
	/*  8 */ "PIX_RGBA_CHK",
	/*  9 */ "PIX_RGBA",
	/* 10 */ "PIX_RGB",
	/* 11 */ "PIX_CPY",
	/* 12 */ "PROCESS_RGB_NO_STUFF",
	/* 13 */ "PROCESS_RGB",
	/* 14 */ "PROCESS_RGB_TAB_NO_STUFF",
	/* 15 */ "PROCESS_RGB_TAB"
};
#endif // 0

struct AllConditions
{
	// opcode
	//ushort		opcode;	// check opcodes
	const char* strs;

	// all condition
	int only_alpha, s_alpha, d_alpha, no_s_alpha, no_d_alpha, s_alpha_bigger, d_alpha_bigger,
	same_a_bit, same_rbg, same_rb, no_same_rgb, use_tab;

} __conditions[] = {
	// STRINGS                                         only_a,  src_a, dst_a, no_src_a, no_dst_a, src_a_bigger, dst_a_bigger, a_bit, same_rbg, same_rb, no_same_rgb, use_tab

	/*{"PIX_TAB_ALPHA\t\t( %s,\t%s,$TAL$DAB,%s, %s, %s );",  0,    0,     1,     1,        0,        0,            0,            0,     0,        0,       1,           1 },
	{"PIX_TAB_ALPHA_SRC\t( %s,\t%s,$TAL%s, %s, %s );",     1,    0,     0,     0,        0,        0,            0,            0,     0,        0,       1,           1 },
	{"PIX_TAB_ALPHA_SRC\t( %s,\t%s,$TAL%s, %s, %s );",     1,    0,     0,     0,        0,        0,            0,            1,     0,        0,       1,           1 },
	{"PIX_TAB_ALPHA_CHK\t( %s,\t%s,$TAL%s, %s, %s );",     1,    1,     1,     0,        0,        0,            1,            0,     0,        0,       1,           1 },
	{"PIX_TAB\t\t\t\t( %s,\t%s,$TAL%s, %s, %s );",         0,    0,     0,     0,        1,        0,            0,            0,     0,        0,       1,           1 },
	{"PIX_RGBA\t\t\t( %s,\t%s,$TAL$DAB );",                0,    0,     1,     0,        0,        0,            0,            0,     1,        0,       0,          -1 },
	{"PIX_OP_RGBA\t\t\t( %s,\t%s,$TAL%s, %s, %s, %s );",   1,    0,     0,     0,        0,        0,            0,            1,     1,        0,       0,          -2 },
	{"PIX_OP_RGBA\t\t\t( %s,\t%s,$TAL%s, %s, %s, %s );",   0,    0,     1,     0,        0,        0,            0,            0,     1,        0,       0,          -3 },
	{"PIX_OP_RGBA\t\t\t( %s,\t%s,$TAL%s, %s, %s, %s );",   0,    0,     1,     0,        0,        0,            0,            1,     1,        0,       0,          -2 },
	{"PIX_OP_RGBA\t\t\t( %s,\t%s,$TAL%s, %s, %s, %s );",   0,    0,     1,     1,        0,        0,            0,            0,     0,        0,       0,          -4 },*/
	// RGBA4441 >> RGBA5542
	{"PIX_OP_RGBA\t\t\t( %s,\t%s,$TAL%s, %s, %s, %s );",   0,    0,     0,     0,        0,        0,            0,            0,     0,        0,       0,          -4 },
	
	{0},
};

// -- conditions fnc

static void replaceCond( char* str, int* src, int* dst, int* af, int* bf )
{
	TRACE_DEBUG( "replace: %s\n", str );

	char* s = str;
	char* d = str;

	while( *s )
	{
		const char cc = *s;
		// replace source alpha bit
		if( cc == '$' && *(s + 1) == 'S' && *(s + 2) == 'A' && *(s + 3) == 'B' )
		{
			if((A(src,af)==1)||(A(src,af)==2))	{ s+=4; *d++ = '1'; }
			else if ( A(src,af) == 4 )			{ s+=4; *d++ = '0'; *d++ = 'x'; *d++ = '0'; *d++ = 'F'; }
			else if ( A(src,af) > 4 )			{ s+=4; *d++ = '2'; *d++ = '5'; *d++ = '5'; }
			else								{ s++; *d++ = ' '; }
		}
		// replace dest alpha bit
		else if( cc == '$' && *(s + 1) == 'D' && *(s + 2) == 'A' && *(s + 3) == 'B' )
		{
			if((A(dst,bf)==1)||(A(dst,bf)==2))	{ s+=4; *d++ = '1'; }
			else if ( A(dst,bf) == 4 )			{ s+=4; *d++ = '0'; *d++ = 'x'; *d++ = '0'; *d++ = 'F'; }
			else if ( A(dst,bf) > 4 )			{ s+=4; *d++ = '2'; *d++ = '5'; *d++ = '5'; }
			else								{ s++; *d++ = ' '; }
		}
		// tabulation depending on destination alpha (rgb == 2 tab, alpha == 1)
		else if( cc == '$' && *(s + 1) == 'T' && *(s + 2) == 'A' && *(s + 3) == 'L' )
		{
			if ( HAS_ALPHA(dst) )	{ s+=4; *d++ = '\t'; }
			else 					{ s+=4; *d++ = '\t'; *d++ = '\t'; }
		}
		else
			*d++ = *s++;
	}

	*d = '\0';
}

static void getAlphaCond( int* id, int* fmt, char* str )
{
	str[0] = '\0';

	if((A(id,fmt)==1)||(A(id,fmt)==2))
		strcpy(str,"1");
	else if ( A(id,fmt) > 2 && A(id,fmt) <= 6  )
		strcpy(str,"0x0F");
	else 
		strcpy(str,"255");

	//return str;
}

static void getTableCond(int in_a, int out_a, char* str)
{
	str[0] = '\0';
	if ( in_a < 6 || out_a < 6 )
	{
		strcpy(str,"SRC_A");
		return;
	}
	sprintf( str, "TABLE_SA(%d,%d)", in_a, out_a );
}

static int processCond( struct AllConditions* cond, const char* from, const char* to, int* s, int* d, int* af, int* bf )
{
	if (!cond->strs) return 0;

	TRACE_DEBUG( "Processing: '%s >> %s'", from, to );

	if ( cond->only_alpha		&& (!HAS_ALPHA(s)||!HAS_ALPHA(d)))					{ TRACE_DEBUG(" return only_alpha\n"); return 0; }
	if ( cond->s_alpha			&& !HAS_ALPHA(s) )									{ TRACE_DEBUG(" return src_alpha\n"); return 0; }
	if ( cond->d_alpha			&& !HAS_ALPHA(d) )									{ TRACE_DEBUG(" return dst_alpha\n"); return 0; }
	if ( cond->s_alpha_bigger	&& (A(d,bf) > A(s,af)) )							{ TRACE_DEBUG(" return src_alpha_bigger\n"); return 0; }
	if ( cond->d_alpha_bigger	&& (A(s,af) > A(d,bf)) )							{ TRACE_DEBUG(" return dst_alpha_bigger\n"); return 0; }
	if ( cond->same_a_bit		&&((cond->same_a_bit!=A(s,af))||(cond->same_a_bit!=A(d,bf))))	{ TRACE_DEBUG(" return same_a_bit\n"); return 0; }
	if ( cond->same_rbg			&& !SAME_RGB(s,d) )									{ TRACE_DEBUG(" return same_rbg\n"); return 0; }
	if ( cond->no_same_rgb		&& (SAME_R(s,d)||SAME_G(s,d)||SAME_B(s,d)))			{ TRACE_DEBUG(" return no_same_rgb\n"); return 0; }
	if ( cond->no_s_alpha		&& HAS_ALPHA(s) )									{ TRACE_DEBUG(" return no_src_alpha\n"); return 0; }
	if ( cond->no_d_alpha		&& HAS_ALPHA(d) )									{ TRACE_DEBUG(" return no_dst_alpha\n"); return 0; }

	// create string
	TRACE_DEBUG("\n");

	char str[256];
	str[0] = '\0';
	int result = 0;
	strcpy(str,cond->strs);
	replaceCond( str, s, d, af, bf );

	/*if ( 1 == use_tab )
	{
		TRACE_DEBUG( " replace done '%s'\n", str );

		char t0[128], t1[128], t2[128];
		t0[0] = '\0'; t1[0] = '\0'; t2[0] = '\0';
		sprintf( t0, "TABLE(%d,%d)", R(s,af), R(d,bf) );
		sprintf( t1, "TABLE(%d,%d)", G(s,af), G(d,bf) );
		sprintf( t2, "TABLE(%d,%d)", B(s,af), B(d,bf) );

		printf( str, from, to, t0, t1, t2 );

		printf("\n");
		result = 1;
	}
	// no tab, only : [ "from", "dest", "alpha bit" ]
	else if ( -1 == use_tab ) 
	{
		printf( str, from, to );
		printf("\n");
		result = 1;
	}
	else if ( -2 == use_tab ) 
	{
		printf( str, from, to, "(*src).r", "(*src).g", "(*src).b", "(*src).a" );
		printf("\n");
		result = 1;
	}
	else if ( -3 == use_tab ) 
	{
		// PIX_OP_RGBA			( BGR888, RGBA8888,		(*src).r, (*src).g, (*src).b, 255 );
		const char* astr = getAlpha( d, bf );
		printf( str, from, to, "(*src).r", "(*src).g", "(*src).b", astr );
		printf("\n");
		result = 1;
	}*/
	// generic function
	if ( -4 == cond->use_tab ) 
	{
		char r[128], g[128], b[128], a[128];
		r[0] = '\0'; g[0] = '\0'; b[0] = '\0'; a[0] = '\0';

		if ( SAME_R(s,d) )
			strcpy( r, "SRC_R" );
		else
			sprintf( r, "TABLE_SR(%d,%d)", R(s,af), R(d,bf) );

		if ( SAME_G(s,d) )
			strcat( g, "SRC_G" );
		else
			sprintf( g, "TABLE_SG(%d,%d)", G(s,af), G(d,bf) );

		if ( SAME_B(s,d) )
			strcat( b, "SRC_B" );
		else
			sprintf( b, "TABLE_SB(%d,%d)", B(s,af), B(d,bf) );

		if (  BOTH_ALPHA(s,d) && SAME_A(s,d) )
			strcat( a, "SRC_A" );
		else if ( BOTH_ALPHA(s,d) )
		{
			//sprintf( a, "TABLE(%d,%d)[(*src).a]", A(s,af), A(d,bf) );
			getTableCond(A(s,af), A(d,bf), a);
		}
		else if ( HAS_ALPHA(d) )
		{
			getAlphaCond( d, bf, a );
		}

		if ( HAS_ALPHA(d) )
			printf( "PIX_OP_RGBA\t\t\t( %s,\t%s,\t%s, %s, %s, %s );\n", from,to,r,g,b,a );
		else
			printf( "PIX_OP_RGB\t\t\t( %s,\t%s,\t\t%s, %s, %s );\n", from,to,r,g,b );

		result = 1;
	}

	return result;
}
// -- conditions fnc

void check_id( const char* str, int* id )
{
	int pos = 0;
	char* s = (char*)str;

	while( *s )
	{
		const char cc = *s;
		if ( RGB_NOT_SET && (cc == 'R' && *(s + 1) == 'G' && *(s + 2) == 'B' && *(s + 3) == 'A') )
		{
			s+=4; SET_FMT(id,FMT_RGBA,1);
		}
		else if ( RGB_NOT_SET && (cc == 'A' && *(s + 1) == 'B' && *(s + 2) == 'G' && *(s + 3) == 'R') )
		{
			s+=4; SET_FMT(id,FMT_ABGR,1);
		}
		else if ( RGB_NOT_SET && (cc == 'B' && *(s + 1) == 'G' && *(s + 2) == 'R' && *(s + 3) == 'A') )
		{
			s+=4; SET_FMT(id,FMT_BGRA,1);
		}
		else if ( RGB_NOT_SET && (cc == 'A' && *(s + 1) == 'R' && *(s + 2) == 'G' && *(s + 3) == 'B') )
		{
			s+=4; SET_FMT(id,FMT_ARGB,1);
		}
		else if ( RGB_NOT_SET && (cc == 'R' && *(s + 1) == 'G' && *(s + 2) == 'B') )
		{
			s+=3; SET_FMT(id,FMT_RGB,0); 
		}
		else if ( RGB_NOT_SET && (cc == 'B' && *(s + 1) == 'G' && *(s + 2) == 'R') )
		{
			s+=3; SET_FMT(id,FMT_BGR,0);
		}
		else if ( IS_NUM( *s ) )
		{
			id[pos] = cc - 48;
			pos++; (void)*s++;
			if( pos > (HAS_ALPHA(id) ? 4 : 3) )
				return;
		}
		else
			(void)*s++;
	}
}


void get_fmt( int* id, int* fmt )
{
	static int rgba[] = { 0, 1, 2, 3, };
	static int argb[] = { 1, 2, 3, 0, };
	static int abgr[] = { 3, 2, 1, 0, };
	static int bgra[] = { 2, 1, 0, 3, }; // BGRA : 0@5 1@5 2@5 3@1
	static int bgr[]  = { 2, 1, 0, 0, };
	static int rgb[]  = { 0, 1, 2, 0, };

	//memcpy( fmt, rgb, sizeof(rgb) );

	if ( IS_RGBA(id) )		memcpy( fmt, rgba, sizeof(rgba) );
	else if ( IS_ARGB(id) )	memcpy( fmt, argb, sizeof(argb) );
	else if ( IS_ABGR(id) )	memcpy( fmt, abgr, sizeof(abgr) );
	else if ( IS_BGRA(id) )	memcpy( fmt, bgra, sizeof(bgra) );
	else if ( IS_BGR(id) )	memcpy( fmt, bgr, sizeof(bgr) );
	else if ( IS_RGB(id) )	memcpy( fmt, rgb, sizeof(rgb) );
}

const char* fmt_str( int* id )
{
	static char str[64]; // tss tss ;)

	str[0] = '\0';

	switch( GET_FMT(id) )
	{
		case FMT_ABGR: strcpy( str, "abgr" ); break;
		case FMT_ARGB: strcpy( str, "argb" ); break;
		case FMT_BGRA: strcpy( str, "bgra" ); break;
		case FMT_RGBA: strcpy( str, "rgba" ); break;
		case FMT_RGB: strcpy( str, "rgb" ); break;
		case FMT_BGR: strcpy( str, "bgr" ); break;
		default : strcpy( str, "unknown" ); break;
	}
	return str;
}

void debug_fmt( int* id, int* fmt )
{
	const char* str_fmt = fmt_str( id );

	if ( HAS_ALPHA(id) )
		printf("type: %s - format: R'%d' G'%d' B'%d' A'%d'\n", str_fmt, id[fmt[0]], id[fmt[1]], id[fmt[2]], id[fmt[3]] );
	else
		printf("type: %s - format: R'%d' G'%d' B'%d'\n", str_fmt, id[fmt[0]],id[fmt[1]],id[fmt[2]] );
}


void process( const char* from, const char* to, int* s, int* d, int* af, int* bf )
{
	int i;
	for ( i = 0; i < ARRAY_SIZE(__conditions); ++i )
	{
		if ( processCond( &__conditions[i], from, to, s, d, af, bf ) )
			return;
	}

	printf( "Unknown opcode: %s >> %s\n", from, to );

	printf("source : ");debug_fmt( s, af );
	printf("dest : ");	debug_fmt( d, bf );
}

// -- 

void generate_function( const char* from, const char* to )
{
	int src_fmt[4];
	int dst_fmt[4];
	int src_id[6];
	int dst_id[6];

	// preprocess
	if ( strcmp(from,to) == 0 )
	{
		printf( "PIX_CPY\t\t\t\t( %s );\n", from );
		return;
	}

	memset(src_id,0x00,sizeof(src_id));
	memset(dst_id,0x00,sizeof(dst_id));
	memset(src_fmt,0x00,sizeof(src_fmt));
	memset(dst_fmt,0x00,sizeof(dst_fmt));

	// check id
	check_id( from, src_id );
	check_id( to, dst_id );

	get_fmt( src_id, src_fmt );
	get_fmt( dst_id, dst_fmt );

	process( from, to, src_id, dst_id, src_fmt, dst_fmt );
}

void generate_all(void)
{
	int count = 0;
	int x,y;
	for ( x = 0; x < ARRAY_SIZE(all_formats); ++x )
	{
		printf("// -- %s ---------------------------------------------------------------------------------------------\n", all_formats[x] );

		for ( y = 0; y < ARRAY_SIZE(all_formats); ++y, ++count )
		{
			generate_function( all_formats[x], all_formats[y] );
		}
	}

	TRACE_DEBUG( "Generated %d tables\n", count );
}

static int itoa( int value, char* result, int base )
{
	// check that the base is valid
	if (base < 2 || base > 36) { *result = '\0'; return 0;}

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do
	{
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if ( tmp_value < 0 )
		*ptr++ = '-';

	*ptr-- = '\0';

	while(ptr1 < ptr)
	{
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}

	// make it upper
	ptr = result;
	do
	{
		*ptr = toupper( *ptr );
	}
	while ( *ptr++ );

	return strlen( result );
}

void gen_table( uint a, uint b )
{                             //  0  1  2  3   4   5   6    7    8 
	static int table_size[] = {   1, 2, 4, 8, 16, 32, 64, 128, 256, };
	static int padd[]       = {   0, 0, 0, 0,  0, 15, 31,   0,   0, };
	static int pdiv[]       = {   0, 3, 3, 7, 15, 15, 31,  31,  31, };
	static int pmul[]       = {   0, 1, 3, 7, 15, 31, 63, 127, 255, };

	int i = 0;
	int count = 0;
	char buf[33];
//	const int t0 = table_size[b]-1;
	const int t1 = table_size[a]-1;

	printf("\nstatic const uchar _%ubit_to_%ubit_table[%d];\n", a, b, table_size[a] );
	printf("\nconst uchar _%ubit_to_%ubit_table[%d] = \n{\n\t", a, b, table_size[a] );

	if ( a > b )
	{
		const uint t0 = table_size[ b ];
		const uint t1 = table_size[ a ];

		for ( i=0; i < t1; ++i)
		{
			const uint v = i * t0 / t1;
			const int len = itoa( v, buf, 16 );
			printf( len>1?"0x%s, ":"0x0%s, ", buf );
			count++;
			if ( count > 15 )
			{
				count = 0;
				printf("\n\t");
			}
		}
		printf("\n};\n\n");
		return;
	}

	for ( i=0; i < t1+1; ++i)
	{
		//printf("v = %d * %d + %d / %d\n", i, pmul[b], padd[a], pdiv[a] );
		const uint v = (i * pmul[b] + padd[a]) / pdiv[a];

		const int len = itoa( v, buf, 16 );
		printf( len>1?"0x%s, ":"0x0%s, ", buf );
		count++;
		if ( count > 15 )
		{
			count = 0;
			printf("\n\t");
		}
	}

	printf("\n};\n\n");
}

// -----------------------------------------------------------------------------
// fnc.c - Last Change: $Date: 2012-05-15 23:36:52 $ - End Of File
// -----------------------------------------------------------------------------
