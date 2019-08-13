AC_PREREQ(2.58)
AC_INIT([sfm], [0.01], [Alexandre Mulatinho <alex@mulatinho.net>])

AM_INIT_AUTOMAKE(1.8)

AC_CONFIG_SRCDIR([src/main.c])

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
AC_CHECK_LIB(ncurses, initscr)
AC_CHECK_LIB(menu, post_menu)
AC_CHECK_LIB(ncurses, initscr)

AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_LN_S
AC_PROG_INSTALL
AC_PROG_AWK
AC_PROG_MAKE_SET

PKG_PROG_PKG_CONFIG

PKG_CHECK_MODULES(GLIB, glib-2.0 >= 2.2.0, HAVE_GLIB="yes")

dnl ---------------------------------------------------------------------------
dnl - Check for NCURSES
dnl ---------------------------------------------------------------------------
PKG_CHECK_MODULES([NCURSES], [ncurses], [],
                  [try_ncurses_fallback=true])
if test x"$try_ncurses_fallback" = xtrue; then
    NCURSES_LIBS=
    AC_CHECK_HEADER([ncurses.h], [],
                    [AC_MSG_ERROR([ncurses.h not found])])

    AC_CHECK_LIB([ncurses], [smbc_opendir],
                 [NCURSES_LIBS="-lncurses -ltinfo -lmenu -lpanel"])
    if test "x$NCURSES_LIBS" = "x" ; then
        AC_MSG_ERROR([libncurses not found])
    fi
    AC_SUBST(NCURSES_LIBS)
fi

dnl ---------------------------------------------------------------------------
dnl - Check for Samba
dnl ---------------------------------------------------------------------------
PKG_CHECK_MODULES([SMBCLIENT], [smbclient], [],
                  [try_smbclient_fallback=true])
if test x"$try_smbclient_fallback" = xtrue; then
    SMBCLIENT_LIBS=
    AC_CHECK_HEADER([samba-4.0/libsmbclient.h], [],
                    [AC_MSG_ERROR([samba-4.0/libsmbclient.h not found])])

    AC_CHECK_LIB([smbclient], [smbc_opendir],
                 [SMBCLIENT_LIBS="-Wl,-rpath,/usr/lib64 -lsmbclient"])
    if test "x$SMBCLIENT_LIBS" = "x" ; then
        AC_MSG_ERROR([libsmbclient not found])
    fi
    AC_SUBST(SMBCLIENT_LIBS)
fi

dnl ---------------------------------------------------------------------------
dnl - Check for GTK
dnl ---------------------------------------------------------------------------
PKG_CHECK_MODULES([GTK], [gtk+-2.0], [],
                  [try_gtk_fallback=true])
if test x"$try_gtk_fallback" = xtrue; then
    GTK_LIBS=
    AC_CHECK_HEADER([gtk-2.0/gtk/gtk.h], [],
                    [AC_MSG_ERROR([gtk-2.0/gtk/gtk.h not found])])

    AC_CHECK_LIB([gtk], [gtk_main],
                 [GTK_LIBS="-lgtk-x11-2.0 -lgdk-x11-2.0 -lpangocairo-1.0 -latk-1.0 -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lpangoft2-1.0 -lpango-1.0 -lgobject-2.0 -lglib-2.0 -lfontconfig -lfreetype"])
    if test "x$GTK_LIBS" = "x" ; then
        AC_MSG_ERROR([gtk+-2.0 not found])
    fi
    AC_SUBST(GTK_LIBS)
fi

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
