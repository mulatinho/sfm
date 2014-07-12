/*
	STRKEY.C - AN FUNCTION FOR REPLACE STRTOK().
	Copyright (C) 2004	Alexandre Mulatinho

	This library is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
*/

// Tue Oct 12 21:51:44 BRT 2004
// char *p = strkey(buf,2,':'); 

#include <stdio.h>
#include <string.h>

char *strkey(char *buf, int who, short del)
{
	char *str = (char*)malloc(strlen(buf));
	short ch, i, f=0, x=0, loop=0;

	for (i=0;i<strlen(buf);i++) {
	ch = *(buf+i);

	if (ch==del && !i && !who)
		return NULL;

	if (ch==del) 
		loop++; 

	if (loop==who) {
		if (i==0 || f!=0) {
			*(str+x) = *(buf+i); x++;
		}
		f++;
	}
	}
	*(str+x)='\0';
	str=(char*)realloc(str,x);
	return (char*)str;
}
