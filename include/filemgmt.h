/* filemgmt.h: header file for filemgmt.c
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of jgsh - JGHFunRun's shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#ifndef FILEMGMT_H
#define FILEMGMT_H

#include <stdio.h>
#include <stdarg.h>

enum {
	LE_LF	= 0x0A,
	LE_CR	= 0x0D,
	LE_LFCR = 0x0A0D,
	LE_CRLF	= 0x0D0A,
	/// Intended primarily for initially detecting the line ending of file
	LE_ANY  = 0x1111,
};

int eprintf(char const *restrict fmt, ...);
int veprintf(char const *restrict fmt, va_list ap);

bool fpisatty(FILE *fp);

void fplock(FILE *fp);
void fpunlock(FILE *fp);

int fgetcNonlock(FILE *fp);

ssize_t getlineAt(char **restrict str, size_t *restrict n,
		FILE *restrict fp, size_t whence);
ssize_t getline(char **restrict buf, size_t *restrict sz, FILE *restrict fp);

#endif // FILEMGMT_H
