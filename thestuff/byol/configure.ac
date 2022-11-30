
AC_INIT([blip], [0.0.1])

AC_PREREQ([2.69])
AC_CONFIG_SRCDIR([src/blip.c])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([1.11 -Wall -Werror subdir-objects foreign])
AC_CONFIG_FILES([Makefile])
AC_PROG_CC

PKG_CHECK_MODULES([DEPS], [libedit])

AC_OUTPUT

