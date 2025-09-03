/* shell.h: header file for shell.c
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of jgsh - JGHFunRun's shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#ifndef SHELL_H
#define SHELL_H

#include "args.h"

#include <stdio.h>

typedef struct {
	char const *shell_name;
	char const *arg0;
	char const *const *prog_args;
	int prog_argc;
	char const *filename;
	FILE *fin;
	bool interactive;
} ShellState;

void initShell(ShellState *state, ArgInfo const *arg_info);

int sourcefp(ShellState *state, FILE *fp);

#endif // SHELL_H
