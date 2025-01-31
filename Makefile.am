# Simple makefile for SFM GUI and Ncurses
PKGNAM = sfm
PKGVERSION = 0.03
EXTRA_DIST=HACKING README INSTALL COPYING
SUBDIRS=po src

test: 
	make -C tests

deb:
	cp -vf src/sfm build/debian/usr/bin/sfm
	gzip doc/sfm.1
	cp -vf doc/sfm.1.gz build/debian/usr/share/man/man1/
	cp -vf LICENSE COPYING doc/functions.txt build/debian/usr/share/doc/sfm/
	find build/debian/ -type d -exec chmod 755 '{}' \;
	chmod 755 build/debian/usr/bin/sfm
	dpkg-deb --root-owner-group --build build/debian/ build/sfm.deb

clean:
	make -C tests clean
	rm -rfv autom4te.cache src/sfm */.deps/
	rm -fv *.in */*.in */*.o */*~ aclocal.m4 compile config.* configure depcomp missing install-sh test-driver *~ .*~
	rm -fv {.,src}/Makefile
	find . -type l -exec rm -fv '{}' \;
