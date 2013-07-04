pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = libifc.pc

AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CFLAGS = -I$(top_srcdir)/include -Wall -Werror -Werror-implicit-function-declaration -ffunction-sections -fdata-sections

lib_LTLIBRARIES = libifc.la

libifc_la_SOURCES = converter.c fnc.c xpm.c tga.c

libifc_la_LDFLAGS = -static

