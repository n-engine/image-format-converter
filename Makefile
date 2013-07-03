#####################################################################
# 
# Makefile
#
# Copyright 2011-2012 ESTEVE Olivier <naskel .[.at.]. gmail.com>
#
# This software is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this software; if not, write to the
# Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#
#
# $Log: Makefile,v $
#
#
#####################################################################

CC := g++
DEBUG := 0

FLAGS = -O2 -Wall -pipe

ifeq ($(DEBUG),1)
FLAGS = -g3 -ggdb -O0 -Wall
endif

generator:
	$(CC) $(FLAGS) -o gen_table main.cxx -lm

test:
	$(CC) $(FLAGS) -o example example.cxx converter.cxx xpm.cxx -lm

all: generator test

# -----------------------------------------------------------------------------
# Makefile - Last Change: $Date: 2012-05-15 23:36:52 $ - End Of File
# -----------------------------------------------------------------------------
