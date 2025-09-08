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

#define CHAR_CAT(CHARSET, CHAR, TYPE) \
	if (isInCharset(&(CHARSET), CHAR)) \
		return TYPE;

static TokType categChar(char c) {
	CHAR_CAT(whitespace_chars, c, TOK_WHITESPACE);
	CHAR_CAT(newline_chars, c, TOK_NEWLINE);
	return TOK_LITERAL;
}

typedef enum ProcResult {
	/// @brief Current character could be delimited if the next character is
	/// `EOF`.
	PROC_DELIMABLE,
	/// @brief A new character is absolutely needed to finish this Token.
	///
	/// If there is no more input (ie `EOF` reached), this will indicate an
	/// error in the input.
	PROC_UNDELIMABLE,

	/// Current character corresponds to a different TokType
	PROC_DELIM_FIRST,
	PROC_END_TOK, ///< Current character must be last in Token

	PROC_CHAR_INVAL, ///< Current character could not fit in any context
	PROC_ERROR,
} ProcRes;

static ProcRes procChar(LexerState *lexer, char c, size_t i, Token *tok) {
	// TODO: IMPLEMEEEENNNTINNNNGG
	if (lexer->expan_stat != LE_NONE) {
		eprintf("Unimplemented");
		assert(1==0);
	}

	if (lexer->quot_stat != LQ_UNQUOTED) {
		eprintf("Unimplemented");
		assert(1==0);
	}

	// TODO: some characters are operators in-and-of themselves. Currently,
	// such characters are treated as literals. Help a parsa out?
	
	TokType tt = categChar(c);

	if (tok->type == TOK_UNDETERMINED)
		tok->type = tt;

	if (tt != tok->type)
		return PROC_DELIM_FIRST;

	ssappend(&tok->str, c);

	return PROC_DELIMABLE;
}

static void initTok(Token *tok) {
	tok->type = TOK_UNDETERMINED;
	initSString(&tok->str);
}

TokType nextTok(LexerState *lexer) {
	Token tok;
	initTok(&tok);

	if (lexer->pos == lexer->str.len) {
		if (!lexer->is_eof) {
			return TOK_NEED_MORE;
		}

		if (lexer->is_delimable) {
			// TODO: delimit the token
		}

		return TOK_EOF;
	}

	for (size_t i=lexer->pos; i < lexer->str.len; i++) {
		char c = lexer->str.buf[i];

		procChar(lexer, c, i, &tok);
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
		STR_TOK_TYPE(TOK_NEWLINE);

		STR_TOK_TYPE(TOK_EOF);
		STR_TOK_TYPE(TOK_ERROR);
		STR_TOK_TYPE(TOK_UNMATCHABLE);
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
	return fprintf(fp, "(%s, '%s')",
	               stringifyTokType(tok.type), tok.str.buf);
}

/// @brief Prints \p tok to `stderr`. See `fprintTok()` for more details.
int eprintTok(Token tok) {
	return fprintTok(stderr, tok);
}

/// @brief Prints \p tok to `stdout`. See `fprintTok()` for more details.
int printTok(Token tok) {
	return fprintTok(stdout, tok);
}
