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
#include <string.h>

typedef struct TokSpec {
	TokType matches_to;

	bool greed;
	enum {
		MM_END = 0,
		MM_CHARSET,
		MM_REGEX,
	} match_method;

	union {
		Charset const *match_cs;
		char const *match_regex;
	};
} TokSpec;

#define DTS_CHARSET(TOK_TYPE, GREED, CHARSET) { \
	.matches_to = TOK_TYPE, \
	.greed = GREED, \
	.match_method = MM_CHARSET, \
	.match_cs = &CHARSET, \
}

#define DTS_REGEX(TOK_TYPE, GREED, REGEX) { \
	.matches_to = TOK_TYPE, \
	.greed = GREED, \
	.match_method = MM_REGEX, \
	.match_regex = REGEX \
}

#define DTS_END { .match_method=MM_END }

const TokSpec specs[] = {
	DTS_CHARSET(TOK_WHITESPACE, true, whitespace_chars),
	DTS_REGEX(TOK_LITERAL, false, "'([^']*)'"),
	DTS_CHARSET(TOK_LITERAL, true, pfn_charset),
	DTS_END,
};

enum {
	MS_UNMATCHABLE = -1,
	MS_INCOMPLETE = 0,
};

void initLexer(LexerState *lexer) {
	LexerState wip = {
		.str = {
			.buf = NULL,
			.len = 0,
			.sz = 0,
		},
		.pos = 0,
		.is_eof = false,
	};

	memcpy(lexer, &wip, sizeof(LexerState));
}

static void procChar(LexerState *lexer, char c, size_t i) {
	if (lexer->quot_stat != LQ_UNQUOTED) {
		assert(1==0);
	}

	if (lexer->expan_stat != LE_NONE) {
		assert(1==0);
	}
}

TokType nextTok(LexerState *lexer) {
	printf("%s<EOL>\n", lexer->str.buf);

	if (lexer->pos == lexer->str.len) {
		if (!lexer->is_eof) {
			return TOK_UNDETERMINED;
		}

		// TODO: Detect if the current token can be delimited,
		// and do so if so

		return TOK_EOF;
	}

	for (size_t i=0; i < lexer->str.len; i++) {
		char c = lexer->str.buf[i];

		procChar(lexer, c, i);
	}

	printf("Lexer pass ended.\n");
}

#define STR_TOK_TYPE(TOK_TYPE) \
	case TOK_TYPE: \
		return (#TOK_TYPE)

char const *stringifyTokType(TokType tt) {
	switch (tt) {
		STR_TOK_TYPE(TOK_COMMENT);
		STR_TOK_TYPE(TOK_UNDETERMINED);
		STR_TOK_TYPE(TOK_LITERAL);
		STR_TOK_TYPE(TOK_WHITESPACE);
		STR_TOK_TYPE(TOK_ERROR);
		//default:
		//	eprintf("Unknown TokType during stringification: %d\n", tt);
		//	exit(3);
	}
}

/// @brief Print a human-readable representation of \p tok to \p fp. Does not
/// print a newline character at the end.
///
/// @param fp `FILE*` to print to
/// @param tok `Token` to print
int fprintTok(FILE *fp, Token tok) {
	return fprintf(fp, "(%s)",
	               stringifyTokType(tok.type));
}

/// @brief Prints \p tok to `stderr`. See `fprintTok()` for more details.
int eprintTok(Token tok) {
	return fprintTok(stderr, tok);
}

/// @brief Prints \p tok to `stdout`. See `fprintTok()` for more details.
int printTok(Token tok) {
	return fprintTok(stdout, tok);
}
