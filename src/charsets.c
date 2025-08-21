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

#include "filemgmt.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

// TODO: Could be optimized in a similar manner to optimizing strlen()
static bool isInCSList(Charset const *cs, char c) {
	assert(cs->set_type == CS_LIST);

	for (size_t i=0; cs->list[i] != '\0'; i++) {
		if (cs->list[i] == c)
			return true;
	}

	return false;
}

static bool isInCSRegion(Charset const *cs, char c) {
	assert(cs->set_type == CS_REGION);

	return c >= cs->region.start && c <= cs->region.end;
}

static bool isInCSUnion(Charset const *cs, char c) {
	assert(cs->set_type == CS_UNION);

	for (size_t i=0; cs->sets[i] != NULL; i++) {
		if (isInCharset(cs->sets[i], c))
			return true;
	}

	return false;
}

static bool isInCSComplement(Charset const *cs, char c) {
	assert(cs->set_type == CS_COMPLEMENT);

	for (size_t i=0; cs->sets[i] != NULL; i++) {
		if (isInCharset(cs->sets[i], c))
			return false;
	}

	return true;
}

bool isInCharset(Charset const *cs, char c) {
	switch (cs->set_type) {
		case CS_LIST:
			return isInCSList(cs, c);
		case CS_REGION:
			return isInCSRegion(cs, c);
		case CS_UNION:
			return isInCSUnion(cs, c);
		case CS_COMPLEMENT:
			return isInCSComplement(cs, c);
		default:
			eprintf("Internal error: Unknown type of Charset\n");
			exit(2);
	}
}
