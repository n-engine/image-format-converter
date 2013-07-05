bin_PROGRAMS = example
example_SOURCES = example.c
AM_CFLAGS = -I$(top_builddir)/include -ggdb -g3
example_LDADD = $(top_builddir)/src/libifc.la -lm

#if WITH_LIBTIFF
example_LDADD += -ltiff
#endif