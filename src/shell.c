/* shell.c: Manages shell state
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of ToySH - JGHFunRun's Toy Shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#define _GNU_SOURCE

#include "shell.h"

#include "filemgmt.h"
#include "lexer.h"

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void initShell(ShellState *restrict output, ArgInfo const *restrict arg_info) {
	char const *filename = arg_info->filename;

	ShellState wip = {
		.shell_name = arg_info->shell_name,
		.arg0 = filename != NULL ?
			filename : arg_info->shell_name,
		.prog_args = arg_info->prog_args,
		.prog_argc = arg_info->prog_argc,
		.filename = filename,
		.fin = filename != NULL ?
			fopen(filename, "r") : stdin,
		.interactive = false,
	};

	if (wip.fin == NULL) {
		eprintf("Failed to open file: %s\nerrno: %d\n",
			filename, errno);

		exit(1);
	}

	if (fpisatty(wip.fin)) {
		eprintf("Interactive!\n");
		wip.interactive = true;
	}

	memcpy(output, &wip, sizeof(ShellState));
}

int sourcefp(ShellState *restrict state, FILE *restrict fp) {
	LexerState lstate;
	initLexer(&lstate);

	Token tok;

	TokType prev_tt = TOK_UNDETERMINED;

	if (ssgetline(&lstate.str, fp) == -1) {
		eprintf("Failed to read file\nerrno = %d\n", errno);
		return 1;
	}

	lstate.is_eof = true;

	do {
		initTok(&tok);

		eprintf("New token\n");
		prev_tt = nextTok(&lstate, &tok);
		eprintf("Got ");
		eprintTok(&tok);
		eprintf("\n");
	} while (prev_tt < TOK_EOF);

	return 0;
}
