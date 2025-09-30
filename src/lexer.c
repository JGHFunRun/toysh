/* lexer.c: Convert text into tokens
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of ToySH - JGHFunRun's Toy Shell
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

		.is_delimable = false,
		.quot_stat = LQ_UNQUOTED,
		.expan_stat = LE_NONE,
	};

	memcpy(lexer, &wip, sizeof(LexerState));
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
	/// Current character must be last in Token
	PROC_END_TOK,

	/// Current character could not fit in any context
	PROC_CHAR_INVAL,
	PROC_ERROR,
} ProcRes;

static ProcRes tryAppendChar(Token *tok, char c, TokType tt, ProcRes succ_val) {
	if (tok->type == TOK_UNDETERMINED)
		tok->type = tt;

	if (tok->type != tt)
		return PROC_DELIM_FIRST;

	ssappend(&tok->str, c);

	return succ_val;
}

// TODO: It's getting long
static ProcRes procChar(LexerState *lexer, char c, Token *tok) {
	if (lexer->amidst_comment) {
		assert(tok->type == TOK_UNDETERMINED);

		if (isInCharset(&newline_chars, c)) {
			lexer->amidst_comment = false;
			tok->type = TOK_NEWLINE;

			ssappend(&tok->str, c);

			return PROC_END_TOK;
		}

		eprintf("Inside a comment; discarding [%c]\n", c);

		return PROC_DELIMABLE;
	}

	// TODO: IMPLEMEEEENNNTINNNNGG
	if (lexer->expan_stat != LE_NONE) {
		eprintf("Unimplemented");
		exit(1);
	}

	if (lexer->quot_stat != LQ_UNQUOTED) {
		eprintf("Unimplemented");
		exit(1);
	}

	// TODO: some characters are operators in-and-of themselves. Currently,
	// such characters are treated as literals. Help a parsa out?

	if (c == '#') {
		if (tok->type != TOK_UNDETERMINED)
			return PROC_DELIM_FIRST;

		lexer->amidst_comment = true;

		return PROC_DELIMABLE;
	}

	if (isInCharset(&whitespace_chars, c)) {
		if (tok->type != TOK_UNDETERMINED)
			return PROC_DELIM_FIRST;

		return PROC_DELIMABLE;
	}

	if (isInCharset(&newline_chars, c)) {
		return tryAppendChar(tok, c, TOK_NEWLINE, PROC_END_TOK);
	}

	return tryAppendChar(tok, c, TOK_LITERAL, PROC_DELIMABLE);
}

void initTok(Token *tok) {
	tok->type = TOK_UNDETERMINED;
	initSString(&tok->str);
}

TokType nextTok(LexerState *lexer, Token *tok) {
	for (; lexer->pos < lexer->str.len; lexer->pos++) {
		char c = lexer->str.buf[lexer->pos];

		ProcRes r = procChar(lexer, c, tok);

		if (r == PROC_DELIM_FIRST) {
			return tok->type;
		}

		lexer->is_delimable = r == PROC_DELIMABLE;

		if (r == PROC_END_TOK) {
			lexer->pos++;
			return tok->type;
		}
	}

	if (!lexer->is_eof) {
		return TOK_NEED_MORE;
	}

	if (tok->type != TOK_UNDETERMINED) {
		if (lexer->is_delimable) {
			return tok->type;
		} else {
			return TOK_BAD_EOF;
		}
	}

	tok->type = TOK_EOF;

	return TOK_EOF;
}

#define STR_TOK_TYPE(TOK_TYPE) \
	case TOK_TYPE: \
		return (#TOK_TYPE)

char const *stringifyTokType(TokType tt) {
	switch (tt) {
		STR_TOK_TYPE(TOK_UNDETERMINED);

		STR_TOK_TYPE(TOK_LITERAL);
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
int fprintTok(FILE *fp, Token const *tok) {
	return fprintf(fp, "(%s, '%s')",
	               stringifyTokType(tok->type), tok->str.buf);
}

/// @brief Prints \p tok to `stderr`. See `fprintTok()` for more details.
int eprintTok(Token const *tok) {
	return fprintTok(stderr, tok);
}

/// @brief Prints \p tok to `stdout`. See `fprintTok()` for more details.
int printTok(Token const *tok) {
	return fprintTok(stdout, tok);
}
