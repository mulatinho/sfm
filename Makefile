# Makefile for file manager
CFLAGS=`pkg-config --cflags gtk+-2.0 smbclient` -W -funroll-loops -ggdb
LIBS=`pkg-config --libs gtk+-2.0 smbclient`
LINK= $(CFLAGS) $(LIBS) -lpthread
PATHBINR=/usr/local/bin/sfm
PATHIMGS=/usr/share/pixmaps
PATHCONF=/etc/sfm.conf

all: sfm
	
strkey.o: strkey.c
	clang -o strkey.o -c strkey.c $(CFLAGS) 

libsmb.o: libsmb.c
	clang -o libsmb.o -c libsmb.c $(CFLAGS)

action.o: action.c
	clang -o action.o -c action.c $(CFLAGS)
	
util.o: util.c
	clang -o util.o -c util.c $(CFLAGS)
	
views.o: views.c
	clang -o views.o -c views.c $(CFLAGS)

test.o: test.c
	clang -o test.o -c test.c $(CFLAGS)

main.o: main.c
	clang -o main.o -c main.c $(CFLAGS)
	
sfm: strkey.o util.o views.o action.o libsmb.o main.o
	clang strkey.o util.o views.o action.o libsmb.o main.o -o sfm $(CFLAGS) $(LIBS)

test: test.o test.o
	clang test.o -o test $(CFLAGS) $(LIBS)

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
