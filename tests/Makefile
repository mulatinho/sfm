# Simple makefile for SFM GUI and Ncurses
CC      = gcc
CFLAGS  = `pkg-config --cflags gtk+-2.0 smbclient`
LDFLAGS = -lpthread
LDFLAGS+= `pkg-config --libs gtk+-2.0 smbclient`

all: test01 test02

*.o:
	gcc $(CFLAGS) $< -o $@

*.c:
	gcc -Wall $^ -o $@

clean:
	rm -fv test[0-9][0-9] *~
