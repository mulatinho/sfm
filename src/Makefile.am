# Simple makefile for SFM GUI and Ncurses
bin_PROGRAMS = sfm

sfm_SOURCES = action.c ui.c libsmb.c main.c main.h util.c views.c

sfm_CFLAGS = `pkg-config --cflags gtk+-2.0 smbclient`

AM_CFLAGS = -lsmbclient -lncurses -lpthread -lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgdk_pixbuf-2.0 -lm -lpangocairo-1.0 -lfontconfig -lXinerama -lXi -lXrandr -lXext -lXcursor -lXfixes -lpango-1.0 -lcairo -lXrender -lX11 -lgobject-2.0 -lgmodule-2.0 -ldl -lglib-2.0
AM_LIBS = ncurses pthread gtk+-2.0 smbclient

sfm_LDFLAGS = -lpthread
sfm_LDFLAGS+= `pkg-config --libs gtk+-2.0 smbclient`
