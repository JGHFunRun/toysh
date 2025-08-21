/* charsets.h: header file for charsets.c
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of ToySH - JGHFunRun's Toy Shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#ifndef CHARSETS_H
#define CHARSETS_H 1

typedef struct Charset {
	enum {
		CS_LIST,
		CS_REGION,
		CS_UNION,
		CS_COMPLEMENT,
	} set_type;

	union {
		char const *list;
		struct {
			char start;
			char end;
		} region;
	};

	struct Charset const *sets[];
} Charset;

bool isInCharset(Charset const *cs, char c);

#define DCS_LIST(CHARS) { \
	.set_type = CS_LIST, \
	.list = CHARS, \
	.subsets = {}, \
}

#define DCS_REGION(START, END) { \
	.set_type = CS_REGION, \
	.region = { \
		.start = START \
		.end = END \
	} \
	.subsets = {}, \
}

#define DCS_UNION(...) { \
	.set_type = CS_UNION, \
	.subsets = { __VA_ARGS__ __VA_OPT__(,) NULL } \
}

#define DCS_COMPLEMENT(...) { \
	.set_type = CS_COMPLEMENT, \
	.subsets = { __VA_ARGS__ __VA_OPT__(,) NULL } \
}

#endif // CHARSETS_H
