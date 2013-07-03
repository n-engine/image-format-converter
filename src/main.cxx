/* 
 * main.cxx
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
 * $Log: main.cxx,v $
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
#include <assert.h>

#include "fnc.h"

static void help(const char* prog)
{
	printf(
		"\n%s [option1] [option2]\n"
		"%s --function            - this will generate all the available function for converte\n"
		"                           and output all text to the console\n"
		"%s --all                 - this will generate all the table for converter\n"
		"                           and output all text to the console\n"
		"%s id id                 - this will generate the needed table, exemple:\n"
		"                           %s 8 5 (this will generate table 8bit_to_5bit_table)\n"
		"                           and output all text to the console\n\n",
		prog,prog,prog,prog,prog
	);
}

int main( int argc, char* argv[] )
{
	uint a;
	uint b;

	/* if you want to generate only one function :
	 *	char* from = "ARGB1448";
	 *	char* to = "RGB888";
	 *	generate_function( argv[1], argv[2] );
	 */

	// generate all function
	if ( argc == 2 && strstr("--function", argv[1]) )
	{
		generate_all();

		return EXIT_SUCCESS;
	}

	// generate all table
	if ( argc == 2 && strstr("--all", argv[1]) )
	{
		TRACE_DEBUG( "\nGenerating table : \n");

		for (a = 1; a < 9; ++a)
			for (b = 1; b < 9; ++b)
				gen_table( a, b );

		return EXIT_SUCCESS;
	}

	// generate only one table
	if ( argc != 3 )
	{
		help(argv[0]);
		return EXIT_SUCCESS;
	}

	a = atoi( argv[1] );
	b = atoi( argv[2] );

	TRACE_DEBUG( "\nGenerating table : \n");

	gen_table( a, b );

	return EXIT_SUCCESS;
}

// -----------------------------------------------------------------------------
// main.cxx - Last Change: $Date: 2012-05-15 23:36:52 $ - End Of File
// -----------------------------------------------------------------------------
