# Simple makefile for SFM GUI and Ncurses
bin_PROGRAMS = sfm

sfm_SOURCES = action.c ui.c libsmb.c main.c main.h util.c views.c

sfm_CFLAGS = `pkg-config --cflags gtk+-2.0 smbclient`

sfm_LDFLAGS = -lpthread
sfm_LDFLAGS+= `pkg-config --libs gtk+-2.0 smbclient`
