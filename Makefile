# Makefile for file manager
DEBUG=-g -ggdb -Wall
CFLAGS=`pkg-config --cflags gtk+-2.0 smbclient`
LIBS=`pkg-config --libs gtk+-2.0 smbclient`
LINK= $(CFLAGS) $(LIBS) -lpthread
PATHBINR=/usr/local/bin/sfm
PATHIMGS=/usr/share/pixmaps
PATHCONF=/etc/sfm.conf

all: sfm
	
strkey.o: strkey.c
	gcc  -o strkey.o -c strkey.c $(CFLAGS) $(DEBUG)

libsmb.o: libsmb.c
	gcc  -o libsmb.o -c libsmb.c $(CFLAGS) $(DEBUG)

action.o: action.c
	gcc  -o action.o -c action.c $(CFLAGS) $(DEBUG)
	
util.o: util.c
	gcc  -o util.o -c util.c $(CFLAGS) $(DEBUG)
	
views.o: views.c
	gcc  -o views.o -c views.c $(CFLAGS) $(DEBUG)

test.o: test.c
	gcc  -o test.o -c test.c $(CFLAGS) $(DEBUG)

main.o: main.c
	gcc  -o main.o -c main.c $(CFLAGS) $(DEBUG)
	
sfm: strkey.o util.o views.o action.o libsmb.o main.o
	gcc strkey.o util.o views.o action.o libsmb.o main.o  -o sfm $(CFLAGS) $(LIBS) $(DEBUG)

test: test.o test.o
	gcc test.o  -o test $(CFLAGS) $(LIBS)

install:
	cp -f sfm.cfg $(PATHCONF)
	mkdir -p /usr/local/bin
	mkdir -p $(PATHIMGS)
	cp sfm*png $(PATHIMGS)
	cp sfm $(PATHBINR) 

clean:
	rm -rf *.o *~
	if [ -f sfm ] ; then rm sfm; fi
	if [ -f $(PATHBINR) ] ; then rm -f $(PATHBINR); fi
	if [ -f $(PATHCONF) ] ; then rm -f $(PATHCONF); fi
