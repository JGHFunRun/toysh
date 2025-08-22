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
		return isIn ## CS_TYPE

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
