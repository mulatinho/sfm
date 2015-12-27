# Simple makefile for SFM GUI and Ncurses
bin_PROGRAMS = sfm
sfm_SOURCES = action.c ui.c libsmb.c main.c main.h util.c views.c
sfm_CFLAGS = @GTK_CFLAGS@ -I/usr/include/samba-4.0
sfm_LDFLAGS = -lpthread -lsmbclient
sfm_LDFLAGS+= @GTK_LIBS@ 
