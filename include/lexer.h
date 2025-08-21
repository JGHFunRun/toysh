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

//#include <stddef.h>
#include <stdio.h>

// TODO: Should a seperate type be used for type of raw tokens?
typedef enum TokType {
	TOK_COMMENT = -1,
	TOK_UNDETERMINED = 0,
	TOK_LITERAL,
	TOK_WHITESPACE,
	TOK_NEWLINE,

	TOK_ERROR,
} TokType;

typedef struct Token {
	TokType type;
} Token;

/*typedef struct {
	size_t allocd;
	size_t len;
	Token *tokens;
} TokArr;*/

typedef struct LexerState {
} LexerState;

void nextTok(FILE *fp);

int fprintTok(FILE *fp, Token tok);
int eprintTok(Token tok);
int printTok(Token tok);

#endif // LEXER_H
