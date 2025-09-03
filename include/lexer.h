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
	TOK_COMMENT = -1,
	TOK_UNDETERMINED = 0,

	TOK_LITERAL, ///< Called simply `TOKEN` by POSIX.
	TOK_WHITESPACE,
	TOK_NEWLINE,

	TOK_EOF,
	TOK_ERROR,
	TOK_UNMATCHABLE,
} TokType;

typedef struct Token {
	TokType type;
} Token;


typedef enum LexerQuoting {
	LQ_UNQUOTED,
	LQ_SINGLE_QUOTE,
	LQ_DOUBLE_QUOTE,
	LQ_DS_DOUBLE_QUOTE, ///< `$"`...
} LexerQuoting;

typedef enum LexerExpanding {
	LE_NONE,
	//LE_BACKTICK,
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
	SString str;
	size_t pos;
	bool is_eof;

	LexerQuoting quot_stat;
	LexerExpanding expan_stat;
} LexerState;

void initLexer(LexerState *lexer);
TokType nextTok(LexerState *lexer);

int fprintTok(FILE *fp, Token tok);
int eprintTok(Token tok);
int printTok(Token tok);

#endif // LEXER_H
