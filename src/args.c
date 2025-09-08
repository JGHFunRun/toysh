/* args.c: Implementing argument parsing
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of ToySH - JGHFunRun's Toy Shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#include "args.h"

#include "invocation.h"

#include <stddef.h>
//#include <stdlib.h>
#include <string.h>

void parseArgs(ArgInfo *restrict arg_info,
               int argc, char const *const *restrict argv) {
	ArgInfo wip = {
		.shell_name = invoked_as,
		.filename = argv[1],
		.prog_argc = 0,
		.prog_args = NULL,
	};

	if (argc > 2) {
		wip.prog_argc = argc - 2;
		wip.prog_args = argv + 2;
	}

	memcpy(arg_info, &wip, sizeof(ArgInfo));
}
