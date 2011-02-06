AUTOMAKE_OPTIONS = foreign

ACLOCAL_AMFLAGS = -I m4

testdir = test/
test_PROGRAMS = test_bsonobj
test_RUNS = $(test_PROGRAMS:%=run_%)

test_bsonobj_SOURCES = test/test_bsonobj.cpp

AM_CPPFLAGS = -O0 -Wall -Werror -ggdb -Isrc $(BOOST_CPPFLAGS)
AM_LDFLAGS = $(BOOST_THREADS_LDFLAGS)
LDADD = $(BOOST_THREAD_LIBS)

# bsoncppdir = src/
# bsoncpp_LIBRARIES = libbsoncpp.a
# libbsonccp_a_SOURCES =
# libbsonccp_a_CPPFLAGS = -fPIC $(AM_CPPFLAGS)

#bin_PROGRAMS = dronestore

#dist_bsoncpp_SCRIPTS = autogen.sh

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
	rm -rf dronestore.so