/* Copyright (C) 2015 Alexandre Mulatinho <alex at mulatinho.net>.
   massert.h is a simple group of functions to test source files in C.  

   This file is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The 'massert.h' file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <stdio.h>
#include <assert.h>

#ifndef __MASSERT_H
#define __MASSERT_H 1

int m_rsuccess = 0;
int m_rtests = 0;

#define m_finish() do { \
	if (!(m_rtests-m_rsuccess)) printf("\nResult: PASSED\n"); \
	else printf("\nResult: FAILED\n"); \
	printf("Tests run: %d, Tests PASSED: %d, Tests FAILED: %d\n", \
		m_rtests, m_rsuccess, (m_rtests-m_rsuccess)); } while(0)

#define m_debug(res) \
	printf("return %s in '%s' on function '%s()' line %d, test '%s'\n", \
	res ? "success" : "error  ", __FILE__, __func__, __LINE__, __STRING(res))

#define m_assert(test) do { \
	if (test) { m_rsuccess++; } \
       m_rtests++; m_debug(test); } while(0)

#endif
