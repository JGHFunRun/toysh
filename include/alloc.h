/* alloc.h: header file for alloc.c
 *
 * Copyright (C) 2025 JGHFunRun
 * 
 * This file is part of ToySH - JGHFunRun's Toy Shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#ifndef ALLOC_H
#define ALLOC_H 1

#include <stddef.h>

// TODO: Rework this to operate on indices instead of sizes for array operations

void *safeRealloc(void **restrict buf, size_t *restrict sz, size_t new_sz);
char *autoiAlloc(char **restrict buf, size_t *restrict sz, size_t i);

#define safeReallocArr(buf, sz, new_n) \
	((typeof(*buf)) safeRealloc((void**) buf, sz, (new_n) * sizeof(**buf)))


#endif // ALLOC_H
