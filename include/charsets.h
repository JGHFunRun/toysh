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
		CS_LCOMPLEMENT,
		CS_UCOMPLEMENT,
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
}

#define DCS_REGION(START, END) { \
	.set_type = CS_REGION, \
	.region = { \
		.start = START, \
		.end = END, \
	} \
}

#define DCS_UNION(...) { \
	.set_type = CS_UNION, \
	.sets = { __VA_ARGS__ __VA_OPT__(,) NULL } \
}

#define DCS_LCOMPLEMENT(CHARS) { \
	.set_type = CS_LCOMPLEMENT, \
	.list = CHARS, \
}

#define DCS_UCOMPLEMENT(...) { \
	.set_type = CS_UCOMPLEMENT, \
	.sets = { __VA_ARGS__ __VA_OPT__(,) NULL } \
}

extern const Charset nonascii_chars;
//extern const Charset basic_latin_lc;
//extern const Charset basic_latin_uc;
extern const Charset whitespace_chars;
extern const Charset newline_chars;
//extern const Charset ignorable_chars;
extern const Charset literal_chars;
extern const Charset pfn_charset;

#endif // CHARSETS_H
