pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = libifc.pc

AM_CPPFLAGS = -I$(top_srcdir)/include -D_GNU_SOURCE
AM_CFLAGS = -Wall -Werror-implicit-function-declaration -ffunction-sections -fdata-sections

lib_LTLIBRARIES = libifc.la

libifc_la_SOURCES = converter.cxx xpm.cxx tga.cxx

libifc_la_LDFLAGS = -static

