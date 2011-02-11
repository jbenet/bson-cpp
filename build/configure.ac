AC_PREREQ(2.61)
AC_INIT([bson-cpp], [0.1], [jbenet@cs.stanford.edu])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL

LT_INIT

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
AC_C_VOLATILE

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_REALLOC

# Boost
BOOST_REQUIRE([1.38])
BOOST_SYSTEM
BOOST_THREADS
BOOST_FILESYSTEM
BOOST_PROGRAM_OPTIONS
BOOST_REGEX

AC_CONFIG_FILES([Makefile])
AM_INIT_AUTOMAKE([bsoncpp], [0.1])

AC_OUTPUT

echo "Install prefix ................... : $prefix"