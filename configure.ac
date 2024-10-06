#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
#---------------------------------------------------------------
# current file Writing, the test are very rudimentary !

AC_PREREQ([2.71])
AC_CONFIG_AUX_DIR([build-aux])
AC_INIT([AeroUp],[0.3.2],[laurentba<at>larueluberlu.net],[],[https://git.larueluberlu.net/AeroUp])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/global.hpp])
AC_CONFIG_HEADERS([src/config.h])
AC_COPYRIGHT([Copyright © 2014 BARATTERO Laurent\n
              License GPLv3+: GNU GPL version 3 or later
              <http://gnu.org/licenses/gpl.html>
              This is free software: you are free to change and redistribute it.\n
              There is NO WARRANTY, to the extent permitted by lawn])
AC_REVISION([$Revision: 0.1 $]) 

AC_DEFINE( [DEBUG], [1], [Define debug mod])

AC_DEFINE( [HAVE_REGCOMP], [1], [Define to 1 if you have the 'regcomp' function.])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_RANLIB
AC_LANG([C++])

# Checks for libraries.
#======================
## usage of boost macro later 
#AC_PROG_LIBTOOL
#BOOST_REQUIRE

#core
AC_CHECK_LIB([boost_system], [main], ,[AC_MSG_ERROR("Linking against boost::system library failed.")])

AC_CHECK_LIB([boost_thread], [main], ,[AC_MSG_ERROR("Linking against boost::thread library failed.")])

AC_CHECK_LIB([boost_regex], [main],
             [HAVE_BOOST_REGEX=yes
                LIBS+=-lboost_regex
                AC_DEFINE( [HAVE_LIBBOOST_REGEX], [1], [Define to 1 if you have the 'boost_regex' library (-lboost_regex)])],
             [HAVE_BOOST_REGEX=no 
                AC_MSG_WARN("Linking against boost::regex library failed. We will try to use linux regcomp ")])

if test "x$HAVE_BOOST_REGEX" = xno; then
  AC_CHECK_FUNCS([regcomp], ,[AC_MSG_ERROR("Linking error : neither find lib boost regex nor the replacement function regcomp")])
  AC_CHECK_HEADER([termios.h],
                  [HAVE_TERMIOS_H=yes 
                    AC_DEFINE( [HAVE_TERMIOS_H], [1], [Define to 1 if you have the <termios.h> header file.])],
                  [AC_MSG_WARN(["Can't find termios header, i hope you have boost assio serial"])])
fi

#QT
# for coming soon gui
#AC_CHECK_LIB([GL], [main])
#AC_CHECK_LIB([Qt5Core], [main])
#AC_CHECK_LIB([Qt5Gui], [main])
#AC_CHECK_LIB([Qt5Widgets], [main])
#AC_CHECK_LIB([pthread], [main])

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T
#AC_TYPE_UINT32_T
#AC_TYPE_UINT8_T

# Checks for library functions.
AC_CHECK_FUNCS([memset regcomp strtol])
AC_CHECK_FUNCS([bzero memset strtol])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 udev/Makefile])


AM_CONDITIONAL([BOOST], [test "$HAVE_BOOST_REGEX" = yes])

# UDEV
AC_MSG_CHECKING([For Udev])
AM_CONDITIONAL([UDEV], [test -d "/etc/udev/rules.d" ])
AM_COND_IF([UDEV], [AC_MSG_RESULT(["yes"])], [AC_MSG_RESULT(["no"])])



AC_OUTPUT

echo \
"-------------------------------------------------
 ${PACKAGE_NAME} Version ${PACKAGE_VERSION}

 Prefix: '${prefix}'.
 Compiler: '${CC} ${CFLAGS} ${CPPFLAGS}'

 Package features: (coming soon)
   Async Execution: ${async_exec}

 Now type 'make @<:@<target>@:>@'
   where the optional <target> is:
     all                - build all binaries
     install            - install everything (need to be root)

--------------------------------------------------"
