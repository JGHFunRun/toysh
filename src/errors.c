/* errors.c: TODO: short desc
 */

#include "errors.h"

#include <errno.h>
#include <stdio.h>

/// @brief A variadic <em>printf</em>-family function that outputs to `stderr`
///
/// Equivalent to calling `vfprintf(stderr, fmt, ap)`
///
/// @param fmt Standard `printf` format string
/// @param vap Standard `va_list` variadic arguments to <em>vprintf</em>-family
int veprintf(char const *restrict fmt, va_list vap) {
	return vfprintf(stderr, fmt, vap);
}

/// @brief A <em>printf</em>-family function that outputs to `stderr`
///
/// Equivalent to calling `fprintf(stderr, fmt, ...)`
///
/// @param fmt Standard `printf` format string
/// @param ... Standard variadic arguments to `printf`
int eprintf(char const *restrict fmt, ...) {
	va_list vap;
	va_start(vap, fmt);
	int rval = veprintf(fmt, vap);
	va_end(vap);

	return rval;
}

// "Variadic typed error printf"
static int vteprintf(char const *restrict etype, char const *restrict file,
		char const *restrict func, int line,
		char const *restrict fmt, va_list vap) {
	int rval;

	rval = eprintf("ToySH: INTERNAL %s in %s, %s line %d: ",
			etype, func, file, line);

	if (rval != 0) {
		return rval;
	}

	return veprintf(fmt, vap);
}

int vdbgprintf(char const *restrict file, char const *restrict func, int line,
		char const *restrict fmt, va_list vap) {
	return vteprintf("DEBUG", file, func, line, fmt, vap);
}

int dbgprintf(char const *restrict file, char const *restrict func, int line,
		char const *restrict fmt, ...) {
	va_list vap;
	va_start(vap, fmt);
	int rval = vdbgprintf(file, func, line, fmt, vap);
	va_end(vap);

	return rval;
}
