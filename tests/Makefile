# Simple makefile for SFM GUI and Ncurses
CFLAGS = `pkg-config --cflags gtk+-2.0 smbclient`
LDFLAGS = -lpthread
LDFLAGS+= `pkg-config --libs gtk+-2.0 smbclient`

all: test01.c test02.c
	
*.c:
	gcc -Wall $^ -o $@

clean:
	rm -fv *~
