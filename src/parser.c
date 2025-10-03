/* parser.c: Convert tokens into an AST
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of ToySH - JGHFunRun's Toy Shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#include "parser.h"

#include "errors.h"

void initParser(ParserState *parser) {
	initLexer(&parser->lexer);
}

void parseLine(ParserState *parser) {
	TokType tt;

	ssgetline(&parser->lexer.str, stdin);
	parser->lexer.pos = 0;
	parser->lexer.is_eof = true;

	do {
		Token tok;
		initTok(&tok);
		eprintf("New token!\n");
		tt = nextTok(&parser->lexer, &tok);
		eprintTok(&tok);
		eprintf("\nnextTok() => %s\n", stringifyTokType(tt));
	} while (tt != TOK_EOF && tt != TOK_NEWLINE);
}
