ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = -g -Wall @SSL_CFLAGS@
AM_CFLAGS	=
AM_CXXFLAGS =
AM_LDFLAGS	= @SSL_LIBS@

lib_LTLIBRARIES = libsha-demo.la

libsha_demo_la_SOURCES = \
./src/bytes.cpp \
./src/envvars.cpp

check_PROGRAMS = test1

test1_SOURCES = ./tests/test1.cpp
test1_LDADD = libsha-demo.la

TESTS = $(check_PROGRAMS)
