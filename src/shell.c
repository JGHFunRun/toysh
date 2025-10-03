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
#include "parser.h"

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
	ParserState pstate;

	initParser(&pstate);

	parseLine(&pstate);

	return 0;
}
