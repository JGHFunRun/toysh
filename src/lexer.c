/* lexer.c: Convert text into tokens
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of jgsh - JGHFunRun's shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#include "lexer.h"

#include "charsets.h"
#include "filemgmt.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct RawToken {
	TokType type;
	size_t start;
	size_t len;
} RawToken;

typedef struct RTokArr {
	size_t allocd;
	size_t len;
	RawToken *toks;
} RTokArr;

static RawToken freshToken(RawToken *prevTok) {
	RawToken tok = {
		TOK_UNDETERMINED,
		0,
		0,
	};

	if (prevTok != NULL) {
		tok.start = prevTok->start + prevTok->len;
	}

	return tok;
}

static const size_t rtaAllocBlock = 16;

static void allocMore(RTokArr *arr) {
	arr->allocd += rtaAllocBlock;

	arr->toks = realloc(arr->toks, arr->allocd * sizeof(RawToken));
}

static RTokArr makeRTokArr() {
	RTokArr arr = {
		0,
		0,
		NULL,
	};

	allocMore(&arr);

	return arr;
}

static void pushToken(RTokArr *arr, RawToken tok) {
	assert(arr->len <= arr->allocd);

	if (arr->len >= arr->allocd) {
		allocMore(arr);
	}

	arr->toks[arr->len] = tok;
	arr->len++;
}


void nextTok(FILE *fp) {
	char *line = NULL;
	size_t allocd = 0;

	ssize_t len = getline(&line, &allocd, fp);

	if (len < 0) {
		int e_save = errno;

		if (feof(fp)) {
			eprintf("Unexpected <EOF> whilst reading file\n");
		}

		if (ferror(fp)) {
			eprintf("Error whilst reading line\nerrno: %d\n",
				e_save);
		}

		errno = e_save;

		return;
	}

	assert(line[len]   == '\0');
	assert(line[len-1] == '\n');

	for (size_t i=0; i<len; i++) {
	}

	printf("%s", line);
}

char const *stringifyTokType(TokType tt) {
	switch (tt) {
		case TOK_COMMENT:
			return "TOK_COMMENT";
		case TOK_UNDETERMINED:
			return "TOK_UNDETERMINED";
		case TOK_LITERAL:
			return "TOK_LITERAL";
		case TOK_WHITESPACE:
			return "TOK_WHITESPACE";
		case TOK_ERROR:
			return "TOK_ERROR";
		default:
			eprintf("Unknown TokType: %d\n", tt);
			exit(3);
	}
}

/// @brief Print a human-readable representation of \p tok to \p fp. Does not
/// print a newline character at the end.
///
/// @param fp `FILE*` to print to
/// @param tok `Token` to print
int fprintTok(FILE *fp, Token tok) {
	return fprintf(fp, "(%s)", stringifyTokType(t.type));
}

/// @brief Print \p tok to `stderr`. See `fprintTok()` for more details.
int eprintTok(Token tok) {
	return fprintTok(stderr, tok);
}

/// @brief Print \p tok to `stdout`. See `fprintTok()` for more details.
int printTok(Token tok) {
	return fprintTok(stdout, tok);
}
