# Simple makefile for SFM GUI and Ncurses
bin_PROGRAMS = sfm

sfm_LDADD = \
	$(GTK_LIBS) \
	$(SMBCLIENT_LIBS) \
	$(NCURSES_LIBS)
	-lpthread

sfm_CFLAGS = -O0 -DDEBUG=1 -W -g -ggdb -pthread \
	$(GTK_CFLAGS) \
	$(SMBCLIENT_CFLAGS) \
	$(NCURSES_CFLAGS)

sfm_SOURCES = memory.c gui.c console.c libsmb.c options.c main.c main.h util.c views.c
