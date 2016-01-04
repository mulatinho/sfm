AC_PREREQ(2.58)
AC_INIT([sfm], [0.01], [Alexandre Mulatinho <alex@mulatinho.net>])

AM_INIT_AUTOMAKE(1.8)

AC_CHECK_HEADERS([unistd.h])
AC_CHECK_HEADERS([pthread.h])
AC_CHECK_HEADERS([libsmbclient.h])
AC_CHECK_HEADERS([curses.h])
AC_CHECK_HEADERS([fcntl.h])

AC_CHECK_FUNCS([memset])
AC_CHECK_FUNCS([mkdir])
AC_CHECK_FUNCS([strerror])

AC_FUNC_FORK
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_FUNC_MALLOC
AC_TYPE_PID_T

AC_CHECK_LIB(pthread, pthread_create)
AC_CHECK_LIB(smbclient, smbc_opendir)
AC_CHECK_LIB(ncurses, initscr)
AC_CHECK_LIB(gtk, gtk_init)

AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_LN_S
AC_PROG_INSTALL

PKG_PROG_PKG_CONFIG

PKG_CHECK_MODULES(GTK, gtk+-2.0 >= 2.10.0, HAVE_GTK="yes")
PKG_CHECK_MODULES(GLIB, glib-2.0 >= 2.2.0, HAVE_GLIB="yes")

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
