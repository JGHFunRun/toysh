/* shell.c: Manages shell state
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of jgsh - JGHFunRun's shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#include "shell.h"

#include "filemgmt.h"
#include "lexer.h"

#include <assert.h>
#include <errno.h>
#include <stdlib.h>

void initShell(ShellState *output, ArgInfo const *arg_info) {
	ShellState wip = {
		.shell_name = arg_info->shell_name,
		.arg0 = arg_info->filename != NULL
			? arg_info->filename
			: arg_info->shell_name,
		.prog_args = arg_info->prog_args,
		.prog_argc = arg_info->prog_argc,
	};
}

int execFile(ShellState *state, char const *filename) {
	FILE *fp = filename == NULL ? stdin : fopen(filename, "r");

	if (fp == NULL) {
		eprintf("Failed to open file: %s\nerrno: %d\n",
			filename, errno);

		exit(1);
	}

	nextTok(fp);

	fclose(fp);

	return 0;
}
