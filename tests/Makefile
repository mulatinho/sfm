# Simple makefile for SFM GUI and Ncurses
CC     = gcc
LDADD  = -latk-1.0 -lcairo -lfontconfig -lfreetype -lgdk-x11-2.0 -lgdk_pixbuf-2.0 \
	    -lgio-2.0 -lglib-2.0 -lgobject-2.0 -lgtk-x11-2.0 -lpango-1.0 \
	    -lpangocairo-1.0 -lpangoft2-1.0 -lpthread -lsmbclient -lncurses
CFLAGS = -W -Wall -g -ggdb -pthread \
	-I/usr/include/samba-4.0 -I/usr/include/atk-1.0 -I/usr/include/cairo \
	-I/usr/include/freetype2 -I/usr/include/gdk-pixbuf-2.0 \
	-I/usr/include/glib-2.0 -I/usr/include/gtk-2.0 -I/usr/include/harfbuzz \
	-I/usr/include/libdrm -I/usr/include/libpng16 -I/usr/include/pango-1.0 \
	-I/usr/include/pixman-1 -I/usr/lib64/glib-2.0/include \
	-I/usr/lib64/gtk-2.0/include -I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
	-I/usr/lib/x86_64-linux-gnu/gtk-2.0/include

all: test01 test02

*.o:
	gcc $(CFLAGS) $< -o $@

*.c:
	gcc -Wall $^ -o $@

clean:
	rm -fv test[0-9][0-9] *~
