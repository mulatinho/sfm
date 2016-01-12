# Simple makefile for SFM GUI and Ncurses
bin_PROGRAMS = sfm
sfm_LDADD = -latk-1.0 -lcairo -lfontconfig -lfreetype -lgdk-x11-2.0 -lgdk_pixbuf-2.0 \
	    -lgio-2.0 -lglib-2.0 -lgobject-2.0 -lgtk-x11-2.0 -lpango-1.0 \
	    -lpangocairo-1.0 -lpangoft2-1.0 -lpthread -lsmbclient -lncurses -lmenu
sfm_CFLAGS = -W -Wall -g -ggdb -pthread \
	-I/usr/include/samba-4.0 -I/usr/include/atk-1.0 -I/usr/include/cairo \
	-I/usr/include/freetype2 -I/usr/include/gdk-pixbuf-2.0 \
	-I/usr/include/glib-2.0 -I/usr/include/gtk-2.0 -I/usr/include/harfbuzz \
	-I/usr/include/libdrm -I/usr/include/libpng16 -I/usr/include/pango-1.0 \
	-I/usr/include/pixman-1 -I/usr/lib64/glib-2.0/include \
	-I/usr/lib64/gtk-2.0/include -I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
	-I/usr/lib/x86_64-linux-gnu/gtk-2.0/include
sfm_SOURCES = operations.c gui.c libsmb.c options.c main.c main.h util.c views.c
