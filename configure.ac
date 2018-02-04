#configure.ac

# Configure file for use with autoconf
# created 1/26/2018
# edit this file then run
# $ autoconf -o configure configure.ac
# autoconf is required for this package. pkg-config is preffered; however
# functions for packages; SAM is not provided as one at this time.

AC_INIT([RSSC], 0.1, [ezztucker@gmail.com])

dnl Find Compiler and compiler flags to use

if test -z "${R_HOME}"; then
    echo "could not determine R_HOME"
    exit 1
fi

CC=`"${R_HOME}/bin/R" CMD config CC`
CPP=`"${R_HOME}/bin/R" CMD config CPP`
CFLAGS=`"${R_HOME}/bin/R" CMD config CFLAGS`
CPPFLAGS=`"${R_HOME}/bin/R" CMD config CPPFLAGS`

dnl check the ssc headers can be found
AC_CHECK_HEADERS(sscapi.h)
if test "${ac_cv_header_sscapi_h}" = no; then
    AC_MSG_ERROR("SSC headers sscapi.h not found")
fi

AC_LANG_PUSH([C++])

dnl check ssc library found
AC_SEARCH_LIBS([dlopen], [dl], [], AC_MSG_ERROR([unable to find libdl]))
AC_SEARCH_LIBS([ssc_version], [:ssc.so], [], AC_MSG_ERROR([unable to find ssc]))

RSSC_CPPFLAGS="${CPPFLAGS}"

dnl substitute RSSC_CPPFLAGS and LIBS
AC_SUBST(RSSC_CPPFLAGS)
AC_SUBST(LIBS)

dnl substitution in src/Makevars.in
AC_CONFIG_FILES([src/Makevars])
AC_OUTPUT