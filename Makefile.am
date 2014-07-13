bin_PROGRAMS = sfm

sfm_SOURCES = action.c build_env.sh libsmb.c main.c main.h strkey.c util.c views.c

sfm_CFLAGS = `pkg-config --cflags gtk+-2.0 smbclient`

sfm_LDFLAGS = -lpthread
sfm_LDFLAGS+= `pkg-config --libs gtk+-2.0 smbclient`
