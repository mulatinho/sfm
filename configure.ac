AC_PREREQ(2.58)
AC_INIT([sfm], [1.0], [Alexandre Mulatinho <alex@mulatinho.net>])

AM_INIT_AUTOMAKE(1.8)

AC_CHECK_HEADERS([unistd.h])
AC_CHECK_LIB(smbclient, smbc_opendir)

AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_LN_S
AC_PROG_INSTALL

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
