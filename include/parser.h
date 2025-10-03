/* parser.h: header file for parser.c
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of ToySH - JGHFunRun's Toy Shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#ifndef PARSER_H
#define PARSER_H 1

#include "lexer.h"

typedef struct ParserState {
	LexerState lexer;
} ParserState;

void initParser(ParserState *parser);
void parseLine(ParserState *parser);

#endif // PARSER_H
