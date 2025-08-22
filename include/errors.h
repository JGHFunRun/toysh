/* errors.h: header file for errors.c
 */

#ifndef ERRORS_H
#define ERRORS_H 1

#include <stdarg.h>

int veprintf(char const *restrict fmt, va_list vap);
int eprintf(char const *restrict fmt, ...);

/*
void verrprintf(char const *restrict file, char const *restrict func, int line,
		char const *restrict fmt, va_list vap);
void errprintf(char const *restrict file, char const *restrict func, int line,
		char const *restrict fmt, ...);
void unrprintf(char const *restrict file, char const *restrict func, int line,
		char const *restrict fmt, ...);
*/

int vdbgprintf(char const *restrict file, char const *restrict func, int line,
		char const *restrict fmt, va_list vap);
int dbgprintf(char const *restrict file, char const *restrict func, int line,
		char const *restrict fmt, ...);

#endif // ERRORS_H
