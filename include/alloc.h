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

void *safeRealloc(void **restrict buf, size_t *restrict sz, size_t new_sz);
void *autoiRealloc(char **restrict buf, size_t *restrict sz, size_t i);

#endif // ALLOC_H
