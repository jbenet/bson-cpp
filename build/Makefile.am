AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4


#########################################################
# LIBRARY

includedir = /usr/local/include/bson
utilpkg_includedir = $(includedir)/util
libpkg_includedir = $(includedir)/lib

VERSION = 0.1

BSONHEADERS = src/*.h
BSONSOURCES = src/bsonobj.cpp src/oid.cpp

UTILHEADERS = src/util/*.h
UTILSOURCES = src/util/json.cpp

LIBHEADERS = lib/atomic_int.h lib/base64.h lib/md5.h lib/nonce.h
LIBSOURCES = lib/base64.cpp lib/md5.c lib/nonce.cpp

bsoncppdir = src/
lib_LTLIBRARIES = libbsoncpp.la
include_HEADERS = $(BSONHEADERS)
utilpkg_include_HEADERS = $(UTILHEADERS)
libpkg_include_HEADERS = $(LIBHEADERS)

libbsoncpp_la_SOURCES = $(BSONSOURCES) $(UTILSOURCES) $(LIBSOURCES)
libbsoncpp_la_CPPFLAGS = -fPIC $(AM_CPPFLAGS)
libbsoncpp_la_LDFLAGS = -version-info 0:1:0

library_includedir=$(includedir)/bsoncpp-$(VERSION)/
library_include_HEADERS = $(BSONHEADERS)



#########################################################
# TESTS

testdir = test/
test_PROGRAMS = test_bsonobj
test_RUNS = $(test_PROGRAMS:%=run_%)

test_bsonobj_SOURCES = test/test_bsonobj.cpp test/framework.cpp

AM_CPPFLAGS = -O0 -Wall -Werror -ggdb -Isrc $(BOOST_CPPFLAGS)
AM_LDFLAGS = $(BOOST_LDFLAGS) \
             $(BOOST_PROGRAM_OPTIONS_LIB) \
             $(BOOST_THREAD_LIB)
LDADD = $(BOOST_THREAD_LIBS) libbsoncpp.la -lboost_system-mt
LIBS = $(BOOST_THREAD_LIBS)

#dist_bsoncpp_SCRIPTS = autogen.sh


#########################################################
# TARGETS

.PHONY: all clean test

all: $(test_PROGRAMS)

run_% : %
	@echo '==============> Running Test $<'
	@./$< > /dev/null

test: $(test_RUNS)
#todo: add testing for tests here.

deep-clean: distclean
	rm -f aclocal.m4 configure config.sub depcomp missing install-sh
	rm -f config.guess
	rm -rf autom4te.cache
	rm -rf */*.in *.in
	rm -rf libbsoncpp.la