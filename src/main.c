/* main.c: Entry point to ToySH
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of ToySH - JGHFunRun's Toy Shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#include "main.h"

#include "args.h"
#include "shell.h"

#include <stdio.h>
#include <stdlib.h>

char const *invokedAs;

int main(int argc, char const *const *argv) {
	invokedAs = argv[0];

	ArgInfo arg_info;
	parseArgs(&arg_info, argc, argv);

	ShellState state;

	initShell(&state, &arg_info);

	int retcode = sourcefp(&state, state.fin);

	fclose(state.fin);

	printf("Process exited with code %i\n", retcode);

	return retcode;
}
