/* lexer.h: header file for lexer.c
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of ToySH - JGHFunRun's Toy Shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#ifndef LEXER_H
#define LEXER_H

#include "sstring.h"

#include <stddef.h>
#include <stdio.h>

// TODO: Should a seperate type be used for type of raw tokens?
typedef enum TokType {
	//TOK_COMMENT = -1,

	TOK_UNDETERMINED = 0,
	TOK_NEED_MORE,

	TOK_LITERAL, ///< Called simply `TOKEN` by POSIX.
	TOK_NEWLINE,

	TOK_EOF,
	TOK_ERROR,
	TOK_UNMATCHABLE,
	TOK_BAD_EOF,
} TokType;

typedef struct Token {
	TokType type;

	union {
		SString str;
		char c;
	};
} Token;


typedef enum LexerQuoting {
	LQ_UNQUOTED,
	LQ_SINGLE_QUOTE,
	LQ_DOUBLE_QUOTE,
	LQ_DS_DOUBLE_QUOTE, ///< `$"`...
} LexerQuoting;

typedef enum LexerExpanding {
	LE_NONE,
	LE_BACKTICK,
	LE_DS_SEARCHING,
	LE_DS_SIMPLEVAR,
	LE_DS_CB,
	LE_DS_PAREN
} LexerExpanding;

typedef enum LexerMode {
	LM_ORDINARY,
	LM_AWAIT_HERE_DOC,
	LM_HERE_DOC,
} LexerMode;

typedef struct LexerState {
	// TODO: Make a wrapper to versatilely read the next character...
	SString str;
	size_t pos;
	bool is_eof;

	bool is_delimable;
	bool amidst_comment;

	LexerQuoting quot_stat;
	LexerExpanding expan_stat;
} LexerState;

void initLexer(LexerState *lexer);
void initTok(Token *tok);
TokType nextTok(LexerState *lexer, Token *tok);

char const *stringifyTokType(TokType tt);
int fprintTok(FILE *fp, Token const *tok);
int eprintTok(Token const *tok);
int printTok(Token const *tok);

#endif // LEXER_H
