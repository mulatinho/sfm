# Documentation 
MANPAGES = sfmgui.1 sfmnc.1
TXTS = functions.txt

all: man txts

man: $(MANPAGES)

txts: $(TXTS)

*.1:
	gzip -v $@

*.txt:
	ls -l functions.txt

clean:
	rm -fv *~ *.gz
