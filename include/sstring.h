/* sstring.h: header file for sstring.c
 */

#ifndef SSTRING_H
#define SSTRING_H

#include <stddef.h>
#include <stdio.h>

typedef struct SString {
	char *buf;
	size_t len;
	size_t sz;
} SString;

ssize_t ssgetline(SString *restrict sstr, FILE *restrict fp);
int sssetByte(SString *restrict sstr, size_t i, char c);

#endif // SSTRING_H
