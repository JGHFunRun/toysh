/* filemgmt.c: Implementing funtions to manage FILE pointers.
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of ToySH - JGHFunRun's Toy Shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#include "filemgmt.h"

#include "macromgmt.h"

#include <errno.h>
//#include <limits.h>

#ifdef __unix__
#include <unistd.h>
//#include <sys/stat.h>
#endif // __unix__

#ifdef _WIN32
#include <io.h>
#endif // _WIN32

/// @brief A variadic <em>printf</em>-family function that outputs to `stderr`
///
/// Equivalent to calling `vfprintf(stderr, fmt, ap)`
///
/// @param fmt Standard `printf` format string
/// @param ap Standard `va_list` variadic arguments to <em>vprintf</em>-family
int veprintf(char const *restrict fmt, va_list ap) {
	return vfprintf(stderr, fmt, ap);
}

/// @brief A <em>printf</em>-family function that outputs to `stderr`
///
/// Equivalent to calling `fprintf(stderr, fmt, ...)`
///
/// @param fmt Standard `printf` format string
/// @param ... Standard variadic arguments to `printf`
int eprintf(char const *restrict fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	int rval = veprintf(fmt, ap);
	va_end(ap);

	return rval;
}

#ifdef __unix__
# define FPISATTY_UNIX 1
#elifdef _WIN32 // (__unix__)
# define FPISATTY_WIN32 1
#else // _WIN32
# error "Function fpisatty() has not been implemented for the target platform."
#endif // #else

/// @brief Checks if \p fp is a terminal.
///
/// Returns true if \p fp is a terminal, or false if \p fp is not a TTY or
/// an error occurs. On Windows, actually detects if \p fp is a "character
/// device", which may also include certain special files.
///
/// The only errors are `EBADF` and `EFAULT`, although `errno` will also be set
/// to `ENOTTY` (rarely, `EINVAL`; see below) if \p fp is not a TTY and no error
/// occurs (technically, this is also an error, but from a practical perspective
/// it is simply stating that \p fp is not a TTY). `EFAULT` will be set if \p fp
/// is `NULL` and `EBADF` will be set if \p fp is otherwise invalid. On some
/// older Linux kernels, may also set `errno` to `EINVAL` as a synonym of
/// `ENOTTY` for certain files, which is due to a violation of POSIX found only
/// on these versions of Linux, where only `ENOTTY` should be returned in such
/// cases.
///
/// @param fp `FILE*` to check.
// TODO: Currently untested
// TODO: Does Windows _isatty() set errno?
bool fpisatty(FILE *fp) {
	if (fp == NULL) {
		errno = EFAULT;
		return false;
	}

#ifdef FPISATTY_UNIX
	return isatty(fileno(fp));
#endif // FPISATTY_UNIX

#ifdef FPISATTY_WIN32
	// Why are you like this...
	return _isatty(_fileno(fp));
#endif // FPISATTY_WIN34
}


/// @brief Locks a `FILE` pointer. All calls must be paired with a call to
/// `fpunlock()`.
///
/// A thinly veiled method around native methods for locking `FILE` pointers.
/// As such, it does *not* check if \p fp is `NULL`. This function has no
/// recoverable errors, and should not error if \p fp is valid.
///
/// Example usage: reimplementing `fgetc()` with `fgetcNonlock()`:
///
/// ```
/// int my_fgetc(FILE *fp) {
/// 	fplock(fp);
/// 	int rval = fgetcNonlock(fp);
/// 	fpunlock(fp);
///
/// 	return rval;
/// }
/// ```
///
/// @param fp `FILE` pointer to lock. Must not be `NULL`.
void fplock(FILE *fp) {
#ifdef __unix__
	flockfile(fp);
	return;
#elifdef _WIN32 // (__unix__)
	_lock_file(fp);
	return;
#endif // _WIN32
}

/// @brief Unlocks a `FILE` pointer. Must always be used after you are finished
/// with `fplock()`.
///
/// @param fp `FILE` pointer to unlock. Must not be `NULL`.
void fpunlock(FILE *fp) {
#ifdef __unix__
	funlockfile(fp);
	return;
#elifdef _WIN32 // (__unix__)
	_unlock_file(fp);
	return;
#endif // _WIN32
}

#ifdef __unix__
# define BUILTIN_GETLINE 1
#endif

#ifndef BUILTIN_GETLINE
/// @brief For documentation and specification of getline(), see the man page
/// and [POSIX.1](https://pubs.opengroup.org/onlinepubs/9799919799/) entries
/// for getline(3), respectively.
///
/// Links:
/// * [POSIX.1-2024 specification](https://pubs.opengroup.org/onlinepubs/9799919799/functions/getdelim.html#tag_17_207)
/// * [Online FreeBSD man page](https://man.freebsd.org/cgi/man.cgi?apropos=0&sektion=0&query=getline)
/// * [GNU/Linux man page on man7.org](https://www.man7.org/linux/man-pages/man3/getline.3.html)
///  * [... on die.net](https://linux.die.net/man/3/getline)
///  * [... on the Ubuntu manuals website](https://manpages.ubuntu.com/manpages/xenial/man3/getline.3.html)
///  * [... on the Arch manuals website](https://man.archlinux.org/man/core/man-pages/getline.3.en)
/// * [The GNU website on line input](https://www.gnu.org/software/libc/manual/html_node/Line-Input.html)
int getline(char **restrict str, size_t *restrict n, FILE *restrict fp) {
	return getlineAt(str, n, fp, 0);
}
# error "Support for getline() on platforms that do not provide it has not been implemented"
#endif // BUILTIN_GETLINE
