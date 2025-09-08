/* sstring.h: header file for sstring.c
 */

#ifndef SSTRING_H
#define SSTRING_H

#include <stddef.h>
#include <stdio.h>

// TODO: Should char *buf be moved to the end and turned into an unsized char[]?
typedef struct SString {
	char *buf;
	size_t len;
	size_t sz;
} SString;

void initSString(SString *sstr);
ssize_t ssgetline(SString *restrict sstr, FILE *restrict fp);
char *ssset(SString *restrict sstr, size_t i, char c);
char *ssappend(SString *sstr, char c);
//const Charset ignorable_chars = DCS_LIST("\r");

#endif // SSTRING_H
