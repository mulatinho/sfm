# Simple makefile for SFM GUI and Ncurses
PKGNAM = sfm
PKGVERSION = 0.03
EXTRA_DIST=HACKING README INSTALL COPYING
SUBDIRS=doc po src tests 

dist:
	tar cvfz build/$(PKGNAM)-$(PKGVERSION).tar.gz doc/ build/

clean:
	rm -rfv autom4te.cache src/sfm
	rm -fv *.in */*.in */*.o */*~ aclocal.m4 compile config.* configure depcomp missing install-sh *~
	rm -fv {.,src}/Makefile
