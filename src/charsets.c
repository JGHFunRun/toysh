/* charsets.c: Sets of characters (not character encodings; literal sets)
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of ToySH - JGHFunRun's Toy Shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#include "charsets.h"

#include "errors.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

const Charset nonascii_chars = DCS_REGION(0x80, 0xFF);

const Charset whitespace_chars = DCS_LIST(" \t");
const Charset newline_chars = DCS_LIST("\r\n");
//const Charset ignorable_chars = DCS_LIST("\r");

const Charset basic_latin_lc = DCS_REGION('a', 'z');
const Charset basic_latin_uc = DCS_REGION('A', 'Z');
//const Charset basic_latin = DCS_UNION(&basic_latin_lc, &basic_latin_uc);
/// @brief Numerals (Western Arabic/ASCII)
const Charset numerical_chars = DCS_REGION('0', '9');

static const Charset period_underscore_hyphen = DCS_LIST("._-");

/// @brief The portable filename character set should be supported on every
/// operating system, including ones that do not explicitly adhere to POSIX,
/// barring encoding-related shenanigans (see below).
///
/// It is defined by [POSIX](https://pubs.opengroup.org/onlinepubs/9799919799/)
/// (specifically [XBD 3.265](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/V1_chap03.html#tag_03_265) for POSIX.1-2024)
/// to be the alphanumerical characters plus the characters `.`, `_`, and `-`.
///
/// Note that the only portability issue I see being an issue is that some
/// encodings such as Baudot do not actually support cas
///
/// `libiconv` does not actually seem to support any such encodings, but I do
/// want to support them myself, just because I think it would be kind-of cool.
/// If nothing else, I would like to implement a caseless mode so that a
/// different conversion program (that is itself more powerful than libiconv)
/// could be used to support Baudot code and similarly caseless encodings.
const Charset pfn_charset =
	DCS_UNION(&basic_latin_lc, &basic_latin_uc, &numerical_chars,
			&period_underscore_hyphen);

// TODO: Could be optimized in a similar manner to optimizing strlen()
static bool isInCS_LIST(Charset const *cs, char c) {
	assert(cs->set_type == CS_LIST ||
		cs->set_type == CS_LCOMPLEMENT);

	for (size_t i=0; cs->list[i] != '\0'; i++) {
		if (cs->list[i] == c)
			return true;
	}

	return false;
}

static bool isInCS_REGION(Charset const *cs, char c) {
	assert(cs->set_type == CS_REGION);

	return c >= cs->region.start && c <= cs->region.end;
}

static bool isInCS_UNION(Charset const *cs, char c) {
	assert(cs->set_type == CS_UNION ||
		cs->set_type == CS_UCOMPLEMENT);

	for (size_t i=0; cs->sets[i] != NULL; i++) {
		if (isInCharset(cs->sets[i], c))
			return true;
	}

	return false;
}

static bool isInCS_LCOMPLEMENT(Charset const *cs, char c) {
	assert(cs->set_type == CS_LCOMPLEMENT);

	return !isInCS_LIST(cs, c);
}

static bool isInCS_UCOMPLEMENT(Charset const *cs, char c) {
	assert(cs->set_type == CS_UCOMPLEMENT);

	return !isInCS_UNION(cs, c);
}

#define CS_CASE(CS_TYPE) \
	case CS_TYPE: \
		return isIn ## CS_TYPE (cs, c)

bool isInCharset(Charset const *cs, char c) {
	switch (cs->set_type) {
		CS_CASE(CS_LIST);
		CS_CASE(CS_REGION);
		CS_CASE(CS_UNION);
		CS_CASE(CS_LCOMPLEMENT);
		CS_CASE(CS_UCOMPLEMENT);
		default:
			eprintf("Internal error: Unknown type of Charset\n");
			exit(2);
	}
}
