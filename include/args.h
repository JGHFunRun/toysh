/* args.h: header file for args.c
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of ToySH - JGHFunRun's Toy Shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#ifndef ARGS_H
#define ARGS_H 1

typedef struct ArgInfo {
	char const *shell_name;
	char const *filename;
	int prog_argc;
	char const *const *prog_args;
} ArgInfo;

void parseArgs(ArgInfo *restrict arg_info,
               int argc, char const *const *restrict argv);

#endif // ARGS_H
