/* main.c: Entry point to jgsh
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of jgsh - JGHFunRun's shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#include "args.h"
#include "shell.h"

#include <stdio.h>
#include <stdlib.h>

// TODO: heavy cleanup
int main(int argc, char const *const *argv) {
	ArgInfo arg_info;
	parseArgs(&arg_info, argc, argv);

	ShellState state;

	initShell(&state, &arg_info);

	int retcode = execFile(&state, arg_info.filename);

	printf("Process exited with code %i\n", retcode);

	return retcode;
}
