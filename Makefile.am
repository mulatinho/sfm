# Simple makefile for SFM GUI and Ncurses
PKGNAM = sfm
PKGVERSION = 0.03
EXTRA_DIST=HACKING README INSTALL COPYING
SUBDIRS=doc po src tests 

clean:
	rm -rfv autom4te.cache src/sfm */.deps/
	rm -fv *.in */*.in */*.o */*~ aclocal.m4 compile config.* configure depcomp missing install-sh *~
	rm -fv {.,src}/Makefile
